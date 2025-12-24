#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


#define NTHREADS 50
#define NLOOPS 100


int active_dthreads = NTHREADS / 2;
pthread_mutex_t mlock;
pthread_cond_t wcond;

int balance = 1000;
int done = 0;

void* withdraw(void *args)
{
	int amount = *(int*) args;
	for (int i = 0; i < NLOOPS; i++)
	{
		pthread_mutex_lock(&mlock);
		printf("Trying to Withdraw: %d, Balance: %d\n", amount, balance);
		while (amount > balance)
		{
			if (done) 
			{
		        printf("[Exit] No more deposits coming. Thread exiting.\n");
		        pthread_mutex_unlock(&mlock); 
		        return NULL;
		    }
			pthread_cond_wait(&wcond, &mlock);
		}
		balance -= amount;
		pthread_cond_signal(&wcond);
		printf("Withdrawing: %d, Balance: %d\n", amount, balance);
		printf("\n");
		pthread_mutex_unlock(&mlock);
	}
	
	pthread_exit(0);
}


void* deposit(void *args)
{
	int amount = *(int*) args;
	for (int i = 0; i < NLOOPS; i++)
	{
		pthread_mutex_lock(&mlock);
		balance += amount;
		printf("Depositing: %d\n", balance);
		pthread_cond_signal(&wcond);
		pthread_mutex_unlock(&mlock);
	}
	pthread_mutex_lock(&mlock);
	active_dthreads--;
	if (active_dthreads == 0)
	{
		done = 1;
		pthread_cond_broadcast(&wcond); 
	}
	pthread_mutex_unlock(&mlock);
	pthread_exit(0);
}


int main()
{
	srand(time(0));
	
	pthread_mutex_init(&mlock, NULL);
	pthread_cond_init(&wcond, NULL);

	
	pthread_t tids[NTHREADS];
	
	for(int i = 0; i < (NTHREADS / 2); i++)
	{
		int *amount = (int*) malloc(sizeof(int));
		*amount = rand() % 100;
		pthread_create(&tids[i], NULL, withdraw, (void *) amount);
	}
	
	for(int i = (NTHREADS / 2); i < NTHREADS; i++)
	{
		int *amount = (int*) malloc(sizeof(int));
		*amount = rand() % 100;
		pthread_create(&tids[i], NULL, deposit, (void *) amount);
	}
	
	for(int i = 0; i < NTHREADS; i++)
		pthread_join(tids[i], NULL);
	
	pthread_mutex_destroy(&mlock);
	pthread_cond_destroy(&wcond);

	
	printf("Total balance: %d\n", balance);
}