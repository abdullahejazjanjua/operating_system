/*
 * Implement a thread-safe circular logger.
     * Shared Resource: A global array of strings char logs[10][256] and an integer write_index.
     * Create 4 threads that are constantly generating logs (e.g., "Thread 2: Event at time X").
     * Use a mutex to protect the write_index.
 * The Catch: Ensure that the logging is "Atomic"—no thread should be able to start writing its string and
   get interrupted by another thread writing to the same index.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAXLEN 256
#define LOGLEN 10
#define NTHREADS 10


char writelog[LOGLEN][MAXLEN];
int writeindex = 0;

pthread_mutex_t mlock;



void* write_to_log(void *args)
{
	int id = (int) args;
	char local_msg[MAXLEN];

	sprintf(local_msg, "Thread %d: Event at time %ld", id, time(NULL));

	pthread_mutex_lock(&mlock);
	strncpy(writelog[writeindex], local_msg, MAXLEN - 1);
	writelog[writeindex][MAXLEN - 1] = '\0';
	writeindex++;
	pthread_mutex_unlock(&mlock);
	
	return NULL;
}


int main()
{
	pthread_t tids[NTHREADS];
	
	pthread_mutex_init(&mlock, NULL);
	
	for (int i = 0; i < NTHREADS; i++)
	{
		pthread_create(&tids[i], NULL, write_to_log, (void*) i);
	}
	
	for (int i = 0; i < NTHREADS; i++)
	{
		pthread_join(tids[i], NULL);
	}
	
	pthread_mutex_destroy(&mlock);
	
	printf("\nFinal Log State:\n");
    for (int i = 0; i < LOGLEN; i++) 
    {
        printf("[%d]: %s\n", i, writelog[i]);
    }
}