#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
double eps = 1e-9;
char table[3500][21];
int n = 0;
//索引表 字母 起始位置 单词个数
struct index
{
    char letter;
    int start_pos;
    int cnt;
} index_list[30];

/*读取单词表*/
void init_index()
{
    for(int i = 0; i < 26; i++)
    {
        index_list[i].letter = 'a' + i;
        index_list[i].start_pos = -1;
        index_list[i].cnt = 0;
    }
}
void read();

/*顺序查找*/
void find_in_order(char str[])
{
    int i = 0;
    while(strcmp(str, table[i]) > 0) i++;
    if(strcmp(str, table[i]) == 0)
    {
        printf("1 %d\n", i+1);
        return ;
    }
    printf("0 %d\n", i+1);
}

void binary_search(char str[])
{
    int l = 0, r = n;
    int cnt = 0;
    while(l <= r)
    {
        int mid = (l + r) / 2;
        cnt++;
        if(strcmp(str, table[mid]) == 0)
        {
            printf("1 %d\n", cnt);
            return;
        }
        else if(strcmp(str, table[mid]) < 0)
            r = mid - 1;
        else if (strcmp(str, table[mid]) > 0)
            l = mid + 1;
    }
    printf("0 %d\n", cnt);
}

//分块查找
void upgrade_binary_search(char str[])
{
    int index = str[0] - 'a';
    int cnt = 0;
    int l = index_list[index].start_pos;
    int r = index_list[index].start_pos + index_list[index].cnt - 1;
    while(l <= r)
    {
        int mid = (l + r) / 2;
        cnt++;
        if(strcmp(str, table[mid]) == 0)
        {
            printf("1 %d\n", cnt);
            return;
        }
        else if(strcmp(str, table[mid]) < 0)
            r = mid - 1;
        else if (strcmp(str, table[mid]) > 0)
            l = mid + 1;
    }
    printf("0 %d\n", cnt);    
}

/* compute hash value for string */
#define NHASH  3001
#define MULT  37
unsigned int hash(char *str)
{
       unsigned int h=0;
       char *p;
       for(p=str; *p!='\0'; p++)

              h = MULT*h + *p;

       return h % NHASH;
}

struct words
{
    char str[21];
    struct words *next;
};
typedef struct words *wordptr;
//创建hash表，构建成指针数组
wordptr hash_list[3500];

void init_hash()
{
    for(int i = 0; i < NHASH; i++)
    {
        hash_list[i] = NULL;
    }
}
void insert_hash(char str[])
{
    unsigned int h = hash(str);
    //空
    if(hash_list[h] == NULL)
    {
        wordptr p = malloc(sizeof(struct words));
        strcpy(p->str, str);
        p->next = NULL;
        hash_list[h] = p;
    }
    else //有结点了 插入尾段。
    {
        wordptr new = malloc(sizeof(struct words));
        strcpy(new->str, str);
        new->next = NULL;

        wordptr p = hash_list[h];
        while(p->next != NULL) p = p->next;
        p->next = new;
    }
}
void find_hash(char str[])
{
    unsigned int h = hash(str);
    int cnt = 0;
    if(hash_list[h] == NULL)
    {
        printf("0 %d\n", cnt);
        return;
    }
    wordptr p = hash_list[h];
    for(; p != NULL && strcmp(p->str, str) <= 0; p = p->next)
    {
        cnt++;
        if(strcmp(p->str, str) == 0)
        {
            printf("1 %d\n", cnt);
            return;
        }
    }
    if(p != NULL && strcmp(p->str, str) > 0) cnt++; // 多比较了一次
    printf("0 %d\n", cnt);
}

int main()
{   
    init_hash();
    read();
    char str[30];
    int mode;
    while(~scanf("%s %d", str, &mode))
    {
        switch (mode)
        {
            case 1:
                find_in_order(str);
                break;
            case 2:
                binary_search(str);
                break;
            case 3:
                upgrade_binary_search(str);
                break;
            case 4:
                find_hash(str);
                break;
            default:
                printf("Invalid mode\n");
        }
    }
    return 0;
}

void read()
{
    FILE* dict = fopen("dictionary3000.txt", "rb");
    init_index();
    int i = -1;
    //使用scanf fscanf 避免换行符问题
    while(~fscanf(dict, "%s", table[++i]))
    {
        int index = table[i][0] - 'a';
        index_list[index].cnt++;
        if(index_list[index].start_pos == -1)
        {
            index_list[index].start_pos = i;
        }
        insert_hash(table[i]);
    }
    n = i;
    fclose(dict);
}
