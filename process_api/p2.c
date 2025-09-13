#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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
    }
    else
    {
        int wc = wait(NULL);
        printf("I am parent process of %d (wc: %d) (PID: %d)", rc, wc, getpid());
    }
}
