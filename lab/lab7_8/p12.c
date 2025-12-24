/*
 * Write a program that takes a filename as the first argument and a command (with its own arguments) as 
 * the remaining arguments. Your program should execute the command, but instead of printing the output 
 * to the screen, it must redirect all standard output (stdout) to the specified file.
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		fprintf(stderr, "USAGE: ./a.out <output.txt> <command> <args0> ... <argsn>");
		return 1;
	}
	
	int rc;
	if ((rc = fork()) < 0)
	{
		fprintf(stderr, "fork() failed\n");
		return 1;
	}
	else if (rc == 0)
	{
		printf("You entered following args: \n");
		char **ptr = argv;
		while (*ptr != NULL)
		{
			printf("%s\n", *ptr);
			ptr++;
		}
		argv++; // original argv[0] is current process name
		
		close(STDOUT_FILENO);
		int fd = open(argv[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		
		argv++; // argv[0] is output file name
		
		execvp(argv[0], argv); // sh -c "ls *.c | wc -l" : call shell (sh/bash) itself to run this with a single exec
		printf("This shouldn't print\n");
	}
	else
	{
		while (wait(0) > 0);
		printf("Done!\n");
	}
}