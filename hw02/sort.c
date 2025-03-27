//读取一组电话号码簿（由姓名和手机号码组成），将重复出现的项删除（姓名和电话号码都相同的项为重复项，只保留第一次出现的项），
//并对姓名相同手机号码不同的项进行如下整理：首次出现的项不作处理，第一次重复的姓名后面加英文下划线字符_和数字1，第二次重复的姓名后面加英文下划线字符_和数字2，依次类推
//号码簿中姓名相同的项数最多不超过10个。最后对整理后的电话号码簿按照姓名进行从小到大排序，并输出排序后的电话号码簿。
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
double eps = 1e-9;
struct phone
{
    char name[50];
    char number[50];
    int cnt;
}  address[100];

int cmp(const void *a, const void *b)
{
    struct phone *c = (struct phone *)a;
    struct phone *d = (struct phone *)b;
    return strcmp(c->name, d->name);
}
int main()
{
    int n;
    scanf("%d", &n);
    int all = 0;
    for(int i = 0; i < n; i++)
    {
        //!如何优化程序，使得不用每一步进行排序
        
        struct phone input;
        scanf("%s %s", input.name, input.number);
        struct phone *find = (struct phone *) bsearch(&input, address, all, sizeof(struct phone), cmp);
        if(find == NULL)
        {
            address[all++] = input;
            address[all-1].cnt = 0;
            qsort(address, all, sizeof(struct phone), cmp);
        }
        else
        {
            if(strcmp(find->number,input.number) != 0)
            {
                //printf("find->number = %s, find->name = %s, find->cnt = %d\n", find->number, find->name, find->cnt);
                find->cnt++;
                sprintf(input.name, "%s_%d", find->name, find->cnt);
                address[all++] = input;
                address[all-1].cnt = find->cnt;
                qsort(address, all, sizeof(struct phone), cmp);
            }
        }
    }
    qsort(address, all, sizeof(struct phone), cmp);
    for(int i = 0; i < all; i++)
    {
        printf("%s %s\n", address[i].name, address[i].number);
    }
    return 0;
}