# 二分搜索 - Python 实现

"""
二分搜索算法
时间复杂度: O(log n)
空间复杂度: O(1) 迭代版，O(log n) 递归版
前置条件: 数组必须有序
"""

def binary_search_iterative(arr, target):
    """
    迭代版二分搜索
    时间: O(log n), 空间: O(1)
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

def binary_search_recursive(arr, target, left=None, right=None):
    """
    递归版二分搜索
    时间: O(log n), 空间: O(log n) 递归栈
    """
    if left is None:
        left = 0
    if right is None:
        right = len(arr) - 1
    
    if left > right:
        return -1
    
    mid = (left + right) // 2
    
    if arr[mid] == target:
        return mid
    elif arr[mid] < target:
        return binary_search_recursive(arr, target, mid + 1, right)
    else:
        return binary_search_recursive(arr, target, left, mid - 1)

def find_first_occurrence(arr, target):
    """
    查找第一个等于目标值的索引
    """
    left, right = 0, len(arr) - 1
    result = -1
    
    while left <= right:
        mid = (left + right) // 2
        
        if arr[mid] == target:
            result = mid
            right = mid - 1  # 继续在左边查找
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    
    return result

def find_last_occurrence(arr, target):
    """
    查找最后一个等于目标值的索引
    """
    left, right = 0, len(arr) - 1
    result = -1
    
    while left <= right:
        mid = (left + right) // 2
        
        if arr[mid] == target:
            result = mid
            left = mid + 1  # 继续在右边查找
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    
    return result

def find_insert_position(arr, target):
    """
    查找目标值应该插入的位置（保持有序）
    如果目标存在，返回其位置
    如果不存在，返回应该插入的位置
    """
    left, right = 0, len(arr)
    
    while left < right:
        mid = (left + right) // 2
        
        if arr[mid] < target:
            left = mid + 1
        else:
            right = mid
    
    return left

if __name__ == "__main__":
    print("=" * 50)
    print("二分搜索 - Python 实现")
    print("=" * 50)
    
    # 测试用例 1：基础二分搜索
    print("\n测试 1: 基础二分搜索（迭代版）")
    arr = [1, 3, 5, 7, 9, 11, 13, 15]
    target = 7
    result = binary_search_iterative(arr, target)
    print(f"有序数组: {arr}")
    print(f"查找: {target}")
    print(f"结果: {result}")
    
    # 测试用例 2：递归版
    print("\n测试 2: 二分搜索（递归版）")
    result = binary_search_recursive(arr, target)
    print(f"查找: {target}")
    print(f"结果: {result}")
    
    # 测试用例 3：查找不存在的元素
    print("\n测试 3: 查找不存在的元素")
    target = 10
    result = binary_search_iterative(arr, target)
    print(f"查找: {target}")
    print(f"结果: {result} (未读到)")
    
    # 测试用例 4：查找重复元素中的第一个
    print("\n测试 4: 查找重复元素中的第一个")
    arr = [1, 3, 5, 5, 5, 7, 9, 11]
    target = 5
    result = find_first_occurrence(arr, target)
    print(f"有序数组: {arr}")
    print(f"查找第一个 {target}")
    print(f"结果: {result}")
    
    # 测试用例 5：查找重复元素中的最后一个
    print("\n测试 5: 查找重复元素中的最后一个")
    result = find_last_occurrence(arr, target)
    print(f"查找最后一个 {target}")
    print(f"结果: {result}")
    
    # 测试用例 6：查找插入位置
    print("\n测试 6: 查找插入位置")
    arr = [1, 3, 5, 7, 9, 11]
    targets = [4, 1, 12]
    for target in targets:
        pos = find_insert_position(arr, target)
        print(f"  {target} 应插入位置: {pos}")
    
    print("\n" + "=" * 50)
