//main.c
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 200 //队列容量
#define MAXSVR 5 //最大服务窗口数
typedef struct {
    int id;
    int wtime;
} CustType;
int Winnum = MAXSVR; //提供服务的窗口数
void updateCustqueue(); //更新等待队列中客户等待时间
void arriveCust(); //获取新客户，并加至等待队列中
int service(); //银行从队列中获取客户进行服务
void enCustqueue(CustType c); //客户入等待队列
CustType deCustqueue(); //客户出队
int getCustnum(); //获取队中等待客户人数
int isFull();
int isEmpty();
//main.c
int main(){
    int clock, simulationtime;
    scanf("%d", &simulationtime);
    for(clock = 1;; clock++) {

        //更新等待队列中客户等待时间
        updateCustqueue();

        //获取新客户，并加至等待队列中
        if(clock <= simulationtime )
            arriveCust();

        //银行从队列中获取客户进行服务
        if(service() == 0 && clock > simulationtime)
            break; //等待队列为空且不会有新客户
    }
    return 0;
}