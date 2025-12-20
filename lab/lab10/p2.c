#include <stdio.h>
#include <pthread.h>

#define NTHREADS 2

pthread_mutex_t mlock;

void *print_msg(void *arg)
{
	char *message = (char*) arg;
	int i = 0;
	pthread_mutex_lock(&mlock);
	while(message[i] != '\0')
	{
		printf("%c", message[i]);
		i++;
	}
	pthread_mutex_unlock(&mlock);
	pthread_exit(0);
}


int main()
{
	pthread_mutex_init(&mlock, NULL);
	pthread_t tids[4];
	
	pthread_create(&tids[0], NULL, print_msg, "AAAAAA");
	pthread_create(&tids[1], NULL, print_msg, "BBBBBB");
	pthread_create(&tids[2], NULL, print_msg, "CCCCCC");
	pthread_create(&tids[3], NULL, print_msg, "DDDDDD");
	
	for(int i = 0; i < NTHREADS; i++)
	{
		pthread_join(tids[i], NULL);
	}
	printf("\nDone\n");
	pthread_mutex_destroy(&mlock);
}