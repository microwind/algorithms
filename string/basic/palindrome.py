"""
字符串算法 - 回文检查 (Palindrome Check)
多种方法检查字符串是否为回文
"""


def is_palindrome_two_pointer(s):
    """
    双指针法检查回文
    时间复杂度: O(n)
    空间复杂度: O(1)
    """
    left, right = 0, len(s) - 1
    
    while left < right:
        # 跳过非字母数字字符
        while left < right and not s[left].isalnum():
            left += 1
        while left < right and not s[right].isalnum():
            right -= 1
        
        if s[left].lower() != s[right].lower():
            return False
        
        left += 1
        right -= 1
    
    return True


def is_palindrome_reverse(s):
    """
    通过反转字符串检查回文
    时间复杂度: O(n)
    空间复杂度: O(n)
    """
    # 只保留字母数字并转为小写
    cleaned = ''.join(c.lower() for c in s if c.isalnum())
    return cleaned == cleaned[::-1]


def is_palindrome_recursive(s, left=0, right=None):
    """
    递归法检查回文
    时间复杂度: O(n)
    空间复杂度: O(n)（递归栈）
    """
    if right is None:
        s = ''.join(c.lower() for c in s if c.isalnum())
        right = len(s) - 1
    
    if left >= right:
        return True
    
    if s[left] != s[right]:
        return False
    
    return is_palindrome_recursive(s, left + 1, right - 1)


def longest_palindrome_substring(s):
    """
    查找最长回文子串
    使用中心扩展法
    """
    if not s:
        return ""
    
    start, max_len = 0, 1
    
    for i in range(len(s)):
        # 奇数长度回文
        len1 = expand_around_center(s, i, i)
        # 偶数长度回文
        len2 = expand_around_center(s, i, i + 1)
        
        length = max(len1, len2)
        if length > max_len:
            max_len = length
            start = i - (length - 1) // 2
    
    return s[start:start + max_len]


def expand_around_center(s, left, right):
    """中心扩展法辅助函数"""
    while left >= 0 and right < len(s) and s[left] == s[right]:
        left -= 1
        right += 1
    return right - left - 1


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("回文检查 (Palindrome Check)")
    print("=" * 50)
    
    test_cases = [
        "racecar",
        "A man a plan a canal Panama",
        "Was it a car or a cat I saw",
        "hello",
        "No lemon, no melon",
    ]
    
    print("\n回文检查结果:")
    for s in test_cases:
        result = "是回文" if is_palindrome_two_pointer(s) else "不是回文"
        print(f"  '{s[:30]}...': {result}" if len(s) > 30 else f"  '{s}': {result}")
    
    print("\n最长回文子串:")
    test_strings = ["babad", "cbbd", "a", "ac"]
    for s in test_strings:
        longest = longest_palindrome_substring(s)
        print(f"  '{s}' -> '{longest}'")
