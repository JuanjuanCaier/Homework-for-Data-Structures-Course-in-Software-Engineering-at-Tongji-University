/*JuanjuanCaier-123456*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAXSIZE 100000
int NumberOfRand = 0;//随机数数目
int Rand[MAXSIZE] = { 0 };

//生成随机数
void CreatRand() {
    for (int i = 0; i < NumberOfRand; i++) {
        Rand[i] = rand();
    }
}
//冒泡排序法
void BubbleSort() {
    auto Start = chrono::high_resolution_clock::now();
    long long int ChangeTimes = 0;
    for (int i = 0; i < NumberOfRand - 1; i++) {
        for (int j = 0; j < NumberOfRand - 1 - i; j++) {
            //交换
            if (Rand[j] > Rand[j + 1]) {
                ChangeTimes++;
                int Temp = Rand[j];
                Rand[j] = Rand[j + 1];
                Rand[j + 1] = Temp;
            }
        }
    }
    auto End = chrono::high_resolution_clock::now();
    chrono::duration<double> Time = End - Start;
    cout << "冒泡排序所用时间（秒）：     " << Time.count() << endl;
    cout << "冒泡排序交换次数：           " << ChangeTimes << endl << endl;
}
//选择排序法
void SelectionSort() {
    auto Start = chrono::high_resolution_clock::now();
    long long int ChangeTimes = 0;
    for (int i = 0; i < NumberOfRand - 1; i++) {
        //假设当前元素为最小值
        int MinIndex = i;
        //在剩余未排序元素中寻找最小值
        for (int j = i + 1; j < NumberOfRand; j++) {
            if (Rand[j] < Rand[MinIndex]) {
                MinIndex = j;
            }
        }
        //交换找到的最小值与当前元素
        ChangeTimes++;
        int Temp = Rand[i];
        Rand[i] = Rand[MinIndex];
        Rand[MinIndex] = Temp;
    }
    auto End = chrono::high_resolution_clock::now();
    chrono::duration<double> Time = End - Start;
    cout << "选择排序所用时间（秒）：     " << Time.count() << endl;
    cout << "选择排序交换次数：           " << ChangeTimes << endl << endl;
}
//直接插入排序法
void InsertionSort() {
    auto Start = chrono::high_resolution_clock::now();
    long long int ChangeTimes = 0;
    for (int i = 1; i < NumberOfRand; i++) {
        int Key = Rand[i];//当前需要插入的元素
        int j = i - 1;
        //将Rand[0..i-1]中大于Key的元素向后移动一位
        while (j >= 0 && Rand[j] > Key) {
            ChangeTimes++;
            Rand[j + 1] = Rand[j];
            j--;
        }
        Rand[j + 1] = Key; //插入key到正确的位置
    }
    auto End = chrono::high_resolution_clock::now();
    chrono::duration<double> Time = End - Start;
    cout << "直接插入排序所用时间（秒）： " << Time.count() << endl;
    cout << "直接插入排序交换次数：       " << ChangeTimes << endl << endl;
}
//希尔排序法
void ShellSort() {
    auto Start = chrono::high_resolution_clock::now();
    long long int ChangeTimes = 0;
    //初始间隔大小设置为数组长度的一半，然后逐渐减小
    for (int gap = NumberOfRand / 2; gap > 0; gap /= 2) {
        //对每个间隔进行插入排序
        for (int i = gap; i < NumberOfRand; i++) {
            int temp = Rand[i];
            int j;
            for (j = i; j >= gap && Rand[j - gap] > temp; j -= gap) {
                ChangeTimes++;
                Rand[j] = Rand[j - gap];
            }
            Rand[j] = temp;
        }
    }
    auto End = chrono::high_resolution_clock::now();
    chrono::duration<double> Time = End - Start;
    cout << "希尔排序所用时间（秒）：     " << Time.count() << endl;
    cout << "希尔排序交换次数：           " << ChangeTimes << endl << endl;
}
//快速排序的分区函数
int Partition(int low, int high,long long int& ChangeTimes) {
    int pivot = Rand[high];//选择最后一个元素作为枢轴
    int i = low - 1;//较小元素的索引

    for (int j = low; j < high; ++j) {
        if (Rand[j] < pivot) {
            ++i;//增加较小元素的索引
            ChangeTimes++;
            swap(Rand[i], Rand[j]);
        }
    }
    ChangeTimes++;
    swap(Rand[i + 1], Rand[high]);//将枢轴放到正确的位置
    return i + 1;
}

//快速排序法
void QuickSort(int low, int high, int Depth, long long int& ChangeTimes) {
    auto Start = chrono::high_resolution_clock::now();
    if (low < high) {
        int pi = Partition(low, high,ChangeTimes);//获取分区索引
        //递归地对枢轴左右两侧的子数组进行排序
        QuickSort(low, pi - 1, 0,ChangeTimes);
        QuickSort(pi + 1, high, 0, ChangeTimes);
    }
    //确保只输出一次
    if (Depth == 1) {
        auto End = chrono::high_resolution_clock::now();
        chrono::duration<double> Time = End - Start;
        cout << "快速排序所用时间（秒）：     " << Time.count() << endl;
        cout << "快速排序交换次数：           " << ChangeTimes << endl << endl;
    }
}
//堆调整函数，用于维护堆的性质
void Heapify(int n, int i,long long int& ChangeTimes) {
    int largest = i;//初始化largest为根节点
    int left = 2 * i + 1;//左子节点
    int right = 2 * i + 2;//右子节点
    //如果左子节点大于根节点
    if (left < n && Rand[left] > Rand[largest]) {
        ChangeTimes++;
        largest = left;
    }
    //如果右子节点大于目前最大的节点
    if (right < n && Rand[right] > Rand[largest]) {
        ChangeTimes++;
        largest = right;
    }
    //如果largest不是根节点
    if (largest != i) {
        swap(Rand[i], Rand[largest]);//交换
        ChangeTimes++;
        //递归地堆化受影响的子树
        Heapify(n, largest, ChangeTimes);
    }
}
//堆排序函数
void HeapSort() {
    auto Start = chrono::high_resolution_clock::now();
    long long int ChangeTimes = 0;
    //构建最大堆
    for (int i = NumberOfRand / 2 - 1; i >= 0; i--)
        Heapify(NumberOfRand, i,ChangeTimes);
    //一个一个地从堆顶取出元素，并放到数组末尾（已排序部分）
    for (int i = NumberOfRand - 1; i >= 0; i--) {
        swap(Rand[0], Rand[i]);//交换
        ChangeTimes++;
        Heapify(i, 0,ChangeTimes);//重新堆化
    }
    auto End = chrono::high_resolution_clock::now();
    chrono::duration<double> Time = End - Start;
    cout << "堆排序所用时间（秒）：       " << Time.count() << endl;
    cout << "堆排序交换次数：             " << ChangeTimes << endl << endl;
}
//归并函数，用于合并两个已排序的子数组
void Merge(int left, int mid, int right, long long int& CompareTimes) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    //创建临时数组
    int L[MAXSIZE/2] = { 0 };
    int R[MAXSIZE/2] = { 0 };
    //拷贝数据到临时数组L[]和R[]
    for (int i = 0; i < n1; i++)
        L[i] = Rand[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = Rand[mid + 1 + i];
    //归并临时数组到arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        CompareTimes++;
        if (L[i] <= R[j]) {
            Rand[k] = L[i];
            i++;
        }
        else {
            Rand[k] = R[j];
            j++;
        }
        k++;
    }
    //拷贝剩余的元素（如果有）
    while (i < n1) {
        Rand[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        Rand[k] = R[j];
        j++;
        k++;
    }
}
//归并排序法
void MergeSort(int left, int right,int Depth, long long int& CompareTimes) {
    auto Start = chrono::high_resolution_clock::now();
    if (left < right) {
        int mid = left + (right - left) / 2; // 防止溢出
        //递归地对两个子数组进行排序
        MergeSort(left, mid,0,CompareTimes);
        MergeSort(mid + 1, right,0, CompareTimes);
        //合并两个已排序的子数组
        Merge(left, mid, right,CompareTimes);
    }
    if (Depth == 1) {
        auto End = chrono::high_resolution_clock::now();
        chrono::duration<double> Time = End - Start;
        cout << "归并排序所用时间（秒）：     " << Time.count() << endl;
        cout << "归并排序比较次数：           " << CompareTimes << endl << endl;
    }
}
//获取数字Num在Digit位置上的值（0-9）
int GetDigit(int Num, int Digit) {
    return (Num / static_cast<int>(pow(10, Digit))) % 10;
}
//计数排序，用于基数排序中的每一位
void CountingSort(int Size, int Digit,long long int& ChangeTimes) {
    int Output[MAXSIZE];//输出数组
    int Count[10] = { 0 };//计数数组，大小为基数10
    //统计每个数字在Digit位置上出现的次数
    for (int i = 0; i < Size; ++i) {
        int DigitValue = GetDigit(Rand[i], Digit);
        Count[DigitValue]++;
    }
    //更改Count数组，使其包含实际的位置
    for (int i = 1; i < 10; ++i) {
        Count[i] += Count[i - 1];
    }
    //建立输出数组
    for (int i = Size - 1; i >= 0; --i) {
        int DigitValue = GetDigit(Rand[i], Digit);
        Output[Count[DigitValue] - 1] = Rand[i];
        Count[DigitValue]--;
    }
    //将排序后的数据复制回原数组
    for (int i = 0; i < Size; ++i) {
        Rand[i] = Output[i];
    }
}
//基数排序法
void RadixSort(int Size) {
    auto Start = chrono::high_resolution_clock::now();
    long long int ChangeTimes = 0;
    //找到数组中的最大值，以确定最大位数
    int MaxVal = *max_element(Rand, Rand + Size);
    int MaxDigits = static_cast<int>(log10(MaxVal)) + 1;
    //从最低有效位到最高有效位进行计数排序
    for (int Digit = 0; Digit < MaxDigits; Digit++) {
        CountingSort(Size, Digit,ChangeTimes);
    }
    auto End = chrono::high_resolution_clock::now();
    chrono::duration<double> Time = End - Start;
    cout << "基数排序所用时间（秒）：     " << Time.count() << endl;
    cout << "基数排序交换次数：           " << ChangeTimes << endl << endl;
}
//界面及选择
int main()
{
    //随机数种子
    srand((unsigned int)(time(0)));
    //界面ui
    cout << "**           排序算法比较           **" << endl;
    cout << "======================================" << endl;
    cout << "**          1 --- 冒泡排序          **" << endl;
    cout << "**          2 --- 选择排序          **" << endl;
    cout << "**          3 --- 直接插入排序      **" << endl;
    cout << "**          4 --- 希尔排序          **" << endl;
    cout << "**          5 --- 快速排序          **" << endl;
    cout << "**          6 --- 堆排序            **" << endl;
    cout << "**          7 --- 归并排序          **" << endl;
    cout << "**          8 --- 基数排序          **" << endl;
    cout << "**          9 --- 退出程序          **" << endl;
    cout << "======================================" << endl;
    //读取要生成的随机数的数目
    while (1) {
        cout << "请输入要产生的随机数的个数：";
        cin >> NumberOfRand;
        if (NumberOfRand > 0 && NumberOfRand <= MAXSIZE) {
            break;
        }
        cout << "输入有误。" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    cout << endl;
    while (1) {
        //生成随机数
        CreatRand();
        cout << "请选择排序算法：             ";
        int Choice = 0;
        cin >> Choice;
        if (Choice == 1) {
            BubbleSort();
        }
        else if (Choice == 2) {
            SelectionSort();
        }
        else if (Choice == 3) {
            InsertionSort();
        }
        else if (Choice == 4) {
            ShellSort();
        }
        else if (Choice == 5) {
            long long int ChangeTimes = 0;
            QuickSort(0, NumberOfRand - 1, 1, ChangeTimes);
        }
        else if (Choice == 6) {
            HeapSort();
        }
        else if (Choice == 7) {
            long long int CompareTimes = 0;
            MergeSort(0, NumberOfRand - 1, 1, CompareTimes);
        }
        else if (Choice == 8) {
            RadixSort(NumberOfRand);
        }
        else if (Choice == 9) {
            break;
        }
        else {
            cout << "输入有误。" << endl;
        }
    }
    system("pause");
    return 0;
}