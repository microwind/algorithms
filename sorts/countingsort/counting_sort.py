#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time


# 计数排序1
def counting_sort1(arr):
    # 计算最大值与最小值
    min_value = min(arr)
    max_value = max(arr)
    buckets = []
    real_len = int(max_value - min_value + 1)
    for i in range(real_len):
        buckets.append(0)
    # 计数数组的长度在最大和最小差值+1
    l = len(arr)
    for i in range(l):
        # 把下标减去min值，以便减少计数数组的长度，同时可以支持负数，最小坐标为0
        idx = int(arr[i] - min_value)
        # 根据待排序项给对应下标的位置增加1个标记
        buckets[idx] += 1
        # print('idx, arr[i], buckets[idx]', idx, arr[i], buckets[idx])
    output = []
    # 遍历计数数组
    for i in range(real_len):
        val = buckets[i]
        # 如果相同则取多次
        for j in range(val):
            output.append(i + min_value)
    return output


# 计数排序2
def counting_sort2(arr):
    buckets = []
    # 根据待排序项给对应下标的位置增加标记，多个相同的则需要递增
    min_value = min(arr)
    max_value = max(arr)
    real_len = int(max_value - min_value + 1)
    for i in range(real_len):
        buckets.append(None)
    for item in arr:
        idx = int(item - min_value)
        if buckets[idx] is None:
            buckets[idx] = 0
        buckets[idx] += 1

    # 遍历全部，从最小数开始遍历
    x = 0
    for i in range(real_len):
        val = buckets[i]
        if val is None:
            continue
        for j in range(val):
            arr[x] = i + min_value
            x += 1
    return arr


def counting_sort3(arr):
    min_value = min(arr)
    max_value = max(arr)
    buckets = []
    real_len = int(max_value - min_value + 1)
    for i in range(real_len):
        buckets.append(0)

    l = len(arr)
    for i in range(l):
        idx = int(arr[i] - min_value)
        buckets[idx] += 1

    j = 0
    for i in range(real_len):
      while (buckets[i]):
        arr[j] = i + min_value
        buckets[i] -= 1
        j += 1
    return arr


# test
arr1 = [3, 4, 15, 3, 3, 7, 10, -2, 1.4]
arr2 = [7, 11, 9, 2, 52, 0, -8, 8, 7, 9, 2, 10]
print('origin arr1:', arr1)
print('origin arr2:', arr2)

start_time = time.time()
print('counting_sort1.1 sorted:', counting_sort1(arr1))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

start_time = time.time()
print('counting_sort1.2 sorted:', counting_sort1(arr2))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

print('\r\n')
arr1 = [3, 4, 15, 3, 3, 7, 10, -2, 1.4]
arr2 = [7, 11, 9, 2, 52, 0, -8, 8, 7, 9, 2, 10]
print('origin arr1:', arr1)
print('origin arr2:', arr2)

start_time = time.time()
print('counting_sort2.1 sorted:', counting_sort2(arr1))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

start_time = time.time()
print('counting_sort2.2 sorted:', counting_sort2(arr2))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

print('\r\n')
arr1 = [3, 4, 15, 3, 3, 7, 10, -2, 1.4]
arr2 = [7, 11, 9, 2, 52, 0, -8, 8, 7, 9, 2, 10]
print('origin arr1:', arr1)
print('origin arr2:', arr2)

start_time = time.time()
print('counting_sort3.1 sorted:', counting_sort3(arr1))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

start_time = time.time()
print('counting_sort3.2 sorted:', counting_sort3(arr2))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

"""
jarry@jarrys-MacBook-Pro countingsort % python counting_sort.py
('origin arr1:', [3, 4, 15, 3, 3, 7, 10, -2, 1.4])
('origin arr2:', [7, 11, 9, 2, 52, 0, -8, 8, 7, 9, 2, 10])
('counting_sort1.1 sorted:', [-2, 1, 3, 3, 3, 4, 7, 10, 15])
time:0.0410079956055 ms
('counting_sort1.2 sorted:', [-8, 0, 2, 2, 7, 7, 8, 9, 9, 10, 11, 52])
time:0.0391006469727 ms


('origin arr1:', [3, 4, 15, 3, 3, 7, 10, -2, 1.4])
('origin arr2:', [7, 11, 9, 2, 52, 0, -8, 8, 7, 9, 2, 10])
('counting_sort2.1 sorted:', [-2, 1, 3, 3, 3, 4, 7, 10, 15])
time:0.0209808349609 ms
('counting_sort2.2 sorted:', [-8, 0, 2, 2, 7, 7, 8, 9, 9, 10, 11, 52])
time:0.0331401824951 ms


('origin arr1:', [3, 4, 15, 3, 3, 7, 10, -2, 1.4])
('origin arr2:', [7, 11, 9, 2, 52, 0, -8, 8, 7, 9, 2, 10])
('counting_sort3.1 sorted:', [-2, 1, 3, 3, 3, 4, 7, 10, 15])
time:0.018835067749 ms
('counting_sort3.2 sorted:', [-8, 0, 2, 2, 7, 7, 8, 9, 9, 10, 11, 52])
time:0.0259876251221 ms
"""