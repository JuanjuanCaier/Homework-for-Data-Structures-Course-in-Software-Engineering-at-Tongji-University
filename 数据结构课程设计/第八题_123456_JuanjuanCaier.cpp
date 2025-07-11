/*JuanjuanCaier-123456*/
#include <iostream>
#include <cstdlib>//为了exe可以看到结果

using namespace std;

//顶点结构体
struct Point
{
	int Num;
	char Name;
	//不带参构造函数
	Point() {
		Num = 0;
		Name = 0;
	}
	//带参构造函数
	Point(int N, char n) {
		Num = N;
		Name = n;
	}
};
//边结构体
struct Side
{
	Point Start;//起始端点
	Point End;//结束端点
	int Count;//权
	//默认构造函数
	Side() {
		Count = INT_MAX;
	}
	//带值构造函数
	Side(Point S, Point E, int C) {
		Start = S;
		End = E;
		Count = C;
	}
};
//全局数组用来存顶点和边
Point Vertex[20];//顶点
int NumberOfVertex = 0;//顶点数目
int NumberOfSide = 0;//边数目
int LinJie[20][20] = { INT_MAX };//邻接矩阵，(x,y)对应从x到y的造价
int Key[20] = { INT_MAX };//储存每个顶点到树的距离
Side Result[190];//储存结果

//检测是否在树中
bool Check(int Checked[20], int& j) {
	for (int i = 0; i < NumberOfVertex; i++) {
		if (j == Checked[i]) {
			return 1;
		}
	}
	return 0;
}
//更新Key值，即所有点距离树的最短距离
void FlashKey(Side Key[20], int Checked[20]) {
	for (int i = 0; i < NumberOfVertex; i++) {//选取起点
		if (!Check(Checked, i)) {//如果选取的起点不在树中
			for (int j = 0; j < NumberOfVertex; j++) {//选取终点
				if (Check(Checked, j)) {//如果所选取的终点在树中
					if (LinJie[i][j] < Key[i].Count) {
						Key[i].Count = LinJie[i][j];
						Key[i].End.Num = j;
					}
				}
			}
		}
	}
}
//为Checked在顶端添加
void Push(int Checked[20], int Num) {
	int i = 0;
	for (i = 0; i < NumberOfVertex; i++) {
		if (Checked[i] == -1) {
			break;
		}
	}
	Checked[i] = Num;
}
// Prim算法
void Prim(int NumPoint,int StartPoint) {
	int Checked[20] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };//储存所有在树中的点
	Side Key[20];//储存每个点距离树的权
	int Min = INT_MAX, Money = 0, Start = 0, End = 0, LoopOfResult = 0;

	//先选权最小的一条边作为起点
	for (int i = 0; i < NumPoint; i++) {//选取起点
		if (Vertex[i].Num == Start) {
			for (int j = 0; j < NumPoint; j++) {//选取终点
				if (LinJie[i][j] < Min) {
					Start = i;
					End = j;
					Min = LinJie[i][j];
				}
			}
		}
	}
	Result[LoopOfResult].Start = Vertex[Start];
	Result[LoopOfResult].End = Vertex[End];
	Result[LoopOfResult].Count = LinJie[Start][End];
	LoopOfResult++;
	Push(Checked,Start);
	Push(Checked, End);

	//开始计算其他边
	for (int j = 0; j < NumPoint - 2; j++) {
		FlashKey(Key, Checked);//刷新Key值
		Min = INT_MAX;
		for (int i = 0; i < NumPoint; i++) {//选取起点
			//选取最小的那个距离
			if (Check(Checked, i) == 0 && Key[i].Count < Min) {//如果起点不在树中，且Key更加小
				Start = i;
				End = Key[i].End.Num;
				Min = Key[i].Count;
			}
		}
		Result[LoopOfResult].Start = Vertex[Start];
		Result[LoopOfResult].End = Vertex[End];
		Result[LoopOfResult].Count = LinJie[Start][End];
		LoopOfResult++;
		Push(Checked, Start);
	}
}
//创建电网顶点
void CreateVertex() {
	while (1) {
		cout << "请输入顶点的个数：";
		cin >> NumberOfVertex;
		if (NumberOfVertex >= 2) {
			break;
		}
		cout << "输入有误。" << endl;
		NumberOfVertex = 0;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	cout << "请依次输入各顶点的名称：" << endl;
	for (int i = 0; i < NumberOfVertex; i++) {
		cin >> Vertex[i].Name;
		Vertex[i].Num = i;
	}
}
//根据点的名字返回其在Vertex数组中的位置(也即Point结构体的Num变量)
int SearchSeat(char Point) {
	int i = 0;
	for (i = 0; i < NumberOfVertex; i++) {
		if (Vertex[i].Name == Point) {
			break;
		}
	}
	return i;
}
//添加电网的边
void AddSide() {
	int MaxSide = NumberOfVertex * (NumberOfVertex - 1) / 2;
	cout << "输入“? ? 0”来结束边的输入，或是在添加 " << MaxSide << " 条边后自动结束输入。" << endl;
	cout << "请不要输入不存在的顶点和不大于零的造价。" << endl;
	for (int i = 0; i < MaxSide; i++) {
		cout << "请输入两个顶点及边：";
		char Start = 0, End = 0;
		int Count = 0;
		cin >> Start >> End >> Count;
		if (Start == '?') {
			break;
		}
		int SeatOfStart = SearchSeat(Start);
		int SeatOfEnd = SearchSeat(End);
		LinJie[SeatOfStart][SeatOfEnd] = LinJie[SeatOfEnd][SeatOfStart] = Count;
		NumberOfSide++;
	}
}
//搜索起始顶点是否存在
bool Search(char Target) {
	for (int i = 0; i < NumberOfVertex; i++) {
		if (Target == Vertex[i].Name) {
			return 1;
		}
	}
	return 0;
}
//构造最小生成树
void MakeMin() {
	char StartPoint = 0;
	while (1) {
		cout << "请输入起始顶点：";
		cin >> StartPoint;
		if (Search(StartPoint)) {
			break;
		}
		else {
			cout << "未找到该顶点。";
		}
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	Prim(NumberOfVertex, SearchSeat(StartPoint));
	cout << "生成Prim最小生成树！" << endl;
}
//显示最小生成树
void Output() {
	cout << "最小生成树的顶点及边为：" << endl;
	for (int i = 0; i < NumberOfVertex - 1; i++) {
		cout << Result[i].Start.Name << "-<" << Result[i].Count << ">-" << Result[i].End.Name << endl;
	}
}
//主函数
int main() {
	cout << "**               电网造价模拟系统               **" << endl;
	cout << "==================================================" << endl;
	cout << "**               A --- 创建电网顶点             **" << endl;
	cout << "**               B --- 添加电网的边             **" << endl;
	cout << "**               C --- 构建最小生成树           **" << endl;
	cout << "**               D --- 显示最小生成树           **" << endl;
	cout << "**               E --- 退出   程序              **" << endl;
	cout << "==================================================" << endl;
	while (1) {
		cout << endl << "请选择操作：";
		char Choice = '\0';
		cin >> Choice;
		if (Choice == 'A') {
			CreateVertex();
			continue;
		}
		else if (Choice=='B') {
			AddSide();
			continue;
		}
		else if (Choice == 'C') {
			MakeMin();
			continue;
		}
		else if (Choice == 'D') {
			Output();
			continue;
		}
		else if (Choice == 'E') {
			break;
		}
		cout << "输入有误。" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	system("pause");
	return 0;
}