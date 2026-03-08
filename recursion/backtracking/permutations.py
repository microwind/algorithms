"""
回溯算法 - 全排列 (Permutations)
使用递归生成数组的所有排列
"""

def permutations(nums):
    """生成数组的所有排列"""
    result = []
    
    def backtrack(current, remaining):
        # 基础情况：没有剩余元素，找到一个排列
        if not remaining:
            result.append(current[:])
            return
        
        # 递归情况：尝试每个剩余元素
        for i in range(len(remaining)):
            # 选择元素
            current.append(remaining[i])
            
            # 递归：处理剩余元素（排除已选择的）
            new_remaining = remaining[:i] + remaining[i+1:]
            backtrack(current, new_remaining)
            
            # 回溯：撤销选择
            current.pop()
    
    backtrack([], nums)
    return result


# 示例
if __name__ == "__main__":
    nums = [1, 2, 3]
    result = permutations(nums)
    print(f"数组 {nums} 的所有排列:")
    for i, perm in enumerate(result, 1):
        print(f"  {i}. {perm}")
    print(f"\n共 {len(result)} 种排列")
