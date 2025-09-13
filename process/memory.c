/*
 When run using:
    ./out.exe & ./out.exe
then, the counter is given same address:
    Process 23624 allocated counter address: 0x600000cc0000
    Process 23625 allocated counter address: 0x600002e8c000
but still they are incremented independently.
    counter: 0
    counter: 0
    counter: 1
    counter: 1
This makes it seem as each program has it's own memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int *counter = malloc(sizeof(int));
    assert(counter != NULL);
    printf("Process %d allocated counter address: %p\n", (int) getpid(), (void*) counter);

    *counter = 0;
    while(1)
    {
        sleep(1);
        printf("counter: %d\n", *counter);
        *counter = *counter + 1;
    }

    return 0;
}
