#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time


# 递归新建数组版本。无需交换，每个分区都是新数组，数量庞大
def quick_sort1(arr):
    # 数组长度为1就不再分级
    arr_len = len(arr)
    if (arr_len <= 1):
        return arr

    print('split array:', arr)

    left = []
    right = []
    # 设置中间数
    mid_index = arr_len / 2
    pivot = arr[mid_index]

    for i in range(arr_len):
        print(
            'i=' + str(i) + ' mid_index=' + str(mid_index) + ' pivot=' +
            str(pivot) + ' arr[]=', arr)
        # 当中间基数等于i时，跳过当前。中间数递归完成时合并
        if (mid_index == i):
            continue

        # 当前数组端里面的项小于基数则添加到左侧
        if (arr[i] < pivot):
            left.append(arr[i])
            # 大于等于则添加到右侧
        else:
            right.append(arr[i])

    arr = quick_sort1(left) + [pivot] + quick_sort1(right)
    print('sorted array:', arr)
    # 递归调用遍历左侧和右侧，再将中间值连接起来
    return arr


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

# 标准递归版本。需要左右不断交换，无需新建数组。
def quick_sort2(arr, left=None, right=None):

    i = left = left if left is not None else 0
    j = right = right if right is not None else len(arr) - 1
    mid_index = (i + j) / 2
    pivot = arr[mid_index]

    # 当左侧小于等于右侧则表示还有值没有对比，需要继续
    while (i <= j):
        # 当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
        while (arr[i] < pivot):
            print('arr[i] < pivot:',
                  ' i=' + str(i) + ' j=' + str(j) + ' pivot=' + str(pivot))
            i = i + 1

        # 当前右侧大于基准时左移，直到找出比基准值小的位置来
        while (arr[j] > pivot):
            print('arr[j] > pivot:',
                  ' i=' + str(i) + ' j=' + str(j) + ' pivot=' + str(pivot))
            j -= 1

        print(
            '  left=' + str(left) + ' right=' + str(right) + ' i=' + str(i) +
            ' j=' + str(j) + ' mid_index=' + str(mid_index) + ' pivot=' +
            str(pivot) + ' arr[]=', arr)

        # 当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
        if (i <= j):
            [arr[i], arr[j]] = [arr[j], arr[i]]
            # 缩小搜查范围，直到左侧都小于基数，右侧都大于基数
            i += 1
            j -= 1

    # 左侧小于基数位置，不断递归左边部分
    if (left < j):
        print(
            'left < j:recursion:  left=' + str(left) + ' right=' + str(right) +
            ' i=' + str(i) + ' j=' + str(j) + 'arr[]', arr)
        quick_sort2(arr, left, j)

    # 基数位置小于右侧，不断递归右侧部分
    if (i < right):
        print(
            'i < right:recursion:  left=' + str(left) + ' right=' +
            str(right) + ' i=' + str(i) + ' j=' + str(j) + 'arr[]', arr)
        quick_sort2(arr, i, right)

    return arr


# 非递归版本。需要交换，无需新建数组，利用stack或queue遍历。
def quick_sort3(arr, left=None, right=None):
    left = left if left is not None else 0
    right = right if right is not None else len(arr) - 1

    stack = []
    #  i, j, mid_index, pivot, tmp
    # 与标准递归版相同，只是将递归改为遍历栈的方式
    # 先将左右各取一个入栈
    stack.append(left)
    stack.append(right)

    while (len(stack) > 0):
        # 如果栈内还有数据，则一并马上取出，其他逻辑与标准递归版同
        j = right = stack.pop()
        i = left = stack.pop()
        mid_index = ((i + j) / 2)
        pivot = arr[mid_index]
        while (i <= j):
            while (arr[i] < pivot):
                print('arr[i] < pivot:',
                      ' i=' + str(i) + ' j=' + str(j) + ' pivot=' + str(pivot))
                i += 1

            while (arr[j] > pivot):
                print('arr[j] > pivot:',
                      ' i=' + str(i) + ' j=' + str(j) + ' pivot=' + str(pivot))
                j -= 1

            # 打印中间过程
            print(
                '  left=' + str(left) + ' right=' + str(right) + ' i=' +
                str(i) + ' j=' + str(j) + ' mid_index=' + str(mid_index) +
                ' pivot=' + str(pivot) + ' arr[]=', arr)

            if (i <= j):
                tmp = arr[j]
                arr[j] = arr[i]
                arr[i] = tmp
                i += 1
                j -= 1

        if (left < j):
            # 与递归版不同，这里添加到栈中，以便继续循环
            print(
                'i < right:recursion:  left=' + str(left) + ' right=' +
                str(right) + ' i=' + str(i) + ' j=' + str(j) + 'arr[]', arr)
            stack.append(left)
            stack.append(j)

        if (i < right):
            print(
                'i < right:recursion:  left=' + str(left) + ' right=' +
                str(right) + ' i=' + str(i) + ' j=' + str(j) + 'arr[]', arr)
            stack.append(i)
            stack.append(right)

    return arr


# 标准递归版本。左右不断分区交换，无需新建数组。
def partition(arr, left, right):
    # pivot基准可以任意挑选，这里取右侧
    pivot_index = right
    pivot = arr[pivot_index]
    partition_index = left - 1
    for i in range(left, right):
        # 如果小于基准值则将小项移到左侧
        if (arr[i] < pivot):
            partition_index += 1
            arr[i], arr[partition_index] = arr[partition_index], arr[i]
    # 最后将基准位置调换至交换位置
    partition_index += 1
    arr[pivot_index], arr[partition_index] = arr[partition_index], arr[pivot_index]
    print('partition_index:', partition_index, 'arr[partition_index]:', arr[partition_index], arr[left:partition_index],
          arr[partition_index:right])
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