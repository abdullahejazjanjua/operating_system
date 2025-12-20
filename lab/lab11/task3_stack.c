/*
 * PRODUCER-CONSUMER problem
 *
 *
 * Task:
 * Implement the proucer-consumer problem for NPRODUCERS producers and
 * NCONSUMERS consumers and a buffer size BUFFSIZE and produce NVALUES
 * values.
 *
 * Can you devise a test your implementation works correctly? i.e.,
 * can you verify that all the values produced have been consumed and
 * only those?
 *
 */


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NPRODUCERS 10
#define NCONSUMERS 10
#define BUFFSIZE 10
#define NVALUES 1000
#define MODULO 99

pthread_cond_t pcond = PTHREAD_COND_INITIALIZER, ccond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;

int BUFFER[BUFFSIZE];
int count = 0;

int producer_sum = 0, consumer_sum = 0;

void *producer(void *arg) 
{
	
	for(int i = 0; i < NVALUES; i++)
	{
		int val = rand() % MODULO;
		
		pthread_mutex_lock(&mlock);
		while(count == BUFFSIZE)
		{
			pthread_cond_wait(&pcond, &mlock);
		}
		
		producer_sum += val;
		BUFFER[count++] = val;
		printf("Producer: %d\n", val);
		pthread_cond_signal(&ccond);
		pthread_mutex_unlock(&mlock);
	}
	
    return NULL;
}

void *consumer(void *arg) 
{

	
	for(int i = 0; i < NVALUES; i++)
	{
		pthread_mutex_lock(&mlock);
		while(count == 0)
		{
			pthread_cond_wait(&ccond, &mlock);
		}
		
		int val = BUFFER[--count];
		printf("Consumer: %d\n", val);
		consumer_sum += val;
		
		pthread_cond_signal(&pcond);
		pthread_mutex_unlock(&mlock);
	}
    return NULL;
}

int main() 
{
	int ntotal = NPRODUCERS + NCONSUMERS;
	pthread_t tids[ntotal];
	
    // create producers and consumers
    for(int i = 0; i < NPRODUCERS; i++)
    {
    	pthread_create(&tids[i], NULL, producer, NULL);
    }
    
    for(int i = NPRODUCERS; i < ntotal; i++)
    {
    	pthread_create(&tids[i], NULL, consumer, NULL);
    }

    // let them do thier work
    
    // join all producers and consumers
    for(int i = 0; i < ntotal; i++)
    {
    	pthread_join(tids[i], NULL);
    }

    printf("The end %d == %d (consumer_sum == producer_sum).\n", consumer_sum, producer_sum);
    return 0;
}
