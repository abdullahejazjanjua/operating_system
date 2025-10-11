/*
 * The program aborts with error:
 *      q6.exe(89891,0x1f61520c0) malloc: *** error for object 0x120e04774: pointer being freed was not allocated
q6.exe(89891,0x1f61520c0) malloc: *** set a breakpoint in malloc_error_break to debug
[1]    89891 abort      ./q6.exe
*/



#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *data = (int *) malloc(100 * sizeof(int));
    data++;
    free(data++);
     
}
