#define _GNU_SOURCE
#include <sys/syscall.h>
//#include <sys/types.h>
//#include <unistd.h>

#include "../include/alien.h"
#include "../include/Lpthreads.h"
#include "../include/graph_points.h"

#define A_START 1
#define B_START 15

const char alienTypes[6] = {'N','A','B','n','a','b'};

alien_t *routes[19] = { aliens_A_in, aliens_A_out, aliens_A_top_left, 
aliens_A_top_center, aliens_A_top_right, aliens_B_top_left, 
aliens_B_top_center, aliens_B_top_right, aliens_A_bottom_left, 
aliens_A_bottom_center, aliens_A_bottom_right, aliens_B_bottom_left, 
aliens_B_bottom_center, aliens_B_bottom_right, aliens_B_in, aliens_B_out,
aliens_bridge_left, aliens_bridge_center, aliens_bridge_right};

int getAlien(int x, int y){
    printf("Coords %d,%d \n",x,y);
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
                printf("Clicked on route %d , position %d \n",i,j);
                if ( cid != 0 ){
                    printf("Alien here! \n");                
                    return i*100 + j;            
            }
            }
            
        }
    }
    return -1;
}

void *alienloop(void* alien_type_v){
    char* alien_type = (char*) alien_type_v;
    int route_number;
    int direction;
    if (*alien_type == 'N' || *alien_type == 'A' || *alien_type == 'B'){
        route_number = A_START;
        direction = 0;
    }else if(*alien_type == 'n' || *alien_type == 'a' || *alien_type == 'b'){
        route_number = B_START;
        direction = 1;
    }
    int position = 0;
    int sleeptime = rand()%300000+100000;    
    alien_t *  current_route = routes[route_number];
    int current_route_size = routes_sizes[route_number];

    alien_t newalien = {.threadID = syscall(SYS_gettid),
                        .speed = rand()%50,
                        .weight = rand()%50,
                        .time = sleeptime,
                        .position = 0,
                        .alienType = *alien_type}; 
    current_route[0] = newalien;
    while (position < current_route_size - 1){
        //printf("I am %d, position %d, sleeptime %d, next is %d\n", 1, 
        //    position, sleeptime, current_route[position+1].threadID);
        while(current_route[position + 1].threadID != 0){            
            //printf("waiting for alien %d to move from %d\n", current_route[position+1].threadID , position +1);
            usleep(sleeptime);
        }
        usleep(sleeptime);
        current_route[position+1] = current_route[position];        
        position++;
        current_route[position].position = position; 
        current_route[position - 1].threadID = 0;
    }
    printf("Reached final position %d !, now exiting aliens...\n",position);
    usleep(sleeptime);

    int Atop[3]  = {2,3,4};
    int Abottom[3] = {8,9,10};

    int Bbottom[3]  = {11,12,13};
    int Btop[3] = {5,6,7};

    int rand_select = rand()%3;
    int new_route_num;
    if (direction == 0){
        new_route_num = Atop[rand_select];
    }else{
        new_route_num = Bbottom[rand_select];
    }
    
    alien_t *  new_route = routes[new_route_num];
    // Selection Atop route
    while(new_route[0].threadID != 0){
        usleep(sleeptime);
        rand_select = rand()%3;
        if (direction == 0){
            new_route_num = Atop[rand_select];
        }else{
            new_route_num = Bbottom[rand_select];
        }
        new_route = routes[new_route_num];
    }
    // Entering Atop
    new_route[0] = current_route[position];
    current_route[position].threadID = 0;
    current_route = new_route;
    route_number = new_route_num;
    position = 0;
    new_route[0].position = 0;
    current_route_size = routes_sizes[route_number];        

    while (position < current_route_size - 1){
        usleep(sleeptime);
        while(current_route[position + 1].threadID != 0){                        
            usleep(sleeptime);
        }            
        current_route[position+1] = current_route[position];        
        position++;
        current_route[position].position = position; 
        current_route[position - 1].threadID = 0;
    }
    printf("moved to bridge!\n");
    // Reached bridge!
    usleep(sleeptime);
    
    // Force copy outside bridge
    
    

    if (direction == 0){
        new_route_num = Abottom[rand_select];
    }else{
        new_route_num = Btop[rand_select];
    }

    new_route = routes[new_route_num];
    
    // Check if after bridge route is full
    while(new_route[0].position != 0){
        printf("crossing bidge %d, %d\n",new_route_num,new_route[0].position );
        usleep(sleeptime);
    }

    current_route = new_route;
    route_number = new_route_num;
    position = 0;
    current_route_size = routes_sizes[route_number];   
    
    while (position < current_route_size - 1){
        usleep(sleeptime);
        while(current_route[position + 1].threadID != 0){                        
            usleep(sleeptime);
        }            
        current_route[position+1] = current_route[position];        
        position++;
        current_route[position].position = position; 
        current_route[position - 1].threadID = 0;
    }

    if (direction == 0){
        new_route_num = 14;
    }else{
        new_route_num = 0;
    }

    new_route = routes[new_route_num];

    // Check if Bin route 
    while(new_route[0].threadID != 0){
        usleep(sleeptime);
    }

    new_route[0] = current_route[position];
    current_route[position].threadID = 0;
    

    current_route = new_route;
    route_number = new_route_num;
    position = 0;
    current_route_size = routes_sizes[route_number];
    while (position < current_route_size - 1){
        usleep(sleeptime);
        while(current_route[position + 1].threadID != 0){                        
            usleep(sleeptime);
        }            
        current_route[position+1] = current_route[position];        
        position++;
        current_route[position].position = position; 
        current_route[position - 1].threadID = 0;
    }


    usleep(sleeptime);
    current_route[position].threadID = 0;

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
        printf("Community %c created new alien!\n", *alien_type);
    }
    return 0;
}
