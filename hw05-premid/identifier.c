#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
double eps = 1e-9;
char sentence[201];
char id[51][33];
int cnt = 0;
int isIdentifier(char ch)
{
    return isalpha(ch) || isdigit(ch) || ch == '_';
}
void moving(int start)
{
    for(int i = cnt-1; i >= start; i--)
    {
        strcpy(id[i+1], id[i]);
    }
}
void insert(char str[])
{
    if(cnt == 0)
    {
        strcpy(id[0], str);
        cnt++;
        return;
    }
    else if(strcmp(str, id[0]) < 0)
    {
        moving(0);
        strcpy(id[0], str);
        cnt++;
        return;
    }
    int i = 0;
    while(i < cnt && strcmp(str, id[i]) > 0) i++;
    if(i == cnt)
    {
        strcpy(id[i], str);
        cnt++;
        return;
    } 
    if(strcmp(str, id[i]) == 0) return;
    moving(i);
    strcpy(id[i], str);
    cnt++;
    
}
int is_num(char s[])
{
    int len = strlen(s);
    for(int i = 0; i < len; i++)
    {
        if(!isdigit(s[i])) return 0;
    }
    return 1;
}
int main()
{
    fgets(sentence, sizeof(sentence), stdin);
    int len = strlen(sentence);
    for(int i = 0; i < strlen(sentence) && sentence[i] != ';'; i++)
    {
        if(isIdentifier(sentence[i]))
        {
            char keyword[33];
            memset(keyword, 0, sizeof(keyword));
            int k = 1;
            keyword[0] = sentence[i];
            for(i = i+1; isIdentifier(sentence[i]); k++,i++)
            {
               keyword[k] = sentence[i];
            }
            if(is_num(keyword)) continue;
            keyword[k+1] = '\0';
            insert(keyword);
        }
    }
    for(int i = 0; i < cnt; i++)
    {
        printf("%s ", id[i]);
    }

    return 0;
}