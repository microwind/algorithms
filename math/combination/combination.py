"""
数学算法 - 组合数计算 (Combination / Binomial Coefficient)
计算 C(n,k) = n! / (k! * (n-k)!)
使用多种方法：递归公式、动态规划、乘法公式
"""


def combination_dp(n, k):
    """
    使用动态规划计算组合数
    利用公式：C(n,k) = C(n-1,k-1) + C(n-1,k)
    
    时间复杂度: O(n*k)
    空间复杂度: O(k)
    """
    k = min(k, n - k)  # 利用对称性减少计算
    
    dp = [0] * (k + 1)
    dp[0] = 1  # C(n,0) = 1
    
    for i in range(1, n + 1):
        for j in range(min(i, k), 0, -1):
            dp[j] = dp[j] + dp[j - 1]
    
    return dp[k]


def combination_multiplicative(n, k):
    """
    使用乘法公式计算组合数
    C(n,k) = n * (n-1) * ... * (n-k+1) / (k * (k-1) * ... * 1)
    
    适合计算单个组合数，避免计算阶乘
    """
    k = min(k, n - k)
    
    result = 1
    for i in range(k):
        result = result * (n - i) // (i + 1)
    
    return result


def pascal_triangle(n):
    """
    生成前n行的杨辉三角
    每行的数字就是对应的组合数
    """
    triangle = []
    
    for i in range(n):
        row = [1] * (i + 1)
        for j in range(1, i):
            row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j]
        triangle.append(row)
    
    return triangle


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("组合数计算 (Combination)")
    print("=" * 50)
    
    print("\n组合数 C(n,k):")
    test_cases = [
        (5, 2),
        (10, 3),
        (20, 10),
        (100, 50),
    ]
    
    for n, k in test_cases:
        result_dp = combination_dp(n, k)
        result_mul = combination_multiplicative(n, k)
        print(f"  C({n},{k}) = {result_dp}")
    
    print("\n杨辉三角 (前7行):")
    triangle = pascal_triangle(7)
    for i, row in enumerate(triangle):
        spaces = " " * (20 - i * 2)
        print(f"{spaces}{' '.join(str(x) for x in row)}")
    
    print("\n应用场景:")
    print("  • 从n个物品中选k个的组合数")
    print("  • 二项式展开系数")
    print("  • 概率计算")
