#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
double eps = 1e-9;
int n;
int m = 0; //最大座位号
struct stu
{
    int id;
    char name[21];
    int seat;
} table[N];

int my_cmp(const void *a, const void *b)
{
    struct stu *stu_a = (struct stu *)a;
    struct stu *stu_b = (struct stu *)b;
    
    if(stu_a->seat != stu_b->seat)
        return stu_a->seat - stu_b->seat; 
    else
        return stu_a->id - stu_b->id; 
}
void check()
{
    int j = n-1;
    int q = (m < n)? m : n;
    int seat = 1;
/*假设当前表中安排的最大座位号为M，取M和N的较小值Q；从1号开始检查，若某个小于等于Q的座位序号没有安排学生，
则将表T2的最后学生的座位设置为该座位号；若存在多个漏排座位，则从表T2最后依次向前设置；*/
    for(int i = 0; i < n, seat <= q; )
    {
        if(table[i].seat == seat)
        {
            while(table[i].seat == seat)
            {
                i++;
            }
            seat++;
        }
        if (table[i].seat > seat) // [seat , table[i].seat) 之间没有安排
        {
            int l = seat;
            int r = table[i].seat;
            for(int k = l; k < r; k++, j--)
            {
                table[j].seat = k;
            }
            seat = r;
        }
    }

    qsort(table, n, sizeof(struct stu), my_cmp);

    //假设当前表中安排的最大座位号为m，
    //将座位号重复的、学号较大的学生的座位号依次设置为m+1、m+2、m+3......；
    int i = n-1;
    int cur_seat = m;
    while(cur_seat >= 1 && i > 1)
    {
        for(; i > 0 && table[i].seat == cur_seat && table[i-1].seat == cur_seat; i--)
        {
            table[i].seat = m;
            m++;
        }
        i--; //跳过最后一个
        cur_seat--;
    }
}
int main()
{
    scanf("%d", &n);
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    for(int i = 0; i < n; i++)
    {
        scanf("%d %s %d", &table[i].id, table[i].name, &table[i].seat);
        if(table[i].seat > m) m = table[i].seat;
    }
    qsort(table, n, sizeof(struct stu), my_cmp);
    check();
    qsort(table, n, sizeof(struct stu), my_cmp);

    for(int i = 0; i < n; i++)
    {
        printf("%d %s %d\n", &table[i].id, table[i].name, &table[i].seat);
    }

    return 0;
}