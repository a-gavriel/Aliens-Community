#ifndef _ALIEN_H_
#define _ALIEN_H_


#include <sys/types.h>
#include <unistd.h>

#include "../include/Lmutex.h"
// Aliens struct
typedef struct aliens {
	pid_t threadID;  
    int speed;
    int weight;
    int time;
    int position;
    char alienType;
} alien_t;

const char alienTypes[6];
const int intersection_Atop_Bbottom[2][3];
const int intersection_Abottom_Btop[2][3];
const int exit_route[2];

const int Atop[3] ;
const int Abottom[3];
const int Bbottom[3] ;
const int Btop[3];

alien_t aliens_A_in [32];
alien_t aliens_A_out [24];
alien_t aliens_A_top_left [12];
alien_t aliens_A_top_center [5];
alien_t aliens_A_top_right [12];
alien_t aliens_B_top_left [12];
alien_t aliens_B_top_center [5];
alien_t aliens_B_top_right [11];
alien_t aliens_A_bottom_left [9];
alien_t aliens_A_bottom_center [4];
alien_t aliens_A_bottom_right [11];
alien_t aliens_B_bottom_left [9];
alien_t aliens_B_bottom_center [4];
alien_t aliens_B_bottom_right [10];
alien_t aliens_B_in [32];
alien_t aliens_B_out [23];
alien_t aliens_bridge_left [5];
alien_t aliens_bridge_center [5];
alien_t aliens_bridge_right [5];

alien_t *routes[19];

int getAlien(int x, int y, unsigned int button);

void* alienloop(void* route_number_ptr);

int generateAlien( const char* alien_type );
int timedsleep(int sleeptime, alien_t* alien);
int move_through_road(int old_position, int route_number, int sleeptime, char* alien_type);
int alien_start(char* alien_type, int* direction, int* sleeptime );
lmutex_t lmutex;

int init_mutex();
void kill_threads();

#endif