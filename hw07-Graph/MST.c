#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
#define INF 0x3f3f3f3f //无穷大
// 无向图，采用邻接矩阵
int n, m;
int G[101][101]; //邻接矩阵表示图
int ID[101][101]; //边的编号
int ans[101]; //存放答案
int top = -1; //栈顶指针
int minweight[101]; //最小权重
int dist[101]; //记录选取的边的另一端点（其中之一）

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
void init_graph()
{
    for (int i = 0; i < 101; i++)
    {
        for (int j = 0; j < 101; j++)
        {
            G[i][j] = INF; // 初始化为无穷大
        }
    }
}
void Create_Graph()
{
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++)
    {
        int x, y, id, weight;
        scanf("%d %d %d %d", &id, &x, &y, &weight); //!注意输入顺序！
        ID[x][y] = ID[y][x] = id;
        G[x][y] = G[y][x] = weight; 
    }
}

int Prim()
{
    int total_weight = 0;
    int min_weight = INF, u, v;
    
    // 将节点0加入MST，更新minweight数组
    minweight[0] = 0; 
    for(int i = 1; i < n; i++)
    {
        
        minweight[i] =  G[0][i]; 
        dist[i] = 0; //初始化dist数组
    }

    // Prim算法主循环
    for(int i = 1; i < n; i++)
    {
        min_weight = INF;
        u = -1;
        for(int j = 0; j < n; j++)
        {
            if(minweight[j] != 0 && minweight[j] < min_weight)
            {
                min_weight = minweight[j];
                u = j; //找到当前最小边的终点
            }
        }
        if(u == -1) return -1; //如果没有可选的边，返回-1表示无法构成MST

        //将节点u加入MST
        minweight[u] = 0;
        total_weight += min_weight; 
        ans[++top] = ID[dist[u]][u];//!核心语句 答案所需的边

        //更新每个节点的Minweight
        for(int j = 0; j < n; j++)
        {
            //!结点j未加入 MST，且(U, j)权重小于当前的最小权重
            if(minweight[j] > 0 && G[u][j] < minweight[j])
            {
                minweight[j] = G[u][j];
                dist[j] = u;
            }
        }
    }
    return total_weight;
}
int main()
{
    init_graph(); //!初始化邻接矩阵为无穷大 不能用memset函数逐字节填充
    Create_Graph();
    printf("%d", Prim());

    printf("\n");
    qsort(ans, top + 1, sizeof(int), cmp); 
    for(int i = 0; i <= top; i++)
    {
        printf("%d ", ans[i]); 
    }
    return 0;
}