/*
 - Here, the parent process is killed.
 - Thus, the child  process has been an orphan.
 The output is:
    Hello, I am the parent of 57239 (PID: 57236)
    Hello, I am the child process (PID: 57239)
    [1]    57236 killed     ./out.exe
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
    int rc = fork();
    int pid = getpid(); // Once fork() is called, then PC is here
    //exit(0); // So, calling exit or kill here will stop both processes as they share the same code
    if (rc < 0)
    {
        fprintf(stderr, "Process creations failed\n");
    }
    else if (rc == 0)
    {
        printf("Hello, I am the child process (PID: %d)\n", pid);
    }
    else
    {
        printf("Hello, I am the parent of %d (PID: %d)\n", rc, pid);
        kill(pid, SIGKILL);
        printf("I am killed, I shouldn't run\n");
    }
}
