/*JuanjuanCaier-123456*/
/*最多支持四字姓名*/
#include<iostream>
#include<iomanip>
using namespace std;

class String {
private:
	char* data;
	size_t length;

public:
	//默认构造函数
	String() : data(nullptr), length(0) {}
	//构造函数
	String(const char* str) {
		if (str) {
			//手动计算字符串长度
			length = 0;
			while (str[length] != '\0') {
				++length;
			}
			data = new char[length + 1];//为'\0'留出空间
			for (size_t i = 0; i < length; ++i) {
				data[i] = str[i];
			}
			data[length] = '\0';//添加字符串结束符
		}
		else {
			data = nullptr;
			length = 0;
		}
	}
	//拷贝构造函数
	String(const String& other) {
		length = other.length;
		data = new char[length + 1];
		for (size_t i = 0; i < length; ++i) {
			data[i] = other.data[i];
		}
		data[length] = '\0';//添加字符串结束符
	}
	//赋值运算符重载
	String& operator=(const String& other) {
		if (this != &other) {//避免自我赋值
			delete[] data;//释放原来的内存
			length = other.length;
			data = new char[length + 1];
			for (size_t i = 0; i < length; ++i) {
				data[i] = other.data[i];
			}
			data[length] = '\0';//添加字符串结束符
		}
		return *this;
	}
	//析构函数
	~String() {
		delete[] data;
	}
	//获取字符串长度
	size_t size() const {
		return length;
	}
	//输出字符串
	void print() const {
		if (data) {
			for (size_t i = 0; i < length; ++i) {
				cout << data[i];
			}
		}
		else {
			cout << "(null)" << endl;
		}
	}
	//比较两个字符串
	bool operator==(const String& other) const {
		if (length != other.length) {
			return false;
		}
		for (size_t i = 0; i < length; ++i) {
			if (data[i] != other.data[i]) {
				return false;
			}
		}
		return true;
	}
	//重载<<运算符，用于输出String对象
	friend ostream& operator<<(ostream& os, const String& str);
	// 重载>>运算符，用于从输入流读取String对象
	friend istream& operator>>(istream& is, String& str);
};

//重载<<运算符，输出String对象
ostream& operator<<(ostream& os, const String& str) {
	//使用C风格字符串输出
	os << str.data;
	return os;
}
//重载>>运算符，从输入流读取String对象
istream& operator>>(istream& is,String& str) {
	char ch;
	size_t capacity = 10;//初始容量
	size_t length = 0;//当前长度
	char* buffer = new char[capacity];//分配缓冲区
	is >> ws;//忽略遗留的空格
	while (is.get(ch) && ch != '\n' && ch != ' ') {//读取字符直到换行或者空格
		if (length == capacity - 1) {//缓冲区已满
			capacity *= 2;//扩大缓冲区
			char* newBuffer = new char[capacity];
			for (size_t i = 0; i < length; i++) {//复制原数据到新缓冲区
				newBuffer[i] = buffer[i];
			}
			delete[] buffer;//释放旧的缓冲区
			buffer = newBuffer;//更新缓冲区指针
		}
		buffer[length] = ch;//将字符存入缓冲区
		length++;
	}
	buffer[length] = '\0';//添加字符串结束符
	//用输入的字符初始化String对象
	str = String(buffer);
	delete[] buffer;//释放缓冲区
	return is;
}

struct StudentInfo//存储结构体
{
	int StudentNumber;//考号
	String StudentName;//名字
	String StudentGender;//性别
	int StudentAge;//年龄
	String ApplicationType;//报考类型
	StudentInfo* Next = NULL;//指向下一个数据
	StudentInfo(int Num, String Name, String Gen, int Age, String Type) {
		StudentNumber = Num;
		StudentName = Name;
		StudentGender = Gen;
		StudentAge = Age;
		ApplicationType = Type;
	}
};
StudentInfo* First = (StudentInfo*)malloc(sizeof(StudentInfo));//获得头指针，链表首元素空

//输入全部
void Input(int StudentCount) {
	int Loop = 0;
	int Num, Age;
	String Name, Gen, Type;
	StudentInfo* Current = First;
	while (Loop < StudentCount) {
		cin >> Num >> Name >> Gen >> Age >> Type;
		Current->Next = new StudentInfo(Num, Name, Gen, Age, Type);
		Current = Current->Next;
		Loop++;
	}
}

void Output() {//输出全部
	cout << "考号    姓名      性别    年龄    报考类别" << endl;
	StudentInfo* Current = First->Next;
	while (Current != NULL) {
		cout << setw(8) << left << Current->StudentNumber
			<< setw(10) << left << Current->StudentName
			<< setw(8) << left << Current->StudentGender
			<< setw(8) << left << Current->StudentAge
			<< setw(8) << left << Current->ApplicationType << endl;
		Current = Current->Next;
	}
}

void InsertInfo(int& StudentCount) {
	int StudentSeat = 0, Loop = 0, Num, Age;
	String Name, Gen, Type;
	StudentInfo* Current = First;
	StudentInfo* InsertData = NULL;
	while (1) {
		cout << "请输入你要插入的考生的位置：";//此处应考虑位置超过最大位置并且做错误处理
		cin >> StudentSeat;
		if (((StudentSeat <= (StudentCount + 1)) && (StudentSeat > 0)) && (cin.good() == 1)) {
			cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
			cin >> Num >> Name >> Gen >> Age >> Type;
			InsertData = new StudentInfo(Num, Name, Gen, Age, Type);
			if (StudentSeat == (StudentCount + 1)) {//末尾
				while (Current->Next != NULL) {//找到最后一个
					Current = Current->Next;
				}
				Current->Next = InsertData;
			}
			else {//中间
				while (Loop < (StudentSeat - 1)) {
					Current = Current->Next;
					Loop++;
				}
				InsertData->Next = Current->Next;
				Current->Next = InsertData;
			}
			StudentCount++;
			break;
		}
		else {
			cout << "输入非法，请再次输入" << endl;
		}
	}
}

void DeleteInfo(int& StudentCount) {
	int StudentNumber = 0;
	StudentInfo* Current = First;
	if (StudentCount == 1) {
		cout << "仅一名考生，无法删除" << endl;
		return;
	}
	while (1) {
		Current = First;
		cout << "请输入要删除的考生的考号：";
		cin >> StudentNumber;
		while (Current->Next != NULL) {
			if (Current->Next->StudentNumber == StudentNumber) {
				Current->Next = Current->Next->Next;
				StudentCount--;
				return;
			}
			Current = Current->Next;
		}
		cout << "未找到目标考号，请重新输入" << endl;
	}
}

void Research() {
	int StudentNumber = 0;
	StudentInfo* Current = First->Next;
	while (1) {
		Current = First->Next;
		cout << "请输入要查找的考生的考号：";
		cin >> StudentNumber;
		while (Current != NULL) {
			if (Current->StudentNumber == StudentNumber) {
				cout << "考号    姓名      性别    年龄    报考类别" << endl;
				cout << setw(8) << left << Current->StudentNumber
					<< setw(10) << left << Current->StudentName
					<< setw(8) << left << Current->StudentGender
					<< setw(8) << left << Current->StudentAge
					<< setw(8) << left << Current->ApplicationType << endl;
				return;
			}
			Current = Current->Next;
		}
		cout << "未找到，请重新输入" << endl;
	}
}

void Modify() {
	int StudentNumber = 0, Num, Age;
	String Name, Gen, Type;
	StudentInfo* Current = First;
	StudentInfo* InsertData = NULL;
	while (1) {
		Current = First;
		cout << "请输入要修改的考生的考号：";
		cin >> StudentNumber;
		while (Current->Next != NULL) {
			if ((Current->Next->Next == NULL) && (Current->Next->StudentNumber == StudentNumber)) {//末尾
				cout << "请依次输入新的考生的考号，姓名，性别，年龄及报考类别！" << endl;
				cin >> Num >> Name >> Gen >> Age >> Type;
				InsertData = new StudentInfo(Num, Name, Gen, Age, Type);
				Current->Next = InsertData;
				return;
			}
			else if (Current->Next->StudentNumber == StudentNumber) {
				cout << "请依次输入新的考生的考号，姓名，性别，年龄及报考类别！" << endl;
				cin >> Num >> Name >> Gen >> Age >> Type;
				InsertData = new StudentInfo(Num, Name, Gen, Age, Type);
				InsertData->Next = Current->Next->Next;
				Current->Next = InsertData;
				return;
			}
			Current = Current->Next;
		}
		cout << "未找到，请重新输入" << endl;
	}
}

void Statistics(int& StudentCount) {//统计性别(应该)
	int Man = 0;
	StudentInfo* Current = First->Next;
	while (Current != NULL) {
		if (Current->StudentGender == "男") {
			Man++;
		}
		Current = Current->Next;
	}
	cout << "共有男生" << Man << "人，女生" << StudentCount - Man << "人。" << endl;
}

int main() {
	int StudentCount = 0, Choice = 0, TimesOfMenu = 0;
	cout << "首先请建立考生信息系统" << endl;
	while (1) {
		cout << "请输入考生人数：";
		cin >> StudentCount;
		if (StudentCount > 0) {
			break;
		}
		else {
			cout << "输入非法，请重新输入" << endl;
		}
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	Input(StudentCount);
	cout << endl;
	while (1) {
		Output();
		if (TimesOfMenu == 0) {
			cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）：";
			TimesOfMenu++;
		}
		else {
			cout << "请选择您要进行的操作：";
		}
		cin >> Choice;
		if (Choice == 0) {
			break;
		}
		else if (Choice == 1) {
			InsertInfo(StudentCount);
		}
		else if (Choice == 2) {
			DeleteInfo(StudentCount);
		}
		else if (Choice == 3) {
			Research();
		}
		else if (Choice == 4) {
			Modify();
		}
		else if (Choice == 5) {
			Statistics(StudentCount);
		}
	}
}
