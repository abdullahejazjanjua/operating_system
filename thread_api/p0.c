#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *myfunc(void *arg)
{
    // This works
    // int *val = (int*) malloc(sizeof(int));
    // *val = 1;
    // return (void*) val;

    // This as well but returns a void pointer that points to address 1
    // return (void *) 1;

    // This allocates the val on stack and when thread exits, stack is destroyed and thus
    //  the val is pointing to a invalid address
    int val = 1;
    return  &val;

}

int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, myfunc, NULL);
    void *status;
    pthread_join(thread_id, (void*) &status);
    // printf("Thread returned %d\n", (int) status); // This prints the value returned and thus works as 1 is a valid value
    printf("Thread returned %d\n", *(int*) status); // This gives seg fault as 1 is NOT a valid address
}