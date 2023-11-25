#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt for input
    long number = get_long ("Number: "); //比如40..378
    int size = 0; //为了算卡号有几位
    int first_digit;
    int second_digit;
    int checksum = 0; // 验证卡号有效性
    long remain_digits = number;
    // 获取每一个digit
    while(remain_digits > 0) //40..378>0
    {
        int digit = remain_digits % 10; // 当前第一位8
        if(size > 0) // 空；while走到第二次时启动这个if循环，可以得到第二位是刚才的第一位8（一定要赶在first digit赋新值前复制过来）
        {
            second_digit = first_digit; //
        }
        first_digit = digit; // 将刚获得的8赋值给fd
        remain_digits = remain_digits / 10; // 迭代更新每次都删第一位

        // 算出checksum
        if (size % 2 == 0) // 偶数位数字0,2,4（从后往前数），直接加到checksum里
        {
            checksum += digit; // 比如说+8
        }
        else // 奇数位要分解成十位数字和个位数字分别加总
        {
            checksum += digit * 2 % 10 + digit * 2 / 10;  // 比如7*2=14执行后得到1+4=5加到checksum里
        }
        size++; //每循环一次，size递增，这样最后可以获得卡号位数
    }
    // 判断是不是有效卡号
    if (checksum % 10 != 0)
    {
        printf("INVALID\n");
        return 0; // 表示结束程序
    }
    // AMEX
    if (size == 15 && first_digit == 3 && (second_digit == 4||second_digit == 7))
    {
        printf("AMEX\n");
        return 0;
    }
    // MasterCard
    if (size == 16 && first_digit == 5 && (second_digit <= 5 && second_digit >= 1))
    {
        printf("MASTERCARD\n");
        return 0;
    }
    // Visa
    if ((size == 13 || size == 16) && first_digit == 4)
    {
        printf("VISA\n");
        return 0;
    }
    printf("INVALID\n"); // 4个if和这个是平行关系，不用再else了。。。
}
