// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch
// 要点：if (argc!=2)要报错1；string replace(string word/argv[1])；用switch
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string replace(string input); // 这里不要直接string argv[1]....

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
    printf("%s\n", replace(argv[1]));
    return 0;
}

string replace(string input)
{
    string output = input; // 后面output会变成改写了的单词，input是原来的；替换的题尽量用新变量+旧变量
    int length = strlen(input);
    for (int i = 0; i < length; i++) // 单个字母一个个来判断
    {
        char c = input[i];
        switch (c)
        {
            case 'a': // 字符串内容一定要加单引号
                output[i] = '6';
                break;
            case 'e':
                output[i] = '3';
                break;
            case 'i':
                output[i] = '1';
                break;
            case 'o':
                output[i] = '0';
                break;
            default:
                output[i] = input[i];
                break;
        }
    }
    return output;
}