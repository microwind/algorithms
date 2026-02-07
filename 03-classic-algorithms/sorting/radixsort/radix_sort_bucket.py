#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time
"""
基数排序LSD版，本基于桶排序。
1. 找出数组中最大的数，确定其位数。
2. LSD是低位到高位，依次按照位数的值将数字放入到不同桶中。
3. 按照桶顺序重新给数组排序。
重复步骤2和3，直到排序完成。
"""
def radix_sort(arr):
    max_value = max(arr)  # 找出数组中最大的数
    min_value = min(arr)  #最小值，为了支持负数
    digit = 1  # 从个位开始排序

    # 每次排序一个数位，从低到高直到排序完成
    while (max_value - min_value) // digit > 0:
        # 创建10个桶，分别对应0-9的数位值
        buckets = [[] for _ in range(10)]
        for num in arr:
            # 找出当前位数的值
            digit_num = (num - min_value) // digit % 10
            # 将数字添加到对应数位的桶中，相当于根据数位排序
            buckets[digit_num].append(num)

        print('buckets:', buckets)

        # 通过exend展开数组，相当于逐层添加
        arr = []
        for bucket in buckets:
            arr.extend(bucket)
            # 或逐项添加
            # for item in bucket:
            #     arr.append(item)

        # 数位移动到下一位
        digit *= 10

    return arr


if __name__ == '__main__':

    # 1. radix_sort1
    arr = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
    print("\r\n Source arr1:")
    print(arr)
    start_time = time.time()
    arr = radix_sort(arr)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("arr1 sorted: ", arr)

    # 2. radix_sort2
    arr2 = [39, 128, 122, 234, 108, 7, 15, -125, 204]
    print("\r\n Source arr2:")
    print(arr2)
    start_time = time.time()
    arr2 = radix_sort(arr2)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("arr2 sorted: ", arr2)
"""
jarry@jarrys-MacBook-Pro radixsort % python radix_sort_bucket.py

 Source arr1:
[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
('buckets:', [[-4, -323454], [7], [], [], [10, 200], [87431], [], [33, 43], [], [15, 1235]])
('buckets:', [[-323454], [], [], [], [], [-4, 200], [7, 10, 15], [], [87431, 33, 1235], [43]])
('buckets:', [[-323454], [], [], [], [-4, 7, 10, 15, 33, 43], [], [200, 1235], [], [87431], []])
('buckets:', [[-323454, 87431], [], [], [-4, 7, 10, 15, 33, 43, 200], [1235], [], [], [], [], []])
('buckets:', [[-323454], [87431], [-4, 7, 10, 15, 33, 43, 200, 1235], [], [], [], [], [], [], []])
('buckets:', [[-323454], [], [], [-4, 7, 10, 15, 33, 43, 200, 1235], [87431], [], [], [], [], []])
time:0.123023986816 ms
('arr1 sorted: ', [-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431])

 Source arr2:
[39, 128, 122, 234, 108, 7, 15, -125, 204]
('buckets:', [[15, -125], [], [7], [128, 108], [39], [], [], [122], [], [234, 204]])
('buckets:', [[-125], [], [204], [7, 108], [15, 122], [128, 234], [39], [], [], []])
('buckets:', [[-125], [7, 15, 39], [108, 122, 128], [204, 234], [], [], [], [], [], []])
time:0.0560283660889 ms
('arr2 sorted: ', [-125, 7, 15, 39, 108, 122, 128, 204, 234])
"""