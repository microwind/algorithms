"""
Copyright © https://github.com/microwind All rights reserved.

@author: jarryli@gmail.com
@version: 1.0
"""

"""
插入排序算法实现
提供6种不同的实现方式，适合不同场景和性能需求
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

# 测试数据：
test_data = [7, 11, 9, 10, 12, 13, 8]

def insert_sort1(arr):
    """
    插入排序基础版本 - 标准实现
    
    算法原理：
    1. 从第二个元素开始，将其作为"当前元素"
    2. 将当前元素与前面已排序的元素比较
    3. 找到合适的位置插入当前元素
    4. 重复步骤1-3，直到所有元素都排序完成
    
    生活类比：就像整理手中的扑克牌，
    每次拿起一张新牌，插入到手中已排序牌的合适位置
    
    时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
    空间复杂度：O(1) - 原地排序
    稳定性：稳定 - 保持相等元素的相对位置
    """
    print("insertSort1 standard:")
    
    # 从第二个元素开始遍历
    for i in range(1, len(arr)):
        # 关键点：保存当前元素作为待插入元素
        current = arr[i]
        j = i - 1
        
        # 向前查找插入位置，同时移动元素
        while j >= 0 and arr[j] > current:
            arr[j + 1] = arr[j]
            j -= 1
        
        # 插入当前元素
        arr[j + 1] = current
    
    print(arr)
    return arr

def binary_search(arr, value, left, right):
    """二分查找插入位置"""
    while left <= right:
        mid = (left + right) // 2
        
        if arr[mid] == value:
            return mid + 1  # 插入到相同元素后面，保持稳定性
        elif arr[mid] < value:
            left = mid + 1
        else:
            right = mid - 1
    
    return left

def insert_sort2(arr):
    """
    插入排序优化版本 - 二分查找插入位置
    
    算法思路：
    使用二分查找确定插入位置，减少比较次数
    保持插入操作，但优化查找过程
    
    优化效果：
    - 减少比较次数：从O(n)到O(log n)
    - 保持插入操作的时间复杂度
    
    时间复杂度：平均O(n²)，最好O(n log n)，最坏O(n²)
    空间复杂度：O(1) - 原地排序
    稳定性：稳定
    """
    print("insertSort2 binary search:")
    
    # 从第二个元素开始遍历
    for i in range(1, len(arr)):
        current = arr[i]
        
        # 使用二分查找确定插入位置
        insert_pos = binary_search(arr, current, 0, i - 1)
        
        # 移动元素为新元素腾出空间
        for j in range(i, insert_pos, -1):
            arr[j] = arr[j - 1]
        
        # 插入元素
        arr[insert_pos] = current
    
    print(arr)
    return arr

def insert_sort3(arr):
    """
    插入排序 - 哨兵版本
    
    算法思路：
    在数组开头添加哨兵元素，简化边界检查
    减少循环中的条件判断
    
    优化效果：
    - 减少边界检查
    - 简化代码逻辑
    - 轻微的性能提升
    
    时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
    空间复杂度：O(1) - 原地排序（忽略哨兵）
    稳定性：稳定
    """
    print("insertSort3 sentinel:")
    
    if len(arr) == 0:
        return arr
    
    # 找到最小值作为哨兵
    min_index = 0
    for i in range(1, len(arr)):
        if arr[i] < arr[min_index]:
            min_index = i
    
    # 将最小值移到开头作为哨兵
    if min_index != 0:
        arr[0], arr[min_index] = arr[min_index], arr[0]
    
    # 从第三个元素开始排序（第二个元素已经相对于哨兵有序）
    for i in range(2, len(arr)):
        current = arr[i]
        j = i
        
        # 向前查找插入位置（哨兵保证不会越界）
        while arr[j - 1] > current:
            arr[j] = arr[j - 1]
            j -= 1
        
        arr[j] = current
    
    print(arr)
    return arr

def insert_sort4(arr):
    """
    插入排序 - 希尔插入版本
    
    算法思路：
    结合希尔排序的增量概念
    对不同间隔的子序列进行插入排序
    
    优化效果：
    - 更好的初始数据分布
    - 减少总的移动次数
    - 适合部分有序的数据
    
    时间复杂度：平均O(n^1.3)，取决于增量序列
    空间复杂度：O(1) - 原地排序
    稳定性：不稳定 - 增量排序可能破坏稳定性
    """
    print("insertSort4 shell insertion:")
    
    n = len(arr)
    
    # 使用希尔增量序列
    gap = n // 2
    while gap > 0:
        # 对每个增量进行插入排序
        for i in range(gap, n):
            current = arr[i]
            j = i
            
            # 在增量子序列中进行插入排序
            while j >= gap and arr[j - gap] > current:
                arr[j] = arr[j - gap]
                j -= gap
            
            arr[j] = current
        
        gap //= 2
    
    print(arr)
    return arr

# ==================== 算法测试和性能对比 ====================

# 测试1：标准版本
performance_test(insert_sort1, test_data, '标准版本')

# 测试2：二分查找版本
performance_test(insert_sort2, test_data, '二分查找版本')

# 测试3：哨兵版本
performance_test(insert_sort3, test_data, '哨兵版本')

# 测试4：希尔插入版本
performance_test(insert_sort4, test_data, '希尔插入版本')

def insert_sort5(arr):
    """
    插入排序新建数组版本 - 插入选择项
    
    算法思路：
    1. 新建数组，以第一个元素初始化
    2. 遍历原数组，将每个元素插入到新数组的正确位置
    3. 使用插入操作，保持数组有序
    4. 返回新建的有序数组
    
    优化效果：
    - 原数组不变：保持原数据完整性
    - 插入操作：利用语言特性简化实现
    - 逻辑清晰：分离插入和排序逻辑
    
    时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
    空间复杂度：O(n) - 需要新建数组
    稳定性：稳定 - 插入操作保持相等元素相对位置
    """
    print("insertSort5 new array insert:")
    
    if len(arr) == 0:
        return []
    
    # 第一步：新建数组，以第一个元素初始化
    new_arr = [arr[0]]
    
    # 第二步：遍历原数组，从第二个元素开始
    for i in range(1, len(arr)):
        current = arr[i]
        is_max = True
        
        # 第三步：在新数组中查找插入位置
        for j in range(len(new_arr)):
            print(f'i={i} j={j} arr[i]={current} new_arr[j]={new_arr[j]} new_arr={new_arr}')
            
            # 如果当前元素小于新数组中的某个元素，则插入到该位置
            if current < new_arr[j]:
                # 使用Python的列表插入操作
                new_arr.insert(j, current)
                is_max = False
                break
        
        # 第四步：如果当前元素最大，则插入到末尾
        if is_max:
            new_arr.append(current)
    
    print(f'new_arr: {new_arr}')
    return new_arr

def insert_sort6(arr):
    """
    插入排序新建数组倒序遍历版本
    
    算法思路：
    1. 新建数组，以第一个元素初始化
    2. 倒序遍历新数组，从后向前查找插入位置
    3. 如果当前元素大于某个元素，则插入到该位置之后
    4. 如果当前元素最小，则插入到开头
    
    优化效果：
    - 倒序遍历：与正向遍历不同的实现思路
    - 新建数组：保持原数组不变
    - 插入策略：从后向前查找，优化插入位置
    
    时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
    空间复杂度：O(n) - 需要新建数组
    稳定性：稳定 - 插入操作保持相等元素相对位置
    """
    print("insertSort6 new array reverse:")
    
    if len(arr) == 0:
        return []
    
    # 第一步：新建数组，以第一个元素初始化
    new_arr = [arr[0]]
    
    # 第二步：遍历原数组，从第二个元素开始
    for i in range(1, len(arr)):
        current = arr[i]
        is_min = True
        new_len = len(new_arr)
        
        # 第三步：倒序遍历新数组，从后向前查找插入位置
        while new_len > 0:
            new_len -= 1
            print(f'i={i} new_len={new_len} arr[i]={current} new_arr[new_len]={new_arr[new_len]} new_arr={new_arr}')
            
            # 如果当前元素大于新数组中的某个元素，则插入到该位置之后
            if current > new_arr[new_len]:
                # 插入到new_len+1位置
                new_arr.insert(new_len + 1, current)
                is_min = False
                break
        
        # 第四步：如果当前元素最小，则插入到开头
        if is_min:
            new_arr.insert(0, current)
    
    print(f'new_arr: {new_arr}')
    return new_arr

# ==================== 算法测试和性能对比 ====================

# 测试1：标准版本
performance_test(insert_sort1, test_data, '标准版本')

# 测试2：二分查找版本
performance_test(insert_sort2, test_data, '二分查找版本')

# 测试3：哨兵版本
performance_test(insert_sort3, test_data, '哨兵版本')

# 测试4：希尔插入版本
performance_test(insert_sort4, test_data, '希尔插入版本')

# 测试5：新建数组插入版本
performance_test(insert_sort5, test_data, '新建数组插入版本')

# 测试6：新建数组倒序遍历版本
performance_test(insert_sort6, test_data, '新建数组倒序遍历版本')

print('=== 算法对比总结 ===')
print('1. 标准版本：经典实现，易于理解')
print('2. 二分查找版本：优化查找，减少比较')
print('3. 哨兵版本：简化边界，提升性能')
print('4. 希尔插入版本：增量排序，混合优化')
print('5. 新建数组插入版本：原数组不变，插入操作')
print('6. 新建数组倒序遍历版本：倒序遍历，不同思路')

"""
打印结果
jarry@Mac insertsort % python insert_sort.py 
标准版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort1 standard:
[7, 8, 9, 10, 11, 12, 13]
标准版本: 0.006ms
标准版本排序结果: [7, 8, 9, 10, 11, 12, 13]

二分查找版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort2 binary search:
[7, 8, 9, 10, 11, 12, 13]
二分查找版本: 0.007ms
二分查找版本排序结果: [7, 8, 9, 10, 11, 12, 13]

哨兵版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort3 sentinel:
[7, 8, 9, 10, 11, 12, 13]
哨兵版本: 0.004ms
哨兵版本排序结果: [7, 8, 9, 10, 11, 12, 13]

希尔插入版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort4 shell insertion:
[7, 8, 9, 10, 11, 12, 13]
希尔插入版本: 0.005ms
希尔插入版本排序结果: [7, 8, 9, 10, 11, 12, 13]

标准版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort1 standard:
[7, 8, 9, 10, 11, 12, 13]
标准版本: 0.004ms
标准版本排序结果: [7, 8, 9, 10, 11, 12, 13]

二分查找版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort2 binary search:
[7, 8, 9, 10, 11, 12, 13]
二分查找版本: 0.005ms
二分查找版本排序结果: [7, 8, 9, 10, 11, 12, 13]

哨兵版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort3 sentinel:
[7, 8, 9, 10, 11, 12, 13]
哨兵版本: 0.003ms
哨兵版本排序结果: [7, 8, 9, 10, 11, 12, 13]

希尔插入版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort4 shell insertion:
[7, 8, 9, 10, 11, 12, 13]
希尔插入版本: 0.003ms
希尔插入版本排序结果: [7, 8, 9, 10, 11, 12, 13]

新建数组插入版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort5 new array insert:
i=1 j=0 arr[i]=11 new_arr[j]=7 new_arr=[7]
i=2 j=0 arr[i]=9 new_arr[j]=7 new_arr=[7, 11]
i=2 j=1 arr[i]=9 new_arr[j]=11 new_arr=[7, 11]
i=3 j=0 arr[i]=10 new_arr[j]=7 new_arr=[7, 9, 11]
i=3 j=1 arr[i]=10 new_arr[j]=9 new_arr=[7, 9, 11]
i=3 j=2 arr[i]=10 new_arr[j]=11 new_arr=[7, 9, 11]
i=4 j=0 arr[i]=12 new_arr[j]=7 new_arr=[7, 9, 10, 11]
i=4 j=1 arr[i]=12 new_arr[j]=9 new_arr=[7, 9, 10, 11]
i=4 j=2 arr[i]=12 new_arr[j]=10 new_arr=[7, 9, 10, 11]
i=4 j=3 arr[i]=12 new_arr[j]=11 new_arr=[7, 9, 10, 11]
i=5 j=0 arr[i]=13 new_arr[j]=7 new_arr=[7, 9, 10, 11, 12]
i=5 j=1 arr[i]=13 new_arr[j]=9 new_arr=[7, 9, 10, 11, 12]
i=5 j=2 arr[i]=13 new_arr[j]=10 new_arr=[7, 9, 10, 11, 12]
i=5 j=3 arr[i]=13 new_arr[j]=11 new_arr=[7, 9, 10, 11, 12]
i=5 j=4 arr[i]=13 new_arr[j]=12 new_arr=[7, 9, 10, 11, 12]
i=6 j=0 arr[i]=8 new_arr[j]=7 new_arr=[7, 9, 10, 11, 12, 13]
i=6 j=1 arr[i]=8 new_arr[j]=9 new_arr=[7, 9, 10, 11, 12, 13]
new_arr: [7, 8, 9, 10, 11, 12, 13]
新建数组插入版本: 0.026ms
新建数组插入版本排序结果: [7, 11, 9, 10, 12, 13, 8]

新建数组倒序遍历版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort6 new array reverse:
i=1 new_len=0 arr[i]=11 new_arr[new_len]=7 new_arr=[7]
i=2 new_len=1 arr[i]=9 new_arr[new_len]=11 new_arr=[7, 11]
i=2 new_len=0 arr[i]=9 new_arr[new_len]=7 new_arr=[7, 11]
i=3 new_len=2 arr[i]=10 new_arr[new_len]=11 new_arr=[7, 9, 11]
i=3 new_len=1 arr[i]=10 new_arr[new_len]=9 new_arr=[7, 9, 11]
i=4 new_len=3 arr[i]=12 new_arr[new_len]=11 new_arr=[7, 9, 10, 11]
i=5 new_len=4 arr[i]=13 new_arr[new_len]=12 new_arr=[7, 9, 10, 11, 12]
i=6 new_len=5 arr[i]=8 new_arr[new_len]=13 new_arr=[7, 9, 10, 11, 12, 13]
i=6 new_len=4 arr[i]=8 new_arr[new_len]=12 new_arr=[7, 9, 10, 11, 12, 13]
i=6 new_len=3 arr[i]=8 new_arr[new_len]=11 new_arr=[7, 9, 10, 11, 12, 13]
i=6 new_len=2 arr[i]=8 new_arr[new_len]=10 new_arr=[7, 9, 10, 11, 12, 13]
i=6 new_len=1 arr[i]=8 new_arr[new_len]=9 new_arr=[7, 9, 10, 11, 12, 13]
i=6 new_len=0 arr[i]=8 new_arr[new_len]=7 new_arr=[7, 9, 10, 11, 12, 13]
new_arr: [7, 8, 9, 10, 11, 12, 13]
新建数组倒序遍历版本: 0.019ms
新建数组倒序遍历版本排序结果: [7, 11, 9, 10, 12, 13, 8]

=== 算法对比总结 ===
1. 标准版本：经典实现，易于理解
2. 二分查找版本：优化查找，减少比较
3. 哨兵版本：简化边界，提升性能
4. 希尔插入版本：增量排序，混合优化
5. 新建数组插入版本：原数组不变，插入操作
6. 新建数组倒序遍历版本：倒序遍历，不同思路
"""
