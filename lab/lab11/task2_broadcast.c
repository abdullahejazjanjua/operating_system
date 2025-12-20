/*
 * The main program creates NUMTHREADS threads and waits for them to finish.
 * Each thread receives its rank and prints it.
 *
 * Task:
 * Your job is to synchronize threads' execution in such a way that they
 * print their output in order of their rank, i.e., if (rank_i < randk_j)
 * then thread_i output should be printed before thread_j.
 *
 * The output will loook something like:
 *
 * main: creating threads.
 * thread: my turn!, my rank is 0.
 * thread: my turn!, my rank is 1.
 * thread: my turn!, my rank is 2.
 * thread: my turn!, my rank is 3.
 * thread: my turn!, my rank is 4.
 * thread: my turn!, my rank is 5.
 * thread: my turn!, my rank is 6.
 * thread: my turn!, my rank is 7.
 * thread: my turn!, my rank is 8.
 * thread: my turn!, my rank is 9.
 * main: i hope all threads are finished by now!!
 *
 *
 * Clarification:
 * The intention was that:
 * 1. main will create all threads
 * 2. all threads will immediately go to sleep
 * 3. main will wake thread0 and go to sleep
 * 4. thread0 will do its task and wake thread1
 * 5. thread1 will do its task and wake thread2 and so on.
 * 6. the last thread will do its work and wake main.
 * 7. now main knows that all threads have take their turns
 * and it will terminate.
 *
 * If you did any other way, try doing it this way.
 *
 * Clarification 2:
 * Did you use sleep() in your solution?
 * That's not good synchronization :(
*/



#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMTHREADS 1000

pthread_cond_t cond;
pthread_mutex_t mlock;

int ticket = 0;

void *tfunc(void *arg) 
{

    int rank = (int) arg;

    // do some work
    sleep(rand()%5);
    
    pthread_mutex_lock(&mlock);
    while(ticket != rank)
    	pthread_cond_wait(&cond, &mlock);
    
    printf("thread: my turn!, my rank is %d.\n", rank);
    
    pthread_cond_broadcast(&cond);
    ticket++;
    pthread_mutex_unlock(&mlock);

    return NULL;
}

int main() 
{
    srand(time(NULL));
    pthread_t tid[NUMTHREADS];
    
    printf("main: creating threads.\n");
    for(int i=0; i<NUMTHREADS; i++)
        pthread_create(&tid[i], NULL, tfunc, (void *) i);


    // main should wait here for the thread
    for(int i=0; i<NUMTHREADS; i++)
        pthread_join(tid[i], NULL);


    printf("main: I hope all threads are finished by now!!\n");

    for(int i=0; i<NUMTHREADS; i++)
        pthread_join(tid[i], NULL);
    return 0;
}
