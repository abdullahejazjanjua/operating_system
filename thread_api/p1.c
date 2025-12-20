#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *myfunc(void *arg)
{
    return (void *) "Hello from the other side";
}

int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, myfunc, NULL);
    char *status;
    pthread_join(thread_id, (void*) &status);
    printf("Thread returned %s\n", status);
}