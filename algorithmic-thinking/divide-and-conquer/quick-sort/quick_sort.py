"""
快速排序 - 分治法的高效应用

分治法三个步骤：
1. 分解：选择一个基准元素，将数组分为三部分
2. 求解：递归对左右两部分进行快速排序
3. 合并：基准元素已经在最终位置，无需额外合并

时间复杂度: O(n log n) 平均，O(n²) 最坏
空间复杂度: O(log n) 不包括递归栈

特点：
- 原地排序（不需要额外空间）
- 不稳定的排序算法
- 平均性能优于归并排序
- 缓存友好，实际性能较好
"""

def quick_sort(arr):
    """
    快速排序主函数

    参数:
        arr: 待排序的数组

    返回:
        排序后的数组
    """
    if len(arr) <= 1:
        return arr

    # 选择基准元素（这里选择第一个元素）
    pivot = arr[0]

    # 分解：将数组分为三部分
    left = [x for x in arr[1:] if x < pivot]
    middle = [pivot]
    right = [x for x in arr[1:] if x >= pivot]

    # 递归求解
    return quick_sort(left) + middle + quick_sort(right)

def quick_sort_inplace(arr, low=0, high=None):
    """
    原地快速排序（使用分割策略）

    参数:
        arr: 待排序的数组
        low: 起始位置
        high: 结束位置

    返回:
        排序后的数组
    """
    if high is None:
        high = len(arr) - 1

    if low < high:
        # 分割
        pi = partition(arr, low, high)

        # 递归排序左右两部分
        quick_sort_inplace(arr, low, pi - 1)
        quick_sort_inplace(arr, pi + 1, high)

    return arr

def partition(arr, low, high):
    """
    分割函数：使用 Hoare 分割方案

    参数:
        arr: 数组
        low: 起始位置
        high: 结束位置

    返回:
        分割点位置
    """
    pivot = arr[high]
    i = low - 1

    for j in range(low, high):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

if __name__ == "__main__":
    print("=== 快速排序 ===\n")

    # 测试用例1：随机数组（简单递归版本）
    arr1 = [64, 34, 25, 12, 22, 11, 90]
    print(f"原数组: {arr1}")
    result1 = quick_sort(arr1)
    print(f"快速排序（递归）: {result1}")
    print()

    # 测试用例2：已排序数组
    arr2 = [1, 2, 3, 4, 5]
    print(f"已排序数组: {arr2}")
    result2 = quick_sort(arr2)
    print(f"排序后: {result2}")
    print()

    # 测试用例3：反序数组
    arr3 = [5, 4, 3, 2, 1]
    print(f"反序数组: {arr3}")
    result3 = quick_sort(arr3)
    print(f"排序后: {result3}")
    print()

    # 测试用例4：包含重复元素（原地排序版本）
    arr4 = [3, 1, 4, 1, 5, 9, 2, 6]
    print(f"原数组（原地排序）: {arr4}")
    quick_sort_inplace(arr4)
    print(f"排序后: {arr4}")
