#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int rc = fork();
    if (rc < -1)
    {
        perror("fork()");
        return 1;
    }

    if(rc == 0)
    {
        int num, fact = 1;
        printf("Enter a number: ");
        scanf("%d", &num);

        for(int i = 1; i <= num; i++)
            fact *= i;
        printf("Factorial of %d: %d\n", num, fact);
    }
    else
    {
        wait(0);
        printf("Factorial calculation complete\n");
    }

    return 0;
}
