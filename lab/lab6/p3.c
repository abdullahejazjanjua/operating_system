#include <stdio.h>

int main()
{
    FILE *f = fopen("test.txt", "a");
    fprintf(f, "\nI am writing to a file from fprintf");
}
