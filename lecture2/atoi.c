#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
#define Deint(x) printf(#x" = %d\n", x)
#define Dell(x) printf(#x" = %lld\n", x)
#define Delf(x) printf(#x" = %lf\n", x)
#define Deull(x) printf(#x" = %llu\n", x)
#define Destr(x) printf(#x" = %s\n", x)
#define Deint(x) printf(#x" = %d\n", x)
#define Dechar(x) printf(#x" = %c\n", x)
#define De printf("debug\n")
#define loop(l,r) for(int i = l; i <= r; i++)
#define input(i,f) scanf("%(#f)", &(i))
double eps = 1e-9;
char str[] = "\t\v\\\0will\n";
int atoi(const char *str)
{
    int i, n = 0, sign;
    char *p = str;
    // skip white space
    while(*p == ' ' || *p == '\t' || *p == '\n')
        p++;
    // get sign
    sign = 1;
    if(*p == '-')
    {
        sign = -1;
        p++;
    }
    // get number
    while(*p != '\0' && *p >= '0' && *p <= '9')
    {
        n = n * 10 + *p - '0';
        p++;
    }
    return sign * n;
}
int main()
{
    int a[5] = {1,2,3};
    printf("%d\n", strlen(str));
    printf("%d", atoi("1235"));
    return 0;
}
