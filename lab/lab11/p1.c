#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define N 100000000
#define NTHREADS 10


pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;

typedef struct arg_t
{
	int *arr;
	long size;
} arg_t;

int prime_count;

int is_prime(int val)
{
	if (val <= 1) return 0;
	
	for (int i = 2; i * i <= val; i++)
	{
		if (val % i == 0)
			return 0;
	}
	
	return 1;
}

void* func(void *args)
{
	arg_t arg = *(arg_t*) args;
	for(long i = 0; i < arg.size; i++)
	{
		if (is_prime(arg.arr[i]))
		{
			pthread_mutex_lock(&mlock);
			prime_count++;
			pthread_mutex_unlock(&mlock);
		}
	}
	
	pthread_exit(0);
}

int main()
{
	
	srand(time(0));
	
	pthread_t tids[NTHREADS];
	arg_t args[NTHREADS];
	
	long size_per_thread = N / NTHREADS;
	int *arr = (int*) malloc(sizeof(int) * N);
	if (arr == NULL) 
	{
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }
	for(long i = 0; i < N; i++)
	{
		arr[i] = rand() % N;
	}
	
	for(int i = 0; i < NTHREADS; i++)
	{
		args[i].arr = arr + (i * size_per_thread);
		args[i].size = size_per_thread;
		
		pthread_create(&tids[i], NULL, func, (void *) &args[i]);
	}
	
	for(int i = 0; i < NTHREADS; i++)
		pthread_join(tids[i], NULL);
	
	printf("Found %d primes\n", prime_count);
}