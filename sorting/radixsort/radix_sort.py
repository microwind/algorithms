#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time


# 利用计数排序来实现基本排序
def counting_sort(arr, exponent):
    # 基数排序的计数排序：按指定位数排序
    arr_len = len(arr)
    amount = 10  # 0-9的数字
    count_list = [0] * amount
    sorted_list = [0] * arr_len
    min_value = min(arr)
    
    # 第一步：统计当前位数的计数
    for i in range(0, arr_len):
        index = (arr[i] - min_value) // exponent % amount
        count_list[index] += 1

    # 第二步：计算累积计数
    for i in range(1, amount):
        count_list[i] += count_list[i - 1]

    # 第三步：构建输出数组
    i = arr_len - 1
    while i >= 0:
        index = (arr[i] - min_value) // exponent % amount
        sorted_list[count_list[index] - 1] = arr[i]
        count_list[index] -= 1
        i -= 1

    # 第四步：复制回原数组
    for i in range(0, arr_len):
        arr[i] = sorted_list[i]

    return arr

# 基数排序LSD版，基于计数排序的基础，按数字的每个位置来排序
def radix_sort(arr):
    # 基数排序LSD版：从低位到高位逐位排序
    max_value = max(arr)
    min_value = min(arr)
    exponent = 1  # 当前位数：个位、十位、百位...
    max_number = max_value - min_value
    
    # 按位数循环处理
    while max_number // exponent > 0:
        counting_sort(arr, exponent)
        exponent *= 10

    return arr

if __name__ == '__main__':

    # 1. radix_sort1
    arr = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
    print("\r\n Source arr1:")
    print(arr)
    start_time = time.time()
    arr = radix_sort(arr)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("radix_sort sorted: ", arr)

"""
jarry@jarrys-MacBook-Pro radixsort % python radix_sort.py

 Source arr1:
[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
time:0.0519752502441 ms
('radix_sort sorted: ', [-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431])
"""