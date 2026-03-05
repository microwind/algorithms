"""
最长递增子序列 (LIS) - 动态规划应用

问题描述：
给定一个无序整数数组，找出其中最长递增子序列的长度
子序列是指从原序列中删除零个或多个元素后得到的序列

例如：[10, 9, 2, 5, 3, 7, 101, 18]
最长递增子序列：[2, 3, 7, 101] 或 [2, 3, 7, 18]
长度都是 4

动态规划方程：
dp[i] = 1 + max(dp[j]) for all j < i and arr[j] < arr[i]
如果不存在这样的 j，则 dp[i] = 1

时间复杂度: O(n²) 基础DP，O(n log n) 优化方案
空间复杂度: O(n)

特点：
- 经典 DP 问题
- 常见的面试题
- 有多种优化方案
"""

def longest_increasing_subsequence(arr):
    """
    最长递增子序列 - 基础DP方案

    参数:
        arr: 整数数组

    返回:
        最长递增子序列的长度
    """
    if not arr:
        return 0

    n = len(arr)

    # dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
    dp = [1] * n

    for i in range(1, n):
        for j in range(i):
            # 如果 arr[j] < arr[i]，可以扩展以 arr[j] 结尾的 LIS
            if arr[j] < arr[i]:
                dp[i] = max(dp[i], dp[j] + 1)

    return max(dp)

def longest_increasing_subsequence_optimized(arr):
    """
    最长递增子序列 - 优化方案 (O(n log n))

    使用二分查找和 tails 数组
    tails[i] 表示长度为 i+1 的递增子序列的最小末尾元素

    参数:
        arr: 整数数组

    返回:
        最长递增子序列的长度
    """
    if not arr:
        return 0

    import bisect

    # tails[i] 是长度为 i+1 的递增子序列的最小末尾元素
    tails = []

    for num in arr:
        # 使用二分查找找到应该替换的位置
        pos = bisect.bisect_left(tails, num)

        if pos == len(tails):
            # 找到了更长的递增子序列
            tails.append(num)
        else:
            # 替换较大的元素，保持 tails 的最小性
            tails[pos] = num

    return len(tails)

def longest_increasing_subsequence_with_sequence(arr):
    """
    最长递增子序列 - 返回子序列本身

    参数:
        arr: 整数数组

    返回:
        (最长长度, 一个最长递增子序列)
    """
    if not arr:
        return 0, []

    n = len(arr)

    # dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
    dp = [1] * n

    # parent[i] 表示以 arr[i] 结尾的 LIS 中，前一个元素的索引
    parent = [-1] * n

    for i in range(1, n):
        for j in range(i):
            if arr[j] < arr[i] and dp[j] + 1 > dp[i]:
                dp[i] = dp[j] + 1
                parent[i] = j

    # 找到最长序列的结尾位置
    max_length = max(dp)
    max_index = dp.index(max_length)

    # 反向追踪构建最长子序列
    lis = []
    idx = max_index
    while idx != -1:
        lis.append(arr[idx])
        idx = parent[idx]

    return max_length, lis[::-1]

if __name__ == "__main__":
    print("=== 最长递增子序列 ===\n")

    # 测试用例1：基本数组
    print("1. 基本数组")
    arr1 = [10, 9, 2, 5, 3, 7, 101, 18]
    print(f"数组: {arr1}")
    print(f"LIS 长度（DP）: {longest_increasing_subsequence(arr1)}")
    print(f"LIS 长度（优化）: {longest_increasing_subsequence_optimized(arr1)}\n")

    # 测试用例2：已排序数组
    print("2. 已排序数组")
    arr2 = [1, 3, 6, 7, 9, 4, 10, 5, 8]
    print(f"数组: {arr2}")
    length, lis = longest_increasing_subsequence_with_sequence(arr2)
    print(f"LIS 长度: {length}")
    print(f"一个 LIS: {lis}\n")

    # 测试用例3：包含重复元素
    print("3. 包含重复元素")
    arr3 = [1, 3, 3, 4, 5]
    print(f"数组: {arr3}")
    print(f"LIS 长度: {longest_increasing_subsequence(arr3)}\n")

    # 测试用例4：单调递减
    print("4. 单调递减")
    arr4 = [5, 4, 3, 2, 1]
    print(f"数组: {arr4}")
    print(f"LIS 长度: {longest_increasing_subsequence(arr4)}")
