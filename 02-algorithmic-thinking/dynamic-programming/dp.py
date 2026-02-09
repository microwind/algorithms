"""
动态规划 - 自底向上、自顶向下

动态规划的两个关键条件：
1. 最优子结构：问题的最优解包含子问题的最优解
2. 重叠子问题：多个子问题有重复计算

常见应用：
- 背包问题
- 最长递增子序列
- 编辑距离
- 路径计数
"""

# 例1: 0-1 背包问题
def knapsack(weights, values, capacity):
    """
    0-1 背包问题
    时间复杂度: O(n*W), 空间复杂度: O(n*W)
    """
    n = len(weights)
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]
    
    for i in range(1, n + 1):
        for w in range(capacity + 1):
            if weights[i-1] <= w:
                # 选择或不选择
                dp[i][w] = max(
                    dp[i-1][w],  # 不选
                    dp[i-1][w-weights[i-1]] + values[i-1]  # 选
                )
            else:
                dp[i][w] = dp[i-1][w]
    
    return dp[n][capacity]

# 例2: 最长递增子序列
def longest_increasing_subsequence(arr):
    """
    最长递增子序列 (LIS)
    时间复杂度: O(n^2), 空间复杂度: O(n)
    """
    n = len(arr)
    dp = [1] * n
    
    for i in range(1, n):
        for j in range(i):
            if arr[j] < arr[i]:
                dp[i] = max(dp[i], dp[j] + 1)
    
    return max(dp)

# 例3: 硬币兑换问题
def coin_change(coins, amount):
    """
    最少硬币数
    时间复杂度: O(n*amount), 空间复杂度: O(amount)
    """
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0
    
    for coin in coins:
        for i in range(coin, amount + 1):
            dp[i] = min(dp[i], dp[i - coin] + 1)
    
    return dp[amount] if dp[amount] != float('inf') else -1

# 例4: 编辑距离
def edit_distance(word1, word2):
    """
    莱文斯坦距离 (Levenshtein Distance)
    时间复杂度: O(m*n), 空间复杂度: O(m*n)
    """
    m, n = len(word1), len(word2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    for i in range(m + 1):
        dp[i][0] = i
    for j in range(n + 1):
        dp[0][j] = j
    
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if word1[i-1] == word2[j-1]:
                dp[i][j] = dp[i-1][j-1]
            else:
                dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
    
    return dp[m][n]

if __name__ == "__main__":
    print("=== 动态规划示例 ===\n")
    
    # 背包问题
    print("1. 0-1 背包问题")
    weights = [2, 3, 4, 5]
    values = [3, 4, 5, 6]
    capacity = 8
    print(f"最大价值: {knapsack(weights, values, capacity)}\n")
    
    # 最长递增子序列
    print("2. 最长递增子序列")
    arr = [10, 9, 2, 5, 3, 7, 101, 18]
    print(f"LIS长度: {longest_increasing_subsequence(arr)}\n")
    
    # 硬币兑换
    print("3. 硬币兑换")
    coins = [1, 2, 5]
    amount = 5
    print(f"最少硬币数: {coin_change(coins, amount)}\n")
    
    # 编辑距离
    print("4. 编辑距离")
    print(f"'horse' 到 'ros': {edit_distance('horse', 'ros')}")
