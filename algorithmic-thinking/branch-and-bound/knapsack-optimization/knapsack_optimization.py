"""
0-1背包优化 - 分支定界算法
在容量限制下，选择物品使得总价值最大
"""

class KnapsackOptimization:
    def __init__(self, weights, values, capacity):
        """
        初始化背包求解器
        时间: O(n), 空间: O(n)
        """
        self.weights = weights
        self.values = values
        self.capacity = capacity
        self.n = len(weights)
        self.max_profit = 0
        self.best_items = [False] * self.n
        self.current_items = [False] * self.n
    
    def upper_bound(self, idx, weight, profit):
        """
        使用分数背包可源计算上界
        时间: O(n), 空间: O(1)
        """
        if weight >= self.capacity:
            return profit
        
        bound = profit
        remain_capacity = self.capacity - weight
        
        # 贪心：按价值/重量比提高顺序选择物品
        for i in range(idx, self.n):
            if self.weights[i] <= remain_capacity:
                # 包含整个物品
                bound += self.values[i]
                remain_capacity -= self.weights[i]
            else:
                # 包含物品的一部分
                bound += int(self.values[i] * remain_capacity / self.weights[i])
                break
        
        return bound
    
    def branch_and_bound(self, idx=0, weight=0, profit=0):
        """
        分支定界及剪枝
        时间: 指数级及剪枝, 空间: O(n) 递归深度
        """
        # 剪枝：上界 <= 当前最优解，跳过此分支
        if self.upper_bound(idx, weight, profit) <= self.max_profit:
            return
        
        # 基础情况：已考虑所有物品
        if idx == self.n:
            if profit > self.max_profit:
                self.max_profit = profit
                self.best_items = self.current_items[:]
            return
        
        # 分支1：包含当前物品
        if weight + self.weights[idx] <= self.capacity:
            self.current_items[idx] = True
            self.branch_and_bound(idx + 1, weight + self.weights[idx], 
                                 profit + self.values[idx])
            self.current_items[idx] = False
        
        # 分支2：排除当前物品
        self.branch_and_bound(idx + 1, weight, profit)
    
    def solve(self):
        """
        求解并返回最大价值和选中物品
        """
        self.branch_and_bound()
        return self.max_profit, self.get_selected_items()
    
    def get_selected_items(self):
        """
        获取选中物品的索引
        """
        return [i for i in range(self.n) if self.best_items[i]]


# 测试和例子
if __name__ == "__main__":
    print("=" * 60)
    print("0-1 Knapsack Optimization - Branch and Bound")
    print("=" * 60)
    
    # Test case 1
    weights = [2, 3, 4, 5]
    values = [3, 4, 5, 6]
    capacity = 8
    
    print("\nTest Case 1:")
    print(f"Items: {len(weights)}")
    print(f"Capacity: {capacity}")
    print(f"Weights: {weights}")
    print(f"Values: {values}")
    
    solver = KnapsackOptimization(weights, values, capacity)
    max_profit, selected = solver.solve()
    
    print(f"\nMaximum Profit: {max_profit}")
    print(f"Selected Items: {selected}")
    print(f"Total Weight: {sum(weights[i] for i in selected)}")
    
    # Test case 2
    print("\n" + "=" * 60)
    weights2 = [5, 4, 3, 4, 2]
    values2 = [10, 40, 30, 50, 35]
    capacity2 = 10
    
    print("Test Case 2:")
    print(f"Weights: {weights2}")
    print(f"Values: {values2}")
    print(f"Capacity: {capacity2}")
    
    solver2 = KnapsackOptimization(weights2, values2, capacity2)
    max_profit2, selected2 = solver2.solve()
    
    print(f"\nMaximum Profit: {max_profit2}")
    print(f"Selected Items: {selected2}")
    print(f"Total Weight: {sum(weights2[i] for i in selected2)}")
