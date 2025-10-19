#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char *buf = "My name is Khan and I am not a terrorist!\n";
    int fd = open("test.txt",  O_CREAT | O_WRONLY | O_TRUNC, 0644);
    int bytes = write(fd, buf, strlen(buf));
    printf("Total bytes written: %d\n", bytes);
}
