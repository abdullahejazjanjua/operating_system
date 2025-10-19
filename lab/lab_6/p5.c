#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
    FILE *f = fopen("data.csv", "r");
    if (f == NULL)
    {
        strerror(errno);
        return 1;
    }
    char name[1024], country[1024], ch;
    char age[1024];
    
    while((ch = fgetc(f)) != '\n' && ch != EOF)
    {
        continue;
    }
    while(fscanf(f, "%[^,],%[^,],%[^\n]%*c", name, age, country) != EOF) 
    {
        printf("%s, %s, %s\n", name, age, country);
    }
}
