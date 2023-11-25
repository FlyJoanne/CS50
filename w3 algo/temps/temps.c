// Practice working with structs
// Practice applying sorting algorithms
// 我做的是bubble sort

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void); // 没有输入和输出的函数，但是可以用return来stop

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities(); // 这就给做排序哈？

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++) // 但是这才打印排序
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(void)
{
    int swap = 19;
    while (swap != 0)
    {
        swap = 0;
        for (int i = 0; i < 10; i++)
        {
            if (temps[i].temp < temps[i + 1].temp)
            {
                int middle = temps[i].temp;
                temps[i].temp = temps[i + 1].temp;
                temps[i + 1].temp = middle;
                swap++;
            }
        }
    }
}
