#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
#define MAXSIZE 1001
#define RIGHT ')'
double eps = 1e-9;
char opstack[101];
char RPN[101];
float stack[101];
int top1 = -1;
int top2 = -1;
int top3 = -1;
void push(char i, char stack[], int* top)
{
    if(*top >= MAXSIZE - 1)
    {
        printf("error ");
        return;
    }
    stack[++(*top)] = i; //!注意
}
void push_float(float i, float stack[], int* top)
{
    if(*top >= MAXSIZE - 1)
    {
        printf("error ");
        return;
    }
    stack[++(*top)] = i; //!注意
}
char pop(char stack[], int *top)
{
    if(*top <= -1)
    {
        printf("error ");
        return '\0';        
    }
    char ch = stack[*top];
    stack[*top] = 0; //清空栈顶元素
    (*top)--;
    return ch;
}
float pop_float(float stack[], int *top)
{
    if(*top <= -1)
    {
        printf("error ");
        return 0;        
    }
    float ch = stack[*top];
    stack[*top] = 0; //清空栈顶元素
    (*top)--;
    return ch;
}
char top_is(char stack[], int *top)
{
    if(*top == -1) return ' ';
    return stack[*top];
}
int isempty(char stack[], int *top)
{
    return (*top == -1);
}
int isop(char i)
{
    return (i == '+') || (i == '-') || (i == '*') || (i == '/') || (i == '(');
}
int precedence(char i)
{
    if(i == '(') return 3;
    if(i == '+' || i == '-') return 1;
    if(i == '*' || i == '/') return 2;
    return 0;
}
void infix_to_suffix()
{
    char str[1001];
    fgets(str, sizeof(str), stdin);
    //! 非的循环出口，用&&连接
    for(int i = 0; str[i] != '\0' && str[i] != '='; i++)
    {
        if(isdigit(str[i]))//!缺少多位数字
        {
            while (isdigit(str[i]))
            {
                push(str[i], RPN, &top2);
                i++;
            }
            push(' ', RPN, &top2); // 用空格分隔数字
            i--; // 回退一位，因为外层循环会自增
            continue;
        }
        if(isop(str[i]))
        {
            if(isempty(opstack, &top1)) push(str[i], opstack, &top1);
            else
            {
                char op = top_is(opstack, &top1);//!左括号需要单独处理
                //! 注意是直到遇到优先级小的再跳出来
                while(precedence(op) >= precedence(str[i]) && op != '(')
                {
                    push(pop(opstack, &top1), RPN, &top2);
                    op = top_is(opstack, &top1);
                }
                push(str[i], opstack, &top1);
            }
            continue;
        }
        if(str[i] == ')')
        {
            if (isempty(opstack, &top1))
            {
                printf("no ( \n");
                return;
            }
            char op = pop(opstack, &top1);
            while(op != '(')
            {
                push(op, RPN, &top2);
                if (isempty(opstack, &top1))
                {
                    printf("no (\n");
                    return;
                }
                op = pop(opstack, &top1);
            }
        }
    }
    while(top1 >= 0)
    {
        push(pop(opstack, &top1), RPN, &top2);
    }
    // printf("suffix: ");
    // for (int i = 0; i <= top2; i++)
    // {
    //     printf("%c", RPN[i]);
    // }
    // printf("\n");
}
void suffix_exp()
{
    for(int i = 0; i <= top2; i++)
    {
        if(isdigit(RPN[i]))
        {
            float num = 0;
            while(isdigit(RPN[i]))
            {
                num = num * 10.0 + (RPN[i] - '0') * 1.0;
                i++;
            }
            push_float(num, stack, &top3);
            i--; // 回退一位，因为外层循环会自增
            continue;
        }
        if(isop(RPN[i]))
        {
            float b = pop_float(stack, &top3);
            float a = pop_float(stack, &top3); // 后弹出的是左操作数
            float result;
            switch(RPN[i])
            {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }
            push_float(result, stack, &top3);
        }
    }
    printf("%.2f\n", pop_float(stack, &top3));
}
int main()
{
    infix_to_suffix();
    suffix_exp();
    return 0;
}