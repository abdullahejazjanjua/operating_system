#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXTHREADS 10

typedef struct arg_t
{
	int val;
} arg_t;

typedef struct result_t
{
	int val;
} result_t;


void* func(void *args)
{
	arg_t arg = *(arg_t *)args;
	result_t *result = (result_t*) malloc(sizeof(result_t));
	
	result->val = arg.val * 9;
	
	return (void *) result; // return address of the result_t that is allocated on the heap
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
		result_t *res_ptr; // make a pointer to result_t to store the address
		pthread_join(tids[i], (void **) &res_ptr); // stores the returned address into res_ptr
		printf("Thread %d returned %d\n", i, res_ptr->val);
		free(res_ptr);
	}
}