#!/usr/bin/env python
#-*- encoding: UTF-8-*-

"""
 * Copyright  https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""

"""
二分查找算法实现
提供多种实现方式，适合不同场景和性能需求
"""

import time

def binary_search1(arr, target):
    """
    binary_search1 - 标准非递归版本，传递左右区间指针
    
    算法步骤：
    1. 初始化左右边界：left=0, right=len(arr)-1
    2. 计算中间位置：mid_index = int((left + right) / 2)
    3. 比较中间值与目标值
    4. 根据比较结果调整查找范围
    5. 重复直到找到目标或范围为空
    
    @param {list} arr - 有序数组
    @param {*} target - 目标值
    @returns {int} 找到返回索引，未找到返回-1
    """
    left = 0
    right = len(arr) - 1
    
    # left是左侧，right是最右侧。搜索区间长度小于1时停止
    while left <= right:
        # 注意：当 left + right 过大时，可能会导致整数溢出，导致 mid_index 计算错误
        mid_index = int((left + right) / 2)
        middle = arr[mid_index]
        if target > middle:
            left = mid_index + 1
        else:
            right = mid_index - 1
    # 循环结束时，left 指向第一个大于 target 的元素位置
    if left < len(arr) and arr[left] == target:
        return left
    return -1


def binary_search2(arr, target, left=0, right=None):
    """
    binary_search2 - 递归实现，移动左右区间指针
    
    算法步骤：
    1. 处理默认参数，设置初始边界
    2. 计算中间位置和中间值
    3. 比较中间值与目标值
    4. 根据比较结果递归查找对应半区
    5. 处理重复项的特殊情况
    
    @param {list} arr - 有序数组
    @param {*} target - 目标值
    @param {int} left - 左边界（可选）
    @param {int} right - 右边界（可选）
    @returns {int} 找到返回索引，未找到返回-1
    """
    right = len(arr) - 1 if right is None else right
    mid_index = int((left + right) / 2)
    middle = arr[mid_index]
    # 中间值等于查找项说明找到了，则返回中间项下标
    if middle == target:
        # 如果有重复项，返回第一个位置
        if arr[left] == target:
            return left
        return mid_index
    # 如果左侧与右侧相同，表面查找完毕，返回-1
    if left >= right:
        return -1
    if target > middle:
        # 折半右侧部分开始递归查找
        return binary_search2(arr, target, mid_index + 1, right)
    else:
        # 折半左侧部分开始递归查找
        return binary_search2(arr, target, left, mid_index - 1)


def binary_search3(arr, target, right=0):
    """
    binary_search3 - 二分搜索递归查找，记录下右侧位置
    
    算法步骤：
    1. 处理边界条件，数组长度小于等于1时特殊处理
    2. 计算中间位置和中间值
    3. 比较中间值与目标值
    4. 根据比较结果递归查找对应半区
    5. 累积索引位置，确保返回正确的绝对位置
    
    @param {list} arr - 有序数组
    @param {*} target - 目标值
    @param {int} right - 累积的右侧位置（内部使用）
    @returns {int} 找到返回索引，未找到返回-1
    """
    length = len(arr)
    if (length <= 1 and target != arr[0]):
        return -1
    mid_index = int((length - 1) / 2)
    mid = arr[mid_index]
    if (target == mid):
        return right + mid_index
    elif (target > mid):
        # 如果在右侧，则需要将中间index加上
        return binary_search3(arr[mid_index + 1:], target, right + mid_index + 1)
    else:
        # 如果在左侧，则直接递归左侧部分
        return binary_search3(arr[0:mid_index], target, right)


def main():
    """
    主程序：演示二分查找算法的性能对比
    
    测试内容：
    1. binary_search1 - 标准非递归版本
    2. binary_search2 - 递归版本，处理重复项
    3. binary_search3 - 递归版本，累积索引位置
    """
    print("=" * 60)
    print("二分查找算法演示")
    print("=" * 60)
    
    # 创建测试数据
    arr = [2, 3, 8, 10, 10, 13]
    
    # 测试 binary_search1
    start_time = time.time()
    result = binary_search1(arr, 10)
    print('binary_search1(arr, 10)', '=> result:', result)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    
    # 测试 binary_search2
    start_time = time.time()
    result = binary_search2(arr, 10)
    print('binary_search2(arr, 10)', '=> result:', result)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    
    # 测试 binary_search3
    start_time = time.time()
    result = binary_search3(arr, 10)
    print('binary_search3(arr, 10)', '=> result:', result)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")


if __name__ == "__main__":
    main()

"""
打印结果
jarry@jarrys-MacBook-Pro binarysearch % python binary_search.py
============================================================
二分查找算法演示
============================================================
binary_search1(arr, 10) => result: 3
time:0.041961669921875 ms
binary_search2(arr, 10) => result: 3
time:0.007867813110351562 ms
binary_search3(arr, 10) => result: 4
time:0.006914138793945312 ms
"""