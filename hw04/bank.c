#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 200       // 队列容量
#define THRESHOLD 7       // 窗口增加阈值
#define MAXSVR 5          // 最大服务窗口数
#define MINSVR 3          // 最小服务窗口数
//! 三个对私、一个对公和一个外币窗口
//       1       2         3
typedef struct {
    int id;
    int type_time;
    int wtime;
} CustType;
CustType Cqueue[MAXSIZE];
int front = 0;
int rear = MAXSIZE - 1;
int cnt = 0;
int cust_sum = 0;
int window_time[MAXSVR + 1] = {0};
int sum_of_opened_window = MINSVR;
int arrive_sum_in_a_period[MAXSIZE] = {0};
int extra_window[MAXSVR + 1] = {1,1,1,0,0}; //0表示关闭，1表示打开
// 函数声明
void updateCustqueue();    // 更新等待队列中客户等待时间
void arriveCust();         // 获取新客户并加入队列
int service();             // 从队列获取客户进行服务
void enCustqueue(CustType c); // 客户入队
CustType deCustqueue();     // 客户出队
int isFull();
int isEmpty();
int print_window()
{
    printf("|");
    for(int i = 0; i < sum_of_opened_window; i++)
    {
        printf("window%d : %d |", i, window_time[i]);
    }
    printf("\n");
}
int main() {
    int clock = 0;
    int simulationtime;
    int Winnum = MINSVR;   // 当前服务窗口数

    scanf("%d", &simulationtime);
    for(int i = 0; i < simulationtime; i++)
    {
        scanf("%d", &arrive_sum_in_a_period[i]);
    }
    for (clock = 0; ; clock++) {
        // 更新等待时间
        updateCustqueue();
        // 新客户入队，尝试增加窗口
        if (clock <= simulationtime) {
            arriveCust(clock);
        }

        // 处理服务并尝试减少窗口
        if (service() == 0 && clock > simulationtime) {
            break; // 队列空且无新客户 
        }

    }
    
    return 0;
}
void updateCustqueue()
{
    if(isEmpty()) return;
    for(int i = front; i <= rear; i = (i+1) % MAXSIZE)
    {
        Cqueue[i].wtime++;
    }
}
void arriveCust(int clock)
{
    while((cnt/sum_of_opened_window ) >= THRESHOLD && sum_of_opened_window < MAXSVR)//
    {
        //只在获取新客户（不管到达新客户数是否为0）时，才按策略调整服务窗口数
        //增加一个窗口就能使得按窗口均等待服务人数小于7人，则只增加一个窗口
        for(int i = MINSVR ; i < MAXSVR; i++)
        {
            //如果有闲置的窗户，打开一个
            if(extra_window[i] == 0 && window_time[i] <= 0)
            {
                extra_window[i] = 1; 
                sum_of_opened_window++;
                break;
            }
        }
    }
    for(int i = 0; i < arrive_sum_in_a_period[clock]; i++)
    {
        CustType new;
        scanf("%d", &new.type_time);
        new.id = ++cust_sum;
        new.wtime = 0;
        //进入队列
        enCustqueue(new);
    }

}
int service()
{
    for(int i = 0; i < MAXSVR; i++)
    {
        if(window_time[i] <= 0 && extra_window[i] == 1)
        {
            //窗口可以接待客户
            CustType next = deCustqueue();
            if(next.id == -1) continue; //队列为空，本窗口不需要再来下一个人了。
            window_time[i] = next.type_time;
            printf("%d : %d\n", next.id, next.wtime);
            
        }
        //假设新到客户是在每个服务周期开始时到达。
        if(window_time[i] > 0 && extra_window[i] == 1) window_time[i]--; //处理一个时间单位 
    }
    //如果此时减去一个窗口均值小于7 且该窗无业务，则关闭
    while((cnt/(sum_of_opened_window-1)) >= THRESHOLD && sum_of_opened_window > MINSVR)
    {
        for(int i = MAXSVR-1; i >= MINSVR; i--)
        {
            if(window_time[i] <= 0 && extra_window[i] == 1) //! 两个条件
            {
                extra_window[i] = 0; 
                sum_of_opened_window--;
                break;
            }
        }
    }
    return cnt;
}
void enCustqueue(CustType c)
{
    if(isFull()) return;
    else
    {
        rear = (rear+1) % MAXSIZE;
        cnt++;
        Cqueue[rear] = c;
    }
}
CustType deCustqueue()
{
    CustType cust;
    cust.id = -1;
    if(isEmpty())
    {
        return cust;
    }
    cust = Cqueue[front];
    front = (front + 1) % MAXSIZE;
    cnt--;
    return cust;
}
int isEmpty()
{
    return cnt == 0;
}
int isFull()
{
    return cnt == MAXSIZE;
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