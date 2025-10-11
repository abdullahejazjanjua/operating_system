/*
 * I get a segmentation fault
*/



#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *ptr = NULL;
    printf("Dereferencing ptr: %d", *ptr);
}
