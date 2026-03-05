# 随机快速排序 - Python 实现

"""
随机快速排序
时间复杂度: O(n log n) 期望, O(n²) 最坏
空间复杂度: O(log n) 平均, O(n) 最坏
关键: 随机选择枢轴，避免最坏情况
"""

import random

def randomized_partition(arr, left, right):
    """
    原地分区，随机选择枢轴
    返回: 枢轴最终位置
    """
    # 随机选择枢轴位置
    random_idx = random.randint(left, right)
    
    # 将随机选中的元素与右端交换
    arr[random_idx], arr[right] = arr[right], arr[random_idx]
    
    pivot = arr[right]
    i = left - 1
    
    # 分区：< pivot 放左边，>= pivot 放右边
    for j in range(left, right):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    
    # 将枢轴放到正确位置
    arr[i + 1], arr[right] = arr[right], arr[i + 1]
    return i + 1

def randomized_quicksort(arr, left=None, right=None):
    """
    随机快速排序（原地排序）
    """
    if left is None:
        left = 0
    if right is None:
        right = len(arr) - 1
    
    if left < right:
        # 随机分区
        pivot_idx = randomized_partition(arr, left, right)
        
        # 递归排序左右两部分
        randomized_quicksort(arr, left, pivot_idx - 1)
        randomized_quicksort(arr, pivot_idx + 1, right)
    
    return arr

def randomized_quicksort_new_array(arr):
    """
    随机快速排序（创建新数组版本）
    时间: O(n log n) 期望, 空间: O(n log n)
    """
    if len(arr) <= 1:
        return arr
    
    # 随机选择枢轴
    pivot_idx = random.randint(0, len(arr) - 1)
    pivot = arr[pivot_idx]
    
    # 分区
    left = [x for i, x in enumerate(arr) if x < pivot and i != pivot_idx]
    middle = [x for x in arr if x == pivot]
    right = [x for i, x in enumerate(arr) if x > pivot and i != pivot_idx]
    
    # 递归排序并合并
    return randomized_quicksort_new_array(left) + middle + randomized_quicksort_new_array(right)

def randomized_select(arr, left, right, k):
    """
    随机选择：平均 O(n) 时间找第 k 小元素
    时间: O(n) 平均, O(n²) 最坏
    """
    if left == right:
        return arr[left]
    
    # 随机分区
    pivot_idx = randomized_partition(arr, left, right)
    
    # 比较 k 与 pivot 位置
    if k == pivot_idx:
        return arr[k]
    elif k < pivot_idx:
        return randomized_select(arr, left, pivot_idx - 1, k)
    else:
        return randomized_select(arr, pivot_idx + 1, right, k)

def three_way_partition(arr, left, right):
    """
    三路分区：处理重复元素更高效
    将数组分为：< pivot, == pivot, > pivot
    """
    pivot_idx = random.randint(left, right)
    pivot = arr[pivot_idx]
    
    # 初始状态：
    # [left, lt) < pivot
    # [lt, i) == pivot
    # [i, gt) 未分类
    # [gt, right] > pivot
    
    lt = left
    i = left
    gt = right + 1
    
    while i < gt:
        if arr[i] < pivot:
            arr[lt], arr[i] = arr[i], arr[lt]
            lt += 1
            i += 1
        elif arr[i] > pivot:
            gt -= 1
            arr[i], arr[gt] = arr[gt], arr[i]
        else:  # arr[i] == pivot
            i += 1
    
    return lt, gt

def randomized_quicksort_3way(arr, left=None, right=None):
    """
    三路随机快速排序
    对于有很多重复元素的数组更高效
    """
    if left is None:
        left = 0
    if right is None:
        right = len(arr) - 1
    
    if left < right:
        lt, gt = three_way_partition(arr, left, right)
        
        # 递归排序 < pivot 和 > pivot 的部分
        randomized_quicksort_3way(arr, left, lt - 1)
        randomized_quicksort_3way(arr, gt, right)
    
    return arr

if __name__ == "__main__":
    print("=" * 50)
    print("随机快速排序 - Python 实现")
    print("=" * 50)
    
    # 测试 1：基础随机快速排序（原地）
    print("\n测试 1: 随机快速排序（原地）")
    arr = [5, 2, 8, 1, 9, 3, 7, 4, 6]
    print(f"原数组: {arr}")
    sorted_arr = randomized_quicksort(arr.copy())
    print(f"排序后: {sorted_arr}")
    
    # 测试 2：随机快速排序（新数组版本）
    print("\n测试 2: 随机快速排序（新数组版本）")
    arr = [5, 2, 8, 1, 9, 3]
    print(f"原数组: {arr}")
    sorted_arr = randomized_quicksort_new_array(arr)
    print(f"排序后: {sorted_arr}")
    
    # 测试 3：随机选择第 k 小元素
    print("\n测试 3: 随机选择第 k 小元素")
    arr = [7, 2, 5, 1, 9, 3, 6, 4, 8]
    print(f"数组: {arr}")
    for k in [0, 2, 5, 8]:
        kth = randomized_select(arr.copy(), 0, len(arr) - 1, k)
        print(f"  第 {k} 小的元素: {kth}")
    
    # 测试 4：有重复元素的数组
    print("\n测试 4: 有重复元素的数组")
    arr = [5, 2, 8, 2, 9, 3, 2, 4, 8, 1]
    print(f"原数组: {arr}")
    sorted_arr = randomized_quicksort(arr.copy())
    print(f"排序后: {sorted_arr}")
    
    # 测试 5：三路分区排序
    print("\n测试 5: 三路随机快速排序")
    arr = [5, 2, 8, 2, 9, 3, 2, 4, 8, 1]
    print(f"原数组: {arr}")
    sorted_arr = randomized_quicksort_3way(arr.copy())
    print(f"排序后: {sorted_arr}")
    
    # 测试 6：性能对比（多次排序统计）
    print("\n测试 6: 性能验证")
    import time
    
    sizes = [100, 1000, 10000]
    for size in sizes:
        arr = [random.randint(0, 1000) for _ in range(size)]
        arr_copy = arr.copy()
        
        start = time.time()
        randomized_quicksort(arr_copy)
        elapsed = time.time() - start
        
        print(f"  排序 {size} 个元素: {elapsed*1000:.2f} ms")
    
    print("\n" + "=" * 50)
