/*
 * leaks utility on mac tells me there is a leak of 16 bytes in my main:
        * leaks Report Version: 4.0, multi-line stacks                                                        Process 88631: 188 nodes malloced for 14 KB
          Process 88631: 1 leak for 16 total leaked bytes.
                                                                                                    STACK OF 1 INSTANCE OF 'ROOT LEAK: <malloc in main>':
          2   dyld                                  0x187e1eb98 start + 6076
          1   q3.exe                                0x102308480 main + 32  q3.c:6
          0   libsystem_malloc.dylib                0x187ff1080 _malloc_zone_malloc_instrumented_or_legacy + 152
          ====
          1 (16 bytes) ROOT LEAK: <malloc in main 0x13d7040f0> [16]

   * lldb doesn't tell me anything
   * The program runs fine
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *ptr = (int *) malloc(sizeof(int));
    printf("The address of allocated space: %p", ptr);

    return 0;
}
