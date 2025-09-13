/*
    * The output is:
        I am child process (PID: 47302)
              28      77     644 p3.c
        I am the parent process of 47302 (PID: 47301)
    * Interestingly, the code after execl isnt executed.
    * That is because, previous copied code and static data is overwritten by the new process.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/errno.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "Process creation failed\n");
        exit(0);
    }
    else if (rc == 0)
    {
        printf("I am child process (PID: %d)\n", getpid());
        execl("/usr/bin/wc", "wc", "p3.c", (char*) NULL);
        printf("execl failed with error %d\n", errno);
        printf("This shouldnt run\n");
    }
    else
    {
        wait(NULL);
        printf("I am the parent process of %d (PID: %d)\n", rc, getpid());
    }
}
