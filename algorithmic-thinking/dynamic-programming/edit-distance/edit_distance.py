"""
编辑距离 (Edit Distance / Levenshtein Distance) - 动态规划应用

问题描述：
给定两个字符串，计算从一个字符串转换到另一个字符串所需的最少编辑操作数
允许的操作：插入、删除、替换

例如：s1 = "horse", s2 = "ros"
h o r s e
  r o s

最少需要 3 次操作：删除 h，删除 e，替换 h -> r

动态规划方程：
dp[i][j] = 转换 s1[0:i] 到 s2[0:j] 的最少操作数

if s1[i-1] == s2[j-1]:
    dp[i][j] = dp[i-1][j-1]
else:
    dp[i][j] = 1 + min(
        dp[i-1][j],      # 删除
        dp[i][j-1],      # 插入
        dp[i-1][j-1]     # 替换
    )

时间复杂度: O(m * n)，其中 m, n 是两个字符串的长度
空间复杂度: O(m * n)，可以优化为 O(min(m, n))

特点：
- 经典 DP 问题
- 常见的编辑算法
- 多种优化方案
"""

def edit_distance(s1, s2):
    """
    编辑距离 - 求最少操作数

    参数:
        s1: 源字符串
        s2: 目标字符串

    返回:
        最少编辑操作数
    """
    m, n = len(s1), len(s2)

    # dp[i][j] 表示将 s1[0:i] 转换到 s2[0:j] 的最少操作数
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    # 初始化：从空字符串转换到 s2 的前 j 个字符，需要 j 次插入
    for j in range(n + 1):
        dp[0][j] = j

    # 初始化：从 s1 的前 i 个字符转换到空字符串，需要 i 次删除
    for i in range(m + 1):
        dp[i][0] = i

    # 填充 DP 表
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s1[i - 1] == s2[j - 1]:
                # 字符相同，不需要操作
                dp[i][j] = dp[i - 1][j - 1]
            else:
                # 字符不同，选择最少操作数的方案
                dp[i][j] = 1 + min(
                    dp[i - 1][j],      # 删除
                    dp[i][j - 1],      # 插入
                    dp[i - 1][j - 1]   # 替换
                )

    return dp[m][n]


def edit_distance_optimized(s1, s2):
    """
    编辑距离 - 空间优化版本

    使用一维数组代替二维数组，空间复杂度为 O(min(m, n))

    参数:
        s1: 源字符串
        s2: 目标字符串

    返回:
        最少编辑操作数
    """
    # 确保 s1 是较短的字符串
    if len(s1) > len(s2):
        s1, s2 = s2, s1

    m, n = len(s1), len(s2)

    # 使用两行数组来计算
    prev = list(range(n + 1))

    for i in range(1, m + 1):
        curr = [i] + [0] * n

        for j in range(1, n + 1):
            if s1[i - 1] == s2[j - 1]:
                curr[j] = prev[j - 1]
            else:
                curr[j] = 1 + min(prev[j], curr[j - 1], prev[j - 1])

        prev = curr

    return prev[n]


def edit_distance_with_operations(s1, s2):
    """
    编辑距离 - 返回具体的编辑操作

    参数:
        s1: 源字符串
        s2: 目标字符串

    返回:
        (最少操作数, 操作列表)
    """
    m, n = len(s1), len(s2)

    # dp[i][j] 表示将 s1[0:i] 转换到 s2[0:j] 的最少操作数
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    # 初始化
    for j in range(n + 1):
        dp[0][j] = j
    for i in range(m + 1):
        dp[i][0] = i

    # 填充 DP 表
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = 1 + min(
                    dp[i - 1][j],      # 删除
                    dp[i][j - 1],      # 插入
                    dp[i - 1][j - 1]   # 替换
                )

    # 反向追踪构建操作序列
    operations = []
    i, j = m, n
    while i > 0 or j > 0:
        if i == 0:
            # 只剩 s2，需要插入
            operations.append(f"Insert {s2[j - 1]} at position {i}")
            j -= 1
        elif j == 0:
            # 只剩 s1，需要删除
            operations.append(f"Delete {s1[i - 1]} at position {i}")
            i -= 1
        elif s1[i - 1] == s2[j - 1]:
            # 字符相同，无需操作
            i -= 1
            j -= 1
        elif dp[i - 1][j - 1] <= dp[i - 1][j] and dp[i - 1][j - 1] <= dp[i][j - 1]:
            # 替换
            operations.append(f"Replace {s1[i - 1]} with {s2[j - 1]} at position {i}")
            i -= 1
            j -= 1
        elif dp[i - 1][j] <= dp[i][j - 1]:
            # 删除
            operations.append(f"Delete {s1[i - 1]} at position {i}")
            i -= 1
        else:
            # 插入
            operations.append(f"Insert {s2[j - 1]} at position {i}")
            j -= 1

    operations.reverse()
    return dp[m][n], operations


if __name__ == "__main__":
    print("=== 编辑距离问题 ===\n")

    # 测试用例1：基本编辑距离
    print("1. 基本编辑距离")
    s1_1, s2_1 = "horse", "ros"
    print(f"字符串1: {s1_1}")
    print(f"字符串2: {s2_1}")
    print(f"编辑距离: {edit_distance(s1_1, s2_1)}\n")

    # 测试用例2：相同字符串
    print("2. 相同字符串")
    s1_2, s2_2 = "hello", "hello"
    print(f"字符串1: {s1_2}")
    print(f"字符串2: {s2_2}")
    print(f"编辑距离: {edit_distance(s1_2, s2_2)}\n")

    # 测试用例3：空字符串
    print("3. 空字符串")
    s1_3, s2_3 = "abc", ""
    print(f"字符串1: {s1_3}")
    print(f"字符串2: {s2_3}")
    print(f"编辑距离: {edit_distance(s1_3, s2_3)}\n")

    # 测试用例4：返回编辑操作
    print("4. 返回编辑操作")
    s1_4, s2_4 = "kitten", "sitting"
    print(f"字符串1: {s1_4}")
    print(f"字符串2: {s2_4}")
    distance, operations = edit_distance_with_operations(s1_4, s2_4)
    print(f"编辑距离: {distance}")
    print("编辑操作:")
    for op in operations:
        print(f"  {op}\n")

    # 测试用例5：优化版本
    print("5. 优化版本")
    s1_5, s2_5 = "intention", "execution"
    print(f"字符串1: {s1_5}")
    print(f"字符串2: {s2_5}")
    print(f"编辑距离（优化）: {edit_distance_optimized(s1_5, s2_5)}")
