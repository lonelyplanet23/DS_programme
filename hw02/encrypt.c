#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
double eps = 1e-9;
char s[50],t[200];
int used[200];
char encrypt[200];
void remove_duplicate(char *s)
{
    char *p = s;
    while(*s != '\0')
    {
        if(used[*s] == 0)
        {
            used[*s] = 1;
            *p = *s;
            p++;
        }
        s++;
    }
    *p = '\0';
}
void generate_encrypt(char *s)
{
    int n = strlen(s);
    for(int i = n, k = 26; i < 26; i++, k--)
    {
        if(used[k + 'a' - 1] == 0)
        {
            s[i] = k + 'a' - 1;
        }
        else i--;
    }
    s[26] = '\0';
    for(int i = 0; i < 26; i++)
    {
        encrypt[i + 'a'] = s[i];
    }
}
int main()
{
    FILE *f = fopen("encrypt.txt", "r");
    FILE *g = fopen("output.txt", "w");
    scanf("%s", s); 
    fgets(t, 200, f);
    int m = strlen(t);
    remove_duplicate(s);
    int n = strlen(s);
    generate_encrypt(s);
    for(int i = 0; i < m; i++)
    {
        if(isalpha(t[i]))
        {
            fprintf(g,"%c", encrypt[t[i]]);
        }
        else
        {
            fprintf(g,"%c", t[i]);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}