#include <stdio.h>
#include <pthread.h>

void *func(void *arg)
{
	
	printf("After thread call\n");
	return NULL;
}

int main()
{
	pthread_t tid;
	printf("Before thread call\n");
	pthread_create(&tid, NULL, func, NULL); // if parent continues running after creating the thread, 
											// then the program wil end and "After thread call" will not 
											// be printed
	return 0;
}