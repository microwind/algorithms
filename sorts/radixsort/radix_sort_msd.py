#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https:#github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time
import math
"""
基数排序，从高到低逐位排序，递归方式，基于桶排序。具体步骤如下：
1. 找出数组中最大的数，确定其位数。
2. MSD是从高位开始，依次按照位数的值将数字放入到不同桶中。
3. 如果桶里的长度超过1，则通过递归继续按桶排序。当桶里的数据只有1位时添加到原列表对应位置。
重复步骤2和3，直到按照最高位排序完成。
"""


# 基数排序，从高到低逐位排序，基于桶排序
def bucket_sort(arr, exponent):
    print('origin arr:', arr, 'exponent:', exponent)
    if (len(arr) <= 1 or exponent <= 0):
        return arr

    min_value = min(arr)

    radix = 10
    amount = 10

    print('prepared arr:', arr, 'exponent:', exponent)
    # 构建排序的桶二维列表
    buckets = [None] * radix

    for i in range(len(arr)):
        item = arr[i] - min_value
        # 根据数位上的值，把数据追加到对应的桶里，减去min是支持负数
        bucketIdx = int(item / exponent) % radix
        # 填充空桶，或者提前填充为列表
        if buckets[bucketIdx] is None:
            buckets[bucketIdx] = []
        buckets[bucketIdx].append(arr[i])

    print('append to buckets:', buckets)

    # 将每个桶的数据按顺序逐个取出，重新赋值给原数组
    sortedIdx = 0
    for i in range(radix):
        bucket = buckets[i]
        if bucket is None or len(bucket) < 1:
            continue
        # 如果是数组则继续递归调用，位数降低1位
        sortedBucket = bucket_sort(bucket, exponent // amount)
        # 把各个桶里的值按顺序赋给原数组
        for num in sortedBucket:
            print ('sortedIdx::', sortedIdx)
            arr[sortedIdx] = num
            print('bucket:', bucket, 'sortedBucket:', sortedBucket,
                  'sortedIdx:', sortedIdx, 'set arr:', arr)
            sortedIdx += 1

    print('exponent:', exponent, 'sorted arr:', arr)

    return arr


def radix_sort_msd(arr):
    # 根据最大值，逐个按进位(基数)来应用排序，从高位到低位。
    # 获取数字的数位，这减去min_value是为了支持负数
    # exponent是最大的数位，由高到低逐位计算
    max_value = max(arr)
    min_value = min(arr)
    numberOfDigits = int(math.log10(max_value - min_value) + 1)
    exponent = math.pow(10, numberOfDigits - 1)
    return bucket_sort(arr, int(exponent))


if __name__ == '__main__':

    # 1. radix_sort1
    arr = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
    print("\r\n Source arr1:")
    print(arr)
    start_time = time.time()
    arr = radix_sort_msd(arr)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("radix_sort sorted: ", arr)

"""
jarry@jarrys-MacBook-Pro radixsort % python radix_sort_msd.py

 Source arr1:
[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
('origin arr:', [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431], 'exponent:', 100000)
('prepared arr:', [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431], 'exponent:', 100000)
('append to buckets:', [[-323454], None, None, [33, -4, 15, 43, 7, 10, 1235, 200], [87431], None, None, None, None, None])
('origin arr:', [-323454], 'exponent:', 10000)
('sortedIdx::', 0)
('bucket:', [-323454], 'sortedBucket:', [-323454], 'sortedIdx:', 0, 'set arr:', [-323454, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431])
('origin arr:', [33, -4, 15, 43, 7, 10, 1235, 200], 'exponent:', 10000)
('prepared arr:', [33, -4, 15, 43, 7, 10, 1235, 200], 'exponent:', 10000)
('append to buckets:', [[33, -4, 15, 43, 7, 10, 1235, 200], None, None, None, None, None, None, None, None, None])
('origin arr:', [33, -4, 15, 43, 7, 10, 1235, 200], 'exponent:', 1000)
('prepared arr:', [33, -4, 15, 43, 7, 10, 1235, 200], 'exponent:', 1000)
('append to buckets:', [[33, -4, 15, 43, 7, 10, 200], [1235], None, None, None, None, None, None, None, None])
('origin arr:', [33, -4, 15, 43, 7, 10, 200], 'exponent:', 100)
('prepared arr:', [33, -4, 15, 43, 7, 10, 200], 'exponent:', 100)
('append to buckets:', [[33, -4, 15, 43, 7, 10], None, [200], None, None, None, None, None, None, None])
('origin arr:', [33, -4, 15, 43, 7, 10], 'exponent:', 10)
('prepared arr:', [33, -4, 15, 43, 7, 10], 'exponent:', 10)
('append to buckets:', [[-4], [15, 7, 10], None, [33], [43], None, None, None, None, None])
('origin arr:', [-4], 'exponent:', 1)
('sortedIdx::', 0)
('bucket:', [-4], 'sortedBucket:', [-4], 'sortedIdx:', 0, 'set arr:', [-4, -4, 15, 43, 7, 10])
('origin arr:', [15, 7, 10], 'exponent:', 1)
('prepared arr:', [15, 7, 10], 'exponent:', 1)
('append to buckets:', [[7], None, None, [10], None, None, None, None, [15], None])
('origin arr:', [7], 'exponent:', 0)
('sortedIdx::', 0)
('bucket:', [7], 'sortedBucket:', [7], 'sortedIdx:', 0, 'set arr:', [7, 7, 10])
('origin arr:', [10], 'exponent:', 0)
('sortedIdx::', 1)
('bucket:', [10], 'sortedBucket:', [10], 'sortedIdx:', 1, 'set arr:', [7, 10, 10])
('origin arr:', [15], 'exponent:', 0)
('sortedIdx::', 2)
('bucket:', [15], 'sortedBucket:', [15], 'sortedIdx:', 2, 'set arr:', [7, 10, 15])
('exponent:', 1, 'sorted arr:', [7, 10, 15])
('sortedIdx::', 1)
('bucket:', [7, 10, 15], 'sortedBucket:', [7, 10, 15], 'sortedIdx:', 1, 'set arr:', [-4, 7, 15, 43, 7, 10])
('sortedIdx::', 2)
('bucket:', [7, 10, 15], 'sortedBucket:', [7, 10, 15], 'sortedIdx:', 2, 'set arr:', [-4, 7, 10, 43, 7, 10])
('sortedIdx::', 3)
('bucket:', [7, 10, 15], 'sortedBucket:', [7, 10, 15], 'sortedIdx:', 3, 'set arr:', [-4, 7, 10, 15, 7, 10])
('origin arr:', [33], 'exponent:', 1)
('sortedIdx::', 4)
('bucket:', [33], 'sortedBucket:', [33], 'sortedIdx:', 4, 'set arr:', [-4, 7, 10, 15, 33, 10])
('origin arr:', [43], 'exponent:', 1)
('sortedIdx::', 5)
('bucket:', [43], 'sortedBucket:', [43], 'sortedIdx:', 5, 'set arr:', [-4, 7, 10, 15, 33, 43])
('exponent:', 10, 'sorted arr:', [-4, 7, 10, 15, 33, 43])
('sortedIdx::', 0)
('bucket:', [-4, 7, 10, 15, 33, 43], 'sortedBucket:', [-4, 7, 10, 15, 33, 43], 'sortedIdx:', 0, 'set arr:', [-4, -4, 15, 43, 7, 10, 200])
('sortedIdx::', 1)
('bucket:', [-4, 7, 10, 15, 33, 43], 'sortedBucket:', [-4, 7, 10, 15, 33, 43], 'sortedIdx:', 1, 'set arr:', [-4, 7, 15, 43, 7, 10, 200])
('sortedIdx::', 2)
('bucket:', [-4, 7, 10, 15, 33, 43], 'sortedBucket:', [-4, 7, 10, 15, 33, 43], 'sortedIdx:', 2, 'set arr:', [-4, 7, 10, 43, 7, 10, 200])
('sortedIdx::', 3)
('bucket:', [-4, 7, 10, 15, 33, 43], 'sortedBucket:', [-4, 7, 10, 15, 33, 43], 'sortedIdx:', 3, 'set arr:', [-4, 7, 10, 15, 7, 10, 200])
('sortedIdx::', 4)
('bucket:', [-4, 7, 10, 15, 33, 43], 'sortedBucket:', [-4, 7, 10, 15, 33, 43], 'sortedIdx:', 4, 'set arr:', [-4, 7, 10, 15, 33, 10, 200])
('sortedIdx::', 5)
('bucket:', [-4, 7, 10, 15, 33, 43], 'sortedBucket:', [-4, 7, 10, 15, 33, 43], 'sortedIdx:', 5, 'set arr:', [-4, 7, 10, 15, 33, 43, 200])
('origin arr:', [200], 'exponent:', 10)
('sortedIdx::', 6)
('bucket:', [200], 'sortedBucket:', [200], 'sortedIdx:', 6, 'set arr:', [-4, 7, 10, 15, 33, 43, 200])
('exponent:', 100, 'sorted arr:', [-4, 7, 10, 15, 33, 43, 200])
('sortedIdx::', 0)
('bucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedIdx:', 0, 'set arr:', [-4, -4, 15, 43, 7, 10, 1235, 200])
('sortedIdx::', 1)
('bucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedIdx:', 1, 'set arr:', [-4, 7, 15, 43, 7, 10, 1235, 200])
('sortedIdx::', 2)
('bucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedIdx:', 2, 'set arr:', [-4, 7, 10, 43, 7, 10, 1235, 200])
('sortedIdx::', 3)
('bucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedIdx:', 3, 'set arr:', [-4, 7, 10, 15, 7, 10, 1235, 200])
('sortedIdx::', 4)
('bucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedIdx:', 4, 'set arr:', [-4, 7, 10, 15, 33, 10, 1235, 200])
('sortedIdx::', 5)
('bucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedIdx:', 5, 'set arr:', [-4, 7, 10, 15, 33, 43, 1235, 200])
('sortedIdx::', 6)
('bucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200], 'sortedIdx:', 6, 'set arr:', [-4, 7, 10, 15, 33, 43, 200, 200])
('origin arr:', [1235], 'exponent:', 100)
('sortedIdx::', 7)
('bucket:', [1235], 'sortedBucket:', [1235], 'sortedIdx:', 7, 'set arr:', [-4, 7, 10, 15, 33, 43, 200, 1235])
('exponent:', 1000, 'sorted arr:', [-4, 7, 10, 15, 33, 43, 200, 1235])
('sortedIdx::', 0)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 0, 'set arr:', [-4, -4, 15, 43, 7, 10, 1235, 200])
('sortedIdx::', 1)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 1, 'set arr:', [-4, 7, 15, 43, 7, 10, 1235, 200])
('sortedIdx::', 2)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 2, 'set arr:', [-4, 7, 10, 43, 7, 10, 1235, 200])
('sortedIdx::', 3)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 3, 'set arr:', [-4, 7, 10, 15, 7, 10, 1235, 200])
('sortedIdx::', 4)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 4, 'set arr:', [-4, 7, 10, 15, 33, 10, 1235, 200])
('sortedIdx::', 5)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 5, 'set arr:', [-4, 7, 10, 15, 33, 43, 1235, 200])
('sortedIdx::', 6)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 6, 'set arr:', [-4, 7, 10, 15, 33, 43, 200, 200])
('sortedIdx::', 7)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 7, 'set arr:', [-4, 7, 10, 15, 33, 43, 200, 1235])
('exponent:', 10000, 'sorted arr:', [-4, 7, 10, 15, 33, 43, 200, 1235])
('sortedIdx::', 1)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 1, 'set arr:', [-323454, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431])
('sortedIdx::', 2)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 2, 'set arr:', [-323454, -4, 7, 43, -323454, 7, 10, 1235, 200, 87431])
('sortedIdx::', 3)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 3, 'set arr:', [-323454, -4, 7, 10, -323454, 7, 10, 1235, 200, 87431])
('sortedIdx::', 4)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 4, 'set arr:', [-323454, -4, 7, 10, 15, 7, 10, 1235, 200, 87431])
('sortedIdx::', 5)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 5, 'set arr:', [-323454, -4, 7, 10, 15, 33, 10, 1235, 200, 87431])
('sortedIdx::', 6)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 6, 'set arr:', [-323454, -4, 7, 10, 15, 33, 43, 1235, 200, 87431])
('sortedIdx::', 7)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 7, 'set arr:', [-323454, -4, 7, 10, 15, 33, 43, 200, 200, 87431])
('sortedIdx::', 8)
('bucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedBucket:', [-4, 7, 10, 15, 33, 43, 200, 1235], 'sortedIdx:', 8, 'set arr:', [-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431])
('origin arr:', [87431], 'exponent:', 10000)
('sortedIdx::', 9)
('bucket:', [87431], 'sortedBucket:', [87431], 'sortedIdx:', 9, 'set arr:', [-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431])
('exponent:', 100000, 'sorted arr:', [-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431])
time:1.1739730835 ms
('radix_sort sorted: ', [-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431])
"""