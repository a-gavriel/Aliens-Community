#include <malloc.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../../include/Lthread.h"

/* The global extern pointer defined in mythread.h which points to the head node in
   Queue of the Thread Control Blocks.
*/
mythread_private_t *mythread_q_head;
int *scheduler_type;

/* This function initializes the Queue with a single node.
*/
void Lthread_q_init(mythread_private_t *node)
{

    node->prev = node;
    node->next = node;

    mythread_q_head = node;
}

/* This function adds a node to the Queue, at the end of the Queue. 
   This is equivalent to Enque operation.
 */
void Lthread_q_add(mythread_private_t *node)
{

    if (mythread_q_head == NULL)
    {

        Lthread_q_init(node);
        return;
    }

    node->next = mythread_q_head;
    node->prev = mythread_q_head->prev;
    mythread_q_head->prev->next = node;
    mythread_q_head->prev = node;

    return;
}

/* This function deleted a specified(passed as a parameter) node from the Queue.
 */
void Lthread_q_delete(mythread_private_t *node)
{

    mythread_private_t *p;
    if (node == mythread_q_head && node->next == mythread_q_head)
    {
        printf("The Q is now Empty!\n");
        mythread_q_head = NULL;
    }

    if (node == mythread_q_head)
        mythread_q_head = node->next;

    p = node->prev;

    p->next = node->next;
    node->next->prev = p;

    return;
}

/**
 * This function iterates over the Queue and prints out the state
 * see Lthread.h to refer to various states
*/
void Lthread_q_state_display()
{
    if (mythread_q_head != NULL)
    {
        printf("State of Threads are -> \n");
        mythread_private_t *p;
        p = mythread_q_head;
        do
        {
            char *state;
            switch (p->state)
            {
            case 0:
                state = "RUNNING";
                break;
            case 1:
                state = "READY";
                break;
            case 2:
                state = "BLOCKED";
                break;
            case 3:
                state = "DEFUNC";
                break;
            default:
                state = "";
                break;
            }
            printf("\t Thread ID: %d - Thread State %s\n", p->tid, state);
            p = p->next;
        } while (p != mythread_q_head);
    }
}

/* This function iterates over the Queue and prints out the state of the specified thread.
 */
mythread_private_t *Lthread_q_search(unsigned long new_tid)
{

    mythread_private_t *p;
    if (mythread_q_head != NULL)
    {
        p = mythread_q_head;
        do
        {
            if (p->tid == new_tid)
                return p;
            p = p->next;
        } while (p != mythread_q_head);
    }
    return NULL;
}

/**
 * This functions is used to lock all the treads 
 * except the thread is given
 * */

void Lthread_q_lock(unsigned long new_tid)
{
    mythread_private_t *p;

    if (mythread_q_head != NULL)
    {

        p = mythread_q_head;

        do
        {
            if (p->tid != new_tid)
            {
                printf("BLOCKING T %d \n\n", p->tid);
                p->state = BLOCKED;
                kill(p->tid, SIGSTOP);
            }
            p = p->next;
        } while (p != mythread_q_head);
    }
}

/**
 * This function is for unlock all the treads
 * except the thread is given
 * */

void Lthread_q_unlock(unsigned long new_tid)
{

    mythread_private_t *p;

    if (mythread_q_head != NULL)
    {

        p = mythread_q_head;

        do
        {
            if (p->tid != new_tid)
            {
                printf("UNBLOCKING T %d \n\n", p->tid);
                p->state = READY;
                kill(p->tid, SIGCONT);
            }
            p = p->next;
        } while (p != mythread_q_head);
    }
}

/**
 * This function lock all the threads 
 * */

void Lthread_q_lock_all()
{
    mythread_private_t *p;

    if (mythread_q_head != NULL)
    {

        p = mythread_q_head;

        do
        {
            kill(p->tid, SIGSTOP);
            p->state = BLOCKED;
            printf("STOPPING T %d \n\n", p->tid);
            p = p->next;
        } while (p != mythread_q_head);
    }
}



