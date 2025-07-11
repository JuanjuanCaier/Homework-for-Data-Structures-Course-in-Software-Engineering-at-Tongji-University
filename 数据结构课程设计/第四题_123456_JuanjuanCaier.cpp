/*JuanjuanCaier-123456*/
#include <iostream>
#include <cstdlib>//为了可执行程序的暂停
using namespace std;

struct Element//栈存储的元素
{
	char Data;
	Element* Next = NULL;
	Element(char D) {
		Data = D;
	}
};
Element* StackFirst = new Element(NULL);//栈头指针

//在链表尾部添加元素
void Add(char Data = NULL) {
	Element* Current = StackFirst;
	while (Current->Next != NULL) {//遍历到最后一个
		Current = Current->Next;
	}
	Current->Next = new Element(Data);
}
//在链表尾部删去元素
void Delete() {
	Element* Current = StackFirst;
	while (Current->Next->Next != NULL) {//遍历到倒数第二个
		Current = Current->Next;
	}
	Current->Next = NULL;
}
//检查是否是空栈
int IfEmpty() {
	if (StackFirst->Next == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
//获得栈顶元素
char GetTop() {
	Element* Current = StackFirst;
	while (Current->Next != NULL) {//遍历到最后一个
		Current = Current->Next;
	}
	return (Current->Data);
}
//判断字符是否是数字
int IsDigit(char Input) {
	if ((Input >= '0') && (Input <= '9')) {
		return 1;
	}
	else {
		return 0;
	}
}
//判断字符是否为运算符  
bool IsOperator(char c) {  
	return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));//是的话就输出1
}
// 获取运算符的优先级 
int Precedence(char op) {
	if ((op == '+') || (op == '-')) {
		return 1;//优先级较低
	}
	else if ((op == '*') || (op == '/')) {
		return 2;//优先级较高
	}
	return 0;//左括号
}
//输出结果
void Output(char Result[100]) {
	for (int i = 0; Result[i] != '\0'; i++) {
		cout << Result[i];
	}
	cout << endl;
}
// 将中缀表达式转换为后缀表达式
void ChangeType() {
	char ch = 0;
	char Result[100] = { 0 };
	int i = 0;
	while ((ch = getchar()) && (ch != '\n')) {//读取到ch中，遇到末尾时停止
		if (ch == ' ') {//如果空格就继续读
			continue;
		}
		if (IsDigit(ch)) {//是数字就直接存入
			Result[i] = ch;
			i++;
			while (1) {
				ch = getchar();
				if (ch == ' ') {
					Result[i] = ' ';
					i++;
					break;
				}
				else if (ch == '\n') {
					Result[i] = ' ';
					i++;
					break;
				}
				else if (IsDigit(ch) || ch == '.') {//如果是数字或者点
					Result[i] = ch;
					i++;
				}
			}
			if (ch == '\n') {
				break;
			}
		}
		else if (ch == '+') {//如果是正号，检测是数字还是单纯正号
			ch = getchar();
			if (IsDigit(ch)) {//是数字就直接存入
				Result[i] = ch;
				i++;
				while (1) {
					ch = getchar();
					if (ch == ' ') {
						Result[i] = ' ';
						i++;
						break;
					}
					else if (ch == '\n') {
						Result[i] = ' ';
						i++;
						break;
					}
					else if (IsDigit(ch) || ch == '.') {//如果是数字或者点
						Result[i] = ch;
						i++;
					}
				}
				if (ch == '\n') {
					break;
				}
			}
			else {//恢复
				ch = '+';
			}
		}
		else if (ch == '-') {//如果是负号，检测是数字还是单纯负号
			ch = getchar();
			if (IsDigit(ch)) {//是数字就直接存入
				Result[i] = '-';
				i++;
				Result[i] = ch;
				i++;
				while (1) {
					ch = getchar();
					if (ch == ' ') {
						Result[i] = ' ';
						i++;
						break;
					}
					else if (ch == '\n') {
						Result[i] = ' ';
						i++;
						break;
					}
					else if (IsDigit(ch) || ch == '.') {//如果是数字或者点
						Result[i] = ch;
						i++;
					}
				}
				if (ch == '\n') {
					break;
				}
			}
			else {//恢复
				ch = '-';
			}
		}
		if (ch == '(') {//如果是左括号，压入栈  
			Add(ch);
		}
		else if (ch == ')') {//如果是右括号，弹出栈顶运算符直到遇到左括号
			while ((!IfEmpty()) && (GetTop() != '(')) {
				//将运算符和空格压入结果
				Result[i] = GetTop();
				i++;
				Result[i] = ' ';
				i++;
				Delete();//压入运算符后弹出该运算符
			}
			Delete();//弹出左括号  
		}
		else if (IsOperator(ch)) {//如果是运算符  
			while ((!IfEmpty()) && (Precedence(GetTop()) >= Precedence(ch))) {//如果栈顶运算符的优先级不小于Token中的
				//压入高级别的运算符和空格
				Result[i] = GetTop();
				i++;
				Result[i] = ' ';
				i++;
				Delete();//压入运算符后弹出该运算符
			}
			Add(ch);
		}
	}
	while (!IfEmpty()) {//将栈中剩余的运算符依次弹出  
		Result[i] = GetTop();
		i++;
		Result[i] = ' ';
		i++;
		Delete();
	}
	//去掉字符串末尾的空格
	int j = 0;
	for (; Result[j] != '\0'; j++) {}
	if (j > 0) {
		Result[j - 1] = '\0';
	}
	Output(Result);
}

int main() {
	StackFirst->Next = NULL;//初始化栈
	cout << "请输入在一行中给出以空格分隔不同对象的中缀表达式，不超过20个字符（不包括空格）：" << endl;
	ChangeType();//转换
	system("pause");
	return 0;
}
