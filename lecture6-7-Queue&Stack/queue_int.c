#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 队列结构
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

// 初始化队列
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

// 判断队列是否为空
int isEmpty(Queue* q) {
    return q->rear < q->front;
}

// 判断队列是否已满
int isFull(Queue* q) {
    return q->rear == MAX_SIZE - 1;
}

// 入队
void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue overflow!\n");
        return;
    }
    q->data[++(q->rear)] = value;
}

// 出队
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow!\n");
        return -1;
    }
    return q->data[(q->front)++];
}

// 获取队头元素
int peek(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->data[q->front];
}

// 示例使用
int main() {
    Queue q;
    initQueue(&q);
    
    enqueue(&q, 10);
    enqueue(&q, 20);
    printf("Front: %d\n", peek(&q)); // 输出10
    printf("Dequeue: %d\n", dequeue(&q)); // 输出10
    printf("Dequeue: %d\n", dequeue(&q)); // 输出20
    
    return 0;
}    