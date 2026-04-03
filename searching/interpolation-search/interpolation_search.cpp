/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 插值查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

#include <iostream>
#include <vector>
#include <chrono>

/**
 * interpolationSearch1 - 插值查找基础版本 - 非递归实现
 * 
 * 算法原理：
 * 1. 通过公式估算目标位置：pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
 * 2. 根据估算位置调整查找范围
 * 3. 重复直到找到目标或确定不存在
 * 
 * 适用场景：
 * - 均匀分布的有序数组
 * - 数值范围较大的数据集
 * 
 * @param arr - 有序数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int interpolationSearch1(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    
    // 检查边界条件
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // 如果范围只有一个元素
        if (low == high) {
            return arr[low] == target ? low : -1;
        }
        
        // 防止除零错误
        if (arr[high] == arr[low]) {
            break;  // 所有元素相同，无法插值
        }
        
        // 计算插值位置
        // 关键公式：根据数值比例估算位置
        int pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low]);
        
        // 检查计算的位置是否有效
        if (pos < low || pos > high) {
            break;  // 位置超出范围，退出循环
        }
        
        // 检查是否找到目标
        if (arr[pos] == target) {
            return pos; // 找到目标
        }
        
        // 调整查找范围
        if (arr[pos] < target) {
            low = pos + 1; // 目标在右侧
        } else {
            high = pos - 1; // 目标在左侧
        }
    }
    
    return -1; // 未找到
}

/**
 * interpolationSearch2 - 插值查找递归版本
 * 
 * 算法原理：
 * 1. 通过公式估算目标位置
 * 2. 递归查找对应区间
 * 3. 处理边界条件和特殊情况
 * 
 * @param arr - 有序数组
 * @param target - 目标值
 * @param low - 左边界
 * @param high - 右边界
 * @return 找到返回索引，未找到返回-1
 */
int interpolationSearch2(const std::vector<int>& arr, int target, int low, int high) {
    // 检查边界条件
    if (low > high || target < arr[low] || target > arr[high]) {
        return -1;
    }
    
    // 如果范围只有一个元素
    if (low == high) {
        return arr[low] == target ? low : -1;
    }
    
    // 防止除零错误
    if (arr[high] == arr[low]) {
        return -1;
    }
    
    // 计算插值位置
    int pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low]);
    
    // 检查计算的位置是否有效
    if (pos < low || pos > high) {
        return -1;
    }
    
    // 检查是否找到目标
    if (arr[pos] == target) {
        return pos;
    }
    
    // 递归查找
    if (arr[pos] < target) {
        return interpolationSearch2(arr, target, pos + 1, high);
    } else {
        return interpolationSearch2(arr, target, low, pos - 1);
    }
}

/**
 * interpolationSearch3 - 插值查找优化版本
 * 
 * 优化特点：
 * 1. 添加边界检查优化
 * 2. 处理重复元素情况
 * 3. 改进数值计算精度
 * 
 * @param arr - 有序数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int interpolationSearch3(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    
    // 快速边界检查
    if (target < arr[low] || target > arr[high]) {
        return -1;
    }
    
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // 防止除零和溢出
        if (arr[high] == arr[low]) {
            break;
        }
        
        // 使用double类型提高精度
        double pos = low + (double)(target - arr[low]) * (high - low) / (arr[high] - arr[low]);
        int posInt = static_cast<int>(pos);
        
        // 边界检查
        if (posInt < low || posInt > high) {
            break;
        }
        
        if (arr[posInt] == target) {
            return posInt;
        }
        
        if (arr[posInt] < target) {
            low = posInt + 1;
        } else {
            high = posInt - 1;
        }
    }
    
    return -1;
}

/**
 * interpolationSearch4 - 插值查找浮点数版本
 * 
 * 特点：
 * 1. 支持浮点数查找
 * 2. 使用epsilon进行浮点数比较
 * 3. 适用于科学计算场景
 * 
 * @param arr - 有序数组
 * @param target - 目标值（浮点数）
 * @return 找到返回索引，未找到返回-1
 */
int interpolationSearch4(const std::vector<double>& arr, double target, double epsilon = 1e-10) {
    int low = 0;
    int high = arr.size() - 1;
    
    while (low <= high && target >= arr[low] - epsilon && target <= arr[high] + epsilon) {
        if (low == high) {
            return std::abs(arr[low] - target) < epsilon ? low : -1;
        }
        
        if (std::abs(arr[high] - arr[low]) < epsilon) {
            break;
        }
        
        double pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low]);
        int posInt = static_cast<int>(pos);
        
        if (posInt < low || posInt > high) {
            break;
        }
        
        if (std::abs(arr[posInt] - target) < epsilon) {
            return posInt;
        }
        
        if (arr[posInt] < target) {
            low = posInt + 1;
        } else {
            high = posInt - 1;
        }
    }
    
    return -1;
}

/**
 * testInterpolationSearch - 测试插值查找算法
 * 
 * 测试内容：
 * 1. 基础版本 - 非递归实现
 * 2. 递归版本 - 递归实现
 * 3. 优化版本 - 改进的实现
 * 4. 浮点数版本 - 支持浮点数
 */
void testInterpolationSearch() {
    std::cout << "=== 插值查找演示 ===" << std::endl;
    
    // 整数测试数据
    std::vector<int> intArr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int intTarget = 70;
    
    std::cout << "\n整数数组: ";
    for (int num : intArr) {
        std::cout << num << " ";
    }
    std::cout << "\n目标值: " << intTarget << std::endl;
    
    // 测试基础版本
    auto start = std::chrono::high_resolution_clock::now();
    int result1 = interpolationSearch1(intArr, intTarget);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time1 = end - start;
    std::cout << "\n1. 基础版本: " << (result1 != -1 ? "找到" : "未找到") 
             << ", 索引=" << result1 << ", 时间=" << time1.count() << "ms" << std::endl;
    
    // 测试递归版本
    start = std::chrono::high_resolution_clock::now();
    int result2 = interpolationSearch2(intArr, intTarget, 0, intArr.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time2 = end - start;
    std::cout << "2. 递归版本: " << (result2 != -1 ? "找到" : "未找到") 
             << ", 索引=" << result2 << ", 时间=" << time2.count() << "ms" << std::endl;
    
    // 测试优化版本
    start = std::chrono::high_resolution_clock::now();
    int result3 = interpolationSearch3(intArr, intTarget);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time3 = end - start;
    std::cout << "3. 优化版本: " << (result3 != -1 ? "找到" : "未找到") 
             << ", 索引=" << result3 << ", 时间=" << time3.count() << "ms" << std::endl;
    
    // 测试浮点数版本
    std::vector<double> doubleArr = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    double doubleTarget = 5.5;
    
    std::cout << "\n浮点数数组: ";
    for (double num : doubleArr) {
        std::cout << num << " ";
    }
    std::cout << "\n目标值: " << doubleTarget << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    int result4 = interpolationSearch4(doubleArr, doubleTarget);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time4 = end - start;
    std::cout << "\n4. 浮点数版本: " << (result4 != -1 ? "找到" : "未找到") 
             << ", 索引=" << result4 << ", 时间=" << time4.count() << "ms" << std::endl;
    
    // 算法特点说明
    std::cout << "\n=== 插值查找特点 ===" << std::endl;
    std::cout << "• 适用于均匀分布的有序数组" << std::endl;
    std::cout << "• 通过公式估算位置，跳过不必要的比较" << std::endl;
    std::cout << "• 平均时间复杂度: O(log log n)" << std::endl;
    std::cout << "• 最坏时间复杂度: O(n)" << std::endl;
    std::cout << "• 空间复杂度: O(1)" << std::endl;
    std::cout << "• 对于均匀数据，性能优于二分查找" << std::endl;
    std::cout << "• 对于非均匀数据，可能退化为线性查找" << std::endl;
}

/**
 * 主程序：演示插值查找功能
 */
int main() {
    std::cout << "============================================================" << std::endl;
    std::cout << "插值查找算法演示" << std::endl;
    std::cout << "============================================================" << std::endl;
    
    testInterpolationSearch();
    
    return 0;
}

/*
打印结果
jarry@Mac interpolation-search % g++ interpolation_search.cpp && ./a.out
============================================================
插值查找算法演示
============================================================
=== 插值查找演示 ===

整数数组: 10 20 30 40 50 60 70 80 90 100 
目标值: 70

1. 基础版本: 找到, 索引=6, 时间=0.001ms
2. 递归版本: 找到, 索引=6, 时间=0.001ms
3. 优化版本: 找到, 索引=6, 时间=0ms

浮点数数组: 1.1 2.2 3.3 4.4 5.5 6.6 7.7 8.8 9.9 
目标值: 5.5

4. 浮点数版本: 找到, 索引=4, 时间=0ms

=== 插值查找特点 ===
• 适用于均匀分布的有序数组
• 通过公式估算位置，跳过不必要的比较
• 平均时间复杂度: O(log log n)
• 最坏时间复杂度: O(n)
• 空间复杂度: O(1)
• 对于均匀数据，性能优于二分查找
• 对于非均匀数据，可能退化为线性查找
*/
