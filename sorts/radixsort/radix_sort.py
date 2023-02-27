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

    # 根据基数求得当前项目对应位置的数值，并给对应计数数组位置加1
    for i in range(0, arr_len):
        index = arr[i] // exponent % amount
        count_list[index] += 1

    # 当前位置加上左侧位置，后面的位数为前面的累加之和
    for i in range(1, amount):
        count_list[i] += count_list[i - 1]

    # 构建输出数组，根据计数数组按顺序取得排序内容
    i = arr_len - 1
    while i >= 0:
        index = arr[i] // exponent % amount
        sorted_list[count_list[index] - 1] = arr[i]
        count_list[index] -= 1
        i -= 1

    # 复制输出数组到原始数组
    for i in range(0, arr_len):
        arr[i] = sorted_list[i]

    return arr

def radix_sort(arr):
    max_value = max(arr)
    # 根据最大值，逐个按进位(基数)来应用排序，exponent即数位。
    exponent = 1
    while max_value // exponent > 0:
        counting_sort(arr, exponent)
        exponent *= 10

    return arr

if __name__ == '__main__':

    # 1. radix_sort1
    arr = [7, 11, 9, 10, 12, 13, 0, 8, 1, 23]
    print("\r\n Source arr1:")
    print(arr)
    start_time = time.time()
    arr = radix_sort(arr)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("radix_sort sorted: ", arr)

"""
jarry@jarrys-MacBook-Pro radixsort % python radix_sort.py

 Source arr1:
[7, 11, 9, 10, 12, 13, 0, 8, 1, 23]
time:0.0269412994385 ms
('radix_sort sorted: ', [0, 1, 7, 8, 9, 10, 11, 12, 13, 23])
"""