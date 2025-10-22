#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
    FILE *f = fopen("test.txt", "r");
    if (f == NULL)
    {
        perror("fopen");
        printf("%s\n", strerror(errno));
        return 1;
    }
    return 0;
}
