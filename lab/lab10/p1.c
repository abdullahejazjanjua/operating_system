#include <stdio.h>
#include <pthread.h>

#define NTHREADS 10
#define N 50000

int balance = 1000;
pthread_mutex_t mlock;

void *withdraw(void *arg)
{
	for(int i = 0; i < N; i++)
	{
		pthread_mutex_lock(&mlock);
		balance += 10;
		pthread_mutex_unlock(&mlock);
	}
	pthread_exit(0);
}

void *deposit(void *arg)
{
	for(int i = 0; i < N; i++)
	{
		pthread_mutex_lock(&mlock);
		balance -= 10;
		pthread_mutex_unlock(&mlock);
	}
	pthread_exit(0);
}

int main()
{
	pthread_mutex_init(&mlock, NULL);
	pthread_t tids[2];
	printf("Before Balance: %d\n", balance);
	
	pthread_create(&tids[0], NULL, withdraw, NULL);
	pthread_create(&tids[1], NULL, deposit, NULL);
	
	for(int i = 0; i < 2; i++)
	{
		pthread_join(tids[i], NULL);
	}
	
	printf("After Balance: %d\n", balance);
	
	pthread_mutex_destroy(&mlock);
}