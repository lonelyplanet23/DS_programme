/*
要求：

1、上述所有输入的编辑操作中的字符串str都不包含空白字符（空格符、制表符或换行符）；

2、插入操作中的位置pos大于等于0，并且小于等于当前文本的字符个数；0位置表示文本第一个字符的位置；若pos为当前文本的字符个数，则表示在文本最后插入字符串；

3、删除操作中的位置pos大于等于0，并且小于当前文字的字符个数；

4、若已无操作可撤销，则再进行撤销操作无效；

5、文本在编辑过程中，总字符个数不会超过512。
*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 150
#define input(i,f) scanf("%(#f)", &(i))
double eps = 1e-9;
typedef struct operator
{
    int type;
    int pos;
    char str[200]; // 无空白字符
} op;
op stack[150];
char cur[550];
int top = -1;
void push(op op1)
{
    if(top == N)
    {
        printf("error!\n");
        return;
    }
    top++;
    stack[top] = op1;
    return ;
}
op pop()
{
    if(top < 0)
    {
        printf("error!\n");
        return;
    }
    op top1 = stack[top];
    top--;
    return top1;
}
void insert(int pos, char str[])
{
    int len_cur = strlen(cur);
    int len_str = strlen(str);

    if(pos < 0 || pos > len_cur)
    {
        printf("invalid!\n");
        return;
    }

    //!这部分理解掌握
     // 将 `cur` 中从 `pos` 开始的部分向后移动，为插入字符串腾出空间
    // 库函数 void *memmove(void *str1, const void *str2, size_t n) 从 str2 复制 n 个字符到 str1
    memmove(cur + pos + len_str, cur + pos, len_cur - pos + 1);
    
}
int main()
{
    fputs(cur,stdin);
    int n1;
    for(int i = 0; i < n1; i++)
    {
        op now;
        scanf("%d %d %s", &now.type, &now.pos, &now.str);
        push(now);
    }
    int num;
    scanf("%d", &num);
    while(num != -1)
    {

        scanf("%d", &num);
    }
    return 0;
}