#include <stdio.h>



int main()
{
    FILE *f = fopen("statements.txt", "r");
    if (f == NULL)
    {
        fprintf(stderr, "File not found\n");
        return 1;
    }
    char buf[1024];

    printf("Doing read 1:\n");
    while(fscanf(f, "%[^\n]%*c", buf) != EOF)
    {
        printf("%s\n", buf);
    } // now file pointer is at EOF

    printf("Doing read 2:\n");
    while(fscanf(f, "%[^\n]%*c", buf) != EOF)
    {
        printf("%s\n", buf);
    }

    fseek(f, 0, SEEK_SET); // Now, f is at start of the file
    printf("Doing read 3:\n");
    while(fscanf(f, "%[^\n]%*c", buf) != EOF)
    {
        printf("%s\n", buf);
    } // now again file pointer is at EOF


}
