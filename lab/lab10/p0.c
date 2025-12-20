#include <stdio.h>
#include <pthread.h>

#define N 10000000
#define NTHREADS 10

int counter = 0;
pthread_mutex_t mlock;

void *func(void *arg)
{
	
	for(long i = 0; i < N; i++)
	{
		pthread_mutex_lock(&mlock);
		counter++;
		pthread_mutex_unlock(&mlock);
	}
		
	return NULL;
}

int main()
{
	pthread_t tids[NTHREADS];
	pthread_mutex_init(&mlock, NULL);
	
	for(int i = 0; i < NTHREADS; i++)
	{
		pthread_create(&tids[i], NULL, func, NULL);
	}
	for(int i = 0; i < NTHREADS; i++)
	{
		pthread_join(tids[i], NULL);
	}
	
	printf("Actual counter: %d VS Expected counter: %d\n", counter, N * NTHREADS);
	pthread_mutex_destroy(&mlock);
}