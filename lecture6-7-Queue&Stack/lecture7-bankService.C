#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 200       // 队列容量
#define THRESHOLD 7       // 窗口增加阈值
#define MAXSVR 5          // 最大服务窗口数
#define MINSVR 3          // 最小服务窗口数

typedef struct {
    int id;
    int wtime;
} CustType;

// 函数声明
void updateCustqueue();    // 更新等待队列中客户等待时间
void arriveCust();         // 获取新客户并加入队列
int service();             // 从队列获取客户进行服务
void enCustqueue(CustType c); // 客户入队
CustType deCustqueue();     // 客户出队
int getCustnum();          // 获取等待客户人数
int isFull();
int isEmpty();

int main() {
    int clock = 0;
    int simulationtime;
    int Winnum = MINSVR;   // 当前服务窗口数

    scanf("%d", &simulationtime);

    for (clock = 0; ; clock++) {
        // 更新等待时间
        updateCustqueue();

        // 新客户入队，尝试增加窗口
        if (clock <= simulationtime) {
            arriveCust();
        }

        // 处理服务并尝试减少窗口
        if (service() == 0 && clock > simulationtime) {
            break; // 队列空且无新客户
        }
    }

    return 0;
}

/* 以下函数需要自行实现：
updateCustqueue()
arriveCust()
service()
enCustqueue()
deCustqueue()
getCustnum()
isFull()
isEmpty()
*/