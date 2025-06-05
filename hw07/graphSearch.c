#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
double eps = 1e-9;
int M[101][101]; //邻接矩阵表示图
int n, m; //n:顶点数，m:边数
int visited[101];
int queue[101];
int front = -1;
int rear = -1;
void push(int node)
{
    //入队
    if(rear == 100) return;
    queue[++rear] = node;
}
int pop()
{
    //出队
    if(front == rear) return 0;
    return queue[++front];
}
int is_empty()
{
    return front == rear;
}
void Create_Graph()
{
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        M[x][y] = M[y][x] = 1;
    }
}
void delete_node(int i)
{
    //删除节点i
    //删除的顶点编号不为0, 因此不需要总体缩小M
    for(int j = 0; j < n; j++)
    {
        M[i][j] = M[j][i] = 0;
    }
}
void dfs(int i)
{
    printf("%d ", i);
    visited[i] = 1;
    for(int j = 0; j < n; j++)
    {
        if(M[i][j] == 1 && visited[j] == 0)
        {
            dfs(j);
        }
    }
}
void bfs(int i)
{
    printf("%d ", i);
    visited[i] = 1;
    push(i);
    while(!is_empty())
    {
        int node = pop();
        for(int j = 0; j < n; j++)
        {
            if(M[node][j] == 1 && visited[j] == 0)
            {
                printf("%d ", j);
                visited[j] = 1;
                push(j);
            }
        }
    }
}
int main()
{
    Create_Graph();
    dfs(0);
    printf("\n");
    memset(visited, 0, sizeof(visited));
    bfs(0);
    printf("\n");
    int delete_index;
    scanf("%d", &delete_index);
    delete_node(delete_index);
    memset(visited, 0, sizeof(visited));
    dfs(0);
    printf("\n");
    memset(visited, 0, sizeof(visited));
    bfs(0);
    return 0;
}