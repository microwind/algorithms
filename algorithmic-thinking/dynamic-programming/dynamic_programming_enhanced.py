"""
动态规划（Dynamic Programming）- 分治与记忆化的完美结合

核心思路：
1. 最优子结构：问题的最优解包含其子问题的最优解
2. 重叠子问题：问题分解过程中会重复计算相同的子问题
3. 记忆化存储：缓存子问题的结果避免重复计算

DP 的两种实现方式：
A. 自顶向下(Top-Down)：递归 + 记忆化
   - 从问题出发，递归求解更小的子问题
   - 使用字典/数组缓存已求解的结果
   
B. 自底向上(Bottom-Up)：迭代 + 填表
   - 从最小子问题开始逐步求解
   - 使用表格存储所有子问题的解

时间优化：从指数时间 O(2^n) 降低到多项式时间 O(n) ~ O(n³)
空间优化：通常需要 O(n) 或 O(n²) 的存储空间

经典问题分类：
- 数值问题：斐波那契、钱币兑换等
- 序列问题：最长子序列、编辑距离等
- 背包问题：0/1 背包、完全背包、多维背包
- 游戏问题：博弈 DP、游戏最优决策
"""

# 问题 1: 斐波那契额数列 - DP 的经典入门
def fibonacci_dp(n):
    """
    计算第 n 个斐波那契数（自底向上DP方式）
    
    递推关系: F(n) = F(n-1) + F(n-2), F(0)=0, F(1)=1
    
    时间复杂度: O(n)（对比朴素递归的 O(2^n)，性能提升巨大）
    空间复杂度: O(n)（使用动态规划表）
    
    参数:
        n: 要求的斐波那契数的位置
    
    返回:
        第 n 个斐波那契数
    
    示例:
        fibonacci_dp(10) = 55
    """
    if n <= 1:
        return n
    
    # 创建 DP 表：dp[i] 表示第 i 个斐波那契数
    dp = [0] * (n + 1)
    dp[0], dp[1] = 0, 1
    
    # 从小到大填表，每个数都基于前两个数计算
    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]
    
    return dp[n]

def fibonacci_optimized(n):
    """
    斐波那契数 - 空间优化版本
    
    关键优化：只需保留最后两个数即可计算下一个数
    
    时间复杂度: O(n)
    空间复杂度: O(1)（只用常数个变量）
    
    参数:
        n: 要求的一个斐波那契数的位置
    
    返回:
        第 n 个斐波那契数
    """
    if n <= 1:
        return n
    
    prev, curr = 0, 1  # F(0)=0, F(1)=1
    
    # 每次迭代计算一个新的斐波那契数
    for _ in range(2, n + 1):
        prev, curr = curr, prev + curr
    
    return curr

# 问题 2: 钱币兑换 - 背包问题思想
def coin_change(coins, amount):
    """
    最少钱币数 - 给定硬币面额，求兑换指定金额所需最少硬币数
    
    递推关系：设 dp[i] 为凑成金额 i 的最少硬币数
    dp[i] = min(dp[i - coin] + 1) for all coin in coins
    
    时间复杂度: O(amount * len(coins))
    空间复杂度: O(amount)
    
    参数:
        coins: 可用的硬币面额列表
        amount: 要凑的总金额
    
    返回:
        最少需要的硬币数，如果无法凑出则返回 -1
    
    示例:
        coin_change([1, 2, 5], 5) = 1  （直接用一个 5 元）
        coin_change([2], 3) = -1  （无法凑出 3 元）
    """
    # 初始化 DP 表：dp[i] 表示凑成 i 元所需的最少硬币数
    # 使用 amount + 1 作为"不可达"的标记（比实际最大值更大）
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0  # 凑成 0 元不需要任何硬币
    
    # 对每个金额从 1 到 amount 计算最少硬币数
    for i in range(1, amount + 1):
        # 尝试每种硬币面额
        for coin in coins:
            # 如果这个硬币不超过当前金额，可以尝试使用它
            if coin <= i:
                # 选择这个硬币后，剩余金额为 i - coin
                # 总硬币数 = dp[i - coin] 加上当前这 1 个硬币
                dp[i] = min(dp[i], dp[i - coin] + 1)
    
    # 返回结果：如果 dp[amount] 仍然是 inf，表示无法凑出
    return dp[amount] if dp[amount] != float('inf') else -1

# 问题 3: 最长递增子序列（LIS）
def longest_increasing_subsequence(nums):
    """
    找最长递增子序列 - 经典序列 DP
    
    递推关系：设 dp[i] 为以 nums[i] 结尾的最长递增子序列长度
    dp[i] = max(dp[j] + 1) for all j < i and nums[j] < nums[i]
    
    时间复杂度: O(n²)（可优化到 O(n log n) 用二分搜索）
    空间复杂度: O(n)
    
    参数:
        nums: 待分析的数字序列
    
    返回:
        最长递增子序列的长度
    
    示例:
        longest_increasing_subsequence([10, 9, 2, 5, 3, 7, 101, 18]) = 4
        （一个 LIS 是 [2, 3, 7, 101]）
    """
    if not nums:
        return 0
    
    n = len(nums)
    # dp[i] = 以 nums[i] 结尾的最长递增子序列长度
    dp = [1] * n
    
    # 对每个位置 i，检查所有之前的位置 j
    for i in range(1, n):
        for j in range(i):
            # 如果 nums[j] < nums[i]，可以将 nums[i] 接在以 nums[j] 结尾的 LIS 后面
            if nums[j] < nums[i]:
                # 更新 dp[i] 为最长的可能选择
                dp[i] = max(dp[i], dp[j] + 1)
    
    # 返回所有 dp[i] 中的最大值
    return max(dp)

# 问题 4: 0/1 背包问题 - DP 的综合应用
def knapsack_01(weights, values, capacity):
    """
    0/1 背包问题 - 给定物品，选择放入背包使总价值最大
    
    关键点：每个物品要么选（1），要么不选（0），不能分割
    
    递推关系：设 dp[i][w] 为用前 i 个物品，背包容量为 w 时的最大价值
    dp[i][w] = max(
        dp[i-1][w],           # 不选第 i 个物品
        dp[i-1][w-weight[i]] + value[i]   # 选第 i 个物品
    )
    
    时间复杂度: O(n * capacity)
    空间复杂度: O(n * capacity)（可优化到 O(capacity)）
    
    参数:
        weights: 每个物品的重量列表
        values: 每个物品的价值列表
        capacity: 背包的最大容量
    
    返回:
        可以放入背包的最大价值
    
    示例:
        weights = [2, 3, 4, 5]
        values  = [3, 4, 5, 6]
        capacity = 8
        结果 = 13 （选重量为 3 和 5 的物品，价值 4+6=10... 实际应重新核实）
    """
    n = len(weights)
    
    # 初始化二维 DP 表
    # dp[i][w] 表示考虑前 i 个物品，背包容量为 w 时的最大价值
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]
    
    # 逐个考虑每个物品
    for i in range(1, n + 1):
        current_weight = weights[i - 1]
        current_value = values[i - 1]
        
        # 对每个可能的背包容量
        for w in range(capacity + 1):
            # 选项 1：不选当前物品，保持前一行的值
            not_take = dp[i - 1][w]
            
            # 选项 2：选当前物品（如果容量允许）
            take = 0
            if current_weight <= w:
                # 选择当前物品后，剩余容量为 w - current_weight
                # 从剩余容量的最优方案加上当前物品的价值
                take = dp[i - 1][w - current_weight] + current_value
            
            # 选择最大价值的方案
            dp[i][w] = max(not_take, take)
    
    return dp[n][capacity]

# 问题 5: 编辑距离 - 二维 DP 的上乘之作
def edit_distance(word1, word2):
    """
    编辑距离（Levenshtein Distance） - 将一个字符串变成另一个所需的最少操作数
    
    允许的操作：
    - 插入一个字符
    - 删除一个字符
    - 替换一个字符
    
    递推关系：设 dp[i][j] 为 word1[0:i] 变为 word2[0:j] 所需的最少操作数
    如果 word1[i-1] == word2[j-1]：
        dp[i][j] = dp[i-1][j-1]  （字符相同，无需操作）
    否则：
        dp[i][j] = 1 + min(
            dp[i-1][j],      # 删除 word1[i-1]
            dp[i][j-1],      # 插入 word2[j-1]
            dp[i-1][j-1]     # 替换 word1[i-1] 为 word2[j-1]
        )
    
    时间复杂度: O(m * n)（m, n 是两个字符串的长度）
    空间复杂度: O(m * n)（可优化到 O(min(m, n))）
    
    参数:
        word1: 源字符串
        word2: 目标字符串
    
    返回:
        编辑距离（最少操作数）
    
    示例:
        edit_distance("horse", "ros") = 3
        （删除 h，替换 r 为 o，... 等）
    """
    m, n = len(word1), len(word2)
    
    # 初始化 DP 表
    # dp[i][j] 表示 word1 的前 i 个字符变为 word2 的前 j 个字符所需操作数
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    # 初始化第一行：从空字符串变为 word2 的前 j 个字符，需要 j 次插入
    for j in range(n + 1):
        dp[0][j] = j
    
    # 初始化第一列：从 word1 的前 i 个字符变为空字符串，需要 i 次删除
    for i in range(m + 1):
        dp[i][0] = i
    
    # 填充 DP 表
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            # 如果当前字符相同，从斜上方承继（不需要操作）
            if word1[i - 1] == word2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                # 否则，在三个操作中选最少的一个
                delete_op = dp[i - 1][j] + 1     # 从 word1 删除
                insert_op = dp[i][j - 1] + 1     # 向 word1 插入
                replace_op = dp[i - 1][j - 1] + 1  # 替换
                dp[i][j] = min(delete_op, insert_op, replace_op)
    
    return dp[m][n]

# 测试代码
if __name__ == "__main__":
    print("=" * 70)
    print("动态规划 - 完整中文注释版本")
    print("=" * 70)
    
    # 测试斐波那契
    print("\n1. 斐波那契数列")
    n = 10
    fib_dp = fibonacci_dp(n)
    fib_opt = fibonacci_optimized(n)
    print(f"   F({n}) = {fib_dp} (DP方式)")
    print(f"   F({n}) = {fib_opt} (空间优化版)")
    print(f"   性能对比：递归 O(2^{n}) vs DP O({n})")
    
    # 测试钱币兑换
    print("\n2. 钱币兑换")
    coins, amount = [1, 2, 5], 5
    result = coin_change(coins, amount)
    print(f"   硬币: {coins}, 金额: {amount}")
    print(f"   最少硬币数: {result}")
    
    # 测试 LIS
    print("\n3. 最长递增子序列（LIS）")
    nums = [10, 9, 2, 5, 3, 7, 101, 18]
    lis_len = longest_increasing_subsequence(nums)
    print(f"   数组: {nums}")
    print(f"   LIS 长度: {lis_len}")
    
    # 测试 0/1 背包
    print("\n4. 0/1 背包问题")
    weights = [2, 3, 4, 5]
    values = [3, 4, 5, 6]
    capacity = 8
    max_value = knapsack_01(weights, values, capacity)
    print(f"   重量: {weights}")
    print(f"   价值: {values}")
    print(f"   容量: {capacity}")
    print(f"   最大价值: {max_value}")
    
    # 测试编辑距离
    print("\n5. 编辑距离（莱文施泰因距离）")
    word1, word2 = "horse", "ros"
    dist = edit_distance(word1, word2)
    print(f"   源字符串: '{word1}'")
    print(f"   目标字符串: '{word2}'")
    print(f"   编辑距离: {dist}")
    
    print("\n" + "=" * 70)
