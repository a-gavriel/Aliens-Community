#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

pthread_t thread1, thread2, thread3, thread4, thread5;
pthread_mutex_t mutex;

int z, x = 0;
long int y = 0;

int *TestFunction2(int value)
{   
    for(int i=0; i<100; i++)
    {
        sleep(0.2);
        z++;
        x = x + z + value;
        y = y + x + 2;
        pthread_mutex_unlock(&mutex);
    }
    printf("EXIT Thread: %d \n", value);
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}

int *TestFunction1(int value)
{   
    for(int i=0; i<100; i++)
    {
        z++;
        x = x + z + value;
        y = y + x + 2;
    }
    return EXIT_SUCCESS;
}
void Test_Lpthread()
{
    pthread_create(&thread1, NULL, (void *)TestFunction2, (void *)1);
    pthread_create(&thread2, NULL, (void *)TestFunction2, (void *)2);
    pthread_create(&thread3, NULL, (void *)TestFunction2, (void *)3);
    pthread_create(&thread4, NULL, (void *)TestFunction2, (void *)4);
    pthread_create(&thread5, NULL, (void *)TestFunction2, (void *)5);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    printf("Value of shared var x: %d and y: %ld \n", x,y);
    x = 0;
    y = 0;
    z = 0;
    TestFunction1(1);
    TestFunction1(2);
    TestFunction1(3);
    TestFunction1(4);
    TestFunction1(5);
    printf("Value of shared var x: %d and y: %ld \n", x,y);
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    Test_Lpthread();
    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}