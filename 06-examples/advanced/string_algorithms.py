"""
高级字符串算法示例
"""

# KMP 算法 - 字符串匹配
def build_failure_function(pattern):
    """构建 KMP 失败函数"""
    m = len(pattern)
    failure = [0] * m
    j = 0
    
    for i in range(1, m):
        while j > 0 and pattern[i] != pattern[j]:
            j = failure[j - 1]
        if pattern[i] == pattern[j]:
            j += 1
        failure[i] = j
    
    return failure

def kmp_search(text, pattern):
    """KMP 字符串查找"""
    if not pattern:
        return 0
    
    failure = build_failure_function(pattern)
    matches = []
    j = 0
    
    for i in range(len(text)):
        while j > 0 and text[i] != pattern[j]:
            j = failure[j - 1]
        if text[i] == pattern[j]:
            j += 1
        if j == len(pattern):
            matches.append(i - len(pattern) + 1)
            j = failure[j - 1]
    
    return matches

# 最长公共子序列
def longest_common_subsequence(s1, s2):
    """LCS 动态规划"""
    m, n = len(s1), len(s2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    
    return dp[m][n]

if __name__ == "__main__":
    print("=== 字符串算法示例 ===\n")
    
    # KMP
    print("KMP 搜索:", kmp_search("ABABDABACDABABCABAB", "ABABCABAB"))
    
    # LCS
    print("最长公共子序列长度:", longest_common_subsequence("abcde", "ace"))
