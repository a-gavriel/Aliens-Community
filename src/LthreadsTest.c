#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "../include/Lthread.h"

mythread_t thread1, thread2;

int *TestFunction2(int value)
{
    int i = 0;
    while (i != 10)
    {
        printf("THREAD %d \n", value);
        Lthread_yield();
        sleep(2);
        i += 1;
    }
    Lthread_exit(NULL);
    return EXIT_SUCCESS;
}

int *TestFunction1(int value)
{
    Lthread_create(&thread2, NULL, TestFunction2, 2);
    int i = 0;
    while (i != 10)
    {
        printf("THREAD %d \n", value);
        sleep(1);
        i += 1;
    }
    Lthread_join(thread2, NULL);
    Lthread_exit(NULL);
    return EXIT_SUCCESS;
}




int main()
{
    char *status;
    Lthread_create(&thread1, NULL, TestFunction1, 1);
    printf("End Create Test\n");
    //Lthread_join(thread1, (void **)&status);
    //sleep(10);
    printf("Paso4 \n");
    return EXIT_SUCCESS;
}