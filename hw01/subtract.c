/*
【问题描述】
编写程序实现两个超长正整数（每个最长80位数字）的减法运算。
 
【输入形式】

从键盘读入两个整数，要考虑输入高位可能为0的情况（如00083）。
1. 第一行是超长正整数A；
2. 第二行是超长正整数B；
*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
#define input(i,f) scanf("%(#f)", &(i))
double eps = 1e-9;
int ans[100] = {0};
int lenA, lenB, len;
char A[100], B[100];
void skip_zero(char *s)
{
    char *d = s;
    while(*s == '0')
    {
        s++;
    }
    while(*s != '\0')
    {
        *d++ = *s++;
    }
    *d = '\0';
}
void mystrrev(char *s)
{
    int len = strlen(s);
    for(int i = 0; i < len / 2; i++)
    {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}
int my_compare(char *a, char *b)
{
    int lenA = strlen(a);
    int lenB = strlen(b);
    if(lenA > lenB)
    {
        return 1;
    }
    else if(lenA < lenB)
    {
        return -1;
    }
    else
    {
        for(int i = 0; i < lenA; i++)
        {
            if(a[i] > b[i])
            {
                return 1;
            }
            else if(a[i] < b[i])
            {
                return -1;
            }
        }
        return 0;
    }
}
int max(int a, int b)
{
    return a > b ? a : b;
}
void substract(char *A, char *B)
{
    for(int i = 0; i < len; i++)
    {
        int a = (i < lenA) ? A[i] - '0' : 0;
        int b = (i < lenB) ? B[i] - '0' : 0;
        ans[i] = (a - b);
        if(ans[i] < 0)
        {
            ans[i] += 10;
            int j = i + 1;
            while(A[j] == '0')
            {
                A[j] = '9';
                j++;
            }
            A[j]--;
        }
    }   
}
int ans_is_zero()
{
    for(int i = 0; i < len; i++)
    {
        if(ans[i] != 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    scanf("%s", A);
    scanf("%s", B);
    skip_zero(A);
    skip_zero(B);
    lenA = strlen(A);
    lenB = strlen(B);
    len = max(lenA, lenB);
    int exchanged = 0; // 记录是否交换！//! main函数内部变量要初始化！
    if(my_compare(A, B) < 0)//绝对值大减小。
    {
        exchanged = 1;
        char temp[100];
        strcpy(temp, A);
        strcpy(A, B);
        strcpy(B, temp);
        int temp_len = lenA;
        lenA = lenB;
        lenB = temp_len;
    }
    mystrrev(A);
    mystrrev(B);
    //判断符号！
    substract(A, B);
    if(ans_is_zero())
    {
        printf("0");
        return 0;
    }
    if(exchanged)
    {
        printf("-");
    }
    int i = len - 1;
    while(ans[i] == 0 && i > 0)
    {
        i--;
    }
    for( ; i >= 0; i--)
    {
        printf("%d", ans[i]);
    }
    return 0;
}