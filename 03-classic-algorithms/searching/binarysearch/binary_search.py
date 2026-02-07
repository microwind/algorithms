#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time

# 标准非递归版本，传递左右区间指针
def binary_search1(arr, item):
    left = 0
    right = len(arr) - 1

    while left <= right:
        mid_index = int((left + right) / 2)
        middle = arr[mid_index]
        if item > middle:
            left = mid_index + 1
        else:
            right = mid_index - 1

    if left < len(arr) and arr[left] == item:
        return left
    return -1

# 递归实现，移动左右区间指针
def binary_search2(arr, item, left = 0, right = None):
    right = len(arr) - 1 if right == None else right
    mid_index = int((left + right) / 2)
    middle = arr[mid_index]
    if middle == item:
        if arr[left] == item:
            return left
        return mid_index

    if left >= right:
        return -1

    if item > middle:
        return binary_search2(arr, item, mid_index + 1, right)
    else:
        return binary_search2(arr, item, left, mid_index - 1)

#  二分搜索递归查找，记录下右侧位置
def binary_search3(arr, item, right = 0):
    length = len(arr)
    if (length <= 1 and item != arr[0]):
        return -1
    mid_index = int((length - 1) / 2)
    mid = arr[mid_index]
    if (item == mid):
        return right + mid_index
    elif (item > mid):
        return binary_search3(arr[mid_index:], item, right + mid_index + 1)
    else:
        return binary_search3(arr[0:mid_index], item, right)

start_time = time.time()
arr = [2, 3, 8, 10, 10, 13]
result = binary_search1(arr, 10)
print('binarySearch1(arr, 10)', '=> result:', result)
print("time:" + str((time.time() - start_time) * 1000) + " ms")

start_time = time.time()
result = binary_search2(arr, 10)
print('binarySearch2(arr, 10)', '=> result:', result)
print("time:" + str((time.time() - start_time) * 1000) + " ms")

start_time = time.time()
result = binary_search3(arr, 10)
print('binarySearch2(arr, 10)', '=> result:', result)
print("time:" + str((time.time() - start_time) * 1000) + " ms")


"""
jarry@jarrys-MacBook-Pro binarysearch % python binary_search.py
('binarySearch1(arr, 10)', '=> result:', 3)
time:0.0419616699219 ms
('binarySearch2(arr, 10)', '=> result:', 3)
time:0.00786781311035 ms
('binarySearch2(arr, 10)', '=> result:', 4)
time:0.00691413879395 ms
"""