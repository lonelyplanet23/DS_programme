#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
typedef struct segment
{
    int x1,y1,x2,y2;
    int n;
    int last_index;
} Segment;
Segment set[1000];
int used[1000];
int my_cmp(const void *a, const void *b)
{
    Segment *A = (Segment *)a;
    Segment *B = (Segment *)b;
    if(A->x1 == B->x1) return A->y1 - B->y1;
    return A->x1 - B->x1;
}
int main()
{
    int n, max = 1, max_index = -1;
    scanf("%d",&n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d %d %d",&set[i].x1,&set[i].y1,&set[i].x2,&set[i].y2);
        used[i] = 0;
        set[i].n = 1;
        set[i].last_index = -1; //表示没有被连接
    }
    qsort(set, n, sizeof(Segment), my_cmp);
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(used[j] == 1) continue; //一条线段不可能被两条线段连接
            if(set[i].x2 == set[j].x1 && set[i].y2 == set[j].y1)
            {
                used[j] = 1;
                set[j].n = set[i].n + 1;
                set[j].last_index = i; //表示i->j连接
            }
        }
        //优化方案：用binary search来查找连接的线段
    }
    for(int i = 0; i < n; i++)
    {
        if(set[i].n > max)
        {
            max = set[i].n;
            max_index = i; //记录最大值的下标
        }
    }
    printf("%d",max);
    int k = max_index;
    while(set[k].last_index >= 0)
    {
        k = set[k].last_index; //回溯
    }
    printf(" %d %d\n",set[k].x1,set[k].y1); //输出起点
    return 0;
}