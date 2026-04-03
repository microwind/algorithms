#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""

import time

"""
冒泡排序算法实现
提供四种不同的实现方式，适合不同场景和性能需求
"""

def bubble_sort1(arr):
    """
    冒泡排序基础版本 - 升序排列
    
    算法原理：
    1. 从数组左端开始，依次比较相邻元素
    2. 若左元素大于右元素，则交换位置
    3. 继续向后比较，直到数组末尾
    4. 重复以上过程，每轮都会将当前未排序部分的最大值"冒泡"到最后
    
    生活类比：就像水中的气泡，轻的气泡会自然上浮到水面
    """
    print('bubble_sort1 from left to right:')
    length = len(arr)
    # 外循环：控制排序轮数，每轮确定一个最大值的位置
    for i in range(length):
        # 内循环：控制比较次数，length-i-1 避免重复比较已排序部分
        for j in range(length - i - 1):
            # 关键点：自左往右每两个进行比较，把大的交换到右侧
            if (arr[j] > arr[j + 1]):
                # Python特点：多重赋值交换
                [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]]
    print(arr)

def bubble_sort2(arr):
    """
    冒泡排序基础版本 - 降序排列
    
    算法思路：
    与升序版本相反，从数组末尾开始比较
    """
    print('bubble_sort2 from right to left:')
    length = len(arr)
    # 外循环：控制排序轮数，每轮确定一个最小值的位置
    for i in range(length):
        # 内循环：从右向左比较，j > i 避免重复比较已排序部分
        for j in range(length - 1, i, -1):
            # 关键点：自右往左每两个进行比较，把小的交换到右侧
            if (arr[j - 1] < arr[j]):
                # Python特点：多重赋值交换
                [arr[j - 1], arr[j]] = [arr[j], arr[j - 1]]
    print(arr)


def bubble_sort3(arr):
    """
    冒泡排序优化版本
    
    优化思路：
    增加一个标志位，记录某一轮是否发生了元素交换
    如果某一轮没有发生任何交换，说明数组已经完全有序
    此时可以提前终止排序过程，避免不必要的比较
    
    优化效果：
    - 对于完全有序的数组：时间复杂度从 O(n²) 优化到 O(n)
    """
    print('bubble_sort3 add flag:')
    # 优化点：增加一个标志，如果某一轮没有进行过任何的交换
    # 则说明当前数组已排好序，则不必继续后面的遍历
    length = len(arr)
    flag = True

    # 外循环：增加 flag 条件，当数组已有序时提前终止
    for i in range(length):
        if not flag:
            break
        flag = False  # 每轮开始时重置标志
        # 内循环：控制比较次数，length-i-1 避免重复比较已排序部分
        for j in range(length - i - 1):
            # 关键点：自左往右每两个进行比较，把大的交换到右侧
            if (arr[j] > arr[j + 1]):
                flag = True  # 发生交换，设置标志
                # Python特点：多重赋值交换
                [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]]
    print(arr)


def bubble_sort4(arr):
    """
    插入冒泡排序法
    """
    print('bubble_sort4:')
    length = len(arr)
    # 外循环：控制排序轮数，i 从 1 开始，因为第 0 个元素默认为已排序
    for i in range(1, length):
        # 内循环：在已排序区域中查找插入位置
        for j in range(i):
            # 关键点：如果待插入元素小于已排序区域的某个元素，则交换
            if (arr[j] > arr[i]):
                # Python特点：多重赋值交换
                [arr[i], arr[j]] = [arr[j], arr[i]]
    print(arr)


def print_array(arr, label):
    """
    打印数组内容的辅助函数
    
    @param list arr: 要打印的数组
    @param str label: 数组的标签说明
    """
    print(f"{label}: [{', '.join(map(str, arr))}]")

def performance_test(sort_func, arr, name):
    """
    性能测试辅助函数
    
    @param function sort_func: 排序函数
    @param list arr: 测试数组
    @param str name: 测试名称
    """
    # 创建数组副本，避免修改原数组
    test_arr = arr.copy()
    print_array(test_arr, f"{name}原始数组")
    
    # 开始计时
    start_time = time.time()
    sort_func(test_arr)
    end_time = time.time()
    
    print_array(test_arr, f"{name}排序结果")
    print(f"{name}: {(end_time - start_time) * 1000:.3f}ms")
    print()  # 空行分隔

# ==================== 主程序：算法演示和性能测试 ====================

# 测试数据：
test_data = [7, 11, 9, 10, 12, 13, 8]

print("=== 冒泡排序算法演示 ===\n")

# 测试1：基础升序版本
performance_test(bubble_sort1, test_data, "基础升序版本")

# 测试2：基础降序版本
performance_test(bubble_sort2, test_data, "基础降序版本")

# 测试3：优化版本
performance_test(bubble_sort3, test_data, "优化版本")

# 测试4：插入式版本
performance_test(bubble_sort4, test_data, "插入式版本")

print("=== 算法对比总结 ===")
print("1. 基础版本：简单易懂，适合学习算法原理")
print("2. 降序版本：展示算法的灵活性，可按需排序")
print("3. 优化版本：通过标志位优化，适合实际应用")
print("4. 插入式版本：结合其他排序思想，性能更稳定")

"""
打印结果
jarry@Mac bubblesort % python bubble_sort.py
=== 冒泡排序算法演示 ===

基础升序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubble_sort1 from left to right:
[7, 8, 9, 10, 11, 12, 13]
基础升序版本排序结果: [7, 8, 9, 10, 11, 12, 13]
基础升序版本: 0.xxxms

基础降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubble_sort2 from right to left:
[13, 12, 11, 10, 9, 8, 7]
基础降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]
基础降序版本: 0.xxxms

优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubble_sort3 add flag:
[7, 8, 9, 10, 11, 12, 13]
优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]
优化版本: 0.xxxms

插入式版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubble_sort4:
[7, 8, 9, 10, 11, 12, 13]
插入式版本排序结果: [7, 8, 9, 10, 11, 12, 13]
插入式版本: 0.xxxms

=== 算法对比总结 ===
1. 基础版本：简单易懂，适合学习算法原理
2. 降序版本：展示算法的灵活性，可按需排序
3. 优化版本：通过标志位优化，适合实际应用
4. 插入式版本：结合其他排序思想，性能更稳定
"""