#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
#define MAXSIZE 100
double eps = 1e-9;
int stack[101];
int top = -1;
void push(int i)
{
    if(top >= MAXSIZE - 1)
    {
        printf("error ");
        return;
    }
    stack[++top] = i;
}
void pop()
{
    if(top <= -1)
    {
        printf("error ");
        return;        
    }
    printf("%d ", stack[top]);
    stack[top] = 0;
    top--;
}
int main()
{
    int op;
    scanf("%d", &op);
    while(op != -1)
    {
        int num;
        if(op == 1)
        {
            scanf("%d", &num);
            push(num);
        }
        else if(op == 0)
        {
            pop();
        }
        scanf("%d", &op);
    }
    return 0;
}