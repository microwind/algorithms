/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 选择排序算法实现
 * 提供5种不同的实现方式，适合不同场景和性能需求
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
 * 选择排序基础版本 - 标准版：原地交换
 *
 * 算法原理：
 * 1. 将数组分为两部分：左侧已排序区域，右侧待排序区域
 * 2. 每次从待排序区域中选择最小元素
 * 3. 将最小元素与待排序区域的第一个元素交换
 * 4. 重复以上过程，直到所有元素排序完成
 *
 * ## 实现步骤
 * 1. 外循环遍历数组，每轮确定一个最小值的位置
 * 2. 内循环在未排序区域中查找最小元素
 * 3. 记录最小值和其索引位置
 * 4. 将最小元素交换到当前轮次的起始位置
 *
 * @param arr - 待排序的整数向量
 * @return vector<int> - 排序后的向量
 */
vector<int> selectionSort1(vector<int> arr)
{
    cout << "selectionSort1 basic:" << endl;
    // 初始化变量
    int min_value, min_idx;
    int len = arr.size();
    
    // 外循环：每轮确定一个最小值
    for (int i = 0; i < len - 1; i++)
    {
        // 假设当前位置为最小值
        min_value = arr[i];
        min_idx = i;
        int j = i + 1;
        
        // 内循环：在未排序区域查找最小值
        for (; j < len; j++)
        {
            if (arr[j] < min_value)
            {
                min_value = arr[j];
                min_idx = j;
            }
        }
        
        // 输出调试信息
        cout << "\r\n i=" << i << " j=" << j << " min_value=" << min_value << " min_idx=" << min_idx;
        
        // 交换最小值到正确位置
        if (min_idx != i)
        {
            swap(arr[i], arr[min_idx]);
        }
    }
    return arr;
}

/**
 * 根据下标移除向量项目的辅助函数
 *
 * ## 实现原理
 * - 从指定索引位置开始，将后续元素向前移动一位
 * - 覆盖要删除的元素，实现向量元素的"删除"
 *
 * ## 实现步骤
 * 1. 从指定索引开始遍历向量
 * 2. 将每个位置的后一个元素前移
 * 3. 删除最后一个元素
 *
 * @param arr - 整数向量引用
 * @param idx - 要移除的元素索引
 * @return int - 成功返回1
 */
int removeIndex(vector<int>& arr, int idx)
{
    // 边界检查
    if (idx < 0 || idx >= static_cast<int>(arr.size())) {
        return 0; // 索引无效
    }
    
    // 元素前移
    for (size_t i = idx; i < arr.size() - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    
    // 删除最后一个元素
    arr.pop_back();
    return 1;
}

/**
 * 选择排序新建数组版本 - 无需交换
 *
 * 算法思路：
 * 1. 创建一个新向量来存储排序结果
 * 2. 每次从原向量中找到最小值
 * 3. 将最小值添加到新向量
 * 4. 从原向量中删除该最小值
 * 5. 重复直到原向量为空
 *
 * ## 实现步骤
 * 1. 初始化新向量和索引
 * 2. 外循环控制选择轮数
 * 3. 内循环查找当前最小值
 * 4. 将最小值添加到新向量
 * 5. 从原向量中移除已选择的元素
 * 6. 调整循环变量以适应向量长度变化
 *
 * @param arr - 待排序的整数向量
 * @return vector<int> - 排序后的新向量
 */
vector<int> selectionSort2(vector<int> arr)
{
    cout << "selectionSort2 new array:" << endl;
    // 初始化变量
    int min_value, min_idx;
    vector<int> new_arr;
    int len = arr.size();
    
    // 外循环：每轮选择一个最小值
    for (int i = 0; i < len; i++)
    {
        // 假设当前位置为最小值
        min_value = arr[i];
        min_idx = i;
        int j = i + 1;
        
        // 内循环：在剩余元素中查找最小值
        for (; j < len; j++)
        {
            if (arr[j] < min_value)
            {
                min_value = arr[j];
                min_idx = j;
            }
        }
        
        // 输出调试信息
        cout << "\r\n i=" << i << " j=" << j << " min_value=" << min_value << " min_idx=" << min_idx;
        
        // 添加最小值到新向量
        new_arr.push_back(min_value);
        
        // 从原向量中移除已选择的元素
        removeIndex(arr, min_idx);
        len--;      // 向量长度减1
        i--;        // 循环变量减1，补偿索引变化
    }
    return new_arr;
}

/**
 * 选择排序降序版本
 *
 * 算法思路：
 * 与基础版本相反，每次选择最大元素
 * 将最大元素与待排序区域的第一个元素交换
 *
 * ## 实现步骤
 * 1. 外循环控制排序轮数，每轮确定一个最大值的位置
 * 2. 内循环在未排序区域中查找最大元素
 * 3. 记录最大值和其索引位置
 * 4. 将最大元素交换到当前轮次的起始位置
 */
void selectionSort3(vector<int>& arr) {
    cout << "selectionSort3 descending:" << endl;
    int n = arr.size();
    
    // 外循环：每轮确定一个最大值
    for (int i = 0; i < n - 1; i++) {
        // 假设当前位置为最大值
        int maxIndex = i;
        
        // 内循环：在未排序区域查找最大值
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j;
            }
        }
        
        // 交换最大元素到正确位置
        if (maxIndex != i) {
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
 * ## 实现步骤
 * 1. 初始化左右边界指针
 * 2. 外循环控制排序轮数，同时处理两端
 * 3. 内循环在未排序区域中查找最小和最大元素
 * 4. 交换最小元素到左侧，最大元素到右侧
 * 5. 调整边界指针
 */
void selectionSort4(vector<int>& arr) {
    cout << "selectionSort4 bidirectional:" << endl;
    int n = arr.size();
    int left = 0;
    int right = n - 1;
    
    // 外循环：同时处理左右两端
    while (left < right) {
        int minIndex = left;
        int maxIndex = left;
        
        // 内循环：同时查找最小和最大元素
        for (int i = left; i <= right; i++) {
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
        
        // 处理最大元素位置变化的特殊情况
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
 * ## 实现步骤
 * 1. 构建最大堆
 * 2. 逐个取出堆顶元素（最大值）
 * 3. 将堆顶元素与末尾元素交换
 * 4. 重新调整堆结构
 * 5. 重复直到堆为空
 */
void selectionSort5(vector<int>& arr) {
    cout << "selectionSort5 heap optimized:" << endl;
    int n = arr.size();
    
    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // 逐个取出堆顶元素
    for (int i = n - 1; i > 0; i--) {
        // 交换堆顶与末尾元素
        swap(arr[0], arr[i]);
        
        // 重新调整堆
        heapify(arr, i, 0);
    }
    
    printArray(arr, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

int main() {
    cout << "\n=== 算法性能对比 ===" << endl;
    
    // 测试1：基础选择版本（直接测试，不使用performanceTest）
    cout << "基础选择版本原始数组: ";
    printArray(testData, "");
    vector<int> temp_arr1 = testData;
    auto start1 = high_resolution_clock::now();
    vector<int> result1 = selectionSort1(temp_arr1);
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(end1 - start1);
    cout << "基础选择版本: " << fixed << setprecision(3) << duration1.count() / 1000.0 << "ms" << endl;
    cout << "基础选择版本排序结果: ";
    printArray(result1, "");
    cout << endl;

    // 测试2：新建数组版本（直接测试，不使用performanceTest）
    cout << "新建数组版本原始数组: ";
    printArray(testData, "");
    vector<int> temp_arr2 = testData;
    auto start2 = high_resolution_clock::now();
    vector<int> result2 = selectionSort2(temp_arr2);
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(end2 - start2);
    cout << "新建数组版本: " << fixed << setprecision(3) << duration2.count() / 1000.0 << "ms" << endl;
    cout << "新建数组版本排序结果: ";
    printArray(result2, "");
    cout << endl;

    // 测试3：降序版本
    performanceTest(selectionSort3, testData, "降序版本");

    // 测试4：双向选择版本
    performanceTest(selectionSort4, testData, "双向选择版本");

    // 测试5：堆优化版本
    performanceTest(selectionSort5, testData, "堆优化版本");

    cout << "=== 算法对比总结 ===" << endl;
    cout << "1. 基础版本：标准版，原地交换，包含详细调试信息" << endl;
    cout << "2. 新建数组版本：无需交换，避免交换操作" << endl;
    cout << "3. 降序版本：展示算法灵活性，可按需排序" << endl;
    cout << "4. 双向版本：同时选择最大最小，效率提升" << endl;
    cout << "5. 堆优化版本：利用堆结构，复杂度优化" << endl;

    return 0;
}

/*打印结果
jarry@Mac selectionsort % g++ selection_sort.cpp -o selection_sort && ./selection_sort

=== 算法性能对比 ===
基础选择版本原始数组: : [7, 11, 9, 10, 12, 13, 8]
selectionSort1 basic:

 i=0 j=7 min_value=7 min_idx=0
 i=1 j=7 min_value=8 min_idx=6
 i=2 j=7 min_value=9 min_idx=2
 i=3 j=7 min_value=10 min_idx=3
 i=4 j=7 min_value=11 min_idx=6
 i=5 j=7 min_value=12 min_idx=6基础选择版本: 0.014ms
基础选择版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

新建数组版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

 i=0 j=7 min_value=7 min_idx=0
 i=0 j=6 min_value=8 min_idx=5
 i=0 j=5 min_value=9 min_idx=1
 i=0 j=4 min_value=10 min_idx=1
 i=0 j=3 min_value=11 min_idx=0
 i=0 j=2 min_value=12 min_idx=0
 i=0 j=1 min_value=13 min_idx=0新建数组版本: 0.015ms
新建数组版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort3 descending:
排序后数组: [13, 12, 11, 10, 9, 8, 7]
降序版本: 0.005ms
降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]

双向选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort4 bidirectional:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
双向选择版本: 0.004ms
双向选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

堆优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort5 heap optimized:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
堆优化版本: 0.005ms
堆优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 基础版本：标准版，原地交换，包含详细调试信息
2. 新建数组版本：无需交换，避免交换操作
3. 降序版本：展示算法灵活性，可按需排序
4. 双向版本：同时选择最大最小，效率提升
5. 堆优化版本：利用堆结构，复杂度优化
*/