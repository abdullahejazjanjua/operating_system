/*
 * Create a program where the child process prints all numbers from 1 to 5, and the parent process prints 
 * all numbers from 6 to 10
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
	int rc = fork();
	if (rc < 0)
	{
		fprintf(stderr, "fork() failed\n");
		return 1;
	}
	else if (rc == 0)
	{
		printf("Mera name hai child (ID: %d) hai aur hum 1-5 print ker rahe hain\n", getpid());
		for (int i = 0; i < 5; i++)
		{
			printf("%d ", i + 1);
		}
		printf("\n");
	}
	else
	{
		while(wait(0) > 0);
		printf("Mera name hai Parent (ID: %d) hai aur hum 6-10 print ker rahe hain\n", getpid());
		for (int i = 5; i < 10; i++)
		{
			printf("%d ", i + 1);
		}
		printf("\n");
	}
}