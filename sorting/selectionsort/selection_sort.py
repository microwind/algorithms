"""
Copyright © https://github.com/microwind All rights reserved.

@author: jarryli@gmail.com
@version: 1.0
"""

"""
选择排序算法实现
提供四种不同的实现方式，适合不同场景和性能需求
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
    选择排序基础版本
    
    算法原理：
    1. 将数组分为两部分：左侧已排序区域，右侧待排序区域
    2. 每次从待排序区域中选择最小元素
    3. 将最小元素与待排序区域的第一个元素交换
    4. 重复以上过程，直到所有元素排序完成
    
    生活类比：就像在队伍中挑选最矮的人站到最前面，
    然后在剩下的人中再挑选最矮的站到第二个位置，依此类推
    
    时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
    空间复杂度：O(1) - 只使用常数个额外变量
    稳定性：不稳定 - 交换可能改变相等元素的相对位置
    
    Args:
        arr (list): 待排序的数字列表
    Returns:
        list: 排序后的列表
    """
    print('selection_sort1 basic:')
    n = len(arr)
    # 外循环：控制排序轮数，每轮确定一个最小值的位置
    for i in range(n - 1):
        min_index = i  # 记录最小元素的索引
        
        # 内循环：在未排序区域中查找最小元素
        for j in range(i + 1, n):
            # 关键点：找到更小的元素，更新最小值索引
            if arr[j] < arr[min_index]:
                min_index = j
        
        # 交换最小元素到当前轮次的起始位置
        if min_index != i:
            # Python特点：元组解包交换
            arr[i], arr[min_index] = arr[min_index], arr[i]
    
    print(arr)
    return arr

def selection_sort2(arr):
    """
    选择排序降序版本
    
    算法思路：
    与基础版本相反，每次选择最大元素
    将最大元素与待排序区域的第一个元素交换
    
    时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
    空间复杂度：O(1) - 只使用常数个额外变量
    稳定性：不稳定 - 交换可能改变相等元素的相对位置
    
    Args:
        arr (list): 待排序的数字列表
    Returns:
        list: 排序后的列表
    """
    print('selection_sort2 descending:')
    n = len(arr)
    # 外循环：控制排序轮数，每轮确定一个最大值的位置
    for i in range(n - 1):
        max_index = i  # 记录最大元素的索引
        
        # 内循环：在未排序区域中查找最大元素
        for j in range(i + 1, n):
            # 关键点：找到更大的元素，更新最大值索引
            if arr[j] > arr[max_index]:
                max_index = j
        
        # 交换最大元素到当前轮次的起始位置
        if max_index != i:
            # Python特点：元组解包交换
            arr[i], arr[max_index] = arr[max_index], arr[i]
    
    print(arr)
    return arr

def selection_sort3(arr):
    """
    选择排序优化版本 - 双向选择
    
    优化思路：
    每轮同时选择最小和最大元素
    将最小元素放到左侧，最大元素放到右侧
    减少排序轮数，提高效率
    
    优化效果：
    - 减少了排序轮数，从n轮减少到n/2轮
    - 每轮需要进行两次查找，但总体效率提升
    
    时间复杂度：O(n²)，空间复杂度：O(1)
    稳定性：不稳定 - 交换可能改变相等元素的相对位置
    
    Args:
        arr (list): 待排序的数字列表
    Returns:
        list: 排序后的列表
    """
    print('selection_sort3 bidirectional:')
    n = len(arr)
    left, right = 0, n - 1
    
    # 外循环：控制排序轮数，每轮确定最小和最大值的位置
    while left < right:
        min_index = left
        max_index = left
        
        # 内循环：在未排序区域中查找最小和最大元素
        for i in range(left, right + 1):
            # 关键点：同时查找最小和最大元素
            if arr[i] < arr[min_index]:
                min_index = i
            if arr[i] > arr[max_index]:
                max_index = i
        
        # 交换最小元素到左侧
        if min_index != left:
            arr[left], arr[min_index] = arr[min_index], arr[left]
        
        # 优化点：如果最大元素原本在left位置，经过交换后位置变为min_index
        if max_index == left:
            max_index = min_index
        
        # 交换最大元素到右侧
        if max_index != right:
            arr[right], arr[max_index] = arr[max_index], arr[right]
        
        left += 1
        right -= 1
    
    print(arr)
    return arr

def selection_sort4(arr):
    """
    选择排序 - 堆优化版本
    
    算法思路：
    利用堆的性质来快速找到最大/最小元素
    每次从堆顶取出最大/最小元素
    重新调整堆结构
    
    时间复杂度：O(n log n)，空间复杂度：O(1)
    稳定性：不稳定 - 交换可能改变相等元素的相对位置
    
    Args:
        arr (list): 待排序的数字列表
    Returns:
        list: 排序后的列表
    """
    print('selection_sort4 heap optimized:')
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
        # 关键点：交换堆顶元素（最大）与末尾元素
        arr[0], arr[i] = arr[i], arr[0]
        
        # 重新调整堆
        heapify(arr, i, 0)
    
    print(arr)
    return arr

# ==================== 算法测试和性能对比 ====================

# 测试1：基础选择版本
performance_test(selection_sort1, test_data, '基础选择版本')

# 测试2：降序版本
performance_test(selection_sort2, test_data, '降序版本')

# 测试3：双向选择版本
performance_test(selection_sort3, test_data, '双向选择版本')

# 测试4：堆优化版本
performance_test(selection_sort4, test_data, '堆优化版本')

print('=== 算法对比总结 ===')
print('1. 基础版本：简单易懂，适合学习算法原理')
print('2. 降序版本：展示算法灵活性，可按需排序')
print('3. 双向版本：同时选择最大最小，效率提升')
print('4. 堆优化版本：利用堆结构，复杂度优化')

"""
打印结果
jarry@Mac selectionsort % python selection_sort.py
基础选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selection_sort1 basic:
[7, 8, 9, 10, 11, 12, 13]
基础选择版本: 0.006ms
基础选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selection_sort2 descending:
[13, 12, 11, 10, 9, 8, 7]
降序版本: 0.006ms
降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]

双向选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selection_sort3 bidirectional:
[7, 8, 9, 10, 11, 12, 13]
双向选择版本: 0.004ms
双向选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

堆优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selection_sort4 heap optimized:
[7, 8, 9, 10, 11, 12, 13]
堆优化版本: 0.006ms
堆优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 基础版本：简单易懂，适合学习算法原理
2. 降序版本：展示算法灵活性，可按需排序
3. 双向版本：同时选择最大最小，效率提升
4. 堆优化版本：利用堆结构，复杂度优化
"""
