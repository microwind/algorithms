
"""
零钱兑换问题（贪心算法）

算法思路：
- 贪心策略：每次选择不超过剩余金额的最大面值硬币
- 不断用最大面值硬币减去剩余金额，直到为0
- 注意：贪心算法并不总是最优

时间复杂度：O(n log n)（排序）+ O(n)（循环）
空间复杂度：O(1)

重要：贪心算法并不适用于所有硬币体系！

反例：
coins = [1, 3, 4], amount = 6
贪心：4 + 1 + 1 = 3枚
最优：3 + 3 = 2枚

因此对于最优解应使用动态规划（coin_change_dp），但对于实际货币（如美元）贪心有效。

与DP对比：
- 贪心：O(n log n)，但不一定最优
- DP：O(n * amount)，一定最优
"""

from typing import List, Tuple


def coin_change_greedy(coins: List[int], amount: int) -> Tuple[int, List[int]]:
    """
    贪心法求凑成目标金额的最少硬币数（不一定最优）

    参数:
        coins: 硬币面值列表
        amount: 目标金额

    返回:
        (最少硬币数, 使用的硬币列表)，无法凑成则返回(-1, [])

    示例:
        >>> coin_change_greedy([1, 7, 10], 11)
        (2, [10, 1])
    """
    if amount == 0:
        return (0, [])
    # 降序排序硬币面值
    sorted_coins = sorted(coins, reverse=True)
    count = 0
    coins_used = []
    remaining = amount
    for coin in sorted_coins:
        while remaining >= coin:
            remaining -= coin
            coins_used.append(coin)
            count += 1

    # 如果无法凑成目标金额
    if remaining != 0:
        return (-1, [])
    return (count, coins_used)


def coin_change_greedy_count_only(coins: List[int], amount: int) -> int:
    """
    只返回最少硬币数（简化版）

    参数:
        coins: 硬币面值列表
        amount: 目标金额

    返回:
        最少硬币数，无法凑成则返回-1
    """
    count, _ = coin_change_greedy(coins, amount)
    return count


def coin_change_dp(coins: List[int], amount: int) -> Tuple[int, List[int]]:
    """
    动态规划法求最少硬币数（一定最优，供对比）

    时间复杂度：O(n * amount)
    空间复杂度：O(amount)
    """
    if amount == 0:
        return (0, [])

    # dp[i] = minimum coins needed for amount i
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0
    parent = [-1] * (amount + 1)

    for curr_amount in range(1, amount + 1):
        for coin in coins:
            if coin <= curr_amount and dp[curr_amount - coin] + 1 < dp[curr_amount]:
                dp[curr_amount] = dp[curr_amount - coin] + 1
                parent[curr_amount] = coin

    if dp[amount] == float('inf'):
        return (-1, [])

    # Reconstruct the solution
    coins_used = []
    curr = amount
    while curr > 0:
        coin = parent[curr]
        coins_used.append(coin)
        curr -= coin

    return (dp[amount], coins_used)


def compare_greedy_vs_dp(coins: List[int], amount: int) -> None:
    """
    对比贪心与动态规划解法
    """
    greedy_count, greedy_coins = coin_change_greedy(coins, amount)
    dp_count, dp_coins = coin_change_dp(coins, amount)

    print(f"Coins: {coins}, Amount: {amount}")
    print(f"Greedy: {greedy_count} coins - {sorted(greedy_coins, reverse=True)}")
    print(f"DP:     {dp_count} coins - {sorted(dp_coins, reverse=True)}")
    if greedy_count != -1 and dp_count != -1:
        if greedy_count == dp_count:
            print("✓ Greedy is optimal for this input")
        else:
            print(f"✗ Greedy is suboptimal (difference: {greedy_count - dp_count})")
    print()



if __name__ == "__main__":
    print("=" * 60)
    print("零钱兑换问题 - 贪心与动态规划对比")
    print("=" * 60)
    # 测试用例 1: 美元硬币（贪心最优）
    print("\n[测试1] 美元硬币（贪心最优）")
    count, coins_used = coin_change_greedy([1, 5, 10, 25], 41)
    print(f"硬币面值: [1, 5, 10, 25], 金额: 41")
    print(f"贪心结果: {count} 枚 - {sorted(coins_used, reverse=True)}")
    # 测试用例 2: 贪心失败
    print("\n[测试2] 贪心失败案例")
    compare_greedy_vs_dp([1, 3, 4], 6)
    # 测试用例 3: 另一个贪心失败案例
    print("\n[测试3] 另一个贪心失败案例")
    compare_greedy_vs_dp([1, 7, 10], 11)
    # 测试用例 4: 贪心最优案例
    print("\n[测试4] 贪心最优案例")
    compare_greedy_vs_dp([1, 5, 10, 25], 30)
    # 测试用例 5: 无法凑成（无1分硬币）
    print("\n[测试5] 无法凑成（无1分硬币）")
    count, coins_used = coin_change_greedy([5, 10, 25], 11)
    print(f"硬币面值: [5, 10, 25], 金额: 11")
    print(f"结果: {count}（无法凑成，无1分硬币）")
    # 测试用例 6: 金额为0
    print("\n[测试6] 金额为0")
    count, coins_used = coin_change_greedy([1, 5, 10], 0)
    print(f"硬币面值: [1, 5, 10], 金额: 0")
    print(f"结果: {count} 枚")
    # 测试用例 7: 单一硬币类型
    print("\n[测试7] 单一硬币类型")
    compare_greedy_vs_dp([7], 21)
    # 测试用例 8: 大金额
    print("\n[测试8] 大金额")
    count, coins_used = coin_change_greedy([1, 5, 10, 25, 50], 158)
    print(f"硬币面值: [1, 5, 10, 25, 50], 金额: 158")
    print(f"贪心结果: {count} 枚 - {sorted(coins_used, reverse=True)}")
    # 测试用例 9: 非标准硬币体系贪心失败
    print("\n[测试9] 非标准硬币体系贪心失败")
    compare_greedy_vs_dp([1, 3, 4, 5], 13)
    # 测试用例 10: 更大面值问题
    print("\n[测试10] 更大面值问题")
    compare_greedy_vs_dp([2, 5, 10], 11)
