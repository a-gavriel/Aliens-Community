#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../../include/Random_Generators.h"


int get_random_int(int max)
{
    srand(time(NULL));          // Initialization, should only be called once.
    int r = rand() % max;      // Returns a pseudo-random integer between 0 and RAND_MAX.
    return r;
}

char *get_random_string(size_t length) 
{
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";        
    char *randomString = NULL;

    if (length) 
    {
        randomString = malloc(sizeof(char) * (length +1));
        if (randomString) 
        {            
            for (int n = 0;n < length;n++) 
            {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }
            randomString[length] = '\0';
        }
    }
    return randomString;
}

double expGenerator(double expectedValue){ //expectedValue = 1/lambda
    double u;
    u = rand() / (RAND_MAX + 1.0);
    return -log(u) * expectedValue;
}

unsigned int poissonGenerator(double expectedValue) {
  unsigned int k = 0; //counter of iteration
  double limit; 
  double p;  //pseudo random number
  limit = exp(-expectedValue);
  p = rand() / (RAND_MAX + 1.0); 
  while (p > limit) {
    k++;
    p *= rand() / (RAND_MAX + 1.0);
  }
  return k;
}

void rand_tester(void){
    srand((unsigned)time(NULL));
    double mean = 0;
    
    printf("Generating exponential distribution\n");
    for (int i=0; i<20; i++)
      printf("%f\n", expGenerator(mean));
  

    printf("Generating Poisson distribution\n");
    for (int i=0; i<100; i++)
      printf("%d\n", poissonGenerator(mean));  
}

unsigned int poissonRandom(double meanSeconds){
  unsigned int random_ = poissonGenerator((double)meanSeconds*100);
  return random_*10000;
}

unsigned int expRandom(double meanSeconds){
  double random_ = expGenerator((double)meanSeconds);
  return (unsigned int) (random_*1000000);
}

short int magicRandom(void){
  short int magic_num =  (short int)(rand() % 7);
  return magic_num;
}