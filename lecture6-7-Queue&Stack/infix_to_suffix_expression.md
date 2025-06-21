# 表达式-常见算法
## 概念
**后缀表达式 ：** 
+ **从左向右遍历**
+ **数字：直接进栈**
+ **运算符：出栈两个数字进行运算（后弹出的是左运算数）**
+ **遍历结束，计算结果从栈中弹出**
+ 如果不止一个元素，说明表达式错误。
  
## 中缀转后缀

**（一） 转换规则**
**通过“栈”来实现！**
1. 数字，直接输出，
2. 若是 `+ - * /` 比较该运算符`op`和栈顶运算符`top`，输出优先级高于该运算符`op`的符号`top`，直到遇到优先级低时，压入栈中。
3. 对于`()`而言：左括号压入栈，右括号`)`，直接弹出栈顶元素并输出，直到遇到`(`，但不输出（后缀不需要括号）。
**（二）伪代码**
```C
int toSuffixExpr() {
    struct Symbol sym = getSym();
    while (sym.symType != EQ) {
        if (sym.symType == NUM) {  //case:数字
            printf("%s ", sym.str);
        }else if (sym.symType == OP && sym.opn != RIGHT) {  //case:非右括号
            while (opPri[sym.opn] <= opPri[topOp()] && topOp() != LEFT)
                printf("%c ", opCh[popOp()]);
            pushOp(sym.opn);
        }else if (sym.symType == OP && sym.opn == RIGHT) {  //case:右括号
            enum Oper t;
            while ((t = popOp()) != LEFT)
                printf("%c ", opCh[t]);
        }else {  //case:其他异常情况
            printf("Error in the expression!\n");
            return 1;
        }
        sym = getSym();  //读取下一个符号/数值
    }
    while (Otop >= 0)  //将栈中所有运算符弹出计算或输出
        printf("%c ", opCh[popOp()]);
    return 0;
}
```
