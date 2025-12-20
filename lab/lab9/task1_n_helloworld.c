/*
 * The main function takes a command line argument of type int, call it N.
 * It should launch N threads, each should run hello().
 * Main thread should wait for all threads to end before exiting.
 *
 * CAN'T USE GLOBAL VARIABLES.
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void* hello (void* p) {
	printf("Hello world from child thread!\n");
	return NULL;
}

int main(int argc, char *argv[]) {

    if (argc<2) {
        fprintf(stderr, "In sufficient argumetns. Usage: ./a.out  NUMTHREADS\n");
        exit(1);
    }

    int N = atoi(argv[1]);
    printf("main() recieved arg: %d\n", N);

    /*
     * YOUR IMPLEMENTATION GOES HERE
     * ADD ANY HELPERS FUNCTIONS YOU NEED
     */

     printf("bye from main thread\n");


     return 0;
}
