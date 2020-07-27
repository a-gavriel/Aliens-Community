#ifndef _ALIEN_H_
#define _ALIEN_H_

#include <pthread.h> 
#include "graph_points.h"

const char alienTypes[3] = {'N','A','B'};
const int starting_routes[2] = {1,15};


// Aliens struct
typedef struct aliens {
	pthread_t threadID;  
    int speed;
    int weight;
    int time;
    int x;
    int y;
    char alienType;
} alien_t;

alien_t list_A_in [32];
alien_t list_A_out [24];
alien_t list_down_top_left [12];
alien_t list_down_top_center [5];
alien_t list_down_top_right [12];
alien_t list_up_top_left [12];
alien_t list_up_top_center [5];
alien_t list_up_top_right [11];
//alien_t list_bridge_left [];
//alien_t list_bridge_center [];
//alien_t list_bridge_right [];
alien_t list_down_bottom_left [9];
alien_t list_down_bottom_center [4];
alien_t list_down_bottom_right [11];
alien_t list_up_bottom_left [9];
alien_t list_up_bottom_center [4];
alien_t list_up_bottom_right [10];
alien_t list_B_in [32];
alien_t list_B_out [23];

alien_t *routes[16] = { list_A_in, list_A_out, list_down_top_left, 
list_down_top_center, list_down_top_right, list_up_top_left, 
list_up_top_center, list_up_top_right, list_down_bottom_left, 
list_down_bottom_center, list_down_bottom_right, list_up_bottom_left, 
list_up_bottom_center, list_up_bottom_right, list_B_in, list_B_out};

int getAlien(int x, int y){
    printf("Coords %d,%d \n",x,y);
    int cx, cy;
    pthread_t cid;
    int clicked_counter = 0;
    for (int i = 0; i< 16; ++i){
        alien_t* currentRoute = routes[i];        
        for (int j = 0; j < routes_sizes[i] ; ++j){
            cid = currentRoute[j].threadID;
            cx = currentRoute[j].x;
            cy = currentRoute[j].y;
            if ((cid != 0) && (cx < x && x < cx+30 && cy < y && y < cy+30 )){
                printf("Clicked on route %d , alien %d\n",i,j);                
                return i*100 + j;
            
            }
        }
    }
    return -1;
}

void* alienloop(void* route_number_ptr){
    int route_number = *((int*) route_number_ptr);
    int position = 0;
    int sleeptime = rand()%3+1;    
    alien_t *  current_route = routes[route_number];
    int current_route_size = routes_sizes[route_number];
    const Point* route_coords = routes_coords[route_number];
    int x = route_coords[0].x;
    int y = route_coords[0].y;

    pthread_t tid = pthread_self();
    alien_t newalien = {.threadID = pthread_self(),
                        .speed = rand()%50,
                        .weight = rand()%50,
                        .time = rand()%50,
                        .x = x,
                        .y = y,
                        .alienType = rand()%3}; 
    current_route[0] = newalien;
    while (position < current_route_size - 1){
        printf("I am %ld, position %d, sleeptime %d, next is %ld\n", tid, 
            position, sleeptime, current_route[position+1].threadID);
        while(current_route[position + 1].threadID != 0){            
            printf("waiting for alien %ld to move from %d\n", current_route[position+1].threadID , position +1);
            sleep(sleeptime);
        }
        sleep(sleeptime);
        current_route[position+1] = current_route[position];        
        position++;
        current_route[position - 1].threadID = 0;
    }
    printf("Reached final position %d !, now exiting list...\n",position);
    sleep(sleeptime);
    current_route[position].threadID = 0;

    pthread_exit(NULL); 
}

int generateAlien( char community ){
    const int* routeNumber;
    if (community == 'A'){
        routeNumber = starting_routes;
    }else if(community == 'B'){
        routeNumber = starting_routes+1;
    }
    alien_t * startingroute = routes[*routeNumber];

    if (startingroute[0].threadID == 0){
        startingroute[0].threadID = 1;
        pthread_t ptid; 
        pthread_create(&ptid, NULL, &alienloop, (void* )routeNumber); 
        printf("Community %c created new alien!\n", community);
    }
}

    
#endif