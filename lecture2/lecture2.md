## Lecture 2
### 数组
1. 初始化与设置
   1. 初始化的方式：类型 名称[元素个数] = {a,b,c,...} 
   2. 元素个数可以指定也可以不指定，但若指定，个数不能超过指定的数
>  `char str[5] = "hello"`是错误的,这个例子中`\0`也占一位
   4. 初始化为零的方式 `int a[5] = {0}`
   5. **字符串最后以`\0`结尾** 总内存空间：字符字数+1
   6. **数组不能直接赋值！！**
> 转义符号 \数字、符号 把后面的转化成ASCII码所对值
```C
    char str[] = "\t\v\\\0will\n";
    printf("%d", strlen(str));
```
 > 输出结果：3 （到`\0`结束）

 >注意：填空题标准：英文半角，符合语法，不要多加东西
 ### 字符串
 1. 朴素的字符串匹配算法 O(n*m)
 2. KMP算法：分析子串，建立回退幅度表，减少回退幅度（朴素算法中回到开始的下一个位置）
    + i不回退，j回退几步
 3. 大小写无关匹配？全部转换为大写OR小写
### 宏定义
1.  define constant`#define PI 3.14`
2.  define constant func like `#define func(A,B)(...)`
3.  参数用括号括起来，**参数间不能有空格**
### 指针
1. 使用任何指针前，必须先给它**赋一个所指合法对象的地址值**！
```C
    int x = 1;
    int *px;
    px = x;
```
```C
    char *string;
    scanf("%s", string);;
    strcpy(string,"hello");
```
+ 上面二者都是错误的
2. 指针的赋值：
    1. 通过`&`取地址符
    2. 赋值给同类型指针
        + `char *s = "hello"` 字符串常量也可以！
    3. 使用malloc calloc函数为指针分配空间