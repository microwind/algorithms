"""
字符串算法 - 编辑距离 (Edit Distance / Levenshtein Distance)
计算将一个字符串转换为另一个字符串所需的最少操作次数
操作包括：插入、删除、替换
"""


def edit_distance_dp(s1, s2):
    """
    动态规划计算编辑距离
    时间复杂度: O(m × n)
    空间复杂度: O(m × n)
    """
    m, n = len(s1), len(s2)
    
    # dp[i][j] 表示 s1[0..i-1] 转换为 s2[0..j-1] 的最小操作数
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    # 初始化边界
    for i in range(m + 1):
        dp[i][0] = i  # 需要i次删除
    for j in range(n + 1):
        dp[0][j] = j  # 需要j次插入
    
    # 填充DP表
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]  # 字符相同，无需操作
            else:
                dp[i][j] = 1 + min(
                    dp[i - 1][j],      # 删除
                    dp[i][j - 1],      # 插入
                    dp[i - 1][j - 1]   # 替换
                )
    
    return dp[m][n]


def edit_distance_optimized(s1, s2):
    """
    空间优化的编辑距离
    只使用两行数组
    空间复杂度: O(min(m, n))
    """
    # 确保s1是较短的字符串
    if len(s1) > len(s2):
        s1, s2 = s2, s1
    
    m, n = len(s1), len(s2)
    
    # 只使用两行
    prev = list(range(m + 1))
    curr = [0] * (m + 1)
    
    for j in range(1, n + 1):
        curr[0] = j
        for i in range(1, m + 1):
            if s1[i - 1] == s2[j - 1]:
                curr[i] = prev[i - 1]
            else:
                curr[i] = 1 + min(prev[i],      # 删除
                                 curr[i - 1],   # 插入
                                 prev[i - 1])   # 替换
        prev, curr = curr, prev
    
    return prev[m]


def similarity_ratio(s1, s2):
    """
    计算字符串相似度
    返回值: 0.0 - 1.0，1.0表示完全相同
    """
    max_len = max(len(s1), len(s2))
    if max_len == 0:
        return 1.0
    
    distance = edit_distance_optimized(s1, s2)
    return 1.0 - distance / max_len


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("编辑距离 (Edit Distance)")
    print("=" * 50)
    
    test_cases = [
        ("kitten", "sitting"),
        ("sunday", "saturday"),
        ("intention", "execution"),
        ("algorithm", "logarithm"),
    ]
    
    print("\n编辑距离计算:")
    for s1, s2 in test_cases:
        dist = edit_distance_optimized(s1, s2)
        sim = similarity_ratio(s1, s2)
        print(f"\n  '{s1}' -> '{s2}'")
        print(f"  编辑距离: {dist}")
        print(f"  相似度: {sim:.2%}")
    
    print("\n应用场景:")
    print("  • 拼写检查")
    print("  • DNA序列比对")
    print("  • 语音识别")
    print("  • 论文抄袭检测")
    print("  • Git diff算法")
