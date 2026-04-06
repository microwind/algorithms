# Copyright © https://github.com/microwind All rights reserved.
# @author: jarryli@gmail.com
# @version: 1.0

"""
字符串递归操作示例

算法特点：
- 演示递归在字符串处理中的应用
- 包含字符串反转、回文检查、元音计数

学习重点：理解递归在字符串操作中的使用
"""


def reverse_string(s):
    """
    递归反转字符串
    时间复杂度: O(n)，空间复杂度: O(n)
    @param s 要反转的字符串
    @return 反转后的字符串
    """
    # 基础情况：空字符串或单个字符
    if len(s) <= 1:
        return s
    
    # 递归：剩余部分反转 + 第一个字符放到末尾
    return reverse_string(s[1:]) + s[0]


def is_palindrome(s):
    """
    递归检查字符串是否为回文
    时间复杂度: O(n)，空间复杂度: O(n)
    @param s 要检查的字符串
    @return 是否为回文
    """
    s = s.lower()  # 忽略大小写
    
    # 基础情况：空字符串或单个字符是回文
    if len(s) <= 1:
        return True
    
    # 如果首尾字符不同，不是回文
    if s[0] != s[-1]:
        return False
    
    # 递归检查去掉首尾后的中间部分
    return is_palindrome(s[1:-1])


def count_vowels(s):
    """
    递归计算字符串中元音字母的数量
    时间复杂度: O(n)，空间复杂度: O(n)
    @param s 要计算的字符串
    @return 元音字母数量
    """
    vowels = 'aeiouAEIOU'
    
    # 基础情况：空字符串
    if not s:
        return 0
    
    # 检查第一个字符是否是元音
    first_is_vowel = 1 if s[0] in vowels else 0
    
    # 递归计算剩余部分
    return first_is_vowel + count_vowels(s[1:])


# 主函数 - 测试字符串递归操作
if __name__ == "__main__":
    # 测试1：字符串反转
    test_str = "Hello"
    print("1. 字符串反转:")
    print(f"   原字符串: '{test_str}'")
    print(f"   反转后:   '{reverse_string(test_str)}'")
    print("===")
    
    # 测试2：回文检查
    test_cases = ["radar", "hello", "Aba", "level", "aabbaa", "cc", "ddd"]
    print("2. 回文检查:")
    for s in test_cases:
        result = "是回文" if is_palindrome(s) else "不是回文"
        print(f"   '{s}' -> {result}")
    print("===")
    
    # 测试3：元音计数
    test_str2 = "Hello World"
    print("3. 元音计数:")
    print(f"   字符串: '{test_str2}'")
    print(f"   元音数量: {count_vowels(test_str2)}")
    print("===")

# 打印结果
"""
jarry@Mac string-recursion % python string_operations.py
1. 字符串反转:
   原字符串: 'Hello'
   反转后:   'olleH'
===
2. 回文检查:
   'radar' -> 是回文
   'hello' -> 不是回文
   'Aba' -> 是回文
   'level' -> 是回文
   'aabbaa' -> 是回文
   'cc' -> 是回文
   'ddd' -> 是回文
===
3. 元音计数:
   字符串: 'Hello World'
   元音数量: 3
===
"""
