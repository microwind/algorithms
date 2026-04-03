/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 二分查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

/**
 * binary_search1 - 标准非递归版本，传递左右区间指针
 * 
 * 算法步骤：
 * 1. 初始化左右边界：left=0, right=len-1
 * 2. 计算中间位置：mid_index = (left + right) / 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * @param arr - 有序数组
 * @param len - 数组长度
 * @param item - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int binary_search1(int *arr, int len, int item)
{
    int left = 0;
    int right = len - 1;
    int mid_index;
    int middle;
    // 注意：当 left == right 时，仍然需要继续循环判断
    while (left <= right)
    {
        // 计算中间位置索引
        mid_index = (left + right) / 2;
        middle = arr[mid_index];
        if (item > middle)
        {
            left = mid_index + 1;           // 目标在右侧
        }
        else
        {
            right = mid_index - 1;          // 目标在左侧或等于中间值
        }
    }
    // 循环结束时，left 指向第一个大于 item 的元素位置
    if (left < len && arr[left] == item)
        return left;
    return -1;                          // 未找到
}

/**
 * binary_search2 - 递归实现，移动左右区间指针
 * 
 * 算法步骤：
 * 1. 计算中间位置和中间值
 * 2. 比较中间值与目标值
 * 3. 根据比较结果递归查找对应半区
 * 4. 处理重复项的特殊情况
 * 
 * @param arr - 有序数组
 * @param item - 目标值
 * @param left - 左边界
 * @param right - 右边界
 * @return 找到返回索引，未找到返回-1
 */
int binary_search2(int *arr, int item, int left, int right)
{
    int mid_index = (left + right) / 2;
    int middle = arr[mid_index];
    // 注意：当 left == right 时，仍然需要继续循环判断
    if (middle == item)
    {
        if (arr[left] == item)          // 处理重复项，返回第一个位置
            return left;
        return mid_index;                 // 返回找到的位置
    }
    // 递归出口：当 left >= right 时，说明没有找到
    if (left >= right)
        return -1;

    // 递归调用，移动左右区间指针
    if (item > middle)
        return binary_search2(arr, item, mid_index + 1, right);   // 查找右侧
    else
        return binary_search2(arr, item, left, mid_index - 1);      // 查找左侧
}

/**
 * 主程序：演示二分查找算法的性能对比
 * 
 * 测试内容：
 * 1. binary_search1 - 标准非递归版本
 * 2. binary_search2 - 递归版本，处理重复项
 * 
 * 性能测试：
 * - 使用clock()函数测量执行时间
 * - 测试多个目标值的查找性能
 */
int main()
{
    /* 测试 binary_search1 */
    int arr[6] = {2, 3, 8, 10, 10, 13};     // 包含重复项的测试数组
    int len = sizeof(arr) / sizeof(arr[0]);
    float startTime = clock();
    printf("search start:");
    int result = binary_search1(arr, len, 3);    // 期望返回1
    printf("\n binary_search1(arr, len, 3), %d", result);
    result = binary_search1(arr, len, 10);       // 期望返回3（第一个10）
    printf("\n binary_search1(arr, len, 10), %d", result);
    result = binary_search1(arr, len, 111);      // 期望返回-1（未找到）
    printf("\n binary_search1(arr, len, 11), %d", result);
    printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));

    /* 测试 binary_search2 */
    int arr2[6] = {2, 3, 8, 10, 10, 13};    // 包含重复项的测试数组
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    startTime = clock();
    printf("search start:");
    result = binary_search2(arr2, 3, 0, len2);        // 期望返回1
    printf("\n binary_search2(arr2, 3, 0, len2), %d", result);
    result = binary_search2(arr2, 10, 0, len2);       // 期望返回3（第一个10）
    printf("\n binary_search2(arr2, 10, 0, len2), %d", result);
    result = binary_search2(arr2, 111, 0, len2);      // 期望返回-1（未找到）
    printf("\n binary_search2(arr2, 111, 0, len2), %d", result);
    printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
}

/**
jarry@jarrys-MacBook-Pro binarysearch % gcc binary_search.c
jarry@jarrys-MacBook-Pro binarysearch % ./a.out            
search start:
 binary_search1(arr, len, 3), 1
 binary_search1(arr, len, 10), 3
 binary_search1(arr, len, 11), -1
time: 0.027000 ms.search start:
 binary_search1(arr, len, 3), 1
 binary_search1(arr2, len2, 10), 3
 binary_search1(arr, len, 111), -1
time: 0.005000 ms.%    
*/