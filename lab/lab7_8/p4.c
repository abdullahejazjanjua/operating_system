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
	
	if (rc == 0)
	{
		printf("Hello, I am a child (ID: %d)\n", getpid());
	}
	else 
	{
		int rc2 = fork();
		if (rc2 < 0)
		{
			fprintf(stderr, "fork() failed\n");
			return 1;
		}
		
		if (rc2 == 0)
		{
			printf("Hello, I am a child 02 (ID: %d)\n", getpid());
		}
		else
		{
			while (wait(NULL) > 0);
			printf("Hello, I am parent of %d & %d (ID: %d)\n", rc, rc2, getpid());
		}
	}
	
	return 0;
}