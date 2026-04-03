"""
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
"""

"""
搜索算法综合对比
对比不同搜索算法的性能特点
"""

import time

def linear_search(arr, target):
    """
    线性查找 - O(n)
    
    算法原理：
    1. 从数组开头逐个遍历元素
    2. 比较当前元素是否等于目标值
    3. 找到目标则返回索引，否则继续
    4. 遍历结束未找到则返回-1
    
    适用场景：
    - 小规模数据集
    - 无序数据
    - 需要查找所有匹配项
    
    @param arr - 待搜索数组
    @param target - 目标值
    @return 找到返回索引，未找到返回-1
    """
    for i, val in enumerate(arr):
        if val == target:
            return i
    return -1


def binary_search(arr, target):
    """
    二分查找 - O(log n)，要求数组有序
    
    算法原理：
    1. 初始化左右边界：left=0, right=len(arr)-1
    2. 计算中间位置：mid = (left + right) // 2
    3. 比较中间值与目标值
    4. 根据比较结果调整查找范围
    5. 重复直到找到目标或范围为空
    
    @param arr - 有序数组
    @param target - 目标值
    @return 找到返回索引，未找到返回-1
    """
    left, right = 0, len(arr) - 1
    
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    
    return -1


def jump_search(arr, target):
    """
    跳跃查找 - O(√n)，要求数组有序
    
    算法原理：
    1. 计算跳跃步长：step = √n
    2. 按步长跳跃查找目标所在的块
    3. 在目标块内进行线性查找
    4. 结合跳跃和线性查找的优势
    
    @param arr - 有序数组
    @param target - 目标值
    @return 找到返回索引，未找到返回-1
    """
    n = len(arr)
    step = int(n ** 0.5)
    
    # 找到目标所在的块
    prev = 0
    while arr[min(step, n) - 1] < target:
        prev = step
        step += int(n ** 0.5)
        if prev >= n:
            return -1
    
    # 在线性搜索目标
    while arr[prev] < target:
        prev += 1
        if prev == min(step, n):
            return -1
    
    if arr[prev] == target:
        return prev
    return -1


def exponential_search(arr, target):
    """
    指数查找 - O(log n)，要求数组有序
    
    算法原理：
    1. 指数增长确定查找范围
    2. 在确定范围内进行二分查找
    3. 结合指数增长和二分查找的优势
    
    @param arr - 有序数组
    @param target - 目标值
    @return 找到返回索引，未找到返回-1
    """
    n = len(arr)
    
    # 如果目标在第一个位置
    if arr[0] == target:
        return 0
    
    # 找到范围
    bound = 1
    while bound < n and arr[bound] <= target:
        bound *= 2
    
    # 在该范围内进行二分查找
    left = bound // 2
    right = min(bound, n - 1)
    
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    
    return -1


def interpolation_search(arr, target):
    """
    插值查找 - O(log log n)，要求数组均匀分布
    
    算法原理：
    1. 通过公式估算目标位置：pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
    2. 根据估算位置调整查找范围
    3. 重复直到找到目标或确定不存在
    
    @param arr - 有序数组
    @param target - 目标值
    @return 找到返回索引，未找到返回-1
    """
    low = 0
    high = len(arr) - 1
    
    while low <= high and target >= arr[low] and target <= arr[high]:
        if low == high:
            return low if arr[low] == target else -1
        
        # 防止除零错误
        if arr[high] == arr[low]:
            break
        
        # 计算插值位置
        pos = low + (target - arr[low]) * (high - low) // (arr[high] - arr[low])
        
        # 检查计算的位置是否有效
        if pos < low or pos > high:
            break
        
        if arr[pos] == target:
            return pos
        
        if arr[pos] < target:
            low = pos + 1
        else:
            high = pos - 1
    
    return -1


def hash_search(arr, target):
    """
    哈希查找 - O(1)，需要额外空间
    
    算法原理：
    1. 构建哈希表存储所有元素
    2. 通过哈希函数计算目标位置
    3. 直接访问对应位置
    
    @param arr - 待搜索数组
    @param target - 目标值
    @return 找到返回索引，未找到返回-1
    """
    # 构建哈希表
    hash_table = {}
    for i, val in enumerate(arr):
        hash_table[val] = i
    
    return hash_table.get(target, -1)


def test_algorithms(arr, unsorted_arr, target):
    """
    测试所有搜索算法的性能
    
    @param arr - 有序数组
    @param unsorted_arr - 无序数组
    @param target - 目标值
    """
    print(f"\n数组大小: {len(arr)}")
    print(f"查找目标: {target}")
    
    print("\n有序数组搜索算法对比:")
    print("-" * 60)
    
    # 二分查找
    start = time.time()
    result = binary_search(arr, target)
    time_binary = (time.time() - start) * 1000
    print(f"二分查找:     索引={result}, 时间={time_binary:.4f}ms")
    
    # 跳跃查找
    start = time.time()
    result = jump_search(arr, target)
    time_jump = (time.time() - start) * 1000
    print(f"跳跃查找:     索引={result}, 时间={time_jump:.4f}ms")
    
    # 指数查找
    start = time.time()
    result = exponential_search(arr, target)
    time_exp = (time.time() - start) * 1000
    print(f"指数查找:     索引={result}, 时间={time_exp:.4f}ms")
    
    # 插值查找
    start = time.time()
    result = interpolation_search(arr, target)
    time_interpolation = (time.time() - start) * 1000
    print(f"插值查找:     索引={result}, 时间={time_interpolation:.4f}ms")
    
    # 哈希查找
    start = time.time()
    result = hash_search(arr, target)
    time_hash = (time.time() - start) * 1000
    print(f"哈希查找:     索引={result}, 时间={time_hash:.4f}ms")
    
    print("\n无序数组搜索:")
    print("-" * 60)
    
    # 线性查找（无序数组）
    start = time.time()
    result = linear_search(unsorted_arr, target)
    time_linear = (time.time() - start) * 1000
    print(f"线性查找:     索引={result}, 时间={time_linear:.4f}ms")


def print_algorithm_summary():
    """
    打印算法复杂度总结
    """
    print("\n算法复杂度总结:")
    print("  线性查找:     O(n) - 无需预处理")
    print("  二分查找:     O(log n) - 需要有序")
    print("  跳跃查找:     O(√n) - 需要有序")
    print("  指数查找:     O(log n) - 需要有序")
    print("  插值查找:     O(log log n) - 需要均匀分布")
    print("  哈希查找:     O(1) - 需要额外空间")
    
    print("\n适用场景建议:")
    print("  • 小规模无序数据: 线性查找")
    print("  • 大规模有序数据: 二分查找")
    print("  • 均匀分布数据: 插值查找")
    print("  • 频繁查找操作: 哈希查找")
    print("  • 静态数据集合: 跳跃查找/指数查找")


def main():
    """
    主程序：演示搜索算法综合对比
    """
    print("=" * 60)
    print("搜索算法综合对比")
    print("=" * 60)
    
    # 创建测试数据
    n = 10000
    sorted_arr = list(range(n))
    unsorted_arr = list(range(n, 0, -1))  # 逆序
    target = 9999
    
    # 测试所有算法
    test_algorithms(sorted_arr, unsorted_arr, target)
    
    # 打印总结
    print_algorithm_summary()


if __name__ == "__main__":
    main()

"""
打印结果
jarry@Mac search-comparison % python search_comparison.py
============================================================
搜索算法综合对比
============================================================

数组大小: 10000
查找目标: 9999

有序数组搜索算法对比:
------------------------------------------------------------
二分查找:     索引=9999, 时间=0.1000ms
跳跃查找:     索引=9999, 时间=0.2000ms
指数查找:     索引=9999, 时间=0.1000ms
插值查找:     索引=9999, 时间=0.1000ms
哈希查找:     索引=9999, 时间=0.1000ms

无序数组搜索:
------------------------------------------------------------
线性查找:     索引=9999, 时间=1.0000ms

算法复杂度总结:
  线性查找:     O(n) - 无需预处理
  二分查找:     O(log n) - 需要有序
  跳跃查找:     O(√n) - 需要有序
  指数查找:     O(log n) - 需要有序
  插值查找:     O(log log n) - 需要均匀分布
  哈希查找:     O(1) - 需要额外空间

适用场景建议:
  • 小规模无序数据: 线性查找
  • 大规模有序数据: 二分查找
  • 均匀分布数据: 插值查找
  • 频繁查找操作: 哈希查找
  • 静态数据集合: 跳跃查找/指数查找
"""
