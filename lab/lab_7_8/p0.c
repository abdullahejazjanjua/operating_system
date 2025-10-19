#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    while(1)
    {
        int num;
        printf("\nEnter a number: ");
        scanf("%d", &num);

        if (num == 0)
        {
            break;
        }

        for(int i = 0; i < num; i++)
        {
            int rc = fork();
            if (rc == -1)
            {
                fprintf(stderr, "fork failed\n");
                return 1;
            }

            if (rc == 0)
            {
                srand(time(0) + getpid());
                printf("num: %d\n", rand() % 100);
                exit(0);
            }
            else
            {
                wait(0);
            }
        }
    }
}
