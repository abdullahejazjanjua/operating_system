/*
 * Create a "grandchild" process. The Parent forks Child A, and Child A forks Child B. Each process must 
 * print its own PID and its Parent's PID (PPID) to prove the hierarchy.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int rc1, rc2;
	
	if ((rc1 = fork()) < 0)
	{
		fprintf(stderr, "fork() failed\n");
		return 1;
	}
	else if (rc1 == 0)
	{
		if ((rc2 = fork()) < 0)
		{
			fprintf(stderr, "fork() failed\n");
			return 1;
		}
		else if (rc2 == 0)
		{
			printf("My PID: %d, Parent PID: %d\n", getpid(), getppid());
		}
		else
		{
			printf("My PID: %d, Parent PID: %d\n", getpid(), getppid());
		}
	}
	else
	{
		while(wait(0) > 0);
		printf("My PID: %d, Parent PID: %d\nc", getpid(), getppid());
	}
}