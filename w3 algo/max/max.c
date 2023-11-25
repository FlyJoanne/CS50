// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: "); // 问客户想让数列有几个数字
    }
    while (n < 1);

    int arr[n]; // 好的那么我们这个数列就是有n个数字

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i); //输啊请输
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    int max = array[0];
    for (int i = 0; i < n; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}
