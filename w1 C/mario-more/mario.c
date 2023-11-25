#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("What's the height?\n");
    }
    while (height < 1 || height > 8);

    int row = 0;
    while (row < height)
    {
        // 第row行打height-row-1个空格;row=0,第一行打7个空格，所以<8-0-1
        for (int k = 0; k < height - row - 1; k++)
        {
            printf(" ");
        }
        // 第row行打row个#; row=0,第一行打1个空格，所以<0+1
        for (int j = 0; j < row + 1; j++)
        {
            printf("#");
        }
        // 每一行打2个空格
        printf("  ");
        // 尾巴第row行打row个#; row=0,第一行打1个空格，所以<0+1
        for (int j = 0; j < row + 1; j++)
        {
            printf("#");
        }
        // while每次都换行，同时row递增
        printf("\n");
        row++;
    }
}
// 第row行， height-row-1个空格+row个#+2个空格+row个#
// 平行关系下，不用阶级套娃，大家都是平等的。。。
