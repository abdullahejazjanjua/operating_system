/*
 * make_array_random(long size):
 *   dynamically allocates an array of "size" integers
 *   initialiezes the array with random values less than MODULO
 *   returns the address of this initialized array
 *
 * find_array(long *arr, long size, int val):
 *   searches for the value "val" in the array "arr"
 *   returns the index of element where value "val" is found, otherwise -1
 *   if there are multiple instances of value "val", returns the last index
 *
 *
 * Task:
 *   your job is to implement the function find_array_parallel() which
 *   does behaves exactly the same as find_array() but does so in parallel
 *   by dividing the search task among NTHREADS threads.
 *
 *   CAN'T USE GLOBAL VARIABLES.

*/



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 1000000000
#define NTHREADS 8
#define MODULO 100000000


long * make_array_random(long size) {

    srand(time(NULL));

    long * arr = malloc(size*sizeof(long));
    if (arr==NULL) exit(-1);

    for(long i=0; i<size; i++)
        arr[i] = rand()%MODULO;

    return arr;
}


int find_array(long *arr, long size, int val) {
    int idx = -1;
    for(long i=0; i<size; i++)
      if (arr[i]==val)
        idx = i;

    return idx;
}


int find_array_parallel(long *arr, long size, int val) {

    /*
     * your implementation goes here.
     * create any helper functions you might need.
     */

    return -1;
}

int main() {

    struct timeval start_time, end_time;
    long seconds, microseconds;
    double elapsed_time;

    long * arr = make_array_random(N);

    int val = rand()%MODULO;

    gettimeofday(&start_time, NULL);
    int idx1 = find_array(arr, N, val);
    gettimeofday(&end_time, NULL);
    seconds = end_time.tv_sec - start_time.tv_sec;
    microseconds = end_time.tv_usec - start_time.tv_usec;
    elapsed_time = seconds + microseconds / 1000000.0;
    printf("find_array found val=%d at index=%d using %lf seconds\n", val, idx1, elapsed_time);

    gettimeofday(&start_time, NULL);
    int idx2 = find_array_parallel(arr, N, val);
    gettimeofday(&end_time, NULL);
    seconds = end_time.tv_sec - start_time.tv_sec;
    microseconds = end_time.tv_usec - start_time.tv_usec;
    elapsed_time = seconds + microseconds / 1000000.0;
    printf("sum_array_parallel round val=%d at index=%d using %lf seconds\n", val, idx2, elapsed_time);

    free(arr);
    return 0;
}
