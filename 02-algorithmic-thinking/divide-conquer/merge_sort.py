"""
归并排序 - 分治法的典型应用

分治法三个步骤：
1. 分解：将数组分成两个子数组
2. 求解：递归对子数组进行归并排序
3. 合并：将两个已排序的子数组合并

时间复杂度: O(n log n)
空间复杂度: O(n)

归并排序是稳定的排序算法，适合链表排序和大数据外部排序
"""

def merge_sort(arr):
    """
    归并排序主函数

    Args:
        arr: 待排序的数组

    Returns:
        排序后的数组
    """
    if len(arr) <= 1:
        return arr

    # 分解：分成两个子数组
    mid = len(arr) // 2
    left = arr[:mid]
    right = arr[mid:]

    # 递归求解
    left = merge_sort(left)
    right = merge_sort(right)

    # 合并
    return merge(left, right)

def merge(left, right):
    """
    合并两个已排序的数组

    Args:
        left: 左侧已排序的数组
        right: 右侧已排序的数组

    Returns:
        合并后的已排序数组
    """
    result = []
    i = j = 0

    # 比较两个数组的元素，依次放入结果数组
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    # 将剩余元素添加到结果
    result.extend(left[i:])
    result.extend(right[j:])

    return result

if __name__ == "__main__":
    print("=== 归并排序 ===\n")

    # 测试用例1：随机数组
    arr1 = [64, 34, 25, 12, 22, 11, 90]
    print(f"原数组: {arr1}")
    print(f"排序后: {merge_sort(arr1)}")
    print()

    # 测试用例2：已排序数组
    arr2 = [1, 2, 3, 4, 5]
    print(f"已排序数组: {arr2}")
    print(f"排序后: {merge_sort(arr2)}")
    print()

    # 测试用例3：反序数组
    arr3 = [5, 4, 3, 2, 1]
    print(f"反序数组: {arr3}")
    print(f"排序后: {merge_sort(arr3)}")
    print()

    # 测试用例4：包含重复元素
    arr4 = [3, 1, 4, 1, 5, 9, 2, 6]
    print(f"包含重复: {arr4}")
    print(f"排序后: {merge_sort(arr4)}")
