#define _GNU_SOURCE

#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sched.h>

#include "../../include/Lthread.h"
#include "./Lthread_q.h"

#define FIBER_STACK 1024 * 64

/* The global extern pointer defined in mythread.h which points to the head node in
   Queue of the Thread Control Blocks. 
 */
mythread_private_t *mythread_q_head;
int *scheduler_type;


/* The mythread_create() function.
   This creates a shared process context by using the clone system call.
   We pass the pointer to a wrapper function ( See mythread_wrapper.c ) which in turn 
   sets up the thread environment and then calls the thread function.
   The mythread_attr_t argument can optionally specify the stack size to be used
   the newly created thread.
 */
int Lthread_create(mythread_t *new_thread_ID, mythread_attr_t *attr, void *start_func, void *arg)
{
    void *child_stack;
    unsigned long stackSize;
    mythread_private_t *new_node;
    pid_t tid;

    new_node = (mythread_private_t *)malloc(sizeof(mythread_private_t));

    if (new_node == NULL)
    {
        printf("Cannot allocate memory for node\n");
        return -ENOMEM;
    }

    /* If Stack-size argument is not provided, use the SIGSTKSZ as the default stack size
     * Otherwise, extract the stacksize argument.
     */
    if (attr == NULL)
    {
        stackSize = SIGSTKSZ;
    }
    else
    {
        stackSize = attr->stackSize;
    }

    /* posix_memalign aligns the allocated memory at a 64-bit boundry. */
    if (posix_memalign((void **)&child_stack, 8, stackSize))
    {
        printf("posix_memalign failed! \n");
        return -ENOMEM;
    }

    child_stack = malloc(FIBER_STACK);
    if (child_stack == 0)
    {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    /* We leave space for one invocation at the base of the stack */
    //child_stack = child_stack + stackSize - sizeof(sigset_t);

    /* Save the thread_fun pointer and the pointer to arguments in the TCB. */
    new_node->start_func = start_func;
    new_node->args = arg;
    /* Set the state as READY - READY in Q, waiting to be scheduled. */
    new_node->state = READY;

    new_node->returnValue = NULL;
    new_node->blockedForJoin = NULL;

    /* Put it in the Q of thread blocks */
    Lthread_q_add(new_node);

    /* Call clone with pointer to wrapper function. TCB will be passed as arg to wrapper function. */
    tid = clone(start_func, /*(char *)child_stack*/ (char *)child_stack + FIBER_STACK, /*FLAGS*/ SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, arg);
    if (tid == -1)
    {
        perror("clone");
        exit(2);
    }
    /* Save the tid returned by clone system call in the tcb. */
    new_thread_ID->tid = tid;
    new_node->tid = tid;
    setbuf(stdout, NULL);
    printf("create: Finished initialising new thread: %ld\n", (unsigned long)new_thread_ID->tid);
    return 0;
}

/* Wait on the thread specified by "target_thread". If the thread is DEFUNCT,
 * just collect the return status. Else, wait for the thread to die and then
 * collect the return status
 */
int Lthread_join(mythread_t target_thread_user, void **status)
{
    mythread_private_t *target_thread_full, *self_thread_full;
    pid_t self_tid = syscall(SYS_gettid);
    self_thread_full = Lthread_q_search(self_tid);
    target_thread_full = Lthread_q_search(target_thread_user.tid);

    if (target_thread_full->state == DEFUNCT)
    {
        *status = target_thread_full->returnValue;
        return 0;
    }

    if (target_thread_full->blockedForJoin != NULL)
    {
        return -1;
    }

    target_thread_full->blockedForJoin = self_thread_full;
    printf("Target: %d \n", target_thread_full->tid);
    pid_t t = waitpid(target_thread_full->tid, 0, 0);
    if (t == -1)
    {
        perror("waitpid");
        exit(3);
    }
    printf("Thread %d Joinet to %d.\n", self_thread_full->tid, target_thread_full->tid);
    self_thread_full->state = BLOCKED;
    //La siguiente linea genera un error, si se descomenta se caae el código, investigar por que
    //*status = self_thread_full->returnValue;
    return 0;
}

/**
 * This function indicates when a thread ends his execution
 */
void Lthread_exit(void *value_ptr)
{
    pid_t t = syscall(SYS_gettid);

    mythread_private_t *thread = Lthread_q_search(t);

    thread->state = DEFUNCT;
    thread->returnValue = value_ptr;

    /* Don't remove the node from the list yet. We still have to collect the return value */

    if (thread->blockedForJoin != NULL)
    {
        thread->blockedForJoin->state = READY;
    }

    // free(thread->args);

    // setbuf(stdout, NULL);
    printf("THREAD %d EXIT \n", thread->tid);

    syscall(SYS_exit, 0);
}

int Lthread_yield()
{
    if(sched_yield() == 0)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        printf("Thread %d: Error during thread yiled \n", syscall(SYS_gettid));
        return EXIT_FAILURE;
    }
}