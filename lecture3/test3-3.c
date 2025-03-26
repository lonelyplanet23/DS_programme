#include <stdio.h>
int main()  
{
      int a[4] = {1,2,3,4};
      int *p;
      p=&a[2];
      printf("%d ",++*p);
      printf("%d\n",*--p);
} 