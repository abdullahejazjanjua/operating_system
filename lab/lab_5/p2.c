#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
    int x = 1/0;
    perror("Invalid Ops");
    char *err = strerror(errno);
    printf("%s\n", err);
    return 0;
}
