#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "../include/Lthread.h"


mythread_t thread1, thread2, thread3;

int *TestFunction3(int value)
{
    int i = 0;
    while (i != 10)
    {
        printf("THREAD %d \n", value);
        sleep(3);
        i += 1;
    }
    Lthread_yield();
    printf("EXIT Thread: 3 \n");
    Lthread_exit(NULL);
    return EXIT_SUCCESS;
}

int *TestFunction2(int value)
{
    Lthread_create(&thread3, NULL, TestFunction3, (int *)3);
    int i = 0;
    while (i != 10)
    {
        printf("THREAD %d \n", value);
        sleep(2);
        i += 1;
    }
    Lthread_join(thread3, NULL);
    printf("EXIT Thread: 2 \n");
    Lthread_exit(NULL);
    return EXIT_SUCCESS;
}

int *TestFunction1(int value)
{
    int i = 0;
    while (i != 10)
    {
        printf("THREAD %d \n", value);
        sleep(1);
        i += 1;
    }
    printf("EXIT Thread: 1 \n");
    Lthread_exit(NULL);
    return EXIT_SUCCESS;
}

int main()
{
    char *status;
    Lthread_create(&thread1, NULL, TestFunction1, (int *)1);
    Lthread_create(&thread2, NULL, TestFunction2, (int *)2);
    sleep(2);
    Lthread_q_state_display();
    Lthread_join(thread2, (void **)&status);
    return EXIT_SUCCESS;
}