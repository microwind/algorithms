## 分支限界 Branch and Bound

### 核心思想
在回溯基础上，为每个分支计算代价上/下界，提前剪除不可能优于当前最优解的分支。

### 与回溯的核心区别

| 维度 | 回溯 | 分支限界 |
|------|------|--------|
| **目标** | 枚举所有可行解 | 求最优解 |
| **剪枝依据** | 约束条件合法性 | 代价界限大小 |
| **应用** | 组合、排列问题 | 优化问题 |
| **最优性** | 不保证 | 保证 |

### 基本框架

```
def branch_and_bound(node, bound):
    if 是叶子节点:
        更新最优解
        return
    
    for 每个子节点 in children:
        子界限 = estimate_bound(子节点)
        if 子界限 < 当前最优值:  # 有希望
            branch_and_bound(子节点, 子界限)
        # else: 剪枝
```

### 关键要素
1. **上界估计** - 已知的最好可行解
2. **下界估计** - 当前分支最好情况的估计
3. **剪枝条件** - 若下界 ≥ 上界，则剪枝
4. **搜索策略** - 宽度优先、深度优先、最优优先等

### 应用场景
- **旅行商问题(TSP)** - 找最短旅行路线
- **背包优化** - 0-1背包最优化版本
- **任务调度** - 最小化完成时间或成本
- **工作分配问题** - 将工作分配给员工最小化成本
- **整数规划** - 线性规划的整数解
- **最小顶点覆盖** - 图论中的NP完全问题

### 界限估计方法

**下界估计**（Lower Bound）：
- 分析当前部分解的最好可能完整解
- 通常基于贪心、松弛、启发式等方法
- 务必保证下界 ≤ 最优解

**上界估计**（Upper Bound）：
- 当前已知的最好可行解
- 初始时用贪心得到的可行解
- 搜索过程中不断更新

### 搜索策略

| 策略 | 特点 | 适用 |
|------|------|------|
| 深度优先(DFS) | 快速找到可行解，内存少 | 一般问题 |
| 宽度优先(BFS) | 逐层搜索，易于分析 | 小规模问题 |
| 最优优先 | 优先搜索界限最好的节点 | 大规模优化 |
| LC搜索 | DFS+宽度结合 | 平衡问题 |

### 常见陷阱
- ✗ 界限估计不紧导致剪枝效果差
- ✗ 下界估计不正确导致遗漏最优解
- ✗ 初始上界太差导致很少能剪枝
- ✗ 搜索策略选择不当

### 优化技巧
1. **紧界限估计** - 下界越紧越好，减少搜索空间
2. **快速可行解** - 优先找到好的上界
3. **动态界限** - 搜索过程中更新界限
4. **启发式顺序** - 先探索更可能的分支

### 与其他范式对比

| 特性 | 分支限界 | 回溯 | 动态规划 |
|------|--------|------|--------|
| 最优解 | 有 | 否 | 有 |
| 剪枝有效性 | 高 | 依赖约束 | N/A |
| 实现复杂度 | 中 | 低 | 高 |
| 时间复杂度 | 指数（可优化） | 指数 | 多项式 |

### 实例分析：0-1背包

**贪心下界估计**：
```
将物品按单位价值排序
从高到低装入直到背包满
所得价值 ≤ 最优值
```

**松弛下界**：
```
允许部分装入物品（分数背包）
计算最好情况的背包价值
```

### 学习建议
1. 理解分支限界相比回溯的改进
2. 学会为具体问题设计界限估计
3. 分析剪枝效果和搜索空间
4. 通过实验调优搜索策略
5. 比较与贪心、DP的性能差异

---

## 典型分支限界代码模板（Python）

以任务分配/旅行商/背包等问题为例，分支限界法的核心结构如下：

```python
# 以任务分配问题为例

def branch_and_bound(task_idx, current_cost):
    # 剪枝：当前成本+下界 >= 当前最优解，直接返回
    if current_cost + lower_bound(task_idx) >= min_cost[0]:
        return
    # 基础情况：所有任务已分配
    if task_idx == n:
        min_cost[0] = min(min_cost[0], current_cost)
        return
    # 分支：尝试将当前任务分配给每个可用工人
    for worker in range(n):
        if not assigned[worker]:
            assigned[worker] = True
            branch_and_bound(task_idx + 1, current_cost + cost[task_idx][worker])
            assigned[worker] = False

# 下界估计函数示例

def lower_bound(task_idx):
    bound = 0
    for i in range(task_idx, n):
        min_c = min(cost[i][j] for j in range(n) if not assigned[j])
        bound += min_c
    return bound
```

**说明：**
- 递归每次分配一个任务，尝试所有可用工人
- 剪枝条件依赖于 lower_bound 的估计
- min_cost[0] 用于全局记录最优解
- lower_bound 采用贪心法估计剩余最小成本

---

## 旅行商问题（TSP）分支限界伪代码

```python
def tsp_branch_and_bound(node, level, cost):
    # 剪枝：下界 >= 当前最优解
    if lower_bound(node, level, cost) >= min_cost[0]:
        return
    # 基础情况：所有城市访问完毕
    if level == n:
        total_cost = cost + dist[node][0]
        if total_cost < min_cost[0]:
            min_cost[0] = total_cost
        return
    # 分支：访问下一个未访问城市
    for next_city in range(n):
        if not visited[next_city]:
            visited[next_city] = True
            tsp_branch_and_bound(next_city, level + 1, cost + dist[node][next_city])
            visited[next_city] = False
```

**说明：**
- 剪枝依赖于 lower_bound 的估计
- 递归深度等于城市数
- 适用于 TSP、作业调度、背包等优化问题

---
