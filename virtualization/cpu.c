/*
 This runs simultaneously
 ./out.exe "A" &; ./out.exe "B" &; ./out.exe "C"

 On a single core processor, the OS does "magic" and runs them simultaneously making
 it seem like that all the programs (processes) are runnnig simultaneously

 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: cpu <string>\n");
    }

    while(1)
    {
        sleep(1);
        printf("%s\n", argv[1]);
    }
    return 0;
}
