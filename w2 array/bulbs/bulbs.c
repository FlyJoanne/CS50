#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
// 一定要区分除以后的得到的整数和余数

const int BITS_IN_BYTE = 8; // 固定表示为8bits的二进制数

void print_bulb(int bit); //对每一bit转换成图形

int main(void)
{
    string text = get_string("Message: ");
    for (int i = 0, n = strlen(text); i < n; i++) //每一个字母
    {
        int a = text[i];                       //字母对应的ASCII编号数字 比如72
        for (int b = BITS_IN_BYTE; b > 0; b--) // 要把数字转换成8bit二进制 最左边的一位是数字/2的8次方的余数
        {
            int c = pow(2, b - 1);
            int d = a / c;
            int e = d % 2; // 72除以2^6时得1，1除以2余数为1，所以72二进制以1作为第二位数
            print_bulb(e); // 把每个bit转换成图形
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
