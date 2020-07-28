#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "../include/alien.h"
#include "../include/bridge.h"

void BridgeMovements()
{
    switch (left_bridge.type)
    {
        case 0: //0 = Algorithm Y          

            break;
        case 1: //1 = Algorithm Sem          

            break;
        case 2: //2 = Algorithm Survival          
            Survival(&left_bridge);
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
            Survival(&center_bridge);
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
            Survival(&right_bridge);
        break;
        default:
            break;
    }

    Move();
}

void Survival(bridge_params_t *bridge)
{
    switch (bridge->position)
    {
        case 0: //Center          
        Survival_AUX_C(bridge);
            break;
        case 1: //Right          
        Survival_AUX_R(bridge);
            break;
        case -1: //Left          
            Survival_AUX_L(bridge);
        break;
        default:
            break;
    }
}

//kill(array_pids[i], SIGCONT);
//sleep(1);
//kill(array_pids[i], SIGSTOP);

void Survival_AUX_L(bridge_params_t *bridge)
{
    if(bridge->count == 0)
    {
        if(aliens_A_top_left[11].threadID != 0 && aliens_bridge_left[0].threadID == 0)
        {
            usleep(aliens_A_bottom_left[11].time);
            kill(aliens_A_top_left[11].threadID, SIGSTOP);
            aliens_bridge_left[0] = aliens_A_top_left[11];
            bridge->count++;
            bridge->dir = 0;
            aliens_bridge_left[0].position = 0;
            aliens_A_top_left[11].threadID = 0;
        }
    }
    else if(bridge->dir == 0 && bridge->count > 0)
    {
        if(aliens_A_top_left[11].threadID != 0 && aliens_bridge_left[0].threadID == 0)
        {
            if(Has_space(bridge, aliens_A_top_left[11]) == EXIT_SUCCESS)
            {
                usleep(aliens_A_bottom_left[11].time);
                kill(aliens_A_top_left[11].threadID, SIGSTOP);
                aliens_bridge_left[0] = aliens_A_top_left[11];
                bridge->count++;
                bridge->dir = 0;
                aliens_bridge_left[0].position = 0;
                aliens_A_top_left[11].threadID = 0;
            }
        }
    }
}

void Survival_AUX_R(bridge_params_t *bridge)
{
    if(bridge->count == 0)
    {
        if(aliens_A_top_right[11].threadID != 0 && aliens_bridge_right[0].threadID == 0)
        {
            usleep(aliens_A_top_right[11].time);
            kill(aliens_A_top_right[11].threadID, SIGSTOP);
            aliens_bridge_right[0] = aliens_A_top_right[11];
            bridge->count++;
            bridge->dir = 0;
            aliens_bridge_right[0].position = 0;
            aliens_A_top_right[11].threadID = 0;
        }
    }
    else if(bridge->dir == 0 && bridge->count > 0)
    {
        if(aliens_A_top_right[11].threadID != 0 && aliens_bridge_right[0].threadID == 0)
        {
            if(Has_space(bridge, aliens_A_top_right[11]) == EXIT_SUCCESS)
            {
                usleep(aliens_A_top_right[11].time);
                kill(aliens_A_top_right[11].threadID, SIGSTOP);
                aliens_bridge_right[0] = aliens_A_top_right[11];
                bridge->count++;
                bridge->dir = 0;
                aliens_bridge_right[0].position = 0;
                aliens_A_top_right[11].threadID = 0;
            }
        }
    }
}

void Survival_AUX_C(bridge_params_t *bridge)
{
    if(bridge->count == 0)
    {
        if(aliens_A_top_center[4].threadID != 0 && aliens_bridge_center[0].threadID == 0)
        {
            usleep(aliens_A_top_center[4].time);
            kill(aliens_A_top_center[4].threadID, SIGSTOP);
            aliens_bridge_center[0] = aliens_A_top_center[4];
            bridge->count++;
            bridge->dir = 0;
            aliens_bridge_center[0].position = 0;
            aliens_A_top_center[4].threadID = 0;
        }
    }
    else if(bridge->dir == 0 && bridge->count > 0)
    {
        if(aliens_A_top_center[4].threadID != 0 && aliens_bridge_center[0].threadID == 0)
        {
            if(Has_space(bridge, aliens_A_top_center[4]) == EXIT_SUCCESS)
            {
                usleep(aliens_A_top_center[4].time);
                kill(aliens_A_top_center[4].threadID, SIGSTOP);
                aliens_bridge_center[0] = aliens_A_top_center[4];
                bridge->count++;
                bridge->dir = 0;
                aliens_bridge_center[0].position = 0;
                aliens_A_top_center[4].threadID = 0;
            }
        }
    }
}

void Move()
{
    if(aliens_bridge_left[4].threadID != 0 && aliens_A_bottom_left[0].threadID == 0)
    {
        aliens_A_bottom_left[0] = aliens_bridge_left[4];
        aliens_A_bottom_left[0].position = 0;
        aliens_bridge_left[4].threadID = 0;
        kill(aliens_A_top_center[4].threadID, SIGCONT);
    }
    for(int i=3; i!=0; i--)
    {
        if(aliens_bridge_left[i].threadID != 0 && aliens_bridge_left[i+1].threadID == 0)
        {
            aliens_bridge_left[i+1] = aliens_bridge_left[i];
            aliens_bridge_left[i+1].position = i+1;
            aliens_bridge_left[i].threadID = 0;
        }
    }
}

int Has_space(bridge_params_t *bridge, alien_t alien)
{
    int a = 0;
    a += alien.weight;
    for(int i=0; i<5; i++)
    {
        switch (bridge->type)
        {
        case 0: //Center          
            if(aliens_bridge_center[i].threadID != 0)
            {
                a += aliens_bridge_center[i].weight;
            }
            break;
        case 1: //Right          
            if(aliens_bridge_right[i].threadID != 0)
            {
                a += aliens_bridge_right[i].weight;
            }
            break;
        case -1: //Left          
            if(aliens_bridge_left[i].threadID != 0)
            {
                a += aliens_bridge_left[i].weight;
            }
        break;
        default:
            break;
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