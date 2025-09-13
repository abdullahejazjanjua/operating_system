/*
 The output of this is:
    Hello, world before fork
    Hello, world after fork
    Hello, world after fork
huh? strange! or is it?

When we call fork(), an exact copy of the calling process is created. The only difference being is the values
of the PC, SP, FP but they are offsetted by the memory allocated to the new process but PC still points to the same
instruction and that is why second print statement is executed twice, once by each process.

Which process runs first, we never know.
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Hello, world before fork\n");
    fork();
    printf("Hello, world after fork\n");

    return 0;
}
