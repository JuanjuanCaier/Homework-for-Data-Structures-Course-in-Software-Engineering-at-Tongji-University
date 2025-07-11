/*JuanjuanCaier-123456*/
#include <iostream>  
#include <cstdlib>//为了可执行程序的暂停
#include <ctime>//随机数
#include<Windows.h>//可视化
#include<iomanip>//格号显示
#define N 40//迷宫的大小
using namespace std;

struct Move//定义坐标的移动
{
    int ChangeX;
    int ChangeY;
    Move(int X, int Y) {
        ChangeX = X;
        ChangeY = Y;
    }
};
const Move MoveDirection[4] = { {-2, 0},{2, 0},{0, -2},{0, 2} };//上，下，左，右
int StoreMaze[N][N] = { 0 };//建立迷宫储存数组，1是墙，0是空地

struct Way
{
    int X;
    int Y;
    Way* Next = NULL;
    Way(int x, int y) {
        X = x;
        Y = y;
    }
};
Way* First = (Way*)malloc(sizeof(Way));//存栈，首元为空
int IfWay[N][N] = { 0 };//存路径，1是路，待输出迷宫时检查此数组

void Add(int x, int y) {//在链表尾部添加元素
    Way* Current = First;
    while (Current->Next != NULL) {//遍历到最后一个
        Current = Current->Next;
    }
    Current->Next = new Way(x, y);
    IfWay[x][y] = 1;
}

void Delete() {//在链表尾部删去元素
    Way* Current = First;
    while (Current->Next->Next != NULL) {//遍历到倒数第二个
        Current = Current->Next;
    }
    IfWay[Current->Next->X][Current->Next->Y] = 0;
    Current->Next = NULL;
}

void Output() {//输出链表（路径）
    Way* Current = First->Next;
    cout << "迷宫路径（地图中已经以紫色标注，坐标路径为先行后列）：" << endl;
    while (Current != NULL) {
        cout << '<' << Current->X << ',' << Current->Y << "> ";
        if (Current->Next != NULL) {//如果不是最后一个
            cout << "---> ";
        }
        Current = Current->Next;
    }
    cout << endl;
}

void SetColor(WORD colorAttribute) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorAttribute);
}

void PrintMaze() {//打印迷宫
    int X = 0, Y = 0, Loop = 0;
    cout << "迷宫地图（黑色为路径，白色为墙体）：" << endl;
    cout << "  ";
    while (Loop < N) {
        if (Loop % 2 == 0) {
            SetColor(6);
        }
        cout << setw(2) << Loop;
        SetColor(7);
        Loop++;
    }
    cout << endl;
    while (X < N) {
        Y = 0;
        if (X % 2 == 0) {
            SetColor(6);
        }
        cout << setw(2) << X;
        SetColor(7);
        while (Y < N) {
            if (StoreMaze[X][Y]) {
                SetColor(0x70);
                cout << "  ";
                SetColor(7);
            }
            else {
                if (IfWay[X][Y] == 0) {
                    cout << "  ";
                }
                else {
                    SetColor(0x50);
                    cout << "  ";
                    SetColor(7);
                }
            }
            Y++;
        }
        cout << endl;//打印完一行的换行
        X++;
    }
}

bool IsValidOfFind(int X, int Y) {//检查坐标是否在迷宫范围内，且是否是墙、路，不是墙、路就能走，为了避免重复走
    if ((X >= 0) && (X <= (N - 1)) && (Y >= 0) && (Y <= (N - 1)) &&
        (StoreMaze[X][Y] == 0) && (IfWay[X][Y] == 0)) {
        return 1;
    }
    return 0;
}

bool IsValid(int X, int Y) {//检查坐标是否在迷宫范围内，且是否是墙，是墙就可以挖
    if ((X >= 1) && (X < (N - 1)) && (Y >= 1) && (Y < (N - 1)) &&
        (StoreMaze[X][Y] == 1)) {
        return 1;
    }
    return 0;
}

void Shuffle(int Directions[4]) {//对数组进行随机排列，元素为0~3
    int Data = 0, Seat = 0;
    while (Data <= 3) {
        Seat = rand() % 4;
        if (Directions[Seat] == 4) {
            Directions[Seat] = Data;
            Data++;
        }
    }
}

void GenerateMaze(int StartX, int StartY) {//生成迷宫
    StoreMaze[StartX][StartY] = 0;  //挖空当前位置
    int Directions[4] = { 4,4,4,4 };//随机选择一个方向进行递归
    Shuffle(Directions);
    for (int Direction : Directions) {
        int MoveToX = StartX + MoveDirection[Direction].ChangeX;
        int MoveToY = StartY + MoveDirection[Direction].ChangeY;
        if (IsValid(MoveToX, MoveToY)) {
            StoreMaze[StartX + MoveDirection[Direction].ChangeX / 2][StartY + MoveDirection[Direction].ChangeY / 2] = 0; //打通墙壁
            GenerateMaze(MoveToX, MoveToY);
        }
    }
}

void SetEntryPointAndExitPoint() {//设置迷宫入口和出口,入口：(0, 1)，出口：(N-1, N-2)  
    int X = 0, Y = 0;
    while (X < N) {
        Y = 0;
        while (Y < N) {
            StoreMaze[X][Y] = 1;
            Y++;
        }
        X++;
    }
    StoreMaze[0][1] = 0;//入口
    StoreMaze[N - 1][N - 2] = 0;//出口
    GenerateMaze(0,1);//从起点挖
    StoreMaze[N - 2][N - 2] = 0;//出口的一部分
}

bool IfEnd = 0;//判断递归是否可以终结
void FindWay(int StartX, int StartY) {
    Add(StartX, StartY);//添加当前位置为路
    if ((StartX == N - 1) && (StartY == N - 2)) {//如果到达了终点
        IfEnd = 1;//递归结束
        return;
    }
    for (int Direction : {0, 1, 2, 3}) {
        int MoveToX = StartX + MoveDirection[Direction].ChangeX / 2;
        int MoveToY = StartY + MoveDirection[Direction].ChangeY / 2;
        if (IsValidOfFind(MoveToX, MoveToY)) {
            FindWay(MoveToX, MoveToY);
            if (IfEnd == 0) {//递归未结束的话就回溯
                Delete();//删除MoveTo的路
            }
            else {
                return;
            }
        }
    }
}

int main() {
    First->Next = NULL;//初始化
    srand((unsigned int)(time(0)));
    SetEntryPointAndExitPoint();//初始化迷宫
    FindWay(0, 1);
    PrintMaze();
    Output();
    system("pause");
    return 0;
}