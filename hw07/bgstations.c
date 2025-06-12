//编写一个程序实现北京地铁最短乘坐（站）线路查询，输入为起始站名和目的站名，输出为从起始站到目的站的最短乘坐站换乘线路。

//注：1. 要求采用Dijkstra算法实现；2）如果两站间存在多条最短路径，找出其中的一条即可。
//文件bgstations.txt为数据文件
/*
输出从起始站到目的站的乘坐信息，要求乘坐站数最少。换乘信息格式如下：

SSN-n1(m1)-S1-n2(m2)-...-ESN

其中：SSN和ESN分别为起始站名和目的站名；n为乘坐的地铁线路号，m为乘坐站数；其它字符都是英文字符。
*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
//采用邻接表
int n = 0, m; //n为站点数，m为线路数
struct edge {
    int index; //!边所在的线路编号
    int to;
    struct edge *next;
};
typedef struct edge* Edge; //边的指针类型
typedef struct node {
    char name[20]; //站名
    int transfer; //换乘标记
    Edge edges; //边的链表
} Node;
Node graph[405]; //图的邻接表表示
int visited[405]; //访问标记
int path[405]; //存储路径

int my_cmp(const void* a, const void* b) 
{
    return strcmp(((Node*)a)->name, ((Node*)b)->name);
} //比较函数，用于bsearch
void my_cpy(Node* a, Node *b) 
{
    strcpy(a->name, b->name); //复制站名
    a->transfer = b->transfer; //复制换乘标记
    a->edges = NULL; //初始化边链表为空
} 

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
    return node.edges; 
}


void Create_list(FILE* fp)
{
    char line[100];
    int index = 0;
    fscanf(fp, "%d\n", &m); //读取站点数和线路数

    //一条线路一条线路的读取
    while(fgets(line, sizeof(line), fp) != NULL) 
    {
        int line_index, tot; //线路编号和站点数
        sscanf(line, "%d %d", &line_index, &tot); //读取线路编号 站点数
        if(line[0] == '\n' || line[0] == '\r') continue; 
        Node current, prev; //当前站和前一站
        for(int i = 0; i < tot; i++)
        {
            fgets(line, sizeof(line), fp); //读取站名
            char line_name[20];
            int transfer;
            sscanf(line, "%s %d", line_name, transfer); //读取站名

            //建立当前站结点
            Node current;
            strcpy(current.name, line_name); //存储站名
            current.transfer = transfer; //存储换乘标记
            current.edges = NULL; //初始化边链表为空

            Node *found = (Node*)bsearch(line_name, graph, n, sizeof(Node), my_cmp); //二分查找站名
            int found_index = found ? (found - graph) : -1; //找到的站点索引
            //如果没有找到，说明是新站点
            if(found == NULL)
            {
                 my_cpy(&graph[n++], &current); 
                 found_index = n - 1; //新站点的索引
            }
            
            // 如果是第一个，第一站作为前一站
            if(i == 0)
            {
                my_cpy(&prev, &current);
                continue;
            }

            //插入边
            //!注意是N-1
            Edge new_edge = insert_edge(prev, n - 1, line_index); //将前一站和当前站连接

        }
    }
}
double eps = 1e-9;
int main()
{
    FILE* bgstations = fopen("bgstations.txt", "r");
    if (bgstations == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    return 0;
}