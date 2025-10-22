/*
    * extern keyword is used to declare a variable or a function whose definition is present in some other file.
    * Basically, it extends the visibility of the variables and functions in C to multiple source files.
 */
#include <stdio.h>

extern char **environ;

int main()
{
    char **tmp = environ;
    while(*tmp != NULL)
    {
        printf("%s\n", *tmp);
        tmp++;
    }
}
