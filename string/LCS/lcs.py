"""
字符串算法 - 最长公共子序列 (LCS)
使用动态规划求解两个字符串的最长公共子序列
"""


def lcs_length(str1, str2):
    """
    计算最长公共子序列的长度
    时间复杂度: O(m*n)
    空间复杂度: O(m*n)
    """
    m, n = len(str1), len(str2)
    
    # 创建DP表
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    # 填充DP表
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if str1[i - 1] == str2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    
    return dp[m][n]


def lcs_string(str1, str2):
    """
    返回最长公共子序列字符串
    """
    m, n = len(str1), len(str2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    # 填充DP表
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if str1[i - 1] == str2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    
    # 回溯构造LCS
    lcs = []
    i, j = m, n
    while i > 0 and j > 0:
        if str1[i - 1] == str2[j - 1]:
            lcs.append(str1[i - 1])
            i -= 1
            j -= 1
        elif dp[i - 1][j] > dp[i][j - 1]:
            i -= 1
        else:
            j -= 1
    
    return ''.join(reversed(lcs))


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("最长公共子序列 (LCS)")
    print("=" * 50)
    
    test_cases = [
        ("ABCDGH", "AEDFHR"),
        ("AGGTAB", "GXTXAYB"),
        ("programming", "gaming"),
    ]
    
    for str1, str2 in test_cases:
        length = lcs_length(str1, str2)
        lcs = lcs_string(str1, str2)
        print(f"\n字符串1: {str1}")
        print(f"字符串2: {str2}")
        print(f"LCS长度: {length}")
        print(f"LCS内容: '{lcs}'")
