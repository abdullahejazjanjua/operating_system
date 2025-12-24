#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
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
			close(STDOUT_FILENO);
			open("output.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
			execlp("ls", "ls", "-l", "/bin", NULL);
			printf("This shouldn't print (PARENT: %d)\n", rc1);
		}
		else
		{
			wait(0);
			char buf[256];
			int occurences = 0;
			FILE *f = fopen("output.txt", "r");
			if (!f)
			{
				fprintf(stderr, "file not found\n");
				return 1;
			}
			
			while(fscanf(f, "%255s", buf) == 1)
			{
				if (strcmp(buf, "wheel") == 0) 
				{
                    occurences++;
				}
			}
				
			return occurences;
		}
	}
	else 
	{
		int status;
		waitpid(rc1, &status, 0); // Wait specifically for child

        if (WIFEXITED(status)) 
        {
            printf("Found %d occurrences of 'wheel'\n", WEXITSTATUS(status));
        }
		
		
	}
}