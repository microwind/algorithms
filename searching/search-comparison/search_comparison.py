"""
搜索算法综合示例
对比不同搜索算法的性能特点
"""
import time


def linear_search(arr, target):
    """线性查找 - O(n)"""
    for i, val in enumerate(arr):
        if val == target:
            return i
    return -1


def binary_search(arr, target):
    """二分查找 - O(log n)，要求数组有序"""
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
    """跳跃查找 - O(√n)，要求数组有序"""
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
    """指数查找 - O(log n)，要求数组有序"""
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


# 测试示例
if __name__ == "__main__":
    print("=" * 60)
    print("搜索算法综合对比")
    print("=" * 60)
    
    # 创建测试数据
    n = 10000
    sorted_arr = list(range(n))
    unsorted_arr = list(range(n, 0, -1))  # 逆序
    
    target = 9999
    
    print(f"\n数组大小: {n}")
    print(f"查找目标: {target}")
    
    print("\n有序数组搜索算法对比:")
    print("-" * 60)
    
    # 二分查找
    start = time.time()
    result = binary_search(sorted_arr, target)
    time_binary = (time.time() - start) * 1000
    print(f"二分查找:     索引={result}, 时间={time_binary:.4f}ms")
    
    # 跳跃查找
    start = time.time()
    result = jump_search(sorted_arr, target)
    time_jump = (time.time() - start) * 1000
    print(f"跳跃查找:     索引={result}, 时间={time_jump:.4f}ms")
    
    # 指数查找
    start = time.time()
    result = exponential_search(sorted_arr, target)
    time_exp = (time.time() - start) * 1000
    print(f"指数查找:     索引={result}, 时间={time_exp:.4f}ms")
    
    print("\n无序数组搜索:")
    print("-" * 60)
    
    # 线性查找（无序数组）
    start = time.time()
    result = linear_search(unsorted_arr, target)
    time_linear = (time.time() - start) * 1000
    print(f"线性查找:     索引={result}, 时间={time_linear:.4f}ms")
    
    print("\n算法复杂度总结:")
    print("  线性查找:     O(n)")
    print("  二分查找:     O(log n) - 需有序")
    print("  跳跃查找:     O(√n) - 需有序")
    print("  指数查找:     O(log n) - 需有序")
    print("  插值查找:     O(log log n) - 需均匀分布")
    print("  哈希查找:     O(1) - 需额外空间")
