#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
double eps = 1e-9;
//邻接矩阵在本题不好用，采用邻接表
int n, m;
struct edge {
    int index; //边的编号
    int to;
    struct edge *next;
};
typedef struct edge* Edge; //边的指针类型
typedef struct node {
    int index; //节点编号
    Edge edges; //边的链表
} Node;
Node graph[101]; //图的邻接表表示
int visited[101]; //访问标记
int path[101]; //存储路径
Edge insert_edge(Node node, int to, int index)
{
    Edge new_edge = (Edge)malloc(sizeof(struct edge));
    new_edge->index = index;
    new_edge->to = to;
    new_edge->next = NULL;
    if (node.edges == NULL) 
    {
        node.edges = new_edge; //如果没有边，直接插入
    } 
    else 
    {
        Edge p = node.edges;
        while (p->next != NULL) {
            p = p->next; //找到链表的最后一个节点
        }
        p->next = new_edge; //插入新边
    }
    return node.edges; //!注意 返回的头结点的链表
}
void create_list()
{
    scanf("%d %d", &n, &m);
    //初始化结点
    for(int i = 0; i < n; i++)
    {
        graph[i].index = i;
        graph[i].edges = NULL; //初始化边链表为空
    }
    for(int i = 0; i < m; i++)
    {
        int index, x, y;
        scanf("%d %d %d", &index, &x, &y);
        //插入边
        graph[x].edges = insert_edge(graph[x], y, index);
        graph[y].edges = insert_edge(graph[y], x, index); //无向图，双向插入
    }
}
void dfs(int i, int dest, int step)
{
    visited[i] = 1;
    if(i == dest) 
    {
        //到达目标节点，输出路径
        for(int j = 0; j < step; j++)
        {
            printf("%d ", path[j]); //输出路径
        }
        printf("\n");
        return; 
    }
    Edge p = graph[i].edges;
    while(p != NULL)
    {
        if(visited[p->to] == 0)
        {
            path[step] = p->index; // 将当前边的编号加入路径
            dfs(p->to, dest, step + 1); //递归访问下一个节点
            visited[p->to] = 0;//!关键句：可以多次重复的关键
        }
        p = p->next;
        //不能直接在进入中途打印边的编号，为什么呢？
        //因为可能会有多条路径到达目标节点，需要在所有路径都遍历完后再输出(否则该节点只输出一次)
    }
}

void free_graph()
{
    for (int i = 0; i < n; i++)
    {
        Edge p = graph[i].edges;
        while (p != NULL)
        {
            Edge temp = p;
            p = p->next;
            free(temp);
        }
        graph[i].edges = NULL;
    }
}
int main()
{
    create_list();
    int start = 0, dest = n-1;
    memset(visited, 0, sizeof(visited)); //初始化访问标记
    dfs(start, dest, 0); //从起点到终点进行深度优先搜索
    free_graph(); // 释放内存
    return 0;
}