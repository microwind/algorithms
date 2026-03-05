"""
二分查找 - 分治法的查询应用

二分查找的三个步骤：
1. 分解：在中间位置检查元素
2. 求解：递归地在左半部分或右半部分查找
3. 合并：返回查找结果

前置条件：数组必须已排序

时间复杂度: O(log n)
空间复杂度: O(1) 迭代版本，O(log n) 递归版本

特点：
- 高效的查找算法
- 不需要额外空间（迭代版本）
- 要求输入有序
"""

def binary_search(arr, target):
    """
    二分查找（递归版本）

    参数:
        arr: 已排序的数组
        target: 查找的目标值

    返回:
        目标值的索引，如果不存在返回 -1
    """
    def search_helper(left, right):
        if left > right:
            return -1

        mid = (left + right) // 2

        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            return search_helper(mid + 1, right)
        else:
            return search_helper(left, mid - 1)

    return search_helper(0, len(arr) - 1)

def binary_search_iterative(arr, target):
    """
    二分查找（迭代版本）

    参数:
        arr: 已排序的数组
        target: 查找的目标值

    返回:
        目标值的索引，如果不存在返回 -1
    """
    left, right = 0, len(arr) - 1

    # 当搜索范围不为空时, 继续查找
    while left <= right:
        mid = (left + right) // 2

        # 检查中间元素是否是目标值
        if arr[mid] == target:
            return mid
        # 如果中间元素小于目标值, 目标在右半部分
        elif arr[mid] < target:
            left = mid + 1
        # 如果中间元素大于目标值, 目标在左半部分
        else:
            right = mid - 1

    return -1

def binary_search_left(arr, target):
    """
    查找第一个 >= target 的元素位置（左边界）

    参数:
        arr: 已排序的数组
        target: 查找的目标值

    返回:
        第一个 >= target 的索引，如果不存在返回 -1
    """
    left, right = 0, len(arr) - 1
    result = -1

    while left <= right:
        mid = (left + right) // 2

        if arr[mid] >= target:
            result = mid
            right = mid - 1
        else:
            left = mid + 1

    return result

def binary_search_right(arr, target):
    """
    查找最后一个 <= target 的元素位置（右边界）

    参数:
        arr: 已排序的数组
        target: 查找的目标值

    返回:
        最后一个 <= target 的索引，如果不存在返回 -1
    """
    left, right = 0, len(arr) - 1
    result = -1

    while left <= right:
        mid = (left + right) // 2

        if arr[mid] <= target:
            result = mid
            left = mid + 1
        else:
            right = mid - 1

    return result

if __name__ == "__main__":
    print("=== 二分查找 ===\n")

    arr = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]
    print(f"数组: {arr}\n")

    # 测试用例1：基本查找（递归）
    print("1. 递归版本:")
    print(f"  查找 7: {binary_search(arr, 7)}")  # 3
    print(f"  查找 20: {binary_search(arr, 20)}")  # -1
    print()

    # 测试用例2：迭代版本
    print("2. 迭代版本:")
    print(f"  查找 9: {binary_search_iterative(arr, 9)}")  # 4
    print(f"  查找 2: {binary_search_iterative(arr, 2)}")  # -1
    print()

    # 测试用例3：查找左边界
    arr_dup = [1, 2, 2, 2, 3, 4, 5, 5, 5, 6]
    print(f"3. 查找边界 (数组: {arr_dup}):")
    print(f"  左边界 2: {binary_search_left(arr_dup, 2)}")  # 1
    print(f"  右边界 5: {binary_search_right(arr_dup, 5)}")  # 8
    print()

    # 测试用例4：查找不存在的元素
    print("4. 查找不存在的元素:")
    print(f"  查找 100: {binary_search_iterative(arr, 100)}")  # -1
    print(f"  查找 0: {binary_search_iterative(arr, 0)}")  # -1
