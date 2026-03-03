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
    arr_len = len(arr)
    # 基数exponent按10进位，amount表示0-9的数字的长度，也是10个
    amount = 10
    count_list = [0] * amount
    sorted_list = [0] * arr_len
    min_value = min(arr)

    # 根据基数求得当前项目对应位置的数值，并给对应计数数组位置加1
    for i in range(0, arr_len):
        index = (arr[i] - min_value) // exponent % amount
        count_list[index] += 1

    # 当前位置加上左侧位置，后面的位数为前面的累加之和
    for i in range(1, amount):
        count_list[i] += count_list[i - 1]

    # 构建输出数组，根据计数数组按顺序取得排序内容
    i = arr_len - 1
    while i >= 0:
        index = (arr[i] - min_value) // exponent % amount
        sorted_list[count_list[index] - 1] = arr[i]
        count_list[index] -= 1
        i -= 1

    # 复制输出数组到原始数组
    for i in range(0, arr_len):
        arr[i] = sorted_list[i]

    return arr

# 基数排序LSD版，基于计数排序的基础，按数字的每个位置来排序
def radix_sort(arr):
    max_value = max(arr)
    min_value = min(arr)
    # 根据最大值，逐个按进位(基数)来应用排序，exponent即数位。
    exponent = 1
    max_number = max_value - min_value
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