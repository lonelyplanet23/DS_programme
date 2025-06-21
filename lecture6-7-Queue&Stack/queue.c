#include <stdio.h>
#include <stdlib.h>

// 定义队列结构
typedef struct Queue {
    void** data;      // 存储元素的指针数组
    int capacity;     // 队列容量
    int front;        // 队头指针
    int rear;         // 队尾指针
    int count;        // 当前元素数量
} Queue;

// 创建队列
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (void**)malloc(sizeof(void*) * capacity);
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
    return queue;
}

// 判断队列是否为空
int isEmpty(Queue* queue) {
    return queue->count == 0;
}

// 判断队列是否已满
int isFull(Queue* queue) {
    return queue->count == queue->capacity;
}

// 入队操作
int enqueue(Queue* queue, void* element) {
    if (isFull(queue)) {
        printf("Queue overflow!\n");
        return 0;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = element;
    queue->count++;
    return 1;
}

// 出队操作
void* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow!\n");
        return NULL;
    }
    void* element = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->count--;
    return element;
}

// 获取队头元素
void* peek(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return NULL;
    }
    return queue->data[queue->front];
}
typedef struct {
    int id;
    char name[50];
} Person;

int main() {
    Queue* queue = createQueue(5);
    
    // 入队操作
    Person p1 = {1, "Charlie"};
    Person p2 = {2, "David"};
    enqueue(queue, &p1);
    enqueue(queue, &p2);
    
    // 出队操作
    Person* p = (Person*)dequeue(queue);
    printf("Dequeued: ID=%d, Name=%s\n", p->id, p->name);
    
    return 0;
}  