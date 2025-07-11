/*JuanjuanCaier-123456*/
#include <iostream>
#include <cstdlib>//为了exe可以看到结果

using namespace std;

#define Most 10000//最多段数
int N = 0;//段数

//整理函数，用于整理数组
void Sort(int Length[Most]) {
    bool IfExchange = 0;
    for (int i = 0; i < N - 1; i++) {
        if (Length[i] < Length[i + 1]) {
            int MiddleData = Length[i];
            Length[i] = Length[i + 1];
            Length[i + 1] = MiddleData;
            IfExchange = 1;
        }
        if (i == N - 2 && IfExchange == 0) {
            break;
        }
        else if (i == N - 2 && IfExchange == 1) {
            i = -1;
            IfExchange = 0;
        }
    }
}
//找到最便宜方案
int Find(int Length[Most]) {
    int Result = 0;
    while (N > 1) {
        Sort(Length);
        Result += Length[N - 1] + Length[N - 2];
        Length[N - 2] += Length[N - 1];
        Length[N - 1] = 0;
        N--;
    }
    return Result;
}

int main() {
    while (1) {
        cout << "请输入木头段数和每段长度：" << endl;
        cin >> N;
        if (N < 10000) {
            break;
        }
        cout << "输入有误。" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    int Length[Most] = { 0 };
    //输入每段长度
    for (int i = 0; i < N; i++) {
        cin >> Length[i];
    }
    cout << Find(Length) << endl;
    system("pause");
    return 0;
}