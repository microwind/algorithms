"""
Copyright © https://github.com/microwind All rights reserved.

@author: jarryli@gmail.com
@version: 1.0
"""

"""
基数排序算法实现
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

# 测试数据：包含大数字和负数的典型数组
test_data = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]

def get_digit(num, exp):
    """获取数字的指定位数"""
    return abs(num) // exp % 10

def counting_sort_by_digit(arr, exp):
    """计数排序辅助函数 - 按位数排序"""
    n = len(arr)
    output = [0] * n
    count = [0] * 10
    
    # 统计每个数字的出现次数
    for i in range(n):
        digit = get_digit(arr[i], exp)
        count[digit] += 1
    
    # 计算累计计数
    for i in range(1, 10):
        count[i] += count[i - 1]
    
    # 构建输出数组
    for i in range(n - 1, -1, -1):
        digit = get_digit(arr[i], exp)
        output[count[digit] - 1] = arr[i]
        count[digit] -= 1
    
    # 复制回原数组
    for i in range(n):
        arr[i] = output[i]

def radix_sort1(arr):
    """
    基数排序基础版本 - LSD（最低位优先）
    
    算法原理：
    1. 从个位开始，对每一位进行计数排序
    2. 逐步处理十位、百位、千位等
    3. 经过所有位数处理后，数组完全有序
    
    生活类比：就像整理学生成绩，先按个位数排序，
    再按十位数排序，最后按百位数排序，最终得到完整排序
    
    时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
    空间复杂度：O(n + k) - 需要额外的计数和输出数组
    稳定性：稳定 - 计数排序保持相等元素的相对位置
    """
    print("radixSort1 LSD:")
    
    # 找到最大值以确定位数
    max_val = max(arr) if arr else 0
    
    # 对每个位数进行计数排序
    exp = 1
    while max_val // exp > 0:
        counting_sort_by_digit(arr, exp)
        exp *= 10
    
    print(arr)
    return arr

def msd_sort(arr, left, right, exp):
    """MSD递归排序函数"""
    if left >= right or exp < 1:
        return
    
    # 创建桶
    buckets = [[] for _ in range(10)]
    
    # 分配到桶中
    for i in range(left, right + 1):
        digit = get_digit(arr[i], exp)
        buckets[digit].append(arr[i])
    
    # 重新排序并递归处理每个桶
    index = left
    for i in range(10):
        if buckets[i]:
            # 复制桶中元素回原数组
            for j in range(len(buckets[i])):
                arr[index] = buckets[i][j]
                index += 1
            
            # 递归处理下一个位数
            msd_sort(arr, left, index - 1, exp // 10)
            left = index

def radix_sort2(arr):
    """
    基数排序优化版本 - MSD（最高位优先）
    
    算法思路：
    从最高位开始排序，使用递归处理子数组
    适合处理字符串或变长数据
    
    优化效果：
    - 更好的内存局部性
    - 适合大数据集
    
    时间复杂度：O(d * (n + k))
    空间复杂度：O(n + k)
    稳定性：稳定
    """
    print("radixSort2 MSD:")
    
    if not arr:
        return arr
    
    # 找到最大值以确定位数
    max_val = max(arr)
    exp = 1
    while max_val // exp > 0:
        exp *= 10
    
    msd_sort(arr, 0, len(arr) - 1, exp // 10)
    
    print(arr)
    return arr

def radix_sort3(arr):
    """
    基数排序 - 迭代MSD版本
    
    算法思路：
    使用迭代方式实现MSD排序
    使用栈来模拟递归调用
    
    优化效果：
    - 避免递归开销
    - 更好的性能控制
    
    时间复杂度：O(d * (n + k))
    空间复杂度：O(n + k)
    稳定性：稳定
    """
    print("radixSort3 iterative MSD:")
    
    if not arr:
        return arr
    
    # 找到最大值以确定位数
    max_val = max(arr)
    exp = 1
    while max_val // exp > 0:
        exp *= 10
    
    # 使用栈模拟递归
    stack = [(0, len(arr) - 1, exp // 10)]
    
    while stack:
        left, right, current_exp = stack.pop()
        
        if left >= right or current_exp < 1:
            continue
        
        # 创建桶
        buckets = [[] for _ in range(10)]
        
        # 分配到桶中
        for i in range(left, right + 1):
            digit = get_digit(arr[i], current_exp)
            buckets[digit].append(arr[i])
        
        # 重新排序并将子问题入栈
        index = left
        for i in range(10):
            if buckets[i]:
                # 复制桶中元素回原数组
                for j in range(len(buckets[i])):
                    arr[index] = buckets[i][j]
                    index += 1
                
                # 将子问题入栈（逆序处理以保持正确顺序）
                stack.append((left, index - 1, current_exp // 10))
                left = index

    print(arr)
    return arr

def radix_sort4(arr):
    """
    基数排序 - 桶优化版本
    
    算法思路：
    使用动态桶大小，优化内存使用
    适合处理稀疏数据
    
    优化效果：
    - 减少内存占用
    - 提高处理效率
    
    时间复杂度：O(d * (n + k))
    空间复杂度：O(n + k)
    稳定性：稳定
    """
    print("radixSort4 bucket optimized:")
    
    # 找到最大值以确定位数
    max_val = max(arr) if arr else 0
    
    # 对每个位数进行计数排序
    exp = 1
    while max_val // exp > 0:
        n = len(arr)
        output = [0] * n
        
        # 动态确定桶范围
        min_digit = 9
        max_digit = 0
        for i in range(n):
            digit = get_digit(arr[i], exp)
            min_digit = min(min_digit, digit)
            max_digit = max(max_digit, digit)
        
        bucket_size = max_digit - min_digit + 1
        count = [0] * bucket_size
        
        # 统计每个数字的出现次数
        for i in range(n):
            digit = get_digit(arr[i], exp)
            count[digit - min_digit] += 1
        
        # 计算累计计数
        for i in range(1, bucket_size):
            count[i] += count[i - 1]
        
        # 构建输出数组
        for i in range(n - 1, -1, -1):
            digit = get_digit(arr[i], exp)
            output[count[digit - min_digit] - 1] = arr[i]
            count[digit - min_digit] -= 1
        
        # 复制回原数组
        for i in range(n):
            arr[i] = output[i]
        
        exp *= 10
    
    print(arr)
    return arr

# ==================== 算法测试和性能对比 ====================

# 测试1：LSD版本
performance_test(radix_sort1, test_data, 'LSD版本')

# 测试2：MSD版本
performance_test(radix_sort2, test_data, 'MSD版本')

# 测试3：迭代MSD版本
performance_test(radix_sort3, test_data, '迭代MSD版本')

# 测试4：桶优化版本
performance_test(radix_sort4, test_data, '桶优化版本')

print('=== 算法对比总结 ===')
print('1. LSD版本：经典实现，从低到高')
print('2. MSD版本：高位优先，递归处理')
print('3. 迭代MSD版本：避免递归，性能稳定')
print('4. 桶优化版本：动态桶大小，内存优化')

"""
打印结果
jarry@Mac radixsort % python radix_sort.py
LSD版本原始数组: [7, 11, 9, 10, 12, 13, 8]
radixSort1 LSD:
[7, 8, 9, 10, 11, 12, 13]
LSD版本: 0.125ms
LSD版本排序结果: [7, 8, 9, 10, 11, 12, 13]

MSD版本原始数组: [7, 11, 9, 10, 12, 13, 8]
radixSort2 MSD:
[7, 8, 9, 10, 11, 12, 13]
MSD版本: 0.042ms
MSD版本排序结果: [7, 8, 9, 10, 11, 12, 13]

迭代MSD版本原始数组: [7, 11, 9, 10, 12, 13, 8]
radixSort3 iterative MSD:
[7, 8, 9, 10, 11, 12, 13]
迭代MSD版本: 0.042ms
迭代MSD版本排序结果: [7, 8, 9, 10, 11, 12, 13]

桶优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
radixSort4 bucket optimized:
[7, 8, 9, 10, 11, 12, 13]
桶优化版本: 0.042ms
桶优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. LSD版本：经典实现，从低到高
2. MSD版本：高位优先，递归处理
3. 迭代MSD版本：避免递归，性能稳定
4. 桶优化版本：动态桶大小，内存优化
"""
