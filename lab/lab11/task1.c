/*
 * The main program creates a thread and will use the results produced
 * by the tfunc(). It has to wait that tfunc() produces the result
 * before proceeding forward.
 *
 * Task:
 * Your job is to implement the synchronization such that the main
 * thread waits for the child thread (tfunc) to produce the result
 * before using it. Ideally the output should look like:
 *
 * main: creating thread.
 * thread: produced result.
 * main: result = 7
 *
 */



#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


pthread_cond_t cond;
pthread_mutex_t mlock;

int result = 0;

void *tfunc(void *arg) 
{

    // do some work
    int r = rand()%10;
    sleep(r);
    result = 7;

    printf("thread: produced result.\n");
    
    pthread_cond_signal(&cond);
    return NULL;
}

int main() 
{
    srand(time(NULL));
    pthread_mutex_init(&mlock, NULL);
    pthread_cond_init(&cond, NULL);
    
    printf("main: creating thread.\n");
    pthread_t tid;
    pthread_create(&tid, NULL, tfunc, NULL);

    // main should wait here for the thread
    pthread_mutex_lock(&mlock);
    while(result == 0)
    	pthread_cond_wait(&cond, &mlock);
    pthread_mutex_unlock(&mlock);
    // use the thread result
    printf("main: result = %d\n", result);

    pthread_join(tid, NULL);
    return 0;
}
