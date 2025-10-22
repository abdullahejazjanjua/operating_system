#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *name;
    int age;
} Person;


int main()
{
    Person p = {"John Doe", 15};
    printf("Name: %s\n", p.name);
    printf("Age: %d\n\n", p.age);

    Person *p2;
    p2->name = "Jane Doe";
    p2->age = 19;

    printf("Name: %s\n", p2->name);
    printf("Age: %d\n", p2->age);

}
