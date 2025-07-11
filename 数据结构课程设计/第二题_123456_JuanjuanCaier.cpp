/*JuanjuanCaier-123456*/
#include<iostream>
#include<cstdlib>//使可执行文件可以看到结果
using namespace std;

struct StoreNumber//存储数字
{
	int Number;//考号
	StoreNumber* Next = NULL;
	StoreNumber(int Num) {
		Number = Num;
	}
};

StoreNumber* FirstOne = (StoreNumber*)malloc(sizeof(StoreNumber));//获得头指针，链表首元素空
StoreNumber* FirstTwo = (StoreNumber*)malloc(sizeof(StoreNumber));
StoreNumber* FirstThree = (StoreNumber*)malloc(sizeof(StoreNumber));

void Input(StoreNumber* First) {//输入
	int Num;
	StoreNumber* Current = First;
	while (1) {
		cin >> Num;
		if (Num == -1) {
			break;
		}
		Current->Next = new StoreNumber(Num);
		Current = Current->Next;
	}
}

void Output(StoreNumber* First) {//输出，未指定为输出交集数据，可以用来中途调试
	StoreNumber* Current = First->Next;
	while (Current != NULL) {
		cout << Current->Number;
		if (Current->Next != NULL) {//如果不是末尾
			cout << ' ';
		}
		Current = Current->Next;
	}
}

void Intersection() {
	StoreNumber* CurrentOne=FirstOne->Next;
	StoreNumber* CurrentTwo = FirstTwo->Next;
	StoreNumber* CurrentThree = FirstThree;
	while (CurrentOne != NULL) {
		CurrentTwo = FirstTwo->Next;
		while (CurrentTwo != NULL) {
			if (CurrentOne->Number == CurrentTwo->Number) {
				CurrentThree->Next = new StoreNumber(CurrentOne->Number);
				CurrentThree = CurrentThree->Next;
			}
			CurrentTwo = CurrentTwo->Next;
		}
		CurrentOne = CurrentOne->Next;
	}
}

int main() {
	int Loop = 0;
	FirstOne->Next = NULL;
	FirstTwo->Next = NULL;
	FirstThree->Next = NULL;
	cout << "请输入两个非降序数组，以-1结尾，分两行输入（数值相同的元素视为两个不同的元素）。" << endl;
	Input(FirstOne);
	Input(FirstTwo);
	Intersection();
	if (FirstThree->Next == NULL) {
		cout << "NULL" << endl;
		system("pause");
		return 0;
	}
	Output(FirstThree);
	cout << endl;
	system("pause");
	return 0;
}