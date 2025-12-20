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
 *   your job is to implement the functionality of find_array_thread() which
 *   does behaves exactly the same as find_array() but would be run
 *   in a separate thread. You'll, of course have to create that thread in
 *   main() and pass any data needed by the thread. The thread will return
 *   the index where it finds the value "val" or -1, which the main thread
 *   will then print.
 *
 *   CAN'T USE GLOBAL VARIABLES.

*/



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 1000000000
#define MODULO 100000000
#define NTHREADS 10

typedef struct arg_t 
{
	int *arr;
	long size;
	int val;
} arg_t;

typedef struct ret_t
{
	int idx;
} ret_t;

int * make_array_random(long size) 
{
    srand(time(NULL));

    int *arr = malloc(size * sizeof(long));
    if (arr == NULL) exit(-1);

    for(long i=0; i<size; i++)
        arr[i] = rand()%MODULO;

    return arr;
}


int find_array(int *arr, long size, int val) 
{
    int idx = -1;
    for(long i = 0; i < size; i++)
      if (arr[i] == val)
        idx = i;

    return idx;
}


void *find_array_thread(void *args) 
{

    /*
     * your implementation goes here.
     * create any helper functions you might need.
     */
     
    arg_t arg = *(arg_t*) args;
    ret_t *ret = (ret_t*) malloc(sizeof(ret_t));
    ret->idx = -1;
    
    for(long i = 0; i < arg.size; i++)
    {
    	if(arg.arr[i] == arg.val)
     	{
      		ret->idx = i;
      	}
    }

    return (void*) ret;
}

int main() 
{

    int * arr = make_array_random(N);

    // value to search
    int val = rand()%MODULO;

    int idx1 = find_array(arr, N, val);
    printf("find_array found val=%d at index=%d\n", val, idx1);


    int idx2 = -1, size_per_thread = N / NTHREADS;
    arg_t args[NTHREADS];
    pthread_t tids[NTHREADS];
    /*
     * YOUR IMPLEMANTATION GOES HERE.
     * ADD ANY HELPER FUNCTIONS NEEDED.
    */
    
    for(int i = 0; i < NTHREADS; i++)
    {
    	args[i].size = size_per_thread;
     	args[i].arr = arr + (i * size_per_thread);
      	args[i].val = val;
    	pthread_create(&tids[i], NULL, find_array_thread, (void*) &args[i]);
    }
    
    for(int i = 0; i < NTHREADS; i++)
    {
    	ret_t *ret;
     	pthread_join(tids[i], (void **) &ret);
      	if(ret->idx != -1)
       	{
      		long global_idx = (i * size_per_thread) + ret->idx; // compute global index
            if (global_idx > idx2) 
            {
                idx2 = (int)global_idx;
            }
        }
        free(ret);
    }
     
    printf("using %d threads found val=%d at index=%d\n", NTHREADS, val, idx2);
    free(arr);
    return 0;
}
