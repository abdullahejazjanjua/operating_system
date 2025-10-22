/*
  As standard output file is closed, nothing of the child's printf is shown in the terminal
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "Process creation failed\n");
        exit(0);
    }
    else if (rc == 0)
    {
        close(STDOUT_FILENO);
        printf("Hello, I am child (PID: %d)\n", getpid());
        printf("I am writing while my standard output file is closed\n");
    }
    else
    {
        printf("Hello, I am parent of %d (PID: %d)\n", rc, getpid());
    }
}
