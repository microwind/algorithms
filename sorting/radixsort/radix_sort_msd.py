#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright (c) https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
"""

"""
基数排序MSD版本实现
递归MSD（最高位优先）实现，基于桶排序

## 算法特点
- 从最高位开始排序（MSD - Most Significant Digit）
- 使用递归处理子数组
- 桶排序实现，动态分配内存
- 适合处理字符串或变长数据

## 复杂度分析
- 时间复杂度：O(d * (n + k))，d为位数，k为基数
- 空间复杂度：O(n + k) - 需要桶和计数数组
- 稳定性：稳定 - 保持相等元素的相对位置

## 负数处理
- 使用最小值偏移处理负数
- 通过arr[i] - min确保索引为正数
- 支持包含负数的整数数组排序

## 实现原理
1. 找出数组中最大的数，确定其位数
2. MSD是从高位开始，依次按照位数的值将数字放入到不同桶中
3. 如果桶里的长度超过1，则通过递归继续按桶排序
4. 当桶里的数据只有1位时添加到原列表对应位置
5. 重复步骤2和3，直到按照最高位排序完成
"""

import time
import math

def bucket_sort(arr, exponent):
    """
    桶排序，根据数位递归调用
    
    ## 实现原理
    - 使用桶排序对指定位数进行排序
    - 递归处理每个桶中的子数组
    - 从最高位向最低位逐层处理
    
    @param arr: list - 待排序的数组
    @param exponent: int - 当前处理的位数基数
    @return: list - 排序后的数组
    """
    # 第一步：递归终止条件检查
    # 关键点：数组长度为1或位数为0时停止递归
    if (len(arr) <= 1 or exponent <= 0):
        return arr

    # 第二步：获取数组的最小值
    # 关键点：用于处理负数，计算偏移量
    min_value = min(arr)
    radix = 10
    
    # 第三步：初始化桶结构
    # 关键点：创建10个桶对应0-9的数字
    buckets = [None] * radix

    # 第四步：将数据分配到对应的桶中
    # 关键点：根据当前位数分组
    for i in range(len(arr)):
        item = arr[i] - min_value
        bucket_idx = int(item / exponent) % radix
        if buckets[bucket_idx] is None:
            buckets[bucket_idx] = []
        buckets[bucket_idx].append(arr[i])

    # 第五步：递归排序每个桶并合并结果
    # 关键点：按桶的顺序重新组合数组
    sorted_idx = 0
    for i in range(radix):
        bucket = buckets[i]
        if bucket is None or len(bucket) < 1:
            continue
        # 递归处理下一位
        sorted_bucket = bucket_sort(bucket, exponent // 10)
        # 将排序结果放回原数组
        for num in sorted_bucket:
            arr[sorted_idx] = num
            sorted_idx += 1

    return arr

def radix_sort_msd(arr):
    """
    基数排序，从高到低逐位排序MSD版，基于桶排序递归实现
    
    ## 实现步骤
    1. 找出数组中的最大值和最小值
    2. 计算数字的位数，确定最高位的基数
    3. 调用递归桶排序函数进行排序
    
    @param arr: list - 待排序的数字数组
    @return: list - 排序后的数组
    """
    # 第一步：找出数组中的最大值和最小值
    # 关键点：用于确定排序范围和处理负数
    max_value = max(arr)
    min_value = min(arr)
    
    # 第二步：计算最大位数
    # 关键点：获取数字一共有几位，减去min得到最大值，以支持负数
    number_of_digits = int(math.log10(max_value - min_value) + 1)
    exponent = int(math.pow(10, number_of_digits - 1))
    
    # 第三步：调用递归桶排序
    # 关键点：根据数组最大值的长度，从前往后逐个对比排序
    return bucket_sort(arr, exponent)


if __name__ == '__main__':
    """
    测试函数
    
    ## 测试内容
    - 包含负数的整数数组排序
    - 性能测试和时间统计
    - 排序结果验证
    """
    
    # 测试1：包含正数和负数的混合数组
    arr = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
    print("\r\n Source arr1:")
    print(arr)
    start_time = time.time()
    arr = radix_sort_msd(arr)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("radix_sort sorted: ", arr)

    # 测试2：另一个测试数组
    arr2 = [195, 272, 276, 2343, 196, 89, 275]
    print("\r\n Source arr2:")
    print(arr2)
    start_time = time.time()
    arr2 = radix_sort_msd(arr2)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("radix_sort sorted: ", arr2)

"""
jarry@Mac radixsort % python radix_sort_msd.py 

 Source arr1:
[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
time:0.02002716064453125 ms
radix_sort sorted:  [-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]

 Source arr2:
[195, 272, 276, 2343, 196, 89, 275]
time:0.007867813110351562 ms
radix_sort sorted:  [89, 195, 196, 272, 275, 276, 2343]
"""