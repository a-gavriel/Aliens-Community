#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>     	// EXIT_FAILURE
#include <stdint.h>     	// For int variants
#include <sys/types.h>

#include "../../include/Lmutex.h"
#include "../../include/Random.h"

int Lmutex_init(lmutex_t *futx, int val)
{
	futx->count = val;
	futx->state = INIT;
}

int Lmutex_lock(lmutex_t *futx)
{
	if(futx->state == INIT)
	{		
		//Atomic operation
		//Compare and Swap
		//Second Parameter is equal to first parameter them put third parameter into first parameter
		//Return True if the values are equals
		while(!__sync_bool_compare_and_swap(&futx->count, 1, 0));
	}
	else
	{
		printf("Error Acquiring the Lock, please initialize de Lmutex var \n");
	}
}

void Lmutex_unlock(lmutex_t *futx)
{	
	//Atomic operation
	//Compare and Swap
	//Second Parameter is equal to first parameter them put third parameter into first parameter
	//Return True if the values are equals
	__sync_bool_compare_and_swap(&futx->count, 0, 1);
}

int Lmutex_trylock(lmutex_t *futx)
{
	if(futx->state == INIT)
	{		
		//Atomic operation
		//Compare and Swap
		//Second Parameter is equal to first parameter them put third parameter into first parameter
		//Return True if the values are equals
		if(__sync_bool_compare_and_swap(&futx->count, 1, 0))
		{
			return EXIT_SUCCESS;
		}
		else
		{
			return EXIT_FAILURE;
		}
	}
	else
	{
		printf("Error Acquiring the Lock, please initialize de Lmutex var \n");
		return EXIT_FAILURE;
	}
}

int Lmutex_destroy(lmutex_t *futx)
{
	futx->count = 0;
	futx->state = DESROY;
}