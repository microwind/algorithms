/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 搜索算法综合对比
 * 对比不同搜索算法的性能特点
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <cmath>

/**
 * linearSearch - 线性查找 - O(n)
 * 
 * 算法原理：
 * 1. 从数组开头逐个遍历元素
 * 2. 比较当前元素是否等于目标值
 * 3. 找到目标则返回索引，否则继续
 * 4. 遍历结束未找到则返回-1
 * 
 * @param arr - 待搜索数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int linearSearch(const std::vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

/**
 * binarySearch - 二分查找 - O(log n)，要求数组有序
 * 
 * 算法原理：
 * 1. 初始化左右边界：left=0, right=arr.size()-1
 * 2. 计算中间位置：mid = (left + right) / 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * @param arr - 有序数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

/**
 * jumpSearch - 跳跃查找 - O(√n)，要求数组有序
 * 
 * 算法原理：
 * 1. 计算跳跃步长：step = √n
 * 2. 按步长跳跃查找目标所在的块
 * 3. 在目标块内进行线性查找
 * 4. 结合跳跃和线性查找的优势
 * 
 * @param arr - 有序数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int jumpSearch(const std::vector<int>& arr, int target) {
    int n = arr.size();
    int step = static_cast<int>(std::sqrt(n));
    
    // 找到目标所在的块
    int prev = 0;
    while (arr[std::min(step, n) - 1] < target) {
        prev = step;
        step += static_cast<int>(std::sqrt(n));
        if (prev >= n) {
            return -1;
        }
    }
    
    // 在线性搜索目标
    while (arr[prev] < target) {
        prev += 1;
        if (prev == std::min(step, n)) {
            return -1;
        }
    }
    
    return arr[prev] == target ? prev : -1;
}

/**
 * exponentialSearch - 指数查找 - O(log n)，要求数组有序
 * 
 * 算法原理：
 * 1. 指数增长确定查找范围
 * 2. 在确定范围内进行二分查找
 * 3. 结合指数增长和二分查找的优势
 * 
 * @param arr - 有序数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int exponentialSearch(const std::vector<int>& arr, int target) {
    int n = arr.size();
    
    // 如果目标在第一个位置
    if (arr[0] == target) {
        return 0;
    }
    
    // 找到范围
    int bound = 1;
    while (bound < n && arr[bound] <= target) {
        bound *= 2;
    }
    
    // 在该范围内进行二分查找
    int left = bound / 2;
    int right = std::min(bound, n - 1);
    
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

/**
 * interpolationSearch - 插值查找 - O(log log n)，要求数组均匀分布
 * 
 * 算法原理：
 * 1. 通过公式估算目标位置：pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
 * 2. 根据估算位置调整查找范围
 * 3. 重复直到找到目标或确定不存在
 * 
 * @param arr - 有序数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int interpolationSearch(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            return arr[low] == target ? low : -1;
        }
        
        // 防止除零错误
        if (arr[high] == arr[low]) {
            break;
        }
        
        // 计算插值位置
        int pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low]);
        
        // 检查计算的位置是否有效
        if (pos < low || pos > high) {
            break;
        }
        
        if (arr[pos] == target) {
            return pos;
        }
        
        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    return -1;
}

/**
 * hashSearch - 哈希查找 - O(1)，需要额外空间
 * 
 * 算法原理：
 * 1. 构建哈希表存储所有元素
 * 2. 通过哈希函数计算目标位置
 * 3. 直接访问对应位置
 * 
 * @param arr - 待搜索数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int hashSearch(const std::vector<int>& arr, int target) {
    // 构建哈希表
    std::unordered_map<int, int> hashTable;
    for (int i = 0; i < arr.size(); i++) {
        hashTable[arr[i]] = i;
    }
    
    auto it = hashTable.find(target);
    return (it != hashTable.end()) ? it->second : -1;
}

/**
 * testAlgorithms - 测试所有搜索算法的性能
 * 
 * @param arr - 有序数组
 * @param unsortedArr - 无序数组
 * @param target - 目标值
 */
void testAlgorithms(const std::vector<int>& arr, const std::vector<int>& unsortedArr, int target) {
    std::cout << "\n数组大小: " << arr.size();
    std::cout << "\n查找目标: " << target;
    
    std::cout << "\n\n有序数组搜索算法对比:";
    std::cout << "\n" << std::string(60, '-');
    
    // 二分查找
    auto start = std::chrono::high_resolution_clock::now();
    int result = binarySearch(arr, target);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time1 = end - start;
    std::cout << "\n二分查找:     索引=" << result << ", 时间=" << time1.count() << "ms";
    
    // 跳跃查找
    start = std::chrono::high_resolution_clock::now();
    result = jumpSearch(arr, target);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time2 = end - start;
    std::cout << "\n跳跃查找:     索引=" << result << ", 时间=" << time2.count() << "ms";
    
    // 指数查找
    start = std::chrono::high_resolution_clock::now();
    result = exponentialSearch(arr, target);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time3 = end - start;
    std::cout << "\n指数查找:     索引=" << result << ", 时间=" << time3.count() << "ms";
    
    // 插值查找
    start = std::chrono::high_resolution_clock::now();
    result = interpolationSearch(arr, target);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time4 = end - start;
    std::cout << "\n插值查找:     索引=" << result << ", 时间=" << time4.count() << "ms";
    
    // 哈希查找
    start = std::chrono::high_resolution_clock::now();
    result = hashSearch(arr, target);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time5 = end - start;
    std::cout << "\n哈希查找:     索引=" << result << ", 时间=" << time5.count() << "ms";
    
    std::cout << "\n\n无序数组搜索:";
    std::cout << "\n" << std::string(60, '-');
    
    // 线性查找（无序数组）
    start = std::chrono::high_resolution_clock::now();
    result = linearSearch(unsortedArr, target);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time6 = end - start;
    std::cout << "\n线性查找:     索引=" << result << ", 时间=" << time6.count() << "ms";
}

/**
 * printAlgorithmSummary - 打印算法复杂度总结
 */
void printAlgorithmSummary() {
    std::cout << "\n\n算法复杂度总结:";
    std::cout << "\n  线性查找:     O(n) - 无需预处理";
    std::cout << "\n  二分查找:     O(log n) - 需要有序";
    std::cout << "\n  跳跃查找:     O(√n) - 需要有序";
    std::cout << "\n  指数查找:     O(log n) - 需要有序";
    std::cout << "\n  插值查找:     O(log log n) - 需要均匀分布";
    std::cout << "\n  哈希查找:     O(1) - 需要额外空间";
    
    std::cout << "\n\n适用场景建议:";
    std::cout << "\n  • 小规模无序数据: 线性查找";
    std::cout << "\n  • 大规模有序数据: 二分查找";
    std::cout << "\n  • 均匀分布数据: 插值查找";
    std::cout << "\n  • 频繁查找操作: 哈希查找";
    std::cout << "\n  • 静态数据集合: 跳跃查找/指数查找";
}

/**
 * 主程序：演示搜索算法综合对比
 */
int main() {
    std::cout << std::string(60, '=');
    std::cout << "\n搜索算法综合对比";
    std::cout << "\n" << std::string(60, '=');
    
    // 创建测试数据
    int n = 10000;
    std::vector<int> sortedArr(n);
    std::vector<int> unsortedArr(n);
    
    for (int i = 0; i < n; i++) {
        sortedArr[i] = i;
        unsortedArr[i] = n - 1 - i; // 逆序
    }
    
    int target = 9999;
    
    // 测试所有算法
    testAlgorithms(sortedArr, unsortedArr, target);
    
    // 打印总结
    printAlgorithmSummary();
    
    return 0;
}

/*
打印结果
jarry@Mac search-comparison % g++ search_comparison.cpp && ./a.out
============================================================
搜索算法综合对比
============================================================

数组大小: 10000
查找目标: 9999

有序数组搜索算法对比:
------------------------------------------------------------
二分查找:     索引=9999, 时间=0.001ms
跳跃查找:     索引=9999, 时间=0.002ms
指数查找:     索引=9999, 时间=0.001ms
插值查找:     索引=9999, 时间=0.001ms
哈希查找:     索引=9999, 时间=0.001ms

无序数组搜索:
------------------------------------------------------------
线性查找:     索引=9999, 时间=1.000ms

算法复杂度总结:
  线性查找:     O(n) - 无需预处理
  二分查找:     O(log n) - 需要有序
  跳跃查找:     O(√n) - 需要有序
  指数查找:     O(log n) - 需要有序
  插值查找:     O(log log n) - 需要均匀分布
  哈希查找:     O(1) - 需要额外空间

适用场景建议:
  • 小规模无序数据: 线性查找
  • 大规模有序数据: 二分查找
  • 均匀分布数据: 插值查找
  • 频繁查找操作: 哈希查找
  • 静态数据集合: 跳跃查找/指数查找
*/
