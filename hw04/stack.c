#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//!不能直接用函数作为栈，需要有一个 index栈
struct function {
    char name[22];
    char call[11][22]; // 每个函数最多调用10个不同函数
    int sum; // 记录调用的不同函数数量
} f[100]; //! 全局函数表，最多100个函数
int func_count = 0; // 当前已注册的函数数量

int stack[200]; //! 栈，保存函数在f数组中的索引
int top = -1;

// 查找函数名对应的索引，不存在返回-1
int find_func(const char *name) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(f[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void push(int index) {
    if (top >= 199) return;
    stack[++top] = index;
}

int pop() {
    if (top < 0) return -1;
    return stack[top--];
}

int isempty() {
    return top == -1;
}

int main() {
    while (1) {
        int op;
        if (scanf("%d", &op) != 1) break;

        if (op == 0) { // 出栈
            if (isempty()) break;
            pop();
        } else if (op == 8) { // 入栈
            char name[22];
            scanf("%s", name);

            // 查找或创建函数
            int index = find_func(name);
            if (index == -1) {//! 没有找到，则创建新函数
                strcpy(f[func_count].name, name);
                f[func_count].sum = 0;
                index = func_count++;
            }

            // 记录调用关系
            if (!isempty()) {
                struct function *caller = &f[stack[top]];
                int exists = 0;
                for (int i = 0; i < caller->sum; i++) {// 检查被caller函数曾经调用过
                    if (strcmp(caller->call[i], name) == 0) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists && caller->sum < 10) {// 没有被caller调用过且未满10个函数
                    strcpy(caller->call[caller->sum++], name);
                }
            }

            push(index); // 压入新函数
        }

        if (isempty()) break; // 栈空时结束输入
    }

    // 输出调用关系
    for (int i = 0; i < func_count; i++) {
        if (f[i].sum > 0) {
            printf("%s:", f[i].name);
            for (int j = 0; j < f[i].sum; j++) {
                printf("%s%c", f[i].call[j], j < f[i].sum-1 ? ',' : '\n'); //! 以后多用这个方式输出结尾
            }
        }
    }

    return 0;
}