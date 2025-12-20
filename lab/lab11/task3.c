/*
 * PRODUCER-CONSUMER problem
 *
 *
 * Task:
 * Implement the proucer-consumer problem for NPRODUCERS producers and
 * NCONSUMERS consumers and a buffer size BUFFSIZE and produce NVALUES
 * values.
 *
 * Can you devise a test your implementation works correctly? i.e.,
 * can you verify that all the values produced have been consumed and
 * only those?
 *
 */



#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NPRODUCERS 10
#define NCONSUMERS 5
#define BUFFSIZE 10
#define NVALUES 1000

int BUFFER[BUFFSIZE];

void *producer(void *arg) {

    return NULL;
}

void *consumer(void *arg) {

    return NULL;
}

int main() {

    // create producers and consumers

    // let them do thier work

    // join all producers and consumers


    printf("the enddddddd.\n");
    return 0;
}
