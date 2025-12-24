#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXCHILD 5


int main()
{
	int rc;
	
	for(int i = 0; i < MAXCHILD; i++)
	{
		if((rc = fork()) == 0)
		{
			printf("Yo, Baby\n");
			return 0;
		}
		else
		{
			// printf("Ok, I'mma keep going\n");
		}
	}
}