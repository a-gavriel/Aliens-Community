#ifndef __RANDOMGENERATORS_H
#define __RANDOMGENERATORS_H

#include <stdlib.h>

int get_random_int(int max);

char *get_random_string(size_t length);

double expGenerator(double expectedValue);

unsigned int poissonGenerator(double expectedValue);

void rand_tester(void);

unsigned int poissonRandom(double meanSeconds);

unsigned int expRandom(double meanSeconds);

short int magicRandom(void);

#endif