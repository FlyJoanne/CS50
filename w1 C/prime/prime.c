#include <cs50.h>
#include <stdio.h>
//布林函数，叫prime，输入值是整数number
bool prime(int number);
//当min<1时，不行，所以要在再要一遍数字；max同理
int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);
    //整数i=min；判断i小于等于max嘛？是的话，判断是不是质数是的话打印，i+1，然后继续循环
    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}
//定义布林函数
bool prime(int number)
{
    for (int j = 2; j < number || number == 1; j++)
    {
        if (number % j == 0)
            return false;
    }
    return true;
}
//布林函数作用：判断一个number是不是素数，什么时候会return false?某个数字分解因子n>2
//判断分解因子个数？当除以2至number-1时，余数有为0的，就不是素数
// for (int j = 2 ; j < number , j++) 对除数的循环，获得除数2至number-1
