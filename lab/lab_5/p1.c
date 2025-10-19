#include <stdio.h>

extern char **environ; // extern tells the compiler that he will find 
                       // definition from another place.

int main()
{
    char **tmp = environ;
    while(*tmp != NULL)
    {
        printf("%s\n", *tmp);
        tmp++;
    }
}
