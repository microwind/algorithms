# 洗牌算法 - Python 实现

"""
Fisher-Yates 洗牌算法
时间复杂度: O(n)
空间复杂度: O(1) 原地洗牌
每个排列等概率出现 (概率 = 1/n!)
"""

import random

def shuffle_fisher_yates(arr):
    """
    Fisher-Yates 洗牌 - 原地洗牌
    从后向前，每个位置与前面某个位置交换
    """
    n = len(arr)
    
    # 从末尾开始向前遍历
    for i in range(n - 1, 0, -1):
        # 在 [0, i] 范围内随机选择
        j = random.randint(0, i)
        # 交换
        arr[i], arr[j] = arr[j], arr[i]
    
    return arr

def shuffle_copy(arr):
    """
    创建新数组的洗牌
    时间: O(n), 空间: O(n)
    """
    result = arr.copy()
    shuffle_fisher_yates(result)
    return result

def shuffle_modern(arr):
    """
    现代洗牌：从前向后交换
    思想相同，起点不同
    """
    n = len(arr)
    
    for i in range(n):
        # 在 [i, n) 范围内随机选择
        j = random.randint(i, n - 1)
        # 交换
        arr[i], arr[j] = arr[j], arr[i]
    
    return arr

def shuffle_sattolo(arr):
    """
    Sattolo 循环洗牌
    生成随机循环排列而非完全随机排列
    每个元素都不保持原位置
    """
    n = len(arr)
    
    for i in range(n - 1, 0, -1):
        # 关键区别：在 [0, i) 内选择，不包括 i
        j = random.randint(0, i - 1)
        arr[i], arr[j] = arr[j], arr[i]
    
    return arr

def weighted_shuffle(arr, weights):
    """
    加权随机洗牌
    based on weights by Efraimidis-Spirakis algorithm
    """
    # 为每个元素计算随机键 = random() ^ (1.0 / weight)
    weighted_items = [
        (random.random() ** (1.0 / w), arr[i], w)
        for i, w in enumerate(weights)
    ]
    
    # 按随机键排序
    weighted_items.sort(reverse=True)
    
    return [item[1] for item in weighted_items]

def verify_shuffle_distribution(arr, trials=1000):
    """
    验证洗牌的均匀分布
    计算每个位置出现在每个原始位置的次数
    """
    n = len(arr)
    # 位置矩阵：position[i][j] = 元素 j 在位置 i 的次数
    position_counts = [[0] * n for _ in range(n)]
    
    original = list(range(n))
    
    for _ in range(trials):
        shuffled = original.copy()
        shuffle_fisher_yates(shuffled)
        
        for pos, element in enumerate(shuffled):
            position_counts[pos][element] += 1
    
    # 理想情况下，每个位置应该有 trials/n 的期望值
    expected = trials / n
    
    print(f"洗牌均匀分布验证 ({trials} 次试验):")
    print(f"预期频率: {expected:.1f}")
    print("位置频率矩阵:")
    
    for pos in range(n):
        print(f"  位置 {pos}: ", end="")
        for count in position_counts[pos]:
            print(f"{count:4d}", end=" ")
        print()
    
    return position_counts

if __name__ == "__main__":
    print("=" * 50)
    print("Fisher-Yates 洗牌算法 - Python 实现")
    print("=" * 50)
    
    # 测试 1：基础洗牌
    print("\n测试 1: 基础洗牌")
    arr = [1, 2, 3, 4, 5]
    print(f"原数组: {arr}")
    for i in range(3):
        shuffled = shuffle_fisher_yates(arr.copy())
        print(f"洗牌 {i+1}: {shuffled}")
    
    # 测试 2：创建副本洗牌
    print("\n测试 2: 创建新数组洗牌")
    arr = ['A', 'B', 'C', 'D']
    print(f"原数组: {arr}")
    shuffled = shuffle_copy(arr)
    print(f"洗牌后: {shuffled}")
    print(f"原数组未变: {arr}")
    
    # 测试 3：现代洗牌
    print("\n测试 3: 现代洗牌（从前向后）")
    arr = [10, 20, 30, 40, 50]
    print(f"原数组: {arr}")
    shuffled = shuffle_modern(arr.copy())
    print(f"洗牌后: {shuffled}")
    
    # 测试 4：Sattolo 循环洗牌
    print("\n测试 4: Sattolo 循环洗牌")
    arr = [1, 2, 3, 4, 5]
    print(f"原数组: {arr}")
    for i in range(2):
        shuffled = shuffle_sattolo(arr.copy())
        print(f"  循环 {i+1}: {shuffled}")
    
    # 测试 5：加权洗牌
    print("\n测试 5: 加权随机洗牌")
    items = ['A', 'B', 'C', 'D']
    weights = [4, 2, 1, 1]  # A 最可能出现，D 最不可能
    print(f"项目: {items}")
    print(f"权重: {weights}")
    for i in range(3):
        shuffled = weighted_shuffle(items.copy(), weights)
        print(f"  加权洗牌 {i+1}: {shuffled}")
    
    # 测试 6：分布均匀性验证
    print("\n测试 6: 洗牌分布验证")
    verify_shuffle_distribution([0, 1, 2, 3], trials=10000)
    
    print("\n" + "=" * 50)
