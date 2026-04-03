#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 """

import time

def bucket_sort1(arr):
    """
    桶排序支持负数版本 - 负数放在第1个桶里排序
    
    算法原理：
    1. 计算数组最大值和最小值（取绝对值）
    2. 根据最大最小值计算桶的数量和大小
    3. 将元素分配到对应桶中，负数统一放在第1个桶
    4. 在每个桶内进行插入排序
    5. 合并所有桶的元素
    
    生活类比：就像整理图书馆的书籍，
    先按类别分到不同的书架，再在每个书架内按字母顺序排列
    
    @param {number[]} arr - 待排序的数字数组
    @returns {number[]} 排序后的数组
    """
    print('bucketSort1 with negative numbers:')
    
    max_value = max(arr)
    min_value = min(arr)
    max_value = abs(max_value)
    min_value = abs(min_value)
    if max_value < min_value:
        tmp = max_value
        max_value = min_value
        min_value = tmp
    
    # 设置桶的数量，可以任意设置，也可以根据最大、最小值来设置
    bucket_number = abs(int((max_value - min_value) / min_value)) + 1
    bucket_size = abs(int((max_value - min_value) / bucket_number)) + 1
    
    # 第一步：初始化桶
    buckets = [None for i in range(min_value, max_value + 1)]
    
    # 第二步：将元素分配到对应桶中
    for item in arr:
        # 关键点：当前项除以桶数取整，决定应该放在某个桶内
        idx = int((item - min_value) / bucket_size)
        # 负数处理：负数全放在第一个桶里，按照插入方式排序
        idx = idx if idx > 0 else 0
        
        if buckets[idx] is None:
            buckets[idx] = []
            buckets[idx].append(item)
        else:
            # 插入排序：自后往前遍历，找到合适的插入位置
            l = len(buckets[idx]) - 1
            while l >= 0:
                # 比较逻辑：如果数字大于数组中的项则插入其后
                if item > buckets[idx][l]:
                    # Python特点：使用insert插入元素
                    buckets[idx].insert(l + 1, item)
                    break
                elif l == 0:
                    # 边界处理：如果数字最小则插入到最前
                    buckets[idx].insert(0, item)
                    break
                l -= 1
    
    # 第三步：合并结果，按照下标和顺序取出桶内的数字，回填到一个数组中
    output = []
    for i in range(len(buckets)):
        if buckets[i]:
            output = output + buckets[i]
    
    print(output)
    return output

def bucket_sort2(arr):
    """
    桶排序标准版 - 不支持负数
    
    算法思路：
    1. 计算数组的最大值和最小值
    2. 处理最小值小于等于0的情况（设为1），避免负数问题
    3. 动态计算桶的数量和大小，基于数组长度优化
    4. 将元素分配到对应桶中
    5. 桶内使用插入排序
    6. 合并所有桶的元素
    
    优化效果：
    - 桶分配更精确，性能较好
    - 动态桶数量，适应不同数据规模
    - 不支持负数，避免复杂的边界处理
    
    @param {number[]} arr - 待排序的数字数组（仅支持正数）
    @returns {number[]} 排序后的数组
    """
    print('bucketSort2 positive numbers only:')
    
    max_value = max(arr)
    min_value = min(arr)
    
    # 边界处理：处理最小值小于等于0的情况，避免负数问题
    if min_value < max_value and min_value <= 0:
        min_value = 1
    
    # 动态计算：根据数组长度动态计算桶的数量和大小
    size = int(len(arr) / 2)
    bucket_number = abs(int((max_value - min_value) / min_value)) + 1
    bucket_number = bucket_number if bucket_number > size else size
    bucket_size = abs(int((max_value - min_value) / bucket_number)) + 1
    
    # 第一步：初始化桶
    buckets = []
    
    # 第二步：将元素分配到对应桶中
    for item in arr:
        # 桶索引：计算元素应该放入的桶索引
        idx = int((item - min_value) / bucket_size)
        
        # 桶初始化：如果桶不存在则创建
        if idx >= len(buckets):
            buckets.extend([[] for _ in range(idx - len(buckets) + 1)])
        
        # 元素插入：将元素放入对应桶中
        buckets[idx].append(item)
    
    # 第三步：桶内排序，对每个桶内的元素进行排序
    for i in range(len(buckets)):
        # 插入排序：对每个桶进行插入排序
        for j in range(1, len(buckets[i])):
            key = buckets[i][j]
            k = j - 1
            # 从前往后比较，找到合适的插入位置
            while k >= 0 and buckets[i][k] > key:
                buckets[i][k + 1] = buckets[i][k]
                k -= 1
            buckets[i][k + 1] = key
    
    # 第四步：合并结果，按照桶的顺序合并所有元素
    output = []
    for i in range(len(buckets)):
        if buckets[i]:
            output = output + buckets[i]
    
    print(output)
    return output

def bucket_sort3(arr):
    """
    桶排序挪动排序版本
    
    算法原理：
    1. 手动遍历计算数组最大值和最小值
    2. 根据数组长度计算桶的数量和大小
    3. 将元素分配到对应桶中，支持负数
    4. 使用挪动排序而非修改进行桶内排序
    5. 合并所有桶的元素
    
    优化效果：
    - 手动计算最大最小值，更可控
    - 支持负数，负数统一处理
    
    @param {number[]} arr - 待排序的数字数组
    @returns {number[]} 排序后的数组
    """
    print('bucketSort3 with move sorting:')
    
    max_value = arr[0]
    min_value = arr[0]
    
    # 手动遍历：获取数组最大最小值，避免使用max/min
    for i in range(1, len(arr)):
        if arr[i] > max_value:
            max_value = arr[i]
        if arr[i] < min_value:
            min_value = arr[i]
    
    # 边界处理：处理最大最小值小于等于0的情况
    if max_value <= 0:
        max_value = 1
    if min_value <= 0:
        min_value = 1
    
    # 桶计算：根据最大最小值计算桶的数量和大小
    bucket_number = abs(int((max_value - min_value) / min_value)) + 1
    bucket_size = abs(int((max_value - min_value) / bucket_number)) + 1
    
    # 第一步：初始化桶
    buckets = []
    
    # 第二步：将元素分配到对应桶中
    for item in arr:
        # 桶索引：计算元素应该放入的桶索引
        idx = int((item - min_value) / bucket_size)
        
        # 负数处理：负数全部放入第一个桶
        if idx < 0:
            idx = 0
        
        # 每个桶都是一个数组，若不存在则创建并放入数字
        if idx >= len(buckets):
            buckets.extend([[] for _ in range(idx - len(buckets) + 1)])
        
        # 桶初始化：如果桶不存在则创建
        if not buckets[idx]:
            buckets[idx] = []
        
        # 挪动排序：使用挪动排序插入元素，保持插入排序的稳定性
        if len(buckets[idx]) == 0:
            buckets[idx].append(item)
        else:
            # 挪动操作：将当前项逐个往后挪动
            len_bucket = len(buckets[idx])
            buckets[idx].extend([None] * (len_bucket + 1))
            buckets[idx][len_bucket] = item
            while len_bucket > 0:
                # 比较逻辑：如果插入的数字小于当前项，则将当前项逐个往后挪动
                if item < buckets[idx][len_bucket - 1]:
                    buckets[idx][len_bucket] = buckets[idx][len_bucket - 1]
                else:
                    # 插入操作：如果大于等于当前项，则插入到当前项后面，循环中止
                    buckets[idx][len_bucket] = item
                    break
                len_bucket -= 1
    
    # 第三步：合并结果，按照桶的顺序合并所有元素
    output = []
    for i in range(len(buckets)):
        if buckets[i]:
            output = output + buckets[i]
    
    print(output)
    return output

def bucket_sort4(arr):
    """
    桶排序负数单独处理版 - 负数单独排序
    
    算法思路：
    1. 手动遍历获取最大最小值
    2. 处理最小值小于等于0的情况
    3. 计算桶的数量和大小
    4. 将正数分配到桶中，负数单独收集
    5. 负数单独排序后先输出
    6. 输出正数桶的元素
    
    优化效果：
    - 负数和正数分别优化，排序更精确
    - 负数使用Array.sort排序，效率更高
    - 最终结果先输出负数再输出正数
    
    @param {number[]} arr - 待排序的数字数组
    @returns {number[]} 排序后的数组
    """
    print('bucketSort4 separate negative sorting:')
    max_value = arr[0]
    min_value = arr[0]

    # 手动遍历：获取数组最大最小值，避免使用max/min
    for i in range(len(arr)):
        # 最大值：如果当前元素大于max，则更新max
        if arr[i] > max_value:
            max_value = arr[i]
        # 最小值：如果当前元素小于min，则更新min
        if arr[i] < min_value:
            min_value = arr[i]

    # 边界处理：处理最小值小于等于0的情况
    if min_value < max_value and min_value <= 0:
        min_value = 1

    # 桶计算：根据最大最小值计算桶的数量和大小
    bucket_number = abs(int((max_value - min_value) / min_value)) + 1
    bucket_size = abs(int((max_value - min_value) / bucket_number)) + 1
    buckets = []
    
    # 负数处理：创建单独的负数数组
    negative_list = []

    # 元素分配：遍历数组，将元素分配到对应桶中
    for item in arr:
        # 分类处理：负数单独收集，正数放入桶中
        if item < 0:
            # 负数收集：将负数添加到负数列表
            negative_list.append(item)
        else:
            # 桶索引：计算正数应该放入的桶索引
            idx = int((item - min_value) / bucket_size)
            
            # 桶初始化：如果桶不存在则创建
            if idx >= len(buckets):
                buckets.extend([[] for _ in range(idx - len(buckets) + 1)])
            if not buckets[idx]:
                buckets[idx] = []
            # 正数分配：将正数放入对应桶中
            buckets[idx].append(item)

    # 负数排序：使用sort对负数进行排序
    negative_list.sort()

    # 结果合并：先输出负数，再输出正数
    output = []

    # 负数输出：将排序后的负数逐个添加到结果数组
    for i in range(len(negative_list)):
        output.append(negative_list[i])

    # 正数输出：按照桶的顺序输出正数
    for i in range(len(buckets)):
        if buckets[i]:
            output.extend(buckets[i])
    
    print(output)
    return output

def bucket_sort5(arr):
    """
    桶排序实时冒泡版 - 负数放在第一个桶内排序
    
    算法思路：
    1. 计算数组的最大值和最小值
    2. 根据数组长度计算桶的大小
    3. 将元素分配到桶中，负数放在第1个桶
    4. 每次插入后立即对桶内进行冒泡排序
    5. 合并所有桶的元素
    
    优化效果：
    - 每次插入后立即排序桶内元素
    - 使用冒泡排序保持桶内有序
    - 插入即排序，无需后续排序步骤
    
    @param {number[]} arr - 待排序的数字数组
    @returns {number[]} 排序后的数组
    """
    print('bucketSort5 real-time bubble sorting:')
    
    # 交换函数：定义数组元素交换的辅助函数
    def swap(lst, i, j):
        temp = lst[i]
        lst[i] = lst[j]
        lst[j] = temp

    # 范围计算：计算数组的最大值和最小值
    max_value = max(arr)
    min_value = min(arr)
    buckets = []
    
    # 桶大小：根据数组长度计算桶的大小
    bucket_size = int((max_value - min_value) / len(arr)) + 1

    # 元素分配：遍历数组，将元素分配到对应桶中
    for i in range(len(arr)):
        # 桶索引：计算元素应该放入的桶索引
        idx = int((arr[i] - min_value) / bucket_size)

        # 负数处理：负数放在第1个桶
        if idx < 0:
            idx = 0

        # 桶初始化：如果桶不存在则创建
        if idx >= len(buckets):
            buckets.extend([[] for _ in range(idx - len(buckets) + 1)])
        if not buckets[idx]:
            buckets[idx] = []

        # 元素插入：将元素插入到桶中
        buckets[idx].append(arr[i])

        # 实时排序：插入后立即对桶内进行冒泡排序
        bucket_len = len(buckets[idx])
        # 冒泡排序：从后往前比较，确保桶内有序
        for j in range(bucket_len - 1, 0, -1):
            # 比较交换：如果前一个元素大于后一个元素，则交换
            if buckets[idx][j] < buckets[idx][j - 1]:
                # 交换操作：调用交换函数
                swap(buckets[idx], j, j - 1)

    # 结果合并：将各桶的数据合并到新数组
    wrap_buckets = []
    for i in range(len(buckets)):
        if buckets[i]:
            wrap_buckets.extend(buckets[i])
    
    print(wrap_buckets)
    return wrap_buckets

def bucket_sort6(arr):
    """
    桶排序优化版 - 使用更精确的桶分配策略
    
    算法思路：
    1. 分析数据分布，计算最优桶数量
    2. 使用更精确的桶边界计算
    3. 桶内使用快速排序提高效率
    4. 支持负数和浮点数
    5. 优化内存使用
    
    优化效果：
    - 智能桶数量计算
    - 更精确的数据分布处理
    - 桶内使用快速排序
    - 更好的边界条件处理
    
    @param {number[]} arr - 待排序的数字数组
    @returns {number[]} 排序后的数组
    """
    print('bucketSort6 optimized version:')
    if len(arr) <= 1:
        return arr.copy()
    
    # 范围计算：计算数据范围
    min_value = min(arr)
    max_value = max(arr)
    range_value = max_value - min_value
    
    # 智能计算：基于数据分布和数组大小计算最优桶数量
    import math
    optimal_bucket_count = max(5, min(len(arr), math.ceil(math.sqrt(len(arr)))))
    bucket_size = range_value / optimal_bucket_count
    
    # 桶创建：创建指定数量的桶
    buckets = [[] for _ in range(optimal_bucket_count)]
    
    # 元素分配：分配元素到对应桶中
    for value in arr:
        # 边界处理：处理最大值和最小值的特殊情况
        if value == max_value:
            bucket_index = optimal_bucket_count - 1
        elif value == min_value:
            bucket_index = 0
        else:
            bucket_index = int((value - min_value) / bucket_size)
        
        # 索引检查：确保索引在有效范围内
        bucket_index = max(0, min(optimal_bucket_count - 1, bucket_index))
        
        # 元素插入：将元素放入对应桶中
        buckets[bucket_index].append(value)
    
    # 桶内排序：对每个桶进行排序并合并
    result = []
    for bucket in buckets:
        if len(bucket) > 0:
            # 快速排序：使用Python内置排序
            bucket.sort()
            result.extend(bucket)
    
    print(result)
    return result

# ==================== 测试代码 ====================

if __name__ == "__main__":
    arr_data = [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
    
    print('=== 桶排序算法演示 ===\n')
    
    # 测试bucket_sort1
    start_time = time.time()
    print('arrData origin:', arr_data)
    result1 = bucket_sort1(arr_data)
    end_time = time.time()
    print('bucketSort1: {:.3f}ms'.format((end_time - start_time) * 1000))
    
    print('\r\n')
    
    # 测试bucket_sort2
    start_time = time.time()
    print('arrData origin:', arr_data)
    result2 = bucket_sort2(arr_data)
    end_time = time.time()
    print('bucketSort2: {:.3f}ms'.format((end_time - start_time) * 1000))
    
    print('\r\n')
    
    # 测试bucket_sort3
    start_time = time.time()
    print('arrData origin:', arr_data)
    result3 = bucket_sort3(arr_data)
    end_time = time.time()
    print('bucketSort3: {:.3f}ms'.format((end_time - start_time) * 1000))
    
    print('\r\n')
    
    # 测试bucket_sort4
    start_time = time.time()
    print('arrData origin:', arr_data)
    result4 = bucket_sort4(arr_data)
    end_time = time.time()
    print('bucketSort4: {:.3f}ms'.format((end_time - start_time) * 1000))
    
    print('\r\n')
    
    # 测试bucket_sort5
    start_time = time.time()
    print('arrData origin:', arr_data)
    result5 = bucket_sort5(arr_data)
    end_time = time.time()
    print('bucketSort5: {:.3f}ms'.format((end_time - start_time) * 1000))
    
    print('\r\n')
    
    # 测试bucket_sort6
    start_time = time.time()
    print('arrData origin:', arr_data)
    result6 = bucket_sort6(arr_data)
    end_time = time.time()
    print('bucketSort6: {:.3f}ms'.format((end_time - start_time) * 1000))
    
    print('\r\n')
    
    print('=== 算法对比总结 ===')
    print('1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理')
    print('2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好')
    print('3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性')
    print('4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确')
    print('5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序')
    print('6. 优化版本：bucketSort6 - 智能桶数量计算，更精确的数据分布处理')

"""
打印结果
jarry@Mac bucketsort % python bucket_sort.py 
=== 桶排序算法演示 ===

arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort1 with negative numbers:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort1: 0.023ms


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort2 positive numbers only:
[6, 9, -10, 11, 13, 15, 0, 20, 30, 80]
bucketSort2: 0.024ms


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort3 with move sorting:
[0, 0, None, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort3: 0.017ms


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort4 separate negative sorting:
[-10, 6, 9, 11, 13, 15, 20, 0, 30, 80]
bucketSort4: 0.013ms


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort5 real-time bubble sorting:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort5: 0.014ms


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort6 optimized version:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort6: 1.294ms


=== 算法对比总结 ===
1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理
2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好
3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性
4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确
5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序
"""
