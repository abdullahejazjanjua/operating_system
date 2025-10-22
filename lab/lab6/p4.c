#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
    FILE *f = fopen("statements.txt", "r");
    if (f == NULL)
    {
        strerror(errno);
        return 1;
    }
    char buf[1024];
    // while(fscanf(f, "%[^\n]", buf) != EOF)
    // This will read the first sentence and leave \n in the input buffer
    // The file pointer is at position of \n
    // In next loop, the pattern doesn't match but it isnt EOF so what is stored in buf
    // is printed infintely.

    // This will read the \n but remove it from the input buffer
    while(fscanf(f, "%[^\n]%*c", buf) != EOF)
    {
        printf("%s\n", buf);
    }
}
