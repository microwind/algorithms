#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time

'''
# 1. 桶排序代码简版，负数全放在第1桶
'''
def bucket_sort1(arr):
    max_value = max(arr)
    min_value = min(arr)
    min_value = 1 if min_value <= 0 else min_value
    # 设置桶的数量，可以任意设置，也可以根据最大、最小值来设置
    bucket_number = int(max_value - min_value) / min_value + 1
    bucket_number = len(arr) / 2 if bucket_number > len(arr) else bucket_number
    bucket_size = int(max_value - min_value) / bucket_number + 1
    # 设置list并填充默认值
    buckets = [None for i in range(min_value, max_value + 1)]
    for item in arr:
        # 当前项除以桶间距取整，决定应该放在某个桶内
        idx = int((item - min_value) / bucket_size)
        # 如果是负数就放在第一桶里面
        # print('bucket_number', bucket_number, 'bucket_size=', bucket_size, 'idx=', idx)
        idx = 0 if idx < 0 else idx
        if buckets[idx] == None:
            buckets[idx] = []
            buckets[idx].append(item)
        else:
            l = len(buckets[idx]) - 1
            while l >= 0:
                # 自后往前遍历，如果数字大于数组中的项则插入其后
                if item > buckets[idx][l]:
                    buckets[idx].insert(l + 1, item)
                    break
                    # 如果数字最小则插入到最前
                elif l == 0:
                    buckets[idx].insert(0, item)
                l -= 1

        # 按照下标和顺序取出桶内的数字，回填到一个数组中
    output = []
    for i in range(len(buckets)):
        if buckets[i]:
            output = output + buckets[i]
    return output

'''
# 2. 桶排序标准版，负数单独排序处理
'''
def bucket_sort2(arr):
    max_value = arr[0]
    min_value = arr[0]
    # 得到最大与最小值
    for item in arr:
        if item > max_value:
            max_value = item
        if item < min_value:
            min_value = item
    min_value = 1 if min_value <= 0 else min_value

    # 设置桶的数量，可以任意设置，也可以根据最大、最小值来设置
    bucket_number = int(max_value - min_value) / min_value + 1
    # bucket_number = len(arr) / 2 if bucket_number > len(arr) / 2 else bucket_number
    # 预设桶列表与桶下标
    buckets = [None for i in range(min_value, max_value + 1)]
    # 支持小数，如果要支持负数，则需要将负数下标单独存取
    negative_list = []

    for item in arr:
        # 排序数字除以桶数得到下标，以此来决定分配到哪个桶里面
        idx = int((item - min_value) // bucket_number)
        # print('bucket_number', bucket_number, 'idx=', idx)

        # 如果要支持负数则需要添加到负数下标列表中去，单独处理循环
        if idx < 0:
            # 负数单独排序或者把负数全部放入第一个桶中
            negative_list.append(item)
            continue

        # 每个桶都是一个数组，若不存在则创建并放入数字
        if isinstance(buckets[idx], list) != True:
            buckets[idx] = []
            buckets[idx].append(item)
        else:
            # 这里使用占位挪动插入，如果桶内已有数字，先在后面添加占位，然后按照顺序逐个挪动，
            l = len(buckets[idx]) - 1
            buckets[idx].append(None)
            while l >= 0:
                if (item < buckets[idx][l]):
                    # 如果插入的数字小于当前项，则将当前项逐个往后挪
                    buckets[idx][l + 1] = buckets[idx][l]
                    # 如果最小则放在首位
                    if l == 0:
                        buckets[idx][0] = item
                else:
                    # 如果大于等于当前项，则插入到当前项后面，循环中止
                    buckets[idx][l + 1] = item
                    break
                l -= 1

    # 按照下标和顺序取出桶内的数字，回填到数组中
    output = []
    # 先将负数下标排序，然后根据顺序逐个按属性取出
    negative_list.sort()
    for item in negative_list:
        output.append(item)

    # 把数组内容取出
    for bucket_item in buckets:
        if (bucket_item is not None):
            j = 0
            bucket_item_len = len(bucket_item)
            while j < bucket_item_len:
                output.append(bucket_item[j])
                j += 1
    return output

'''
# 1. 桶排序，利用sorted函数
'''
def bucket_sort3(arr):
    buckets = []
    max_value = max(arr)
    min_value = min(arr)
    min_value = 1 if min_value <= 0 else min_value
    bucket_number = int(max_value - min_value) / min_value + 1

    # Create empty buckets
    for i in range(bucket_number):
        buckets.append([])

    # Insert elements into their respective buckets
    for item in arr:
        idx = int((item - min_value) / bucket_number)
        # print('idx:', idx, item, min_value, bucket_number)
        if idx < 0:
            idx = 0
        buckets[idx].append(item)

    # Sort the elements of each bucket
    for i in range(len(arr)):
        buckets[i] = sorted(buckets[i])

    # Get the sorted elements
    idx = 0
    for item in buckets:
        for number in item:
            arr[idx] = number
            idx += 1
    return arr


# test
arr1 = [20, 11, 9, 5, 30, 30, 15, 13, 80, 30]
arr2 = [3, 4.3, 15, -2.1, -2, -2.1, 2, 3.2, 0, 3, -7, 100]
print('origin arr1:', arr1)
print('origin arr2:', arr2)

start_time = time.time()
print('bucket_sort1.1 sorted:', bucket_sort1(arr1))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

start_time = time.time()
print('bucket_sort1.2 sorted:', bucket_sort1(arr2))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

print('\r\n')

start_time = time.time()
print('bucket_sort2.1 sorted:', bucket_sort2(arr1))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

start_time = time.time()
print('bucket_sort2.2 sorted:', bucket_sort2(arr2))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

print('\r\n')

start_time = time.time()
print('bucket_sort3.1 sorted:', bucket_sort3(arr1))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

start_time = time.time()
print('bucket_sort3.2 sorted:', bucket_sort3(arr2))
print("time:" + str((time.time() - start_time) * 1000) + " ms")
"""
jarry@jarrys-MacBook-Pro bucketsort % python bucket_sort.py
('origin arr1:', [20, 11, 9, 5, 30, 30, 15, 13, 80, 30])
('origin arr2:', [3, 4.3, 15, -2.1, -2, -2.1, 2, 3.2, 0, 3, -7, 100])
('bucket_number', 5, 'bucket_size=', 16, 'idx=', 0)
('bucket_number', 5, 'bucket_size=', 16, 'idx=', 0)
('bucket_number', 5, 'bucket_size=', 16, 'idx=', 0)
('bucket_number', 5, 'bucket_size=', 16, 'idx=', 0)
('bucket_number', 5, 'bucket_size=', 16, 'idx=', 1)
('bucket_number', 5, 'bucket_size=', 16, 'idx=', 1)
('bucket_number', 5, 'bucket_size=', 16, 'idx=', 0)
('bucket_number', 5, 'bucket_size=', 16, 'idx=', 0)
('bucket_number', 5, 'bucket_size=', 16, 'idx=', 4)
('bucket_number', 5, 'bucket_size=', 16, 'idx=', 1)
('bucket_sort1.1 sorted:', [5, 9, 11, 13, 15, 20, 30, 30, 30, 80])
time:0.0860691070557 ms
('bucket_number', 6, 'bucket_size=', 17, 'idx=', 0)
('bucket_number', 6, 'bucket_size=', 17, 'idx=', 0)
('bucket_number', 6, 'bucket_size=', 17, 'idx=', 0)
('bucket_number', 6, 'bucket_size=', 17, 'idx=', 0)
('bucket_number', 6, 'bucket_size=', 17, 'idx=', -1)
('bucket_number', 6, 'bucket_size=', 17, 'idx=', 0)
('bucket_number', 6, 'bucket_size=', 17, 'idx=', 0)
('bucket_number', 6, 'bucket_size=', 17, 'idx=', 0)
('bucket_number', 6, 'bucket_size=', 17, 'idx=', -1)
('bucket_number', 6, 'bucket_size=', 17, 'idx=', 0)
('bucket_number', 6, 'bucket_size=', 17, 'idx=', -1)
('bucket_number', 6, 'bucket_size=', 17, 'idx=', 5)
('bucket_sort1.2 sorted:', [-7, -2.1, -2.1, -2, 0, 2, 3, 3, 3.2, 4.3, 15, 100])
time:0.0951290130615 ms


('bucket_sort2.1 sorted:', [5, 9, 11, 13, 15, 20, 30, 30, 30, 80])
time:0.0319480895996 ms
('bucket_sort2.2 sorted:', [-7, -2.1, -2.1, -2, 0, 2, 3, 3, 3.2, 4.3, 15, 100])
time:0.0410079956055 ms


('bucket_sort3.1 sorted:', [5, 9, 11, 13, 15, 20, 30, 30, 30, 80])
time:0.0250339508057 ms
('bucket_sort3.2 sorted:', [-7, -2.1, -2.1, -2, 0, 2, 3, 3, 3.2, 4.3, 15, 100])
time:0.124931335449 ms
"""