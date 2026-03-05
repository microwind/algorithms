# 核心算法思想完全指南

作为程序员，每当你面对一个复杂问题时，最重要的不是立刻敲代码，而是**选对解题的思路**。本指南介绍了 7 大核心算法思想，这些思想贯穿于整个计算机科学领域，理解它们会让你的编程能力质的飞跃。

> **算法思想 ≠ 代码实现**。同一个思想可以用多种语言、多种方式实现。掌握思想，你就掌握了问题求解的本质。

### 1. 贪心（Greedy）

**定义**：在每个决策点选择当下局部最优的选择，期望通过一系列局部最优决策得到全局最优解。

**核心特性**：
- **贪心选择性质**：全局最优解可由局部最优选择导出
- **最优子结构**：原问题的最优解包含其子问题的最优解

**伪代码框架**：
```
Algorithm Greedy(Problem P):
    solution = ∅
    while P is not fully solved:
        choice = selectBestChoice(P)  // 局部最优选择
        solution = solution + choice
        P = reducedProblem(P, choice)
    return solution
```

**算法流程**：
```
初始问题 → 选择局部最优 → 更新问题状态 → 重复 → 最终解
```

**适用条件**：
- 问题具有贪心选择性质和最优子结构
- 不能回溯或修改已做的选择

**典型应用**：
- **分数背包**：按单位价值从高到低选择物品
- **最小生成树**：Kruskal（边贪心）、Prim（顶点贪心）
- **最短路径**：Dijkstra 算法
- **哈夫曼编码**：频率最低的两个节点合并
- **活动选择**：选择最早结束的活动

### 2. 分治（Divide and Conquer）

**定义**：将原问题分解为若干个规模更小、结构相同的子问题，递归地求解各子问题，然后合并子问题的解以构造原问题的解。

**三个关键步骤**：
1. **Divide**（分）：将问题分解为独立的子问题
2. **Conquer**（治）：递归求解子问题
3. **Combine**（合）：合并子问题的解

**伪代码框架**：
```
Algorithm DivideConquer(Problem P, boundary b):
    if P.size <= b:                    // 基础情况
        return directSolve(P)
    
    // 分解
    subProblems = divide(P)
    
    // 递归求解
    subSolutions = []
    for each subProblem in subProblems:
        subSolutions.add(DivideConquer(subProblem, b))
    
    // 合并
    return combine(subSolutions)
```

**执行树示意**：
```
        原问题
       /  |  \
      /   |   \
    子问题1 2 3
    /|    |    |\
   ...   ...  ...
```

**时间复杂度**：通常由分治递推式 `T(n) = a·T(n/b) + f(n)` 决定，使用主定理求解。

**适用条件**：
- 子问题相互独立，无重叠状态
- 存在明确的分割点
- 子问题可高效地合并

**典型应用**：
- **排序**：归并排序、快速排序
- **查找**：二分查找
- **矩阵运算**：Strassen 快速矩阵乘法
- **凸包**：分治构造凸包
- **逆序对计数**：基于归并排序

### 3. 动态规划（Dynamic Programming）

**定义**：将问题分解为存在重叠的子问题，通过定义状态和状态转移方程，利用存储空间换取计算时间，避免重复计算相同的子问题。

**核心要素**：
- **问题最优子结构**：原问题的最优解由子问题的最优解组成
- **状态定义**：明确每个阶段的状态变量
- **状态转移方程**：描述不同状态之间的递推关系
- **边界条件**：初始状态的解

**伪代码框架 - 自底向上**：
```
Algorithm DP_Tabulation(Problem P, int n):
    // 创建 DP 表
    dp[0...n] = new Array
    
    // 初始化边界条件
    dp[0] = baseCase()
    
    // 逐步填表
    for i = 1 to n:
        for j = 0 to i-1:  // 可能的状态转移
            dp[i] = max/min(dp[i], transitionFunc(dp[j], ...))
    
    return dp[n]
```

**伪代码框架 - 自顶向下**：
```
HashMap<State, Value> memo = new HashMap()

Algorithm DP_Memoization(State s):
    if s in memo:
        return memo[s]
    
    if isBase(s):
        return baseValue(s)
    
    // 递归求解并存储
    result = transitionFunc(subStates)
    memo[s] = result
    return result
```

**状态转移示意**：
```
     DP[1]        DP[2]        DP[3]  ...  DP[n]
      ↑            ↑            ↑            ↑
      └────────────┴────────────┴────────────┘
           状态转移方程链
```

**两种实现对比**：
| 方式 | 优点 | 缺点 |
|------|------|------|
| 自顶向下（记忆化） | 只计算需要的状态，直观 | 递归开销，栈溢出风险 |
| 自底向上（制表） | 迭代实现，效率稳定 | 需预先计算所有状态 |

**适用条件**：
- 存在重叠子问题（多个子问题计算相同）
- 具有最优子结构（无后效性）

**典型应用**：
- **背包问题**：0-1 背包、完全背包、多重背包
- **序列问题**：最长递增子序列、最长公共子序列、编辑距离
- **路径问题**：矩阵路径和、地牢游戏、最小路径和
- **计数问题**：不同路径数、爬楼梯、硬币兑换
- **图论**：Floyd-Warshall 全对最短路径

### 4. 回溯（Backtracking）

**定义**：采用试错的思想，在深度优先搜索求解过程中，当发现该分支路径行不通时（不满足约束条件），就回溯撤销该分支的选择，尝试其他分支。

**解空间树与策略**：
```
              根节点
            /   |   \
          分支1 分支2 分支3
         /  |   |   |
       ...剪枝 ...剪枝...
```

**伪代码框架**：
```
Algorithm Backtracking(candidates, track, constraints):
    // 完成一个合法方案
    if isSolution(track, constraints):
        solutions.add(copy(track))
        return
    
    // 剪枝：路径已不满足约束
    if !isValid(track, constraints):
        return
    
    // 选择、探索、撤销（Choose-Explore-Unchoose）
    for choice in candidates:
        track.add(choice)                    // 选择
        Backtracking(rest, track, constraints)  // 探索
        track.remove(choice)                 // 撤销
```

**三阶段循环模式**：
```
入栈/选择 → 检查合法性 → 递归探索 → 出栈/撤销
  ↑                                           ↓
  └───────────────────尝试下一选择──────────┘
```

**关键技巧**：
- **剪枝**：提前识别不可能的分支，减少搜索空间
- **约束传播**：维护当前约束集合，加快合法性检查

**适用条件**：
- 需要枚举解空间中的所有可能方案
- 方案具有树形结构或递归结构
- 存在约束条件可以剪枝

**典型应用**：
- **排列组合**：全排列、组合、子集
- **约束满足**：八皇后问题、数独求解
- **路径搜索**：岛屿数量、迷宫寻路
- **字符串**：电话号码字母组合、单词搜索
- **图着色**：地图着色、图着色问题

### 5. 分支定界（Branch and Bound）

**定义**：在回溯算法基础上，为每个部分解（搜索树中的节点）计算一个界（上界或下界），当该界表明该分支不可能产生比当前最优解更优的完全解时，就剪去该分支。

**与回溯的本质区别**：
| 维度 | 回溯 | 分支定界 |
|------|------|---------|
| **目标** | 找出所有可行解 | 找出最优解 |
| **遍历方式** | DFS，深度优先 | BFS/优先队列，按界优先 |
| **剪枝依据** | 约束条件 | 代价界 + 当前最优解 |
| **应用** | 组合、排列、搜索 | 最优化问题 |

**伪代码框架**：
```
Algorithm BranchAndBound(initialState, costFunc):
    bestValue = ∞  // 当前最优解的值
    bestSolution = null
    queue = PriorityQueue()  // 按下界排序
    queue.push(initialState, 0)
    
    while queue is not empty:
        node = queue.pop()  // 取界最小的节点
        
        // 剪枝：界超过当前最优
        if lowerBound(node) >= bestValue:
            continue
        
        // 找到完全解
        if isComplete(node):
            if cost(node) < bestValue:
                bestValue = cost(node)
                bestSolution = node
        else:
            // 生成子节点并入队
            for child in branch(node):
                if lowerBound(child) < bestValue:
                    queue.push(child, lowerBound(child))
    
    return bestSolution
```

**界的计算示意**：
```
       节点
       /│\
      / │ \
    节点2 节点3 ...
    ↓ ↓   ↓
 界  界   界   ← 每个分支的下界
    ↓    ↓
  比较当前最优值，决定是否剪枝
```

**分支策略**：
- **深度优先分支**（DFS）：通常与剪枝结合，内存效率高
- **广度优先分支**（BFS）：扩展上界界，更快到达最优解
- **最优优先分支**：每次选择界最小的节点，收敛快

**适用条件**：
- 问题是最优化问题（求最大值或最小值）
- 能够快速计算界（下界或上界）
- 界的计算不能过于复杂

**典型应用**：
- **旅行商问题（TSP）**：利用矩阵规化的下界
- **0-1 背包最优化版**：分数背包放松的上界
- **任务分配**：利用最小费用匹配的下界
- **装箱问题**：利用物品总体积的下界
- **作业调度**：利用关键路径的下界

---

## 二、搜索策略

### 6. 搜索（Search）

**定义**：在状态空间中系统性地探索节点，从初始状态逐步转移到目标状态，或在所有可达状态中寻找特定目标。

#### 广度优先搜索（BFS）

**特点**：逐层扩展，先扩展距起点近的节点。

**实现原理**：
```
Algorithm BFS(Graph G, start, target):
    queue = Queue()
    visited = Set()
    queue.enqueue(start)
    visited.add(start)
    
    while queue is not empty:
        node = queue.dequeue()
        if node == target:
            return found(node)
        
        for neighbor in G.getNeighbors(node):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.enqueue(neighbor)
    
    return notFound()
```

**扩展顺序**：
```
        起点
       / | \
      1  2  3   ← 第 1 层
     /| |\ |    ← 第 2 层
```

**特性**：
- **完备性**：若目标存在必定找到
- **最优性**：在无权图中找到最短路径
- **空间复杂度**：O(b^d)，b 为分支因子，d 为深度

**应用**：无权最短路径、连通性检测、层级遍历

---

#### 深度优先搜索（DFS）

**特点**：沿一条路走到底，再回溯尝试其他路径，用栈或递归实现。

**实现原理 - 递归版**：
```
Algorithm DFS_Recursive(node, target, visited, Graph G):
    if node == target:
        return found(node)
    
    visited.add(node)
    
    for neighbor in G.getNeighbors(node):
        if neighbor not in visited:
            result = DFS_Recursive(neighbor, target, visited, G)
            if result found:
                return result
    
    return notFound()
```

**实现原理 - 迭代版（栈）**：
```
Algorithm DFS_Iterative(start, target, Graph G):
    stack = Stack()
    visited = Set()
    stack.push(start)
    visited.add(start)
    
    while stack is not empty:
        node = stack.pop()
        if node == target:
            return found(node)
        
        for neighbor in G.getNeighbors(node):
            if neighbor not in visited:
                visited.add(neighbor)
                stack.push(neighbor)
    
    return notFound()
```

**遍历顺序**：
```
       起点
        │
        ├─→ 1-1-1-1  ← 一条路走到底
        │
        └─→ 2-2-2    ← 回溯再走
```

**应用**：拓扑排序、强连通分量、回溯搜索、括号生成

---

#### 启发式搜索（A*）

**特点**：利用启发函数 f(n) = g(n) + h(n) 估计每个节点的潜力，优先扩展最有希望的节点。

**概念解析**：
- **g(n)**：从起点到当前节点 n 的实际代价
- **h(n)**：启发估计，从 n 到目标的估计代价（需满足可采纳性）
- **f(n)**：整体估计，决定节点优先级（越小越优先）

**伪代码框架**：
```
Algorithm AStar(start, target, Graph G):
    openSet = PriorityQueue()  // 按 f(n) 排序
    closedSet = Set()
    gScore = {start: 0}
    fScore = {start: heuristic(start, target)}
    
    openSet.add(start, fScore[start])
    
    while openSet is not empty:
        current = openSet.pop()  // f 值最小节点
        
        if current == target:
            return reconstruct_path(current)
        
        closedSet.add(current)
        
        for neighbor in G.getNeighbors(current):
            if neighbor in closedSet:
                continue
            
            tentative_g = gScore[current] + cost(current, neighbor)
            
            if neighbor not in openSet or tentative_g < gScore[neighbor]:
                gScore[neighbor] = tentative_g
                fScore[neighbor] = gScore[neighbor] + heuristic(neighbor, target)
                openSet.add(neighbor, fScore[neighbor])
    
    return pathNotFound()
```

**启发函数设计**：
- **曼哈顿距离**（h(n) = |x₁-x₂| + |y₁-y₂|）：网格问题
- **欧几里得距离**（h(n) = √((x₁-x₂)² + (y₁-y₂)²)）：连续空间
- **直线距离**：任何空间

**可采纳性条件**：h(n) ≤ 实际最小代价，保证找到最优解

**应用**：游戏 AI 寻路、机器人导航、地图导航

---

#### 迭代加深（IDDFS）

**特点**：结合 DFS 和 BFS 的优点，逐次增加深度限制，直到找到目标。

**实现原理**：
```
Algorithm IDDFS(start, target, Graph G):
    depth = 0
    
    while true:
        result = DFS_DepthLimited(start, target, depth, G)
        if result found:
            return result
        depth = depth + 1
```

**深度限制 DFS**：
```
Algorithm DFS_DepthLimited(node, target, maxDepth, visited, G):
    if node == target:
        return found(node)
    
    if maxDepth == 0:
        return notFound()
    
    visited.add(node)
    
    for neighbor in G.getNeighbors(node):
        if neighbor not in visited:
            result = DFS_DepthLimited(neighbor, target, maxDepth-1, visited, G)
            if result found:
                return result
    
    return notFound()
```

**搜索轨迹**：
```
第 1 次：深度限制 = 1  →  搜索 A 层节点
第 2 次：深度限制 = 2  →  搜索 A-B 层节点
第 3 次：深度限制 = 3  →  搜索 A-B-C 层节点  ← 找到目标
```

**特性**：
- **空间复杂度**：O(d)，d 为解的深度（DFS 优势）
- **时间复杂度**：O(b^d)，与 BFS 相同但常数因子更小
- **应用**：深度未知的大规模搜索空间

---

**搜索策略对比表**：

| 策略 | 完备性 | 最优性 | 时间 | 空间 | 适用场景 |
|------|--------|--------|------|------|---------|
| **BFS** | ✓ | ✓（无权） | O(b^d) | O(b^d) | 无权、层级 |
| **DFS** | ✓ | ✗ | O(b^d) | O(d) | 内存受限、回溯 |
| **A\*** | ✓ | ✓（可采纳h） | 依赖h | 依赖h | 启发式、寻路 |
| **IDDFS** | ✓ | ✓（无权） | O(b^d) | O(d) | unknown depth |

---

## 三、随机化算法

### 7. 随机化（Randomization）

**定义**：在算法的执行过程中引入随机性（通常是随机选择），以期望意义上改进性能、打破对手的最坏情况构造、简化问题分析。

**理论基础**：
- **随机变量期望**：E[X] = Σ probability(x) × value(x)
- **高概率事件**：事件发生概率至少为 1 - δ（δ 很小）
- **几何分布**：第一次成功的期望次数

**两大类型**：

#### 蒙特卡洛算法（Monte Carlo）

**特点**：
- 运行时间**固定或确定**
- 结果可能**有误差概率**
- 错误是**可控的**（通过多次运行降低误差率）

**伪代码框架**：
```
Algorithm MonteCarlo(Problem P, iterations):
    result_counts = {}
    
    for i = 1 to iterations:
        // 随机模拟一次
        sample = randomRun(P)
        result_counts[sample] += 1
    
    // 按频率估计答案
    return mostFrequent(result_counts)
    
    // 误差率 ≈ 1 / iterations
```

**误差率分析**：
```
运行次数越多，结果越接近真实值
│
│     ╱╲
│    ╱  ╲    ╱╲
└───╱────╲──╱──╲──── 真实值
    迭代次数增加 →
```

**典型应用**：
- **蒙特卡洛估算圆周率**：随机点落在圆内的比例
- **概率验证**：快速检验某个数是否大素数（Miller-Rabin）
- **数值积分**：随机采样点估算函数积分
- **随机采样**：大规模数据中的无偏采样

---

#### 拉斯维加斯算法（Las Vegas）

**特点**：
- 结果**一定正确**
- 运行时间**具有随机性**
- 性能是**概率意义上的**

**伪代码框架**：
```
Algorithm LasVegas(Problem P):
    while true:
        // 随机尝试
        solution = randomAttempt(P)
        
        // 严格验证
        if verify(solution, P):
            return solution  // 一定正确
        
        // 否则重试
        // 期望尝试次数的数学分析...
```

**时间复杂度分析**：
```
期望时间 E[T] = Σ P(success at round i) × T(i)
              = p + 2p(1-p) + 3p(1-p)² + ...
              = 1/p  （其中 p = 成功概率）
```

**典型应用**：
- **随机快速排序**：随机选择枢轴，平均时间 O(n log n)
- **跳表**：随机化的平衡链表，支持 O(log n) 搜索
- **哈希表**：随机哈希函数减少碰撞
- **素数测试**：随机见证人验证（Miller-Rabin）
- **随机最小割**：Karger 的最小割算法

---

**蒙特卡洛 vs 拉斯维加斯**：

| 维度 | 蒙特卡洛 | 拉斯维加斯 |
|------|----------|----------|
| **结果正确性** | 可能有误差 | 一定正确 |
| **时间复杂度** | 确定性或固定 | 随机的，需期望分析 |
| **失败处理** | 多次运行取多数 | 失败重试 |
| **应用倾向** | 检验、估算、模拟 | 快速查找、排序 |
| **代表例子** | Miller-Rabin 素性测试 | 快速排序、跳表 |

**可靠性与性能权衡**：
```
    蒙特卡洛（快但可能错误）
        ↑
        │  运行次数/迭代次数增加
        │  →→→ 准确性提升，时间增加
        │
        └──→ 拉斯维加斯（慢但一定对）


         期望时间 = f(问题难度) + g(随机性)
```

**算法选择指南**：
- 若**答案必须正确**且有高效验证方式：选 **Las Vegas**
- 若**单次答案可接受误差**但需快速得到估计：选 **Monte Carlo**
- 若需**完全可靠**但允许长时间运行：**Las Vegas 多次运行**
- 若需**快速近似**不在乎偶现错误：**Monte Carlo + 验证**