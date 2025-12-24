/*
 * Create a "mini-shell" program. It should take a command name as a command-line argument 
 * (e.g., ls or whoami) and use fork() and execvp() to execute that command in the child process 
 * while the parent wait
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "USAGE: ./a.out <command_name>");
		return 1;
	}
	
	int rc;
	if((rc = fork()) < 0)
	{
		fprintf(stderr, "fork() failed\n");
		return 1;
	}
	else if (rc == 0)
	{
		char **ptr = argv;
		while(*ptr != NULL)
		{
			printf("%s\n", *ptr);
			ptr++;
		} 
		argv++; // original argv[0] is current program name
		execvp(argv[0], argv);
		printf("This shouldn't print\n");
	}
	else
	{
		while (wait(0) > 0);
		// printf("Done\n");
	}
}