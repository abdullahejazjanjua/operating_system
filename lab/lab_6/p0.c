#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char buf[1024];
    
    int fd = open("statements.txt", O_RDONLY);
    int bytes = read(fd, buf, 1024);
    
    buf[bytes] = '\0';
    printf("Data read: \n%s\n", buf);

    close(fd);
}
