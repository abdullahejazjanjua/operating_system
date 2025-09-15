/*
    Changes made to variables in one process doesn't affect the variables of another process because they don't
    share memory.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    int x = 100;
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "Process creation failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("\n-------------------------------------------\n");
        printf("Hello, I am the child (PID: %d)\n", getpid());
        printf("The value of x is: %d \n", x);
        printf("Incrementing x:\n");
        x++;
        printf("Now, The value of x is: %d\n", x);
        printf("\n-------------------------------------------\n");

    }
    else
    {
        printf("\n-------------------------------------------\n");
        printf("Hello, I am the parent (PID: %d)\n", getpid());
        printf("The value of x is: %d (PID: %d)\n", x, getpid());
        printf("Incrementing x:\n");
        x++;
        printf("Now, The value of x is: %d\n", x);
        printf("\n-------------------------------------------\n");
    }
}
