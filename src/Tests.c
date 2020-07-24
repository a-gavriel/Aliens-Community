#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>
#include <pthread.h>

#include "../include/Lpthreads.h"
#include "../include/Lmutex.h"
#include "../include/Random.h"

//*****************
//Lpthread Var
lpthread_t lpthread[7];
lmutex_t lmutex;
lmutex_t lmutex_trylock;
//*****************
//Pthread Var
pthread_t pthread[5];
pthread_mutex_t pmutex;
//*****************

int r = 0;
int x = 0;
int y = 0;
int z = 0;

//Lpthreads Test Code

int *Lpthreads_Test_Aux(int value)
{   
    for(int i=0; i<10; i++)
    {
        Lmutex_lock(&lmutex);
        z++;
        r = r + value;
        x = x + r;
        y = y + x;
        Lmutex_unlock(&lmutex);
    }
    Lthread_end(NULL);
    return EXIT_SUCCESS;
}

void Lpthread_Test()
{
    Lthread_create(&lpthread[0], NULL, Lpthreads_Test_Aux, (int *)2);
    Lthread_create(&lpthread[1], NULL, Lpthreads_Test_Aux, (int *)2);
    Lthread_create(&lpthread[2], NULL, Lpthreads_Test_Aux, (int *)2);
    Lthread_create(&lpthread[3], NULL, Lpthreads_Test_Aux, (int *)2);
    Lthread_create(&lpthread[4], NULL, Lpthreads_Test_Aux, (int *)2);
    Lthread_join(lpthread[0], NULL);
    Lthread_join(lpthread[1], NULL);
    Lthread_join(lpthread[2], NULL);
    Lthread_join(lpthread[3], NULL);
    Lthread_join(lpthread[4], NULL);
    Lthread_q_state_display();
    printf("Value of shared var x: %d and y: %d and z: %d \n", x,y,z);
}

//Test Lmutex Try Lock
int *Lpthread_Test_trylock_Aux(int id)
{
    int i = 0;
    while(i < 5)
    {
        if(Lmutex_trylock(&lmutex_trylock))
        {
            printf("Thread %d : Capture the Lock \n", id);
            i++;
            printf("Thread %d : Increment the counter: i = %d \n", id,i);
            Lmutex_unlock(&lmutex_trylock);
        }
        else
        {
            printf("Thread %d : Cant't capture the Lock \n", id);
        }
    }
}

void Lpthread_Test_trylock()
{
    Lthread_create(&lpthread[5], NULL, Lpthread_Test_trylock_Aux, (int *)1);
    Lthread_create(&lpthread[6], NULL, Lpthread_Test_trylock_Aux, (int *)2);
    Lthread_join(lpthread[5], NULL);
    Lthread_join(lpthread[6], NULL);
}

//Pthreads Test Code

int *Pthreads_Test_Aux(int value)
{   
    for(int j=0; j<10; j++)
    {
        pthread_mutex_lock(&pmutex);
        z++;
        r = r + value;
        x = x + r;
        y = y + x;
        pthread_mutex_unlock(&pmutex);
    }
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}

void Pthread_Test()
{
    pthread_create(&pthread[0], NULL, (void *)Pthreads_Test_Aux, (void *)2);
    pthread_create(&pthread[1], NULL, (void *)Pthreads_Test_Aux, (void *)2);
    pthread_create(&pthread[2], NULL, (void *)Pthreads_Test_Aux, (void *)2);
    pthread_create(&pthread[3], NULL, (void *)Pthreads_Test_Aux, (void *)2);
    pthread_create(&pthread[4], NULL, (void *)Pthreads_Test_Aux, (void *)2);
    pthread_join(pthread[0], NULL);
    pthread_join(pthread[1], NULL);
    pthread_join(pthread[2], NULL);
    pthread_join(pthread[3], NULL);
    pthread_join(pthread[4], NULL);
    printf("Value of shared var x: %d and y: %d and z: %d \n", x,y,z);
}


void Test_ramdom_generators()
{
    srand(time(NULL));
    printf("Rand Number: %d \n", Get_random_value(100));
    printf("Rand String: %s \n", Get_random_string(10));
}

int main()
{
    printf("****************************** \n");
    printf("Run Lpthreads/Lmutex Test \n");
    Lmutex_init(&lmutex, 1);
    Lpthread_Test();
    Lmutex_destroy(&lmutex);
    r = 0;
    x = 0;
    y = 0;
    z = 0;
    printf("****************************** \n");
    printf("Run Pthreads Test \n");
    pthread_mutex_init(&pmutex, NULL);
    Pthread_Test();
    pthread_mutex_destroy(&pmutex);
    printf("****************************** \n");
    printf("Run Lmutex TryLock Test \n");
    Lmutex_init(&lmutex_trylock, 1);
    Lpthread_Test_trylock();
    Lmutex_destroy(&lmutex_trylock);
    printf("****************************** \n");
    printf("Run Random Generators Test \n");
    Test_ramdom_generators();
    return EXIT_SUCCESS;
}