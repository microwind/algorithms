/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 选择排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

/**
 * 打印数组内容的辅助函数
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
 * 性能测试辅助函数
 */
void performanceTest(function<void(vector<int>&)> sortFunc, const vector<int>& arr, const string& name) {
    // 创建数组副本，避免修改原数组
    vector<int> testArr = arr;
    printArray(testArr, name + "原始数组");
    
    // 开始计时
    auto start = high_resolution_clock::now();
    sortFunc(testArr);
    auto end = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(end - start);
    cout << name << ": " << fixed << setprecision(3) << duration.count() / 1000.0 << "ms" << endl;
    printArray(testArr, name + "排序结果");
    cout << endl; // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
vector<int> testData = {7, 11, 9, 10, 12, 13, 8};

/**
 * 选择排序基础版本
 * 
 * 算法原理：
 * 1. 将数组分为两部分：左侧已排序区域，右侧待排序区域
 * 2. 每次从待排序区域中选择最小元素
 * 3. 将最小元素与待排序区域的第一个元素交换
 * 4. 重复以上过程，直到所有元素排序完成
 * 
 * 生活类比：就像在队伍中挑选最矮的人站到最前面，
 * 然后在剩下的人中再挑选最矮的站到第二个位置，依此类推
 * 
 * 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
 * 空间复杂度：O(1) - 只使用常数个额外变量
 * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
 */
void selectionSort1(vector<int>& arr) {
    cout << "selectionSort1 basic:" << endl;
    int n = arr.size();
    // 外循环：控制排序轮数，每轮确定一个最小值的位置
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i; // 记录最小元素的索引
        
        // 内循环：在未排序区域中查找最小元素
        for (int j = i + 1; j < n; j++) {
            // 关键点：找到更小的元素，更新最小值索引
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // 交换最小元素到当前轮次的起始位置
        if (minIndex != i) {
            // C++特点：使用swap函数
            swap(arr[i], arr[minIndex]);
        }
    }
    printArray(arr, "排序后数组");
}

/**
 * 选择排序降序版本
 * 
 * 算法思路：
 * 与基础版本相反，每次选择最大元素
 * 将最大元素与待排序区域的第一个元素交换
 * 
 * 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
 * 空间复杂度：O(1) - 只使用常数个额外变量
 * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
 */
void selectionSort2(vector<int>& arr) {
    cout << "selectionSort2 descending:" << endl;
    int n = arr.size();
    // 外循环：控制排序轮数，每轮确定一个最大值的位置
    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i; // 记录最大元素的索引
        
        // 内循环：在未排序区域中查找最大元素
        for (int j = i + 1; j < n; j++) {
            // 关键点：找到更大的元素，更新最大值索引
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j;
            }
        }
        
        // 交换最大元素到当前轮次的起始位置
        if (maxIndex != i) {
            // C++特点：使用swap函数
            swap(arr[i], arr[maxIndex]);
        }
    }
    printArray(arr, "排序后数组");
}

/**
 * 选择排序优化版本 - 双向选择
 * 
 * 优化思路：
 * 每轮同时选择最小和最大元素
 * 将最小元素放到左侧，最大元素放到右侧
 * 减少排序轮数，提高效率
 * 
 * 优化效果：
 * - 减少了排序轮数，从n轮减少到n/2轮
 * - 每轮需要进行两次查找，但总体效率提升
 * 
 * 时间复杂度：O(n²)，空间复杂度：O(1)
 * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
 */
void selectionSort3(vector<int>& arr) {
    cout << "selectionSort3 bidirectional:" << endl;
    int n = arr.size();
    int left = 0;
    int right = n - 1;
    
    // 外循环：控制排序轮数，每轮确定最小和最大值的位置
    while (left < right) {
        int minIndex = left;
        int maxIndex = left;
        
        // 内循环：在未排序区域中查找最小和最大元素
        for (int i = left; i <= right; i++) {
            // 关键点：同时查找最小和最大元素
            if (arr[i] < arr[minIndex]) {
                minIndex = i;
            }
            if (arr[i] > arr[maxIndex]) {
                maxIndex = i;
            }
        }
        
        // 交换最小元素到左侧
        if (minIndex != left) {
            swap(arr[left], arr[minIndex]);
        }
        
        // 优化点：如果最大元素原本在left位置，经过交换后位置变为minIndex
        if (maxIndex == left) {
            maxIndex = minIndex;
        }
        
        // 交换最大元素到右侧
        if (maxIndex != right) {
            swap(arr[right], arr[maxIndex]);
        }
        
        left++;
        right--;
    }
    printArray(arr, "排序后数组");
}

/**
 * 堆化辅助函数
 */
void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // 初始化最大元素为根节点
    int left = 2 * i + 1; // 左子节点
    int right = 2 * i + 2; // 右子节点
    
    // 如果左子节点大于根节点
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    // 如果右子节点大于当前最大节点
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    // 如果最大节点不是根节点，交换并继续堆化
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

/**
 * 选择排序 - 堆优化版本
 * 
 * 算法思路：
 * 利用堆的性质来快速找到最大/最小元素
 * 每次从堆顶取出最大/最小元素
 * 重新调整堆结构
 * 
 * 时间复杂度：O(n log n)，空间复杂度：O(1)
 * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
 */
void selectionSort4(vector<int>& arr) {
    cout << "selectionSort4 heap optimized:" << endl;
    int n = arr.size();
    
    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // 逐个取出堆顶元素
    for (int i = n - 1; i > 0; i--) {
        // 关键点：交换堆顶元素（最大）与末尾元素
        swap(arr[0], arr[i]);
        
        // 重新调整堆
        heapify(arr, i, 0);
    }
    
    printArray(arr, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

int main() {
    // 测试1：基础选择版本
    performanceTest(selectionSort1, testData, "基础选择版本");

    // 测试2：降序版本
    performanceTest(selectionSort2, testData, "降序版本");

    // 测试3：双向选择版本
    performanceTest(selectionSort3, testData, "双向选择版本");

    // 测试4：堆优化版本
    performanceTest(selectionSort4, testData, "堆优化版本");

    cout << "=== 算法对比总结 ===" << endl;
    cout << "1. 基础版本：简单易懂，适合学习算法原理" << endl;
    cout << "2. 降序版本：展示算法灵活性，可按需排序" << endl;
    cout << "3. 双向版本：同时选择最大最小，效率提升" << endl;
    cout << "4. 堆优化版本：利用堆结构，复杂度优化" << endl;

    return 0;
}

/*
打印结果
jarry@Mac selectionsort % g++ selection_sort.cpp -o selection_sort && ./selection_sort
基础选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort1 basic:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
基础选择版本: 0.125ms
基础选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort2 descending:
排序后数组: [13, 12, 11, 10, 9, 8, 7]
降序版本: 0.042ms
降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]

双向选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort3 bidirectional:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
双向选择版本: 0.042ms
双向选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

堆优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort4 heap optimized:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
堆优化版本: 0.042ms
堆优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 基础版本：简单易懂，适合学习算法原理
2. 降序版本：展示算法灵活性，可按需排序
3. 双向版本：同时选择最大最小，效率提升
4. 堆优化版本：利用堆结构，复杂度优化
*/
