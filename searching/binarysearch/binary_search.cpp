/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 二分查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

#include <iostream>
#include <vector>
#include <chrono>

/**
 * binarySearch1 - 标准非递归版本，传递左右区间指针
 * 
 * 算法步骤：
 * 1. 初始化左右边界：left=0, right=arr.size()-1
 * 2. 计算中间位置：midIndex = (left + right) / 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * @param arr - 有序数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int binarySearch1(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int midIndex, mid;
    
    // left是左侧，right是最右侧。搜索区间长度小于1时停止
    while (left <= right) {
        midIndex = (left + right) / 2;  // 计算中间位置
        mid = arr[midIndex];               // 获取中间值
        // 中间项等于目标项则返回下标
        if (mid == target) {
            return midIndex;
        } else if (target > mid) {
            // 大于中间项折半查找右侧
            left = midIndex + 1;
        } else {
            // 小于中间项折半查找左侧
            right = midIndex - 1;
        }
    }
    return -1;  // 未找到
}

/**
 * binarySearch2 - 递归实现，移动左右区间指针
 * 
 * 算法步骤：
 * 1. 处理默认参数，设置初始边界
 * 2. 计算中间位置和中间值
 * 3. 比较中间值与目标值
 * 4. 根据比较结果递归查找对应半区
 * 5. 处理重复项的特殊情况
 * 
 * @param arr - 有序数组
 * @param target - 目标值
 * @param left - 左边界（可选）
 * @param right - 右边界（可选）
 * @return 找到返回索引，未找到返回-1
 */
int binarySearch2(const std::vector<int>& arr, int target, int left = 0, int right = -1) {
    right = (right == -1) ? arr.size() - 1 : right;  // 默认右边界为末尾
    int midIndex = (left + right) / 2;
    int mid = arr[midIndex];
    
    // 中间值等于查找项说明找到了，则返回中间项下标
    if (mid == target) {
        // 如果有重复项，返回第一个位置
        if (arr[left] == target) {
            return left;
        }
        return midIndex;
    }
    // 如果左侧与右侧相同，表面查找完毕，返回-1
    if (left >= right) {
        return -1;
    }
    
    if (target > mid) {
        // 折半右侧部分开始递归查找
        return binarySearch2(arr, target, midIndex + 1, right);
    } else {
        // 折半左侧部分开始递归查找
        return binarySearch2(arr, target, left, midIndex - 1);
    }
}

/**
 * binarySearch3 - 二分搜索递归查找，记录下右侧位置
 * 
 * 算法步骤：
 * 1. 处理边界条件，数组长度小于等于1时特殊处理
 * 2. 计算中间位置和中间值
 * 3. 比较中间值与目标值
 * 4. 根据比较结果递归查找对应半区
 * 5. 累积索引位置，确保返回正确的绝对位置
 * 
 * @param arr - 有序数组
 * @param target - 目标值
 * @param right - 累积的右侧位置（内部使用）
 * @return 找到返回索引，未找到返回-1
 */
int binarySearch3(const std::vector<int>& arr, int target, int right = 0) {
    int length = arr.size();
    if (length <= 1 && target != arr[0]) {
        return -1;
    }
    int midIndex = (length - 1) / 2;
    int mid = arr[midIndex];
    
    if (target == mid) {
        return right + midIndex;
    } else if (target > mid) {
        // 如果在右侧，则需要将中间index加上
        std::vector<int> subArr(arr.begin() + midIndex + 1, arr.end());
        return binarySearch3(subArr, target, right + midIndex + 1);
    } else {
        // 如果在左侧，则直接递归左侧部分
        std::vector<int> subArr(arr.begin(), arr.begin() + midIndex);
        return binarySearch3(subArr, target, right);
    }
}

/**
 * binarySearch4 - 查找第一个匹配项，处理重复项
 * 
 * 算法思路：
 * 1. 使用非递归方式，但处理重复项的特殊情况
 * 2. 当找到目标时，继续向左查找第一个出现的位置
 * 3. 通过缩小右边界来确保找到第一个匹配项
 * 
 * @param arr - 有序数组
 * @param target - 目标值
 * @return 第一个匹配项的索引，未找到返回-1
 */
int binarySearch4(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int midIndex, mid;
    
    // 搜索区间小于等于1停止搜索
    while (left <= right) {
        // 找到中间值
        midIndex = (left + right) / 2;
        mid = arr[midIndex];
        
        if (target > mid) {
            // 大于中间项折半查找右侧
            left = midIndex + 1;
        } else {
            // 小于等于中间项则折半查找左侧，同时缩小右侧范围
            right = midIndex - 1;
        }
    }
    // 此时left是最左侧目标项
    if (left < arr.size() && arr[left] == target) {
        return left;
    }
    
    return -1;  // 未找到
}

/**
 * main - 主程序：演示二分查找算法的性能对比
 * 
 * 测试内容：
 * 1. binarySearch1 - 标准非递归版本
 * 2. binarySearch2 - 递归版本，处理重复项
 * 3. binarySearch3 - 递归版本，累积索引位置
 * 4. binarySearch4 - 查找第一个匹配项
 */
int main() {
    std::cout << "============================================================" << std::endl;
    std::cout << "二分查找算法演示" << std::endl;
    std::cout << "============================================================" << std::endl;
    
    // 创建测试数据
    std::vector<int> arr = {2, 3, 8, 10, 10, 13};
    
    // 测试 binarySearch1
    auto start = std::chrono::high_resolution_clock::now();
    int result = binarySearch1(arr, 10);
    std::cout << "binarySearch1(arr, 10) => result:" << result << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time1 = end - start;
    std::cout << "time:" << time1.count() << "ms" << std::endl;
    
    // 测试 binarySearch2
    start = std::chrono::high_resolution_clock::now();
    result = binarySearch2(arr, 10);
    std::cout << "binarySearch2(arr, 10) => result:" << result << std::endl;
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time2 = end - start;
    std::cout << "time:" << time2.count() << "ms" << std::endl;
    
    // 测试 binarySearch3
    start = std::chrono::high_resolution_clock::now();
    result = binarySearch3(arr, 10);
    std::cout << "binarySearch3(arr, 10) => result:" << result << std::endl;
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time3 = end - start;
    std::cout << "time:" << time3.count() << "ms" << std::endl;
    
    // 测试 binarySearch4
    start = std::chrono::high_resolution_clock::now();
    result = binarySearch4(arr, 10);
    std::cout << "binarySearch4(arr, 10) => result:" << result << std::endl;
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time4 = end - start;
    std::cout << "time:" << time4.count() << "ms" << std::endl;
    
    return 0;
}

/*
打印结果
jarry@Mac binarysearch % g++ binary_search.cpp && ./a.out
============================================================
二分查找算法演示
============================================================
binarySearch1(arr, 10) => result:4
time:0.001ms
binarySearch2(arr, 10) => result:3
time:0.001ms
binarySearch3(arr, 10) => result:4
time:0.001ms
binarySearch4(arr, 10) => result:3
time:0ms
*/
