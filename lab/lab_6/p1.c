#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char *buf = "Hello from write sys call\n";
    int bytes = write(2, buf, strlen(buf));
    printf("Total bytes written: %d\n", bytes);
}
