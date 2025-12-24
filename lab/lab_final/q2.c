#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NPRODUCERS 10
#define NCONSUMERS 10
#define BUFSIZE 10
#define NVALUES 1000
#define MODULO 99


pthread_mutex_t mlock;
pthread_cond_t pcond, ccond;

int buffer[BUFSIZE];
int head = 0, tail = 0, count = 0;

int producer_sum = 0, consumer_sum = 0; // verifies correctness


int get()
{
	int val = buffer[tail]; 
	tail = (tail + 1) % BUFSIZE;
	
	return val;
}

void put(int val)
{
	buffer[head] = val;
	head = (head + 1) % BUFSIZE;
}

void* producer(void *args)
{
	for (int i = 0; i < NVALUES; i++)
	{
		pthread_mutex_lock(&mlock);
		while (count == BUFSIZE)
		{
			pthread_cond_wait(&pcond, &mlock);
		}
		int val = rand() % MODULO;
		put(val);
		count++;
		printf("Producer: %d\n", val);
		producer_sum += val;
		pthread_cond_signal(&ccond);
		pthread_mutex_unlock(&mlock);
		
	}
	
	pthread_exit(0);
}


void* consumer(void *args)
{
	
	for (int i = 0; i < NVALUES; i++)
	{
		pthread_mutex_lock(&mlock);
		while (count == 0)
		{
			pthread_cond_wait(&ccond, &mlock);
		}
		int val = get();
		consumer_sum += val;
		count--;
		printf("Consumer: %d\n", val);
		pthread_cond_signal(&pcond);
		pthread_mutex_unlock(&mlock);
		
	}
	pthread_exit(0);
}


int main()
{
	srand(time(0));
	
	pthread_mutex_init(&mlock, NULL);
	pthread_cond_init(&ccond, NULL);
	pthread_cond_init(&pcond, NULL);

	int ntotal = NPRODUCERS + NCONSUMERS;
	pthread_t tids[ntotal];
	
    for(int i = 0; i < NPRODUCERS; i++)
    {
    	pthread_create(&tids[i], NULL, producer, NULL);
    }
    
    for(int i = NPRODUCERS; i < ntotal; i++)
    {
    	pthread_create(&tids[i], NULL, consumer, NULL);
    }

    for(int i = 0; i < ntotal; i++)
    {
    	pthread_join(tids[i], NULL);
    }

	
	
	pthread_mutex_destroy(&mlock);
	pthread_cond_destroy(&ccond);
	pthread_cond_destroy(&pcond);

	printf("The end %d == %d (consumer_sum == producer_sum).\n", consumer_sum, producer_sum);


}