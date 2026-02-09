"""
0-1 背包问题 - 动态规划的经典应用

问题描述：
给定 n 件物品和一个容量为 W 的背包，每件物品有一个重量和一个价值
在背包容量限制下，选择物品使得总价值最大

动态规划方程：
dp[i][w] = max(
    dp[i-1][w],  # 不选择第 i 件物品
    dp[i-1][w-weight[i]] + value[i]  # 选择第 i 件物品
)

时间复杂度: O(n * W)，其中 n 是物品数量，W 是容量
空间复杂度: O(n * W)，可以优化为 O(W)

特点：
- 经典背包问题
- 每件物品最多选一次（0-1）
- 最优子结构明显
- 重叠子问题存在
"""

def knapsack(weights, values, capacity):
    """
    0-1 背包问题 - 动态规划求解

    Args:
        weights: 物品重量列表
        values: 物品价值列表
        capacity: 背包容量

    Returns:
        背包能容纳的最大价值
    """
    n = len(weights)

    # dp[i][w] 表示前 i 件物品，容量为 w 时的最大价值
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]

    # 填充 dp 表
    for i in range(1, n + 1):
        for w in range(capacity + 1):
            # 第 i 件物品的重量和价值（索引为 i-1）
            weight = weights[i - 1]
            value = values[i - 1]

            if weight <= w:
                # 选择或不选择
                dp[i][w] = max(
                    dp[i - 1][w],  # 不选
                    dp[i - 1][w - weight] + value  # 选
                )
            else:
                # 物品太重，无法选择
                dp[i][w] = dp[i - 1][w]

    return dp[n][capacity]

def knapsack_optimized(weights, values, capacity):
    """
    0-1 背包问题 - 空间优化版本（仅用一维数组）

    Args:
        weights: 物品重量列表
        values: 物品价值列表
        capacity: 背包容量

    Returns:
        背包能容纳的最大价值
    """
    n = len(weights)

    # dp[w] 表示容量为 w 时的最大价值
    dp = [0] * (capacity + 1)

    # 处理每件物品
    for i in range(n):
        weight = weights[i]
        value = values[i]

        # 从后向前遍历容量，保证每件物品只使用一次
        for w in range(capacity, weight - 1, -1):
            dp[w] = max(dp[w], dp[w - weight] + value)

    return dp[capacity]

def knapsack_with_items(weights, values, capacity):
    """
    0-1 背包问题 - 返回选中的物品

    Args:
        weights: 物品重量列表
        values: 物品价值列表
        capacity: 背包容量

    Returns:
        (最大价值, 选中物品索引列表)
    """
    n = len(weights)

    # 构建 dp 表
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        for w in range(capacity + 1):
            weight = weights[i - 1]
            value = values[i - 1]

            if weight <= w:
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weight] + value)
            else:
                dp[i][w] = dp[i - 1][w]

    # 反向追踪选中的物品
    selected = []
    w = capacity
    for i in range(n, 0, -1):
        if dp[i][w] != dp[i - 1][w]:
            selected.append(i - 1)
            w -= weights[i - 1]

    return dp[n][capacity], selected[::-1]

if __name__ == "__main__":
    print("=== 0-1 背包问题 ===\n")

    # 测试用例1：基本背包问题
    print("1. 基本背包问题")
    weights = [2, 3, 4, 5]
    values = [3, 4, 5, 6]
    capacity = 8
    max_value = knapsack(weights, values, capacity)
    print(f"物品重量: {weights}")
    print(f"物品价值: {values}")
    print(f"背包容量: {capacity}")
    print(f"最大价值: {max_value}\n")

    # 测试用例2：空间优化版本
    print("2. 空间优化版本")
    max_value_opt = knapsack_optimized(weights, values, capacity)
    print(f"最大价值（优化）: {max_value_opt}\n")

    # 测试用例3：返回选中物品
    print("3. 返回选中物品")
    max_value_items, selected_items = knapsack_with_items(weights, values, capacity)
    print(f"最大价值: {max_value_items}")
    print(f"选中物品索引: {selected_items}")
    print(f"选中物品重量: {[weights[i] for i in selected_items]}")
    print(f"选中物品价值: {[values[i] for i in selected_items]}")
    print()

    # 测试用例4：容量较大
    print("4. 容量较大的背包")
    weights2 = [1, 2, 3, 4, 5]
    values2 = [1, 3, 5, 7, 9]
    capacity2 = 10
    max_value2 = knapsack(weights2, values2, capacity2)
    print(f"物品重量: {weights2}")
    print(f"物品价值: {values2}")
    print(f"背包容量: {capacity2}")
    print(f"最大价值: {max_value2}")
