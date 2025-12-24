/*
 * Easy: Use execl() to replace the current process image with the date command located at /bin/date. 
 * Ensure you pass the correct arguments and a NULL terminator.
*/

#include <stdio.h>
#include <unistd.h>


int main()
{
	execl("/bin/date", "", NULL);
	printf("This shouldn't be executed\n");
}