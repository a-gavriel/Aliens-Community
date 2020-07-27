#include<stdio.h> 
#include<stdlib.h>
#include<time.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/syscall.h>


const int N = 5;
// Alien Types (N:Normal, A:Alfa, B:Beta)
const char alienTypes[3] = {'N','A','B'};

// Aliens struct
typedef struct aliens {
	char alienType;
	pthread_t threadID;
    int speed;
    int weight;
    int time;
} alien_t;

// List struct
typedef struct node { 
    alien_t *alien;  
    struct node *next; 
} node_t; 
  
// Inserts an alien in front of the list
void pushAlien(node_t** head_ref, alien_t *new_alien, size_t data_size) { 
    node_t* new_node = (node_t*) malloc(sizeof(node_t)); 
    new_node->alien = new_alien; 
    new_node->next = (*head_ref); 
    (*head_ref) = new_node; 
} 

// Deletes an alien by threadID
void deleteAlien(node_t **node, int ID) {
    node_t *current; 
    node_t *previous;

    // For first node, there is no previous
    previous = NULL;

    // Visit each node, keeping a pointer to the previous node just visited
    for(current = *node; current != NULL; previous = current, current = current->next) {
        if(current->alien->threadID == ID) { 
        // Found it     
            if (previous == NULL) {
            // Fix beginning pointer 
                *node = current->next;
            } 
            else {
                // Fix previous node's next to skip over the removed node
                previous->next = current->next;
            }           
            // Deallocate node and return
            free(current);
            return;
        }
    }
}

// Prints aliens in the list
void printList(node_t *node) { 
    while (node != NULL) { 
        printf("ID: %ld \n", node->alien->threadID);         
        printf("AlienType: %c \n", node->alien->alienType);
        printf("Speed: %d \n", node->alien->speed);
        printf("Weight: %d \n", node->alien->weight);
        printf("Time: %d \n\n", node->alien->time); 
        node = node->next; 
    } 
}



void* alienloop(void* aliens_v){
    int position = 0;
    int sleeptime = rand()%3+1;
    alien_t *  aliens = (alien_t*) aliens_v;
    pthread_t tid = pthread_self();
    alien_t newalien = {rand()%3,
                        pthread_self(),
                        rand()%50,
                        rand()%50,
                        rand()%50}; 
    aliens[0] = newalien;
    while (position < N - 1){
        printf("I am %ld, position %d, sleeptime %d, next is %ld\n", tid, 
            position, sleeptime, aliens[position+1].threadID);
        while(aliens[position + 1].threadID != 0){            
            printf("waiting for alien %ld to move from %d\n", aliens[position+1].threadID , position +1);
            sleep(sleeptime);
        }
        sleep(sleeptime);
        aliens[position+1] = aliens[position];
        position++;
        aliens[position - 1].threadID = 0;
    }
    printf("Reach final position %d !, now exiting list...\n",position);
    sleep(sleeptime);
    aliens[position].threadID = 0;

    pthread_exit(NULL); 
}

void* createAliens(alien_t* aliens){
    int i = 0;
    while (i < 5){
        i++;
        while(aliens[0].threadID != 0){
                int sleeptime = rand()%3+3;
                sleep(sleeptime);
        }
        printf("Community created new alien!\n");
        aliens[0].threadID = 1;
        pthread_t ptid; 
        pthread_create(&ptid, NULL, &alienloop, (void* )aliens); 
        // new thread to function alienloop(alien_t* aliens);
    }
    sleep(10);
    
}

int main() { 
    // Only for testing purpose
    // node_t *start = NULL; 
	alien_t aliens[N];
    memset(aliens,0,sizeof(aliens));

    time_t t;
    // Initializes random number generator
    srand((unsigned) time(&t));
    createAliens( aliens);
    /*
    unsigned aliens_size = sizeof(aliens);            
    int i;
    for (i=0; i<N; i++) { 
        aliens[i].threadID=rand()%50;
        aliens[i].alienType=alienTypes[rand()%3];
        aliens[i].speed=rand()%50;          
        aliens[i].weight=rand()%50;          
        aliens[i].time=rand()%50;          
        pushAlien(&start, &aliens[i], aliens_size); 
    }

    */

    ///printList(start);
    // deleteAlien(&start,5);       
    return 0; 
} 