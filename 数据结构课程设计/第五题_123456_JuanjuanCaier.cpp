/*JuanjuanCaier-123456*/
#include <iostream>  
#include <cstdlib>//为了可执行程序的暂停
using namespace std;

//节点结构体定义
struct Data {
    int Number;
    Data* Next;
    Data(int n) {
        Number = n;
        Next = NULL;
    }
};
Data* FirstA = new Data(NULL);
Data* FirstB = new Data(NULL);
//入队，永远塞到第一位
void Add(Data* First, int N) {
    Data* Current = new Data(N);
    Current->Next = First->Next;
    First->Next = Current;
}
//出队，出最后一个
void Out(Data* First) {
    Data* Current = First;
    while (Current->Next->Next != NULL) {
        Current = Current->Next;
    }
    free(Current->Next);
    Current->Next = NULL;
}
//获得顶端（出队者）
int GetTop(Data* First) {
    Data* Current = First;
    while (Current->Next != NULL) {
        Current = Current->Next;
    }
    return Current->Number;
}
//检测是否是空串，是则给0
bool Ifempty(Data* First) {
    if (First->Next == NULL) {
        return 0;
    }
    return 1;
}

int main() {
    //初始化
    FirstA->Next = NULL;
    FirstB->Next = NULL;
    int PeopleNumber, Middle;
    cout << "请输入一行正整数，其中第一数字N（N<=1000）为顾客总数，后面跟着N位顾客的编号。" << endl;
    cin >> PeopleNumber;
    while (PeopleNumber > 0) {
        cin >> Middle;
        //编号为偶数的去B
        if (Middle % 2 == 0) {
            Add(FirstB, Middle);
        }
        else {
            Add(FirstA, Middle);
        }
        PeopleNumber--;
    }
    while (1) {
        if ((Ifempty(FirstA) == 0 && Ifempty(FirstB) == 0)) {//如果全是空串就退出
            break;
        }
        if (Ifempty(FirstA)) {
            cout << GetTop(FirstA);
            Out(FirstA);
            if ((Ifempty(FirstA) == 0 && Ifempty(FirstB) == 0)) {}//如果全是空串就不输出空格
            else {
                cout << ' ';
            }
        }
        if (Ifempty(FirstA)) {
            cout << GetTop(FirstA);
            Out(FirstA);
            if ((Ifempty(FirstA) == 0 && Ifempty(FirstB) == 0)) {}//如果全是空串就不输出空格
            else {
                cout << ' ';
            }
        }
        if (Ifempty(FirstB)) {
            cout << GetTop(FirstB);
            Out(FirstB);
            if ((Ifempty(FirstA) == 0 && Ifempty(FirstB) == 0)) {}//如果全是空串就不输出空格
            else {
                cout << ' ';
            }
        }
    }
    cout << endl;
    system("pause");
}