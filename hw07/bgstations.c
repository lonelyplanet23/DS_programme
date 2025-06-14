//编写一个程序实现北京地铁最短乘坐（站）线路查询，输入为起始站名和目的站名，输出为从起始站到目的站的最短乘坐站换乘线路。

//注：1. 要求采用Dijkstra算法实现；2）如果两站间存在多条最短路径，找出其中的一条即可。
//文件bgstations.txt为数据文件
/*
输出从起始站到目的站的乘坐信息，要求乘坐站数最少。换乘信息格式如下：

SSN-n1(m1)-S1-n2(m2)-...-ESN

其中：SSN和ESN分别为起始站名和目的站名；n为乘坐的地铁线路号，m为乘坐站数；其它字符都是英文字符。
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<locale.h>

#define MAX_NODES 405
#define INF 0x3f3f3f3f // 无穷大
typedef struct edge {
    int index; // 边所在的线路编号
    int from; //! 前驱站点的索引
    int to;
    struct edge *next;
} *Edge;

typedef struct node {
    char name[50]; // 站名
    int transfer; // 换乘标记
    Edge edges; // 边的链表
} Node;
Node graph[405]; //图的邻接表表示
Edge path[405]; //!存储路径 储存前驱边？

int n = 0, m; // n:站点数，m:线路数

int stack[MAX_NODES]; // 用于存储路径的栈
int top = -1;

void push(int value)
{
    if(top >= MAX_NODES - 1) {
        printf("栈溢出\n");
        return;
    }
    stack[++top] = value; // 将值压入栈
}

int pop() 
{
    if(top < 0) {
        return -1; // 栈为空
    }
    return stack[top--]; // 弹出栈顶元素
}

int top_value() 
{
    if(top < 0) {
        return -1; // 栈为空
    }
    return stack[top]; // 返回栈顶元素
}

int my_cmp(const void* a, const void* b) 
{
    return strcmp(((Node*)a)->name, ((Node*)b)->name);
}

void my_cpy(Node* a, Node *b) 
{
    strcpy(a->name, b->name); // 复制站名
    a->transfer = b->transfer; // 复制换乘标记
    a->edges = NULL; // 初始化边链表为空
}

// 线性查找站点
int find_station(const char* name)
{
    if (n <= 0) return -1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(graph[i].name, name) == 0) 
        {
            return i; 
        }
    }
    return -1;
}

Edge insert_edge(int from, int to, int index)
{
    Node node = graph[from]; // 获取前驱站点
    Edge new_edge = (Edge)malloc(sizeof(struct edge));
    new_edge->index = index;
    new_edge->from = from; // 前驱站点的索引
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
    return node.edges; 
}


void Create_list(FILE* fp)
{
    char line[100];
    int line_index, tot;

    fgets(line, sizeof(line), fp);
    sscanf(line, "%d", &m); // 读取线路数

    // 一条线路一条线路的读取
    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        if (line[0] == L'\n' || line[0] == L'\r') continue; 
        
        // 读取线路编号和站点数
        sscanf(line, "%d %d", &line_index, &tot);

        int cur = 0, prev = 0; // 当前站和前一站在图中的索引
        for (int i = 0; i < tot; i++)
        {
            fgets(line, sizeof(line), fp); // 读取站名
            char line_name[20];
            int transfer;
            sscanf(line, "%s %d", line_name, &transfer); // 读取站名和换乘标记

            // 建立当前站节点
            Node current;
            strcpy(current.name, line_name);
            current.transfer = transfer;
            current.edges = NULL;

            //二分查找不行，需要反复排序，只能线性查找
            cur = find_station(line_name); //查找当前站在图中的索引

            // 如果没有找到，说明是新站点
            if (cur == -1)
            {
                my_cpy(&graph[n], &current); 
                cur = n++; // 新站点的索引
            }

            // 如果是第一个，第一站作为前一站
            if (i == 0)
            {
                prev = cur; 
                continue;
            }

            //插入边
            Edge new_edge = insert_edge(prev, cur, line_index); //!将前一站和当前站连接
            graph[prev].edges = new_edge; //更新前一站的边链表
            new_edge = insert_edge(cur, prev, line_index); //站可以双向
            graph[cur].edges = new_edge; //更新当前站的边链表

            // 更新前一站为当前站
            prev = cur; 
        }
    }
}

// Dijkstra算法实现最短路径查找
int dist[MAX_NODES]; // 存储起点到各个节点的最短距离
void dijkstra(int start, int end)
{
    int visited[MAX_NODES] = {0}; 
    for(int i = 0; i < n; i++)
    {
        if (i != start) 
        {
            dist[i] = INF; 
            path[i] = NULL; 
        }
    }

    //初始化，将start加入已确定集合中
    visited[start] = 1;
    dist[start] = 0; 

    Edge edge = graph[start].edges;
    while(edge != NULL)
    {
        dist[edge->to] = 1;
        path[edge->to] = edge; //! 记录前驱边
        edge = edge->next;
    }

    //主循环
    for(int i = 1; i < n; i++)
    {
        int min = INF;
        int u = -1; // 这是集合Y中的结点标记

        //找出未访问结点中dist最小值和下标
        for(int j = 0; j < n; j++)
        {
            if(!visited[j] && dist[j] < min)
            {
                min = dist[j];
                u = j;
            }
        }

        //访问
        if(u == -1) break;
        visited[u] = 1;

        //更新邻结点
        Edge p = graph[u].edges;
        while(p != NULL)
        {
            if(!visited[p->to]) //!注意哦 
            {
                if(dist[u] + 1 < dist[p->to])
                {
                    dist[p->to] = dist[u] + 1;
                    path[p->to] = p; //! 更新前驱边
                }
            }
            p = p->next;
        }
    }
}

//思路：用队列来找出整个路径：倒着输入，正着输出，遇到特殊数字‘0’说明要换乘。
void print_path(int start, int end)
{
    int cur = end; //遍历结点cur

    while(cur != start)
    {
        Edge e = path[cur]; //读取前驱边

        int prv = e->from;
        int line_index = e->index;

        // 将边的站号入队列
        push(e->index); 
        
        // 更新当前站为前驱站
        cur = prv; 

        // 如果来到换乘站且不是首站，使用负数标记换乘站下标
        //! 且是真的换乘了，而非路过
        if (cur != start && graph[cur].transfer && e->index != path[cur]->index) 
        {
            push(0 - cur); 
        }
    }

    // 最终输出
    printf("%s-", graph[start].name); 
    while(top >= 0)
    {
        int value = pop();

        //换乘站
        if(value < 0)
        {
            value = 0 - value;
            printf("-%s-", graph[value].name);
            continue;
        }

        //非换乘站
        int index = value; //线路号
        int cnt = 1; //站数
        //如果栈顶也是该条线路，则站数+1,出栈
        while(top_value() == index)
        {
            cnt++;
            value = pop();
        }

        printf("%d(%d)", value, cnt);
    }
    printf("-%s", graph[end].name); 
}
int main()
{
    //# 用freopen实现更方便
    FILE* bgstations = fopen("bgstations.txt", "r");
    if (bgstations == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    Create_list(bgstations);
    
    char start_name[20], end_name[20];
    scanf("%s %s", start_name, end_name); 
    int start = find_station(start_name); // 查找起始站在图中的索引
    int end = find_station(end_name); // 查找目的站在图中的索引

    if (start == -1 || end == -1) {
        printf("起始站或目的站不存在。\n");
        fclose(bgstations);
        return 1;
    }

    dijkstra(start, end); 
    print_path(start, end); 

    fclose(bgstations);
    return 0;
}