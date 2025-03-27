//* 用 C 语言实现图书管理系统，支持录入、查找、删除操作，按书名排序，文件读写，控制台交互，输出格式规范。
//! 输出指定字符宽度的方法！
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define BOOK struct book
int n = 0;
struct book
{
    char name[51];
    char author[21];
    char publisher[31];
    char publish_dates[11];
} books[501];
int mycmp(const void *a, const void *b)
{
    return strcmp(((BOOK*)a)->name, ((BOOK*)b)->name);
}
void input_book(BOOK book)
{
    books[n++] = book;
    qsort(books, n, sizeof(BOOK), mycmp);
}
void output(FILE *out, BOOK book)
{
    fprintf(out, "%-50s%-20s%-30s%-10s\n", book.name, book.author, book.publisher, book.publish_dates);
}
void find_book(char *key)
{
    
    for(int i = 0; i < n; i++)
    {
        if(strstr(books[i].name, key) != NULL)
        {
            printf("%-50s%-20s%-30s%-10s\n", books[i].name, books[i].author, books[i].publisher, books[i].publish_dates);
        }
    }
}
void delete_book(char *key)
{
    int delete[501] = {0};
    int cnt = 0;
    for(int i = 0; i < n; i++)
    {
        if(strstr(books[i].name, key) != NULL)
        {
            delete[i] = 1;
            cnt++;
        }
    }
    for(int i = 0, j = 0; i < n; i++)
    {
        if(delete[i] == 0)
        {
            books[j++] = books[i];
        }
    }
    n -= cnt;
    memset(books + n, 0, sizeof(BOOK) * cnt);
}
int main()
{
    FILE* books_lib = fopen("books.txt", "r");
    FILE* out = fopen("ordered.txt", "w");
    //读取文件，储存每一行的图书信息
    while(~(fscanf(books_lib, "%s %s %s %s", &books[n].name, &books[n].author, &books[n].publisher, &books[n].publish_dates)))
    {
        n++;
    }
    //按照书名排序
    qsort(books, n, sizeof(BOOK), mycmp);
    int op;
    scanf("%d", &op);
    while(op != 0)
    {
        if(op == 1)
        {
            scanf("%s %s %s %s", &books[n].name, &books[n].author, &books[n].publisher, &books[n].publish_dates);
            input_book(books[n]);
        }
        if(op == 2)
        {
            char key[51];
            scanf("%s", key);
            find_book(key);
        }
        if(op == 3)
        {
            char key[51];
            scanf("%s", key);
            delete_book(key);
        }
        scanf("%d", &op);
    }
    for(int i = 0; i < n; i++)
    {
        output(out, books[i]);
    }
    fclose(books_lib);
    fclose(out);
    return 0;
}