#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time


def selection_sort1(arr):
    l = len(arr)
    for i in range(l - 1):
        min = arr[i]
        min_idx = i
        j = i + 1
        while j < l:
            # 从待排序列表找到最小值和位置
            if arr[j] < min:
                min = arr[j]
                min_idx = j

            print('i=' + str(i), ' j=' + str(j), 'min=' + str(min),
                  'arr[i]=' + str(arr[i]), 'arr[j]=' + str(arr[j]), 'arr[]=',
                  arr)

            j += 1
        # 将待排序里最小值交换到已排序最后面
        if min_idx != i:
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

# 新建数组版，无需交换
def selection_sort2(arr):
    new_list = []
    i = 0
    l = len(arr)
    while (i < l):
        min = arr[i]
        min_idx = i
        j = i + 1
        while (j < l):
            # 找到并记录下最小值和位置
            if (arr[j] < min):
                min = arr[j]
                min_idx = j

                print('i=' + str(i), ' j=' + str(j), 'min=' + str(min),
                      'arr[i]=' + str(arr[i]), 'arr[j]=' + str(arr[j]),
                      'arr[]=', arr)
            j += 1

        # 将待排序里最小值添加到新数组中去
        new_list.append(min)
        # 原数组中删除对应的项
        arr.remove(min)
        l -= 1

    return new_list


# test
if __name__ == '__main__':

    # 1. sort1
    arr1 = [7, 11, -9, 10, -12, 13, 8]
    print("\r\norgin arr1:")
    print(arr1)
    start_time1 = time.time()
    print('arr1 sorted:', selection_sort1(arr1))
    print("time:" + str((time.time() - start_time1) * 1000) + " ms")

    # 1. sort2
    arr2 = [7, 11, -9, 10, -12, 13, 8]
    print("\r\norgin arr2:")
    print(arr2)
    start_time2 = time.time()
    print('arr2 sorted:', selection_sort2(arr2))
    print("time:" + str((time.time() - start_time2) * 1000) + " ms")
"""
jarry@jarrys-MacBook-Pro selectionsort % python selection_sort.py

orgin arr1:
[7, 11, -9, 10, -12, 13, 8]
('i=0', ' j=1', 'min=7', 'arr[i]=7', 'arr[j]=11', 'arr[]=', [7, 11, -9, 10, -12, 13, 8])
('i=0', ' j=2', 'min=-9', 'arr[i]=7', 'arr[j]=-9', 'arr[]=', [7, 11, -9, 10, -12, 13, 8])
('i=0', ' j=3', 'min=-9', 'arr[i]=7', 'arr[j]=10', 'arr[]=', [7, 11, -9, 10, -12, 13, 8])
('i=0', ' j=4', 'min=-12', 'arr[i]=7', 'arr[j]=-12', 'arr[]=', [7, 11, -9, 10, -12, 13, 8])
('i=0', ' j=5', 'min=-12', 'arr[i]=7', 'arr[j]=13', 'arr[]=', [7, 11, -9, 10, -12, 13, 8])
('i=0', ' j=6', 'min=-12', 'arr[i]=7', 'arr[j]=8', 'arr[]=', [7, 11, -9, 10, -12, 13, 8])
('i=1', ' j=2', 'min=-9', 'arr[i]=11', 'arr[j]=-9', 'arr[]=', [-12, 11, -9, 10, 7, 13, 8])
('i=1', ' j=3', 'min=-9', 'arr[i]=11', 'arr[j]=10', 'arr[]=', [-12, 11, -9, 10, 7, 13, 8])
('i=1', ' j=4', 'min=-9', 'arr[i]=11', 'arr[j]=7', 'arr[]=', [-12, 11, -9, 10, 7, 13, 8])
('i=1', ' j=5', 'min=-9', 'arr[i]=11', 'arr[j]=13', 'arr[]=', [-12, 11, -9, 10, 7, 13, 8])
('i=1', ' j=6', 'min=-9', 'arr[i]=11', 'arr[j]=8', 'arr[]=', [-12, 11, -9, 10, 7, 13, 8])
('i=2', ' j=3', 'min=10', 'arr[i]=11', 'arr[j]=10', 'arr[]=', [-12, -9, 11, 10, 7, 13, 8])
('i=2', ' j=4', 'min=7', 'arr[i]=11', 'arr[j]=7', 'arr[]=', [-12, -9, 11, 10, 7, 13, 8])
('i=2', ' j=5', 'min=7', 'arr[i]=11', 'arr[j]=13', 'arr[]=', [-12, -9, 11, 10, 7, 13, 8])
('i=2', ' j=6', 'min=7', 'arr[i]=11', 'arr[j]=8', 'arr[]=', [-12, -9, 11, 10, 7, 13, 8])
('i=3', ' j=4', 'min=10', 'arr[i]=10', 'arr[j]=11', 'arr[]=', [-12, -9, 7, 10, 11, 13, 8])
('i=3', ' j=5', 'min=10', 'arr[i]=10', 'arr[j]=13', 'arr[]=', [-12, -9, 7, 10, 11, 13, 8])
('i=3', ' j=6', 'min=8', 'arr[i]=10', 'arr[j]=8', 'arr[]=', [-12, -9, 7, 10, 11, 13, 8])
('i=4', ' j=5', 'min=11', 'arr[i]=11', 'arr[j]=13', 'arr[]=', [-12, -9, 7, 8, 11, 13, 10])
('i=4', ' j=6', 'min=10', 'arr[i]=11', 'arr[j]=10', 'arr[]=', [-12, -9, 7, 8, 11, 13, 10])
('i=5', ' j=6', 'min=11', 'arr[i]=13', 'arr[j]=11', 'arr[]=', [-12, -9, 7, 8, 10, 13, 11])
('arr1 sorted:', [-12, -9, 7, 8, 10, 11, 13])
time:0.305891036987 ms

orgin arr2:
[7, 11, -9, 10, -12, 13, 8]
('i=0', ' j=2', 'min=-9', 'arr[i]=7', 'arr[j]=-9', 'arr[]=', [7, 11, -9, 10, -12, 13, 8])
('i=0', ' j=4', 'min=-12', 'arr[i]=7', 'arr[j]=-12', 'arr[]=', [7, 11, -9, 10, -12, 13, 8])
('i=0', ' j=2', 'min=-9', 'arr[i]=7', 'arr[j]=-9', 'arr[]=', [7, 11, -9, 10, 13, 8])
('i=0', ' j=1', 'min=10', 'arr[i]=11', 'arr[j]=10', 'arr[]=', [11, 10, 13, 8])
('i=0', ' j=3', 'min=8', 'arr[i]=11', 'arr[j]=8', 'arr[]=', [11, 10, 13, 8])
('i=0', ' j=1', 'min=10', 'arr[i]=11', 'arr[j]=10', 'arr[]=', [11, 10, 13])
('arr2 sorted:', [-12, -9, 7, 8, 10, 11, 13])
time:0.0650882720947 ms
"""