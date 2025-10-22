#include <stdio.h>
#include <unistd.h>

int main()
{
    char buffer[20];
    int count = 0;

    int sz = read(STDIN_FILENO, buffer, 20);
    if (sz == -1)
    {
        perror("read");
        return 1;
    }
    buffer[sz + 1] = '\0';
    for(int i = 0; i <= sz; i++)
    {
        if(buffer[i] == 'a' || buffer[i] == 'e' || buffer[i] == 'i' || buffer[i] == 'o' || buffer[i] == 'u')
        {
            count++;
        }
    }
    printf("Total vowels found: %d\n", count);

}
