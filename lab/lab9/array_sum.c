#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 1000000000
#define NTHREADS 8

void* hello (void* p) {
	printf("Hello world from child thread!\n");
	return NULL;
}

long * make_array(long size) {

    long * arr = malloc(size*sizeof(long));
    if (arr==NULL) exit(-1);

    for(long i=0; i<size; i++)
        arr[i] = 2;

    return arr;
}

long sum_array(long *arr, long size) {
    long sum = 0;
    for(long i=0; i<size; i++)
        sum += arr[i];

    return sum;
}

typedef struct thread_info {
    long * start;
    long size;
} thread_info;


void * partial_sum_thread (void *p) {
    thread_info * ip = (thread_info *)p;
    long partial_sum = 0;
    for(long i=0; i<ip->size; i++)
        partial_sum += ip->start[i];

    long * retp = malloc(sizeof(long ));
    *retp = partial_sum;
    return retp;
}

long sum_array_parallel(long *arr, long size) {
    pthread_t tid[NTHREADS];
    thread_info info[NTHREADS];
    for (long i=0; i<NTHREADS; i++) {
        info[i].size = size/NTHREADS;
        info[i].start = arr + i*(size/NTHREADS);
    }
    for(long i=0; i<NTHREADS; i++)
        pthread_create(&tid[i], NULL, partial_sum_thread, &info[i]);

    long * retpp = NULL;
    long sum = 0;
    for(long i=0; i<NTHREADS; i++) {
        pthread_join(tid[i], (void **)&retpp);
        sum += *retpp;
    }

    return sum;
}

int main() {

    struct timeval start_time, end_time;
    long seconds, microseconds;
    double elapsed_time;

    long * arr = make_array(N);

    gettimeofday(&start_time, NULL);
    long sum1 = sum_array(arr, N);
    gettimeofday(&end_time, NULL);
    seconds = end_time.tv_sec - start_time.tv_sec;
    microseconds = end_time.tv_usec - start_time.tv_usec;
    elapsed_time = seconds + microseconds / 1000000.0;
    printf("sum_array returned %ld using %lf seconds\n", sum1, elapsed_time);

    gettimeofday(&start_time, NULL);
    long sum2 = sum_array_parallel(arr, N);
    gettimeofday(&end_time, NULL);
    seconds = end_time.tv_sec - start_time.tv_sec;
    microseconds = end_time.tv_usec - start_time.tv_usec;
    elapsed_time = seconds + microseconds / 1000000.0;
    printf("sum_array_parallel returned %ld using %lf seconds\n", sum2, elapsed_time);

    free(arr);
    return 0;
}
