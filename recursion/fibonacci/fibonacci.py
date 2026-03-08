"""
斐波那契数列 - 多种实现方式对比

斐波那契数列: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34...
递推公式: F(n) = F(n-1) + F(n-2), F(0)=0, F(1)=1
"""

# 方法1: 纯递归（最慢）
def fib_naive(n):
    """O(2^n) 时间复杂度，不推荐"""
    if n <= 1:
        return n
    return fib_naive(n-1) + fib_naive(n-2)

# 方法2: 记忆化递归（推荐）
def fib_memo(n, cache=None):
    """O(n) 时间复杂度"""
    if cache is None:
        cache = {}
    
    if n in cache:
        return cache[n]
    
    if n <= 1:
        return n
    
    # 计算并缓存结果，避免重复计算
    cache[n] = fib_memo(n-1, cache) + fib_memo(n-2, cache)
    return cache[n]

# 方法3: 动态规划（最优）
def fib_dp(n):
    """O(n) 时间复杂度，O(n) 空间复杂度"""
    if n <= 1:
        return n
    
    dp = [0] * (n + 1)
    dp[1] = 1
    
    # 从2开始填充dp数组，直到n
    for i in range(2, n + 1):
        dp[i] = dp[i-1] + dp[i-2]
    
    return dp[n]

# 方法4: 优化动态规划（空间优化）
def fib_optimized(n):
    """O(n) 时间复杂度，O(1) 空间复杂度"""
    if n <= 1:
        return n
    
    prev, curr = 0, 1
    # 从2开始迭代计算，直到n
    for _ in range(2, n + 1):
        prev, curr = curr, prev + curr
    
    return curr

# 测试并对比
if __name__ == "__main__":
    n = 30
    print(f"计算第 {n} 个斐波那契数\n")
    
    import time
    
    # 记忆化递归
    start = time.time()
    result1 = fib_memo(n)
    time1 = time.time() - start
    print(f"记忆化递归: {result1}, 耗时: {time1:.6f}s")
    
    # 动态规划
    start = time.time()
    result2 = fib_dp(n)
    time2 = time.time() - start
    print(f"动态规划: {result2}, 耗时: {time2:.6f}s")
    
    # 优化动态规划
    start = time.time()
    result3 = fib_optimized(n)
    time3 = time.time() - start
    print(f"优化DP: {result3}, 耗时: {time3:.6f}s")
