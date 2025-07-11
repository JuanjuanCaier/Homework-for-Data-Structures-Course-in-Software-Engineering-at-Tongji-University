/*JuanjuanCaier-123456*/
#include <iostream>  
#include <cstdlib>//为了可执行程序的暂停
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
    //获取C风格字符串（用于输出）
    const char* c_str() const {
        return data;
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
    os << str.c_str();
    return os;
}
//重载>>运算符，从输入流读取String对象
istream& operator>>(istream& is, String& str) {
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

//结构体定义 
struct Data {
    String Name;
    Data* Next[20];
    Data(String n) {
        Name = n;
        for (int i = 0; i < 20; i++) {
            Next[i] = NULL;
        }
    }
};
Data* First = new Data("\0");//头指针，首元为空
Data* Find = First;//用于查找

//检查是否是空数组
bool Empty(Data* Next[20]) {
    for (int i = 0; i < 20; i++) {
        if (Next[i] != NULL) {
            return 0;
        }
    }
    return 1;
}
//在数组顶端放入指针
void PushBack(Data* Next[20],Data* N) {
    for (int i = 0; i < 20; i++) {
        if (Next[i] == NULL) {
            Next[i] = N;
            break;
        }
    }
}
//遍历多叉树寻找目标
void Search(Data* Current,String NameForFind) {
    if (Empty(Current->Next)) {//处理空指针情况
        return;
    }
    //遍历Next容器中的每个指针
    for (auto next : Current->Next) {
        if (next == NULL) {
            break;
        }
        Search(next, NameForFind);//递归访问子节点
        if (next->Name == NameForFind) {
            Find = next;
            return;
        }
    }
}
//完善家谱
void AddFamily() {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    while (1) {
        Find = First;
        cout << "请输入要建立家庭的人姓名：" << endl;
        String NameForFind;
        cin >> NameForFind;
        Search(First, NameForFind);
        if (Find->Name == NameForFind) {
            break;
        }
        else {
            cout << "未找到此人。" << endl;
        }
    }
    int Num = 0;
    while (1) {
        Num = 0;
        cout << "请输入" << Find->Name << "的儿女人数：" << endl;
        if (cin >> Num) {
            break;
        }
        else {
            cout << "输入有误。" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }
    cout << "请依次输入" << Find->Name << "的儿女的姓名：" << endl;
    String NameForSun;
    while (Num > 0) {
        cin >> NameForSun;
        PushBack(Find->Next, new Data(NameForSun));
        Num--;
    }
    cout << Find->Name << "的第一代子孙是";
    for (auto next : Find->Next) {
        if (next == NULL) {
            break;
        }
        cout << next->Name << "  ";
    }
    cout << endl;
    return;
}
//添加家庭成员
void AddPeople() {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    while (1) {
        Find = First;
        cout << "请输入要添加儿子（或女儿）的人的姓名：" << endl;
        String NameForFind;
        cin >> NameForFind;
        Search(First, NameForFind);
        if (Find->Name == NameForFind) {
            break;
        }
        else {
            cout << "未找到此人。" << endl;
        }
    }
    String Name;
    cout << "请输入" << Find->Name << "新添加的儿子（或女儿）的姓名：" << endl;
    cin >> Name;
    PushBack(Find->Next, new Data(Name));
    cout << Find->Name << "的第一代子孙是";
    for (auto next : Find->Next) {
        if (next == NULL) {
            break;
        }
        cout << next->Name << "  ";
    }
    cout << endl;
    return;
}
//解散局部家庭
void DeleteFamily() {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    while (1) {
        Find = First;
        cout << "请输入要解散家庭的人的姓名：" << endl;
        String NameForFind;
        cin >> NameForFind;
        Search(First, NameForFind);
        if (Find->Name == NameForFind) {
            break;
        }
        else {
            cout << "未找到此人。" << endl;
        }
    }
    cout << "要解散家庭的人是：" << Find->Name << endl;
    cout << Find->Name << "的第一代子孙是";
    for (auto next : Find->Next) {
        if (next == NULL) {
            break;
        }
        cout << next->Name << "  ";
    }
    cout << endl;
    for (int i = 0; i < 20; i++) {
        Find->Next[i] = NULL;
    }
    return;
}
//修改家庭成员姓名
void Exchange() {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    while (1) {
        Find = First;
        cout << "请输入要更改姓名的人的目前姓名：" << endl;
        String NameForFind;
        cin >> NameForFind;
        Search(First, NameForFind);
        if (Find->Name == NameForFind) {
            break;
        }
        else {
            cout << "未找到此人。" << endl;
        }
    }
    cout << "请输入更改后的姓名：" << endl;
    String Name;
    cin >> Name;
    cout << Find->Name << "已更名为" << Name << endl;
    Find->Name = Name;
    return;
}

int main() {
    cout << "====================================" << endl;
    cout << "**          家谱管理系统          **" << endl;
    cout << "====================================" << endl;
    cout << "**       请选择要执行的操作       **" << endl;
    cout << "**          A--完善家谱           **" << endl;
    cout << "**          B--添加家庭成员       **" << endl;
    cout << "**          C--解散局部家庭       **" << endl;
    cout << "**          D--更改家庭成员姓名   **" << endl;
    cout << "**          E--退出程序           **" << endl;
    cout << "====================================" << endl;
    cout << "首先建立一个家谱！" << endl;
    cout << "请输入祖先的姓名:" << endl;
    String Ancestor;
    cin >> Ancestor;
    PushBack(First->Next, new Data(Ancestor));
    cout << "此家谱的祖先是：" << Ancestor << endl;
    while (1) {
        //初始化
        Data* Find = First;
        char Input;
        while (1) {
            cout << "请输入要执行的操作：";
            cin >>Input;
            if ((Input == 'A') || (Input == 'B') || (Input == 'C') || (Input == 'D') || (Input == 'E')) {
                break;
            }
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "输入有误。" << endl;
        }
        if (Input == 'E') {
            break;
        }
        else if (Input == 'A') {
            AddFamily();
        }
        else if (Input == 'B') {
            AddPeople();
        }
        else if (Input == 'C') {
            DeleteFamily();
        }
        else if (Input == 'D') {
            Exchange();
        }
    }
    system("pause");
}