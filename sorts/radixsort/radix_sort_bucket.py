#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time

"""
基数排序算法的思想是先按照数位的值将数字分组，然后按照分组的顺序进行排序。具体步骤如下：
找出数组中最大的数，确定其位数。
从个位开始，依次按照位数的值将数字分组，可以使用桶或计数排序等算法来实现。
将每一位分组后得到的数组按照分组顺序进行合并，得到一个新的数组。
重复步骤2和3，直到按照最高位排序完成。
"""

def radix_sort(arr):
    max_value = max(arr)  # 找出数组中最大的数
    min_value = min(arr) #最小值，为了支持负数
    digit = 1  # 从个位开始排序

    # 每次排序一位，直到按照最高位排序完成
    while (max_value - min_value) // digit > 0:
        # 创建10个桶，分别对应0-9的数位值
        buckets = [[] for _ in range(10)]
        for num in arr:
            # 找出当前位数的值
            digit_num = (num - min_value) // digit % 10
            # 将数字添加到对应数位的桶中，相当于根据数位排序
            buckets[digit_num].append(num)
        
        # 通过exend展开数组，得到新的排序
        arr = []
        for bucket in buckets:
            arr.extend(bucket)

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
    print("radix_sort sorted: ", arr)

"""
jarry@jarrys-MacBook-Pro radixsort % python radix_sort_bucket.py

 Source arr1:
[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
time:0.046968460083 ms
('radix_sort sorted: ', [-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431])
"""