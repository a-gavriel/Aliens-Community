#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MYTHREAD_H

#define FALSE 0
#define TRUE 1

#define RUNNING 0
#define READY 1   /* Ready to be scheduled */
#define BLOCKED 2 /* Waiting on Join */
#define DEFUNCT 3 /* Dead */

#define FIFO 0
#define SSROUNDROBIN 1
#define LOTTERY 2
#define REAL 3

typedef struct lpthread_attr
{
    unsigned long stackSize; /* Stack size to be used by this thread. Default is SIGSTKSZ */
} lpthread_attr_t;

/* Thread Handle exposed to the user */
typedef struct lpthread
{
    pid_t tid; /* The thread-id of the thread */
} lpthread_t;

/* The Actual Thread Control Block structure */
typedef struct lpthread_private
{

    pid_t tid;                               /* The thread-id of the thread */
    int state;                               /* the state in which the corresponding thread will be. */
    void *(*start_func)(void *);             /* The func pointer to the thread function to be executed. */
    void *args;                              /* The arguments to be passed to the thread function. */
    void *returnValue;                       /* The return value that thread returns. */
    struct lpthread_private *blockedForJoin; /* Thread blocking on this thread */
    struct lpthread_private *prev, *next;
    int joinable;                            /*1 = Can Join, 0 = Can't Join*/

} lpthread_private_t;

extern int *scheduler_type;

extern lpthread_private_t *mythread_q_head; /* The pointer pointing to head node of the TCB queue */

int Lthread_create(lpthread_t *new_thread_ID,
                    lpthread_attr_t *attr,
                    void *start_func,
                    void *arg);

int Lthread_join(lpthread_t target_thread, void **status);

int Lthread_detach(lpthread_t thread_ID);

int Lthread_end(void *retval);

void Lthread_sched(char *scheduler);

void Lthread_q_state_display();

int Lthread_yield();