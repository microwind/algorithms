#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time

def merge_sort1(values):
    # 归并排序：分治法，递归分割后合并
    result = values
    if len(values) > 1:
        mid = len(values) // 2
        left = values[:mid]
        right = values[mid:]
        # 递归排序左右子数组
        left = merge_sort1(left)
        right = merge_sort1(right)

        # 合并两个已排序数组
        result = []
        while len(left) > 0 and len(right) > 0:
            if left[0] < right[0]:
                result.append(left[0])
                left.pop(0)
            else:
                result.append(right[0])
                right.pop(0)

        # 添加剩余元素
        for i in left:
            result.append(i)
        for i in right:
            result.append(i)

    return result



## merge_sort2
def merge_sort2(arr):
    # 归并排序原地版本：直接修改原数组
    if len(arr) > 1:
        mid = len(arr) // 2
        left_arr = arr[:mid]
        right_arr = arr[mid:]

        # 递归排序左右子数组
        merge_sort2(left_arr)
        merge_sort2(right_arr)

        i = j = k = 0

        # 合并左右子数组到原数组
        while i < len(left_arr) and j < len(right_arr):
            if left_arr[i] < right_arr[j]:
                arr[k] = left_arr[i]
                i += 1
            else:
                arr[k] = right_arr[j]
                j += 1
            k += 1

        # 复制左侧剩余元素
        while i < len(left_arr):
            arr[k] = left_arr[i]
            i += 1
            k += 1

        # 复制右侧剩余元素
        while j < len(right_arr):
            arr[k] = right_arr[j]
            j += 1
            k += 1


if __name__ == '__main__':

    # 1. merge_sort1
    arr = [7, 11, 9, 10, 12, 13, 8]
    print("\r\n Source array1:")
    print(arr)
    start_time = time.time()
    arr = merge_sort1(arr)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("merge_sort1 sorted: ", arr)

    # 2. merge_sort2
    arr = [7, 11, 9, 10, 12, 13, 8]
    print("\r\n Source array2:")
    print(arr)
    start_time = time.time()
    merge_sort2(arr)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("merge_sort2 sorted: ", arr)

"""
jarry@jarrys-mbp mergesort % python merge_sort.py

 Source array1:
[7, 11, 9, 10, 12, 13, 8]
time:0.0290870666504 ms
('merge_sort1 sorted: ', [7, 8, 9, 10, 11, 12, 13])

 Source array2:
[7, 11, 9, 10, 12, 13, 8]
time:0.0190734863281 ms
('merge_sort2 sorted: ', [7, 8, 9, 10, 11, 12, 13])
"""