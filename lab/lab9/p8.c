/*
	* Q2 (Medium): Implement Matrix-Vector Multiplication (Ax=b). If A is a 4×4 matrix, create 4 
	* threads where each thread calculates exactly one element of the resulting vector b.	 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct args_t 
{
	int *A;
	int *B;
	int size;
} args_t;


void* vec_mul(void *args)
{
	args_t thread_args = *(args_t*) args;
	int *sum = (int*) malloc(sizeof(int));
	*sum = 0;
	
	for(int i = 0; i < thread_args.size; i++)
	{
		*sum += (thread_args.A[i] * thread_args.B[i]);
	}
	return (void *) sum;
}




int main()
{
	int size = 4;
	pthread_t tids[size];
	
	int **A = (int**) malloc(size * sizeof(int*)); // size x size
	int *B = (int*) malloc(size * sizeof(int)); // size x 1
	int *C = (int*) malloc(size * sizeof(int)); // size x 1
	
	for(int i = 0; i < size; i++)
	{
		A[i] = (int*) malloc(size * sizeof(int));
	}
	
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		count++;
		B[i] = count;
		C[i] = 0;
		for(int j = 0; j < size; j++)
		{
			A[i][j] = count;
		}
	}
	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			args_t *thread_args = (args_t*) malloc(sizeof(args_t));
			thread_args->A = A[i];

			thread_args->B = B;
			thread_args->size = size;
			pthread_create(&tids[j], NULL, vec_mul, (void *) thread_args);
		}
	}
	
	for (int i = 0; i < size; i++)
	{
		int *sum;
		pthread_join(tids[i], (void**) &sum);
		C[i] = *sum;
	}
	
	for (int i = 0; i < size; i++)
	{
		printf("%d ", C[i]);
	}
	printf("\n");
}