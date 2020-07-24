#include <time.h>
#include <stdlib.h>

#include "../../include/Random.h"


int Get_random_value(int max)
{
    srand(time(NULL));          // Initialization, should only be called once.
    int r = rand() % max;      // Returns a pseudo-random integer between 0 and RAND_MAX.
    return r;
}

char *Get_random_string(size_t length) 
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