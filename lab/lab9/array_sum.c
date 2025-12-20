#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 1000000000
#define NTHREADS 8

void* hello(void* p)
{
    printf("Hello world from child thread!\n");
    return NULL;
}

int* make_array(int size)
{
    int* arr = malloc(size * sizeof(int));
    if (arr == NULL) exit(-1);

    for (int i = 0; i < size; i++)
        arr[i] = 2;

    return arr;
}

int sum_array(int* arr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];

    return sum;
}

typedef struct thread_info
{
    int* start;
    int size;
} thread_info;

void* partial_sum_thread(void* p)
{
	thread_info t = *(thread_info*)p;
	int *partial_sum = (int *) malloc(sizeof(int));
	*partial_sum = 0;
	
	for(int i = 0; i < t.size; i++)
	{
		*partial_sum += t.start[i];
	}
	
	return (void*) partial_sum;
	
}

int sum_array_parallel(int* arr, int size)
{
	pthread_t tids[NTHREADS];
	thread_info args[NTHREADS];
	
	int sum;
	int *partial_sum;
	int size_per_thread = size / NTHREADS;
	
	for(int i = 0; i < NTHREADS; i++)
	{
		args[i].size = size_per_thread;
		args[i].start = arr + (i * size_per_thread);
	
		pthread_create(&tids[i], NULL, partial_sum_thread, (void*) &args[i]);	
	}
	
	for(int i = 0; i < NTHREADS; i++)
	{
		pthread_join(tids[i], (void**) &partial_sum);	
		sum += *partial_sum;
		free(partial_sum);
	}

    return sum;
}

int main()
{
    struct timeval start_time, end_time;
    int seconds, microseconds;
    double elapsed_time;

    int* arr = make_array(N);

    gettimeofday(&start_time, NULL);
    int sum1 = sum_array(arr, N);
    gettimeofday(&end_time, NULL);
    seconds = end_time.tv_sec - start_time.tv_sec;
    microseconds = end_time.tv_usec - start_time.tv_usec;
    elapsed_time = seconds + microseconds / 1000000.0;
    printf("sum_array returned %d using %lf seconds\n", sum1, elapsed_time);

    gettimeofday(&start_time, NULL);
    int sum2 = sum_array_parallel(arr, N);
    gettimeofday(&end_time, NULL);
    seconds = end_time.tv_sec - start_time.tv_sec;
    microseconds = end_time.tv_usec - start_time.tv_usec;
    elapsed_time = seconds + microseconds / 1000000.0;
    printf("sum_array_parallel returned %d using %lf seconds\n", sum2, elapsed_time);

    free(arr);
    return 0;
}