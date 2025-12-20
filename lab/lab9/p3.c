#include <stdio.h>
#include <pthread.h>

#define MAXTHREADS 10

int global_counter = 0;

void* func(void *args)
{
	int local_counter = 0;
	local_counter++;
	global_counter++;
	
	printf("Local Counter: %d, Global Counter: %d\n", local_counter, global_counter);
	
	
	return NULL;
}

int main()
{
	pthread_t tids[MAXTHREADS];
	
	for (int i = 0; i < MAXTHREADS; i++)
	{
		pthread_create(&tids[i], NULL, func, NULL);
	}
	
	for (int i = 0; i < MAXTHREADS; i++)
	{
		pthread_join(tids[i], NULL);
	}
	
	printf("Done\n");
	return 0;
}