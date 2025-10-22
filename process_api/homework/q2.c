/*
 - We open a file for both processes
 - Both the processes are writing to the file at the same time.
 - It seems that when we do this, our outputs are interleaved, when I add a sleep
 - They can indeed access the same file.
 */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define NUM_WRITES 10

int main()
{
    int file_descriptor = open("q2.output", O_WRONLY | O_CREAT );
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
        printf("file descriptor: %d \n", file_descriptor);
        char *buf = "Hello, I am child writing to file\n";
        for (int i = 0; i < NUM_WRITES; i++)
        {
            sleep(2);
            write(file_descriptor, (void*) buf, (size_t) sizeof(char) * (strlen(buf)));
        }
        printf("\n-------------------------------------------\n");
    }
    else
    {
        printf("\n-------------------------------------------\n");
        printf("Hello, I am the parent (PID: %d)\n", getpid());
        printf("file descriptor: %d \n", file_descriptor);
        char *buf = "Hello, I am parent writing to file\n";
        for (int i = 0; i < NUM_WRITES; i++)
        {
            sleep(2);
            write(file_descriptor, (void*) buf, (size_t) sizeof(char) * (strlen(buf)));
        }
        printf("\n-------------------------------------------\n");

    }

}
