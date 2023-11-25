// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library
// 请分清bool函数和bool variable
#include <cs50.h>
#include <ctype.h>  // islower这些要用到
#include <stdio.h>
#include <string.h> // strlen要用到

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password)) // 就是说这个布林函数valid返回值是true
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool up = false, low = false, num = false, sym = false;

    for (int i = 0, n = strlen(password); i < n; i++)
    {
        if (up == false)
        {
            up = isupper(password[i]); // up will become true if isupper returns non 0
        }                              // 有大写字母的话用一次这个函数就够了，不用再测还有没有别的
        if (low == false)
        {
            low = islower(password[i]);
        }
        if (num == false)
        {
            num = isdigit(password[i]);
        }
        // isalnum这个函数如果不是数字（也就是你是符号）返回0，但我们希望如果是符号返回1所以加个!
        if (sym == false)
        {
            sym = !(isalnum(password[i]));
        }
    }
    if (up == true && low == true && num == true && sym == true)
    {
        return true;
    }
    return false;
}
