"""
记忆化搜索 - 背包问题 (0/1 Knapsack)
使用递归+记忆化解决经典的背包问题
"""

def knapsack_memo(weights, values, capacity):
    """
    0/1背包问题 - 记忆化搜索解法
    
    问题：给定n个物品，每个物品有重量weight和价值value，
          在背包容量为capacity的情况下，求能装入的最大价值
    
    参数:
        weights: 物品重量列表
        values: 物品价值列表
        capacity: 背包容量
    """
    n = len(weights)
    # 记忆化字典: (index, remaining_capacity) -> max_value
    memo = {}
    
    def dfs(index, remaining_capacity):
        # 基础情况：没有物品了或容量用尽
        if index >= n or remaining_capacity <= 0:
            return 0
        
        # 检查是否已计算过
        if (index, remaining_capacity) in memo:
            return memo[(index, remaining_capacity)]
        
        # 选择1：不选当前物品
        skip = dfs(index + 1, remaining_capacity)
        
        # 选择2：选当前物品（前提是装得下）
        take = 0
        if weights[index] <= remaining_capacity:
            take = values[index] + dfs(index + 1, remaining_capacity - weights[index])
        
        # 记录最优解
        result = max(skip, take)
        memo[(index, remaining_capacity)] = result
        
        return result
    
    return dfs(0, capacity)


# 示例
if __name__ == "__main__":
    # 示例1
    weights = [2, 3, 4, 5]
    values = [3, 4, 5, 6]
    capacity = 8
    
    print("=" * 50)
    print("0/1背包问题 - 记忆化搜索")
    print("=" * 50)
    
    print(f"\n物品信息:")
    print(f"{'物品':<6}{'重量':<8}{'价值':<8}")
    print("-" * 22)
    for i in range(len(weights)):
        print(f"{i:<6}{weights[i]:<8}{values[i]:<8}")
    
    print(f"\n背包容量: {capacity}")
    
    max_value = knapsack_memo(weights, values, capacity)
    print(f"最大价值: {max_value}")
    
    print(f"\n复杂度分析:")
    print(f"  • 无记忆化: O(2^n) - 每个物品选/不选两种可能")
    print(f"  • 记忆化后: O(n × capacity) - 每个状态只计算一次")
