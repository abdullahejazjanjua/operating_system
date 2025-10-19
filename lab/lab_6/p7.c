#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

#define BUFF_SIZE 100
#define SIZE 10000

typedef struct 
{
    char name[BUFF_SIZE];
    double temp;
} city;

city *sort(city *city_stat);
void print_city(city city_stat);

int main()
{
    FILE *f = fopen("weather_stations_ttrc.csv", "r");
    if (f == NULL)
    {
        fprintf(stderr, "File not found\n");
        return 1;
    }
    city *city_stat = malloc(SIZE * sizeof(city));

    char city_name[BUFF_SIZE], temp[BUFF_SIZE];

    int i = 0;
    while(fscanf(f, "%[^;];%[^\n]%*c", city_name, temp) != EOF)
    {
        strcpy(city_stat[i].name, city_name);
        city_stat[i].temp = atof(temp);
        i++;
    }

    city_stat = sort(city_stat);
    printf("Minimum:\n");
    print_city(city_stat[0]);

    printf("Maxmum:\n");
    print_city(city_stat[SIZE - 1]);

    printf("Medium:\n");
    print_city(city_stat[SIZE / 2]);

}


city *sort(city *city_stat) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE - i - 1; j++) 
        {
            if (city_stat[j].temp > city_stat[j + 1].temp) 
            {
                city tmp = city_stat[j];
                city_stat[j] = city_stat[j + 1];
                city_stat[j + 1] = tmp;
            }
        }
    }
    return city_stat;
}

void print_city(city city_stat)
{
    printf("Name: %s\n", city_stat.name);
    printf("Temperature: %f\n", city_stat.temp);
    printf("\n"); 
    return;
}
