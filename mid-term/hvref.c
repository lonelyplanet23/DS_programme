#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define N 100001
#define Deint(x) printf(#x" = %d\n", x)
#define Destr(x) printf(#x" = %s\n", x)
#define Dechar(x) printf(#x" = %c\n", x)
#define De printf("debug\n")
#define loop(l,r) for(int i = l; i <= r; i++)
int atoi(const char *str)
{
    int i, n = 0, sign;
    char *p = str;
    // skip white space
    while(*p == ' ' || *p == '\t' || *p == '\n')
        p++;
    // get sign
    sign = 1;
    if(*p == '-')
    {
        sign = -1;
        p++;
    }
    // get number
    while(*p != '\0' && *p >= '0' && *p <= '9')
    {
        n = n * 10 + *p - '0';
        p++;
    }
    return sign * n;
}
struct Node
{
    char author[32];
    int year;
} list[101];
int cnt = 0;
typedef struct Node node;
int is_same(node p, node q)
{
    return(strcmp(p.author, q.author) == 0 && (p.year == q.year));
}
void insert(node p)
{
    for(int i = 0; i < cnt; i++)
    {
        if(is_same(p, list[i]))
        {
            return ;
        }
    }
    list[cnt++] = p;
}
void search(char str[])
{
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] == '(')
        {
            node p;
            memset(p.author, 0, sizeof(p.author));
            int t = 0;
            i++; //跳过左括号
            while(str[i] != ',')//复制作者名
            {
                p.author[t++] = str[i++];
            }
            i += 1;//跳过逗号
            p.year = atoi(str + i);//读取年份
            insert(p);
        }
    }
}
void print()
{
    for(int i = 0; i < cnt; i++)
    {
        printf("%s %d\n", list[i].author, list[i].year);
    }
}
int main()
{
    char passage[10002];
    fgets(passage, sizeof(passage), stdin);
    search(passage);
    print();
    return 0;
}