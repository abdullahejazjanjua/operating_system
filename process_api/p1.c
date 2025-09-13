/*
 fork() has two return calls. It returns values to both parent and child process.
 To the parent process, it returns the PID of the child process.
 To the child process, it returns 0 indicating sucessfull creation of the process.
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Hello, world\n");
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "Process creation failed\n");
    }
    else if (rc == 0)
    {
        printf("Hello, I am a child process with PID: %d\n", getpid());
    }
    else
    {
        printf("Hello, I am parent process of %d with PID: %d\n", rc, getpid());
    }
}
