//内存申请
//1）从当前位置开始遍历空闲块链表（初始是从地址最小的第一个空闲块开始），寻找满足条件的最小块（即：大于等于请求空间的最小空闲块，如果有多个大小相同的最小空闲块，则选择遍历遇到的第一个空闲块）（最佳适应原则）；
//2）如果选择的空闲块恰好与请求的大小相符合，则将它从链表中移除并返回给用户；这时当前位置变为移除的空闲块指向的下一空闲块；
//3）如果选择的空闲块大于所申请的空间大小，则将大小合适的空闲块返回给用户，剩下的部分留在空闲块链表中；这时当前位置仍然为该空闲块；
//4）如果找不到足够大的空闲块，则申请失败；这时当前位置不变。
//! 链表中没有空闲块，则什么都不输出，容易出现内存泄漏，必须处理
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define ll long long
#define N 100001
double eps = 1e-9;
typedef struct node
{
    int pos;
    int len;
    struct node *next;
} *Nodeptr;
void print(Nodeptr head)
{
    if (head == NULL) {
        return;
    }
    Nodeptr p = head->next;
    do
    {
        printf("%d %d\n", p->pos, p->len);
        p = p->next;
    } while(p != head->next);
}
Nodeptr create_list(int n)
{
    if (n <= 0) {
        printf("无效的链表大小\n");
        return NULL;
    }
    if (n <= 0) return NULL;
    Nodeptr head = NULL, p, q;
    int pos, len;
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d", &pos, &len);
        q = (Nodeptr) malloc(sizeof(struct node));
        if (q == NULL)
        {
            printf("内存分配失败\n");
            exit(1);
        }
        q->len = len;
        q->pos = pos;
        q->next = NULL;
        if(head == NULL)
        {
            head = p = q;
            continue;
        }
        else
        {
            p->next = q;
            p = p->next;// p = q;
        }
    }
    // Creating a circular linked list by pointing the last node to the head
    p->next = head;
    return p;
}
Nodeptr allocate_memory(Nodeptr dst_prv, Nodeptr dst, int len)
{
    if(dst_prv == NULL || dst == NULL) return NULL;

    if(dst->len == len)
    {
        if (dst_prv == dst) {
            // 链表中只有一个节点
            free(dst);
            return NULL;
        }
        //删除该区块
        dst_prv -> next = dst -> next;
        free(dst);
        return dst_prv;
    }
    else if(dst->len > len)
    {
        // if(dst->pos == 142640)
        // {
        //     printf(" %d mem: %d   apply: %d\n", dst->pos, dst->len, len);
        //     printf("At this time:");
        //     print(dst);
        //     printf("\n");
        // }
        dst->len -= len;
        return dst_prv;
    }
    return NULL;
}
Nodeptr apply_for_memmory(Nodeptr prv, int len)
{
    if (prv == NULL || prv->next == NULL) {
        // 链表为空或只有一个节点且被完全分配
        return prv;
    }
    Nodeptr cur = prv->next;
    Nodeptr best_fit_prv = NULL;
    Nodeptr p = prv;
    if(len == 2048)
    {
        print(prv);
        printf("\n");
    }

    do
    {
        if(best_fit_prv == NULL)
        {
            if(p->next->len == len)
            {
                best_fit_prv = p;
                break;
            }
            else if(p->next->len > len && best_fit_prv == NULL)
            {
                best_fit_prv = p;
            }
            else if(p->next->len < len)
            {
                p = p->next;
                continue;
            }
        }
        if(p->next->len == len)
        {
            best_fit_prv = p;
            break;
        }
        else if(p->next->len >= len && p->next->len < best_fit_prv->next->len) //严格小于
        {
            best_fit_prv = p;
        }
        p = p->next;
    } while(p->next != cur);
    if(best_fit_prv == NULL)
    {
        return prv;
    }
    Nodeptr next = allocate_memory(best_fit_prv, best_fit_prv->next, len);
    return next;

}
void free_list(Nodeptr head)
{
    if (head == NULL) return;

    Nodeptr p = head->next;
    Nodeptr temp;

    // 遍历链表并释放每个节点
    while (p != head)
    {
        temp = p;
        p = p->next;
        free(temp);
    }
    free(head); // 最后释放头节点
}

int main()
{
    int n;
    scanf("%d", &n);
    Nodeptr prv = create_list(n);
    int apply_len;
    scanf("%d", &apply_len);
    while (apply_len != -1)
    {
        prv = apply_for_memmory(prv, apply_len);
        scanf("%d", &apply_len);
    }

    print(prv);

    // 释放链表内存
    free_list(prv);

    return 0;
}