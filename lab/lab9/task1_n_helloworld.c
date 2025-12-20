#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void *hello(void *p) 
{
    printf("Hello world from child thread!\n");
    return NULL;
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        fprintf(stderr, "Insufficient arguments. Usage: ./a.out NUMTHREADS\n");
        exit(1);
    }

    int N = atoi(argv[1]);
    printf("main() received arg: %d\n", N);

    pthread_t tids[N];

    // Thread Creation Loop
    for (int i = 0; i < N; i++) 
    {
        pthread_create(&tids[i], NULL, hello, NULL);
    }

    // Thread Joining Loop
    for (int i = 0; i < N; i++) 
    {
        pthread_join(tids[i], NULL);
    }

    printf("bye from main thread\n");

    return 0;
}