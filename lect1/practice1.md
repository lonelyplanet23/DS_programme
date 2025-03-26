1. 字符数组：
   1. 不可以用数组名直接赋值，除非用`` char * strcpy ( char * destination, const char * source ); ``
   2. 长度定义有限，不能超过长度，否则可以直接`char[] = "XXXXX"`
   3.` char c[]="\t\v\\\0will\n";` 长度为3
