//从标准输入中读入一个整数算术运算表达式，如5 - 1 * 2 * 3 + 12 / 2 / 2  = 。计算表达式结果，并输出。
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
double eps = 1e-9;
void delete_space(char *s)
{
    char *d = s;
    while (*s != '\0')
    {
        if (*s != ' ')
        {
            *d++ = *s;//这里本质上，就通过地址修改了原来的字符串。
            //s比d快，所以不会出现覆盖的情况。
        }
        s++;
    }
    *d = '\0';
}

int main()
{
    char input[1000];
    gets(input);
    delete_space(input);
    int len = strlen(input);
    int ans = 0;
    char *p = input;
    while (*p != '\0' && *p != '=' && *p >= '0' && *p <= '9')
    {
        ans = ans * 10 + *p - '0';
        p++;
    }
    while (*p != '=')
    {
        if (*p == '+' || *p == '-')
        {
            int part1 = 0; //part1是所有这个加减号到下一个加减号之间的结果。
            char op1 = *p;
            p++;
            while (*p != '\0' && *p >= '0' && *p <= '9'&& *p != '=')
            {
                part1 = part1 * 10 + *p - '0';
                p++;
            }
            while(*p != '\0' && *p != '+' && *p != '-' && *p != '=')
            {
                char op = *p;
                p++;
                int num = 0;
                int flag = 0;
                while (*p != '\0' && *p >= '0' && *p <= '9'&& *p != '=')
                {
                    num = num * 10 + *p - '0';
                    p++;
                    flag = 1;
                }
                if(!flag) num = 1;
                if(op == '*')
                {
                    part1 *= num;
                }
                else if(op == '/')
                {
                    part1 /= num;
                }
            }
            if(op1 == '+') ans += part1;
            else if(op1 == '-') ans -= part1;
        }
        else if(*p == '*' || *p == '/')
        {
            while(*p != '\0' && *p != '+' && *p != '-' && *p != '=')
            {
                char op = *p;
                p++;
                int num = 0;
                while (*p != '\0' && *p >= '0' && *p <= '9'&& *p != '=')
                {
                    num = num * 10 + *p - '0';
                    p++;
                }
                if(op == '*')
                {
                    ans *= num;
                }
                else if(op == '/')
                {
                    ans /= num;
                }
            }
        }
    }
    printf("%d", ans);
    return 0;
}