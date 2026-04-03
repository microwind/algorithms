/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 线性查找算法实现
 * 
 * 线性查找 - Linear Search
 * 逐个遍历查找目标元素
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
#include <stdio.h>

/**
 * linear_search - 基本线性查找
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
            return i;  // 找到目标，返回索引
        }
    }
    return -1;  // 未找到
}

/**
 * linear_search_all - 查找所有匹配项
 * 
 * 算法思路：
 * 遍历整个数组，收集所有匹配项的索引
 * 适合处理重复元素的情况
 * 
 * @param arr - 待搜索数组
 * @param n - 数组长度
 * @param target - 目标值
 * @param result - 存储匹配索引的数组
 * @return 匹配项的数量
 */
int linear_search_all(int arr[], int n, int target, int result[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            result[count++] = i;  // 收集匹配索引
        }
    }
    return count;  // 返回匹配数量
}

/**
 * linear_search_sentinel - 带哨兵的线性查找
 * 
 * 算法优化：
 * 在数组末尾设置哨兵（目标值）
 * 减少每次循环中的边界检查
 * 可以略微提高性能
 * 
 * @param arr - 待搜索数组
 * @param n - 数组长度
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int linear_search_sentinel(int arr[], int n, int target) {
    int last = arr[n - 1];  // 保存最后一个元素
    arr[n - 1] = target;     // 设置哨兵
    
    int i = 0;
    while (arr[i] != target) {
        i++;
    }
    
    arr[n - 1] = last;  // 恢复最后一个元素
    
    if (i < n - 1 || arr[n - 1] == target) {
        return i;
    }
    return -1;
}

/**
 * 主程序：演示线性查找功能
 * 
 * 演示内容：
 * 1. 基本线性查找 - 查找第一个匹配项
 * 2. 查找所有匹配项 - 处理重复元素
 * 3. 查找不存在的元素 - 验证算法正确性
 * 4. 展示线性查找的特点和优势
 */
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 22};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 22;
    
    printf("线性查找演示:\n\n");
    printf("数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n目标元素: %d\n\n", target);
    
    // 基本查找测试
    int index = linear_search(arr, n, target);
    if (index != -1) {
        printf("基本查找: 找到于索引 %d\n", index);
    } else {
        printf("基本查找: 未找到\n");
    }
    
    // 查找所有匹配项
    int result[10];
    int count = linear_search_all(arr, n, target, result);
    printf("所有匹配位置: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", result[i]);
    }
    printf("(共%d个)\n", count);
    
    // 查找不存在的元素
    int not_found = linear_search(arr, n, 100);
    printf("查找100: %s\n", not_found != -1 ? "找到" : "未找到");
    
    // 线性查找特点说明
    printf("\n线性查找特点:\n");
    printf("• 算法简单，易于实现\n");
    printf("• 适用于小规模数据和无序数据\n");
    printf("• 时间复杂度：O(n)\n");
    printf("• 空间复杂度：O(1)\n");
    printf("• 可以查找所有匹配项\n");
    printf("• 适合处理重复元素\n");
    
    return 0;
}
