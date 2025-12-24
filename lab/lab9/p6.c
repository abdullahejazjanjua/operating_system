/*
 * Write a program where the main thread passes a struct containing a filename and a target character to a 
 * worker thread. The worker thread should count occurrences of that character in the file and return the 
 * count via pthread_exit()
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>



#define MAXLEN 256

typedef struct args_t
{
	char filename[MAXLEN];
	char target;
} args_t;

typedef struct ret_t
{
	int occurences;
} ret_t;



void* search_file(void *args)
{
	args_t arg = *(args_t*) args;
	char buf;
	int nbytes, fd;
	ret_t *result = (ret_t*) malloc(sizeof(ret_t));
	result->occurences = 0;
	
	fd = open(arg.filename, O_RDONLY);
	
	while((nbytes = read(fd, &buf, 1)) != 0)
	{
		if (buf == arg.target)
		{
			result->occurences++;
		}
	}
	
	return (void *) result;
}

int main()
{
	pthread_t tid;
	ret_t *ret;
	args_t args = {"file.txt", 'r'};
	
	
	pthread_create(&tid, NULL, search_file, (void *) &args);
	pthread_join(tid, (void **) &ret);
	
	printf("The total occurence was found to be: %d\n", ret->occurences);
	
	printf("Done\n");
}