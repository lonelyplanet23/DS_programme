#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
struct function
{
    char name[22];
    char call[102][22];
    int sum;
} f[102];
typedef struct function func;
int top = -1;

void push(func i)
{
    if(top >= 102 - 1)
    {
        printf("error ");
        return;
    }
    f[++top] = i;
}
func pop()
{
    if(top <= -1)
    {
        printf("error ");
        return;        
    }
    func i = f[top];
    func p;
    f[top] = p;
    top--;
    return i;
}
int isempty()
{
    if(top == -1) return 1;
    return 0;
}
func top_is()
{
    if(top <= -1)
    {
        printf("error ");
        func p;
        return p;        
    }
    return f[top];
}
int main()
{
    do{
        int op;
        scanf("%d", &op);
        if(op == 0)
        {
            func poped = pop();
        }
        else if(op == 8)
        {
            func newfunc;
            scanf("%s", newfunc.name);
            memset(newfunc.call, 0, sizeof(newfunc.call));
            newfunc.sum = 0;
            if(!isempty())
            {
                //二维字符串数组不能直接赋值。
                if(bsearch(newfunc.name, f[top].call, f[top].sum, sizeof(f[top].call[0]), strcmp) == NULL)
                {
                    strcpy(f[top].call[f[top].sum++], newfunc.name);
                }
            }
            push(newfunc);
        }
    }while(!isempty());
    return 0;
}