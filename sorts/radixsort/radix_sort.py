#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time


# 利用计数排序来实现基本排序
def count_sort(arr, exp):
    size = len(arr)
    output = [0] * size
    count = [0] * 10
    amount = 10

    # 按下标位置计算，exp为数字的位置
    for i in range(0, size):
        index = arr[i] // exp
        count[index % amount] += 1

    # 当前位置加上左侧位置，后面的位数为前面的累加之和
    for i in range(1, amount):
        count[i] += count[i - 1]

    # 构建输出数组，根据计数数组按顺序取得排序内容
    i = size - 1
    while i >= 0:
        index = arr[i] // exp
        output[count[index % amount] - 1] = arr[i]
        count[index % amount] -= 1
        i -= 1

    # 复制输出数组到原始数组
    for i in range(0, size):
        arr[i] = output[i]

    return arr

def radix_sort(arr):
    max_value = max(arr)
    # 按位数应用计数排序
    exp = 1
    while max_value // exp > 0:
        count_sort(arr, exp)
        exp *= 10

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