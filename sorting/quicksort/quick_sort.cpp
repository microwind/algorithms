/**
 * 快速排序算法实现集合
 * 
 * 本文件包含7种不同的快速排序实现，涵盖了快速排序的主要算法变体：
 * - 不同的基准选择策略（中间、左侧、最后、第一个元素）
 * - 不同的扫描方式（相向扫描、单向扫描、双向扫描、三路分区）
 * - 不同的实现方式（递归、迭代、栈模拟）
 * - 不同的分区策略（Hoare分区、Lomuto分区、三路分区）
 * 
 * @author jarryli@gmail.com
 * @version 1.0
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <utility>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

/**
 * 打印数组指定范围内的元素
 * @param arr 目标数组
 * @param start 起始索引（包含）
 * @param end 结束索引（包含）
 */
void printArrayRange(const vector<int>& arr, int start, int end) {
    cout << "[";
    for (int i = start; i <= end; i++) {
        cout << arr[i];
        if (i < end) {
            cout << ", ";
        }
    }
    cout << "]";
}

/**
 * 打印整个数组的内容
 * @param arr 目标数组
 * @param label 打印标签
 */
void printArray(const vector<int>& arr, const string& label) {
    cout << label << ": [";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

/**
 * 快速排序1 - 标准递归版本
 * 
 * 算法特点：
 * - 使用中间元素作为基准，避免最坏情况
 * - 双向扫描：左右指针相向移动，减少交换次数
 * - 原地排序：不需要额外空间
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定
 */
void quickSort1(vector<int>& arr, int low, int high)
{
    // 步骤1：初始化指针和基准
    int i = low > 0 ? low : 0;  // 处理边界情况
    int j = high;
    int midIndex = (i + j) / 2;
    int pivot = arr[midIndex];

    // 步骤2：分区过程 - 双向扫描
    while (i <= j) {
        // 步骤2.1：左指针向右扫描，找到大于基准的元素
        while (arr[i] < pivot) {
            i++;
        }
        
        // 步骤2.2：右指针向左扫描，找到小于基准的元素
        while (arr[j] > pivot) {
            j--;
        }

        cout << "\r\n  low=" << low << ", high=" << high << ", i=" << i << ", j=" << j << ", midIndex=" << midIndex << ", pivot=" << pivot;

        // 步骤2.3：交换元素并缩小范围
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    
    // 步骤3：递归处理左右子数组
    if (low < j) {
        cout << "\r\n  low < j:recursion:  low=" << low << ", high=" << high << ", i=" << i << ", j=" << j << ", midIndex=" << midIndex << ", pivot=" << pivot;
        quickSort1(arr, low, j);
    }
    if (i < high) {
        cout << "\r\n  i < high:recursion:  low=" << low << ", high=" << high << ", i=" << i << ", j=" << j << ", midIndex=" << midIndex << ", pivot=" << pivot;
        quickSort1(arr, i, high);
    }
}

/**
 * 快速排序2 - 递归分区交换版本
 * 
 * 算法特点：
 * - 使用左侧第一个元素作为基准
 * - 单向扫描：从左向右一次性扫描
 * - Lomuto分区方案的变体
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定
 */
int partition(vector<int>& arr, int left, int right)
{
    // 步骤1：初始化基准和分区指针
    int pivotIndex = left;           // 基准位置
    int partitionIndex = pivotIndex + 1;  // 分区指针
    
    // 步骤2：遍历数组进行分区
    for (int i = partitionIndex; i <= right; i++) {
        // 步骤2.1：将小于基准的元素交换到左侧
        if (arr[i] < arr[pivotIndex]) {
            swap(arr[i], arr[partitionIndex]);
            partitionIndex++;  // 扩展小于基准的区域
        }
    }
    
    // 步骤3：将基准元素放到正确位置
    swap(arr[pivotIndex], arr[partitionIndex - 1]);
    
    // 调试输出
    cout << "\r\n";
    printArrayRange(arr, left, partitionIndex);
    cout << " partitionIndex=" << partitionIndex << ", arr[partitionIndex]=" << arr[partitionIndex] << " ";
    printArrayRange(arr, partitionIndex, right);
    
    return partitionIndex - 1;
}

void quickSort2(vector<int>& arr, int left, int right)
{
    // 步骤1：递归终止条件检查
    if (left < right) {
        // 步骤2：分区并获取基准位置
        int pivot = partition(arr, left, right);
        
        // 步骤3：递归处理左右子数组
        quickSort2(arr, left, pivot - 1);
        quickSort2(arr, pivot + 1, right);
    }
}

// ==================== 栈数据结构实现 ====================

/** 栈结构 - 用于非递归快速排序 */
struct stack_data {
    int top;
    int *data;
    int size;
};

/** 栈指针类型 */
typedef struct stack_data *Stack;

/** 创建栈 */
Stack stack_create(int max_size)
{
    Stack s = (Stack)malloc(sizeof(struct stack_data));
    s->data = (int *)malloc(max_size * sizeof(int));
    s->top = -1;
    s->size = max_size;
    return s;
}

/** 判断栈是否为空 */
bool stack_is_empty(Stack s)
{
    return s->top == -1;
}

/** 入栈 */
void stack_push(Stack s, int value)
{
    s->top++;
    s->data[s->top] = value;
}

/** 出栈 */
int stack_pop(Stack s)
{
    return s->data[s->top--];
}

/** 判断栈是否已满 */
bool stack_is_full(Stack s)
{
    return s->top == s->size - 1;
}

/**
 * 快速排序3 - 非递归版本
 * 
 * 算法特点：
 * - 使用栈模拟递归调用
 * - 双向扫描：左右指针相向移动
 * - 避免递归调用栈溢出
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(n) - 栈空间
 * 稳定性：不稳定
 */
void quickSort3(vector<int>& arr, int low, int high)
{
    // 步骤1：创建栈
    Stack stack = stack_create(high - low + 1);
    
    // 步骤2：初始范围入栈
    stack_push(stack, low);
    stack_push(stack, high);
    
    // 步骤3：循环处理栈中的范围
    while (!stack_is_empty(stack)) {
        // 步骤3.1：出栈获取当前处理范围
        int h = stack_pop(stack);
        int l = stack_pop(stack);
        
        // 步骤3.2：分区处理
        int i = l > 0 ? l : 0;
        int j = h;
        int midIndex = (i + j) / 2;
        int pivot = arr[midIndex];
        
        cout << "\r\nhigh - low = " << (h - l) << "\r\n";
        
        // 步骤3.3：双向扫描分区
        while (i <= j) {
            while (arr[i] < pivot) {
                i++;
            }
            while (arr[j] > pivot) {
                j--;
            }
            
            if (i <= j) {
                cout << "arr[i] < pivot: i=" << i << ", j=" << j << ", arr[i]=" << arr[i] << ", arr[j]=" << arr[j] << ", pivot=" << pivot << "\r\n";
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
        
        // 步骤3.4：将子范围入栈
        if (l < j) {
            stack_push(stack, l);
            stack_push(stack, j);
        }
        if (i < h) {
            stack_push(stack, i);
            stack_push(stack, h);
        }
    }
    
    // 步骤4：释放栈内存
    free(stack);
}

/**
 * Lomuto分区函数
 */
int partitionLomuto(vector<int>& arr, int low, int high) {
    // 步骤1：初始化基准和指针
    int pivot = arr[high];  // 最后一个元素作为基准
    int i = low - 1;           // 小于基准的元素的边界
    
    // 步骤2：遍历数组进行分区
    for (int j = low; j < high; j++) {
        // 步骤2.1：将小于基准的元素移到左边
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // 步骤3：将基准元素放到正确位置
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

/**
 * 快速排序4 - 迭代版本
 * 
 * 算法特点：
 * - 使用栈模拟递归调用
 * - Lomuto分区：最后元素基准，单向扫描
 * - 迭代实现：避免递归调用
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(n) - 栈空间
 * 稳定性：不稳定
 */
void quickSort4(vector<int>& arr, int size)
{
    cout << "\nquickSort4 迭代版本:\n";
    
    // 步骤1：创建栈
    Stack stack = stack_create(size);
    
    // 步骤2：初始范围入栈
    stack_push(stack, 0);
    stack_push(stack, size - 1);
    
    // 步骤3：循环处理栈中的范围
    while (!stack_is_empty(stack)) {
        // 步骤3.1：出栈获取当前处理范围
        int high = stack_pop(stack);
        int low = stack_pop(stack);
        
        // 步骤3.2：分区处理
        int pi = partitionLomuto(arr, low, high);
        
        // 步骤3.3：将子范围入栈
        if (pi - 1 > low) {
            stack_push(stack, low);
            stack_push(stack, pi - 1);
        }
        if (pi + 1 < high) {
            stack_push(stack, pi + 1);
            stack_push(stack, high);
        }
    }
    
    // 步骤4：释放栈内存
    free(stack);
}

/**
 * 快速排序5 - Lomuto分区递归版本
 * 
 * 算法特点：
 * - 使用最后一个元素作为基准
 * - 单向扫描：从左向右一次性扫描
 * - Lomuto分区：经典的分区方案
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定
 */
void quickSort5(vector<int>& arr, int size)
{
    cout << "\nquickSort5 Lomuto分区递归版本:\n";
    printArrayRange(arr, 0, size);
    
    // 步骤1：递归终止条件检查
    if (size <= 1) {
        return;
    }
    
    // 步骤2：分区并获取基准位置
    int pi = partitionLomuto(arr, 0, size - 1);
    
    // 步骤3：递归排序左右子数组
    if (pi > 0) {
        vector<int> leftArr(arr.begin(), arr.begin() + pi);
        quickSort5(leftArr, pi);
        for (int i = 0; i < pi; i++) {
            arr[i] = leftArr[i];
        }
    }
    if (pi < size - 1) {
        vector<int> rightArr(arr.begin() + pi + 1, arr.end());
        quickSort5(rightArr, size - pi - 1);
        for (int i = 0; i < size - pi - 1; i++) {
            arr[pi + 1 + i] = rightArr[i];
        }
    }
}

/**
 * 快速排序6 - Hoare分区递归版本
 * 
 * 算法特点：
 * - 使用第一个元素作为基准
 * - 双向扫描：左右指针同时向中间移动
 * - Hoare分区：经典的分区方案
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定
 */
void quickSort6(vector<int>& arr, int size)
{
    cout << "\nquickSort6 Hoare分区递归版本:\n";
    printArrayRange(arr, 0, size);
    
    // 步骤1：递归终止条件检查
    if (size <= 1) {
        return;
    }
    
    // 步骤2：初始化基准和双向指针
    int pivot = arr[0];     // 第一个元素作为基准
    int i = 1;             // 左指针
    int j = size - 1;       // 右指针
    
    // 步骤3：双向分区
    while (i <= j) {
        // 步骤3.1：左指针扫描，找到大于基准的元素
        while (i <= j && arr[i] <= pivot) {
            i++;
        }
        
        // 步骤3.2：右指针扫描，找到小于基准的元素
        while (i <= j && arr[j] > pivot) {
            j--;
        }
        
        // 步骤3.3：交换元素
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    
    // 步骤4：调整基准位置
    swap(arr[0], arr[j]);
    
    // 步骤5：递归处理左右子数组
    if (j > 0) {
        vector<int> leftArr(arr.begin(), arr.begin() + j);
        quickSort6(leftArr, j);
        for (int i = 0; i < j; i++) {
            arr[i] = leftArr[i];
        }
    }
    if (j < size - 1) {
        vector<int> rightArr(arr.begin() + j + 1, arr.end());
        quickSort6(rightArr, size - j - 1);
        for (int i = 0; i < size - j - 1; i++) {
            arr[j + 1 + i] = rightArr[i];
        }
    }
}

/**
 * 快速排序7 - 三路分区递归版本
 * 
 * 算法特点：
 * - 使用第一个元素作为基准
 * - 三路分区：处理重复元素，提高效率
 * - 递归优化：减少递归调用次数
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定
 */
void quickSort7(vector<int>& arr, int size)
{
    cout << "\nquickSort7 三路分区递归版本:\n";
    printArrayRange(arr, 0, size);
    
    // 步骤1：递归终止条件检查
    if (size <= 1) {
        return;
    }
    
    // 步骤2：初始化基准和三路指针
    int pivot = arr[0];      // 第一个元素作为基准
    int lt = 0;              // 小于基准的右边界
    int gt = size - 1;       // 大于基准的左边界
    int i = 1;               // 当前遍历指针
    
    // 步骤3：三路分区
    while (i <= gt) {
        if (arr[i] < pivot) {
            // 步骤3.1：小于基准，交换到左边
            swap(arr[lt], arr[i]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            // 步骤3.2：大于基准，交换到右边
            swap(arr[i], arr[gt]);
            gt--;
        } else {
            // 步骤3.3：等于基准，直接跳过
            i++;
        }
    }
    
    // 步骤4：递归处理
    if (lt > 0) {
        vector<int> leftArr(arr.begin(), arr.begin() + lt);
        quickSort7(leftArr, lt);
        for (int i = 0; i < lt; i++) {
            arr[i] = leftArr[i];
        }
    }
    if (gt < size - 1) {
        vector<int> rightArr(arr.begin() + gt + 1, arr.end());
        quickSort7(rightArr, size - gt - 1);
        for (int i = 0; i < size - gt - 1; i++) {
            arr[gt + 1 + i] = rightArr[i];
        }
    }
}

// ==================== 包装函数 ====================

void quickSort1Wrapper(vector<int>& arr) {
    quickSort1(arr, 0, arr.size() - 1);
    cout << "排序后数组: ";
    printArray(arr, "");
}

void quickSort2Wrapper(vector<int>& arr) {
    quickSort2(arr, 0, arr.size() - 1);
    cout << "排序后数组: ";
    printArray(arr, "");
}

void quickSort3Wrapper(vector<int>& arr) {
    quickSort3(arr, 0, arr.size() - 1);
    cout << "排序后数组: ";
    printArray(arr, "");
}

void quickSort4Wrapper(vector<int>& arr) {
    quickSort4(arr, arr.size());
    cout << "排序后数组: ";
    printArray(arr, "");
}

void quickSort5Wrapper(vector<int>& arr) {
    quickSort5(arr, arr.size());
    cout << "排序后数组: ";
    printArray(arr, "");
}

void quickSort6Wrapper(vector<int>& arr) {
    quickSort6(arr, arr.size());
    cout << "排序后数组: ";
    printArray(arr, "");
}

void quickSort7Wrapper(vector<int>& arr) {
    quickSort7(arr, arr.size());
    cout << "排序后数组: ";
    printArray(arr, "");
}

// ==================== 性能测试 ====================

/**
 * 性能测试辅助函数
 */
void performanceTest(function<void(vector<int>&)> sortFunc, const vector<int>& arr, const string& name) {
    // 创建数组副本，避免修改原数组
    vector<int> testArr = arr;
    cout << name << "原始数组: ";
    printArray(testArr, "");
    
    // 开始计时
    auto start = high_resolution_clock::now();
    sortFunc(testArr);
    auto end = high_resolution_clock::now();
    
    // 计算耗时
    auto duration = duration_cast<microseconds>(end - start);
    cout << name << ": " << fixed << setprecision(3) << duration.count() / 1000.0 << "ms" << endl;
    
    cout << name << "排序结果: ";
    printArray(testArr, "");
    cout << endl; // 空行分隔
}

// ==================== 主程序 ====================

int main() {
    // 测试数据
    vector<int> testData = {7, 11, 9, 10, 12, 13, 8};
    
    // 测试1：标准递归版本
    performanceTest(quickSort1Wrapper, testData, "标准递归版本");
    
    // 测试2：递归分区交换版本
    performanceTest(quickSort2Wrapper, testData, "递归分区交换版本");
    
    // 测试3：非递归版本
    performanceTest(quickSort3Wrapper, testData, "非递归版本");
    
    // 测试4：迭代版本
    performanceTest(quickSort4Wrapper, testData, "迭代版本");
    
    // 测试5：Lomuto分区递归版本
    performanceTest(quickSort5Wrapper, testData, "Lomuto分区递归版本");
    
    // 测试6：Hoare分区递归版本
    performanceTest(quickSort6Wrapper, testData, "Hoare分区递归版本");
    
    // 测试7：三路分区递归版本
    performanceTest(quickSort7Wrapper, testData, "三路分区递归版本");
    
    cout << "=== 算法对比总结 ===" << endl;
    cout << "1. 标准递归版本：中间基准，相向扫描" << endl;
    cout << "2. 递归分区交换版本：左侧基准，单向扫描" << endl;
    cout << "3. 非递归版本：栈模拟，避免递归" << endl;
    cout << "4. 迭代版本：Lomuto分区，栈模拟" << endl;
    cout << "5. Lomuto分区递归版本：最后基准，单向扫描" << endl;
    cout << "6. Hoare分区递归版本：第一个基准，双向扫描" << endl;
    cout << "7. 三路分区递归版本：第一个基准，三路分区" << endl;
    
    return 0;
}
/*打印结果
jarry@Mac quicksort % g++ quick_sort.cpp -o quick_sort && ./quick_sort
标准递归版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

  low=0, high=6, i=1, j=6, midIndex=3, pivot=10
  low=0, high=6, i=3, j=3, midIndex=3, pivot=10
  low < j:recursion:  low=0, high=6, i=4, j=2, midIndex=3, pivot=10
  low=0, high=2, i=1, j=1, midIndex=1, pivot=8
  i < high:recursion:  low=0, high=6, i=4, j=2, midIndex=3, pivot=10
  low=4, high=6, i=5, j=6, midIndex=5, pivot=13
  low < j:recursion:  low=4, high=6, i=6, j=5, midIndex=5, pivot=13
  low=4, high=5, i=4, j=5, midIndex=4, pivot=12排序后数组: : [7, 8, 9, 10, 11, 12, 13]
标准递归版本: 0.030ms
标准递归版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

递归分区交换版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

[7, 11] partitionIndex=1, arr[partitionIndex]=11 [11, 9, 10, 12, 13, 8]
[8, 9, 10, 11, 13] partitionIndex=5, arr[partitionIndex]=13 [13, 12]
[8, 9] partitionIndex=2, arr[partitionIndex]=9 [9, 10]
[9, 10] partitionIndex=3, arr[partitionIndex]=10 [10]
[12, 13, 0] partitionIndex=7, arr[partitionIndex]=0 []排序后数组: : [7, 8, 9, 10, 11, 12, 13]
递归分区交换版本: 0.052ms
递归分区交换版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

非递归版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

high - low = 6
arr[i] < pivot: i=1, j=6, arr[i]=11, arr[j]=8, pivot=10
arr[i] < pivot: i=3, j=3, arr[i]=10, arr[j]=10, pivot=10

high - low = 2
arr[i] < pivot: i=5, j=6, arr[i]=13, arr[j]=11, pivot=13

high - low = 1
arr[i] < pivot: i=4, j=5, arr[i]=12, arr[j]=11, pivot=12

high - low = 2
arr[i] < pivot: i=1, j=1, arr[i]=8, arr[j]=8, pivot=8
排序后数组: : [7, 8, 9, 10, 11, 12, 13]
非递归版本: 0.027ms
非递归版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

迭代版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

quickSort4 迭代版本:
排序后数组: : [7, 8, 9, 10, 11, 12, 13]
迭代版本: 0.006ms
迭代版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

Lomuto分区递归版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

quickSort5 Lomuto分区递归版本:
[7, 11, 9, 10, 12, 13, 8, 0]
quickSort5 Lomuto分区递归版本:
[7, 0]
quickSort5 Lomuto分区递归版本:
[9, 10, 12, 13, 11, 0]
quickSort5 Lomuto分区递归版本:
[9, 10, 0]
quickSort5 Lomuto分区递归版本:
[9, 0]
quickSort5 Lomuto分区递归版本:
[13, 12, 0]
quickSort5 Lomuto分区递归版本:
[13, 0]排序后数组: : [7, 8, 9, 10, 11, 12, 13]
Lomuto分区递归版本: 0.180ms
Lomuto分区递归版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

Hoare分区递归版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

quickSort6 Hoare分区递归版本:
[7, 11, 9, 10, 12, 13, 8, 0]
quickSort6 Hoare分区递归版本:
[11, 9, 10, 12, 13, 8, 0]
quickSort6 Hoare分区递归版本:
[8, 9, 10, 0]
quickSort6 Hoare分区递归版本:
[9, 10, 0]
quickSort6 Hoare分区递归版本:
[10, 0]
quickSort6 Hoare分区递归版本:
[13, 12, 0]
quickSort6 Hoare分区递归版本:
[12, 0]排序后数组: : [7, 8, 9, 10, 11, 12, 13]
Hoare分区递归版本: 0.034ms
Hoare分区递归版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

三路分区递归版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

quickSort7 三路分区递归版本:
[7, 11, 9, 10, 12, 13, 8, 0]
quickSort7 三路分区递归版本:
[9, 10, 12, 13, 8, 11, 0]
quickSort7 三路分区递归版本:
[8, 0]
quickSort7 三路分区递归版本:
[13, 12, 11, 10, 0]
quickSort7 三路分区递归版本:
[12, 11, 10, 0]
quickSort7 三路分区递归版本:
[11, 10, 0]
quickSort7 三路分区递归版本:
[10, 0]排序后数组: : [7, 8, 9, 10, 11, 12, 13]
三路分区递归版本: 0.034ms
三路分区递归版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 标准递归版本：中间基准，相向扫描
2. 递归分区交换版本：左侧基准，单向扫描
3. 非递归版本：栈模拟，避免递归
4. 迭代版本：Lomuto分区，栈模拟
5. Lomuto分区递归版本：最后基准，单向扫描
6. Hoare分区递归版本：第一个基准，双向扫描
7. 三路分区递归版本：第一个基准，三路分区
*/