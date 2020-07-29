#define _GNU_SOURCE
#include <sys/syscall.h>
//#include <sys/types.h>
//#include <unistd.h>
#include <signal.h>

#include "../include/alien.h"
#include "../include/Lpthreads.h"
#include "../include/ConfigFile_Reader.h"
#include "../include/graph_points.h"

#define A_START 1
#define B_START 15

const char alienTypes[6] = {'N','A','B','n','a','b'};

const int Atop[3]  = {2,3,4};
const int Abottom[3] = {8,9,10};
const int Bbottom[3]  = {11,12,13};
const int Btop[3] = {5,6,7};

const int intersection_Atop_Bbottom[2][3] = {{2,3,4},{11,12,13}};
const int intersection_Abottom_Btop[2][3] = {{8,9,10},{5,6,7}};
const int exit_route[2] = {14,0};

alien_t *routes[19] = { aliens_A_in, aliens_A_out, aliens_A_top_left, 
aliens_A_top_center, aliens_A_top_right, aliens_B_top_left, 
aliens_B_top_center, aliens_B_top_right, aliens_A_bottom_left, 
aliens_A_bottom_center, aliens_A_bottom_right, aliens_B_bottom_left, 
aliens_B_bottom_center, aliens_B_bottom_right, aliens_B_in, aliens_B_out,
aliens_bridge_left, aliens_bridge_center, aliens_bridge_right};

int init_mutex(){
    Lmutex_init(&lmutex, 1);
    return 1;
}

int timedsleep(int sleeptime, alien_t* alien){
    if (alien->time > sleeptime){
        alien->time -= sleeptime;
    }else if(alien->alienType == 'B' || alien->alienType == 'b'){
        alien->time = 0;                
        kill(alien->threadID, SIGTSTP);                
    }
    return usleep(sleeptime);
}

int getAlien(int x, int y, unsigned int button){    
    int cx, cy;
    pid_t cid;
    for (int i = 0; i< 16; ++i){
        alien_t* currentRoute = routes[i];  
        const Point *currentRoute_coords = routes_coords[i];      
        for (int j = 0; j < routes_sizes[i] ; ++j){
            cid = currentRoute[j].threadID;
            cx = (int)currentRoute_coords[j].x;
            cy = (int)currentRoute_coords[j].y;            
            if (cx < x && x < cx+30 && cy < y && y < cy+30 ) {                
                if ( button == 1 && cid != 0 ){                    
                    kill(cid,SIGKILL);
                    currentRoute[j].threadID = 0;
                    return i*100 + j;            
                }else if(button == 2 && cid != 0 && currentRoute[j].time == 0){
                    currentRoute[j].time = alienB.execution_time*1000000;
                    kill(cid,SIGCONT);
                }
            }            
        }
    }
    return -1;
}


int alien_start(char* alien_type, int* direction, int* sleeptime ){
    int route_number;
    if (*alien_type < 0x60){
        route_number = A_START;
        *direction = 0;
    }else{
        route_number = B_START;
        *direction = 1;
    }

    if(*alien_type == 'N' || *alien_type == 'n'){
        *sleeptime = (int) alienN.speed;        
    }else if(*alien_type == 'A' || *alien_type == 'a'){
        *sleeptime = (int) (1.2* (float)alienN.speed);        
    }else if(*alien_type == 'B' || *alien_type == 'b'){
        *sleeptime = (int)(((float)(rand()%150+50))/100 * (float)alienN.speed) ;        
    }    

    (routes[route_number])[0] = (alien_t){.threadID = syscall(SYS_gettid),
                        .speed = *sleeptime,
                        .weight = rand()%50,
                        .time = alienB.execution_time*1000000,
                        .position = 0,
                        .alienType = *alien_type}; 
    
    return route_number;
}


int move_through_road(int old_position, int route_number, int sleeptime, char* alien_type){
    alien_t *  current_route = routes[route_number];
    int current_route_size = routes_sizes[route_number];
    int position = old_position;

    while (position < current_route_size - 1){
        while(current_route[position + 1].threadID != 0){            
            timedsleep(sleeptime, &(current_route[position]));
        }
        timedsleep(sleeptime, &(current_route[position]));
        current_route[position+1] = current_route[position];        
        position++;
        current_route[position].position = position; 
        current_route[position - 1].threadID = 0;
    }    
    timedsleep(sleeptime, &(current_route[position]));
    return position;
}



void* alienloop(void* alien_type_v){
    char* alien_type = (char*) alien_type_v;
    int route_number;
    int direction;
    int sleeptime;
    pid_t cid;
    route_number = alien_start(alien_type, &direction, &sleeptime );
    int position = 0;
    cid = (routes[route_number])[0].threadID;
    position = move_through_road(position, route_number, sleeptime, alien_type);    

    // Reached intersection_Atop_Bbottom
    int rand_select = rand()%3;
    int new_route_num;
    new_route_num = intersection_Atop_Bbottom[direction][rand_select];        
    alien_t *  new_route = routes[new_route_num];
    // Selection Atop route
    while(new_route[0].threadID != 0){
        timedsleep(sleeptime, &((routes[route_number])[position]));
        rand_select = rand()%3;
        new_route_num = intersection_Atop_Bbottom[direction][rand_select];
        new_route = routes[new_route_num];
    }
    // Entering intersection_Atop_Bbottom
    new_route[0] = (routes[route_number])[position];
    (routes[route_number])[position].threadID = 0;
    route_number = new_route_num;
    position = 0;    
    new_route[0].position = 0;          
    position = move_through_road(position, route_number, sleeptime, alien_type); 
    
    // Reached bridge!    
    timedsleep(sleeptime, &((routes[route_number])[position]));
    // Get route after bridge
    new_route_num = intersection_Abottom_Btop[direction][rand_select];
    new_route = routes[new_route_num];        
    // Check if placed after route?
    while(new_route[0].threadID != cid){        
        timedsleep(sleeptime, &((routes[route_number])[position]));
    }
        
    route_number = new_route_num;
    position = 0;  
    position = move_through_road(position, route_number, sleeptime, alien_type); 
    
    // Reached intersection_Abottom_Btop
    new_route_num = exit_route[direction];
    new_route = routes[new_route_num];
    // Check if second intersection
    while(new_route[0].threadID != 0){
        timedsleep(sleeptime, &((routes[route_number])[position]));
    }
    new_route[0] = (routes[route_number])[position];
    (routes[route_number])[position].threadID = 0;
    route_number = new_route_num;
    position = 0;

    position = move_through_road(position, route_number, sleeptime, alien_type); 
    // Reached Destination!
    (routes[route_number])[position].threadID = 0;
    Lthread_end(NULL); 
    return NULL;
}

int generateAlien( const char* alien_type ){
    int route_number;
    if (*alien_type == 'N' || *alien_type == 'A' || *alien_type == 'B'){
        route_number = A_START;
    }else if(*alien_type == 'n' || *alien_type == 'a' || *alien_type == 'b'){
        route_number = B_START;
    }else{
        return -1;
    }
    alien_t * startingroute = routes[route_number];

    if (startingroute[0].threadID == 0){
        startingroute[0].threadID = 1;
        lpthread_t ptid; 
        Lthread_create(&ptid, NULL, &alienloop, (void* )alien_type);         
    }
    return 0;
}

void kill_threads(){
    pid_t cid;
    for (int i = 0; i< 19; ++i){
        alien_t* currentRoute = routes[i];        
        for (int j = 0; j < routes_sizes[i] ; ++j){
            cid = currentRoute[j].threadID;           
            if (cid != 0) {
                kill(cid,SIGTERM);            
            }
        }
    }
}