"""
Copyright © https://github.com/microwind All rights reserved.

@author: jarryli@gmail.com
@version: 1.0
"""

"""
归并排序算法实现
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

# 测试数据：
test_data = [7, 11, 9, 10, 12, 13, 8]

def merge_sort1(arr):
    """
    归并排序基础版本 - 递归实现（基于pop操作）
    
    算法原理：
    1. 分治法，递归分割后合并
    2. 使用pop(0)操作获取首元素，简化代码逻辑
    3. 递归处理左右子数组，然后合并结果
    
    优化效果：
    - 代码逻辑简洁易懂
    - 充分利用Python列表的pop操作
    - 函数式编程风格
    
    时间复杂度：O(n log n)
    空间复杂度：O(n) - 需要额外空间存储临时数组
    稳定性：稳定 - 合并过程中保持相等元素的相对位置
    """
    print("mergeSort1 recursive (pop-based):")
    
    # 归并排序：分治法，递归分割后合并
    result = arr
    if len(arr) > 1:
        # 第一步：分割数组
        # 关键点：使用整数除法计算中间位置，将数组分为两半
        mid = len(arr) // 2
        left = arr[:mid]
        right = arr[mid:]
        
        # 第二步：递归排序左右子数组
        # 关键点：分别对左右两部分进行递归排序
        left = merge_sort1(left)
        right = merge_sort1(right)
        
        # 第三步：合并两个已排序数组
        # 关键点：创建新数组存储合并结果
        result = []
        while len(left) > 0 and len(right) > 0:
            # 比较两个数组的首元素，取较小的添加到结果中
            # 关键点：使用pop(0)获取并移除首元素
            if left[0] < right[0]:
                result.append(left[0])
                left.pop(0)  # Python特点：pop(0)移除并返回首元素
            else:
                result.append(right[0])
                right.pop(0)  # Python特点：pop(0)移除并返回首元素
        
        # 第四步：添加剩余元素
        # 关键点：将未处理完的数组元素直接添加到结果数组
        for i in left:
            result.append(i)
        for i in right:
            result.append(i)
    
    print(result)
    return result

def merge_sort2(arr):
    """
    归并排序原地版本 - 直接修改原数组
    
    算法原理：
    1. 分治法，递归分割后在原数组合并
    2. 避免创建新数组，直接在原数组上操作
    3. 使用索引操作，提高空间效率
    
    优化效果：
    - 空间复杂度更低
    - 减少内存分配
    - 原地操作，提高缓存效率
    
    时间复杂度：O(n log n)
    空间复杂度：O(log n) - 仅递归栈空间
    稳定性：稳定 - 合并过程中保持相等元素的相对位置
    """
    print("mergeSort2 in-place:")
    
    # 归并排序原地版本：直接修改原数组
    if len(arr) > 1:
        # 第一步：分割数组
        # 关键点：使用整数除法计算中间位置
        mid = len(arr) // 2
        left_arr = arr[:mid]
        right_arr = arr[mid:]

        # 第二步：递归排序左右子数组
        # 关键点：分别对左右两部分进行递归排序
        merge_sort2(left_arr)
        merge_sort2(right_arr)

        # 第三步：初始化合并指针
        # 关键点：i指向左数组，j指向右数组，k指向原数组
        i = j = k = 0

        # 第四步：合并左右子数组到原数组
        # 关键点：将两个有序子数组合并到原数组的对应位置
        while i < len(left_arr) and j < len(right_arr):
            if left_arr[i] < right_arr[j]:
                arr[k] = left_arr[i]
                i += 1
            else:
                arr[k] = right_arr[j]
                j += 1
            k += 1

        # 第五步：复制左侧剩余元素
        # 关键点：左数组可能还有未处理的元素
        while i < len(left_arr):
            arr[k] = left_arr[i]
            i += 1
            k += 1

        # 第六步：复制右侧剩余元素
        # 关键点：右数组可能还有未处理的元素
        while j < len(right_arr):
            arr[k] = right_arr[j]
            j += 1
            k += 1
    
    print(arr)
    return arr

def merge_sort3(arr):
    """
    归并排序 - 迭代版本
    
    算法思路：
    使用迭代方式代替递归，避免递归栈开销
    从小规模合并开始，逐步扩大合并规模
    
    优化效果：
    - 避免了递归调用的开销
    - 更好的缓存局部性
    
    时间复杂度：O(n log n)
    空间复杂度：O(n) - 需要临时数组
    稳定性：稳定 - 合并过程中保持相等元素的相对位置
    """
    print("mergeSort3 iterative:")
    
    def merge(arr, temp, left, mid, right):
        """合并两个有序子数组"""
        i = left  # 左子数组索引
        j = mid + 1  # 右子数组索引
        k = left  # 临时数组索引
        
        # 合并到临时数组
        while i <= mid and j <= right:
            if arr[i] <= arr[j]:
                temp[k] = arr[i]
                i += 1
            else:
                temp[k] = arr[j]
                j += 1
            k += 1
        
        # 复制左子数组剩余元素
        while i <= mid:
            temp[k] = arr[i]
            i += 1
            k += 1
        
        # 复制右子数组剩余元素
        while j <= right:
            temp[k] = arr[j]
            j += 1
            k += 1
        
        # 将临时数组复制回原数组
        for i in range(left, right + 1):
            arr[i] = temp[i]
    
    n = len(arr)
    temp = [0] * n
    
    # 迭代合并，步长从1开始翻倍
    size = 1
    while size < n:
        for left in range(0, n - size, 2 * size):
            mid = left + size - 1
            right = min(left + 2 * size - 1, n - 1)
            merge(arr, temp, left, mid, right)
        size *= 2
    
    print(arr)
    return arr

def merge_sort4(arr):
    """
    归并排序 - 自底向上版本
    
    算法思路：
    先将数组分成单个元素，然后两两合并
    逐步扩大合并规模，直到整个数组有序
    
    优化效果：
    - 更好的内存访问模式
    - 适合外部排序（处理大数据）
    
    时间复杂度：O(n log n)
    空间复杂度：O(n) - 需要临时数组
    稳定性：稳定 - 合并过程中保持相等元素的相对位置
    """
    print("mergeSort4 bottom-up:")
    
    def merge(arr, temp, left, mid, right):
        """合并两个相邻的有序子数组"""
        i = left
        j = mid
        k = left
        
        # 合并两个有序子数组到临时数组
        while i < mid and j <= right:
            if arr[i] <= arr[j]:
                temp[k] = arr[i]
                i += 1
            else:
                temp[k] = arr[j]
                j += 1
            k += 1
        
        # 复制剩余元素
        while i < mid:
            temp[k] = arr[i]
            i += 1
            k += 1
        while j <= right:
            temp[k] = arr[j]
            j += 1
            k += 1
        
        # 复制回原数组
        for i in range(left, right + 1):
            arr[i] = temp[i]
    
    n = len(arr)
    temp = [0] * n
    
    # 自底向上合并
    width = 1
    while width < n:
        for i in range(0, n, 2 * width):
            left = i
            mid = min(i + width, n)
            right = min(i + 2 * width, n)
            
            if mid < right:
                merge(arr, temp, left, mid, right - 1)
        width *= 2
    
    print(arr)
    return arr

# ==================== 算法测试和性能对比 ====================

def merge_sort5(arr):
    """
    归并排序 - 非递归合并版本
    
    算法思路：
    使用非递归方式进行合并操作，避免递归调用
    通过迭代方式处理合并过程，提高内存效率
    
    优化效果：
    - 避免递归栈开销
    - 更好的内存访问模式
    - 适合大数据处理
    
    时间复杂度：O(n log n)
    空间复杂度：O(n) - 需要临时数组
    稳定性：稳定 - 合并过程中保持相等元素的相对位置
    """
    print("mergeSort5 non-recursive merge:")
    
    def merge_non_recursive(arr, temp, left, mid, right):
        """非递归合并两个有序子数组"""
        # 步骤1：初始化索引指针
        # 关键点：i指向左子数组，j指向右子数组，k指向临时数组
        i = left      # 左子数组索引
        j = mid + 1   # 右子数组索引
        k = left      # 临时数组索引
        
        # 步骤2：合并到临时数组
        # 关键点：按顺序合并两个有序子数组
        while i <= mid and j <= right:
            if arr[i] <= arr[j]:
                temp[k] = arr[i]
                i += 1
            else:
                temp[k] = arr[j]
                j += 1
            k += 1
        
        # 步骤3：复制左子数组剩余元素
        # 关键点：左子数组可能还有未处理的元素
        while i <= mid:
            temp[k] = arr[i]
            i += 1
            k += 1
        
        # 步骤4：复制右子数组剩余元素
        # 关键点：右子数组可能还有未处理的元素
        while j <= right:
            temp[k] = arr[j]
            j += 1
            k += 1
        
        # 步骤5：将临时数组复制回原数组
        # 关键点：使用循环逐个复制，确保数据正确性
        # Python特点：也可以使用切片赋值，但循环更直观
        for index in range(left, right + 1):
            arr[index] = temp[index]
    
    n = len(arr)
    if n <= 1:
        return arr
    
    # 步骤1：创建临时数组
    # 关键点：临时数组用于存储合并过程中的中间结果
    temp = [0] * n
    
    # 步骤2：非递归合并过程
    # 关键点：通过迭代方式模拟递归的合并过程
    size = 1
    while size < n:
        # 步骤3：处理所有相邻的子数组对
        # 关键点：每次处理两个大小为size的相邻子数组
        for left in range(0, n - size, 2 * size):
            # 步骤4：计算当前合并的边界
            # 关键点：确定左子数组 [left, mid] 和右子数组 [mid+1, right]
            mid = left + size - 1
            right = left + 2 * size - 1
            if right >= n:
                right = n - 1
            
            # 步骤5：执行非递归合并
            # 关键点：使用迭代方式合并两个有序子数组
            merge_non_recursive(arr, temp, left, mid, right)
        
        size *= 2
    
    print(arr)
    return arr

def main():
    # 测试1：递归版本（基于pop操作）
    performance_test(merge_sort1, test_data, "递归版本（基于pop操作）")

    # 测试2：原地合并版本
    performance_test(merge_sort2, test_data, "原地合并版本")

    # 测试3：迭代版本
    performance_test(merge_sort3, test_data, "迭代版本")

    # 测试4：自底向上版本
    performance_test(merge_sort4, test_data, "自底向上版本")
    
    # 测试5：非递归合并版本
    performance_test(merge_sort5, test_data, "非递归合并版本")

    print("=== 算法对比总结 ===")
    print("1. 递归版本（基于pop操作）：代码简洁，利用Python特性")
    print("2. 原地版本：空间优化，减少内存使用")
    print("3. 迭代版本：避免递归，性能稳定")
    print("4. 底向上版本：适合大数据，外部排序")
    print("5. 非递归合并版本：迭代合并，高效内存")

if __name__ == '__main__':
    main()

"""
jarry@Mac mergesort % python merge_sort.py 
递归版本（基于pop操作）原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort1 recursive (pop-based):
mergeSort1 recursive (pop-based):
mergeSort1 recursive (pop-based):
[7]
mergeSort1 recursive (pop-based):
mergeSort1 recursive (pop-based):
[11]
mergeSort1 recursive (pop-based):
[9]
[9, 11]
[7, 9, 11]
mergeSort1 recursive (pop-based):
mergeSort1 recursive (pop-based):
mergeSort1 recursive (pop-based):
[10]
mergeSort1 recursive (pop-based):
[12]
[10, 12]
mergeSort1 recursive (pop-based):
mergeSort1 recursive (pop-based):
[13]
mergeSort1 recursive (pop-based):
[8]
[8, 13]
[8, 10, 12, 13]
[7, 8, 9, 10, 11, 12, 13]
递归版本（基于pop操作）: 0.032ms
递归版本（基于pop操作）排序结果: [7, 11, 9, 10, 12, 13, 8]

原地合并版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort2 in-place:
mergeSort2 in-place:
mergeSort2 in-place:
[7]
mergeSort2 in-place:
mergeSort2 in-place:
[11]
mergeSort2 in-place:
[9]
[9, 11]
[7, 9, 11]
mergeSort2 in-place:
mergeSort2 in-place:
mergeSort2 in-place:
[10]
mergeSort2 in-place:
[12]
[10, 12]
mergeSort2 in-place:
mergeSort2 in-place:
[13]
mergeSort2 in-place:
[8]
[8, 13]
[8, 10, 12, 13]
[7, 8, 9, 10, 11, 12, 13]
原地合并版本: 0.026ms
原地合并版本排序结果: [7, 8, 9, 10, 11, 12, 13]

迭代版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort3 iterative:
[7, 8, 9, 10, 11, 12, 13]
迭代版本: 0.010ms
迭代版本排序结果: [7, 8, 9, 10, 11, 12, 13]

自底向上版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort4 bottom-up:
[7, 8, 9, 10, 11, 12, 13]
自底向上版本: 0.008ms
自底向上版本排序结果: [7, 8, 9, 10, 11, 12, 13]

非递归合并版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort5 non-recursive merge:
[7, 8, 9, 10, 11, 12, 13]
非递归合并版本: 0.007ms
非递归合并版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归版本（基于pop操作）：代码简洁，利用Python特性
2. 原地版本：空间优化，减少内存使用
3. 迭代版本：避免递归，性能稳定
4. 底向上版本：适合大数据，外部排序
5. 非递归合并版本：迭代合并，高效内存
"""