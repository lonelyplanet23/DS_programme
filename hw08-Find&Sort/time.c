/*
由于学生可以多次登陆、注销，所以有可能记录了某位学生多次使用系统的情况，
请统计合并每位学生使用系统的时间，并按由大至小排序输出（时间相同时按学号由小到大排序输出）。
*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 101
struct stu
{
    int id;
    char name[21];
    int time;
} table[N];
int m = 0;
int n = 0; //记录学生人数
int my_find(struct stu s, int tot)
{
    for(int i = 0; i <= tot; i++)
    {
        if(table[i].id == s.id) return i;
    }
    return -1;
}

int my_cmp(const void *a, const void *b)
{
    struct stu *stu_a = (struct stu *)a;
    struct stu *stu_b = (struct stu *)b;
    
    if(stu_a->time != stu_b->time)
        return stu_b->time - stu_a->time; // 按时间降序 后减前
    else
        return stu_a->id - stu_b->id; // 时间相同时按学号升序
}
void read()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        struct stu temp;
        scanf("%d %s %d", &temp.id, temp.name, &temp.time);
        //!二分查找要求有序 用线性查找
        int find = my_find(temp, i);
        if(find != -1)
        {
            table[find].time += temp.time; // 如果找到了，累加时间
        }
        else
        {
            table[m++] = temp; // 如果没找到，添加新记录
        }
    }    
}

double eps = 1e-9;
int main()
{
    read();
    qsort(table, n, sizeof(struct stu), my_cmp);
    for(int i = 0; i < m; i++)
    {
        if(table[i].time != 0)
        {
            printf("%08d %s %d\n", table[i].id, table[i].name, table[i].time);     
        } 
    }
    return 0;
}