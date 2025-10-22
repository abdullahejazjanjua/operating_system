/*
 Taken from : https://en.wikipedia.org/wiki/Exec_(system_call)#C_language_prototypes
The base of each is exec, followed by one or more letters:

    * e – Environment variables are passed as an array of pointers to null-terminated strings of form name=value.
          The final element of the array must be a null pointer.[3]
    * l – Command-line arguments are passed as individual pointers to null-terminated strings.
          The last argument must be a null pointer.
    * p – Uses the PATH environment variable to find the file named in the file argument to be executed.
    * v – Command-line arguments are passed as an array of pointers to null-terminated strings.
          The final element of the array must be a null pointer.[3]
    * f (prefix) – A file descriptor is passed instead.
                   The file descriptor must be opened with O_RDONLY or O_PATH and
                   the caller must have permission to execute its file.
 */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./out.exe test");
    }

    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "Process creation failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("I am the child (PID: %d)\n", getpid());
        // printf("Using execl\n");
        // execl("/bin/ls", "ls", argv[1], (char*) NULL);
        printf("Using execv\n");
        char *args[] = {"ls", argv[1], (char*) NULL};
        execv("/bin/ls", args);
        printf("exec failed with error: %d\n", errno);
    }
    else
    {
        printf("I am the parent of %d (PID: %d)\n", rc, getpid());
    }
}
