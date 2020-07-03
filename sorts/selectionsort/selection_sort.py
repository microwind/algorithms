#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time


def selection_sort(arr):
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
def selection_sort1(arr):
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
arr = [7, 11, 9, 10, 12, 13, 8]
start_time = time.time()
print(selection_sort(arr))
print("time:" + str((time.time() - start_time) * 1000) + " ms")
"""
jarrys-MacBook-Pro:selection_sort jarry$ python selection_sort.py 
('i=0', ' j=1', 'min=7', 'arr[i]=7', 'arr[j]=11', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=0', ' j=2', 'min=7', 'arr[i]=7', 'arr[j]=9', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=0', ' j=3', 'min=7', 'arr[i]=7', 'arr[j]=10', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=0', ' j=4', 'min=7', 'arr[i]=7', 'arr[j]=12', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=0', ' j=5', 'min=7', 'arr[i]=7', 'arr[j]=13', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=0', ' j=6', 'min=7', 'arr[i]=7', 'arr[j]=8', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=1', ' j=2', 'min=9', 'arr[i]=11', 'arr[j]=9', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=1', ' j=3', 'min=9', 'arr[i]=11', 'arr[j]=10', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=1', ' j=4', 'min=9', 'arr[i]=11', 'arr[j]=12', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=1', ' j=5', 'min=9', 'arr[i]=11', 'arr[j]=13', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=1', ' j=6', 'min=8', 'arr[i]=11', 'arr[j]=8', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=2', ' j=3', 'min=9', 'arr[i]=9', 'arr[j]=10', 'arr[]=', [7, 8, 9, 10, 12, 13, 11])
('i=2', ' j=4', 'min=9', 'arr[i]=9', 'arr[j]=12', 'arr[]=', [7, 8, 9, 10, 12, 13, 11])
('i=2', ' j=5', 'min=9', 'arr[i]=9', 'arr[j]=13', 'arr[]=', [7, 8, 9, 10, 12, 13, 11])
('i=2', ' j=6', 'min=9', 'arr[i]=9', 'arr[j]=11', 'arr[]=', [7, 8, 9, 10, 12, 13, 11])
('i=3', ' j=4', 'min=10', 'arr[i]=10', 'arr[j]=12', 'arr[]=', [7, 8, 9, 10, 12, 13, 11])
('i=3', ' j=5', 'min=10', 'arr[i]=10', 'arr[j]=13', 'arr[]=', [7, 8, 9, 10, 12, 13, 11])
('i=3', ' j=6', 'min=10', 'arr[i]=10', 'arr[j]=11', 'arr[]=', [7, 8, 9, 10, 12, 13, 11])
('i=4', ' j=5', 'min=12', 'arr[i]=12', 'arr[j]=13', 'arr[]=', [7, 8, 9, 10, 12, 13, 11])
('i=4', ' j=6', 'min=11', 'arr[i]=12', 'arr[j]=11', 'arr[]=', [7, 8, 9, 10, 12, 13, 11])
('i=5', ' j=6', 'min=12', 'arr[i]=13', 'arr[j]=12', 'arr[]=', [7, 8, 9, 10, 11, 13, 12])
[7, 8, 9, 10, 11, 12, 13]
time:0.281095504761 ms
"""