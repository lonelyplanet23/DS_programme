//! 计算前缀表达式的简洁算法：递归实现
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<stack>
using namespace std;
double f(){
    char s[10];
    if(!~scanf("%s",s))exit(0);
    switch(*s){
        case '+':return f()+f();break;
        case '-':return f()-f();break;
        case '/':return f()/f();break;
        case '*':return f()*f();break;
        default:return atof(s);
    }
}
int main(){
    while(1)printf("%.2lf\n",f());
    return 0;
}