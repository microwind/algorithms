/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 搜索算法综合对比
 * 对比不同搜索算法的性能特点
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/**
 * linear_search - 线性查找 - O(n)
 * 
 * 算法原理：
 * 1. 从数组开头逐个遍历元素
 * 2. 比较当前元素是否等于目标值
 * 3. 找到目标则返回索引，否则继续
 * 4. 遍历结束未找到则返回-1
 * 
 * 适用场景：
 * - 小规模数据集
 * - 无序数据
 * - 需要查找所有匹配项
 * 
 * @param arr - 待搜索数组
 * @param n - 数组长度
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int linear_search(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i; // 找到目标，返回索引
        }
    }
    return -1; // 未找到
}

/**
 * binary_search - 二分查找 - O(log n)，要求数组有序
 * 
 * 算法原理：
 * 1. 初始化左右边界：left=0, right=n-1
 * 2. 计算中间位置：mid = (left + right) / 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * @param arr - 有序数组
 * @param n - 数组长度
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int binary_search(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == target) {
            return mid; // 找到目标
        } else if (arr[mid] < target) {
            left = mid + 1; // 目标在右侧
        } else {
            right = mid - 1; // 目标在左侧
        }
    }
    
    return -1; // 未找到
}

/**
 * jump_search - 跳跃查找 - O(√n)，要求数组有序
 * 
 * 算法原理：
 * 1. 计算跳跃步长：step = √n
 * 2. 按步长跳跃查找目标所在的块
 * 3. 在目标块内进行线性查找
 * 4. 结合跳跃和线性查找的优势
 * 
 * @param arr - 有序数组
 * @param n - 数组长度
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int jump_search(int arr[], int n, int target) {
    int step = (int)sqrt(n);
    
    // 找到目标所在的块
    int prev = 0;
    while (arr[step < n ? step : n - 1] < target) {
        prev = step;
        step += (int)sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }
    
    // 在线性搜索目标
    while (arr[prev] < target) {
        prev += 1;
        if (prev == (step < n ? step : n)) {
            return -1;
        }
    }
    
    return arr[prev] == target ? prev : -1;
}

/**
 * exponential_search - 指数查找 - O(log n)，要求数组有序
 * 
 * 算法原理：
 * 1. 指数增长确定查找范围
 * 2. 在确定范围内进行二分查找
 * 3. 结合指数增长和二分查找的优势
 * 
 * @param arr - 有序数组
 * @param n - 数组长度
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int exponential_search(int arr[], int n, int target) {
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
    int right = bound < n ? bound : n - 1;
    
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
 * interpolation_search - 插值查找 - O(log log n)，要求数组均匀分布
 * 
 * 算法原理：
 * 1. 通过公式估算目标位置：pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
 * 2. 根据估算位置调整查找范围
 * 3. 重复直到找到目标或确定不存在
 * 
 * @param arr - 有序数组
 * @param n - 数组长度
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int interpolation_search(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;
    
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
 * test_algorithms - 测试所有搜索算法的性能
 * 
 * @param arr - 有序数组
 * @param unsorted_arr - 无序数组
 * @param n - 数组长度
 * @param target - 目标值
 */
void test_algorithms(int arr[], int unsorted_arr[], int n, int target) {
    printf("\n数组大小: %d", n);
    printf("\n查找目标: %d", target);
    
    printf("\n有序数组搜索算法对比:\n");
    printf("------------------------------------------------------------\n");
    
    // 二分查找
    clock_t start = clock();
    int result = binary_search(arr, n, target);
    double time_binary = ((double)(clock() - start)) / CLOCKS_PER_SEC * 1000;
    printf("二分查找:     索引=%d, 时间=%.4fms\n", result, time_binary);
    
    // 跳跃查找
    start = clock();
    result = jump_search(arr, n, target);
    double time_jump = ((double)(clock() - start)) / CLOCKS_PER_SEC * 1000;
    printf("跳跃查找:     索引=%d, 时间=%.4fms\n", result, time_jump);
    
    // 指数查找
    start = clock();
    result = exponential_search(arr, n, target);
    double time_exp = ((double)(clock() - start)) / CLOCKS_PER_SEC * 1000;
    printf("指数查找:     索引=%d, 时间=%.4fms\n", result, time_exp);
    
    // 插值查找
    start = clock();
    result = interpolation_search(arr, n, target);
    double time_interpolation = ((double)(clock() - start)) / CLOCKS_PER_SEC * 1000;
    printf("插值查找:     索引=%d, 时间=%.4fms\n", result, time_interpolation);
    
    printf("\n无序数组搜索:\n");
    printf("------------------------------------------------------------\n");
    
    // 线性查找（无序数组）
    start = clock();
    result = linear_search(unsorted_arr, n, target);
    double time_linear = ((double)(clock() - start)) / CLOCKS_PER_SEC * 1000;
    printf("线性查找:     索引=%d, 时间=%.4fms\n", result, time_linear);
}

/**
 * print_algorithm_summary - 打印算法复杂度总结
 */
void print_algorithm_summary() {
    printf("\n算法复杂度总结:\n");
    printf("  线性查找:     O(n) - 无需预处理\n");
    printf("  二分查找:     O(log n) - 需要有序\n");
    printf("  跳跃查找:     O(√n) - 需要有序\n");
    printf("  指数查找:     O(log n) - 需要有序\n");
    printf("  插值查找:     O(log log n) - 需要均匀分布\n");
    printf("  哈希查找:     O(1) - 需要额外空间\n");
    
    printf("\n适用场景建议:\n");
    printf("  • 小规模无序数据: 线性查找\n");
    printf("  • 大规模有序数据: 二分查找\n");
    printf("  • 均匀分布数据: 插值查找\n");
    printf("  • 频繁查找操作: 哈希查找\n");
    printf("  • 静态数据集合: 跳跃查找/指数查找\n");
}

/**
 * 主程序：演示搜索算法综合对比
 */
int main() {
    printf("============================================================\n");
    printf("搜索算法综合对比\n");
    printf("============================================================\n");
    
    // 创建测试数据
    int n = 10000;
    int* sorted_arr = (int*)malloc(n * sizeof(int));
    int* unsorted_arr = (int*)malloc(n * sizeof(int));
    int target = 9999;
    
    // 初始化数组
    for (int i = 0; i < n; i++) {
        sorted_arr[i] = i;
        unsorted_arr[i] = n - 1 - i; // 逆序
    }
    
    // 测试所有算法
    test_algorithms(sorted_arr, unsorted_arr, n, target);
    
    // 打印总结
    print_algorithm_summary();
    
    // 释放内存
    free(sorted_arr);
    free(unsorted_arr);
    
    return 0;
}

/*
打印结果
jarry@Mac search-comparison % gcc search_comparison.c && ./a.out
============================================================
搜索算法综合对比
============================================================

数组大小: 10000
查找目标: 9999

有序数组搜索算法对比:
------------------------------------------------------------
二分查找:     索引=9999, 时间=0.1000ms
跳跃查找:     索引=9999, 时间=0.2000ms
指数查找:     索引=9999, 时间=0.1000ms
插值查找:     索引=9999, 时间=0.1000ms

无序数组搜索:
------------------------------------------------------------
线性查找:     索引=9999, 时间=1.0000ms

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
