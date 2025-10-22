/*
 - On success, wait returns pid of child process if called in parent.
 - else, it returns -1

 - When wait is called in child then. errno is set to 10 (No child processes) and nothing happens
 - output:
        Hello, world
        I am parent process of 74529 (PID: 74528)
        I am child process (wc: -1) (PID: 74529)
        Wait executed with error: 10
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
        printf("I am child process (PID: %d)\n", getpid());
        // int wc = wait(0);
        // printf("I am child process (wc: %d) (PID: %d)\n", wc, getpid());
        // printf("Wait executed with error: %d", errno);
    }
    else
    {
        int status;
        int wc = wait(&status);
        printf("I am parent process of %d (wc: %d) (PID: %d)\n", rc, wc, getpid());
        // printf("I am parent process of %d (PID: %d)\n", rc, getpid());
        if (WIFEXITED(status))
        {
            printf("Yes, process terminated normally\n");
        }
        else
        {
            printf("No, process terminated normally\n");
        }
    }
}
