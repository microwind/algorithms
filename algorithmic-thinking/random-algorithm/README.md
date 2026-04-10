# 随机化（Randomization）算法

> 在算法执行过程中利用随机性来解决问题，通过引入随机决策实现更高效的平均性能，避免最坏情况。

## 导航

| [算法原理](#概述) | [复杂度分析](#算法复杂度总结) | [实现列表](#实现列表) |

---

## 概述

随机化算法在算法执行过程中利用随机性来解决问题。通过引入随机决策，可以实现更高效的平均性能，避免最坏情况，或解决某些确定性算法难以处理的问题。

---

## 算法1：洗牌算法（Shuffle）

### 描述
将数组中的元素随机重新排列，使其处于随机顺序。Fisher-Yates 洗牌算法是最常用的实现。

### 关键特性
- **时间复杂度**：O(n)
- **空间复杂度**：O(1) 原地洗牌，O(n) 创建新数组
- **性质**：每个排列出现的概率相等
- **方法**：Fisher-Yates 算法

### 算法步骤
1. 从数组末尾开始
2. 在当前位置和前面元素中随机选择
3. 交换当前元素与随机选中的元素
4. 向前移动一位
5. 重复直到起始位置

### 应用场景
- 随机扩展样本集
- 随机排列元素
- 游戏随机性（洗牌、掷骰子）
- 机器学习数据预处理
- 蒙特卡洛模拟

---

## 算法2：随机快速排序（Randomized QuickSort）

### 描述
在标准快速排序基础上，随机选择枢轴元素，避免最坏情况。

### 关键特性
- **平均时间复杂度**：O(n log n)
- **最坏时间复杂度**：O(n²)（概率极低）
- **空间复杂度**：O(log n) 平均，O(n) 最坏
- **优点**：期望性能更优
- **策略**：随机选枢轴而非固定选择

### 算法步骤
1. 在分区中随机选择一个元素作为枢轴
2. 将小于枢轴的元素移到左边
3. 将大于枢轴的元素移到右边
4. 递归处理左右子数组
5. 重复直到排序完成

### 与标准快速排序对比
- **标准版**：枢轴选择固定（首、尾、中等），某些输入会导致 O(n²)
- **随机版**：随机枢轴选择，最坏情况概率极低

### 应用场景
- 大规模数据排序
- 需要稳定平均性能的情况
- 对手可能精心构造最坏输入的场景
- 实时系统对性能敏感

---

## 算法3：随机采样（Random Sampling）

### 描述
从大数据集中随机选择 k 个元素，每个元素被选中的概率相等。Reservoir Sampling 方法可处理流式数据。

### 关键特性
- **时间复杂度**：O(n)
- **空间复杂度**：O(k)
- **特点**：适合流式数据、无需预知数据量
- **方法**：Reservoir Sampling 算法

### 算法步骤（Reservoir Sampling）
1. 初始化大小为 k 的水池，填充前 k 个元素
2. 对于第 i 个元素（i > k）：
   - 生成 0 到 i 的随机数 j
   - 如果 j < k，用第 i 个元素替换水池中第 j 个元素
3. 继续处理所有元素
4. 最后水池中的 k 个元素就是随机采样结果

### 应用场景
- 流式数据随机抽样
- 大文件随机行抽取
- 数据库随机查询
- 网络流量采样
- 推荐系统采样

---

## 算法4：蒙特卡洛方法（Monte Carlo）

### 描述
利用随机数进行数值计算和模拟，通过大量随机实验得到近似解。

### 应用示例
- **π 的估算**：随机点在单位圆内外的比例
- **积分计算**：随机点下的面积近似
- **概率问题**：模拟随机事件

### 特点
- **概率保证**：给出正确答案的概率
- **可靠性**：重复多次可提高精度
- **适用性**：解决高维复杂问题

---

## 算法5：拉斯维加斯算法（Las Vegas）

### 描述
一定能给出正确答案，但运行时间随机。与蒙特卡洛不同，结果总是正确，只是时间不确定。

### vs 蒙特卡洛
| 特性 | 拉斯维加斯 | 蒙特卡洛 |
|------|----------|---------|
| 正确性 | 总是正确 | 概率正确 |
| 时间 | 随机 | 固定 |
| 例子 | 随机快速排序 | π估算 |

---

## 随机化优势

1. **避免敌对输入**：对手无法预知随机决策
2. **概率保证**：提供概率性能保证
3. **简化分析**：期望值比最坏情况更有代表性
4. **实际性能**：通常比最坏情况分析更优

---

## 性能对比

| 算法 | 时间复杂度 | 特点 | 适用场景 |
|------|-----------|------|---------|
| 洗牌 | O(n) | 均匀分布 | 随机重排 |
| 随机快速排序 | O(n log n) 期望 | 避免最坏 | 通用排序 |
| 随机采样 | O(n) | 流式处理 | 大数据集 |
| 蒙特卡洛 | 可变 | 概率保证 | 数值计算 |
| 拉斯维加斯 | 可变 | 总是正确 | 需要精确解 |

---

## 实现语言

每个随机化算法都包含以下语言的实现：
- C
- Go
- Java
- JavaScript
- Python
- Rust

## Python 实现示例：`randomization.py`

下面给出一个整合了多种随机化算法的 Python 示例文件，实现了洗牌、随机快速排序、水库采样、蒙特卡洛估算 π 和积分等功能。

```python
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
```

## 实现列表

| 语言 | 文件名 | 说明 |
|------|--------|------|
| C | [shuffle.c](./shuffle.c) | Fisher-Yates洗牌实现 |
| C | [randomized_quicksort.c](./randomized_quicksort.c) | 随机快排实现 |
| Java | [Shuffle.java](./Shuffle.java) | 洗牌类 |
| Java | [RandomizedQuickSort.java](./RandomizedQuickSort.java) | 随机快排类 |
| Go | [random_algorithm.go](./random_algorithm.go) | 综合实现 |
| Python | [random_algorithm.py](./random_algorithm.py) | 简洁实现 |
| JavaScript | [randomAlgorithm.js](./randomAlgorithm.js) | 随机算法实现 |
| TypeScript | [RandomAlgorithm.ts](./RandomAlgorithm.ts) | 类型安全 |
| Rust | [random_algorithm.rs](./random_algorithm.rs) | 随机实现 |

---

## 参考资源

- 概率论与数理统计
- 随机算法 (Randomized Algorithms) - Motwani & Raghavan
- 算法导论 (Introduction to Algorithms) - CLRS
- 更多应用的 Monte Carlo 方法介绍
