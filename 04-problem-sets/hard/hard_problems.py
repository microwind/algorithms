"""
困难问题集合

这个模块包含一些高级算法问题
涉及复杂的数据结构和算法组合
"""

# 1. 正则表达式匹配
def is_match(s, p):
    """
    正则表达式匹配（简化版）
    支持 '.' 和 '*'
    """
    m, n = len(s), len(p)
    dp = [[False] * (n + 1) for _ in range(m + 1)]
    dp[0][0] = True
    
    for j in range(2, n + 1):
        if p[j - 1] == '*':
            dp[0][j] = dp[0][j - 2]
    
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if p[j - 1] == '*':
                dp[i][j] = dp[i][j - 2] or (
                    (s[i - 1] == p[j - 2] or p[j - 2] == '.') and dp[i - 1][j]
                )
            else:
                dp[i][j] = (s[i - 1] == p[j - 1] or p[j - 1] == '.') and dp[i - 1][j - 1]
    
    return dp[m][n]

# 2. 中位数查找
def find_median_sorted_arrays(nums1, nums2):
    """找到两个排序数组的中位数"""
    if len(nums1) > len(nums2):
        nums1, nums2 = nums2, nums1
    
    low, high = 0, len(nums1)
    
    while low <= high:
        cut1 = (low + high) // 2
        cut2 = (len(nums1) + len(nums2) + 1) // 2 - cut1
        
        left1 = float('-inf') if cut1 == 0 else nums1[cut1 - 1]
        left2 = float('-inf') if cut2 == 0 else nums2[cut2 - 1]
        right1 = float('inf') if cut1 == len(nums1) else nums1[cut1]
        right2 = float('inf') if cut2 == len(nums2) else nums2[cut2]
        
        if left1 <= right2 and left2 <= right1:
            if (len(nums1) + len(nums2)) % 2 == 0:
                return (max(left1, left2) + min(right1, right2)) / 2
            else:
                return max(left1, left2)
        elif left1 > right2:
            high = cut1 - 1
        else:
            low = cut1 + 1
    
    return -1

# 3. 最大矩形
def max_rectangle_area(matrix):
    """给定由 0 和 1 组成的矩阵，找最大的矩形面积"""
    if not matrix:
        return 0
    
    height = [0] * len(matrix[0])
    max_area = 0
    
    for row in matrix:
        for i in range(len(row)):
            height[i] = height[i] + 1 if row[i] == 1 else 0
        max_area = max(max_area, largest_rectangle_in_histogram(height))
    
    return max_area

def largest_rectangle_in_histogram(heights):
    """最大矩形直方图面积"""
    stack = []
    max_area = 0
    
    for i, h in enumerate(heights):
        while stack and heights[stack[-1]] > h:
            height = heights[stack.pop()]
            width = i if not stack else i - stack[-1] - 1
            max_area = max(max_area, height * width)
        stack.append(i)
    
    while stack:
        height = heights[stack.pop()]
        width = len(heights) if not stack else len(heights) - stack[-1] - 1
        max_area = max(max_area, height * width)
    
    return max_area

if __name__ == "__main__":
    print("=== 困难问题集合 ===\n")
    
    print("1. 正则表达式匹配")
    print(is_match("aa", "a") == False)
    print(is_match("aa", "a*") == True)
    
    print("\n2. 中位数")
    print(find_median_sorted_arrays([1, 3], [2]))
    
    print("\n3. 最大矩形面积")
    print(largest_rectangle_in_histogram([2, 1, 5, 6, 2, 3]))
