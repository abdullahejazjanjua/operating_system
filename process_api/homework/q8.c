/*

    * dup2(old_filedesc, new_filedesc)
    * It will duplicate old_filedesc's File and assign it to new_filedesc's File
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_BYTES 50

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./out.exe test");
        exit(1);
    }

    int p[2];
    if (pipe(p) < 0) {
        fprintf(stderr, "Pipe failed\n");
        exit(1);
    }

    int rc_1 = fork();
    if (rc_1 < 0)
    {
        fprintf(stderr, "Process 1 creation failed\n");
        exit(1);
    }
    else if (rc_1 == 0)
    {
        printf("I am the first child (PID: %d) \n", getpid());
        dup2(p[1], STDOUT_FILENO); // std_out has it's file changed to file of p[1]
        close(p[1]);
        execl("/bin/ls", "ls", argv[1], (char*) NULL);
    }
    else
    {
        int rc_2 = fork();
        if (rc_2 < 0)
        {
            fprintf(stderr, "Process 2 creation failed\n");
            exit(1);
        }
        else if (rc_2 == 0) {
            waitpid(rc_1, 0, 0); // wait for child0 to finish
            printf("I am the second child (PID: %d) \n", getpid());
            dup2(p[0], STDIN_FILENO);
            close(p[0]);
            execl("/usr/bin/grep", "grep", "test0", (char*) NULL);
        }
        else
        {
            while(wait(0) != -1);
            exit(0);
        }
    }

}
