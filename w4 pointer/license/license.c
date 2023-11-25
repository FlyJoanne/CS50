#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into 车牌号是单字符六位，加一位给\0
    char buffer[7];

    // Create array to store plate numbers 8个车牌号
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL) // 如果没有这个文件。。。指针==NULL
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    int idx = 0;
    while (fread(buffer, 1, 7, infile) == 7)
    {
        // change from '\n' to '\0'
        buffer[6] = '\0';
        plates[idx] = malloc(7 * sizeof(char));
        strcpy(plates[idx], buffer);
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }

    for (int i = 0; i < 8; i++)
    {
        free(plates[i]);
    }

    fclose(infile);
}

// the original code is:
// while(fread(buffer,1,7,infile) == 7)
// {buffer[6]='\0';
//  plates[idx]=buffer;
//  idx++}
// char buffer[7]本身是一个array，所以也是pointer，它一直指向自己的第一个元素，也就是array[0]，也就是说buffer的value是第一个元素的地址
// 因为plates[idx]=buffer，所以plates[idx]的value也是第一个元素的地址。
// 第一个元素的地址是一直不变的！只是第一个元素存储的内容在变。
// plates[0]到[7]都是相等的，它们的value全都是第一个元素的地址。最后之所以打印出来车牌号，是因为printf用了%s。。。
// The key point here is that plates[idx] = buffer; is storing a memory address, not the actual data in buffer.
// To store the data, you need to allocate new memory for each plates[idx] and copy the data from buffer into it.