#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time
"""
# 选择排序优化版，同时找出最小和最大值进行交换，可减少1半遍历
# 把数列分为前中后三个区间，分别代表最小已排序、中间待排序以及最大已排序区间
# 遍历中间待排序同时找最大和最小值，分别交换到最小值区间和最大值区间
"""


def selection_sort(arr):
    arr_len = len(arr)
    for i in range(arr_len - 1):
        # 初始最小值和下标
        min_idx = i
        min_value = arr[min_idx]
        # 初始最大值和下标
        max_idx = i
        max_value = arr[max_idx]

        # 最小和最大序列里最新待交换的下标
        # 最小序列的下标从0开始，自前往后递加
        min_list_idx = min_idx
        # 最大序列的下标从数组最后1位开始，自后往前递减
        max_list_idx = arr_len - 1 - i
        # 如果最小和最大下标相同，说明只剩下1个数字，则终止循环
        if min_list_idx == max_list_idx:
            break

        # 逐一遍历待排序区间，找出最小和最大值
        # 待排序区间在最小值序列和和最大值序列之间
        # 待比较区间的下标j从i+1开始，到最大已排序前结束
        j = i + 1
        while j < arr_len - i:
            # 从待排序列表找到最小值和最大值及位置
            if arr[j] < min_value:
                min_idx = j
                min_value = arr[min_idx]
            elif arr[j] > max_value:
                max_idx = j
                max_value = arr[max_idx]
            j += 1

        # 如果最小值等于最小序列待交换的值，且最大值等于最大序列里待交换的值，则跳过
        if arr[min_idx] == arr[min_list_idx] and arr[max_idx] == arr[
                max_list_idx]:
            continue

        print('min_value=', min_value, 'max_value=', max_value, 'min_idx=',
              min_idx, 'max_idx=', max_idx, 'min_list_idx=', min_list_idx,
              'max_list_idx=', max_list_idx)

        # 先交换小值，再交换大值
        arr[min_list_idx], arr[min_idx] = arr[min_idx], arr[min_list_idx]
        # 如果最大值被交换了，则需要更新最大值的下标
        if arr[min_idx] == max_value:
            max_idx = min_idx
        arr[max_list_idx], arr[max_idx] = arr[max_idx], arr[max_list_idx]

    return arr


# test
if __name__ == '__main__':

    # 1. arr1
    arr1 = [7, 11, -9, 10, -12, 13, 8]
    print("\r\norgin arr1:")
    print(arr1)
    start_time1 = time.time()
    print('arr1 sorted:', selection_sort(arr1))
    print("time:" + str((time.time() - start_time1) * 1000) + " ms")

    # 1. arr2
    arr2 = [7, 11, 121, -9, 545, 110, -210, 1245, -132, 192, 153, 19, 8]
    print("\r\norgin arr2:")
    print(arr2)
    start_time2 = time.time()
    print('arr2 sorted:', selection_sort(arr2))
    print("time:" + str((time.time() - start_time2) * 1000) + " ms")

    # 1. arr3
    arr3 = [57, 311, 131, -9, 415, 10, 1330, 1245, -12, 1942, 123, 129, 80]
    print("\r\norgin arr3:")
    print(arr3)
    start_time3 = time.time()
    print('arr3 sorted:', selection_sort(arr3))
    print("time:" + str((time.time() - start_time3) * 1000) + " ms")
"""
jarry@jarrys-MacBook-Pro selectionsort % python selection_sort2.py

orgin arr1:
[7, 11, -9, 10, -12, 13, 8]
('min_value=', -12, 'max_value=', 13, 'min_idx=', 4, 'max_idx=', 5, 'min_list_idx=', 0, 'max_list_idx=', 6)
('min_value=', -9, 'max_value=', 11, 'min_idx=', 2, 'max_idx=', 1, 'min_list_idx=', 1, 'max_list_idx=', 5)
('min_value=', 7, 'max_value=', 10, 'min_idx=', 4, 'max_idx=', 3, 'min_list_idx=', 2, 'max_list_idx=', 4)
('arr1 sorted:', [-12, -9, 7, 8, 10, 11, 13])
time:0.0381469726562 ms

orgin arr2:
[7, 11, 121, -9, 545, 110, -210, 1245, -132, 192, 153, 19, 8]
('min_value=', -210, 'max_value=', 1245, 'min_idx=', 6, 'max_idx=', 7, 'min_list_idx=', 0, 'max_list_idx=', 12)
('min_value=', -132, 'max_value=', 545, 'min_idx=', 8, 'max_idx=', 4, 'min_list_idx=', 1, 'max_list_idx=', 11)
('min_value=', -9, 'max_value=', 192, 'min_idx=', 3, 'max_idx=', 9, 'min_list_idx=', 2, 'max_list_idx=', 10)
('min_value=', 7, 'max_value=', 153, 'min_idx=', 6, 'max_idx=', 9, 'min_list_idx=', 3, 'max_list_idx=', 9)
('min_value=', 8, 'max_value=', 121, 'min_idx=', 7, 'max_idx=', 6, 'min_list_idx=', 4, 'max_list_idx=', 8)
('min_value=', 11, 'max_value=', 110, 'min_idx=', 6, 'max_idx=', 5, 'min_list_idx=', 5, 'max_list_idx=', 7)
('arr2 sorted:', [-210, -132, -9, 7, 8, 11, 19, 110, 121, 153, 192, 545, 1245])
time:0.0600814819336 ms

orgin arr3:
[57, 311, 131, -9, 415, 10, 1330, 1245, -12, 1942, 123, 129, 80]
('min_value=', -12, 'max_value=', 1942, 'min_idx=', 8, 'max_idx=', 9, 'min_list_idx=', 0, 'max_list_idx=', 12)
('min_value=', -9, 'max_value=', 1330, 'min_idx=', 3, 'max_idx=', 6, 'min_list_idx=', 1, 'max_list_idx=', 11)
('min_value=', 10, 'max_value=', 1245, 'min_idx=', 5, 'max_idx=', 7, 'min_list_idx=', 2, 'max_list_idx=', 10)
('min_value=', 57, 'max_value=', 415, 'min_idx=', 8, 'max_idx=', 4, 'min_list_idx=', 3, 'max_list_idx=', 9)
('min_value=', 123, 'max_value=', 131, 'min_idx=', 7, 'max_idx=', 5, 'min_list_idx=', 5, 'max_list_idx=', 7)
('arr3 sorted:', [-12, -9, 10, 57, 80, 123, 129, 131, 311, 415, 1245, 1330, 1942])
time:0.172138214111 ms
"""