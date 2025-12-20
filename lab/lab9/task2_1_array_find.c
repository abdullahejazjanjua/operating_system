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

int * make_array_random(long size) {

    srand(time(NULL));

    int * arr = malloc(size*sizeof(long));
    if (arr==NULL) exit(-1);

    for(long i=0; i<size; i++)
        arr[i] = rand()%MODULO;

    return arr;
}


int find_array(int *arr, long size, int val) {
    int idx = -1;
    for(long i=0; i<size; i++)
      if (arr[i]==val)
        idx = i;

    return idx;
}


void *find_array_thread(void *arg) {

    /*
     * your implementation goes here.
     * create any helper functions you might need.
     */

    return NULL;
}

int main() {

    int * arr = make_array_random(N);

    // value to search
    int val = rand()%MODULO;

    int idx1 = find_array(arr, N, val);
    printf("find_array found val=%d at index=%d\n", val, idx1);


    int idx2 = -1;

    /*
     * YOUR IMPLEMANTATION GOES HERE.
     * ADD ANY HELPER FUNCTIONS NEEDED.
     */

     printf("using a separate thread found val=%d at index=%d\n", val, idx2);

    free(arr);
    return 0;
}
