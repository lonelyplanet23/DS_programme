/*已知两人分别执白棋和黑棋在一个围棋棋盘上下五子棋，若同一颜色的棋子在同一条横行、纵行或斜线上连成5个棋子，则执该颜色棋子的人获胜。编写程序读入某一时刻下棋的状态，并判断是否有人即将获胜，即：同一颜色的棋子在同一条横行、纵列或斜线上连成4个棋子，且该4个棋子的两端至少有一端为空位置。
输入的棋盘大小是19×19，用数字0表示空位置（即没有棋子），用数字1表示该位置下了一白色棋子，用数字2表示该位置下了一黑色棋子。假设同一颜色的棋子在同一条横行、纵列或斜线上连成的棋子个数不会超过4个，并且最多有一人连成线的棋子个数为4。*/
//! 错误点：没有考虑左下方向
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define N 100001
double eps = 1e-9;
int board[20][20];
int check_right(int i, int j, int piece) // 检查某一点右方是否有这种情况
{
    if(j + 3 > 19) //! 重点学习
        return 0;
    for(int k = j+1; k < j + 4; k++)
    {
        if(board[i][k] != piece)
            return 0;
    }
    if(j - 1 >= 1 && board[i][j-1] == 0)
        return 1;
    if(j + 4 <= 18 && board[i][j+4] == 0)
        return 1;
    return 0;
}
int check_down(int i, int j, int piece) // 检查某一点下方是否有这种情况
{
    if(i + 3 > 19)
        return 0;
    for(int k = i+1; k < i + 4; k++)
    {
        if(board[k][j] != piece)
            return 0;
    }
    if(i - 1 >= 1 && board[i-1][j] == 0)
        return 1;
    if(i + 4 <= 18 && board[i+4][j] == 0)
        return 1;
    return 0;
}
int check_right_down(int i, int j, int piece) // 检查某一点右下方是否有这种情况
{
    if(i + 3 > 19 || j + 3 > 19)
        return 0;
    for(int k = 1; k < 4; k++)
    {
        if(board[i+k][j+k] != piece)
            return 0;
    }
    if(i - 1 >= 1 && j - 1 >= 1 && board[i-1][j-1] == 0)
        return 1;
    if(i + 4 <= 18 && j + 4 <= 18 && board[i+4][j+4] == 0)
        return 1;
    return 0;
}
int check_left_down(int i, int j, int piece)
{
    if(i + 3 > 19 || j - 3 < 1) //!边界点检查 脑子要清醒！
        return 0;
    for(int k = 1; k <= 3; k++)
    {
        if(board[i+k][j-k] != piece)
        {
            return 0;
        }
    }
    if(i + 4 <= 19 && j - 4 >= 1 && board[i+4][j-4] == 0)
        return 1;
    if(i - 1 >= 1 && j + 1 <= 19 && board[i-1][j+1] == 0)
        return 1;
    return 0;
}
int check(int i, int j) // 检查某一点右下方（和边界）是否有这种情况
{
    int piece = board[i][j];
    if (piece == 0)
        return 0;
    //检查右方
    if(check_right(i, j, piece))
        return 1;
    //检查下方
    if(check_down(i, j, piece))
        return 1;
    //检查右下方
    if(check_right_down(i, j, piece))
        return 1;
    if(check_left_down(i, j, piece))
        return 1;
    return 0;

}
int main()
{
    for(int i=1;i<=19;i++)
    {
        for(int j=1;j<=19;j++)
        {
            scanf("%d",&board[i][j]);
        }
    }
    for(int i = 1; i <= 19; i++)
    {
        for(int j = 1; j <= 19; j++)
        {
            if(check(i, j))
            {
                printf("%d:%d,%d\n", board[i][j], i, j);
                return 0;
            }
        }
    }
    printf("No\n");
    return 0;
}