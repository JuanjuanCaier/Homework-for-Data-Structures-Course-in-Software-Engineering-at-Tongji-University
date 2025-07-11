/*JuanjuanCaier-123456*/
#include <iostream>
#include <cstdlib>

using namespace std;

//定义一个结构体Task，表示一个任务
struct Task {
    //任务的开始节点、结束节点和所需时间
    int Start;
    int End;
    int Time;
    int ES;//任务的最早开始时间
    int EF;//任务的最早结束时间
    int LS;//任务的最晚开始时间
    int LF;//任务的最晚结束时间
    bool IfChecked;//检查是否已经经过，仅用于检测是否为环
    //重载小于运算符，用于Task的排序
    bool operator<(const Task& other) const {
        if (Start != other.Start)
            return Start < other.Start;//如果开始节点不同，按开始节点排序
        return End > other.End;//如果开始节点相同，按结束节点降序排序
    }
    Task() {
        Start = End = Time = ES = EF = LS = LF = IfChecked = 0;
    }
};

Task Tasks[100];//定义一个结构体数组，储存所有任务信息，共M个
int N = 0, M = 0;//定义两个整数N和M，分别表示节点数和任务数

//寻找所有前置任务的最早结束时间的最大值
int FindMaxEF(int Start) {//输入该任务起始节点
    int MaxEF = 0;
    for (int i = 0; i < M; i++) {
        if (Tasks[i].End == Start) {//如果是前置任务
            if (Tasks[i].EF > MaxEF) {
                MaxEF = Tasks[i].EF;
            }
        }
    }
    return MaxEF;
}
//寻找所有后置任务的最晚开始时间的最小值
int FindMinLS(int End) {
    int MinLS = INT_MAX;
    for (int i = M - 1; i >= 0; i--) {
        if (Tasks[i].Start == End) {//如果是后置任务
            if (Tasks[i].LS < MinLS) {
                MinLS = Tasks[i].LS;
            }
        }
    }
    return MinLS;
}
//检查是否可行
bool IfOk() {
    for (int i = 0; i < M; i++) {
        Tasks[i].IfChecked = 1;
        if (Tasks[i].End < Tasks[i].Start) {
            for (int j = 0; j < M; j++) {
                //如果链接到了之前的一个任务且它已经被访问过
                if (Tasks[j].Start == Tasks[i].End && Tasks[j].IfChecked == 1) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
//主函数
int main() {
    cout << "请输入节点数和任务数量：" << endl;
    while (1) {
        cin >> N >> M;//从输入读取N和M
        if (N <= 100 && M <= 100) {
            break;
        }
        cout << "输入有误。" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    cout << "请输入所有任务的开始节点、结束节点和所需时间：" << endl;
    //读取所有任务的信息
    for (int i = 0; i < M; i++) {
        cin >> Tasks[i].Start >> Tasks[i].End >> Tasks[i].Time;//从输入读取任务的开始节点、结束节点和所需时间
    }
    Tasks[M].Start = N;
    Tasks[M].End = N + 1;
    Tasks[M].Time = 0;
    N++;
    M++;
    cout << "结果为：" << endl;
    if (!IfOk()) {
        cout << 0 << endl;
        system("pause");
        return 0;
    }
    //计算最早开始时间和最早结束时间
    for (int i = 0; i < M;i++) {
        if (Tasks[i].Start == 1) {//没有前置任务
            Tasks[i].ES = 0;//最早开始时间就是项目开始时间
            Tasks[i].EF = 0 + Tasks[i].Time;//最早结束时间是最早开始时间加上所需时间
        }
        else {//有前置任务
            Tasks[i].ES = FindMaxEF(Tasks[i].Start);//最早开始时间是所有前置任务的最早结束时间的最大值
            Tasks[i].EF = Tasks[i].ES + Tasks[i].Time;//最早结束时间是最早开始时间加上所需时间
        }
    }
    //计算最晚开始时间和最晚结束时间
    for (int i = (M - 1); i >= 0; i--) {
        if (Tasks[i].End == N) {//没有后置任务
            Tasks[i].LF = Tasks[i].EF;//最晚结束时间就是最早结束时间
            Tasks[i].LS = Tasks[i].LF - Tasks[i].Time;//最晚开始时间是最晚结束时间减去所需时间
        }
        else {//有后置任务
            Tasks[i].LF = FindMinLS(Tasks[i].End);//最晚结束时间是所有后置任务的最晚开始时间的最小值
            Tasks[i].LS = Tasks[i].LF - Tasks[i].Time;//最晚开始时间是最晚结束时间减去所需时间
        }
    }
    Task Result[100];//储存结果
    int LengthOfResult = 0;
    //把结果放入结果数组中
    for (int i = 0; i < M; i++) {
        if (Tasks[i].LS == Tasks[i].ES) {
            Result[LengthOfResult] = Tasks[i];
            LengthOfResult++;
        }
    }
    int TimeResult = 0, Start = 1;
    //计算耗时
    for (int i = 0; i < LengthOfResult; i++) {
        if (Result[i].Start == Start) {
            TimeResult += Result[i].Time;
            Start = Result[i].End;
        }
    }
    cout << TimeResult << endl;
    //修正顺序
    for (int i = 0; i < LengthOfResult - 1; i++) {
        if (Result[i + 1] < Result[i]) {
            Task MiddleData = Result[i];
            Result[i] = Result[i + 1];
            Result[i + 1] = MiddleData;
        }
    }
    //输出路径
    for (int i = 0; i < LengthOfResult - 1; i++) {
        cout << Result[i].Start << "->" << Result[i].End << endl;
    }
    system("pause");
    return 0; // 主函数返回0，表示程序正常结束
}