#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
#define MAXSIZE 101
double eps = 1e-9;

//操作符栈，便于后缀转前缀
char opstack[101];
char RPN[101];
int optop = -1;

//结点结构体
struct node
{
    int type; // 0:数字，1:操作符
    int value; // 数字值
    char op; // 操作符值
    struct node *lchild, *rchild;
};
typedef struct node* nodeptr;
//实现表达式树的栈
nodeptr stack[101];
int top = -1;
//!不要混淆两个top

//栈操作函数的声明，实现在后面
void push(nodeptr i);
nodeptr pop();
void push_op(char i);
char pop_op();
int isempty()
{
    return top == -1;
}

//后缀表达式转前缀表达式的几个函数
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
// 便于sprintf 函数拼接，尝试一下 
int rpn_index = 0;
void infix_to_suffix();

nodeptr Create_exp_tree()
{
    //读入一个符号：
    char *p = RPN;
    nodeptr root = NULL;
    for(; *p != '\0' && *p != '='; p++)
    {
        //数字：创建结点
        if(isdigit(*p))
        {
            int num = *p - '0';
            for(p++; isdigit(*p); p++)
            {
                num = num * 10 + (*p - '0');
            }
            p--; //! 回退一位，因为外层循环会自增
            nodeptr new_node = (nodeptr)malloc(sizeof(struct node));
            new_node->type = 0;
            new_node->value =  num;
            new_node->lchild = NULL;
            new_node->rchild = NULL;
            push(new_node);
            continue;
        }
        //操作符：创建结点
        //弹出指向两棵树T1和T2的指针（T1先弹出）并形成一棵新树
        //!左、右子树分别指向T2和T1(先弹右，后弹左)
        if(isop(*p))
        {
            nodeptr new_node = (nodeptr)malloc(sizeof(struct node));
            new_node->type = 1;
            new_node->op = *p;
            new_node->rchild = pop();
            new_node->lchild = pop();
            push(new_node);
        }
    }
    //为什么表达式只会剩一个结点
    //因为每次弹出两个结点，形成一个新结点
    //最后只剩下一个结点，就是根结点
    root = pop();
    return root;
}
int cal(nodeptr root)
{
    //递归实现
    //后序遍历
    if(root == NULL) return 0;
    if(root->type == 0) return root->value; //数字
    //操作符
    int l = cal(root->lchild);
    int r = cal(root->rchild);
    switch(root->op)
    {
        case '+': return l + r;
        case '-': return l - r;
        case '*': return l * r;
        case '/': return l / r;
    }
    return 0;
}
int main()
{
    infix_to_suffix();
    //printf("suffix: %s\n", RPN);
    nodeptr root = Create_exp_tree();
    //首先在屏幕上输出表达式树根、左子节点及右子节点上的运算符或操作数，
    //中间由一个空格分隔，最后有一个回车（如果无某节点，则该项不输出）
    if(root != NULL)
    {
        if(root->type == 0)
        {
            printf("%d", root->value);
        }
        else
        {
            printf("%c", root->op);
        }
        if(root->lchild != NULL)
        {
            if(root->lchild->type == 0)
            {
                printf(" %d", root->lchild->value);
            }
            else
            {
                printf(" %c", root->lchild->op);
            }
        }
        if(root->rchild != NULL)
        {
            if(root->rchild->type == 0)
            {
                printf(" %d", root->rchild->value);
            }
            else
            {
                printf(" %c", root->rchild->op);
            }
        }
    }
    else
    {
        printf("error: empty tree\n");
    }
    printf("\n");
    printf("%d", cal(root));
    return 0;
}

//* 以下为栈操作函数
void push(nodeptr i)
{
    if(top >= MAXSIZE - 1)
    {
        printf("error push(nodeptr i)\n");
        return;
    }
    stack[++top] = i; 
}
nodeptr pop()
{
    if(top <= -1)
    {
        printf("error nodeptr pop()\n");
        return NULL;        
    }
    nodeptr ch = stack[top];
    stack[top] = NULL; //清空栈顶元素
    top--;
    return ch;
}
void push_op(char i)
{
    if(optop >= MAXSIZE - 1)
    {
        printf("error push_op(char i)\n");
        return;
    }
    opstack[++optop] = i; 
}
char pop_op()
{
    if(optop <= -1)
    {
        printf("error char pop_op()\n");
        return '\0';        
    }
    char ch = opstack[optop];
    opstack[optop] = 0; //清空栈顶元素
    optop--;
    return ch;
}
void infix_to_suffix()
{
    char exp[1001];
    fgets(exp, sizeof(exp), stdin);
    //换用指针来遍历表达式
    char *p = exp;
    for(; *p !='\0' && *p != '='; p++)
    {
        //数字：输出
        if(isdigit(*p))
        {
            while (isdigit(*p))
            {
                rpn_index += sprintf(RPN + rpn_index, "%c", *p);
                p++;
            }
            rpn_index += sprintf(RPN + rpn_index, " "); // 用空格分隔数字
            p--; // 回退一位，因为外层循环会自增
            continue;
        }
        //除右括号以外的操作符
        if(isop(*p))
        {
            //栈为空
            if(optop <= -1) 
            {
                push_op(*p);
                continue;
            }
            char top_op = opstack[optop];
            //! 注意是直到遇到优先级小的或者左括号再跳出来
            while(precedence(top_op) >= precedence(*p) && top_op != '(')
            {
                //输出弹出来的符号
                rpn_index += sprintf(RPN + rpn_index, "%c ", top_op);
                pop_op();
                top_op = opstack[optop];
            }
            //!将当前操作符压入栈
            push_op(*p);
            continue;
        }
        //右括号，把左括号前的所有符号弹出输出
        if(*p == ')')
        {
            char op = pop_op();
            while(op != '\0' && op != '(')
            {
                rpn_index += sprintf(RPN + rpn_index, "%c ", op);
                op = pop_op();
            }
        }
    }
    //将剩余的操作符弹出输出
    while(optop >= 0)
    {
        rpn_index += sprintf(RPN + rpn_index, "%c ", pop_op());
    }
}