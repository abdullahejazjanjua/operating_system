#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int rc = fork();
    if (rc == -1)
    {
        fprintf(stderr, "fork failed\n");
        return 1;
    }

    if (rc == 0)
    {
        char *args[] = {"date", NULL};
        execvp(args[0], args);
    }
    else
    {
        wait(0);
        printf("This is parent running\n");
    }
}
