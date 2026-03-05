"""
随机化算法 - 利用随机性解决问题

特点：
- 洗牌：均匀随机重排
- 随机快速排序：期望 O(n log n)
- 随机采样：流式处理大数据
- 蒙特卡洛：概率数值计算
"""

import random
import math
from typing import List, TypeVar

T = TypeVar('T')

# 例1: Fisher-Yates 洗牌算法
def shuffle_fisher_yates(arr: List[T]) -> List[T]:
    """
    Fisher-Yates 洗牌算法
    时间: O(n), 空间: O(1) 原地洗牌
    每个排列等概率出现
    """
    n = len(arr)
    
    # 从后向前，每个位置与前面某个位置交换
    for i in range(n - 1, 0, -1):
        # 在 [0, i] 范围内随机选择
        j = random.randint(0, i)
        # 交换
        arr[i], arr[j] = arr[j], arr[i]
    
    return arr

# 例2: 随机洗牌（非原地，创建新数组）
def shuffle_new_array(arr: List[T]) -> List[T]:
    """
    创建新数组的洗牌
    时间: O(n), 空间: O(n)
    """
    n = len(arr)
    result = arr.copy()
    
    for i in range(n - 1, 0, -1):
        j = random.randint(0, i)
        result[i], result[j] = result[j], result[i]
    
    return result

# 例3: 随机快速排序
def randomized_quicksort(arr: List[int]) -> List[int]:
    """
    随机快速排序
    时间: O(n log n) 期望, O(n²) 最坏
    空间: O(log n) 平均
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
    
    # 递归排序
    return randomized_quicksort(left) + middle + randomized_quicksort(right)

# 例4: 随机采样 - Reservoir Sampling（水库采样）
def reservoir_sampling(data, k: int) -> List[T]:
    """
    水库采样：从流式数据中随机选择 k 个元素
    时间: O(n), 空间: O(k)
    每个元素被选中的概率相等：k/n
    """
    reservoir = []
    
    for i, item in enumerate(data):
        if i < k:
            # 前 k 个元素直接放入水池
            reservoir.append(item)
        else:
            # 对于第 i 个元素，以 k/(i+1) 的概率替换
            j = random.randint(0, i)
            if j < k:
                reservoir[j] = item
    
    return reservoir

# 例5: 蒙特卡洛方法 - 估算 π
def estimate_pi_monte_carlo(num_samples: int) -> float:
    """
    蒙特卡洛方法估算 π
    在单位正方形内随机投点，计算落在内切圆内的比例
    时间: O(num_samples), 空间: O(1)
    """
    inside_circle = 0
    
    for _ in range(num_samples):
        # 在 [0, 1] × [0, 1] 内随机生成点
        x = random.random()
        y = random.random()
        
        # 判断是否在原点为中心、半径为 1 的圆内
        if x * x + y * y <= 1.0:
            inside_circle += 1
    
    # 圆的面积 / 正方形面积 = π/4
    # 所以 π ≈ 4 * (圆内的点数 / 总点数)
    pi_estimate = 4.0 * inside_circle / num_samples
    return pi_estimate

# 例6: 蒙特卡洛方法 - 计算积分
def monte_carlo_integration(func, a: float, b: float, num_samples: int) -> float:
    """
    蒙特卡洛方法计算积分
    估算 ∫[a,b] f(x)dx
    时间: O(num_samples), 空间: O(1)
    """
    sum_values = 0.0
    
    for _ in range(num_samples):
        # 在 [a, b] 内随机生成 x
        x = random.uniform(a, b)
        sum_values += func(x)
    
    # 积分 ≈ (b - a) * (平均函数值)
    integral = (b - a) * sum_values / num_samples
    return integral

# 例7: 随机数组分区（用于快速排序）
def randomized_partition(arr: List[int], left: int, right: int) -> int:
    """
    原地分区，随机选择枢轴
    返回枢轴最终位置
    """
    # 选择随机枢轴
    random_idx = random.randint(left, right)
    # 交换到最右
    arr[random_idx], arr[right] = arr[right], arr[random_idx]
    
    pivot = arr[right]
    i = left - 1
    
    for j in range(left, right):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    
    arr[i + 1], arr[right] = arr[right], arr[i + 1]
    return i + 1

# 例8: 随机选择第 k 个最小元素
def randomized_select(arr: List[int], left: int, right: int, k: int) -> int:
    """
    随机选择：平均 O(n) 时间内找第 k 个最小元素
    时间: O(n) 平均, O(n²) 最坏
    """
    if left == right:
        return arr[left]
    
    pivot_idx = randomized_partition(arr, left, right)
    
    if k == pivot_idx:
        return arr[k]
    elif k < pivot_idx:
        return randomized_select(arr, left, pivot_idx - 1, k)
    else:
        return randomized_select(arr, pivot_idx + 1, right, k)

# 测试代码
if __name__ == "__main__":
    print("=" * 50)
    print("随机化算法示例")
    print("=" * 50)
    
    # 洗牌测试
    print("\n1. Fisher-Yates 洗牌")
    arr = [1, 2, 3, 4, 5]
    print(f"  原数组: {arr}")
    shuffled = shuffle_fisher_yates(arr.copy())
    print(f"  洗牌后: {shuffled}")
    
    # 随机快速排序
    print("\n2. 随机快速排序")
    arr = [5, 2, 8, 1, 9, 3, 4]
    print(f"  原数组: {arr}")
    sorted_arr = randomized_quicksort(arr)
    print(f"  排序后: {sorted_arr}")
    
    # 水库采样
    print("\n3. 水库采样（k=3）")
    data = range(1, 11)
    sample = reservoir_sampling(data, 3)
    print(f"  从 {list(data)} 中随机采样 3 个: {sample}")
    
    # 蒙特卡洛估算 π
    print("\n4. 蒙特卡洛方法估算 π")
    samples = 100000
    pi_est = estimate_pi_monte_carlo(samples)
    print(f"  采样数: {samples}")
    print(f"  π 估算值: {pi_est:.6f}")
    print(f"  π 真实值: {math.pi:.6f}")
    print(f"  误差: {abs(pi_est - math.pi):.6f}")
    
    # 蒙特卡洛计算积分
    print("\n5. 蒙特卡洛方法计算积分")
    # 计算 ∫[0,1] x² dx，真实值应该是 1/3 ≈ 0.333
    def f(x):
        return x * x
    
    integral_est = monte_carlo_integration(f, 0, 1, 50000)
    print(f"  计算: ∫[0,1] x² dx")
    print(f"  估算值: {integral_est:.6f}")
    print(f"  真实值: {1/3:.6f}")
    
    print("\n" + "=" * 50)
