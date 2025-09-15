/*
  - We are closing the Standard output file.
  - Then we open a new file
  - Any printf call writes it to that new file and doesn't print it to the terminal.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    close(STDOUT_FILENO);
    open("p5.output", O_WRONLY | O_CREAT | O_TRUNC);
    printf("Hello, I am printing to the file");
    return 0;
}
