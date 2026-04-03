/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <chrono>

// 打印数组函数
void printArray(const std::vector<int>& arr, const std::string& label) {
    std::cout << label << ": [";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i < arr.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// 性能测试函数
template<typename SortFunc>
void performanceTest(SortFunc sortFunc, std::vector<int> data, const std::string& version) {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::cout << version << "原始数组: ";
    printArray(data, "");
    
    sortFunc(data);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << version;
    printArray(data, "排序后数组");
    std::cout << version << ": " << duration.count() / 1000.0 << "ms" << std::endl;
    std::cout << version << "排序结果: ";
    printArray(data, "");
    std::cout << std::endl;
}

/**
 * 桶排序原版标准实现 - 标准桶排序算法
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 将元素分配到对应桶中
 * 4. 使用插入排序进行桶内排序
 * 5. 合并所有桶的元素
 * 
 * 原版特点：
 * - 使用插入排序进行桶内排序
 * - 记录每个桶的实际长度
 * - 保持原版算法逻辑不变
 * 
 * 时间复杂度：平均O(n + k)，最坏O(n²)
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
void bucketSort1(std::vector<int>& arr) {
    std::cout << "bucketSort1 original standard version:" << std::endl;
    
    if (arr.empty()) return;
    
    // 原版标准实现 - 第一步：计算数组最大值和最小值
    int max_value = arr[0];
    int min_value = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > max_value)
            max_value = arr[i];
        if (arr[i] < min_value)
            min_value = arr[i];
    }
    // 边界处理：确保最大最小值至少为1
    if (max_value < 1)
        max_value = 2;
    if (min_value < 1)
        min_value = 1;

    // 原版标准实现 - 第二步：计算桶的大小和数量
    int bucket_size = (max_value - min_value) / min_value + 1;
    int bucket_number = (max_value - min_value) / bucket_size + 1;

    std::cout << "bucket_size=" << bucket_size << " len=" << arr.size() << " bucket_number=" << bucket_number;
    
    // 原版标准实现 - 第三步：初始化桶和长度记录数组
    std::vector<std::vector<int>> buckets(bucket_number, std::vector<int>(arr.size()));
    std::vector<int> buckets_real_length(bucket_number, 0);

    // 原版标准实现 - 第四步：将元素分配到对应桶中（使用插入排序）
    for (int i = 0; i < arr.size(); i++) {
        int item = arr[i];
        // 计算桶索引
        int idx = (item - min_value) / bucket_size;
        std::cout << "\r\n i=" << i << " item=" << item << " idx=" << idx << " buckets_real_length[idx]=" << buckets_real_length[idx];
        
        // 原版插入排序：将元素插入到桶的正确位置
        if (buckets_real_length[idx] == 0) {
            buckets[idx][0] = item;
        } else {
            // 找到插入位置
            int j = buckets_real_length[idx] - 1;
            while (j >= 0 && buckets[idx][j] > item) {
                buckets[idx][j + 1] = buckets[idx][j];
                j--;
            }
            buckets[idx][j + 1] = item;
        }
        buckets_real_length[idx]++;
    }

    // 原版标准实现 - 第五步：打印各桶内容（调试用）
    for (int i = 0; i < bucket_number; i++) {
        std::cout << " [";
        for (int j = 0; j < buckets_real_length[i]; j++) {
            std::cout << buckets[i][j];
            if (j < buckets_real_length[i] - 1) std::cout << ", ";
        }
        std::cout << "]";
    }

    // 原版标准实现 - 第六步：合并结果
    std::vector<int> output;
    for (int i = 0; i < bucket_number; i++) {
        for (int j = 0; j < buckets_real_length[i]; j++) {
            output.push_back(buckets[i][j]);
        }
    }
    
    // 打印最终结果
    std::cout << "{";
    for(int i = 0; i < output.size(); i++) {
        std::cout << output[i];
        if(i < output.size()-1) std::cout << ", ";
    }
    std::cout << "}";
    std::cout << "\nsorted:{";
    for(int i = 0; i < output.size(); i++) {
        std::cout << output[i];
        if(i < output.size()-1) std::cout << ", ";
    }
    std::cout << "}";
    
    // 将结果复制回原数组
    arr = output;
}

/**
 * 桶排序标志位版本 - 使用标志位填充的原版实现
 * 
 * 算法思路：
 * 1. 计算数组最大值和最小值
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 使用FLAG(-1)标记初始化所有桶位置
 * 4. 将元素分配到对应桶中，使用查找插入位置
 * 5. 合并所有桶的元素，过滤掉FLAG标记
 * 
 * 原版特点：
 * - 使用FLAG(-1)作为填充标记
 * - 使用查找函数查找可用位置
 * - 标记位数据在合并时被忽略
 * - 保持原版算法逻辑不变
 */
void bucketSort2(std::vector<int>& arr) {
    std::cout << "bucketSort2 original flag version:" << std::endl;
    
    if (arr.empty()) return;
    
    // 原版标志位实现 - 第一步：计算数组最大值和最小值
    int max_value = arr[0];
    int min_value = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > max_value)
            max_value = arr[i];
        if (arr[i] < min_value)
            min_value = arr[i];
    }
    // 边界处理：确保最大最小值至少为1
    if (max_value < 1)
        max_value = 2;
    if (min_value < 1)
        min_value = 1;

    // 原版标志位实现 - 第二步：计算桶的大小和数量
    int bucket_size = (max_value - min_value) / min_value + 1;
    int bucket_number = (max_value - min_value) / bucket_size + 1;

    std::cout << "bucket_size=" << bucket_size << " len=" << arr.size() << " bucket_number=" << bucket_number;
    
    // 原版标志位实现 - 第三步：初始化桶和设置标志位
    const int FLAG = -1; // 标志位，用于标记未使用的位置
    std::vector<std::vector<int>> buckets(bucket_number, std::vector<int>(arr.size(), FLAG));

    // 原版标志位实现 - 第四步：将元素分配到对应桶中
    for (int i = 0; i < arr.size(); i++) {
        int item = arr[i];
        // 计算桶索引
        int idx = (item - min_value) / bucket_size;
        
        // 使用查找函数查找FLAG标记的位置
        int last_idx = 0;
        for (int j = 0; j < arr.size(); j++) {
            if (buckets[idx][j] == FLAG) {
                last_idx = j;
                break;
            }
        }
        
        std::cout << "\r\n i=" << i << " item=" << item << " idx=" << idx << " last_idx=" << last_idx;
        
        // 插入元素到找到的位置
        buckets[idx][last_idx] = item;
    }

    // 原版标志位实现 - 第五步：合并结果，过滤FLAG标记
    std::vector<int> output;
    for (int i = 0; i < bucket_number; i++) {
        for (int j = 0; j < arr.size(); j++) {
            // 过滤掉FLAG标记，只取出有效数据
            if (buckets[i][j] == FLAG)
                break;
            output.push_back(buckets[i][j]);
        }
    }
    
    // 打印最终结果
    std::cout << "\nsorted:{";
    for(int i = 0; i < output.size(); i++) {
        std::cout << output[i];
        if(i < output.size()-1) std::cout << ", ";
    }
    std::cout << "}";
    
    // 将结果复制回原数组
    arr = output;
}

/**
 * 桶排序动态桶版本 - 动态计算桶数量
 * 
 * 算法思路：
 * 根据数据大小动态确定桶的数量
 * 更好的负载均衡
 * 减少空桶的数量
 */
void bucketSort3(std::vector<int>& arr) {
    std::cout << "bucketSort3 dynamic buckets:" << std::endl;
    
    if (arr.empty()) return;
    
    // 找到最小值和最大值
    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());
    
    // 动态计算桶数量（基于数据范围和元素数量）
    int range = maxVal - minVal;
    int bucketCount = arr.size();
    if (bucketCount > 10) {
        bucketCount = arr.size() / 5;
    }
    if (bucketCount < 5) {
        bucketCount = 5;
    }
    double bucketSize = static_cast<double>(range) / bucketCount;
    
    // 创建桶
    std::vector<std::vector<int>> buckets(bucketCount);
    
    // 将元素分配到桶中
    for (int i = 0; i < arr.size(); ++i) {
        int value = arr[i];
        int bucketIndex;
        
        if (value == maxVal) {
            bucketIndex = bucketCount - 1;
        } else {
            bucketIndex = static_cast<int>((value - minVal) / bucketSize);
        }
        
        buckets[bucketIndex].push_back(value);
    }
    
    // 对每个桶进行排序并合并结果
    std::vector<int> result;
    for (int i = 0; i < bucketCount; ++i) {
        if (!buckets[i].empty()) {
            // 对桶内元素进行排序
            std::sort(buckets[i].begin(), buckets[i].end());
            result.insert(result.end(), buckets[i].begin(), buckets[i].end());
        }
    }
    
    // 复制回原数组
    arr = result;
}

/**
 * 桶排序链表版本 - 使用链表结构优化插入
 * 
 * 算法思路：
 * 使用类似链表的结构进行桶内元素管理
 * 提高插入效率
 * 保持元素有序性
 */
void bucketSort4(std::vector<int>& arr) {
    std::cout << "bucketSort4 linked list:" << std::endl;
    
    if (arr.empty()) return;
    
    // 找到最小值和最大值
    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());
    
    // 创建桶（使用数组模拟链表）
    const int bucketCount = 5;
    std::vector<std::vector<int>> buckets(bucketCount);
    
    // 计算每个桶的范围
    int range = maxVal - minVal;
    double bucketSize = static_cast<double>(range) / bucketCount;
    
    // 将元素分配到桶中（保持有序插入）
    for (int i = 0; i < arr.size(); ++i) {
        int value = arr[i];
        int bucketIndex;
        
        if (value == maxVal) {
            bucketIndex = bucketCount - 1;
        } else {
            bucketIndex = static_cast<int>((value - minVal) / bucketSize);
        }
        
        // 有序插入到桶中
        bool inserted = false;
        for (int j = 0; j < buckets[bucketIndex].size(); ++j) {
            if (value < buckets[bucketIndex][j]) {
                buckets[bucketIndex].insert(buckets[bucketIndex].begin() + j, value);
                inserted = true;
                break;
            }
        }
        
        if (!inserted) {
            buckets[bucketIndex].push_back(value);
        }
    }
    
    // 合并所有桶
    std::vector<int> result;
    for (int i = 0; i < bucketCount; ++i) {
        result.insert(result.end(), buckets[i].begin(), buckets[i].end());
    }
    
    // 复制回原数组
    arr = result;
}

/**
 * 桶排序自适应版本 - 根据数据特征自适应调整
 * 
 * 算法思路：
 * 根据数据分布特征自动调整桶数量
 * 优化不同数据场景下的性能
 * 提供更好的适应性
 */
void bucketSort5(std::vector<int>& arr) {
    std::cout << "bucketSort5 adaptive:" << std::endl;
    
    if (arr.empty()) return;
    
    // 找到最小值和最大值
    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());
    
    // 自适应计算桶数量
    int range = maxVal - minVal;
    int bucketCount;
    
    if (arr.size() <= 10) {
        bucketCount = 3;
    } else if (range <= 100) {
        bucketCount = 5;
    } else if (range <= 1000) {
        bucketCount = 10;
    } else {
        bucketCount = 20;
    }
    
    double bucketSize = static_cast<double>(range) / bucketCount;
    
    // 创建桶
    std::vector<std::vector<int>> buckets(bucketCount);
    
    // 将元素分配到桶中
    for (int i = 0; i < arr.size(); ++i) {
        int value = arr[i];
        int bucketIndex;
        
        if (value == maxVal) {
            bucketIndex = bucketCount - 1;
        } else {
            bucketIndex = static_cast<int>((value - minVal) / bucketSize);
        }
        
        buckets[bucketIndex].push_back(value);
    }
    
    // 对每个桶进行排序并合并结果
    std::vector<int> result;
    for (int i = 0; i < bucketCount; ++i) {
        if (!buckets[i].empty()) {
            std::sort(buckets[i].begin(), buckets[i].end());
            result.insert(result.end(), buckets[i].begin(), buckets[i].end());
        }
    }
    
    // 复制回原数组
    arr = result;
}

/**
 * 桶排序实时冒泡版本 - 实时维护桶内有序性
 * 
 * 算法思路：
 * 每次插入都保持桶内有序
 * 避免最后的排序步骤
 * 提供实时排序能力
 */
void bucketSort6(std::vector<int>& arr) {
    std::cout << "bucketSort6 real-time bubble:" << std::endl;
    
    if (arr.empty()) return;
    
    // 找到最小值和最大值
    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());
    
    // 创建桶
    const int bucketCount = 5;
    std::vector<std::vector<int>> buckets(bucketCount);
    
    // 计算每个桶的范围
    int range = maxVal - minVal;
    double bucketSize = static_cast<double>(range) / bucketCount;
    
    // 将元素分配到桶中（实时冒泡排序）
    for (int i = 0; i < arr.size(); ++i) {
        int value = arr[i];
        int bucketIndex;
        
        if (value == maxVal) {
            bucketIndex = bucketCount - 1;
        } else {
            bucketIndex = static_cast<int>((value - minVal) / bucketSize);
        }
        
        // 实时冒泡插入到正确位置
        buckets[bucketIndex].push_back(value);
        int j = buckets[bucketIndex].size() - 1;
        while (j > 0 && buckets[bucketIndex][j] < buckets[bucketIndex][j - 1]) {
            std::swap(buckets[bucketIndex][j], buckets[bucketIndex][j - 1]);
            j--;
        }
    }
    
    // 合并所有桶
    std::vector<int> result;
    for (int i = 0; i < bucketCount; ++i) {
        result.insert(result.end(), buckets[i].begin(), buckets[i].end());
    }
    
    // 复制回原数组
    arr = result;
}

int main() {
    // 测试数据
    std::vector<int> testData = {20, 11, 0, -10, 9, 6, 30, 15, 13, 80};
    
    std::cout << "=== 桶排序算法演示 ===" << std::endl << std::endl;
    
    // 测试所有版本的桶排序
    performanceTest(bucketSort1, testData, "原版标准版本");
    performanceTest(bucketSort2, testData, "原版标志位版本");
    performanceTest(bucketSort3, testData, "动态桶版本");
    performanceTest(bucketSort4, testData, "链表版本");
    performanceTest(bucketSort5, testData, "自适应版本");
    performanceTest(bucketSort6, testData, "实时冒泡版本");
    
    std::cout << "=== 算法对比总结 ===" << std::endl;
    std::cout << "1. 原版标准版本：bucketSort1 - 标准桶排序实现，使用插入排序" << std::endl;
    std::cout << "2. 原版标志位版本：bucketSort2 - 使用标志位填充，查找插入位置" << std::endl;
    std::cout << "3. 动态桶版本：bucketSort3 - 动态计算桶数量，更好的负载均衡" << std::endl;
    std::cout << "4. 链表版本：bucketSort4 - 模拟链表结构，优化插入效率" << std::endl;
    std::cout << "5. 自适应版本：bucketSort5 - 根据数据特征自适应调整" << std::endl;
    std::cout << "6. 实时冒泡版本：bucketSort6 - 实时维护桶内有序性" << std::endl;
    
    return 0;
}

/*
打印结果
jarry@Mac bucketsort % g++ bucket_sort.cpp -o bucket_sort && ./bucket_sort
=== 桶排序算法演示 ===

原版标准版本原始数组: : [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort1 original standard version:
bucket_size=80 len=10 bucket_number=1
 i=0 item=20 idx=0 buckets_real_length[idx]=0
 i=1 item=11 idx=0 buckets_real_length[idx]=1
 i=2 item=0 idx=0 buckets_real_length[idx]=2
 i=3 item=-10 idx=0 buckets_real_length[idx]=3
 i=4 item=9 idx=0 buckets_real_length[idx]=4
 i=5 item=6 idx=0 buckets_real_length[idx]=5
 i=6 item=30 idx=0 buckets_real_length[idx]=6
 i=7 item=15 idx=0 buckets_real_length[idx]=7
 i=8 item=13 idx=0 buckets_real_length[idx]=8
 i=9 item=80 idx=0 buckets_real_length[idx]=9 [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]{-10, 0, 6, 9, 11, 13, 15, 20, 30, 80}
sorted:{-10, 0, 6, 9, 11, 13, 15, 20, 30, 80}原版标准版本排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
原版标准版本: 0.023ms
原版标准版本排序结果: : [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

原版标志位版本原始数组: : [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort2 original flag version:
bucket_size=80 len=10 bucket_number=1
 i=0 item=20 idx=0 last_idx=0
 i=1 item=11 idx=0 last_idx=1
 i=2 item=0 idx=0 last_idx=2
 i=3 item=-10 idx=0 last_idx=3
 i=4 item=9 idx=0 last_idx=4
 i=5 item=6 idx=0 last_idx=5
 i=6 item=30 idx=0 last_idx=6
 i=7 item=15 idx=0 last_idx=7
 i=8 item=13 idx=0 last_idx=8
 i=9 item=80 idx=0 last_idx=9
sorted:{20, 11, 0, -10, 9, 6, 30, 15, 13, 80}原版标志位版本排序后数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
原版标志位版本: 0.015ms
原版标志位版本排序结果: : [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

动态桶版本原始数组: : [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort3 dynamic buckets:
动态桶版本排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
动态桶版本: 0.007ms
动态桶版本排序结果: : [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

链表版本原始数组: : [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort4 linked list:
链表版本排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
链表版本: 0.007ms
链表版本排序结果: : [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

自适应版本原始数组: : [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort5 adaptive:
自适应版本排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
自适应版本: 0.005ms
自适应版本排序结果: : [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

实时冒泡版本原始数组: : [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort6 real-time bubble:
实时冒泡版本排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
实时冒泡版本: 0.027ms
实时冒泡版本排序结果: : [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 原版标准版本：bucketSort1 - 标准桶排序实现，使用插入排序
2. 原版标志位版本：bucketSort2 - 使用标志位填充，查找插入位置
3. 动态桶版本：bucketSort3 - 动态计算桶数量，更好的负载均衡
4. 链表版本：bucketSort4 - 模拟链表结构，优化插入效率
5. 自适应版本：bucketSort5 - 根据数据特征自适应调整
6. 实时冒泡版本：bucketSort6 - 实时维护桶内有序性
*/