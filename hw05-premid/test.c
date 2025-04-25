#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
double eps = 1e-9;
int main()
{
    char ch[] = "600";
    int a, s = 0;
    for(a = 0; ch[a] >= '0' && ch[a] <= '9'; a++)
    {
        s = 10 * s + ch[a] - '0';
    }
    printf("%d", s);
    return 0;
}
/*
    1 3 5 7 9 11 13 15 17 19  %2 = 1
    1 5 9 13 17 19 %4 = 1
    1 9 17  %8 = 1 
    1 17 %16 = 1
    1 
*/