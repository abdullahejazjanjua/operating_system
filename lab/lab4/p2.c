#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

int main()
{
    // 1D allocation
    int *a = (int *) malloc(ARRAY_SIZE * sizeof(int));
    if (a == NULL)
    {
        fprintf(stderr, "Array was not allocated\n");
        return 1;
    }

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("a[%d]: %d\n", i, a[i]);
    }

    //2D allocation
    int **b = (int **) malloc(ARRAY_SIZE * sizeof(int*));
    if (b == NULL)
    {
        fprintf(stderr, "Array was not allocated\n");
        return 1;
    }
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        b[i] = (int *) malloc(ARRAY_SIZE * sizeof(int));
        if (b[i] == NULL)
        {
            fprintf(stderr, "Array was not allocated\n");
            return 1;
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        for(int j = 0; j < ARRAY_SIZE; j++)
        {
            printf("b[%d][%d] = %d\n", i, j, b[i][j]);
        }
    }

    // Freeing memory
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        free(b[i]);
    }
    free(b);
    free(a);

}
