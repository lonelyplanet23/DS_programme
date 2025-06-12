# 第10讲 图-(2)

## 最短路径问题

**1. 深度、广度优先搜索 + 擂台计算最短**

**2. 动态规划：蚂蚁走路问题**

**3. 贪心： Dijkstra 算法**
**核心：**
+ Dijkstra 算法是一种**单源最短路径算法**，用于计算**从起点到其他所有点的最短路径**（**不能有负权边**）。

1. **初始化**：

   * 把起点到自己的距离设为 0，其他点设为 ∞（表示暂时不可达）。
   * 建立一个「已确定最短路径的集合」，最开始只有起点。

2. **每轮循环**：将目前最短的点加入到**已确定的集合X**中，并更新剩余的点

   * 从**未处理的点中选择当前距离起点最近的点 u**； -- **这是贪心实质**
   * 对 u 的所有邻接点 v，如果经过 u 到 v 更短，就更新 v 的距离；
   * 把 u 标记为“已确定”。


3. **重复以上过程，直到所有点都处理完**。


```c
int n; // 顶点个数
int graph[MAX][MAX]; // 邻接矩阵

void dijkstra(int start, int dist[]) {
    int visited[MAX] = {0};
    int spath[MAX] = {0}; //表示最短路径，只记前驱结点

    // 初始化
    for (int i = 0; i < n; i++) {
        dist[i] = graph[start][i];
    }
    dist[start] = 0;
    visited[start] = 1;

    // 主循环
    for (int i = 1; i < n; i++) {
        int min = INF;
        int u = -1;

        // 找未访问中距离最小的点 u
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // 所有点已放入X，结束算法
        visited[u] = 1;

        // 用 u 更新其邻居 v 的距离
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            } // 在Y中，且路径存在，且比当前距离小
        }
    }
}
```
---
## 最小生成树


 **概念**： 
 1. 对于图G(V,E) 包含全部顶点的极小连通子图，包含n-1条边、无回路！
   + **以下条件任选其二都可以推出是最小生成树**
      + 连通
      + n-1条边
      + 无回路
2. 带权连通图中，**总的权值之和最小**的生成树称为最小生成树

### 求解最小生成树

**两种增量法（递推！！！）**：从空树开始，依次从图G中挑选一条边/顶点加入生成树，逐步构造出完整的生成树。

#### 普里姆(Prim)算法

1. **残图**：**图G**去掉当前**生成树T**后的剩余
   
2. 初始化：将v0加入树
3. 选择：从连接残图G’(顶点集V’)和最小生成树T(顶点集U)的所有边中**选择一条权值最小的边/顶点** **贪心实质！！** 从minweight里找最小的
4. 添加：将该边及其端点加入生成树T
5. 更新：：更新邻接顶点的最短边信息

```C
#define INF 1000000
#define N 100  // 最大顶点数

int n;                // 顶点数
int cost[N][N];       // 邻接矩阵，存边权
int visited[N];       // 是否已经加入 MST
int minweight[N];           // 到当前 MST 的最小边权
int dest[VNUM];             // 记录最短边的另一个端点

int prim(int start) {
    //初始化
    int total = 0;
    for (int i = 0; i < n; i++) {
        minweight[i] = cost[start][i]; //将初始节点加入MST
        visited[i] = 0;
    }
    visited[start] = 1;

    
    for (int i = 1; i < n; i++) {
        int min = INF, k = -1;

        //查找满足要求的一条边(j,k)
        for (int j = 0; j < n; j++) {
            if (!visited[j] && minweight[j] < min) {
                min = minweight[j];
                k = j;
            }
        }

        //添加到MST
        if (k == -1) break;  // 图不连通
        visited[k] = 1;
        total += min;

        //更新
        for (int j = 0; j < n; j++) {
            if (!visited[j] && cost[k][j] < low[j]) {
                minweight[j] = cost[k][j];
                dest[j] = k;
            }
        }
    }

    return total;
}

```

#### Kruskal 算法 ：从所有边中选

1. 选择：从G中选择一条之前未选择过的、权值最小的边e（注：可以先对所有边按权值升序排序）
2. 更新：若边e使得T产生回路,则本次选择无效,放弃e；否则将e加入T
3. 重复上述选择过程直到TE中包含了G的n-1条边，此时的T为G的最小生成树。

代码实现需要**并查集（Disjoint Set / Union-Find）**

## 小结
| 属性   | 最短路径树（SPT）   | 最小生成树（MST） |
| ---- | ------------ | ---------- |
| 起点   | 有指定源点        | 无源点（全图）    |
| 路径   | 源点到每个点的最短路径  | 覆盖所有点的最小权和 |
| 边数   | n − 1        | n − 1      |
| 目标   | 最短路径长度       | 总边权最小      |
| 判断依据 | 最小路径总长（针对单点） | 无回路，总权重最小  |
