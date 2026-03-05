"""
任务分配问题 - 分支定界算法
将任务分配给员工以最小化总成本
"""

class TaskAssignment:
    def __init__(self, cost_matrix):
        """
        初始化任务分配求解器
        cost_matrix[i][j] = 将任务i分配给员工j的成本
        时间: O(n^2), 空间: O(n^2)
        """
        self.cost = cost_matrix
        self.n = len(cost_matrix)
        self.min_cost = float('inf')
        self.best_assignment = [-1] * self.n
        self.current_assignment = [-1] * self.n
        self.assigned_workers = [False] * self.n
    
    def lower_bound(self, task_idx):
        """
        使用匈牙利算法近似计算下界
        时间: O(n), 空间: O(n)
        """
        bound = 0
        
        # 对于每个未划配任务，添加最小成本
        for i in range(task_idx, self.n):
            min_cost = float('inf')
            for j in range(self.n):
                if not self.assigned_workers[j]:
                    min_cost = min(min_cost, self.cost[i][j])
            
            if min_cost != float('inf'):
                bound += min_cost
        
        return bound
    
    def branch_and_bound(self, task_idx=0, current_cost=0):
        """
        分支定界及剪枝
        时间: 指数级及剪枝, 空间: O(n)
        """
        # 剪枝：下界 + 当前成本 >= 最优解，跳过
        if current_cost + self.lower_bound(task_idx) >= self.min_cost:
            return
        
        # 基础情况：所有任务已分配
        if task_idx == self.n:
            if current_cost < self.min_cost:
                self.min_cost = current_cost
                self.best_assignment = self.current_assignment[:]
            return
        
        # 分支：尝试将当前任务分配给每个可用员工
        for worker in range(self.n):
            if not self.assigned_workers[worker]:
                self.current_assignment[task_idx] = worker
                self.assigned_workers[worker] = True
                
                self.branch_and_bound(task_idx + 1, 
                                     current_cost + self.cost[task_idx][worker])
                
                self.assigned_workers[worker] = False
    
    def solve(self):
        """
        求解并返回最小成本和分配
        """
        self.branch_and_bound()
        return self.min_cost, self.best_assignment
    
    def get_assignment_details(self):
        """
        获取详细的分配信息
        """
        details = []
        for task, worker in enumerate(self.best_assignment):
            details.append({
                'task': task,
                'worker': worker,
                'cost': self.cost[task][worker]
            })
        return details


# 测试和例子
if __name__ == "__main__":
    print("=" * 60)
    print("Task Assignment Problem - Branch and Bound")
    print("=" * 60)
    
    # Test case
    cost_matrix = [
        [5, 7, 9],      # Task 0 costs
        [6, 8, 4],      # Task 1 costs
        [3, 5, 7]       # Task 2 costs
    ]
    
    print("\nCost Matrix:")
    print("Task \\ Worker  0   1   2")
    for i, row in enumerate(cost_matrix):
        print(f"   {i}         {row[0]:2d}  {row[1]:2d}  {row[2]:2d}")
    
    solver = TaskAssignment(cost_matrix)
    min_cost, assignment = solver.solve()
    
    print(f"\nMinimum Total Cost: {min_cost}")
    print("\nOptimal Assignment:")
    print("Task -> Worker")
    for task, worker in enumerate(assignment):
        print(f" {task}   ->   {worker}    (cost: {cost_matrix[task][worker]})")
    
    # Test case 2
    print("\n" + "=" * 60)
    cost_matrix2 = [
        [10, 2, 3, 4],
        [4, 13, 8, 9],
        [14, 4, 13, 10],
        [4, 7, 5, 12]
    ]
    
    print("\nTest Case 2 (4 tasks, 4 workers):")
    print("\nCost Matrix:")
    print("Task \\ Worker", end="")
    for j in range(4):
        print(f"  {j:2d}", end="")
    print()
    for i, row in enumerate(cost_matrix2):
        print(f"   {i}        ", end="")
        for cost in row:
            print(f" {cost:2d}", end=" ")
        print()
    
    solver2 = TaskAssignment(cost_matrix2)
    min_cost2, assignment2 = solver2.solve()
    
    print(f"\nMinimum Total Cost: {min_cost2}")
    print("\nOptimal Assignment:")
    for task, worker in enumerate(assignment2):
        print(f"Task {task} -> Worker {worker} (cost: {cost_matrix2[task][worker]})")
