"""
Copyright © https://github.com/microwind All rights reserved.

@author: jarryli@gmail.com
@version: 1.0
"""

import math

"""
字符串算法 - 编辑距离 (Edit Distance / Levenshtein Distance)

算法原理：
1. 计算将一个字符串转换为另一个字符串所需的最少操作次数。
2. 允许的操作包括：插入、删除、替换。
3. 使用动态规划（DP）求解。

时间复杂度：O(m * n)
空间复杂度：O(m * n)，可优化至 O(min(m, n))
"""

def edit_distance(word1, word2):
    """
    动态规划版本 - 计算编辑距离
    """
    n, m = len(word1), len(word2)
    # dp[i][j] 表示 word1[0..i-1] 转换为 word2[0..j-1] 的最小操作数
    dp = [[0] * (m + 1) for _ in range(n + 1)]

    # 初始化边界
    for i in range(n + 1):
        dp[i][0] = i
    for j in range(m + 1):
        dp[0][j] = j

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if word1[i - 1] == word2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = 1 + min(
                    dp[i - 1][j],    # 删除
                    dp[i][j - 1],    # 插入
                    dp[i - 1][j - 1] # 替换
                )
    return dp[n][m]

def edit_distance_optimized(word1, word2):
    """
    空间优化后的动态规划版本
    """
    if len(word1) < len(word2):
        word1, word2 = word2, word1
    
    n, m = len(word1), len(word2)
    prev = list(range(m + 1))
    curr = [0] * (m + 1)

    for i in range(1, n + 1):
        curr[0] = i
        for j in range(1, m + 1):
            if word1[i - 1] == word2[j - 1]:
                curr[j] = prev[j - 1]
            else:
                curr[j] = 1 + min(prev[j], curr[j - 1], prev[j - 1])
        prev = curr[:]
    return prev[m]

def edit_distance_recursive(word1, word2):
    """
    递归版本（结合记忆化）
    """
    memo = {}

    def helper(i, j):
        if i == 0: return j
        if j == 0: return i
        if (i, j) in memo:
            return memo[(i, j)]
        
        if word1[i - 1] == word2[j - 1]:
            res = helper(i - 1, j - 1)
        else:
            res = 1 + min(
                helper(i - 1, j),    # 删除
                helper(i, j - 1),    # 插入
                helper(i - 1, j - 1) # 替换
            )
        memo[(i, j)] = res
        return res

    return helper(len(word1), len(word2))

def get_edit_operations(word1, word2):
    """
    获取具体的编辑操作步骤
    """
    n, m = len(word1), len(word2)
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(n + 1): dp[i][0] = i
    for j in range(m + 1): dp[0][j] = j
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if word1[i - 1] == word2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])

    ops = []
    i, j = n, m
    while i > 0 or j > 0:
        if i > 0 and j > 0 and word1[i - 1] == word2[j - 1]:
            i -= 1
            j -= 1
        elif i > 0 and j > 0 and dp[i][j] == dp[i - 1][j - 1] + 1:
            ops.insert(0, f"替换 '{word1[i - 1]}' 为 '{word2[j - 1]}'")
            i -= 1
            j -= 1
        elif i > 0 and dp[i][j] == dp[i - 1][j] + 1:
            ops.insert(0, f"删除 '{word1[i - 1]}'")
            i -= 1
        else:
            ops.insert(0, f"插入 '{word2[j - 1]}'")
            j -= 1
    return ops

def get_similarity_ratio(word1, word2):
    """
    计算相似度
    """
    distance = edit_distance(word1, word2)
    max_len = max(len(word1), len(word2))
    return 1.0 if max_len == 0 else 1.0 - distance / max_len

if __name__ == "__main__":
    print("=" * 50)
    print("编辑距离 (Edit Distance) - Python 实现")
    print("=" * 50)

    test_cases = [
        ("kitten", "sitting"),
        ("sunday", "saturday"),
        ("abc", ""),
        ("", "abc"),
        ("same", "same")
    ]

    for s1, s2 in test_cases:
        print(f"\n源字符串: \"{s1}\"")
        print(f"目标字符串: \"{s2}\"")
        print(f"最小编辑距离 (DP): {edit_distance(s1, s2)}")
        print(f"最小编辑距离 (优化DP): {edit_distance_optimized(s1, s2)}")
        print(f"最小编辑距离 (递归): {edit_distance_recursive(s1, s2)}")
        print(f"相似度: {get_similarity_ratio(s1, s2):.2%}")
        if len(s1) < 10 and len(s2) < 10:
            print("操作步骤:", " -> ".join(get_edit_operations(s1, s2)))
