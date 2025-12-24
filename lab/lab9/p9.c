/*
 * Q3 (Hard): Create a program that parallelizes a search over an array of 106 integers. 
 * Divide the array into 4 segments. Each thread finds the local maximum in its segment 
 * and returns a pointer to that value. The main thread must compare these 4 values to 
 * print the global maximum. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>

#define SIZE 9999999
#define MOD 100000
#define NTHREADS 10

typedef struct args_t 
{
	int *arr;
	int size;
} args_t;



void* find_max(void *args)
{
	args_t thread_args = *(args_t*) args;
	int *local_max = (int*) malloc(sizeof(int));
	*local_max = INT_MIN;
	
	for(int i = 0; i < thread_args.size; i++)
	{
		if (thread_args.arr[i] > *local_max)
		{
			*local_max = thread_args.arr[i];
		}
	}
	
	return (void *) local_max;
}


int main()
{
	srand(time(0));
	int size_per_thread, par_max;
	int *A;
	pthread_t tids[NTHREADS];
	
	size_per_thread = SIZE / NTHREADS;
	par_max = INT_MIN;
	A = (int*) malloc(SIZE * sizeof(int));
		
	for (int i = 0; i < SIZE; i++)
	{
		A[i] = rand() % MOD;
	}
	
	for (int i = 0; i < NTHREADS; i++)
	{
		args_t *thread_args = (args_t*) malloc(sizeof(args_t));
		thread_args->arr = A + (i * size_per_thread);
		thread_args->size = size_per_thread;
		
		pthread_create(&tids[i], NULL, find_max, (void*) thread_args);
	}
	
	for (int i = 0; i < NTHREADS; i++)
	{
		int *local_max;
		pthread_join(tids[i], (void **) &local_max);
		if (*local_max > par_max)
		{
			par_max = *local_max;
		}
		
		free(local_max);
	}
	
	for (int i = (NTHREADS * size_per_thread); i < SIZE; i++)
	{
		if (A[i] > par_max)
			par_max = A[i];
	}

	printf("The parallel max is: %d\n", par_max);
}