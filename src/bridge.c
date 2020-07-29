#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "../include/alien.h"
#include "../include/bridge.h"
#include "../include/graph_points.h"

const int bridge_pairs [2][3][2] = {
    {{2,8},{3,9},{4,10}},
    {{11,5},{12,6},{13,7}}
    };

const int bridge_routes [3] = {16,17,18};

const int bridge_pos [2][5] = {{0,1,2,3,4},{4,3,2,1,0}};
const int bridge_dirs [2] = {1,-1};

void BridgeMovements()
{
    switch (left_bridge.type)
    {
        case 0: //0 = Algorithm Y          

            break;
        case 1: //1 = Algorithm Sem          

            break;
        case 2: //2 = Algorithm Survival          
            Survival_AUX(&left_bridge);
        break;
        default:
            break;
    }

    switch (center_bridge.type)
    {
        case 0: //0 = Algorithm Y          

            break;
        case 1: //1 = Algorithm Sem          

            break;
        case 2: //2 = Algorithm Survival          
            Survival_AUX(&center_bridge);
        break;
        default:
            break;
    }

    switch (right_bridge.type)
    {
        case 0: //0 = Algorithm Y          

            break;
        case 1: //1 = Algorithm Sem          

            break;
        case 2: //2 = Algorithm Survival          
            Survival_AUX(&right_bridge);
        break;
        default:
            break;
    }
    Move_aliens(&left_bridge);
    Move_aliens(&center_bridge);
    Move_aliens(&right_bridge);
    //Move();
}

void Survival(bridge_params_t *bridge)
{
    switch (bridge->pos)
    {
        case 1: //Center          
            Survival_AUX(bridge);
            break;
        case 2: //Right          
            Survival_AUX(bridge);
            break;
        case 0: //Left          
            Survival_AUX(bridge);
        break;
        default:
            break;
    }
}


void Survival_AUX(bridge_params_t *bridge)
{
    if(bridge->count == 0)
    {
        int start_route = bridge_pairs[0][bridge->pos][0];
        alien_t* startA = routes[start_route]+routes_sizes[start_route]-1;
        bridge->dir = 0;

        if(startA->threadID == 0){

            start_route = bridge_pairs[1][bridge->pos][0];
            startA = routes[start_route]+routes_sizes[start_route]-1;
            bridge->dir = 1;
        }

        if(startA->threadID != 0)
        {               
            alien_t* bridgeA = routes[ bridge_routes[bridge->pos] ];
            //usleep(startA->time);
            kill(startA->threadID, SIGTSTP);
            bridgeA[0] = *startA;
            bridge->count++;            
            bridgeA[0].position = 0;
            startA->threadID = 0;            
        }    

    }
    else    
    {
        int start_route = bridge_pairs[bridge->dir][bridge->pos][0];

        alien_t* startA = routes[start_route]+routes_sizes[start_route]-1;    
        alien_t* bridgeA = routes[ bridge_routes[bridge->pos] ];

        if(startA->threadID != 0 && bridgeA[0].threadID == 0)
        {
            if(Has_space_int(bridge, startA->weight) == EXIT_SUCCESS)
            {
                //usleep(startA->time);
                kill(startA->threadID, SIGTSTP);
                bridgeA[0] = *startA;
                bridge->count++;
                bridge->dir = 0;
                bridgeA[0].position = 0;
                startA->threadID = 0;
            }
        }
    }
}

void Move_aliens(bridge_params_t *bridge)
{
        
    int end_route = bridge_pairs[bridge->dir][bridge->pos][1];
      
    alien_t* endA = routes[end_route];
    alien_t* bridgeA = routes[ bridge_routes[bridge->pos] ];

    int last = bridge_pos[bridge->dir][4];

    if(bridgeA[last].threadID != 0 && endA[0].threadID == 0){
        endA[0] = bridgeA[last];
        endA[0].position = 0;
        bridge->count--;
        bridgeA[last].threadID = 0;
        kill(bridgeA[0].threadID, SIGCONT);
    }

    for(int i=3; i>=0; i--)
    {

        if(bridgeA[bridge_pos[bridge->dir][i]].threadID != 0 && bridgeA[bridge_pos[bridge->dir][i+1]].threadID == 0)
        {            
            bridgeA[bridge_pos[bridge->dir][i+1]] = bridgeA[bridge_pos[bridge->dir][i]];
            bridgeA[bridge_pos[bridge->dir][i+1]].position = i+1;
            bridgeA[i].threadID = 0;
        }

    }
}


int Has_space_int(bridge_params_t *bridge, int alien_weight)
{
    int a = 0;
    a += alien_weight;
    alien_t* bridgeA = routes[ bridge_routes[bridge->pos] ];
    for(int i=0; i<5; i++)
    {
        if(bridgeA[i].threadID != 0)
        {
            a += bridgeA[i].weight;
        }
    }

    if(a < bridge->max_weight)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}