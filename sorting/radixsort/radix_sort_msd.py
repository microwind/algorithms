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
# 桶排序，根据数位递归调用
def bucket_sort(arr, exponent):
    # 桶排序递归版：按指定位数分组排序
    if (len(arr) <= 1 or exponent <= 0):
        return arr

    min_value = min(arr)
    radix = 10
    # 创建10个桶
    buckets = [None] * radix

    # 按当前位数分组
    for i in range(len(arr)):
        item = arr[i] - min_value
        bucketIdx = int(item / exponent) % radix
        if buckets[bucketIdx] is None:
            buckets[bucketIdx] = []
        buckets[bucketIdx].append(arr[i])

    # 递归排序每个桶并合并结果
    sortedIdx = 0
    for i in range(radix):
        bucket = buckets[i]
        if bucket is None or len(bucket) < 1:
            continue
        # 递归处理下一位
        sortedBucket = bucket_sort(bucket, exponent // 10)
        # 将排序结果放回原数组
        for num in sortedBucket:
            arr[sortedIdx] = num
            sortedIdx += 1

    return arr

# 基数排序，从高到低逐位排序MSD版，基于桶排序递归实现
def radix_sort_msd(arr):
    # 基数排序MSD版：从高位到低位递归排序
    max_value = max(arr)
    min_value = min(arr)
    # 计算最大位数
    numberOfDigits = int(math.log10(max_value - min_value) + 1)
    exponent = int(math.pow(10, numberOfDigits - 1))
    return bucket_sort(arr, exponent)


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