#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    if (argc == 2 && only_digits(argv[1]))
    {
        int key = atoi(argv[1]); // 把输入的数字key真正变成数字
        string plaintext = get_string("plaintext:  ");
        printf("ciphertext: ");
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            printf("%c", rotate(plaintext[i], key));
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        char c = s[i];
        if (isdigit(c) == false)
        {
            return false;
        }
    }
    return true;
}

// 97-122 a-z 65-90 A-Z
char rotate(char c, int n)
{
    int k = n % 26; // 13
    if (islower(c))
    {
        int m1 = c - 97;    // t对应116-97=29
        int m2 = m1 + k;    // 42
        int m3 = m2 % 26;   // 防止溢出ASCII范围      16
        char end = m3 + 97; // 139 让它回到字母103. 103
        return end;
    }
    else if (isupper(c))
    {
        int m1 = c - 65;
        int m2 = m1 + k;
        int m3 = m2 % 26;
        char end = m2 + 65;
        return end;
    }
    else
    {
        return c;
    }
}