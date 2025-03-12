// 题目要求：以科学计数法形式输出数据。
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
double eps = 1e-9;
//拆解：指数：头部0的个数，（除去个位的0）底数：大小介于1-10之间。
int main()
{
    char input[1000];
    scanf("%s", input);
    int len = strlen(input);
    int base = 0;
    int exp = 0;
    if(input[0] == '0') //情况1：这个数小于1
    {
        char *p = input;
        while(*p == '0'|| *p == '.')
        {
            if(*p == '0')
            {
                base++;
            }
            p++;
        }
        printf("%c", *p);
        p++;
        if(*p != '\0')
        {
            printf(".");
            while(*p != '\0')
            {
                printf("%c", *p);
                p++;
            }
        }
        printf("e-%d", base);
    }
    else
    {
        char *p = input;
        while(*(p+1) != '\0' && *(p+1) != '.')
        {
            base++;
            p++;
        }
        printf("%c.", *input);
        for(int i = 1; i < len; i++)
        {
            if(input[i] != '.')
            {
                printf("%c", input[i]);
            }
        }
        printf("e%d", base);
    }
    
    return 0;
}