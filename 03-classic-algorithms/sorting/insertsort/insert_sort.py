#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time

'''
# 插入排序标准通用版
'''
def insert_sort1(arr):
    l = len(arr)
    for i in range(l):
        j = i - 1
        current = arr[i]
        # 将该项自右往左与已排序项逐个对比，当遇到比自己大的项时，将该位置右移
        # 直到遇到小于等于自己的项则停止移动，表示插入成功
        print('i=' + str(i), ' j=' + str(j), 'current=' + str(current),
              'arr[i]=' + str(arr[i]), 'arr[j]=' + str(arr[j]), 'arr[]=', arr)
        while (j >= 0 and current < arr[j]):
            # 逐个位移
            arr[j + 1] = arr[j]
            j -= 1
        # 交换为当前项
        arr[j + 1] = current
    return arr

'''
# 插入排序利用list insert函数插入选择项
'''
def insert_sort2(arr):
    l = len(arr)
    is_min = False
    for i in range(l):
        j = i - 1
        current = arr[i]
        print('current:', current)
        is_min = True
        print('i=' + str(i), ' j=' + str(j), 'current=' + str(current),
              'arr[i]=' + str(arr[i]), 'arr[j]=' + str(arr[j]), 'arr[]=', arr)
        while j >= 0:
            if (current > arr[j]):
                # 利用insert插入
                arr.insert(j + 1, current)
                is_min = False
                break
            j -= 1
        if (is_min):
            arr.insert(0, current)
        arr.pop(i)
    return arr

'''
# 插入排序利用list insert函数插入最大项
'''
def insert_sort3(arr):
    l = len(arr)
    new_arr = [arr[0]]
    for i in range(1, l):
        isMax = True
        for j in range(len(new_arr)):
            print('i=' + str(i), ' j=' + str(j), 'arr[i]=' + str(arr[i]),
                  'new_arr[j]=' + str(new_arr[j]), 'new_arr[]=', new_arr)
            if arr[i] < new_arr[j]:
                # 新建数组来插入到某个位置中
                new_arr.insert(j, arr[i])
                isMax = False
                break
        if (isMax == True):
            new_arr.append(arr[i])
    print('new_arr:', new_arr)
    return new_arr


'''
# 插入排序新建数组版倒序遍历
'''
def insert_sort4(arr):
    l = len(arr)
    new_arr = [arr[0]]
    for i in range(1, l):
        is_min = True
        new_len = len(new_arr)
        while (new_len > 0):
            new_len -= 1
            print('i=' + str(i), ' new_len=' + str(new_len),
                  'arr[i]=' + str(arr[i]),
                  'new_arr[new_len]=' + str(new_arr[new_len]), 'new_arr[]=', new_arr)
            if arr[i] > new_arr[new_len]:
                new_arr.insert(new_len + 1, arr[i])
                is_min = False
                break
        if is_min == True:
            new_arr.insert(0, arr[i])
    print('new_arr:', new_arr)
    return new_arr


# test
arr1 = [7, 11, 9, 10, 12, 13, 8]
start_time = time.time()
print(insert_sort1(arr1))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

arr2 = [7, 11, 9, 10, 12, 13, 8]
start_time = time.time()
print(insert_sort2(arr2))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

arr3 = [7, 11, 9, 10, 12, 13, 8]
start_time = time.time()
print(insert_sort3(arr3))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

arr4 = [7, 11, 9, 10, 12, 13, 8]
start_time = time.time()
print(insert_sort4(arr4))
print("time:" + str((time.time() - start_time) * 1000) + " ms")
"""
jarrys-MacBook-Pro:insert_sort jarry$ python insert_sort.py
('i=0', ' j=-1', 'current=7', 'arr[i]=7', 'arr[j]=8', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=1', ' j=0', 'current=11', 'arr[i]=11', 'arr[j]=7', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=2', ' j=1', 'current=9', 'arr[i]=9', 'arr[j]=11', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('i=3', ' j=2', 'current=10', 'arr[i]=10', 'arr[j]=11', 'arr[]=', [7, 9, 11, 10, 12, 13, 8])
('i=4', ' j=3', 'current=12', 'arr[i]=12', 'arr[j]=11', 'arr[]=', [7, 9, 10, 11, 12, 13, 8])
('i=5', ' j=4', 'current=13', 'arr[i]=13', 'arr[j]=12', 'arr[]=', [7, 9, 10, 11, 12, 13, 8])
('i=6', ' j=5', 'current=8', 'arr[i]=8', 'arr[j]=13', 'arr[]=', [7, 9, 10, 11, 12, 13, 8])
[7, 8, 9, 10, 11, 12, 13]
time:0.168800354004 ms
('current:', 7)
('i=0', ' j=-1', 'current=7', 'arr[i]=7', 'arr[j]=8', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('current:', 11)
('i=1', ' j=0', 'current=11', 'arr[i]=11', 'arr[j]=7', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('current:', 9)
('i=2', ' j=1', 'current=9', 'arr[i]=9', 'arr[j]=11', 'arr[]=', [7, 11, 9, 10, 12, 13, 8])
('current:', 10)
('i=3', ' j=2', 'current=10', 'arr[i]=10', 'arr[j]=9', 'arr[]=', [7, 9, 9, 10, 12, 13, 8])
('current:', 12)
('i=4', ' j=3', 'current=12', 'arr[i]=12', 'arr[j]=10', 'arr[]=', [7, 9, 9, 10, 12, 13, 8])
('current:', 13)
('i=5', ' j=4', 'current=13', 'arr[i]=13', 'arr[j]=12', 'arr[]=', [7, 9, 9, 10, 12, 13, 8])
('current:', 8)
('i=6', ' j=5', 'current=8', 'arr[i]=8', 'arr[j]=13', 'arr[]=', [7, 9, 9, 10, 12, 13, 8])
[7, 8, 9, 9, 10, 12, 8]
time:0.189781188965 ms
('i=1', ' j=0', 'arr[i]=11', 'new_arr[j]=7', 'new_arr[]=', [7])
('i=2', ' j=0', 'arr[i]=9', 'new_arr[j]=7', 'new_arr[]=', [7, 11])
('i=2', ' j=1', 'arr[i]=9', 'new_arr[j]=11', 'new_arr[]=', [7, 11])
('i=3', ' j=0', 'arr[i]=10', 'new_arr[j]=7', 'new_arr[]=', [7, 9, 11])
('i=3', ' j=1', 'arr[i]=10', 'new_arr[j]=9', 'new_arr[]=', [7, 9, 11])
('i=3', ' j=2', 'arr[i]=10', 'new_arr[j]=11', 'new_arr[]=', [7, 9, 11])
('i=4', ' j=0', 'arr[i]=12', 'new_arr[j]=7', 'new_arr[]=', [7, 9, 10, 11])
('i=4', ' j=1', 'arr[i]=12', 'new_arr[j]=9', 'new_arr[]=', [7, 9, 10, 11])
('i=4', ' j=2', 'arr[i]=12', 'new_arr[j]=10', 'new_arr[]=', [7, 9, 10, 11])
('i=4', ' j=3', 'arr[i]=12', 'new_arr[j]=11', 'new_arr[]=', [7, 9, 10, 11])
('i=5', ' j=0', 'arr[i]=13', 'new_arr[j]=7', 'new_arr[]=', [7, 9, 10, 11, 12])
('i=5', ' j=1', 'arr[i]=13', 'new_arr[j]=9', 'new_arr[]=', [7, 9, 10, 11, 12])
('i=5', ' j=2', 'arr[i]=13', 'new_arr[j]=10', 'new_arr[]=', [7, 9, 10, 11, 12])
('i=5', ' j=3', 'arr[i]=13', 'new_arr[j]=11', 'new_arr[]=', [7, 9, 10, 11, 12])
('i=5', ' j=4', 'arr[i]=13', 'new_arr[j]=12', 'new_arr[]=', [7, 9, 10, 11, 12])
('i=6', ' j=0', 'arr[i]=8', 'new_arr[j]=7', 'new_arr[]=', [7, 9, 10, 11, 12, 13])
('i=6', ' j=1', 'arr[i]=8', 'new_arr[j]=9', 'new_arr[]=', [7, 9, 10, 11, 12, 13])
('new_arr:', [7, 8, 9, 10, 11, 12, 13])
[7, 8, 9, 10, 11, 12, 13]
time:0.335931777954 ms
('i=1', ' new_len=0', 'arr[i]=11', 'new_arr[new_len]=7', 'new_arr[]=', [7])
('i=2', ' new_len=1', 'arr[i]=9', 'new_arr[new_len]=11', 'new_arr[]=', [7, 11])
('i=2', ' new_len=0', 'arr[i]=9', 'new_arr[new_len]=7', 'new_arr[]=', [7, 11])
('i=3', ' new_len=2', 'arr[i]=10', 'new_arr[new_len]=11', 'new_arr[]=', [7, 9, 11])
('i=3', ' new_len=1', 'arr[i]=10', 'new_arr[new_len]=9', 'new_arr[]=', [7, 9, 11])
('i=4', ' new_len=3', 'arr[i]=12', 'new_arr[new_len]=11', 'new_arr[]=', [7, 9, 10, 11])
('i=5', ' new_len=4', 'arr[i]=13', 'new_arr[new_len]=12', 'new_arr[]=', [7, 9, 10, 11, 12])
('i=6', ' new_len=5', 'arr[i]=8', 'new_arr[new_len]=13', 'new_arr[]=', [7, 9, 10, 11, 12, 13])
('i=6', ' new_len=4', 'arr[i]=8', 'new_arr[new_len]=12', 'new_arr[]=', [7, 9, 10, 11, 12, 13])
('i=6', ' new_len=3', 'arr[i]=8', 'new_arr[new_len]=11', 'new_arr[]=', [7, 9, 10, 11, 12, 13])
('i=6', ' new_len=2', 'arr[i]=8', 'new_arr[new_len]=10', 'new_arr[]=', [7, 9, 10, 11, 12, 13])
('i=6', ' new_len=1', 'arr[i]=8', 'new_arr[new_len]=9', 'new_arr[]=', [7, 9, 10, 11, 12, 13])
('i=6', ' new_len=0', 'arr[i]=8', 'new_arr[new_len]=7', 'new_arr[]=', [7, 9, 10, 11, 12, 13])
('new_arr:', [7, 8, 9, 10, 11, 12, 13])
[7, 8, 9, 10, 11, 12, 13]
time:0.219106674194 ms
"""