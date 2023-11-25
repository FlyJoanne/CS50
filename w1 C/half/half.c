// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>
//给编译器的提示，表明这个函数在下面存在，括号里是这个函数的输入的类型和变量名称
float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// 定义函数;23行100.0可以达到(float)的效果
float half(float bill, float tax, int tip)
{
    float tax_amount = bill * (tax / 100);
    float total_1 = bill + tax_amount;
    float tip_amount = total_1 * (tip / 100.0);
    float total_2 = total_1 + tip_amount;
    float half = total_2 / 2;
    return half;
}
