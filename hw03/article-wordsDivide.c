#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
double eps = 1e-9;
char words_in_process[20];
typedef struct node
{
    char words[20];
    int cnt;
    struct node *next;
} *nodeptr;
void words(char* str)
{
    //剔除首尾的符号（空格、换行符不包含）
    int i = 0, j;
    int len = strlen(str);
    for(; i < len && !isalpha(str[i]); i++); //!边界条件
    for(j = i; j < len &&isalpha(str[j]); j++); 
    //static char words[20]; //!需要转化为静态数组
    memset(words_in_process, 0, sizeof(words_in_process));
    int t = 0;
    for(int k = i; k < j; k++, t++)
    {
        //包含大写字母的单词应将大写字母转换为小写字母后统计。
        if(isupper(str[k]))
        {
            str[k] = tolower(str[k]);
        }
        words_in_process[t] = str[k];
    }
    words_in_process[t] = '\0'; //字符串结束符
    //return words;//!错误，局部变量被释放了
}
nodeptr insert_in_order(nodeptr head, nodeptr src)
{ 
    //以字母顺序，插入到合适的位置 src不为空
    nodeptr p = head, newhead = head;
    if(head == NULL) return src; //!头结点为空，直接返回src
    if(strcmp(p->words, src->words) > 0)
    {
        //头插
        src->next = head;
        p = src;
        return p;
    }
    if(strcmp(p->words, src->words) == 0) //头结点单词一样
    {
        p->cnt++;
        return newhead;
    }
    //头结点单词不一样，且小于src，继续往下找
    while(p->next != NULL && strcmp(p->next->words, src->words) < 0)
    {
        p = p->next;
    }
    if(p->next != NULL && strcmp(p->next->words, src->words) == 0) //下一个结点单词一样
    {
        p->next->cnt++;
        return newhead;
    }
    //下一个单词结点与待插入结点不同（或者是空），肯定是大了，插入到p后面
    if(p->next != NULL) src->next = p->next; //如果不是尾部，再连一条
    p->next = src; //插入到p后面
    return newhead;
}
//!获取单词的函数，返回一个链表，单词按字母顺序排列
nodeptr create_list() {
    nodeptr head = NULL, q;
    char line[1024]; // 用于存储一行内容
    char *token;

    while (fgets(line, sizeof(line), stdin)) {
        // 使用 strtok 分割单词，按非字母字符分割
        token = strtok(line, " \t\n-.,!?;:\"()[]{}<>");
        while(token != NULL){
            words(token); // 处理单词
            if (strlen(words_in_process) > 0) { //!防御性编程
                q = (nodeptr)malloc(sizeof(struct node));
                strcpy(q->words, words_in_process); // 深拷贝
                q->next = NULL;
                q->cnt = 1;
                head = insert_in_order(head, q);
            }
            token = strtok(NULL, " \t\n-.,!?;:\"()[]{}<>"); // 获取下一个单词
        }
    }

    return head;
}
void print_list(nodeptr head)
{
    if(head == NULL) return;
    nodeptr p = head;
    while(p != NULL)
    {
        printf("%s %d\n", p->words, p->cnt);
        p = p->next;
    }
}
void free_list(nodeptr head) {
    nodeptr p = head;
    while (p != NULL) {
        nodeptr temp = p;
        p = p->next;
        free(temp);
    }
}
int main()
{
    freopen("article.txt", "rb", stdin);
    nodeptr head = create_list();
    print_list(head);
    fclose(stdin);
    free_list(head);
    return 0;
}