"""
字符串算法 - 字符串反转 (String Reversal)
多种方法实现字符串反转
"""


def reverse_slicing(s):
    """使用切片反转字符串 - Pythonic"""
    return s[::-1]


def reverse_loop(s):
    """使用循环反转字符串"""
    result = ""
    for char in s:
        result = char + result
    return result


def reverse_recursive(s):
    """递归反转字符串"""
    if len(s) <= 1:
        return s
    return reverse_recursive(s[1:]) + s[0]


def reverse_two_pointer(s):
    """双指针法反转字符串"""
    chars = list(s)
    left, right = 0, len(chars) - 1
    
    while left < right:
        chars[left], chars[right] = chars[right], chars[left]
        left += 1
        right -= 1
    
    return "".join(chars)


def reverse_words(sentence):
    """反转句子中的单词顺序"""
    words = sentence.split()
    return " ".join(reversed(words))


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("字符串反转 (String Reversal)")
    print("=" * 50)
    
    test_strings = [
        "Hello",
        "Python",
        "algorithm",
        "A man a plan a canal Panama",
    ]
    
    print("\n不同反转方法对比:")
    for s in test_strings:
        print(f"\n原字符串: '{s}'")
        print(f"  切片法:   '{reverse_slicing(s)}'")
        print(f"  循环法:   '{reverse_loop(s)}'")
        print(f"  递归法:   '{reverse_recursive(s)}'")
        print(f"  双指针:   '{reverse_two_pointer(s)}'")
    
    # 句子单词反转
    sentence = "Hello World Python"
    print(f"\n\n句子反转:")
    print(f"  原句: '{sentence}'")
    print(f"  单词反转: '{reverse_words(sentence)}'")
