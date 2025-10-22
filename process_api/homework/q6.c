/*
    - Same as q5.c
    - The waitpid is usefull, when we want to wait for some specific child
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    printf("Hello, world\n");
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "Process creation failed\n");
        exit(0);
    }
    else if (rc == 0)
    {
        // printf("I am child process (PID: %d)\n", getpid());
        int wc = waitpid(getpid(), 0, 0); // As child has no children of its own, -1 is returned
        printf("I am child process (wc: %d) (PID: %d)\n", wc, getpid());
        printf("Wait executed with error: %d\n", errno);
    }
    else
    {
        // int wc = waitpid(rc, 0, 0);
        // printf("I am parent process of %d (wc: %d) (PID: %d)\n", rc, wc, getpid());
        printf("I am parent process of %d (PID: %d)\n", rc, getpid());
         // printf("Wait executed with error: %d\n", errno);
    }
}
