"""
分治与递归（Divide and Conquer）- 大问题分解的艺术

分治法的三个步骤：
1. 分解（Divide）：将原问题分解为若干子问题
   - 子问题是原问题的较小实例
   - 形式和原问题相同但规模更小

2. 递归求解（Conquer）：递归地求解每个子问题
   - 若子问题仍然过大，继续分解
   - 直到问题规模足够小可直接求解

3. 合并（Combine）：将子问题的答案合并得到原问题的解
   - 根据子问题的解构造原问题的解

关键特性：
- 层级结构清晰：形成递归树
- 子问题相对独立：处理互不影响
- 合并相对简单：如何将子问题答案组合

时间复杂度分析：
使用主定理（Master Theorem）分析 T(n) = aT(n/b) + f(n)
- a：子问题个数
- n/b：每个子问题的规模
- f(n)：分解和合并的代价

常见应用：
- 排序：归并排序 O(n log n)、快速排序 O(n log n)
- 搜索：二分搜索 O(log n)
- 树/图算法：二叉树遍历、图连通性等
- 数值计算：矩阵乘法、傅里叶变换等
- 几何算法：最近点对问题等
"""

# 问题 1: 归并排序（Merge Sort）
def merge_sort(arr):
    """
    归并排序 - 分治的经典排序算法
    
    流程：
    1. 分解：将数组对半分割直到单元素
    2. 合并：比较相邻的排好序的子数组，合并成一个更大的有序数组
    
    时间复杂度：O(n log n)（最好、平均、最坏都是）
    空间复杂度：O(n)（需要临时存储合并的数据）
    
    稳定性：稳定的排序算法（相等元素保持原相对位置）
    
    参数:
        arr: 待排序的数组
    
    返回:
        排好序的数组
    
    示例:
        merge_sort([38, 27, 43, 3, 9]) → [3, 9, 27, 38, 43]
    """
    # 基础情况：数组长度 <= 1 时已有序
    if len(arr) <= 1:
        return arr
    
    # 步骤 1：分解 - 找中点分割数组
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    
    # 步骤 2：递归求解 - 对左右两个子数组分别排序
    left_sorted = merge_sort(left_half)
    right_sorted = merge_sort(right_half)
    
    # 步骤 3：合并 - 将两个有序子数组合并为一个有序数组
    return merge(left_sorted, right_sorted)

def merge(left, right):
    """
    合并两个有序数组
    
    关键思路：
    - 使用两个指针分别指向两个数组的开头
    - 每次比较两个指针指向的元素，选择较小的放入结果
    - 直到一个数组处理完，将另一个数组的剩余元素追加
    
    时间复杂度：O(m + n)（m, n 是两个数组的长度）
    """
    result = []
    i = j = 0
    
    # 逐个比较两个数组的元素
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            # 选择左数组的元素
            result.append(left[i])
            i += 1
        else:
            # 选择右数组的元素
            result.append(right[j])
            j += 1
    
    # 追加左数组的剩余元素
    while i < len(left):
        result.append(left[i])
        i += 1
    
    # 追加右数组的剩余元素
    while j < len(right):
        result.append(right[j])
        j += 1
    
    return result

# 问题 2: 快速排序（Quick Sort）
def quick_sort(arr, low=0, high=None):
    """
    快速排序 - 分治的高效排序算法
    
    流程：
    1. 分解：选择一个基准元素（pivot），将数组分为 < pivot、= pivot、> pivot 三部分
    2. 递归求解：对 < pivot 和 > pivot 的部分递归排序
    3. 合并：自动完成（原地排序）
    
    时间复杂度：
    - 平均：O(n log n)
    - 最坏：O(n²)（当基准总是最小或最大元素时）
    - 最好：O(n log n)
    
    空间复杂度：O(log n)（递归栈深度）
    
    稳定性：不稳定的排序
    
    参数:
        arr: 待排序的数组
        low: 子数组的左端点
        high: 子数组的右端点
    
    返回:
        排好序的数组（原地排序）
    """
    if high is None:
        high = len(arr) - 1
    
    # 基础情况：子数组大小 <= 1 时已有序
    if low < high:
        # 分解：选择基准并分割
        pivot_index = partition(arr, low, high)
        
        # 递归求解：分别对左右两部分排序
        quick_sort(arr, low, pivot_index - 1)  # 左部分：< pivot
        quick_sort(arr, pivot_index + 1, high)  # 右部分：> pivot
    
    return arr

def partition(arr, low, high):
    """
    分割函数 - 选择基准并分割数组
    
    策略：Lomuto 分割方案
    - 选择最后一个元素作为基准（也可选第一个或中间的）
    - 维持两个区间：[low, i] 是 <= pivot，[i+1, j-1] 是 > pivot
    - 最后将基准放在正确位置
    
    时间复杂度：O(n)
    """
    # 选择最后一个元素作为基准
    pivot = arr[high]
    
    # i 标记 <= pivot 的最后一个元素位置
    i = low - 1
    
    # 遍历数组，比较每个元素与基准
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            # 交换：把 <= pivot 的元素放到左边
            arr[i], arr[j] = arr[j], arr[i]
    
    # 将基准放在正确的位置
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    
    return i + 1  # 返回基准的最终位置

# 问题 3: 二分搜索（Binary Search）
def binary_search(arr, target):
    """
    二分搜索 - 有序数组的高效搜索
    
    流程：
    1. 分解：比较中间元素与目标
    2. 递归求解：
       - 如果中间元素 == 目标，找到了
       - 如果中间元素 > 目标，搜索左半部分
       - 如果中间元素 < 目标，搜索右半部分
    3. 合并：无需合并（直接返回结果）
    
    时间复杂度：O(log n)
    空间复杂度：O(log n)（递归栈深度），迭代版本 O(1)
    
    前提条件：数组必须是已排序的
    
    参数:
        arr: 已排序的数组
        target: 要搜索的值
    
    返回:
        目标值的索引，如果不存在返回 -1
    
    示例:
        binary_search([1, 3, 5, 7, 9], 5) → 2
        binary_search([1, 3, 5, 7, 9], 4) → -1
    """
    def _binary_search_helper(low, high):
        # 基础情况：搜索范围为空
        if low > high:
            return -1
        
        # 分解：计算中点
        mid = (low + high) // 2
        
        # 分析：比较中点元素与目标
        if arr[mid] == target:
            # 找到目标，返回索引
            return mid
        elif arr[mid] < target:
            # 目标在右半部分，递归搜索右半
            return _binary_search_helper(mid + 1, high)
        else:
            # 目标在左半部分，递归搜索左半
            return _binary_search_helper(low, mid - 1)
    
    return _binary_search_helper(0, len(arr) - 1)

# 问题 4: 计算幂（Power）
def power(base, exponent):
    """
    快速幂计算 - 计算 base^exponent
    
    流程：
    1. 分解：base^n = base^(n//2) * base^(n//2) * (base if n is odd else 1)
    2. 递归求解：计算 base^(n//2)
    3. 合并：将两个 base^(n//2) 相乘（如果 n 为奇数，再乘以 base）
    
    时间复杂度：O(log n)（对比朴素方法的 O(n)）
    空间复杂度：O(log n)（递归栈）
    
    参数:
        base: 底数
        exponent: 指数（可为负数）
    
    返回:
        base^exponent 的结果
    
    示例:
        power(2, 10) → 1024
        power(2, -2) → 0.25
    """
    # 处理边界情况
    if exponent == 0:
        return 1
    
    # 处理负数指数
    if exponent < 0:
        return power(1 / base, -exponent)
    
    # 分解：计算 base^(exponent//2)
    half_power = power(base, exponent // 2)
    
    # 合并：
    if exponent % 2 == 0:
        # exponent 为偶数：base^n = (base^(n/2))^2
        return half_power * half_power
    else:
        # exponent 为奇数：base^n = (base^(n/2))^2 * base
        return half_power * half_power * base

# 问题 5: 最大子数组问题（Maximum Subarray Problem）
def max_subarray_sum(arr):
    """
    最大子数组和 - 找连续子数组使其和最大
    
    分治方法：
    1. 分解：将数组分为左右两部分
    2. 递归求解：
       - 最大和可能在左部分
       - 最大和可能在右部分
       - 最大和可能跨越中点（需要特殊处理）
    3. 合并：比较三种情况，返回最大值
    
    时间复杂度：O(n log n)（对比动态规划的 O(n)，但思想更清晰）
    空间复杂度：O(log n)（递归栈）
    
    参数:
        arr: 整数数组
    
    返回:
        最大子数组的和
    
    示例:
        max_subarray_sum([-2, 1, -3, 4, -1, 2, 1, -5, 4]) → 6
        （子数组 [4, -1, 2, 1] 的和）
    """
    def _max_subarray_helper(low, high):
        # 基础情况：只有一个元素
        if low == high:
            return arr[low]
        
        # 分解：计算中点
        mid = (low + high) // 2
        
        # 递归求解：左右两部分的最大和
        left_max = _max_subarray_helper(low, mid)
        right_max = _max_subarray_helper(mid + 1, high)
        
        # 特殊处理：跨越中点的最大和
        cross_max = _max_cross_sum(low, mid, high)
        
        # 合并：返回三者中的最大值
        return max(left_max, right_max, cross_max)
    
    def _max_cross_sum(low, mid, high):
        """计算跨越中点的最大子数组和"""
        # 从中点向左延伸，找最大和
        left_sum = float('-inf')
        sum_val = 0
        for i in range(mid, low - 1, -1):
            sum_val += arr[i]
            left_sum = max(left_sum, sum_val)
        
        # 从中点向右延伸，找最大和
        right_sum = float('-inf')
        sum_val = 0
        for i in range(mid + 1, high + 1):
            sum_val += arr[i]
            right_sum = max(right_sum, sum_val)
        
        # 跨越中点的最大和 = 左边最大和 + 右边最大和
        return left_sum + right_sum
    
    return _max_subarray_helper(0, len(arr) - 1)

# 测试代码
if __name__ == "__main__":
    print("=" * 70)
    print("分治与递归 - 完整中文注释版本")
    print("=" * 70)
    
    test_arr = [38, 27, 43, 3, 9, 82, 10]
    
    # 测试归并排序
    print("\n1. 归并排序")
    arr_copy = test_arr.copy()
    sorted_arr = merge_sort(arr_copy)
    print(f"   原始数组: {test_arr}")
    print(f"   排序后: {sorted_arr}")
    print(f"   时间复杂度: O(n log n) = O({len(test_arr)} * {len(test_arr).bit_length() - 1})")
    
    # 测试快速排序
    print("\n2. 快速排序")
    arr_copy = test_arr.copy()
    sorted_arr = quick_sort(arr_copy)
    print(f"   原始数组: {test_arr}")
    print(f"   排序后: {sorted_arr}")
    print(f"   均匀复杂度: O(n log n)，最坏 O(n²)")
    
    # 测试二分搜索
    print("\n3. 二分搜索")
    arr_sorted = sorted(test_arr)
    target = 43
    index = binary_search(arr_sorted, target)
    print(f"   有序数组: {arr_sorted}")
    print(f"   搜索 {target} 的索引: {index}")
    print(f"   时间复杂度: O(log n) = O(log {len(arr_sorted)})")
    
    # 测试快速幂
    print("\n4. 快速幂计算")
    base, exp = 2, 10
    result = power(base, exp)
    print(f"   {base}^{exp} = {result}")
    print(f"   负数指数：{base}^-2 = {power(base, -2)}")
    
    # 测试最大子数组和
    print("\n5. 最大子数组和（分治解法）")
    arr_test = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
    max_sum = max_subarray_sum(arr_test)
    print(f"   数组: {arr_test}")
    print(f"   最大子数组和: {max_sum}")
    print(f"   时间复杂度: O(n log n)（分治），也可用 O(n) 的贪心解法）")
    
    print("\n" + "=" * 70)
