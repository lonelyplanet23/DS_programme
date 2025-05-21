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
#define END 999999
int tot = 0;
typedef struct node
{
    int m;
    struct node *next;
} *nodeptr;
nodeptr insert_in_order(nodeptr head, nodeptr p)
{
    if(head == NULL)
        return p; //链表为空，以p作为头节点
    nodeptr q = head; //q为遍历指针
    if(p->m <= q->m)
    {
        //头插
        p -> next = q;
        return p;
    }
    while (q->next != NULL && q->next->m < p->m)   q = q->next;
    //现在q->next指向 空指针或者 第一个大于等于P的指针
    if(q->next == NULL)
    {
        q->next = p; // 直接插入
    }
    else
    { //q->next指向第一个大于等于P的指针，两步插入
        p->next = q->next;
        q->next = p;
    }   
    return head;
}
nodeptr sell(nodeptr head, int m)
{
    if(m > tot || head == NULL) return head; // 若m大于链表银块的总重量，则不处理（忽略该操作）
    //从链表第一个结点开始依次取出银块，直到取出银块的累计重量大于等于m为止
    //都是头部结点删除！！
    int sum = 0;
    nodeptr p = head;
    while(p != NULL && sum +  p->m <= m) // 直接卖掉 //!&&
    {
        sum += p->m; // sum 加上
        nodeptr del = p;
        // free(del); // 头删
        p = p->next;
         
    }
    //此时 判断是否切割 还不够的话切割
    if(sum < m)
    {    
        p->m -= (m - sum); // 剩余质量
    }
    tot -= m; // 判断了是否操作
    return p;

}
nodeptr connect(nodeptr head)
{
    nodeptr p = head;
    nodeptr new = malloc(sizeof(nodeptr));
    new->m = 0;
    if(p == NULL) return NULL; //空表格
    while(p != NULL && p->m < 10)
    {
        new->m += p->m;
        p = p->next;
    }
    new -> next = NULL;
    //此时 p是 第一个大于等于10的 把new插入
    return insert_in_order(p, new);
}
void print(nodeptr head)
{
    nodeptr p = head;
    while(p != NULL)
    {
        printf("%d ", p->m);
        p = p->next;
    }
}
int main()
{
    nodeptr head = malloc(sizeof(nodeptr));
    head = NULL; // 创建空头指针
    int op;
    scanf("%d", &op);
    while(op != END)
    {
        if(op > 0)//购买！
        {
            nodeptr p = malloc(sizeof(nodeptr));
            p -> m = op;
            p -> next = NULL;
            head = insert_in_order(head, p);
            tot += op;
        }
        else if(op < 0)
        {
            head = sell(head, 0-op);
        }
        else if(op == 0)
        {
            head = connect(head);
        }
        scanf("%d", &op);
    }
    print(head);
    return 0;
}