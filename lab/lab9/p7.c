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



#define NTHREADS 10
#define BUFSIZE 1024

typedef struct args_t
{
	char buf[BUFSIZE];
	int buf_size;
	char target;
} args_t;

typedef struct ret_t
{
	int occurences;
} ret_t;


void* search_file(void *args)
{
	args_t arg = *(args_t*) args;
	ret_t *result = (ret_t*) malloc(sizeof(ret_t));
	result->occurences = 0;
	
	for (int i = 0; i < arg.buf_size; i++)
	{
		if(arg.buf[i] == arg.target)
		{
			result->occurences++;
		}
	}

	return (void *) result;
}

int main()
{
	int total_occurences = 0, fd,  end_of_file = 0;
	char filename[] = "file.txt";
	
	pthread_t tid[NTHREADS];

	fd = open(filename, O_RDONLY);
	while(end_of_file != 1)
	{
		int threads_created = 0;
		for (int i = 0; i < NTHREADS; i++)
		{
			args_t *args = (args_t*) malloc(sizeof(args_t));;
			int nbytes = read(fd, args->buf, BUFSIZE);
	
			if (nbytes > 0)
			{
				args->buf[nbytes] = '\0';
				args->buf_size = nbytes;
				args->target = 'r';
				threads_created++;
				pthread_create(&tid[i], NULL, search_file, (void *) args);
			}
			else
			{
				free(args);
				end_of_file = 1;
				break;
			}
		}
		for (int i = 0; i < threads_created; i++)
		{
			ret_t *ret;
			pthread_join(tid[i], (void **) &ret);
			total_occurences += ret->occurences;
			
			free(ret);
		}
	}
	printf("The total occurence was found to be: %d\n", total_occurences);
	
	printf("Done\n");
}