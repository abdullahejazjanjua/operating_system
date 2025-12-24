/*
 * Fork two child processes from a single parent. The first child should calculate the square of a number, 
 * the second should calculate the cube, and the parent must use wait() to ensure both finish before printing 
 * "Calculations Complete" 
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main()
{
	int rc1, rc2, num;
	printf("Enter a number: ");
	scanf("%d", &num);
	printf("\n");
	
	printf("Original num: %d\n", num);
	
	if ((rc1 = fork()) < 0)
	{
		fprintf(stderr, "fork() failed\n");
		return 1;
	}
	else if (rc1 == 0)
	{
		num = num * num; // squaring
		exit(num);
	}
	else 
	{
		if ((rc2 = fork()) < 0)
		{
			fprintf(stderr, "fork() failed\n");
			return 1;
		}
		else if (rc2 == 0)
		{
			num = num * num * num; // cubing
			exit(num);
		}
		else
		{
			int status, pid;
			while((pid = wait(&status)) > 0)
			{
				if(WIFEXITED(status))
				{
					int result = WEXITSTATUS(status);
					printf("num (Child ID: %d): %d\n", pid, result);
				}
			}
			// printf("num: %d\n", num);
		}
	}
}