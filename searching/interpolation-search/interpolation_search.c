/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 插值查找算法实现
 * 
 * 插值查找 - Interpolation Search
 * 适用于均匀分布的有序数组
 * 通过估算位置快速定位目标
 * 时间复杂度: 平均O(log log n)，最坏O(n)
 */
#include <stdio.h>

/**
 * interpolation_search - 插值查找基础版本
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
 * @param n - 数组长度
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int interpolation_search(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;
    
    // 检查边界条件
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // 如果范围只有一个元素
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }
        
        // 计算插值位置
        // pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
        int pos = low + ((double)(target - arr[low]) / (arr[high] - arr[low])) * (high - low);
        
        // 检查计算的位置
        if (arr[pos] == target) {
            return pos;  // 找到目标
        }
        
        // 调整查找范围
        if (arr[pos] < target) {
            low = pos + 1;  // 目标在右侧
        } else {
            high = pos - 1;  // 目标在左侧
        }
    }
    
    return -1;  // 未找到
}

/**
 * 主程序：演示插值查找功能
 * 
 * 演示内容：
 * 1. 创建均匀分布的有序数组
 * 2. 测试多个目标值的查找
 * 3. 展示插值查找的特点和优势
 */
int main() {
    // 插值查找适用于均匀分布的有序数组
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("插值查找演示:\n\n");
    printf("数组 (均匀分布): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
    
    // 测试不同目标值的查找
    int targets[] = {30, 85, 10, 100};
    int num_targets = sizeof(targets) / sizeof(targets[0]);
    
    for (int i = 0; i < num_targets; i++) {
        int target = targets[i];
        int result = interpolation_search(arr, n, target);
        
        if (result != -1) {
            printf("查找 %d: 找到于索引 %d\n", target, result);
        } else {
            printf("查找 %d: 未找到\n", target);
        }
    }
    
    // 插值查找特点说明
    printf("\n插值查找特点:\n");
    printf("• 适用于均匀分布的数据\n");
    printf("• 通过公式估算位置，跳过不必要的比较\n");
    printf("• 对于均匀数据，性能优于二分查找\n");
    printf("• 对于非均匀数据，可能退化为线性查找\n");
    
    return 0;
}
