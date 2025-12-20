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
	pthread_create(&tid, NULL, func, NULL); 
	pthread_join(tid, NULL); // wait for child to finish before continuing
	return 0;
}