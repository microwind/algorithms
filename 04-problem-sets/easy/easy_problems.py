"""
简单问题集合

这个模块包含一些初级算法问题的解答
涵盖基础数据结构和算法
"""

# 1. 两数之和
def two_sum(nums, target):
    """
    给定数组和目标值，找到两个数使其和等于目标值
    时间复杂度: O(n), 空间复杂度: O(n)
    """
    seen = {}
    for i, num in enumerate(nums):
        complement = target - num
        if complement in seen:
            return [seen[complement], i]
        seen[num] = i
    return []

# 2. 回文数
def is_palindrome(x):
    """检查整数是否为回文"""
    if x < 0:
        return False
    original = x
    reversed_num = 0
    while x > 0:
        reversed_num = reversed_num * 10 + x % 10
        x //= 10
    return original == reversed_num

# 3. 最长公共前缀
def longest_common_prefix(strs):
    """找到字符串数组中的最长公共前缀"""
    if not strs:
        return ""
    
    for i in range(len(strs[0])):
        char = strs[0][i]
        for j in range(1, len(strs)):
            if i >= len(strs[j]) or strs[j][i] != char:
                return strs[0][:i]
    
    return strs[0]

# 4. 有效的括号
def is_valid_parentheses(s):
    """检查括号是否匹配"""
    stack = []
    pairs = {'(': ')', '{': '}', '[': ']'}
    
    for char in s:
        if char in pairs:
            stack.append(char)
        else:
            if not stack or pairs[stack.pop()] != char:
                return False
    
    return len(stack) == 0

# 5. 删除重复元素
def remove_duplicates(nums):
    """
    删除排序数组中的重复元素
    时间复杂度: O(n), 空间复杂度: O(1)
    """
    if not nums:
        return 0
    
    i = 0
    for j in range(1, len(nums)):
        if nums[j] != nums[i]:
            i += 1
            nums[i] = nums[j]
    
    return i + 1

if __name__ == "__main__":
    print("=== 简单问题集合 ===\n")
    
    print("1. 两数之和")
    print(two_sum([2, 7, 11, 15], 9))
    
    print("\n2. 回文数")
    print(is_palindrome(121))
    
    print("\n3. 最长公共前缀")
    print(longest_common_prefix(["flower", "flow", "flight"]))
    
    print("\n4. 有效的括号")
    print(is_valid_parentheses("()[]{}"))
    
    print("\n5. 删除重复元素")
    nums = [1, 1, 2, 2, 3]
    print(f"长度: {remove_duplicates(nums)}")
