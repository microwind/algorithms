"""
字符串递归操作
演示递归在字符串处理中的应用
"""


def reverse_string(s):
    """
    递归反转字符串
    思路：将字符串分为第一个字符 + 剩余部分
    """
    # 基础情况：空字符串或单个字符
    if len(s) <= 1:
        return s
    
    # 递归：剩余部分反转 + 第一个字符放到末尾
    return reverse_string(s[1:]) + s[0]


def is_palindrome(s):
    """
    递归检查字符串是否为回文
    思路：比较首尾字符，然后递归检查中间部分
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
    """
    vowels = 'aeiouAEIOU'
    
    # 基础情况：空字符串
    if not s:
        return 0
    
    # 检查第一个字符是否是元音
    first_is_vowel = 1 if s[0] in vowels else 0
    
    # 递归计算剩余部分
    return first_is_vowel + count_vowels(s[1:])


# 测试示例
if __name__ == "__main__":
    print("=" * 40)
    print("字符串递归操作示例")
    print("=" * 40)
    
    # 测试字符串反转
    test_str = "Hello"
    print(f"\n1. 字符串反转:")
    print(f"   原字符串: '{test_str}'")
    print(f"   反转后:   '{reverse_string(test_str)}'")
    
    # 测试回文检查
    test_cases = ["radar", "hello", "Aba", "level"]
    print(f"\n2. 回文检查:")
    for s in test_cases:
        result = "是回文" if is_palindrome(s) else "不是回文"
        print(f"   '{s}' -> {result}")
    
    # 测试元音计数
    test_str2 = "Hello World"
    print(f"\n3. 元音计数:")
    print(f"   字符串: '{test_str2}'")
    print(f"   元音数量: {count_vowels(test_str2)}")
    
    print("\n" + "=" * 40)
