#include <stdio.h>
void swap(int *p, int *q)
{
         int *t;
         t=p;
         p=q;
         q=t;
}
int main()  
{
          int a=10,b=20;
       
          swap(&a,&b);
           printf("a=%d,b=%d\n",a,b);
}