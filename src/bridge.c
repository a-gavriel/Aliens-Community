#include <stdio.h>
#include <stdlib.h>

#include "../include/alien.h"
#include "../include/bridge.h"

void Survival(bridge_params_t *bridge)
{
    switch (bridge->type)
    {
        case 0: //Center          

            break;
        case 1: //Right          

            break;
        case -1: //Left          
            Survival_AUX_L(bridge);
        break;
        default:
            break;
    }
}

void Survival_AUX_L(bridge_params_t *bridge)
{
    if(bridge->count == 0)
    {
        if(aliens_A_top_left[11].threadID != 0)
        {
            aliens_A_bottom_left[0] = aliens_A_top_left[11];
            aliens_A_top_left[11].threadID = 0;
        }
    }
    else if(bridge->dir == 0 && bridge->count > 0)
    {
        if(aliens_A_top_left[11].threadID != 0)
        {
            if(Has_space(bridge, aliens_A_top_left[11]) == EXIT_SUCCESS)
            {
                aliens_A_bottom_left[0] = aliens_A_top_left[11];
                aliens_A_top_left[11].threadID = 0;
            }
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