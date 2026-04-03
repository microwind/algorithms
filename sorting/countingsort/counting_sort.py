"""
Copyright © https://github.com/microwind All rights reserved.

@author: jarryli@gmail.com
@version: 1.0
"""

"""
计数排序算法实现
提供四种不同的实现方式，适合不同场景和性能需求
"""

import time

def print_array(arr, label):
    """打印数组内容的辅助函数"""
    print(f"{label}: [{', '.join(map(str, arr))}]")

def performance_test(sort_func, arr, name):
    """性能测试辅助函数"""
    # 创建数组副本，避免修改原数组
    test_arr = arr.copy()
    print_array(test_arr, f"{name}原始数组")
    
    # 开始计时
    start_time = time.perf_counter()
    sort_func(test_arr)
    end_time = time.perf_counter()
    
    print(f"{name}: {(end_time - start_time) * 1000:.3f}ms")
    print_array(test_arr, f"{name}排序结果")
    print()  # 空行分隔

# ==================== 主程序：算法演示和性能测试 ====================

# 测试数据：包含负数和重复元素的典型数组
test_data = [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]

def counting_sort1(arr):
    """
    计数排序基础版本 - 标准实现
    
    算法原理：
    第一步：找到最小值和最大值，确定数据范围
    第二步：创建计数数组，统计每个元素出现的次数
    第三步：计算累计计数以确定元素位置
    第四步：从后向前遍历，根据累计计数将元素放到正确位置
    
    生活类比：就像统计班级学生成绩分布，
    先统计每个分数段有多少人，然后按分数段排序
    
    时间复杂度：O(n + k)，n为元素个数，k为数据范围
    空间复杂度：O(k) - 需要计数数组
    稳定性：稳定 - 从后向前遍历保持相等元素的相对位置
    """
    print("countingSort1 standard:")
    
    if len(arr) == 0:
        return arr
    
    # 第一步：找到最小值和最大值，确定数据范围
    min_val = min(arr)
    max_val = max(arr)
    range_val = max_val - min_val + 1
    
    # 第二步：创建计数数组，统计每个元素出现的次数
    count = [0] * range_val
    
    # 统计每个元素出现的次数
    for i in range(len(arr)):
        # 将元素值转换为计数数组索引（支持负数）
        count[arr[i] - min_val] += 1
    
    # 第三步：计算累计计数以确定元素位置
    for i in range(1, len(count)):
        count[i] += count[i - 1]
    
    # 第四步：从后向前遍历，根据累计计数将元素放到正确位置
    output = [0] * len(arr)
    
    # 从后向前遍历，保证稳定性
    for i in range(len(arr) - 1, -1, -1):
        value = arr[i]
        index = value - min_val
        # 根据累计计数确定最终位置
        output[count[index] - 1] = value
        # 减少计数，为重复元素预留位置
        count[index] -= 1
    
    # 复制回原数组
    for i in range(len(arr)):
        arr[i] = output[i]
    
    print(arr)
    return arr

def counting_sort2(arr):
    """
    计数排序优化版本 - 内存优化
    
    算法思路：
    第一步：找到最小值和最大值，确定数据范围
    第二步：创建计数数组，统计每个元素出现的次数
    第三步：直接根据计数重构数组，省去累加步骤
    
    优化效果：
    - 减少额外空间使用
    - 更好的缓存性能
    
    时间复杂度：O(n + k)
    空间复杂度：O(k)
    稳定性：不稳定 - 原地修改可能影响稳定性
    """
    print("countingSort2 memory optimized:")
    
    if len(arr) == 0:
        return arr
    
    # 第一步：找到最小值和最大值，确定数据范围
    min_val = min(arr)
    max_val = max(arr)
    range_val = max_val - min_val + 1
    
    # 第二步：创建计数数组，统计每个元素出现的次数
    count = [0] * range_val
    
    # 统计每个元素出现的次数
    for i in range(len(arr)):
        # 将元素值转换为计数数组索引（支持负数）
        count[arr[i] - min_val] += 1
    
    # 第三步：直接根据计数重构数组，省去累加步骤
    index = 0
    for i in range(len(count)):
        while count[i] > 0:
            # 将索引转换回原值并放入数组
            arr[index] = i + min_val
            index += 1
            count[i] -= 1
    
    print(arr)
    return arr

def counting_sort3(arr):
    """
    计数排序 - 负数单独处理版本
    
    算法思路：
    第一步：分离正数和负数，分别处理
    第二步：对负数部分转换为绝对值进行排序，然后反转并恢复负号
    第三步：对正数部分使用标准计数排序
    第四步：合并排序后的负数和正数部分
    
    优化效果：
    - 支持负数排序
    - 保持算法稳定性
    
    时间复杂度：O(n + k)
    空间复杂度：O(k)
    稳定性：稳定
    """
    print("countingSort3 negative numbers:")
    
    if len(arr) == 0:
        return arr
    
    # 第一步：分离正数和负数，分别处理
    negatives = [x for x in arr if x < 0]
    positives = [x for x in arr if x >= 0]
    
    # 第二步：对负数部分转换为绝对值进行排序，然后反转并恢复负号
    if negatives:
        abs_negatives = [abs(x) for x in negatives]
        
        # 使用独立的计数排序逻辑
        if len(abs_negatives) > 0:
            # 找到最小值和最大值
            min_abs = min(abs_negatives)
            max_abs = max(abs_negatives)
            range_abs = max_abs - min_abs + 1
            
            # 创建计数数组
            count_abs = [0] * range_abs
            
            # 统计每个元素出现的次数
            for num in abs_negatives:
                count_abs[num - min_abs] += 1
            
            # 计算累计计数
            for i in range(1, len(count_abs)):
                count_abs[i] += count_abs[i - 1]
            
            # 从后向前遍历，保证稳定性
            output_abs = [0] * len(abs_negatives)
            for i in range(len(abs_negatives) - 1, -1, -1):
                value = abs_negatives[i]
                index = value - min_abs
                output_abs[count_abs[index] - 1] = value
                count_abs[index] -= 1
            
            # 反转并恢复负号（负数排序后应该是从大到小，所以要反转）
            for i in range(len(output_abs)):
                negatives[i] = -output_abs[len(output_abs) - 1 - i]
    
    # 第三步：对正数部分使用标准计数排序
    if positives:
        # 使用独立的计数排序逻辑
        if len(positives) > 0:
            # 找到最小值和最大值
            min_pos = min(positives)
            max_pos = max(positives)
            range_pos = max_pos - min_pos + 1
            
            # 创建计数数组
            count_pos = [0] * range_pos
            
            # 统计每个元素出现的次数
            for num in positives:
                count_pos[num - min_pos] += 1
            
            # 计算累计计数
            for i in range(1, len(count_pos)):
                count_pos[i] += count_pos[i - 1]
            
            # 从后向前遍历，保证稳定性
            output_pos = [0] * len(positives)
            for i in range(len(positives) - 1, -1, -1):
                value = positives[i]
                index = value - min_pos
                output_pos[count_pos[index] - 1] = value
                count_pos[index] -= 1
            
            # 复制回正数数组
            for i in range(len(output_pos)):
                positives[i] = output_pos[i]
    
    # 第四步：合并排序后的负数和正数部分
    result = negatives + positives
    
    # 复制回原数组
    for i in range(len(result)):
        arr[i] = result[i]
    
    print(arr)
    return arr

def counting_sort4(arr):
    """
    计数排序 - 桶优化版本
    
    算法思路：
    第一步：找到最小值和最大值，确定数据范围和桶参数
    第二步：创建多个桶，将相近的数值分组
    第三步：对每个桶进行计数排序
    第四步：合并所有桶的排序结果
    
    优化效果：
    - 减少内存使用
    - 提高处理稀疏数据的效率
    
    时间复杂度：O(n + k)
    空间复杂度：O(k)
    稳定性：稳定
    """
    print("countingSort4 bucket optimized:")
    
    if len(arr) == 0:
        return arr
    
    # 第一步：找到最小值和最大值，确定数据范围和桶参数
    min_val = min(arr)
    max_val = max(arr)
    range_val = max_val - min_val + 1
    
    # 确定桶的大小（可以调整以优化性能）
    bucket_size = max(1, range_val // 10)
    bucket_count = (range_val + bucket_size - 1) // bucket_size
    
    # 第二步：创建多个桶，将相近的数值分组
    buckets = [[] for _ in range(bucket_count)]
    
    # 将元素分配到桶中
    for i in range(len(arr)):
        # 根据值计算桶索引
        bucket_index = (arr[i] - min_val) // bucket_size
        buckets[bucket_index].append(arr[i])
    
    # 第三步：对每个桶进行计数排序
    # 第四步：合并所有桶的排序结果
    index = 0
    for i in range(bucket_count):
        if buckets[i]:
            # 使用独立的计数排序逻辑
            bucket = buckets[i]
            if len(bucket) > 0:
                # 找到最小值和最大值
                min_bucket = min(bucket)
                max_bucket = max(bucket)
                range_bucket = max_bucket - min_bucket + 1
                
                # 创建计数数组
                count_bucket = [0] * range_bucket
                
                # 统计每个元素出现的次数
                for num in bucket:
                    count_bucket[num - min_bucket] += 1
                
                # 计算累计计数
                for j in range(1, len(count_bucket)):
                    count_bucket[j] += count_bucket[j - 1]
                
                # 从后向前遍历，保证稳定性
                output_bucket = [0] * len(bucket)
                for j in range(len(bucket) - 1, -1, -1):
                    value = bucket[j]
                    idx = value - min_bucket
                    output_bucket[count_bucket[idx] - 1] = value
                    count_bucket[idx] -= 1
            
            # 将排序后的桶内容复制回原数组
            for j in range(len(output_bucket)):
                arr[index] = output_bucket[j]
                index += 1
    
    print(arr)
    return arr

# ==================== 算法测试和性能对比 ====================

# 测试1：标准版本
performance_test(counting_sort1, test_data, '标准版本')

# 测试2：内存优化版本
performance_test(counting_sort2, test_data, '内存优化版本')

# 测试3：负数处理版本
performance_test(counting_sort3, test_data, '负数处理版本')

# 测试4：桶优化版本
performance_test(counting_sort4, test_data, '桶优化版本')

print('=== 算法对比总结 ===')
print('1. 标准版本：经典实现，稳定排序')
print('2. 内存优化版本：原地修改，节省空间')
print('3. 负数处理版本：支持负数，功能完整')
print('4. 桶优化版本：分组处理，适合稀疏数据')

"""
打印结果
jarry@Mac countingsort % python counting_sort.py 
标准版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort1 standard:
[-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
标准版本: 0.014ms
标准版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

内存优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort2 memory optimized:
[-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
内存优化版本: 0.011ms
内存优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

负数处理版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort3 negative numbers:
[-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
负数处理版本: 0.014ms
负数处理版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

桶优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort4 bucket optimized:
[-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
桶优化版本: 0.013ms
桶优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 标准版本：经典实现，稳定排序
2. 内存优化版本：原地修改，节省空间
3. 负数处理版本：支持负数，功能完整
4. 桶优化版本：分组处理，适合稀疏数据
"""
