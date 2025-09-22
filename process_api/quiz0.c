#include <stdio.h>
#include <unistd.h>

int main()
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        count++;
        fork();
    }

    printf("count: %d\n", count);
}


/*                   (count = 3)
                      Parent
     /                   |                 \
  child                 child             child
  (count = 3           (count = 3         (count = 3
  i = 1)                i = 2)             i = 3)
/            \            |
child       child        (count = 3
(count = 3  (count = 3    i = 3)
i = 2)       i = 3)
  |
child
(count = 3
i = 3)

 */
