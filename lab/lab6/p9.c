#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./p9.exe file_name.txt");
        return 1;
    }
    char buf[1024];
    int fd = open(argv[1], O_RDONLY);
    int sz = read(fd, buf, 1024);
    if (sz < 0)
    {
        perror("read");
        return 1;
    }
    buf[sz] = '\0';

    int words = 0, lines = 0, chars = 0;
    for(int i = 0; i < sz; i++)
    {
        chars++; // space is also a character
        if(isspace(buf[i]))
        {
            words++;
        }
        if(buf[i] == '\n')
        {
            lines++;
        }
    }

    printf("lines: %d, words: %d, chars: %d\n", lines, words, chars - lines);

}
