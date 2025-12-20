#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXTHREADS 10

typedef struct arg_t
{
	int val;
} arg_t;


void* func(void *args)
{
	arg_t arg = *(arg_t *)args;

	return (void *) (arg.val * 9); // return the result as a address
}

int main()
{
	pthread_t tids[MAXTHREADS];
	arg_t args[MAXTHREADS];
	
	for (int i = 0; i < MAXTHREADS; i++)
	{
		args[i].val = i + 1;
		pthread_create(&tids[i], NULL, func, (void*) &args[i]);
	}
	
	for (int i = 0; i < MAXTHREADS; i++)
	{
		int *ptr; 
		pthread_join(tids[i], (void **) &ptr); 
		printf("Thread %d returned %d\n", i,  ptr); // simply printing the address will print the returned value
		// printf("Thread %d returned %d\n", i, *ptr); // this will give an error as it is not a valid address to deref
	}
}