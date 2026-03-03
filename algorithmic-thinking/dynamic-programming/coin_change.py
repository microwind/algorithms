"""
硬币兑换问题 (Coin Change) - 动态规划应用

问题描述：
给定不同面值的硬币和一个金额，找出使用最少数量的硬币凑出该金额的方法
如果无法凑出该金额，返回 -1

例如：coins = [1, 2, 5], amount = 5
可以使用 [5] 或 [2, 2, 1]，最少需要 1 枚硬币

动态规划方程：
dp[i] = min(dp[i], dp[i-coin] + 1) for each coin

时间复杂度: O(n * amount)，其中 n 是硬币数量
空间复杂度: O(amount)

特点：
- 完全背包问题的变体
- 每枚硬币可以使用无限次
- 最优子结构明显
"""

def coin_change(coins, amount):
    """
    硬币兑换 - 求最少硬币数量

    参数:
        coins: 硬币面值列表
        amount: 需要凑出的金额

    返回:
        最少需要的硬币数量，如果无法凑出返回 -1
    """
    if amount == 0:
        return 0

    # dp[i] 表示凑出金额 i 需要的最少硬币数
    # 初始化为无穷大，表示无法凑出
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0

    # 对每个金额进行处理
    for i in range(1, amount + 1):
        # 尝试使用每枚硬币
        for coin in coins:
            if coin <= i:
                # 如果可以使用该硬币，更新最少数量
                dp[i] = min(dp[i], dp[i - coin] + 1)

    # 如果 dp[amount] 仍为无穷大，说明无法凑出
    return dp[amount] if dp[amount] != float('inf') else -1


def coin_change_with_coins(coins, amount):
    """
    硬币兑换 - 返回具体的硬币组合

    参数:
        coins: 硬币面值列表
        amount: 需要凑出的金额

    返回:
        (最少硬币数量, 硬币组合列表) 或 (-1, [])
    """
    if amount == 0:
        return 0, []

    # dp[i] 表示凑出金额 i 需要的最少硬币数
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0

    # parent[i] 表示凑出金额 i 时使用的硬币面值
    parent = [-1] * (amount + 1)

    # 对每个金额进行处理
    for i in range(1, amount + 1):
        # 尝试使用每枚硬币
        for coin in coins:
            if coin <= i and dp[i - coin] + 1 < dp[i]:
                dp[i] = dp[i - coin] + 1
                parent[i] = coin

    # 如果无法凑出
    if dp[amount] == float('inf'):
        return -1, []

    # 反向追踪构建硬币组合
    result = []
    idx = amount
    while idx > 0:
        coin = parent[idx]
        result.append(coin)
        idx -= coin

    return dp[amount], result


def coin_change_optimized(coins, amount):
    """
    硬币兑换 - 优化版本（使用一维数组）

    通过对硬币排序并使用贪心优化，可以提高实际效率

    参数:
        coins: 硬币面值列表
        amount: 需要凑出的金额

    返回:
        最少需要的硬币数量
    """
    # 按硬币面值从大到小排序
    coins.sort(reverse=True)

    # dp[i] 表示凑出金额 i 需要的最少硬币数
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0

    # 对每个金额进行处理
    for i in range(1, amount + 1):
        for coin in coins:
            if coin > i:
                # 硬币面值过大，跳过
                continue
            if coin <= i and dp[i - coin] != float('inf'):
                dp[i] = min(dp[i], dp[i - coin] + 1)

    return dp[amount] if dp[amount] != float('inf') else -1


if __name__ == "__main__":
    print("=== 硬币兑换问题 ===\n")

    # 测试用例1：基本硬币兑换
    print("1. 基本硬币兑换")
    coins1 = [1, 2, 5]
    amount1 = 5
    print(f"硬币面值: {coins1}")
    print(f"需要凑出的金额: {amount1}")
    print(f"最少硬币数: {coin_change(coins1, amount1)}\n")

    # 测试用例2：返回具体的硬币组合
    print("2. 返回具体的硬币组合")
    coins2 = [1, 2, 5]
    amount2 = 7
    print(f"硬币面值: {coins2}")
    print(f"需要凑出的金额: {amount2}")
    count, combination = coin_change_with_coins(coins2, amount2)
    print(f"最少硬币数: {count}")
    print(f"硬币组合: {combination}\n")

    # 测试用例3：无法凑出的金额
    print("3. 无法凑出的金额")
    coins3 = [2, 5]
    amount3 = 3
    print(f"硬币面值: {coins3}")
    print(f"需要凑出的金额: {amount3}")
    print(f"最少硬币数: {coin_change(coins3, amount3)}\n")

    # 测试用例4：更大的金额
    print("4. 更大的金额")
    coins4 = [1, 3, 4]
    amount4 = 10
    print(f"硬币面值: {coins4}")
    print(f"需要凑出的金额: {amount4}")
    count, combination = coin_change_with_coins(coins4, amount4)
    print(f"最少硬币数: {count}")
    print(f"硬币组合: {combination}")
