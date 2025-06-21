//题目要求：从标准输入中输入一组整数，在输入过程中按照左子结点值小于根结点值、右子结点值大于等于根结点值的方式构造一棵二叉查找树，然后从左至右输出所有树中叶结点的值及高度（根结点的高度为1）。
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
struct node
{
    int data;
    struct node *lchild, *rchild;
};
typedef struct node* nodeptr;
nodeptr create_Tree(int n)
{
    nodeptr root = NULL;
    for(int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        //创建当前结点
        nodeptr p = (nodeptr)malloc(sizeof(struct node));
        p->data = x;
        p->lchild = NULL;
        p->rchild = NULL;
        nodeptr q = root; //q为遍历节点
        while(1)
        {
            if(q == NULL)// 如果q为空，则将当前结点p作为根结点
            {
                root = p; //! 注意要用将当前结点p赋值给root，而不是q
                break;
            }
            if(x < q->data)
            {
                if(q->lchild == NULL) // 如果q的左子树为空，则将当前结点p插入到q的左子树
                {
                    q->lchild = p;
                    break;
                }
                else // 否则遍历节点q进入下一层
                {
                    q = q->lchild;
                }
            }
            else // 如果x >= q->data
            {
                if(q->rchild == NULL) // 如果q的右子树为空，则将当前结点p插入到q的右子树
                {
                    q->rchild = p;
                    break;
                }
                else // 否则遍历节点q进入下一层
                {
                    q = q->rchild;
                }
            }
        }
    }
    return root;
}
void print_leaf(nodeptr root, int h)
{
    // 递归实现，且采用前序遍历
    // 深度优先的方式
    if(root == NULL) return;
    if(root->lchild == NULL && root->rchild == NULL) // 如果当前结点是叶子结点
    {
        printf("%d %d\n", root->data, h);
    }
    else
    {
        print_leaf(root->lchild, h + 1); // 遍历左子树
        print_leaf(root->rchild, h + 1); // 遍历右子树
    }
}
double eps = 1e-9;
int main()
{
    int n;
    scanf("%d", &n);
    nodeptr root = create_Tree(n); 
    print_leaf(root, 1); 
    return 0;
}