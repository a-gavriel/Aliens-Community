#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>
#include <pthread.h>

#include "../include/Lpthreads.h"
#include "../include/Lmutex.h"
#include "../include/Random_Generators.h"
#include "../include/json.h"
#include "../include/ConfigFile_Reader.h"

//*****************
//Lpthread Var
lpthread_t lpthread[8];
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

int a = 0;
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
            a++;
            printf("Thread %d : Increment the counter: i = %d \n", id,a);
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
    printf("Final Value need to be: %d \n", 10);
    Lthread_create(&lpthread[5], NULL, Lpthread_Test_trylock_Aux, (int *)1);
    Lthread_create(&lpthread[6], NULL, Lpthread_Test_trylock_Aux, (int *)2);
    Lthread_join(lpthread[5], NULL);
    Lthread_join(lpthread[6], NULL);
}

//Detach Test Code

int Lpthread_Test_Detach_Aux()
{
    for(int i = 0; i<5; i++)
    {
        sleep(1);
    }
    return EXIT_SUCCESS;
}

int Lpthread_Test_Detach()
{
    printf("Run Thread 1 \n");
    Lthread_create(&lpthread[7], NULL, Lpthread_Test_Detach_Aux, NULL);
    printf("Detach Thread 1 \n");
    Lthread_detach(lpthread[7]);
    printf("Try Join Thread 1 \n");
    if(Lthread_join(lpthread[7], NULL) == -2)
    {
        printf("Can't Join Thread 1 was detached \n");
    }
    sleep(3);
    return EXIT_SUCCESS;
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
    printf("Rand Number: %d \n", get_random_int(100));
    printf("Rand String: %s \n", get_random_string(10));
}

void TestJson()
{
    bridge_t bridgeI;
    alien_beta_t alienB;
    alien_normal_t alienN;
    aliens_generator_t alienG;
    //char *file =  "bridge_config_file_I.json";
    Read_bridge_configFile(FILE_NAME_BRIDGE_I, &bridgeI);
    Read_alien_normal_configFile(FILE_NAME_ALIEN_N, &alienN);
    Read_alien_beta_configFile(FILE_NAME_ALIEN_B, &alienB);
    Read_aliens_generator_configFile(FILE_NAME_ALIEN_GENERATOR, &alienG);
    printf("Bridge Config File \n");
    printf("\t Size: %d \n", bridgeI.size);
    printf("\t Max Weigth: %d \n", bridgeI.max_weigth);
    printf("\t Bridge: %d \n", bridgeI.bridge_type);
    printf("\t Scheduler: %d \n", bridgeI.scheduler_type);
    printf("\t QueueSize: %d \n", bridgeI.queue_size);
    printf("Alien Normal Config File \n");
    printf("\t Speed: %d \n", alienN.speed);
    printf("Alien Beta Config File \n");
    printf("\t Execution Time: %d \n", alienB.execution_time);
    printf("Aliens Generator Config File \n");
    printf("\t Normal Percentage : %d \n", alienG.normal);
    printf("\t Beta Percentage : %d \n", alienG.beta);
    printf("\t Alfa Percentage : %d \n", alienG.alfa);
    printf("\t Mean Time : %d \n", alienG.mean);
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
    printf("Run Detach Test \n");
    Lpthread_Test_Detach();
    printf("****************************** \n");
    printf("Run Random Generators Test \n");
    Test_ramdom_generators();
    printf("****************************** \n");
    printf("Run Json Test \n");
    TestJson();
    return EXIT_SUCCESS;
}