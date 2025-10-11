/*
 * Nothing happens when the program runs.
 * Leaks doesn't find anything. 
*/


#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *data = (int *) malloc(100 * sizeof(int));
    free(data);
    data[0] = 0;
     
}
