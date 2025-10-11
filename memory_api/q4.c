/*
 * Nothing happens when the program runs
 * leaks utility only shows memory leak but doesn't complain about any illegal write operation.
 * Valgrind should show this
*/


#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *data = (int *) malloc(100 * sizeof(int));
    data[100] = 0; 
}
