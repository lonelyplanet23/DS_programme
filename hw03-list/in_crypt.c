#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
double eps = 1e-9;
FILE *fin, *fout;
typedef struct node
{
    char ch;
    struct node *next;
} *nodeptr;
int used[128]; //表示字符是否使用过
char str_without_repeat[128]; //存储不重复的字符
char encrypt[128]; //存储加密后的字符
void remove_duplicate(FILE *fin)
{
    char ch;
    int k = 0;
    while((ch = fgetc(fin)) != EOF)
    {
        if(ch == '\n') continue;
        if(ch >= 32 && ch <= 126) //判断是否是可打印字符
        {
            if(used[ch] == 0) //如果没有使用过
            {
                str_without_repeat[k++] = ch; //存储不重复的字符
            }
            else continue; //如果使用过则跳过
        }
    }
    str_without_repeat[k] = '\0'; //字符串结束符
}
nodeptr create_list(char *str_without_repeat)
{
    nodeptr head = (nodeptr)malloc(sizeof(struct node)); //创建头结点
    head->next = NULL;
    nodeptr p = head;
    for(int i = 0; str_without_repeat[i] != '\0'; i++)
    {
        nodeptr new_node = (nodeptr)malloc(sizeof(struct node)); //创建新节点
        new_node->ch = str_without_repeat[i]; //存储字符
        new_node->next = NULL; //指向NULL
        p->next = new_node; //将新节点连接到链表中 
        p = new_node; //移动指针到新节点
    }
    for(int i = 32; i <= 126; i++)
    {
        if(used[i] == 0) //如果没有使用过
        {
            nodeptr new_node = (nodeptr)malloc(sizeof(struct node)); //创建新节点
            new_node->ch = i; //存储字符
            new_node->next = NULL; 
            p->next = new_node; 
            p = new_node; 
        }
    }
    p -> next = head;
    return p; //返回尾结点
}
nodeptr delete(nodeptr prv, nodeptr cur)
{
    prv->next = cur->next;
    free(cur);
    return prv->next;
}
nodeptr moving(nodeptr cur, int n)
{
    nodeptr p = cur;
    for(int i = 1; i < n-1; i++) //可优化n
    {
        p= p->next;
    }
    return p; //返回目标指针的前一个
}
void encrypt_list(nodeptr tail, char *encrypt)
{
    nodeptr p = tail, q = tail->next; //指向第一个节点
    int i = 32;
    char first = p->ch;
    q = q->next;
    while(p != q)
    {
        int movingTimes = (int)p->ch;
        p = delete(p,p); //head这时无所指


    }

}
int main()
{
    fin = fopen("in.txt", "r"); //打开输入文件
    fout = fopen("out.txt", "w"); //打开输出文件
    remove_duplicate(fin); //去除重复字符
    nodeptr list = create_list(str_without_repeat); 
    encrypt_list(list, encrypt); //加密字符
    char cur;
    while((cur = fgetc(fin) )!= EOF)
    {
        if(cur == '\n') fputc('\n', fout); 
        if(cur >= 32 && cur <= 126) 
        {
            fputc(encrypt[cur], fout); 
        }
    }
    return 0;
}