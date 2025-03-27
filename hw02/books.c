#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
#define BOOK struct book
double eps = 1e-9;
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
    qsort(books, n-1, sizeof(BOOK), mycmp);
    // int left = 0;
    // int right = n - 1; 
    // int mid;
    // while(left <= right)
    // {
    //     mid = (right + left) / 2;
    //     if(mycmp(&books[mid], &book) < 0)
    //     {
    //         left = mid + 1;
    //     }
    //     else if(mycmp(&books[mid], &book) > 0)
    //     {
    //         right = mid - 1;
    //     }
    // }
}
void find_book(BOOK book);
void delete_book(BOOK book)
{
    n--;
    for(int)
}
int main()
{
    FILE* books_lib = fopen("books.txt", "r");
    FILE* out = fopen("ordered.txt", "w");
    //读取文件，储存每一行的图书信息
    while(~(scanf("%s %s %s %s", &books[n].name, &books[n].author, &books[n].publisher, &books[n].publish_dates)))
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

        }
        if(op == 2)
        {

        }
        if(op == 3)
        {

        }
        scanf("%d", &op);
    }

    return 0;
}