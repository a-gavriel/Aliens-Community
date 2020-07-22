#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

pthread_t thread1, thread2, thread3;

int *TestFunction3(int value)
{
    int i = 0;
    while (i != 10)
    {
        printf("THREAD %d \n", value);
        sleep(3);
        i += 1;
    }
    printf("EXIT Thread: 3 \n");
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}

int *TestFunction2(int value)
{
    pthread_create(&thread3, NULL, (void *)TestFunction3, (int *)3);
    int i = 0;
    while (i != 10)
    {
        printf("THREAD %d \n", value);
        sleep(2);
        i += 1;
    }
    pthread_join(thread3, NULL);
    printf("EXIT Thread: 2 \n");
    pthread_exit(NULL);
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
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}

int main()
{
    char *status;
    pthread_create(&thread1, NULL, (void *)TestFunction1, (int *)1);
    pthread_create(&thread2, NULL, (void *)TestFunction2, (int *)2);
    pthread_join(thread2, NULL);
    return EXIT_SUCCESS;
}