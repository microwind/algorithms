"""
Coin Change - Greedy Approach

Algorithm:
- Use greedy approach: always select the largest coin possible
- Keep subtracting the largest coin until amount is 0
- Does NOT always give optimal solution

Time Complexity: O(n log n) - sorting + O(n) for the loop
Space Complexity: O(1) - excluding output

Important: This greedy approach is NOT optimal for all coin systems!

示例 where greedy fails:
- coins = [1, 3, 4], amount = 6
- Greedy: 4 + 1 + 1 = 3 coins
- Optimal: 3 + 3 = 2 coins

This is why DP (coin_change_dp) should be used for optimal results.
However, for real currencies (like USD coins), greedy works.

Comparison with DP:
- Greedy: O(n log n) time, but may not be optimal
- DP: O(n * amount) time, but always optimal
"""

from typing import List, Tuple


def coin_change_greedy(coins: List[int], amount: int) -> Tuple[int, List[int]]:
    """
    Find minimum coins using greedy approach (not always optimal).

    参数:
        coins: List of coin denominations
        amount: Target amount to make

    返回:
        Tuple of (count, list of coins used)
        返回 (-1, []) if amount cannot be made

    示例:
        >>> coin_change_greedy([1, 7, 10], 11)
        (2, [10, 1])
    """
    if amount == 0:
        return (0, [])

    # Sort coins in descending order
    sorted_coins = sorted(coins, reverse=True)
    count = 0
    coins_used = []
    remaining = amount

    for coin in sorted_coins:
        while remaining >= coin:
            remaining -= coin
            coins_used.append(coin)
            count += 1

    # If we couldn't make exact amount
    if remaining != 0:
        return (-1, [])

    return (count, coins_used)


def coin_change_greedy_count_only(coins: List[int], amount: int) -> int:
    """
    Return only the count of coins (simplified version).

    参数:
        coins: List of coin denominations
        amount: Target amount

    返回:
        Count of coins, or -1 if impossible
    """
    count, _ = coin_change_greedy(coins, amount)
    return count


def coin_change_dp(coins: List[int], amount: int) -> Tuple[int, List[int]]:
    """
    Find minimum coins using Dynamic Programming (always optimal).

    This is provided for comparison with greedy approach.

    Time Complexity: O(n * amount)
    Space Complexity: O(amount)
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
    Compare greedy and DP solutions for a given problem.
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
    print("COIN CHANGE - Greedy vs DP Comparison")
    print("=" * 60)

    # 测试用例 1: Standard coins (greedy works)
    print("\n[Test 1] US Coins (greedy optimal)")
    count, coins_used = coin_change_greedy([1, 5, 10, 25], 41)
    print(f"Coins: [1, 5, 10, 25], Amount: 41")
    print(f"Greedy Result: {count} coins - {sorted(coins_used, reverse=True)}")

    # 测试用例 2: Where greedy fails
    print("\n[Test 2] Greedy fails case")
    compare_greedy_vs_dp([1, 3, 4], 6)

    # 测试用例 3: Another greedy fails case
    print("\n[Test 3] Another greedy fails case")
    compare_greedy_vs_dp([1, 7, 10], 11)

    # 测试用例 4: Greedy optimal case
    print("\n[Test 4] Greedy optimal case")
    compare_greedy_vs_dp([1, 5, 10, 25], 30)

    # 测试用例 5: Impossible amount
    print("\n[Test 5] Impossible amount (no 1-cent coin)")
    count, coins_used = coin_change_greedy([5, 10, 25], 11)
    print(f"Coins: [5, 10, 25], Amount: 11")
    print(f"Result: {count} (impossible without 1-cent coin)")

    # 测试用例 6: Zero amount
    print("\n[Test 6] Zero amount")
    count, coins_used = coin_change_greedy([1, 5, 10], 0)
    print(f"Coins: [1, 5, 10], Amount: 0")
    print(f"Result: {count} coins")

    # 测试用例 7: Single coin
    print("\n[Test 7] Single coin type")
    compare_greedy_vs_dp([7], 21)

    # 测试用例 8: Large amount
    print("\n[Test 8] Large amount")
    count, coins_used = coin_change_greedy([1, 5, 10, 25, 50], 158)
    print(f"Coins: [1, 5, 10, 25, 50], Amount: 158")
    print(f"Greedy Result: {count} coins - {sorted(coins_used, reverse=True)}")

    # 测试用例 9: Complex non-standard coins
    print("\n[Test 9] Non-standard coins where greedy fails")
    compare_greedy_vs_dp([1, 3, 4, 5], 13)

    # 测试用例 10: Larger denomination problem
    print("\n[Test 10] Larger problem")
    compare_greedy_vs_dp([2, 5, 10], 11)
