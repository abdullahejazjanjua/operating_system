#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
        close(STDOUT_FILENO); // OR close(1)
        open("p4.output", O_WRONLY | O_CREAT | O_TRUNC); // Reter to man 2 open
        execl("/usr/bin/wc", "wc", "p4.c", (char*) NULL);
        printf("The exec failed with status %d", errno);
    }
    else
    {
        printf("I am the parent process of %d (PID: %d)", rc, getpid());
    }

    return 0;
}
