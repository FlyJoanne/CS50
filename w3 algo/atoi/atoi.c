#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int length = strlen(input);
    if (length == 1) // base case
    {
        return (input[0] - 48);
    }
    else
    {
        int last = input[length - 1] - 48;   // 0-9：ASCII里编号48-57
        input[length - 1] = '\0';            // 相当于cut掉了最后一位，记得用单引号
        return (10 * convert(input) + last); // recursive case
    }
}