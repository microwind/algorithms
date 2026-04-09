# Copyright © https://github.com/microwind All rights reserved.
# @author: jarryli@gmail.com
# @version: 1.0

"""
动态规划记忆化示例 - 斐波那契数列

算法特点：
- 使用记忆化避免重复计算
- 将递归转换为动态规划
- 时间复杂度: O(n)，空间复杂度: O(n)

学习重点：理解记忆化在递归优化中的应用
"""

# 全局记忆化数组
memo = {}

def fibonacci_memo(n):
    """
    记忆化计算斐波那契数列
    时间复杂度: O(n)，空间复杂度: O(n)
    @param n 要计算的项数
    @return 斐波那契数值
    """
    # 基本情况
    if n <= 1:
        return n
    
    # 检查是否已经计算过
    if n in memo:
        return memo[n]
    
    # 递归计算并存储结果
    memo[n] = fibonacci_memo(n - 1) + fibonacci_memo(n - 2)
    return memo[n]

# 主函数 - 测试记忆化算法
def main():
    # 测试1：计算斐波那契数列
    test_numbers = [10, 20, 30]
    print("1. 记忆化算法 - 斐波那契数列:")
    for num in test_numbers:
        # 清空记忆化数组
        memo.clear()
        result = fibonacci_memo(num)
        print(f"   F({num}) = {result}")
    print("===")
    
    # 测试2：边界测试
    print("2. 边界测试:")
    for num in [0, 1, 2]:
        memo.clear()
        result = fibonacci_memo(num)
        print(f"   F({num}) = {result}")
    print("===")
    
    # 测试3：性能对比
    print("3. 性能对比:")
    import time
    
    # 普通递归版本
    def fibonacci_normal(n):
        if n <= 1:
            return n
        return fibonacci_normal(n - 1) + fibonacci_normal(n - 2)
    
    # 测试性能
    test_num = 35
    memo.clear()
    
    start_time = time.time()
    memo_result = fibonacci_memo(test_num)
    memo_time = time.time() - start_time
    
    start_time = time.time()
    normal_result = fibonacci_normal(test_num)
    normal_time = time.time() - start_time
    
    print(f"   F({test_num}) 记忆化: {memo_time:.6f}s")
    print(f"   F({test_num}) 普通递归: {normal_time:.6f}s")
    print(f"   性能提升: {normal_time/memo_time:.1f}x")
    print("===")

# 打印结果
"""
jarry@Mac dp-memoization % python fibonacci_memo.py
1. 记忆化算法 - 斐波那契数列:
   F(10) = 55
   F(20) = 6765
   F(30) = 832040
===
2. 边界测试:
   F(0) = 0
   F(1) = 1
   F(2) = 1
===
3. 性能对比:
   F(35) 记忆化: 0.000012s
   F(35) 普通递归: 0.267721s
   性能提升: 22310.1x
===
"""

if __name__ == "__main__":
    main()
