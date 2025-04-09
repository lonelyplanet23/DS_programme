#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
struct entry
{
    int a, n;
    struct entry *next;
};
typedef struct entry* enptr;
enptr list1, list2, ans;
enptr create_list()
{
    enptr head = NULL, p, q; //表头，前一个，当前一个
    int a, n;
    //!换行读取
    while(scanf("%d %d", &a, &n) == 2)
    {
        enptr q = (enptr)malloc(sizeof(struct entry));
        q->a = a;
        q->n = n;
        q->next = NULL;
        if(head == NULL)
        {
            head = q;
            p = q;
        }
        else
        {
            p -> next = q;
            p = p->next;
        }
        if (getchar() == '\n') break; // 处理换行符
    }
    return head;
}
enptr insert_sorted(enptr list, enptr src)//合并同类项专用
{
    //!头部插入没有前驱 prev为空 导致出错，必须提前处理
    if(list == NULL || src->n > list->n)
    {
        src->next = list;
        return src;
    }
    enptr prev = NULL, p = list;
    while(p != NULL && p->n >= src->n)
    {
        if(p->n == src->n)
        {
            p->a += src->a;
            free(src);
            return list;
        }
        prev = p;
        p = p->next;
    }
    //! 插入到中间或者末尾需要前驱 
    prev->next = src;
    src->next = p;
    return list;
}
enptr multiply(enptr list1, enptr list2);
void freePolynomial(enptr head) {
    enptr temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
void print(enptr list)
{
    enptr p = list;
    for(; p != NULL; p=p->next)
    {
        printf("%d %d ", p->a, p->n);//! 不能在这里free
    }
    printf("\n");
}
int main()
{
    list1 = create_list();
    list2 = create_list();
    enptr ans = multiply(list1, list2);
    print(ans);
    freePolynomial(list1);
    freePolynomial(list2);
    freePolynomial(ans);
    return 0;
}

enptr multiply(enptr list1, enptr list2)
{
    enptr p1 = list1, p2 = list2, p, q;
    enptr ans = NULL;
    for(p1 = list1; p1 != NULL; p1 = p1->next)
    {
        for(p2 = list2; p2 != NULL; p2 = p2->next) //回到开头
        {
            q = (enptr)malloc(sizeof(struct entry));
            q->a = p1->a * p2->a;
            q->n = p1->n + p2->n;
            q->next = NULL;
            //把这一项插入或者合并到合适的位置
            ans = insert_sorted(ans, q);
        }
    }
    return ans;
}