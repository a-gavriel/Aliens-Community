#ifndef _LMUTEX_H_
#define _LMUTEX_H

#define INIT 1
#define DESROY 0

typedef struct lmutex
{
	int count;
	int state;
} lmutex_t;

int Lmutex_init(lmutex_t *sem, int val);
int Lmutex_lock(lmutex_t *sem);
void Lmutex_unlock(lmutex_t *sem);
int Lmutex_destroy(lmutex_t *sem);
int Lmutex_trylock(lmutex_t *sem);

#endif