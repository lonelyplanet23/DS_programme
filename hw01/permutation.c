//【问题描述】输入整数N( 1 <= N <= 10 )，生成从1~N所有整数的全排列。
//【输入形式】输入一个整数N。
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
int ans[N];
int used[N];
void dfs(int step, int n)
{
    if(step == n + 1)
    {
        for(int i = 1; i <= n; i++)
        {
            printf("%d ", ans[i]);
        }
        printf("\n");
        return;
    }
    for(int i = 1; i <= n; i++)
    {
        if(used[i] == 0)
        {
            ans[step] = i;
            used[i] = 1;
            dfs(step + 1, n);
            used[i] = 0;
        }
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    dfs(1, n);
    return 0;
}