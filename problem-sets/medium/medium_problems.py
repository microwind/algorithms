"""
中等问题集合

这个模块包含一些中级算法问题的解答
涉及动态规划、图论、深度搜索等
"""

# 1. 三数之和
def three_sum(nums):
    """找到所有和为 0 的三元组"""
    nums.sort()
    result = []
    
    for i in range(len(nums) - 2):
        if nums[i] > 0:
            break
        if i > 0 and nums[i] == nums[i - 1]:
            continue
        
        left, right = i + 1, len(nums) - 1
        while left < right:
            total = nums[i] + nums[left] + nums[right]
            if total == 0:
                result.append([nums[i], nums[left], nums[right]])
                while left < right and nums[left] == nums[left + 1]:
                    left += 1
                while left < right and nums[right] == nums[right - 1]:
                    right -= 1
                left += 1
                right -= 1
            elif total < 0:
                left += 1
            else:
                right -= 1
    
    return result

# 2. 最长子串
def longest_substring_without_repeating(s):
    """找到最长不重复子串的长度"""
    char_index = {}
    max_length = 0
    start = 0
    
    for i, char in enumerate(s):
        if char in char_index:
            start = max(start, char_index[char] + 1)
        char_index[char] = i
        max_length = max(max_length, i - start + 1)
    
    return max_length

# 3. 最长递增子序列
def longest_increasing_subsequence(nums):
    """找到最长递增子序列的长度"""
    if not nums:
        return 0
    
    dp = [1] * len(nums)
    for i in range(1, len(nums)):
        for j in range(i):
            if nums[j] < nums[i]:
                dp[i] = max(dp[i], dp[j] + 1)
    
    return max(dp)

# 4. 单词搜索
def word_search(board, word):
    """在二维网格中搜索单词"""
    if not board or not word:
        return False
    
    def dfs(i, j, index):
        if index == len(word):
            return True
        if i < 0 or i >= len(board) or j < 0 or j >= len(board[0]):
            return False
        if board[i][j] != word[index]:
            return False
        
        # 标记为已访问
        board[i][j] = '#'
        
        # 搜索四个方向
        result = (dfs(i + 1, j, index + 1) or
                 dfs(i - 1, j, index + 1) or
                 dfs(i, j + 1, index + 1) or
                 dfs(i, j - 1, index + 1))
        
        # 恢复
        board[i][j] = word[index]
        return result
    
    for i in range(len(board)):
        for j in range(len(board[0])):
            if dfs(i, j, 0):
                return True
    
    return False

if __name__ == "__main__":
    print("=== 中等问题集合 ===\n")
    
    print("1. 三数之和")
    print(three_sum([-1, 0, 1, 2, -1, -4]))
    
    print("\n2. 最长不重复子串")
    print(longest_substring_without_repeating("abcabcbb"))
    
    print("\n3. 最长递增子序列")
    print(longest_increasing_subsequence([10, 9, 2, 5, 3, 7, 101, 18]))
