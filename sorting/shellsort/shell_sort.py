#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time


# 1. 希尔排序标准版，基于插入排序进行分组排序，步长按1/2缩减。
def shell_sort1(arr):
    # 希尔排序：插入排序的改进版，按步长分组排序
    size = len(arr)
    # 初始步长为数组长度的一半
    gap = size // 2

    # 按步长递减排序
    while gap > 0:
        for i in range(gap, size):
            current = arr[i]
            j = i
            # 对每个子序列进行插入排序
            while j >= gap and current < arr[j - gap]:
                arr[j] = arr[j - gap]
                j -= gap
            # 插入当前元素
            arr[j] = current
        # 步长减半
        gap = gap // 2
    return arr


# 2. 希尔排序，基于插入排序进行分组排序，步长按3倍递减。
def shell_sort2(arr):
    # 希尔排序优化版：使用3x+1步长序列
    size = len(arr)
    gap = 1
    # 计算初始步长：3x+1序列
    while gap < (size // 3):
        gap = gap * 3 + 1

    # 按步长递减排序
    while (gap > 0):
        for i in range(gap, size):
            current = arr[i]
            j = i - gap
            # 对每个子序列进行插入排序
            while j >= 0 and arr[j] > current:
                arr[j + gap] = arr[j]
                j -= gap
            # 插入当前元素
            arr[j + gap] = current
        # 步长按3倍缩减
        gap = gap // 3
    return arr


if __name__ == '__main__':

    # shell_sort1
    arr1 = [33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431]
    print("arr1 origin:", arr1)
    time1 = time.time()
    arr1 = shell_sort1(arr1)
    print("time:" + str((time.time() - time1) * 1000) + " ms")
    print("arr1 sorted: ", arr1)

    # shell_sort2
    arr2 = [33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431]
    print("arr2 origin:", arr2)
    time2 = time.time()
    arr2 = shell_sort2(arr2)
    print("time:" + str((time.time() - time2) * 1000) + " ms")
    print("arr2 sorted: ", arr2)
"""
jarry@jarrys-MacBook-Pro shellsort % python shell_sort.py
('arr1 origin:', [33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431])
gap=5 i=5 j-gap=0 j=5
gap=5 i=9 j-gap=4 j=9
gap=2 i=5 j-gap=3 j=5
gap=2 i=6 j-gap=4 j=6
gap=2 i=6 j-gap=2 j=4
gap=2 i=8 j-gap=6 j=8
gap=1 i=4 j-gap=3 j=4
time:0.0381469726562 ms
('arr1 sorted: ', [-7, 4, 10.5, 15, 33, 43, 200, 1235, 87431, 323454])
('arr2 origin:', [33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431])
gap=4 i=5 j=1 j+gap=5
gap=4 i=6 j=2 j+gap=6
gap=4 i=8 j=4 j+gap=8
gap=1 i=1 j=0 j+gap=1
gap=1 i=2 j=1 j+gap=2
gap=1 i=5 j=4 j+gap=5
gap=1 i=5 j=3 j+gap=4
gap=1 i=5 j=2 j+gap=3
gap=1 i=5 j=1 j+gap=2
gap=1 i=6 j=5 j+gap=6
gap=1 i=6 j=4 j+gap=5
gap=1 i=6 j=3 j+gap=4
gap=1 i=9 j=8 j+gap=9
time:0.0479221343994 ms
('arr2 sorted: ', [-7, 4, 10.5, 15, 33, 43, 200, 1235, 87431, 323454])
"""