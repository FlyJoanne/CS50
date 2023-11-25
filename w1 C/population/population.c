#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int n;
    do
    {
        n = get_int("Start Size:");
    }
    while (n < 9);
    // TODO: Prompt for end size
    int m;
    do
    {
        m = get_int("End Size:");
    }
    while (m < n);
    // TODO: Calculate number of years until we reach threshold
    // TODO: Print number of years
    if (m == n)
    {
        printf("Years: 0");
    }
    else
    {
        int year = 0;
        do
        {
            float b = n / 3;
            float c = n / 4;
            n = n + b - c;
            year++;
        }
        while (m > n);
        printf("Years: %i", year);
      }
}