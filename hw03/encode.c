#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define ll long long

typedef struct node
{
    char ch;
    struct node *next;
    struct node *prv;
} *nodeptr;
int used[129]; //表示字符是否使用过
char str_without_repeat[129]; //存储不重复的字符
char encrypt[129]; //存储加密后的字符
char code[1024];
void remove_duplicate(char *code)
{
    char ch;
    int k = 0;
    for(int i = 0; i < strlen(code); i++)
    {
        ch = code[i];
        if(ch >= 32 && ch <= 126) //判断是否是可打印字符
        {
            if(used[ch] == 0) //如果没有使用过
            {
                used[ch] = 1; //!及时更新
                str_without_repeat[k++] = ch; //存储不重复的字符
            }
            else continue; //如果使用过则跳过
        }
    }
    str_without_repeat[k] = '\0'; //字符串结束符

}
nodeptr create_list(char *str_without_repeat)
{
    nodeptr head = NULL; //创建头结点
    nodeptr p = head;
    for(int i = 0; str_without_repeat[i] != '\0'; i++)
    {
        nodeptr new_node = (nodeptr)malloc(sizeof(struct node)); //创建新节点
        new_node->ch = str_without_repeat[i]; //存储字符
        new_node->next = NULL; 
        if(head == NULL)
        {
            head = p = new_node;
            continue; 
        }
        new_node->prv = p;
        p->next = new_node;
        p = p->next;
    }
    for(int i = 32; i <= 126; i++) //没有使用过的字符依次连接在后面
    {
        if(used[i] == 0) 
        {
            nodeptr new_node = (nodeptr)malloc(sizeof(struct node)); //创建新节点
            new_node->ch = i; //存储字符
            new_node->next = NULL; 
            new_node->prv = p;
            p->next = new_node; 
            p = new_node; 
        }
    }
    if (head != NULL) {
        p->next = head;
        head->prv = p;
    }
    return head; //返回首节点
}
nodeptr delete(nodeptr cur)
{
    // Deletes the current node from the doubly circular linked list 
    if (cur == NULL) return NULL;
    nodeptr p = cur->next;
    cur->next->prv = cur->prv;
    cur->prv->next = cur->next;
    free(cur); 
    return p;
}
nodeptr moving(nodeptr cur, int n)
{
    nodeptr p = cur;
    for(int i = 1; i < n; i++) //可优化n
    {
        p = p->next;
    }
    return p; //返回目标指针
}
void encrypt_list(nodeptr head, char *encrypt)
{
    nodeptr p = head;//指向第一个节点
    int i = 32;
    char first = p->ch;
    while(p->next != p) //循环条件，节点数大于等于2
    {
        int movingTimes = (int)p->ch;
        p = delete(p); //p指向被删除节点下一个
        p = moving(p, movingTimes);
        if (movingTimes >= 32 && movingTimes <= 126) {//!保护性编程
            encrypt[movingTimes] = p->ch;
        }
    }
    encrypt[p->ch] = first; //只剩下一个节点，则其密文为原密钥的第一个字符
}
void print_list(char* str)
{
    for(int i = 32; i <= 126; i++)
    {
        printf("%c is en enrypted as %c\n", (char)i, str[i]);
    }
}
int main()
{
    fgets(code, sizeof(code), stdin); //输入密钥
    freopen("in.txt", "rb", stdin);
    freopen("in_crpyt.txt", "wb", stdout);
    code[strcspn(code, "\n")] = '\0';
    memset(used, 0, sizeof(used)); //初始化
    remove_duplicate(code); //去除重复字符
    //printf("%s\n", str_without_repeat);
    nodeptr list = create_list(str_without_repeat); 
    encrypt_list(list, encrypt); //加密字符
    char cur;
    //print_list(encrypt); 
    while((cur = getchar())!= EOF)
    { 
        if(cur >= 32 && cur <= 126) 
        {
            putchar(encrypt[cur]); 
        }
        else
        {
            putchar(cur);
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}