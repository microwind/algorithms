"""
回溯算法 - 子集生成 (Subsets)
使用递归生成数组的所有子集
"""

def subsets(nums):
    """生成数组的所有子集"""
    result = []
    
    def backtrack(start, current):
        # 每次递归都将当前子集加入结果
        result.append(current[:])
        
        # 从start开始尝试每个元素
        for i in range(start, len(nums)):
            # 选择元素
            current.append(nums[i])
            
            # 递归：继续处理后面的元素
            backtrack(i + 1, current)
            
            # 回溯：撤销选择
            current.pop()
    
    backtrack(0, [])
    return result


# 示例
if __name__ == "__main__":
    nums = [1, 2, 3]
    result = subsets(nums)
    
    print(f"数组 {nums} 的所有子集:")
    print(f"共 {len(result)} 个子集\n")
    
    for i, subset in enumerate(result, 1):
        print(f"  {i}. {subset}")
    
    print("\n递归过程可视化:")
    print("        []")
    print("       / | \\")
    print("     [1] [2] [3]")
    print("    /  \\      |")
    print("  [1,2] [1,3] [2,3]")
    print("   /")
    print("[1,2,3]")
