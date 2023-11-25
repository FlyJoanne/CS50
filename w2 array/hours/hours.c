#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output); // AT也是这个函数的输入变量

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
// 也可以定义函数时先不用weeks这些名字的，比如定义y=x+1,实际算的时候比如是拿2去算2+1
float calc_hours(int hours[], int weeks, char output)
{
    int sum = 0;
    for (int i = 0; i < weeks; i++)
    {
        sum += hours[i];
    }
    if (output == 'A')
    {
        return sum / (float) weeks;
    }
    return sum;
}