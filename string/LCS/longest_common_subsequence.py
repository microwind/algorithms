def longest_common_subsequence(first_string, second_string):
    """
    最长公共子序列（LCS）求解函数
    
    功能：找到两个字符串中最长的公共子序列（字符顺序一致但不必连续）
    
    参数：
        first_string: 第一个输入字符串
        second_string: 第二个输入字符串
        
    返回值：
        一个元组，包含LCS的长度和LCS的具体内容
    
    举例：
        序列A为"abcdef"，序列B为"bcef"，
        最长公共子序列为"bcef"，
        注意最长公共子序列不用保证每一个字符必须连续。
        
    暴力做法思路：
        1. 选择一个参照序列（如A）
        2. 遍历参照序列的每一个字符作为公共子序列的头部
        3. 将该字符与另一序列的每个字符比较
        4. 若相等，则在两序列中都向后移动继续比较
        5. 遍历所有可能的头部，找到最长的子序列
        （注：本实现采用动态规划方法，效率远高于暴力法）
    """
    # 获取两个字符串的长度
    length_of_first = len(first_string)
    length_of_second = len(second_string)
    
    # 采用动态规划表来实现
    # 创建一个二维数组（DP表）来存储子问题的解
    # dp_table[i][j]表示first_string前i个字符与second_string前j个字符的LCS长度
    # 加1是为了处理空字符串的情况（i=0或j=0时）
    dp_table = [
        [0 for _ in range(length_of_second + 1)] 
        for _ in range(length_of_first + 1)
    ]
    
    # 填充DP表
    # 外层循环：遍历第一个字符串的每个字符（从第1个到最后一个）
    for i in range(1, length_of_first + 1):
        # 内层循环：遍历第二个字符串的每个字符（从第1个到最后一个）
        for j in range(1, length_of_second + 1):
            # 当前比较的字符（注意索引要减1，因为字符串是从0开始的）
            char_from_first = first_string[i - 1]
            char_from_second = second_string[j - 1]
            
            # 如果两个字符相同
            if char_from_first == char_from_second:
                # 那么当前LCS长度 = 两个字符串都去掉当前字符后的LCS长度 + 1
                dp_table[i][j] = dp_table[i - 1][j - 1] + 1
            else:
                # 如果字符不同，取两种情况的最大值：
                # 1. 去掉第一个字符串当前字符后的LCS长度
                # 2. 去掉第二个字符串当前字符后的LCS长度
                dp_table[i][j] = max(dp_table[i - 1][j], dp_table[i][j - 1])
    
    # 回溯找到具体的LCS序列
    # 创建一个列表来存储LCS的字符
    lcs_characters = []
    
    # 从DP表的右下角开始回溯（即两个字符串的最后一个字符）
    current_i = length_of_first
    current_j = length_of_second
    
    # 当两个指针都没有回到起点时继续回溯
    while current_i > 0 and current_j > 0:
        # 当前比较的字符
        current_char_first = first_string[current_i - 1]
        current_char_second = second_string[current_j - 1]
        
        # 如果字符相同，说明这个字符是LCS的一部分
        if current_char_first == current_char_second:
            lcs_characters.append(current_char_first)
            # 两个指针都向前移动一步
            current_i -= 1
            current_j -= 1
        else:
            # 如果字符不同，向LCS长度更大的方向移动
            if dp_table[current_i - 1][current_j] > dp_table[current_i][current_j - 1]:
                current_i -= 1  # 向上移动（舍弃第一个字符串的当前字符）
            else:
                current_j -= 1  # 向左移动（舍弃第二个字符串的当前字符）
    
    # 由于回溯是从后往前收集字符，所以需要反转得到正确的顺序
    lcs_content = ''.join(reversed(lcs_characters))
    
    # 返回LCS的长度和内容
    return dp_table[length_of_first][length_of_second], lcs_content


def run_lcs_tests():
    """运行最长公共子序列算法的测试用例集合"""
    # 定义测试用例：(字符串1, 字符串2, 预期长度, 可能的预期结果列表)
    test_cases = [
        # 测试用例1：基础示例
        (
            "ABCBDAB", 
            "BDCAB", 
            4, 
            ["BCAB", "BDAB"]  # 可能有多个正确结果
        ),
        
        # 测试用例2：完全相同的字符串
        (
            "HELLO", 
            "HELLO", 
            5, 
            ["HELLO"]
        ),
        
        # 测试用例3：一个字符串是另一个的子序列
        (
            "ABCDEF", 
            "ACE", 
            3, 
            ["ACE"]
        ),
        
        # 测试用例4：没有公共字符
        (
            "ABCD", 
            "EFGH", 
            0, 
            [""]
        ),
        
        # 测试用例5：其中一个是空字符串
        (
            "", 
            "TEST", 
            0, 
            [""]
        ),
        
        # 测试用例6：包含重复字符
        (
            "AABBAABB", 
            "ABAB", 
            4, 
            ["AABB", "ABAB", "ABBA"]
        ),
        
        # 测试用例7：长度不同的字符串
        (
            "XMJYAUZ", 
            "MZJAWXU", 
            4, 
            ["MJAU", "MZAU"]
        ),
        
        # 测试用例8：单个字符匹配
        (
            "A", 
            "A", 
            1, 
            ["A"]
        ),
        
        # 测试用例9：单个字符不匹配
        (
            "A", 
            "B", 
            0, 
            [""]
        ),
        
        # 测试用例10：数字和特殊字符
        (
            "123@abc", 
            "a3@x1", 
            3, 
            ["3@a", "1@a", "3a@"]  # 取决于回溯路径
        )
    ]
    
    # 执行测试
    for i, (s1, s2, expected_len, possible_results) in enumerate(test_cases, 1):
        print(f"\n测试用例 {i}:")
        print(f"字符串1: {s1}")
        print(f"字符串2: {s2}")
        
        actual_len, actual_result = longest_common_subsequence(s1, s2)
        
        # 验证长度
        len_match = actual_len == expected_len
        # 验证结果是否在可能的正确结果列表中
        result_match = actual_result in possible_results
        
        print(f"预期长度: {expected_len}, 实际长度: {actual_len} → {'通过' if len_match else '失败'}")
        print(f"预期结果之一: {possible_results[0]}, 实际结果: {actual_result} → {'通过' if result_match else '失败'}")
        print(f"测试结果: {'全部通过' if len_match and result_match else '存在问题'}")


# 程序入口
if __name__ == "__main__":
    # 示例用法
    string_one = "AABCBDAB"
    string_two = "ABDCAB"
    
    # 调用函数计算LCS
    lcs_length, lcs_result = longest_common_subsequence(string_one, string_two)
    
    # 输出结果
    print(f"示例计算结果：")
    print(f"第一个字符串: {string_one}")
    print(f"第二个字符串: {string_two}")
    print(f"最长公共子序列的长度: {lcs_length}")  # 输出5
    print(f"最长公共子序列的内容: {lcs_result}")  # 输出"ABDAB"或其他正确结果

    # 运行测试用例集合
    print("\n开始执行测试用例...")
    run_lcs_tests()

"""
jarry@Mac LCS % python longest_common_subsequence.py
示例计算结果：
第一个字符串: AABCBDAB
第二个字符串: ABDCAB
最长公共子序列的长度: 5
最长公共子序列的内容: ABDAB

开始执行测试用例...

测试用例 1:
字符串1: ABCBDAB
字符串2: BDCAB
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: BCAB, 实际结果: BDAB → 通过
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
预期长度: 3, 实际长度: 3 → 通过
预期结果之一: ACE, 实际结果: ACE → 通过
测试结果: 全部通过

测试用例 4:
字符串1: ABCD
字符串2: EFGH
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 5:
字符串1: 
字符串2: TEST
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 6:
字符串1: AABBAABB
字符串2: ABAB
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: AABB, 实际结果: ABAB → 通过
测试结果: 全部通过

测试用例 7:
字符串1: XMJYAUZ
字符串2: MZJAWXU
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: MJAU, 实际结果: MJAU → 通过
测试结果: 全部通过

测试用例 8:
字符串1: A
字符串2: A
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: A, 实际结果: A → 通过
测试结果: 全部通过

测试用例 9:
字符串1: A
字符串2: B
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 10:
字符串1: 123@abc
字符串2: a3@x1
预期长度: 3, 实际长度: 2 → 失败
预期结果之一: 3@a, 实际结果: 3@ → 失败
测试结果: 存在问题
"""