#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
"""

"""
基数排序桶优化版本实现
基于桶排序的LSD（最低位优先）实现，动态桶大小优化

## 算法特点
- 从低位到高位进行排序（LSD - Least Significant Digit）
- 使用桶排序实现，动态分配内存
- 适合处理稀疏数据，减少不必要的内存分配
- 支持负数处理

## 复杂度分析
- 时间复杂度：O(d * (n + k))，d为位数，k为基数
- 空间复杂度：O(n + k') - k'为实际使用的基数范围（≤k）
- 稳定性：稳定 - 保持相等元素的相对位置

## 负数处理
- 使用最小值偏移处理负数
- 通过arr[i] - min确保索引为正数
- 支持包含负数的整数数组排序

## 实现原理
1. 找出数组中最大的数，确定其位数
2. LSD是低位到高位，依次按照位数的值将数字放入到不同桶中
3. 按照桶顺序重新给数组排序
4. 重复步骤2和3，直到排序完成
"""

import time

def radix_sort(arr):
    """
    基数排序LSD版：基于桶排序，从低位到高位
    
    ## 实现步骤
    1. 找出数组中的最大值和最小值
    2. 根据最大值，逐个按进位(基数)来应用排序，从个位到高位
    3. 对每一位进行桶排序处理
    4. 将桶中的数据按顺序重新赋值给原数组
    
    @param arr: list - 待排序的数字数组
    @return: list - 排序后的数组
    """
    # 第一步：获取数组的最小值和最大值
    # 关键点：用于确定排序范围和处理负数
    max_value = max(arr)
    min_value = min(arr)  # 支持负数
    digit = 1  # 从个位开始

    # 第二步：按位数循环处理
    # 关键点：最大减去最小得到数位，最小按0来计算，这样可以支持负数
    while (max_value - min_value) // digit > 0:
        # 步骤2.1：创建10个桶对应0-9
        # 关键点：创建桶结构用于存储对应位数的数字
        buckets = [[] for _ in range(10)]
        
        # 步骤2.2：将数据分配到对应的桶中
        # 关键点：根据当前位数计算桶索引
        for num in arr:
            # 计算当前位数的值
            digit_num = (num - min_value) // digit % 10
            # 放入对应桶中
            buckets[digit_num].append(num)

        # 步骤2.3：重新组合数组
        # 关键点：按桶的顺序重新组合数组
        arr = []
        for bucket in buckets:
            arr.extend(bucket)

        # 步骤2.4：移动到下一位
        # 关键点：位数基数乘以10，处理下一位
        digit *= 10

    return arr


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
    arr = radix_sort(arr)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("arr1 sorted: ", arr)

    # 测试2：另一个测试数组
    arr2 = [39, 128, 122, 234, 108, 7, 15, -125, 204]
    print("\r\n Source arr2:")
    print(arr2)
    start_time = time.time()
    arr2 = radix_sort(arr2)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("arr2 sorted: ", arr2)
"""
jarry@Mac radixsort % python radix_sort_bucket.py

 Source arr1:
[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
time:0.013828277587890625 ms
arr1 sorted:  [-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]

 Source arr2:
[39, 128, 122, 234, 108, 7, 15, -125, 204]
time:0.0059604644775390625 ms
arr2 sorted:  [-125, 7, 15, 39, 108, 122, 128, 204, 234]
"""