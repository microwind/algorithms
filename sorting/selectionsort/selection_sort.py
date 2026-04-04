"""
Copyright © https://github.com/microwind All rights reserved.

@author: jarryli@gmail.com
@version: 1.0
"""

"""
选择排序算法实现
提供五种不同的实现方式，适合不同场景和性能需求
"""

def print_array(arr, label):
    """打印数组内容的辅助函数"""
    print(f"{label}: [{', '.join(map(str, arr))}]")

def performance_test(sort_func, arr, name):
    """性能测试辅助函数"""
    # 创建数组副本，避免修改原数组
    test_arr = arr.copy()
    print_array(test_arr, f"{name}原始数组")
    
    # 开始计时
    import time
    start_time = time.perf_counter()
    sort_func(test_arr)
    end_time = time.perf_counter()
    
    print(f"{name}: {(end_time - start_time) * 1000:.3f}ms")
    print_array(test_arr, f"{name}排序结果")
    print()  # 空行分隔

# ==================== 主程序：算法演示和性能测试 ====================

# 测试数据：
test_data = [7, 11, 9, 10, 12, 13, 8]

def selection_sort1(arr):
    """
    选择排序基础版本 - 标准版：原地交换
    
    算法原理：
    1. 将数组分为两部分：左侧已排序区域，右侧待排序区域
    2. 每次从待排序区域中选择最小元素
    3. 将最小元素与待排序区域的第一个元素交换
    4. 重复以上过程，直到所有元素排序完成
    
    ## 实现步骤
    1. 外循环遍历数组，每轮确定一个最小值的位置
    2. 内循环在未排序区域中查找最小元素
    3. 记录最小值和其索引位置
    4. 将最小元素交换到当前轮次的起始位置
    
    Args:
        arr (list): 待排序的数字列表
    Returns:
        list: 排序后的列表
    """
    # 选择排序：每次找到最小元素放到前面
    print('selection_sort1 basic:')
    l = len(arr)
    # 外层循环：每次确定一个最小值的位置
    for i in range(l - 1):
        min = arr[i]
        min_idx = i
        j = i + 1
        # 内层循环：在未排序部分找最小元素
        while j < l:
            if arr[j] < min:
                min = arr[j]
                min_idx = j
            j += 1
        # 将最小元素交换到已排序部分末尾
        if min_idx != i:
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

def selection_sort2(arr):
    """
    选择排序新建数组版本 - 无需交换
    
    算法思路：
    1. 创建一个新数组来存储排序结果
    2. 每次从原数组中找到最小值
    3. 将最小值添加到新数组
    4. 从原数组中删除该最小值
    5. 重复直到原数组为空
    
    ## 实现步骤
    1. 初始化新数组和索引
    2. 外循环控制选择轮数
    3. 内循环查找当前最小值
    4. 将最小值添加到新数组
    5. 从原数组中移除已选择的元素
    6. 调整循环变量以适应数组长度变化
    
    Args:
        arr (list): 待排序的数字列表
    Returns:
        list: 排序后的新列表
    """
    # 选择排序新建数组版：避免交换操作
    print('selection_sort2 new array:')
    new_list = []
    l = len(arr)
    # 外层循环：每次找到最小值并添加到新数组
    while (l > 0):
        min = arr[0]
        min_idx = 0
        j = 1
        # 内层循环：在未排序部分找最小元素
        while (j < l):
            if (arr[j] < min):
                min = arr[j]
                min_idx = j
            j += 1
        # 直接添加最小值到新数组，无需交换
        new_list.append(min)
        # 从原数组删除对应的项
        arr.remove(min)
        l -= 1
    return new_list

def selection_sort3(arr):
    """
    选择排序降序版本
    
    算法思路：
    与基础版本相反，每次选择最大元素
    将最大元素与待排序区域的第一个元素交换
    
    ## 实现步骤
    1. 外循环控制排序轮数，每轮确定一个最大值的位置
    2. 内循环在未排序区域中查找最大元素
    3. 记录最大值和其索引位置
    4. 将最大元素交换到当前轮次的起始位置
    
    Args:
        arr (list): 待排序的数字列表
    Returns:
        list: 排序后的列表
    """
    print('selection_sort3 descending:')
    n = len(arr)
    # 外循环：每轮确定一个最大值
    for i in range(n - 1):
        # 假设当前位置为最大值
        max_index = i
        
        # 内循环：在未排序区域查找最大值
        for j in range(i + 1, n):
            if arr[j] > arr[max_index]:
                max_index = j
        
        # 交换最大元素到正确位置
        if max_index != i:
            arr[i], arr[max_index] = arr[max_index], arr[i]
    
    print(arr)
    return arr

def selection_sort4(arr):
    """
    选择排序优化版本 - 双向选择
    
    优化思路：
    每轮同时选择最小和最大元素
    将最小元素放到左侧，最大元素放到右侧
    减少排序轮数，提高效率
    
    ## 实现步骤
    1. 初始化左右边界指针
    2. 外循环控制排序轮数，同时处理两端
    3. 内循环在未排序区域中查找最小和最大元素
    4. 交换最小元素到左侧，最大元素到右侧
    5. 调整边界指针
    """
    print('selection_sort4 bidirectional:')
    n = len(arr)
    left, right = 0, n - 1
    
    # 外循环：同时处理左右两端
    while left < right:
        min_index = left
        max_index = left
        
        # 内循环：同时查找最小和最大元素
        for i in range(left, right + 1):
            if arr[i] < arr[min_index]:
                min_index = i
            if arr[i] > arr[max_index]:
                max_index = i
        
        # 交换最小元素到左侧
        if min_index != left:
            arr[left], arr[min_index] = arr[min_index], arr[left]
        
        # 处理最大元素位置变化的特殊情况
        if max_index == left:
            max_index = min_index
        
        # 交换最大元素到右侧
        if max_index != right:
            arr[right], arr[max_index] = arr[max_index], arr[right]
        
        left += 1
        right -= 1
    
    print(arr)
    return arr

def selection_sort5(arr):
    """
    选择排序 - 堆优化版本
    
    算法思路：
    利用堆的性质来快速找到最大/最小元素
    每次从堆顶取出最大/最小元素
    重新调整堆结构
    
    ## 实现步骤
    1. 构建最大堆
    2. 逐个取出堆顶元素（最大值）
    3. 将堆顶元素与末尾元素交换
    4. 重新调整堆结构
    5. 重复直到堆为空
    """
    print('selection_sort5 heap optimized:')
    n = len(arr)
    
    def heapify(arr, n, i):
        """堆化辅助函数"""
        largest = i  # 初始化最大元素为根节点
        left = 2 * i + 1  # 左子节点
        right = 2 * i + 2  # 右子节点
        
        # 如果左子节点大于根节点
        if left < n and arr[left] > arr[largest]:
            largest = left
        
        # 如果右子节点大于当前最大节点
        if right < n and arr[right] > arr[largest]:
            largest = right
        
        # 如果最大节点不是根节点，交换并继续堆化
        if largest != i:
            arr[i], arr[largest] = arr[largest], arr[i]
            heapify(arr, n, largest)
    
    # 构建最大堆
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    
    # 逐个取出堆顶元素
    for i in range(n - 1, 0, -1):
        # 交换堆顶与末尾元素
        arr[0], arr[i] = arr[i], arr[0]
        
        # 重新调整堆
        heapify(arr, i, 0)
    
    print(arr)
    return arr

# ==================== 算法测试和性能对比 ====================

import time

print('\n=== 算法性能对比 ===')

# 测试1：基础选择版本（直接测试，不使用performance_test）
print('基础选择版本原始数组:')
print_array(test_data, '')
temp_arr1 = test_data.copy()
start1 = time.perf_counter()
result1 = selection_sort1(temp_arr1)
end1 = time.perf_counter()
print(f'基础选择版本: {(end1 - start1) * 1000:.3f}ms')
print('基础选择版本排序结果:')
print_array(result1, '')
print()

# 测试2：新建数组版本（直接测试，不使用performance_test）
print('新建数组版本原始数组:')
print_array(test_data, '')
temp_arr2 = test_data.copy()
start2 = time.perf_counter()
result2 = selection_sort2(temp_arr2)
end2 = time.perf_counter()
print(f'新建数组版本: {(end2 - start2) * 1000:.3f}ms')
print('新建数组版本排序结果:')
print_array(result2, '')
print()

# 测试3：降序版本
performance_test(selection_sort3, test_data, '降序版本')

# 测试4：双向选择版本
performance_test(selection_sort4, test_data, '双向选择版本')

# 测试5：堆优化版本
performance_test(selection_sort5, test_data, '堆优化版本')

print('=== 算法对比总结 ===')
print('1. 基础版本：标准版，原地交换，包含详细调试信息')
print('2. 新建数组版本：无需交换，避免交换操作')
print('3. 降序版本：展示算法灵活性，可按需排序')
print('4. 双向版本：同时选择最大最小，效率提升')
print('5. 堆优化版本：利用堆结构，复杂度优化')

"""
jarry@Mac selectionsort % python selection_sort.py

=== 算法性能对比 ===
基础选择版本原始数组:
: [7, 11, 9, 10, 12, 13, 8]
selection_sort1 basic:
基础选择版本: 0.005ms
基础选择版本排序结果:
: [7, 8, 9, 10, 11, 12, 13]

新建数组版本原始数组:
: [7, 11, 9, 10, 12, 13, 8]
selection_sort2 new array:
新建数组版本: 0.004ms
新建数组版本排序结果:
: [7, 8, 9, 10, 11, 12, 13]

降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selection_sort3 descending:
[13, 12, 11, 10, 9, 8, 7]
降序版本: 0.006ms
降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]

双向选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selection_sort4 bidirectional:
[7, 8, 9, 10, 11, 12, 13]
双向选择版本: 0.005ms
双向选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

堆优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selection_sort5 heap optimized:
[7, 8, 9, 10, 11, 12, 13]
堆优化版本: 0.009ms
堆优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 基础版本：标准版，原地交换，包含详细调试信息
2. 新建数组版本：无需交换，避免交换操作
3. 降序版本：展示算法灵活性，可按需排序
4. 双向版本：同时选择最大最小，效率提升
5. 堆优化版本：利用堆结构，复杂度优化
"""