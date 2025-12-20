#include <stdio.h>
#include <pthread.h>

#define MAXTHREADS 10

typedef struct arg_t
{
	int val;
} arg_t;

void* func(void *args)
{
	arg_t arg = *(arg_t*)args;
	printf("val: %d\n", arg.val);
	
	return NULL;
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
		pthread_join(tids[i], NULL);
	}
	
	printf("Done!\n");
}