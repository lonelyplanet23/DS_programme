#include <stdio.h>
#include <stdlib.h>

// 定义栈结构
typedef struct Stack {
    void** data;      // 存储元素的指针数组
    int capacity;     // 栈的容量
    int top;          // 栈顶指针
} Stack;

// 创建栈
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (void**)malloc(sizeof(void*) * capacity);
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

// 判断栈是否为空
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 判断栈是否已满
int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// 入栈操作
int push(Stack* stack, void* element) {
    if (isFull(stack)) {
        printf("Stack overflow!\n");
        return 0;
    }
    stack->data[++stack->top] = element;
    return 1;
}

// 出栈操作
void* pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        return NULL;
    }
    return stack->data[stack->top--];
}

// 获取栈顶元素
void* peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return NULL;
    }
    return stack->data[stack->top];
}

// 销毁栈
void destroyStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

// 示例使用
typedef struct {
    int id;
    char name[50];
} Student;

int main() {
    Stack* stack = createStack(5);
    
    // 入栈操作
    Student s1 = {1, "Alice"};
    Student s2 = {2, "Bob"};
    push(stack, &s1);
    push(stack, &s2);
    
    // 出栈操作
    Student* s = (Student*)pop(stack);
    printf("Popped: ID=%d, Name=%s\n", s->id, s->name);
    
    destroyStack(stack);
    return 0;
}  