//��дһ������ʵ�ֱ���������̳�����վ����·��ѯ������Ϊ��ʼվ����Ŀ��վ�������Ϊ����ʼվ��Ŀ��վ����̳���վ������·��

//ע��1. Ҫ�����Dijkstra�㷨ʵ�֣�2�������վ����ڶ������·�����ҳ����е�һ�����ɡ�
//�ļ�bgstations.txtΪ�����ļ�
/*
�������ʼվ��Ŀ��վ�ĳ�����Ϣ��Ҫ�����վ�����١�������Ϣ��ʽ���£�

SSN-n1(m1)-S1-n2(m2)-...-ESN

���У�SSN��ESN�ֱ�Ϊ��ʼվ����Ŀ��վ����nΪ�����ĵ�����·�ţ�mΪ����վ���������ַ�����Ӣ���ַ���
*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
//�����ڽӱ�
int n = 0, m; //nΪվ������mΪ��·��
struct edge {
    int index; //!�����ڵ���·���
    int to;
    struct edge *next;
};
typedef struct edge* Edge; //�ߵ�ָ������
typedef struct node {
    char name[20]; //վ��
    int transfer; //���˱��
    Edge edges; //�ߵ�����
} Node;
Node graph[405]; //ͼ���ڽӱ��ʾ
int visited[405]; //���ʱ��
int path[405]; //�洢·��

int my_cmp(const void* a, const void* b) 
{
    return strcmp(((Node*)a)->name, ((Node*)b)->name);
} //�ȽϺ���������bsearch
void my_cpy(Node* a, Node *b) 
{
    strcpy(a->name, b->name); //����վ��
    a->transfer = b->transfer; //���ƻ��˱��
    a->edges = NULL; //��ʼ��������Ϊ��
} 

Edge insert_edge(Node node, int to, int index)
{
    Edge new_edge = (Edge)malloc(sizeof(struct edge));
    new_edge->index = index;
    new_edge->to = to;
    new_edge->next = NULL;
    if (node.edges == NULL) 
    {
        node.edges = new_edge; //���û�бߣ�ֱ�Ӳ���
    } 
    else 
    {
        Edge p = node.edges;
        while (p->next != NULL) {
            p = p->next; //�ҵ���������һ���ڵ�
        }
        p->next = new_edge; //�����±�
    }
    return node.edges; 
}


void Create_list(FILE* fp)
{
    char line[100];
    int index = 0;
    fscanf(fp, "%d\n", &m); //��ȡվ��������·��

    //һ����·һ����·�Ķ�ȡ
    while(fgets(line, sizeof(line), fp) != NULL) 
    {
        int line_index, tot; //��·��ź�վ����
        sscanf(line, "%d %d", &line_index, &tot); //��ȡ��·��� վ����
        if(line[0] == '\n' || line[0] == '\r') continue; 
        Node current, prev; //��ǰվ��ǰһվ
        for(int i = 0; i < tot; i++)
        {
            fgets(line, sizeof(line), fp); //��ȡվ��
            char line_name[20];
            int transfer;
            sscanf(line, "%s %d", line_name, transfer); //��ȡվ��

            //������ǰվ���
            Node current;
            strcpy(current.name, line_name); //�洢վ��
            current.transfer = transfer; //�洢���˱��
            current.edges = NULL; //��ʼ��������Ϊ��

            Node *found = (Node*)bsearch(line_name, graph, n, sizeof(Node), my_cmp); //���ֲ���վ��
            int found_index = found ? (found - graph) : -1; //�ҵ���վ������
            //���û���ҵ���˵������վ��
            if(found == NULL)
            {
                 my_cpy(&graph[n++], &current); 
                 found_index = n - 1; //��վ�������
            }
            
            // ����ǵ�һ������һվ��Ϊǰһվ
            if(i == 0)
            {
                my_cpy(&prev, &current);
                continue;
            }

            //�����
            //!ע����N-1
            Edge new_edge = insert_edge(prev, n - 1, line_index); //��ǰһվ�͵�ǰվ����

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