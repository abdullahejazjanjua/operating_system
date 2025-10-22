#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int rc = fork();
    if (rc < 0)
    {
        perror("fork()");
        return 1;
    }

    if (rc == 0)
    {
        int fd = open("report.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        char *args[] = {"ls", "-l", "..", NULL};
        execvp(args[0], args);
    }
    else
    {
        wait(0);
        printf("Child process finished. Check report.txt\n");
    }
}
