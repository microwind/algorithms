#!/usr/bin/env python
# -*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""

from typing import List
import time

""""
# 求最大连续子数组之和
# 暴力求解法，双循环
# 1. 外层循环从数组的每个位置开始。
# 2. 内层循环从外层循环的起始位置开始，逐个增加后续元素，把每一种子数组和都求出来。
# 3. 比较最大值和子数组中的和，得到最大值。
"""


def max_subarray_sum1(arr: List[int]) -> int:

    # 初始值设为负无穷，以覆盖负数子数组
    max_sum = float('-inf')

    for i in range(len(arr)):
        # 子数组之和，初始化为当前数组项
        current_sum = arr[i]
        # 更新单个最大和
        if current_sum > max_sum:
            max_sum = current_sum

        print(f'第{i + 1}位组合:')
        print(arr[i])

        for j in range(i + 1, len(arr)):
            # 更新子数组之和
            current_sum += arr[j]
            # 更新最大和
            if current_sum > max_sum:
                max_sum = current_sum

            out = " + ".join(map(str, arr[i:j + 1]))
            print(out, '=', current_sum)

    print('max_subarray_sum1->max_sum:', max_sum)
    return max_sum


""""
# 求最大连续子数组之和
# 动态规划算法
"""


def max_subarray_sum2(arr):
    if not arr:
        return 0
    # 初始化全部为0
    dp = [0] * len(arr)
    # 将第1个赋值为数组第1项
    dp[0] = arr[0]

    for i in range(1, len(arr)):
        # 当前总和与当前项比较，大的为新的当前总和
        dp[i] = max(dp[i-1] + arr[i], arr[i])

    # 从全部当前项中得到最大值
    max_sum = max(dp)

    print('max_subarray_sum2->max_sum:', max_sum)
    return max_sum


""""
# 求最大连续子数组之和
# Kadane算法，是动态规划的优化，最简单高效
"""


def max_subarray_sum3(arr: List[int]) -> int:

    # 初始化为第1位
    max_sum = arr[0]
    current_sum = arr[0]

    # 外层循环从第2位开始
    for i in range(1, len(arr)):
        # 当前最大和，通过比较当前项与当前最大和得到，相当于把小的项过滤掉了
        current_sum = max(arr[i], current_sum + arr[i])
        # 更新最大和，当前串最大和与全局最大和比较
        max_sum = max(max_sum, current_sum)
        print(f'    current_sum:, {current_sum}, max_sum:, {max_sum}')

    print('max_subarray_sum3->max_sum:', max_sum)
    return max_sum


# 计算分割点最大子数组和


def max_crossing_sum(arr, left, mid, right):
    # 计算左侧的最大子数组和
    left_sum = float('-inf')
    temp_sum = 0
    for i in range(mid, left - 1, -1):
        temp_sum += arr[i]
        if temp_sum > left_sum:
            left_sum = temp_sum

    # 计算右侧的最大子数组和
    right_sum = float('-inf')
    temp_sum = 0
    for i in range(mid + 1, right + 1):
        temp_sum += arr[i]
        if temp_sum > right_sum:
            right_sum = temp_sum

    # 返回包含分割点的最大子数组和
    return left_sum + right_sum


""""
# 求最大连续子数组之和
# 分治法，跟暴力求解类似，只不过不是从前往后，而是从中间开始
# 1. 最大子序列全部在数组左部分
# 2. 最大子序列全部在数组右部分
# 3. 最大子序列横跨左右数组
# 对于前两种情况，将原问题转化为了规模更小的同样问题。
# 对于第三种情况，根据中点进行一次循环，分别找出左边和右边的最大子序列即可。
"""


def max_subarray_sum(arr, left, right):
    # 如果只有一个元素，返回该元素
    if left == right:
        return arr[left]

    # 找到数组的中点
    mid = (left + right) // 2

    # 递归计算左侧、右侧子数组和
    left_max = max_subarray_sum(arr, left, mid)
    right_max = max_subarray_sum(arr, mid + 1, right)
    # 计算分割点最大子数组和
    cross_max = max_crossing_sum(arr, left, mid, right)

    # 返回三者中的最大值
    return max(left_max, right_max, cross_max)


def max_subarray_sum4(arr):
    if not arr:
        return 0
    max_sum = max_subarray_sum(arr, 0, len(arr) - 1)
    print('max_subarray_sum4->max_sum:', max_sum)
    return max_sum


# test
if __name__ == '__main__':

    start_time = time.time()
    arr = [-11, 10, -3, 1, -6, 13, -4]  # 最大为15
    max_subarray_sum1(arr)
    max_subarray_sum2(arr)
    max_subarray_sum3(arr)
    max_subarray_sum4(arr)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")


"""
jarry@jarrys-MacBook-Pro array % python maximum_subarray.py
第1位组合:
-11 + 10 = -1
-11 + 10 + -3 = -4
-11 + 10 + -3 + 1 = -3
-11 + 10 + -3 + 1 + -6 = -9
-11 + 10 + -3 + 1 + -6 + 13 = 4
-11 + 10 + -3 + 1 + -6 + 13 + -4 = 0
第2位组合:
10 + -3 = 7
10 + -3 + 1 = 8
10 + -3 + 1 + -6 = 2
10 + -3 + 1 + -6 + 13 = 15
10 + -3 + 1 + -6 + 13 + -4 = 11
第3位组合:
-3 + 1 = -2
-3 + 1 + -6 = -8
-3 + 1 + -6 + 13 = 5
-3 + 1 + -6 + 13 + -4 = 1
第4位组合:
1 + -6 = -5
1 + -6 + 13 = 8
1 + -6 + 13 + -4 = 4
第5位组合:
-6 + 13 = 7
-6 + 13 + -4 = 3
第6位组合:
13 + -4 = 9
第7位组合:
max_subarray_sum1->max_sum: 15
max_subarray_sum2->max_sum: 15
    current_sum:, 10, max_sum:, 10
    current_sum:, 7, max_sum:, 10
    current_sum:, 8, max_sum:, 10
    current_sum:, 2, max_sum:, 10
    current_sum:, 15, max_sum:, 15
    current_sum:, 11, max_sum:, 15
max_subarray_sum3->max_sum: 15
max_subarray_sum4->max_sum: 15
time:0.2589225769042969 ms
"""
