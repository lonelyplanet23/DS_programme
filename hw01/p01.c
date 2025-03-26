#include <stdio.h>
long fib(int x)
{
 switch(x)
 {
  case 0: return 0;
  case 1:
  case 2:  return 1;
 }
 return (fib(x-1)+fib(x-2));
}
int main()
{
 int x=6;
 printf("%d\n",fib(x));

 return 0;
}