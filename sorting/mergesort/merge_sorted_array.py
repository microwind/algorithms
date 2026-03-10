#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https:#github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time
"""
   * 双指针合并两个已排序数组。
   * 新建数组复制法，比较数组1和数组2的当前项，将小的添加到新数组中
   * @param:list one
   * @param:list two
"""


def merge_sorted1(one, two):
    # 双指针法合并两个已排序数组
    i = j = k = 0
    one_len = len(one)
    two_len = len(two)
    result = [None] * (one_len + two_len)

    # 比较两个数组元素，小的放入结果数组
    while i < one_len and j < two_len:
        if one[i] < two[j]:
            result[k] = one[i]
            i += 1
        else:
            result[k] = two[j]
            j += 1
        k += 1

    # 处理数组1剩余元素
    while i < one_len:
        result[k] = one[i]
        k += 1
        i += 1

    # 处理数组2剩余元素
    while j < two_len:
        result[k] = two[j]
        k += 1
        j += 1

    return result


"""
  * 合并两个已排序数组。
  * 插入法，从第一个数组里取出一项，自前往后逐个与第二个数组项进行比较，插入到第二个数组中
  * @param:list one
  * @param:lisit two
"""


def merge_sorted2(one, two):
    # 插入法：将数组1元素插入到数组2中
    one_len = len(one)
    two_len = len(two)
    
    for i in range(one_len):
        # 找到插入位置
        inserted = False
        for j in range(two_len):
            if one[i] < two[j]:
                two.insert(j, one[i])
                two_len += 1
                inserted = True
                break
        # 如果没找到插入位置，添加到末尾
        if not inserted:
            two.append(one[i])
            two_len += 1

    return two


"""
  * 合并两个已排序数组。
  * 合并数组再采取普通排序法
  * @param:list one
  * @param:list two
"""


def merge_sorted3(one, two):
    # 合并后插入排序：先合并再排序
    one_len = len(one)
    two_len = len(two)
    result = one + two
    
    # 对合并后的数组进行插入排序
    for i in range(one_len, one_len + two_len):
        j = i - 1
        current = result[i]
        # 将当前元素插入到已排序部分的正确位置
        while (j >= 0 and current < result[j]):
            result[j + 1] = result[j]
            j -= 1
        result[j + 1] = current

    return result


if __name__ == '__main__':

    # 1. merge_sorted1
    arr1 = [-3, 7, 9, 10, 11, 15, 16]
    arr2 = [-1, 5, 6, 9, 12]
    print("\r\n Source array1:")
    print(arr1, arr2)
    start_time = time.time()
    arr = merge_sorted1(arr1, arr2)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("merge_sorted1 sorted: ", arr)

    # 2. merge_sorted2
    arr1 = [-3, 7, 9, 10, 11, 15, 16]
    arr2 = [-1, 5, 6, 9, 12]
    print("\r\n Source array2:")
    print(arr1, arr2)
    start_time = time.time()
    merge_sorted2(arr1, arr2)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("merge_sorted2 sorted: ", arr)

    # 3. merge_sorted3
    arr1 = [-3, 7, 9, 10, 11, 15, 16]
    arr2 = [-1, 5, 6, 9, 12]
    print("\r\n Source array3:")
    print(arr1, arr2)
    start_time = time.time()
    merge_sorted3(arr1, arr2)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("merge_sorted3 sorted: ", arr)


"""
jarry@jarrys-MacBook-Pro mergesort % python merge_sorted_array.py

 Source array1:
([-3, 7, 9, 10, 11, 15, 16], [-1, 5, 6, 9, 12])
time:0.00810623168945 ms
('merge_sorted1 sorted: ', [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16])

 Source array2:
([-3, 7, 9, 10, 11, 15, 16], [-1, 5, 6, 9, 12])
time:0.014066696167 ms
('merge_sorted2 sorted: ', [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16])

 Source array3:
([-3, 7, 9, 10, 11, 15, 16], [-1, 5, 6, 9, 12])
time:0.00619888305664 ms
('merge_sorted3 sorted: ', [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16])
"""