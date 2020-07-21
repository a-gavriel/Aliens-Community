#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "../include/Lthread.h"

int *TestFunction(int value)
{
    int i = 0;
    while (i != 50)
    {
        //setbuf(stdout, NULL);
        printf("THREAD %d \n", value);
        sleep(0.5);
        i += 1;
    }
    Lthread_exit(NULL);
    return EXIT_SUCCESS;
}

int main()
{
    mythread_t *thread1;
    int *value = (int*)1;
    Lthread_create(&thread1, NULL, TestFunction, value);
    //Lthread_join(*thread1, NULL);
    sleep(2);
    printf("Paso4 \n");
    return EXIT_SUCCESS;
}