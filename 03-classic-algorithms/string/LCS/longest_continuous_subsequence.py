"""
最长公共子序列（LCS）问题有两种方式定义子序列，一种是子序列不要求连续，一种是子序列要求连续。
下面介绍要求子序列必须是连续的情况下，如何用算法解决最长公共子序列问题。

以两个字符串 “abcdea”和“aebcda”为例，如果子序列不要求连续，其最长公共子序列为“abcda”，
如果子序列要求是连续，则其最长公共子序列应为“bcd”。在这种情况下，有可能两个字符串出现多个长度相同的
公共子串，比如“askdfiryetd”和“trkdffirey”两个字符串就存在两个长度为3的公共子串，分别是“kdf”和“fir”，
因此问题的性质发生了变化，需要找出两个字符串所有可能存在公共子串的情况，然后取最长的一个，如果有多个
最长的公共子串，只取其中一个即可。
"""
def longest_continuous_subsequence(str1, str2):
    """
    最长公共子串（连续）求解函数
    
    功能：找到两个字符串中最长的连续公共子串（字符顺序一致且连续相邻）
    
    参数：
        str1: 第一个输入字符串
        str2: 第二个输入字符串
        
    返回值：
        一个元组，包含最长公共子串的长度和具体内容
    """
    len1 = len(str1)
    len2 = len(str2)
    
    # 特殊情况处理
    if len1 == 0 or len2 == 0:
        return 0, ""
    
    # 创建DP表
    # dp[i][j]表示以str1[i-1]和str2[j-1]为结尾的最长公共子串长度
    dp = [[0] * (len2 + 1) for _ in range(len1 + 1)]
    
    max_length = 0  # 记录最长公共子串的长度
    end_index = 0   # 记录最长公共子串在str1中的结束索引
    
    # 填充DP表
    for i in range(1, len1 + 1):
        for j in range(1, len2 + 1):
            if str1[i-1] == str2[j-1]:
                # 当前字符相同，长度 = 前一位的长度 + 1（连续累加）
                dp[i][j] = dp[i-1][j-1] + 1
                
                # 更新最长长度和结束索引
                if dp[i][j] > max_length:
                    max_length = dp[i][j]
                    end_index = i  # 记录在str1中的结束位置
            else:
                # 字符不同，连续中断，长度重置为0
                dp[i][j] = 0
    
    # 提取最长公共子串
    # 从结束索引向前推max_length个字符
    start_index = end_index - max_length
    longest_substring = str1[start_index:end_index]
    
    return max_length, longest_substring


# 测试用例
def test_longest_continuous_subsequence():
    test_cases = [
        ("ABCBDAB", "BDCAB", 2, ["BC", "AB"]),  # 最长连续子串长度为2
        ("HELLO", "HELLO", 5, ["HELLO"]),
        ("ABCDEF", "ACE", 1, ["A", "C", "E"]),   # 非连续，所以最长为1
        ("ABCDXYZ", "XYZABCD", 4, ["ABCD"]),
        ("12345", "54321", 1, ["1", "2", "3", "4", "5"]),
        ("ABABC", "BABCA", 4, ["ABCA", "BABC"]),
    ]
    
    for i, (s1, s2, expected_len, possible_results) in enumerate(test_cases, 1):
        print(f"测试用例 {i}:")
        print(f"字符串1: {s1}")
        print(f"字符串2: {s2}")
        
        actual_len, actual_result = longest_continuous_subsequence(s1, s2)
        
        len_match = actual_len == expected_len
        result_match = actual_result in possible_results
        
        print(f"预期长度: {expected_len}, 实际长度: {actual_len} → {'通过' if len_match else '失败'}")
        print(f"预期结果之一: {possible_results[0]}, 实际结果: {actual_result} → {'通过' if result_match else '失败'}")
        print(f"测试结果: {'全部通过' if len_match and result_match else '存在问题'}\n")


if __name__ == "__main__":
    # 示例
    s1 = "ABCBDAB"
    s2 = "BDCAB"
    length, substring = longest_continuous_subsequence(s1, s2)
    print(f"示例:")
    print(f"字符串1: {s1}")
    print(f"字符串2: {s2}")
    print(f"最长公共子串长度: {length}")
    print(f"最长公共子串: {substring}\n")
    
    # 运行测试
    test_longest_continuous_subsequence()

"""
jarry@Mac LCS % python longest_continuous_subsequence.py
示例:
字符串1: ABCBDAB
字符串2: BDCAB
最长公共子串长度: 2
最长公共子串: AB

测试用例 1:
字符串1: ABCBDAB
字符串2: BDCAB
预期长度: 2, 实际长度: 2 → 通过
预期结果之一: BC, 实际结果: AB → 通过
测试结果: 全部通过

测试用例 2:
字符串1: HELLO
字符串2: HELLO
预期长度: 5, 实际长度: 5 → 通过
预期结果之一: HELLO, 实际结果: HELLO → 通过
测试结果: 全部通过

测试用例 3:
字符串1: ABCDEF
字符串2: ACE
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: A, 实际结果: A → 通过
测试结果: 全部通过

测试用例 4:
字符串1: ABCDXYZ
字符串2: XYZABCD
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: ABCD, 实际结果: ABCD → 通过
测试结果: 全部通过

测试用例 5:
字符串1: 12345
字符串2: 54321
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: 1, 实际结果: 1 → 通过
测试结果: 全部通过

测试用例 6:
字符串1: ABABC
字符串2: BABCA
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: ABCA, 实际
"""