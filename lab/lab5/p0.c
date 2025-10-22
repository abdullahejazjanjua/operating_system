/*
    *  argv is an array of pointers pointing to the address of a null-terminated string.
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./file.exe number\n");
        return 1;
    }

    printf("Number in cmd arg: %s\n", argv[1]);
    return 0;
}
