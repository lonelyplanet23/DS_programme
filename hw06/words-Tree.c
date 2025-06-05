#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001

// 定义二叉排序树节点
typedef struct TreeNode {
    char word[101]; // 单词
    int count;      // 出现次数
    struct TreeNode *left, *right; // 左右子节点
} TreeNode;

// 创建新节点
TreeNode* createNode(const char *word) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(node->word, word);
    node->count = 1;
    node->left = node->right = NULL;
    return node;
}

// 插入单词到二叉排序树
TreeNode* insert(TreeNode *root, const char *word) {
    if (root == NULL) {
        return createNode(word);
    }
    int cmp = strcmp(word, root->word);
    if (cmp == 0) {
        root->count++; // 单词已存在，计数加1
    } else if (cmp < 0) {
        root->left = insert(root->left, word); // 插入左子树
    } else {
        root->right = insert(root->right, word); // 插入右子树
    }
    return root;
}

// 中序遍历输出单词及其出现次数
void inorder(TreeNode *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%s %d\n", root->word, root->count);
    inorder(root->right);
}

// 输出根节点及其右节点
void printRootAndRight(TreeNode *root) {
    if (root == NULL) return;
    printf("%s", root->word);
    if (root->right != NULL) {
        printf(" %s", root->right->word);
        if (root->right->right != NULL) {
            printf(" %s", root->right->right->word);
        }
    }
    printf("\n");
}

// 释放二叉排序树
void freeTree(TreeNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// 将字符串转换为小写
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// 从文件中读取单词
TreeNode* readWordsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }

    TreeNode *root = NULL;
    char word[101];
    char ch;
    int index = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            word[index++] = tolower(ch); // 转为小写并存储
        } else {
            if (index > 0) {
                word[index] = '\0'; // 结束当前单词
                root = insert(root, word); // 插入到二叉排序树
                index = 0; // 重置索引
            }
        }
    }
    // 处理文件末尾的最后一个单词
    if (index > 0) {
        word[index] = '\0';
        root = insert(root, word);
    }

    fclose(file);
    return root;
}

int main() {
    TreeNode *root = readWordsFromFile("article.txt");
    printRootAndRight(root);
    inorder(root);
    freeTree(root);

    return 0;
}