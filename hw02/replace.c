#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
#define MAXLINE 1024
double eps = 1e-9;
char new[1000], old[1000];
char line[1024];//读取的一行
char line_tolower[1024];
char result[1024]; //被替换后的一行
void my_toLower(char *str, char *des)
{
    char *p = str;
    char *q = des;
    while(*p != '\0')
    {
        if(*p >= 'A' && *p <= 'Z')
        {
            *q = *p - 'A' + 'a';
        }
        else *q = *p;
        p++;
        q++;
    }
    *q = '\0';
}
int main()
{
    FILE * in;
    FILE * out;
    in = fopen("filein.txt","r");
    out = fopen("fileout.txt", "w"); //第二个参数
    scanf("%s", old);
    scanf("%s", new);
    my_toLower(old,old);
    while(fgets(line, MAXLINE-1, in) != NULL) // 什么都没读到为空，每次执行时，文件指针自动后移
    {
        memset(result, 0, sizeof(result));
        my_toLower(line, line_tolower);
        char *replace_str = line_tolower; //库函数，找到匹配位置
        char *q = result;//新建一个被替换后的字符串，目前是空
        char *p = line;
        while(*replace_str != '\0' && *replace_str != '\n')
        {
            if(strstr(replace_str, old) == replace_str)//此时接下来几个字母恰好是被替换的单词
            {
                strcpy(q, new);
                replace_str += strlen(old);
                q += strlen(new); // 指针后移替换量
                p += strlen(old);
            }
            else
            {
                *q++ = *p++;//如果没有读到，那就复制原字符串即可
                replace_str++;
            }
        }
        fprintf(out, "%s\n", result);//等同于printf,只不过写进了文件。
    }
    fclose(in);
    fclose(out);//记得关闭！
    return 0;
}