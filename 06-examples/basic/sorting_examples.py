"""
基础排序算法示例

常见排序算法的对比和实现
"""

def bubble_sort(arr):
    """冒泡排序，O(n²)"""
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def quick_sort(arr):
    """快速排序，O(n log n) 平均"""
    if len(arr) <= 1:
        return arr
    pivot = arr[0]
    left = [x for x in arr[1:] if x < pivot]
    right = [x for x in arr[1:] if x >= pivot]
    return quick_sort(left) + [pivot] + quick_sort(right)

def merge_sort(arr):
    """归并排序，O(n log n)"""
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    return merge(left, right)

def merge(left, right):
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

if __name__ == "__main__":
    arr = [64, 34, 25, 12, 22, 11, 90]
    print(f"原数组: {arr}")
    print(f"冒泡排序: {bubble_sort(arr.copy())}")
    print(f"快速排序: {quick_sort(arr.copy())}")
    print(f"归并排序: {merge_sort(arr.copy())}")
