/*
 - If our parent process runs first, we can tell it stop using SIGSTOP signal.
 - Now, the child process starts executing, after it has finished we can
   tell it's parent to continue using SIGCONT and getting the parent's id using getppid
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


int main() {
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "Process creation failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("Hello\n");
        kill(getppid(), SIGCONT);
    }
    else
    {
        kill(getpid(), SIGSTOP);
        printf("Goodbye\n");
    }

    return 0;
}
