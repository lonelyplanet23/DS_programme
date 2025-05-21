# Lecture 9 树

### 二叉树的常见性质
**1. n个结点的非空二叉树，共有n-1个分支**
   
**2.  叶子结点和其他节点的数量关系**
   
$\large n_0 = 1 + \sum_{k>=1} (k-1)*n_k$  
+ 其中$n_i$指度为i的节点数

1. 理解：**从根向底部，分支增加多少，就1+多少个叶子结点！**

2.  非空二叉树，第i层，最多有$2^{i-1} (i >= 1)$个结点

**3. 树枝数和结点数关系** 

$\large 树枝数 = 结点数 - 1$  

**3.  完全二叉树的性质**
1.  编号确定 
    + 当i = 1,则编号为i的结点为二叉树的根结点；若i>1,则编号为i的结点的双亲的编号为$\lfloor i/2 \rfloor + 1$；
    + 若2i > n,则编号为i的结点无左子树; 若2i<=n,则编号为i的结点的左孩子的编号为2i；
    + 若2i+1 >n,则编号为i的结点无右子树; 若2i+1 <= n,则编号为i的结点的右孩子的编号为2i + 1。
2. 除叶子节点层以外，**其他层的结点数**为$2^{i-1} (i >= 1)$
3. n个结点的非空完全二叉树的**深度**为$\lfloor log_2 n\rfloor + 1$


## 二叉树的存储结构
### 顺序储存结构
**1. 完全二叉树**：由上到下，由左到右编号。

**2. 非完全二叉树**：只须在二叉树中“添加”一些实际上二叉树中并不存在的**“虚结点”** 转化为完全二叉树。

**3. 特点** 顺序存储结构便于结点的检索（由双亲查子、由子查双亲）动态数据容易溢出，**更适用于接近满二叉树的二叉树**
### 链式储存结构
1. 二叉链表 ![本地图片](image-1.png)
```C
struct node{
    Datatype data;
    struct node *lchild, *rchild
};
typedef struct node btnode;
typedef struct *node btnodeptr;
```
+ 应用：表达式树，后缀表达式，前缀表达式


**易错题**

**题目一：指针域**

若具有n个结点的二叉树采用二叉链表存储结构，则该链表中有 **(2n)** 个指针域，其中 **(n-1)** 个指针域用于链接孩子结点， **(n+1)** 个指针域空闲存放着NULL。
+ **链接孩子节点 = 边数！**

## 二叉树的遍历 重点！
输出所有结点的信息；
找出或统计满足条件的结点；
求二叉树的深度；
求指定结点所在的层次；
求指定结点的所有祖先结点
### 几种遍历方式
1. **按层次遍历 BFS**
```C
#define NodeNum100
BTNodeptrqueue[NodeNum],p;
int front,rear;
void layerOrder(BTNodeptr t)
{
    if(t != NULL)
    {
        push(p);
        while(!empty()) /* 若队列不空*/
        {
            p = pop();
            Visit(p); /* 访问p指结点*/
            if(p->lchild != NULL)
                push(p->lchild);
            if(p->rchild != NULL)
                push(p->rchild);
        }
    }
}
```   
2. **DFS 深度优先**

>**小结: 前中后指的是根节点访问的前中后！！**
   1. **前序遍历 D-L-R**
       1. D 访问根结点;
       2. L 以前序遍历原则遍历根结点的左子树;
       3. R 以前序遍历原则遍历根结点的右子树。
```C
    void preorder(BTnodeptr p)
    {
        if(p != NULL)
        {
            Visit(p);
            if(p->lchild != NULL)
                preorder(p->lchild);
            if(p->rchild != NULL)
                preorder(p->rchild);
        }
    }
```
```C
// 前序遍历非递归算法实现
void inOrder(BTNodeptr t) {
    BTNodeptr stack[M];  // 定义栈容器，M为预定义常量
    BTNodeptr p = t;     // 初始化遍历指针
    int top = -1;        // 栈顶指针初始化

    if (t != NULL) {     // 空树直接跳过
        do {
            // 将左子树全部入栈（含当前结点）
            while (p != NULL) {
                stack[++top] = p;     // 结点入栈
                VISIT(p);          // 访问该结点
                p = p->lchild;       
            }
            // 栈非空时进行回退访问
            if (top != -1) {
                p = stack[top--];    // 弹出栈顶元素
                p = p->rchild;       // 转向右子树进行遍历
            }
        } while (!(p == NULL && top == -1)); // 终止条件：栈空且无右子树
    }
}
```
+ 前缀表达式的计算：
  + 类比前序遍历，详情见代码


   1. **中序遍历 L D R**
      1. 以中序遍历原则遍历根结点的左子树;
       2. 访问根结点;
       3. 以中序遍历原则遍历根结点的右子树。
```C
    void inorder(BTnodeptr p)
    {
        if(p != NULL)
        {
            if(p->lchild != NULL)
                inorder(p->lchild);
            Visit(p); //!调换位置即可
            if(p->rchild != NULL)
                inorder(p->rchild);
        }
    }
```
+ 非递归的实现法（有时效率更高）
```C
// 中序遍历非递归算法实现
void inOrder(BTNodeptr t) {
    BTNodeptr stack[M];  // 定义栈容器，M为预定义常量
    BTNodeptr p = t;     // 初始化遍历指针
    int top = -1;        // 栈顶指针初始化

    if (t != NULL) {     // 空树直接跳过
        //注意用DO WHILE 因为一开始top = -1
        do {
            // 将左子树全部入栈（含当前结点）
            while (p != NULL) {
                stack[++top] = p;     // 结点入栈
                p = p->lchild;       // 持续访问左子树
            }

            // 栈非空时进行回退访问
            if (top != -1) {
                p = stack[top--];    // 弹出栈顶元素
                VISIT(p);            // 访问该结点
                p = p->rchild;       // 转向右子树进行遍历
            }
        } while (!(p == NULL && top == -1)); // 终止条件：栈空且无右子树
    }
}
```
   1. **后序遍历 L R D**
      1. 以中序遍历原则遍历根结点的左子树;
       2. 访问根结点;
       3. 以中序遍历原则遍历根结点的右子树。
```C
    void postorder(BTnodeptr p)
    {
        if(p != NULL)
        {
            if(p->lchild != NULL)
                postorder(p->lchild);
            if(p->rchild != NULL)
                postorder(p->rchild);
            Visit(p); //!调换位置即可
        }
    }
```
**顺序表的方式相同！**

### 由遍历序列恢复二叉树
**核心：必须是中序+ 前序/后序**
+  利用前序后序，定出根节点
+ 利用中序，分割左右子树
+ 递归进行左右子树。
    
## 二叉树的几种典型操作

### 获取高度 前序
```C
    int heightOfTree(BTnodeptr p)
    {
        if(p == NULL)
            return 0;
        else return 1 + max(heightOfTree(p->lchild), heightOfTree(p->rchild));
    }
```
### 删除
```C
    void  destoryTree(BTNodeptr p){
        if(p != NULL){
            destoryTree(p->lchild);
            destoryTree(p->rchild);
            free(p);
            p = NULL; 
        }
 }
```