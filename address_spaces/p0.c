#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 10;
    // All the addresses printed here are virtual addresses
    printf("The address of code segment: %p\n", main);
    printf("The address of heap: %p\n",  malloc(100e6));
    printf("The address of stack: %p\n", &x);
}
