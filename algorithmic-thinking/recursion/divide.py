"""
分治法 - 分而治之

分治法三个步骤：
1. 分解：将问题分解为较小的子问题
2. 求解：递归求解子问题
3. 合并：将子问题的解合并为原问题的解
"""

def merge_sort(arr):
    """
    归并排序 - 典型分治算法
    时间复杂度: O(n log n)
    空间复杂度: O(n)
    """
    if len(arr) <= 1:
        return arr
    
    # 分解
    mid = len(arr) // 2
    left = arr[:mid]
    right = arr[mid:]
    
    # 递归求解
    left = merge_sort(left)
    right = merge_sort(right)
    
    # 合并
    return merge(left, right)

def merge(left, right):
    """合并两个已排序的数组"""
    result = []
    i = j = 0
    
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def quick_sort(arr):
    """
    快速排序 - 分治算法
    时间复杂度: O(n log n) 平均，O(n^2) 最坏
    空间复杂度: O(log n)
    """
    if len(arr) <= 1:
        return arr
    
    pivot = arr[0]
    left = [x for x in arr[1:] if x < pivot]
    right = [x for x in arr[1:] if x >= pivot]
    
    return quick_sort(left) + [pivot] + quick_sort(right)

if __name__ == "__main__":
    print("=== 分治法示例 ===\n")
    
    arr = [64, 34, 25, 12, 22, 11, 90]
    
    print(f"原数组: {arr}")
    print(f"归并排序: {merge_sort(arr)}")
    print(f"快速排序: {quick_sort(arr)}")
