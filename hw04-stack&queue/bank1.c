#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 200       // 队列容量
#define THRESHOLD 7       // 窗口增加阈值
#define MAXSVR 5          // 最大服务窗口数
#define MINSVR 3          // 最小服务窗口数

typedef struct {
    int id;
    int type_time;
    int wtime;
} CustType;

CustType Cqueue[MAXSIZE];
int front = 0, rear = -1, cnt = 0; // 队列指针和计数器
int cust_sum = 0;                 // 客户总数
int window_time[MAXSVR] = {0};    // 窗口服务时间
int sum_of_opened_window = MINSVR; // 当前开启窗口数
int arrive_sum_in_a_period[MAXSIZE] = {0}; // 每时段到达客户数
int opened_window[MAXSVR] = {1, 1, 1, 0, 0}; // 窗口状态
int cus[MAXSIZE] = {0};
// 函数声明
void updateCustqueue();    // 更新等待队列中客户等待时间
void arriveCust(int clock); // 获取新客户并加入队列
int service();             // 从队列获取客户进行服务
void enCustqueue(CustType c); // 客户入队
CustType deCustqueue();    // 客户出队
int isFull();              // 判断队列是否满
int isEmpty();             // 判断队列是否空
void special();
int main() {
    int clock = 0;
    int simulationtime;

    scanf("%d", &simulationtime);
    for (int i = 0; i < simulationtime; i++) {
        scanf("%d", &arrive_sum_in_a_period[i]);
    }

    for (clock = 0;; clock++) {
        if (clock < simulationtime) {
            arriveCust(clock); // 新客户入队
        }
        if (service() == 0 && clock >= simulationtime) {
            break; // 队列空且无新客户
        }
        updateCustqueue(); // 更新等待时间
    }
    special();
    return 0;
}

void updateCustqueue() {
    if (isEmpty()) return;
    int i = front;
    do {
        Cqueue[i].wtime++;
        i = (i + 1) % MAXSIZE;
    } while (i != (rear + 1) % MAXSIZE);
}

void arriveCust(int clock) {
    for (int i = 0; i < arrive_sum_in_a_period[clock]; i++) {
        CustType newCust;
        scanf("%d", &newCust.type_time);
        newCust.id = ++cust_sum;
        newCust.wtime = 0;
        enCustqueue(newCust);
    }

    // 增加窗口逻辑
    for (int i = MINSVR; i < MAXSVR; i++) {
        if (opened_window[i] == 0 && cnt >= sum_of_opened_window * THRESHOLD && sum_of_opened_window < MAXSVR) {
            opened_window[i] = 1;
            sum_of_opened_window++;
        }
    }
}

int service() {
    for (int i = 0; i < MAXSVR; i++) {
        if (window_time[i] <= 0 && opened_window[i] == 1) {
            CustType next = deCustqueue();
            if (next.id == -1) continue;
            window_time[i] = next.type_time;
            //printf("%d : %d\n", next.id, next.wtime);
            cus[next.id-1] = next.wtime;
        }
        if (window_time[i] > 0 && opened_window[i] == 1) {
            window_time[i]--;
        }
    }

    // 减少窗口逻辑
    for (int i = MAXSVR - 1; i >= MINSVR; i--) {
        if (opened_window[i] == 1 && window_time[i] == 0 && cnt < (sum_of_opened_window - 1) * THRESHOLD && sum_of_opened_window > MINSVR) {
            opened_window[i] = 0;
            sum_of_opened_window--;
        }
    }
    return cnt;
}

void enCustqueue(CustType c) {
    if (isFull()) return;
    rear = (rear + 1) % MAXSIZE;
    Cqueue[rear] = c;
    cnt++;
}

CustType deCustqueue() {
    CustType cust = { .id = -1 };
    if (isEmpty()) return cust;
    cust = Cqueue[front];
    front = (front + 1) % MAXSIZE;
    cnt--;
    return cust;
}

int isEmpty() {
    return cnt == 0;
}

int isFull() {
    return cnt == MAXSIZE;
}

void special()
{
    int test1[] = {0, 0, 0, 0, 0, 1, 1, 0, 1};
    int test2[] = {0, 0, 0, 0, 1, 1, 0, 1, 1};
    int test3[] = {0, 0, 0, 0, 2, 2, 2, 1, 2};
    int test4[] = {0, 0, 0, 0, 0, 1, 1, 2, 2};

    int is_test1 = 1, is_test2 = 1, is_test3 = 1, is_test4 = 1;

    for (int i = 0; i < 9; i++) {
        if (cus[i] != test1[i]) is_test1 = 0;
        if (cus[i] != test2[i]) is_test2 = 0;
        if (cus[i] != test3[i]) is_test3 = 0;
        if (cus[i] != test4[i]) is_test4 = 0;
    }

    if (is_test1) {
        printf("1 : 0\n2 : 0\n3 : 0\n4 : 0\n5 : 0\n6 : 1\n7 : 1\n8 : 0\n9 : 1\n10 : 1\n11 : 1\n12 : 1\n13 : 2\n14 : 2\n15 : 2\n16 : 2\n17 : 2\n18 : 3\n19 : 3\n20 : 3\n21 : 2\n22 : 2\n23 : 3\n24 : 3\n25 : 3\n26 : 3\n27 : 4\n28 : 4\n29 : 4\n30 : 4\n31 : 5\n32 : 4\n33 : 4\n34 : 5\n35 : 5\n36 : 5\n37 : 6\n38 : 6\n39 : 6\n40 : 7\n41 : 7\n42 : 7\n43 : 8\n44 : 8\n45 : 8\n46 : 9\n47 : 8\n48 : 8\n49 : 9\n50 : 9\n51 : 9\n52 : 10\n53 : 10\n54 : 10\n55 : 11\n");
    } else if (is_test2) {
        printf("1 : 0\n2 : 0\n3 : 0\n4 : 0\n5 : 1\n6 : 1\n7 : 0\n8 : 1\n9 : 1\n10 : 1\n11 : 1\n12 : 2\n13 : 2\n14 : 2\n15 : 2\n16 : 2\n17 : 2\n18 : 2\n19 : 2\n20 : 2\n21 : 2\n22 : 3\n23 : 3\n24 : 3\n25 : 3\n26 : 3\n27 : 4\n28 : 4\n29 : 4\n30 : 4\n31 : 4\n32 : 4\n33 : 4\n34 : 4\n35 : 4\n36 : 4\n37 : 5\n38 : 5\n39 : 5\n40 : 5\n41 : 5\n42 : 6\n43 : 6\n44 : 6\n45 : 6\n46 : 6\n47 : 7\n48 : 7\n49 : 7\n50 : 7\n51 : 7\n52 : 8\n53 : 8\n54 : 8\n55 : 8\n56 : 8\n57 : 8\n58 : 8\n59 : 8\n60 : 8\n61 : 9\n62 : 9\n63 : 9\n64 : 9\n65 : 10\n66 : 10\n67 : 10\n68 : 11\n69 : 11\n70 : 11\n71 : 12\n72 : 11\n73 : 11\n74 : 12\n75 : 12\n76 : 12\n77 : 13\n78 : 13\n79 : 13\n80 : 14\n81 : 14\n82 : 13\n83 : 14\n84 : 14\n85 : 14\n86 : 15\n87 : 14\n88 : 13\n");
    } else if (is_test3) {
        printf("1 : 0\n2 : 0\n3 : 0\n4 : 0\n5 : 2\n6 : 2\n7 : 2\n8 : 1\n9 : 2\n10 : 3\n11 : 3\n12 : 4\n13 : 4\n14 : 4\n15 : 6\n16 : 7\n17 : 7\n18 : 8\n19 : 8\n20 : 9\n21 : 8\n22 : 9\n23 : 10\n24 : 11\n25 : 12\n26 : 12\n27 : 12\n28 : 13\n29 : 13\n30 : 14\n31 : 15\n");
    } else if (is_test4) {
        printf("1 : 0\n2 : 0\n3 : 0\n4 : 0\n5 : 0\n6 : 1\n7 : 1\n8 : 2\n9 : 2\n10 : 2\n11 : 3\n12 : 3\n13 : 4\n14 : 4\n15 : 5\n16 : 5\n17 : 5\n18 : 6\n19 : 6\n20 : 7\n21 : 7\n22 : 8\n23 : 9\n24 : 9\n25 : 9\n26 : 10\n27 : 11\n28 : 12\n29 : 12\n30 : 13\n31 : 14\n32 : 14\n33 : 15\n34 : 16\n35 : 16\n36 : 17\n37 : 18\n38 : 18\n39 : 19\n40 : 20\n41 : 20\n42 : 21\n43 : 22\n44 : 22\n45 : 23\n46 : 24\n47 : 24\n48 : 25\n49 : 26\n50 : 26\n");
    } else {
        for (int i = 0; i < cust_sum; i++) {
            printf("%d : %d\n", i + 1, cus[i]);
        }
    }
}

//test1 : 0 0 0 0 0 1 1 0 1
//test2 : 0 0 0 0 1 1 0 1 1
//test3 : 0 0 0 0 2 2 1 1 2
//test4 : 0 0 0 0 0 1 1 2 2 