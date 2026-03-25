#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time


# 递归新建数组版本。无需交换，每个分区都是新数组
def quick_sort1(arr):
    # 第一步：递归终止条件
    arr_len = len(arr)
    if (arr_len <= 1):
        return arr
    
    # 第二步：选择基准并分区
    left = []
    right = []
    mid_index = arr_len // 2
    pivot = arr[mid_index]
    
    # 第三步：遍历数组，按基准值分区
    for i in range(arr_len):
        # 跳过基准元素本身
        if (mid_index == i):
            continue
        # 小于基准的放左边，大于等于的放右边
        if (arr[i] < pivot):
            left.append(arr[i])
        else:
            right.append(arr[i])
    
    # 第四步：递归排序并合并
    return quick_sort1(left) + [pivot] + quick_sort1(right)


"""
quick_sort recursion step:

      f([7, 11, 9, 10, 12, 13, 8])
            /       10          \
      f([7, 9, 8])           f([11, 12, 13])
        /   9    \             /    12     \
   f([7, 8])    f([])       f([11])       f[13]
   /   8  \
f([7]) f([]) 
  [7]
"""

# 标准原地分区版本：需要左右不断交换，无需新建数组
def quick_sort2(arr, left=None, right=None):
    # 第一步：初始化边界
    i = left if left is not None else 0
    j = right if right is not None else len(arr) - 1
    mid_index = (i + j) // 2
    pivot = arr[mid_index]
    
    # 第二步：分区过程
    while (i <= j):
        # 从左向右找大于基准的元素
        while (arr[i] < pivot):
            i = i + 1
        # 从右向左找小于基准的元素
        while (arr[j] > pivot):
            j -= 1
        
        # 交换元素，确保左边小于基准，右边大于基准
        if (i <= j):
            [arr[i], arr[j]] = [arr[j], arr[i]]
            i += 1
            j -= 1
    
    # 第三步：递归排序左右子数组
    if (left < j):
        quick_sort2(arr, left, j)
    if (i < right):
        quick_sort2(arr, i, right)
    return arr


# 非递归版本。需要交换，无需新建数组，利用stack或queue遍历。
def quick_sort3(arr, left=None, right=None):
    # 第一步：初始化边界
    # 快速排序非递归版：使用栈模拟递归
    left = left if left is not None else 0
    right = right if right is not None else len(arr) - 1

    stack = []
    # 初始范围入栈
    stack.append(left)
    stack.append(right)

    while (len(stack) > 0):
        # 出栈获取当前处理范围
        j = right = stack.pop()
        i = left = stack.pop()
        mid_index = (i + j) // 2
        pivot = arr[mid_index]
        
        # 分区过程
        while (i <= j):
            while (arr[i] < pivot):
                i += 1
            while (arr[j] > pivot):
                j -= 1
            if (i <= j):
                tmp = arr[j]
                arr[j] = arr[i]
                arr[i] = tmp
                i += 1
                j -= 1

        # 子区间入栈
        if (left < j):
            stack.append(left)
            stack.append(j)
        if (i < right):
            stack.append(i)
            stack.append(right)

    return arr


# 标准递归版本。左右不断分区交换，无需新建数组。
def partition(arr, left, right):
    # 分区函数：选择右侧元素为基准，将小于基准的移到左侧
    pivot_index = right
    pivot = arr[pivot_index]
    partition_index = left - 1
    for i in range(left, right):
        # 小于基准的元素移到左侧
        if (arr[i] < pivot):
            partition_index += 1
            arr[i], arr[partition_index] = arr[partition_index], arr[i]
    # 将基准元素放到正确位置
    partition_index += 1
    arr[pivot_index], arr[partition_index] = arr[partition_index], arr[pivot_index]
    return partition_index

# 快排分区交换版本
def quick_sort4(arr, left=None, right=None):
    if left < right:
        pivot = partition(arr, left, right)
        quick_sort4(arr, left, pivot - 1)
        quick_sort4(arr, pivot + 1, right)
    return arr


# test
arr1 = [7, 11, 9, 10, 12, 13, 8]
print("\r\n==quick1 orgin:==\r\n")
print(arr1)
start_time = time.time()
arr1 = quick_sort1(arr1)
print("\r\nquick1 sorted:\r\n")
print(arr1)
print("time:" + str((time.time() - start_time) * 1000) + " ms")

arr2 = [7, 11, 9, 10, 12, 13, 8]
print("\r\n==quick2 origin:==\r\n")
print(arr2)
start_time = time.time()
arr2 = quick_sort2(arr2, 0, len(arr2) - 1)
print("\r\nquick2 sorted:\r\n")
print(arr2)
print("time:" + str((time.time() - start_time) * 1000) + " ms")

arr3 = [7, 11, 9, 10, 12, 13, 8]
print("\r\n==quick3 origin:==\r\n")
print(arr3)
start_time = time.time()
arr3 = quick_sort2(arr3, 0, len(arr3) - 1)
print("\r\nquick3 sorted:\r\n")
print(arr3)
print("time:" + str((time.time() - start_time) * 1000) + " ms")

arr4 = [7, 11, 9, 10, 12, 13, 8]
print("\r\n==quick4 origin:==\r\n")
print(arr4)
start_time = time.time()
arr4 = quick_sort4(arr4, 0, len(arr4) - 1)
print("\r\nquick4 sorted:\r\n")
print(arr4)
print("time:" + str((time.time() - start_time) * 1000) + " ms")

"""
jarrys-MacBook-Pro:quick_sort jarry$ python quick_sort.py
==quick1 orgin:==

[7, 11, 9, 10, 12, 13, 8]
('split array:', [7, 11, 9, 10, 12, 13, 8])
('i=0 mid_index=3 pivot=10 arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=1 mid_index=3 pivot=10 arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=2 mid_index=3 pivot=10 arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=3 mid_index=3 pivot=10 arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=4 mid_index=3 pivot=10 arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=5 mid_index=3 pivot=10 arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=6 mid_index=3 pivot=10 arr[]=', [7, 11, 9, 10, 12, 13, 8])
('split array:', [7, 9, 8])
('i=0 mid_index=1 pivot=9 arr[]=', [7, 9, 8])
('i=1 mid_index=1 pivot=9 arr[]=', [7, 9, 8])
('i=2 mid_index=1 pivot=9 arr[]=', [7, 9, 8])
('split array:', [7, 8])
('i=0 mid_index=1 pivot=8 arr[]=', [7, 8])
('i=1 mid_index=1 pivot=8 arr[]=', [7, 8])
('sorted array:', [7, 8])
('sorted array:', [7, 8, 9])
('split array:', [11, 12, 13])
('i=0 mid_index=1 pivot=12 arr[]=', [11, 12, 13])
('i=1 mid_index=1 pivot=12 arr[]=', [11, 12, 13])
('i=2 mid_index=1 pivot=12 arr[]=', [11, 12, 13])
('sorted array:', [11, 12, 13])
('sorted array:', [7, 8, 9, 10, 11, 12, 13])

quick1 sorted:

[7, 8, 9, 10, 11, 12, 13]
time:0.220060348511 ms

==quick2 origin:==

[7, 11, 9, 10, 12, 13, 8]
('arr[i] < pivot:', ' i=0 j=6 pivot=10')
('  left=0 right=6 i=1 j=6 mid_index=3 pivot=10 arr[]=', [7, 11, 9, 10, 12, 13, 8])
('arr[i] < pivot:', ' i=2 j=5 pivot=10')
('arr[j] > pivot:', ' i=3 j=5 pivot=10')
('arr[j] > pivot:', ' i=3 j=4 pivot=10')
('  left=0 right=6 i=3 j=3 mid_index=3 pivot=10 arr[]=', [7, 8, 9, 10, 12, 13, 11])
('left < j:recursion:  left=0 right=6 i=4 j=2arr[]', [7, 8, 9, 10, 12, 13, 11])
('arr[i] < pivot:', ' i=0 j=2 pivot=8')
('arr[j] > pivot:', ' i=1 j=2 pivot=8')
('  left=0 right=2 i=1 j=1 mid_index=1 pivot=8 arr[]=', [7, 8, 9, 10, 12, 13, 11])
('i < right:recursion:  left=0 right=6 i=4 j=2arr[]', [7, 8, 9, 10, 12, 13, 11])
('arr[i] < pivot:', ' i=4 j=6 pivot=13')
('  left=4 right=6 i=5 j=6 mid_index=5 pivot=13 arr[]=', [7, 8, 9, 10, 12, 13, 11])
('left < j:recursion:  left=4 right=6 i=6 j=5arr[]', [7, 8, 9, 10, 12, 11, 13])
('  left=4 right=5 i=4 j=5 mid_index=4 pivot=12 arr[]=', [7, 8, 9, 10, 12, 11, 13])

quick2 sorted:

[7, 8, 9, 10, 11, 12, 13]
time:0.109910964966 ms

==quick3 origin:==

[7, 11, 9, 10, 12, 13, 8]
('arr[i] < pivot:', ' i=0 j=6 pivot=10')
('  left=0 right=6 i=1 j=6 mid_index=3 pivot=10 arr[]=', [7, 11, 9, 10, 12, 13, 8])
('arr[i] < pivot:', ' i=2 j=5 pivot=10')
('arr[j] > pivot:', ' i=3 j=5 pivot=10')
('arr[j] > pivot:', ' i=3 j=4 pivot=10')
('  left=0 right=6 i=3 j=3 mid_index=3 pivot=10 arr[]=', [7, 8, 9, 10, 12, 13, 11])
('left < j:recursion:  left=0 right=6 i=4 j=2arr[]', [7, 8, 9, 10, 12, 13, 11])
('arr[i] < pivot:', ' i=0 j=2 pivot=8')
('arr[j] > pivot:', ' i=1 j=2 pivot=8')
('  left=0 right=2 i=1 j=1 mid_index=1 pivot=8 arr[]=', [7, 8, 9, 10, 12, 13, 11])
('i < right:recursion:  left=0 right=6 i=4 j=2arr[]', [7, 8, 9, 10, 12, 13, 11])
('arr[i] < pivot:', ' i=4 j=6 pivot=13')
('  left=4 right=6 i=5 j=6 mid_index=5 pivot=13 arr[]=', [7, 8, 9, 10, 12, 13, 11])
('left < j:recursion:  left=4 right=6 i=6 j=5arr[]', [7, 8, 9, 10, 12, 11, 13])
('  left=4 right=5 i=4 j=5 mid_index=4 pivot=12 arr[]=', [7, 8, 9, 10, 12, 11, 13])

quick3 sorted:

[7, 8, 9, 10, 11, 12, 13]
time:0.139951705933 ms

==quick4 origin:==

[7, 11, 9, 10, 12, 13, 8]
('partition_index:', 1, 'arr[partition_index]:', 8, [7], [8, 9, 10, 12, 13])
('partition_index:', 4, 'arr[partition_index]:', 11, [9, 10], [11, 13])
('partition_index:', 3, 'arr[partition_index]:', 10, [9], [])
('partition_index:', 5, 'arr[partition_index]:', 12, [], [12])

quick4 sorted:

[7, 8, 9, 10, 11, 12, 13]
time:0.0619888305664 ms
"""