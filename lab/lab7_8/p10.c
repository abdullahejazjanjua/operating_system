/*
 * Write a program that purposefully creates a Zombie process. Explain why the child becomes a 
 * zombie based on the parent's action (or lack thereof)
*/

#include <stdio.h>
#include <unistd.h>


int main()
{
	int rc;
	if((rc = fork()) < 0)
	{
		fprintf(stderr, "fork() failed\n");
		return 1;
	}
	else if (rc == 0)
	{
		printf("Huh?\n");
	}
	else 
	{
		sleep(2);
	}
}