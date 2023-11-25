#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);// text自然而然就是一个字符串 不用强调的
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string para = get_string("Text: ");
    float L = (float) count_letters(para) / (float) count_words(para) * 100.00;
    float S = (float) count_sentences(para) / (float) count_words(para) * 100.00;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int l = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            l++;
        }
    }
    return l;
}

int count_words(string text)
{
    int w = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            w++;
        }
    }
    return w + 1;
}

int count_sentences(string text)
{
    int s = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            s++;
        }
    }
    return s;
}