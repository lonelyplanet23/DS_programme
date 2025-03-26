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
int check(char ch)
{
    if(ch >= 'a' && ch <= 'z')
    {
        return 1;
    }
    if(ch >= 'A' && ch <= 'Z')
    {
        return 2;
    }
    if(ch >= '0' && ch <= '9')
    {
        return 3;
    }
}
int main()
{
    char input[1000];
    scanf("%s", input);
    int len = strlen(input);
    printf("%c", input[0]);
    for(int i = 1; i < len-1; i++)
    {
        if(input[i] == '-')
        {
            if((check(input[i-1]) == check(input[i+1])) && input[i-1] < input[i+1])
            {
                for(char ch = input[i-1]+1; ch < input[i+1]; ch++)
                {
                    printf("%c", ch);
                }
            }
            else
            {
                printf("%c", input[i]);
            }
        }
        else
        {
            printf("%c", input[i]);
        }
    } 
    printf("%c", input[len-1]);
    return 0;
}