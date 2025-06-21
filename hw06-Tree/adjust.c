/*【问题描述】

假设某机场所有登机口（Gate）呈树形排列（树的度为3），安检处为树的根，如下图所示。图中的分叉结点（编号大于等于100）表示分叉路口，登机口用小于100的编号表示（其一定是一个叶结点）。通过对机场所有出发航班的日志分析，得知每个登机口每天的平均发送旅客流量。作为提升机场服务水平的一个措施，在不改变所有航班相对关系的情况下（即：出发时间不变，原在同一登机口的航班不变），仅改变登机口（例如：将3号登机口改到5号登机口的位置），使得整体旅客到登机口的时间有所减少（即：从安检口到登机口所经过的分叉路口最少）。
编写程序模拟上述登机口的调整，登机口调整规则如下：

1）首先按照由大到小的顺序对输入的登机口流量进行排序，流量相同的按照登机口编号由小到大排序；

2）从上述登机口树的树根开始，将登机口按照从上到下（安检口在最上方）、从左到右的顺序，依次对应上面排序后将要调整的登机口。

例如上图的树中，若只考虑登机口，则从上到下有三层，第一层从左到右的顺序为：5、6、14、13，第二层从左到右的顺序为：7、8、9、10、1、2、18、17、16、15，第三层从左到右的顺序为：11、12、3、4、20、19。若按规则1排序后流量由大至小的前五个登机口为3、12、16、20、15，则将流量最大的3号登机口调整到最上层且最左边的位置（即：5号登机口的位置），12号调整到6号，16号调整到14号，20号调整到13号，15号调整到第二层最左边的位置（即7号登机口的位置）。

【输入形式】

1）首先按层次从根开始依次输入树结点之间的关系。其中分叉结点编号从数字100开始（树根结点编号为100，其它分叉结点编号没有规律但不会重复），登机口为编号小于100的数字（编号没有规律但不会重复，其一定是一个叶结点）。树中结点间关系用下面方式描述：

R S1 S2 S3 -1

其中R为分叉结点，从左至右S1，S2，S3分别为树叉R的子结点，其可为树叉或登机口，由于树的度为3，S1，S2，S3中至多可以2个为空，最后该行以-1和换行符结束。各项间以一个空格分隔。如：

100 101 102 103 -1

表明编号100的树根有三个子叉，编号分别为101、102和103，又如：

104 7 8 -1 

表明树叉104上有2个编号分别为7和8的登机口。

假设分叉结点数不超过100个。分叉结点输入的顺序不确定，但可以确定：输入某个分叉结点信息时，其父结点的信息已经输入。

输入完所有树结点关系后，在新的一行上输入-1表示树结点关系输入完毕。

2）接下来输入登机口的流量信息，每个登机口流量信息分占一行，分别包括登机口编号（1~99之间的整数）和流量（大于0的整数），两整数间以一个空格分隔。登机口数目与前面构造树时的登机机口数目一致。

【输出形式】

按照上述调整规则中排序后的顺序（即按旅客流量由大到小，流量相同的按照登机口编号由小到大）依次分行输出每个登机口的调整结果：先输出调整前的登机口编号，然后输出字符串"->"（由英文减号字符与英文大于字符组成），再输出要调整到的登机口编号。
*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
double eps = 1e-9;
struct node
{
    int type; // 0:分叉节点，1:登机口
    int index; // 编号或登机号
    int flow; // 流量
    struct node *lchild, *mchild, *rchild;
};
typedef struct node* nodeptr;
nodeptr stack[101]; //便于排序
int top = -1;
int my_cmp(const void *a, const void *b)
{
    //排序函数
    //首先按照由大到小的顺序对输入的登机口流量进行排序，流量相同的按照登机口编号由小到大排序
    nodeptr x = *(nodeptr*)a;
    nodeptr y = *(nodeptr*)b;
    if(x->flow != y->flow) return y->flow - x->flow; //降序
    return x->index - y->index; //升序
}
nodeptr find_node(nodeptr root, int index)
{
    //递归实现，寻找分支点，便于插入
    if(root == NULL) return NULL;
    if(root->index == index) return root;
    nodeptr l = find_node(root->lchild, index);
    if(l != NULL) return l;
    nodeptr m = find_node(root->mchild, index);
    if(m != NULL) return m;
    nodeptr r = find_node(root->rchild, index);
    if(r != NULL) return r;
    return NULL;
}
nodeptr create_node(int index)
{
    nodeptr new_node = (nodeptr)malloc(sizeof(struct node));
    new_node->type = (index > 99) ? 0 : 1; // 0:分叉节点，1:登机口
    new_node->index = index;
    new_node->lchild = NULL;
    new_node->mchild = NULL;
    new_node->rchild = NULL;
    if(new_node->type == 1)
    {
        stack[++top] = new_node; // 将登机口节点压入栈
        new_node->flow = 0; // 登机口流量初始化为0
    }
    else
    {
        new_node->flow = 0; // 分叉节点流量为0
    }
    return new_node;
}
nodeptr create_tree()
{
    int index, lindex, mindex, rindex;
    int space;
    nodeptr root = NULL;
    while(1)
    {
        scanf("%d", &index);
        if(index == -1) break;
        nodeptr new_node = create_node(index);//第一遍读入的是结点
        if(root == NULL) root = new_node;
        else
        {
            new_node = find_node(root, index);
            if(new_node == NULL)
            {
                printf("error: parent node not found\n");
                return NULL;
            }
        }
        scanf("%d", &lindex);
        if(lindex == -1) continue;
        nodeptr lchild = create_node(lindex);
        new_node->lchild = lchild;

        scanf("%d", &mindex);
        if(mindex == -1) continue;
        nodeptr mchild = create_node(mindex);
        new_node->mchild = mchild;

        scanf("%d", &rindex);

        if(rindex == -1) continue;
        nodeptr rchild = create_node(rindex);
        new_node->rchild = rchild;
        
        scanf("%d", &space);//三个叉都有，记得读入-1
    }
    return root;
}
void read_flow(nodeptr root)
{
    //读入流量
    int index, flow;
    for(int i = 0; i <= top; i++)
    {
        scanf("%d %d", &index, &flow);
        // if(index == 8)
        // {
        //     printf("index == 8\n");
        // }
        nodeptr node = find_node(root, index);
        if(node == NULL)
        {
            printf("error: node not found\n");
            return;
        }
        node->flow = flow;
    }
}   
nodeptr queue[101]; //便于调整BFS
int front = -1;
int rear = -1;
void push(nodeptr node)
{
    //入队
    if(rear == 100) return;
    queue[++rear] = node;
}
nodeptr pop()
{
    //出队
    if(front == rear) return NULL;
    return queue[++front];
}
void adjust(nodeptr root)
{
    //先排序
    //!注意第二个参数是元素个数
    qsort(stack, top + 1, sizeof(nodeptr), my_cmp);
    //再调整
    //!登机口按照从上到下（安检口在最上方）、从左到右的顺序 层级优先 BFS
    push(root);
    int i = 0; //记录当前调整的登机口 排序后的stack数组
    while(rear != front)
    {
        nodeptr current = pop();
        if(current->type == 1) // 登机口
        {
            printf("%d->%d\n", stack[i++]->index, current->index); //!注意顺序
        }
        //!注意入队的顺序
        if(current->lchild != NULL) push(current->lchild);
        if(current->mchild != NULL) push(current->mchild);
        if(current->rchild != NULL) push(current->rchild);
    }
}
int main()
{
    nodeptr root = create_tree();
    if(root == NULL)
    {
        printf("error: tree creation failed\n");
        return 1;
    }
    //读入流量
    read_flow(root);
    //调整
    adjust(root);
    //释放内存
    for(int i = 0; i <= top; i++)
    {
        free(stack[i]);
    }
    return 0;
}