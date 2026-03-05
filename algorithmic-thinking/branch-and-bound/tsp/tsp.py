"""
旅行商题 - 分支定界算法
找到伺寻回路的最小成本
"""

import sys
from typing import List, Tuple

class TSPSolver:
    def __init__(self, distance_matrix: List[List[int]]):
        self.dist = distance_matrix
        self.n = len(distance_matrix)
        self.min_cost = float('inf')
        self.best_path = []
        self.current_path = [0]
        self.visited = [False] * self.n
        self.visited[0] = True
    
    def lower_bound(self, node: int, level: int, current_cost: int) -> int:
        """
        使用最小启程树近似计算下界
        时间: O(n^2), 空间: O(n)
        """
        bound = current_cost
        
        # 从当前节点到未访问城市添加最小成本边
        min_edge = float('inf')
        for i in range(self.n):
            if not self.visited[i]:
                min_edge = min(min_edge, self.dist[node][i])
        
        if min_edge != float('inf'):
            bound += min_edge
        
        # 估计剩余路径的最小成本
        for i in range(self.n):
            if not self.visited[i]:
                min1, min2 = float('inf'), float('inf')
                for j in range(self.n):
                    if not self.visited[j] and i != j:
                        if self.dist[i][j] < min1:
                            min2 = min1
                            min1 = self.dist[i][j]
                        elif self.dist[i][j] < min2:
                            min2 = self.dist[i][j]
                
                if min2 != float('inf'):
                    bound += min1
        
        return bound
    
    def branch_and_bound(self, node: int, level: int, cost: int) -> None:
        """
        Branch and bound recursion with pruning
        Time: Exponential with pruning, Space: O(n) recursion depth
        """
        # 剪枝：下界 >= 当前最优，跳过此分支
        if self.lower_bound(node, level, cost) >= self.min_cost:
            return
        
        # 基础情况：找到完整路径
        if level == self.n - 1:
            total_cost = cost + self.dist[node][0]
            if total_cost < self.min_cost:
                self.min_cost = total_cost
                self.best_path = self.current_path[:]
            return
        
        # 分支：探索未访问的城市
        for i in range(self.n):
            if not self.visited[i]:
                self.visited[i] = True
                self.current_path.append(i)
                
                self.branch_and_bound(i, level + 1, cost + self.dist[node][i])
                
                self.current_path.pop()
                self.visited[i] = False
    
    def solve(self) -> Tuple[int, List[int]]:
        """
        求解TSP并返回最小成本和巡回路径
        """
        self.branch_and_bound(0, 1, 0)
        return self.min_cost, self.best_path + [0]


# Example usage and test
if __name__ == "__main__":
    # 测试用例1：4个城市
    graph = [
        [0, 10, 15, 20],
        [10, 0, 35, 25],
        [15, 35, 0, 30],
        [20, 25, 30, 0]
    ]
    
    print("=" * 60)
    print("旅行商题 - 分支定界算法")
    print("=" * 60)
    print("\nDistance Matrix:")
    for row in graph:
        print(row)
    
    solver = TSPSolver(graph)
    min_cost, path = solver.solve()
    
    print(f"\n最小巡回成本: {min_cost}")
    print(f"巡回路线: {' -> '.join(map(str, path))}")
    
    # 测试用例2：5个城市
    print("\n" + "=" * 60)
    graph2 = [
        [0, 29, 20, 32, 23],
        [29, 0, 21, 37, 18],
        [20, 21, 0, 28, 23],
        [32, 37, 28, 0, 34],
        [23, 18, 23, 34, 0]
    ]
    
    print("5个城市的测试:")
    print("\n距离矩阵:")
    for row in graph2:
        print(row)
    
    solver2 = TSPSolver(graph2)
    min_cost2, path2 = solver2.solve()
    
    print(f"\n最小巡回成本: {min_cost2}")
    print(f"巡回路线: {' -> '.join(map(str, path2))}")
