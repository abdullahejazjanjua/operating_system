#include <stdio.h>
#include <pthread.h>

#define MAXVALS 5

int buffer[MAXVALS];
int idx = 0;


pthread_mutex_t mlock;
pthread_cond_t pcond, ccond;

void* consumer(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mlock);
		while(idx != MAXVALS)
			pthread_cond_wait(&ccond, &mlock);
		
		printf("Consuming...\n");
		for(int i = 0; i < MAXVALS; i++)
		{
			printf("%d ", buffer[i]);
		}
		printf("\n");
		idx = 0;
		pthread_cond_signal(&pcond);
		pthread_mutex_unlock(&mlock);
	}
}



int main()
{
	pthread_t tid;
	
	pthread_mutex_init(&mlock, NULL);
	pthread_cond_init(&pcond, NULL);
	pthread_cond_init(&ccond, NULL);
	
	pthread_create(&tid, NULL, consumer, NULL);
	
	while(1)
	{
		int val;
		printf("Enter a Number: ");
		if (scanf("%d", &val) != 1) 
		{
    		fprintf(stderr, "Invalid input. Exiting.\n");
     		break;
		}
		
		pthread_mutex_lock(&mlock);
		buffer[idx++] = val;
		while (idx == MAXVALS)
		{
			pthread_cond_signal(&ccond);
			pthread_cond_wait(&pcond, &mlock);
		}
		pthread_mutex_unlock(&mlock);
	}
	
	return 0;
}