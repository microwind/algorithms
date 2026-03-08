# Core Algorithm Thinking Every Programmer Must Master

> **Algorithm Thinking ≠ Code Implementation**. The same idea can be implemented in multiple languages and ways. Mastering algorithmic thinking means grasping the essence of problem-solving, and solving problems more efficiently through different implementation approaches.

## Overview

Algorithms are methods for solving problems. Problem-solving methods are inseparable from guiding principles. **Guiding principles are the key to solving problems**.

As a programmer, when we face a complex problem, the most important thing is not to start coding immediately, but to **choose the right problem-solving approach**.

This guide introduces **5 core algorithm thinking approaches** + **2 common problem-solving strategies**. These ideas and strategies run through the entire computer programming field. Mastering them will give your programming skills a qualitative leap.

## What Algorithm Thinking Approaches Are There?

### 1. Greedy (Greedy) [Source Code](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/greedy-algorithm)

**Definition**: At each decision point, you always choose the locally optimal choice, hoping to obtain a globally optimal solution through a series of locally optimal decisions. In simple terms, it's step-by-step optimal to eventually achieve global optimality. Greedy algorithms are widely used in optimization problems such as shortest paths, knapsack problems, and matrix chain multiplication.

**Core Characteristics**:
- **Greedy Choice Property**: Global optimal solution can be derived from locally optimal choices
- **Optimal Substructure**: The optimal solution of the original problem contains the optimal solutions of its subproblems

**Pseudocode**:
```c
Algorithm Greedy(Problem P):
    solution = ∅
    while P is not fully solved:
        // Locally optimal choice that will lead to global optimal solution
        choice = selectBestChoice(P)
        solution = solution + choice
        // Update problem state, prepare for next selection
        P = reducedProblem(P, choice)
    return solution
```

**Algorithm Flow**:
```
Initial Problem → Select Local Optimal → Update Problem State → Repeat → Final Solution
```

**Applicable Conditions**:
- The problem has greedy choice property and optimal substructure
- Cannot backtrack or modify choices already made

**Typical Applications**:
- **Fractional Knapsack**: Select items from highest to lowest unit value
- **Minimum Spanning Tree**: Kruskal (edge greedy), Prim (vertex greedy)
- **Shortest Path**: Dijkstra's algorithm
- **Huffman Coding**: Merge the two nodes with lowest frequency
- **Activity Selection**: Select activities that end earliest

### 2. Divide and Conquer (Divide and Conquer) [Source Code](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/divide-and-conquer)

**Definition**: Divide the original problem into several smaller subproblems with the same structure, recursively solve each subproblem, then combine the solutions of subproblems to obtain the solution to the original problem. In simple terms, it's dividing large problems into smaller ones and conquering them separately. Divide and conquer algorithms are widely used in sorting, searching, and matrix operations.

**Three Key Steps**:
1. **Divide**: Decompose the problem into independent subproblems
2. **Conquer**: Recursively solve subproblems
3. **Combine**: Combine the solutions of subproblems

**Diagram**:
```
Initial Problem → Decompose → Recursively Solve Subproblems → Combine Subproblem Solutions → Final Solution
```

**Pseudocode**:
```javascript
Algorithm DivideConquer(Problem P, boundary b):
    // Base case
    if P.size <= b:
        return directSolve(P)

    // Decompose, subproblems are independent
    subProblems = divide(P)

    // Recursive solve, combine subproblem solutions
    subSolutions = []
    for each subProblem in subProblems:
        subSolutions.add(DivideConquer(subProblem, b))

    // Combine subproblem solutions
    return combine(subSolutions)
```

**Execution Tree**:
```
        Original Problem
       /  |  \
      /   |   \
   Subproblem1 2 3
    /|    |    |\
   ...   ...  ...
```

**Time Complexity**: Usually determined by the divide-conquer recurrence `T(n) = a·T(n/b) + f(n)`, solved using the Master Theorem.

**Applicable Conditions**:
- Subproblems are independent with no overlapping states
- There are clear division points
- Subproblems can be efficiently combined

**Typical Applications**:
- **Sorting**: Merge Sort, Quick Sort
- **Search**: Binary Search
- **Matrix Operations**: Strassen Fast Matrix Multiplication
- **Convex Hull**: Divide and conquer convex hull construction
- **Inversion Count**: Based on merge sort

### 3. Dynamic Programming (Dynamic Programming) [Source Code](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/dynamic-programming)

**Definition**: Decompose the problem into overlapping subproblems, define states and state transition equations, use storage space to trade for computation time, and avoid recalculating the same subproblems. Dynamic programming is widely used in optimization problems such as shortest paths, knapsack problems, and matrix chain multiplication.

**Core Elements**:
- **Optimal Substructure of Problem**: The optimal solution of the original problem is composed of optimal solutions of subproblems
- **State Definition**: Clearly define state variables at each stage
- **State Transition Equation**: Describe the recursive relationship between different states
- **Boundary Condition**: Solution to the initial state


**Diagram**:
```
     DP[1]        DP[2]        DP[3]  ...  DP[n]
      ↑            ↑            ↑            ↑
      └────────────┴────────────┴────────────┘
              State Transition Equation Chain
```

**Pseudocode - Bottom-Up**:
```java
Algorithm DP_Tabulation(Problem P, int n):
    // Create DP table
    dp[0...n] = new Array

    // Initialize boundary condition
    dp[0] = baseCase()

    // Fill table step by step, populate dp[i]
    for i = 1 to n:
        for j = 0 to i-1:  // Possible state transitions
            dp[i] = max/min(dp[i], transitionFunc(dp[j], ...))

    return dp[n]
```

**Pseudocode - Top-Down**:
```java
HashMap<State, Value> memo = new HashMap()

Algorithm DP_Memoization(State s):
    if s in memo:
        return memo[s]
    // Recursively solve subproblem
    if isBase(s):
        return baseValue(s)

    // Recursively solve and store
    result = transitionFunc(subStates)
    memo[s] = result
    return result
```

**Comparison of Two Implementations**:
| Approach | Advantages | Disadvantages |
|------|------|------|
| Top-Down (Memoization) | Only compute needed states, intuitive | Recursion overhead, risk of stack overflow |
| Bottom-Up (Tabulation) | Iterative implementation, stable efficiency | Need to precompute all states |

**Applicable Conditions**:
- Existence of overlapping subproblems (multiple subproblems compute the same)
- Optimal substructure (no future dependency)

**Typical Applications**:
- **Knapsack Problems**: 0-1 Knapsack, Unbounded Knapsack, Multiple Knapsack
- **Sequence Problems**: Longest Increasing Subsequence, Longest Common Subsequence, Edit Distance
- **Path Problems**: Matrix Path Sum, Dungeon Game, Minimum Path Sum
- **Counting Problems**: Different Paths, Climbing Stairs, Coin Change
- **Graph Theory**: Floyd-Warshall All-Pairs Shortest Path

### 4. Backtracking (Backtracking) [Source Code](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/backtracking)

**Definition**: Backtracking adopts trial-and-error thinking. During depth-first search solving, when you find a branch path doesn't work (fails constraints), you backtrack to undo that branch's choice and try other branches. In simple terms, it's continuous trial and error until you find a solution or determine there's no solution. Backtracking is widely used in permutation combinations, constraint satisfaction, and path searching problems.

**Diagram**:
```
              Root Node
            /   |   \
          Branch1 Branch2 Branch3
         /  |   |   |
       ...Prune ...Prune...
```

**Pseudocode**:
```c
Algorithm Backtracking(candidates, track, constraints):
    // Reach a valid solution
    if isSolution(track, constraints):
        solutions.add(copy(track))
        return

    // Prune: path no longer satisfies constraints
    if !isValid(track, constraints):
        return

    // Choose, Explore, Unchoose
    for choice in candidates:
        track.add(choice)                       // Choose
        Backtracking(rest, track, constraints)  // Explore
        track.remove(choice)                    // Unchoose
```

**Key Techniques**:
- **Pruning**: Identify impossible branches early, reduce search space
- **Constraint Propagation**: Maintain current constraint set, speed up legality checks

**Applicable Conditions**:
- Need to enumerate all possible solutions in solution space
- Solutions have tree or recursive structure
- Constraint conditions exist for pruning

**Typical Applications**:
- **Permutation Combination**: Permutations, Combinations, Subsets
- **Constraint Satisfaction**: N-Queens Problem, Sudoku Solving
- **Path Search**: Island Count, Maze Pathfinding
- **Strings**: Phone Number Letter Combinations, Word Search
- **Graph Coloring**: Map Coloring, Graph Coloring Problems

### 5. Branch and Bound (Branch and Bound) [Source Code](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/branch-and-bound)

**Definition**: Branch and Bound (also called Branch Limit Method) calculates a bound (upper or lower) for each partial solution (node in the search tree) based on backtracking. When this bound indicates that a branch cannot produce a complete solution better than the current optimal solution, the branch is pruned. In simple terms, it adds bound calculation and pruning for each node on top of backtracking. Branch and Bound is widely used in combinatorial optimization problems such as Traveling Salesman Problem, Knapsack Problem, and Task Assignment.

**Diagram**:
```
       Node
       / │ \
      /  │  \
    Node2   Node3 ...
    ↓    ↓    ↓
    Bound Bound Bound  ← Lower bound for each branch
    ↓    ↓
  Compare current optimal, decide whether to prune
```

**Key Difference from Backtracking**:
| Dimension | Backtracking | Branch and Bound |
|------|------|---------|
| **Goal** | Find all feasible solutions | Find optimal solution |
| **Traversal Method** | DFS, Depth-First | BFS/Priority Queue, Bound-First |
| **Pruning Basis** | Constraint conditions | Cost bound + Current optimal |
| **Application** | Combinations, Permutations, Search | Optimization problems |

**Pseudocode**:
```c
Algorithm BranchAndBound(initialState, costFunc):
    bestValue = ∞  // Current optimal solution value
    bestSolution = null
    queue = PriorityQueue()  // Sorted by lower bound
    queue.push(initialState, 0)

    while queue is not empty:
        node = queue.pop()  // Take node with smallest bound

        // Prune: bound exceeds current optimal
        if lowerBound(node) >= bestValue:
            continue

        // Found complete solution
        if isComplete(node):
            if cost(node) < bestValue:
                bestValue = cost(node)
                bestSolution = node
        else:
            // Generate child nodes and enqueue
            for child in branch(node):
                if lowerBound(child) < bestValue:
                    queue.push(child, lowerBound(child))

    return bestSolution
```

**Branching Strategies**:
- **Depth-First Branching (DFS)**: Usually combined with pruning, high memory efficiency
- **Breadth-First Branching (BFS)**: Reaches optimal solution faster
- **Best-First Branching**: Select node with smallest bound each time, converges quickly

**Applicable Conditions**:
- Problem is an optimization problem (maximize or minimize)
- Can quickly calculate bounds (lower or upper)
- Bound calculation is not overly complex

**Typical Applications**:
- **Traveling Salesman Problem (TSP)**: Use matrix normalization lower bound
- **0-1 Knapsack Optimization**: Upper bound from fractional knapsack relaxation
- **Task Assignment**: Lower bound from minimum cost matching
- **Bin Packing**: Lower bound from total item volume
- **Job Scheduling**: Lower bound from critical path

---

## II. Search Strategies

Search strategies are not core algorithm thinking, but rather a problem-solving strategy. They define how to systematically explore nodes in state space to find target states or solutions satisfying specific conditions. Search strategies can be divided into two main categories: Depth-First Search (DFS) and Breadth-First Search (BFS).

### 6. Search (Search) [Source Code](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/search-algorithms)

**Definition**: Search is the systematic exploration of nodes in state space, gradually transferring from initial state to target state, or finding specific targets in all reachable states. In simple terms, it's traversing state nodes according to some strategy (such as breadth-first, depth-first) until you find the target or traverse all nodes. Search strategies are widely used in pathfinding and state space exploration problems.

#### Breadth-First Search (BFS)

**Characteristics**: Breadth-First Search is a layer-by-layer traversal strategy, expanding level by level, expanding nodes closer to the starting point first. It's generally implemented with a queue, ensuring nodes closer to the starting point are visited first.

**Implementation Principle**:
```c
Algorithm BFS(Graph G, start, target):
    queue = Queue()
    visited = Set()
    queue.enqueue(start)
    visited.add(start)
    // Dequeue node from queue, check if it's target
    while queue is not empty:
        node = queue.dequeue()
        if node == target:
            return found(node)
        // Traverse all neighbors of current node
        for neighbor in G.getNeighbors(node):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.enqueue(neighbor)

    return notFound()
```

**Traversal Principle**:
```
       Start
      / | \
     1  2  3   ← Level 1
    /| |\ |    ← Level 2
   ...   ...  ...
```

**Characteristics**:
- **Completeness**: Will definitely find target if it exists
- **Optimality**: Finds shortest path in unweighted graphs
- **Space Complexity**: O(b^d), where b is branching factor, d is depth

**Applications**: Unweighted shortest path, connectivity detection, level traversal

---

#### Depth-First Search (DFS)

**Characteristics**: Depth-First Search is a strategy that goes to the end of one path, then backtracks to try other paths. Simply put, go to the end of one path first, then backtrack to the previous node and go to the end of another path. It's typically implemented with a stack or recursion.

**Implementation Principle - Recursive Version**:
```c
Algorithm DFS_Recursive(node, target, visited, Graph G):
    if node == target:
        return found(node)

    visited.add(node)
    // Traverse all neighbors of current node
    for neighbor in G.getNeighbors(node):
        if neighbor not in visited:
            // Recursively call DFS to search neighbor
            result = DFS_Recursive(neighbor, target, visited, G)
            if result found:
                return result

    return notFound()
```

**Implementation Principle - Iterative Version (Stack)**:
```c
Algorithm DFS_Iterative(start, target, Graph G):
    stack = Stack()
    visited = Set()
    stack.push(start)
    visited.add(start)
    // Pop node from stack, check if it's target
    while stack is not empty:
        node = stack.pop()
        if node == target:
            return found(node)
        // Traverse all neighbors of current node
        for neighbor in G.getNeighbors(node):
            if neighbor not in visited:
                visited.add(neighbor)
                stack.push(neighbor)

    return notFound()
```

**Traversal Order**:
```
    Start
    │
    ├─→ 1-1-1-1  ← Go to end of one path
    │
    └─→ 2-2-2    ← Backtrack and go another path
```

**Applications**: Topological Sort, Strongly Connected Components, Backtracking Search, Parentheses Generation

---

#### Heuristic Search (A*)

**Characteristics:** Heuristic search is a class of search strategies that use heuristic functions to evaluate node potential. The typical algorithm is A* (A-star) search.

The core idea is to evaluate each node's priority through the heuristic function **f(n) = g(n) + h(n)**, where g(n) represents the actual cost from start to current node n, and h(n) represents the estimated cost from n to target node. The algorithm prioritizes expanding nodes with smallest f(n) that are most promising to reach the target.

**Concept Analysis**:
- **g(n)**: Actual cost from start to current node n
- **h(n)**: Heuristic estimate, estimated cost from n to target (must satisfy admissibility)
- **f(n)**: Overall estimate, determines node priority (smaller is higher priority)

**Pseudocode**:
```c
Algorithm AStar(start, target, Graph G):
    openSet = PriorityQueue()  // Sorted by f(n)
    closedSet = Set()
    gScore = {start: 0}
    fScore = {start: heuristic(start, target)}

    openSet.add(start, fScore[start])

    while openSet is not empty:
        current = openSet.pop()  // Node with smallest f value

        if current == target:
            return reconstruct_path(current)

        closedSet.add(current)
        // Traverse all neighbors of current node
        for neighbor in G.getNeighbors(current):
            if neighbor in closedSet:
                continue

            tentative_g = gScore[current] + cost(current, neighbor)
            // If neighbor not in openSet, or reaching neighbor through current is better
            if neighbor not in openSet or tentative_g < gScore[neighbor]:
                gScore[neighbor] = tentative_g
                fScore[neighbor] = gScore[neighbor] + heuristic(neighbor, target)
                openSet.add(neighbor, fScore[neighbor])

    return pathNotFound()
```

**Diagram**:
```
         Start
         / │ \
        /  │  \
     Node1 Node2 Node3
     (f=10) (f=5) (f=8)
```

**Heuristic Function Design**:
- **Manhattan Distance** (h(n) = |x₁-x₂| + |y₁-y₂|): Grid problems
- **Euclidean Distance** (h(n) = √((x₁-x₂)² + (y₁-y₂)²)): Continuous space
- **Straight-line Distance**: Any space

**Admissibility Condition**: h(n) ≤ actual minimum cost, guarantees finding optimal solution

**Applications**: Game AI pathfinding, Robot Navigation, Map Navigation

---

#### Iterative Deepening (IDDFS)

**Characteristics**: Iterative Deepening Search (IDDFS) combines the low space consumption of Depth-First Search (DFS) and the level-by-level search characteristics of Breadth-First Search (BFS), gradually increasing search depth limits and repeatedly performing depth-first search until the target node is found. The core idea is to start depth-first search from depth 0, each time increase the maximum search depth by 1, gradually expand the search range, thereby finding the shallowest solution while maintaining low space complexity.

**Implementation Principle**:
```c
Algorithm IDDFS(start, target, Graph G):
    depth = 0

    while true:
        // Each time increase depth limit and perform one depth-first search
        result = DFS_DepthLimited(start, target, depth, G)
        if result found:
            return result
        depth = depth + 1
```

**Depth-Limited DFS**:
```py
Algorithm DFS_DepthLimited(node, target, maxDepth, visited, G):
    if node == target:
        return found(node)

    if maxDepth == 0:
        return notFound()

    visited.add(node)
    # Loop recursively search neighbor nodes
    for neighbor in G.getNeighbors(node):
        if neighbor not in visited:
            result = DFS_DepthLimited(neighbor, target, maxDepth-1, visited, G)
            if result found:
                return result

    return notFound()
```

**Search Trajectory**:
```
1st time: Depth limit = 1  →  Search Layer A nodes
2nd time: Depth limit = 2  →  Search Layers A-B nodes
3rd time: Depth limit = 3  →  Search Layers A-B-C nodes  ← Found target
```

**Characteristics**:
- **Space Complexity**: O(d), d is solution depth (DFS advantage)
- **Time Complexity**: O(b^d), same as BFS but with smaller constant factor
- **Applications**: Large search space with unknown depth

---

**Search Strategy Comparison Table**:

| Strategy | Completeness | Optimality | Time | Space | Applicable Scenarios |
|------|--------|--------|------|------|---------|
| **BFS** | ✓ | ✓(Unweighted) | O(b^d) | O(b^d) | Unweighted, Level-based |
| **DFS** | ✓ | ✗ | O(b^d) | O(d) | Memory-limited, Backtracking |
| **A\*** | ✓ | ✓(Admissible h) | Depends on h | Depends on h | Heuristic, Pathfinding |
| **IDDFS** | ✓ | ✓(Unweighted) | O(b^d) | O(d) | Unknown depth |

---

## III. Randomization Algorithm

### 7. Randomization (Randomization) [Source Code](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/random-algorithm)

Randomization is not core algorithm thinking, but rather a problem-solving strategy.

**Definition**: Randomization introduces randomness into algorithm execution (usually random choice), aiming to improve performance in expectation, break worst-case constructions, and simplify problem analysis. In simple terms, it's introducing random factors into algorithms.

Randomization has many applications. For example, in sorting algorithms, randomly selecting pivots can avoid worst-case scenarios; in graph algorithms, randomization can be used to quickly approximate shortest paths; in machine learning, randomization can be used to initialize model parameters.

**Theoretical Foundation**:
- **Random Variable Expectation**: E[X] = Σ probability(x) × value(x)
- **High-Probability Events**: Events occur with probability at least 1 - δ (δ is small)
- **Geometric Distribution**: Expected number of trials until first success

**Two Main Types**:

#### Monte Carlo Algorithm (Monte Carlo)

**Characteristics**:
- Running time is **fixed or determined**
- Results may **have error probability**
- Errors are **controllable** (reduce error rate by multiple runs)

**Pseudocode**:
```c
Algorithm MonteCarlo(Problem P, iterations):
    result_counts = {}

    for i = 1 to iterations:
        // Random simulation once
        sample = randomRun(P)
        result_counts[sample] += 1

    // Estimate answer by frequency
    return mostFrequent(result_counts)

    // Error rate ≈ 1 / iterations
```

**Error Rate Analysis**:
```
More runs, results closer to true value
│
│     ╱╲
│    ╱  ╲    ╱╲
└───╱────╲──╱──╲──── True value
    Iterations increase →
```

**Typical Applications**:
- **Monte Carlo Estimate of Pi**: Ratio of random points falling in circle
- **Probability Verification**: Test if number is prime (Miller-Rabin)
- **Numerical Integration**: Estimate function integral by random sampling
- **Random Sampling**: Unbiased sampling in large-scale data

---

#### Las Vegas Algorithm (Las Vegas)

**Characteristics**:
- Result is **definitely correct**
- Running time **has randomness**
- Performance is **probabilistic**

**Pseudocode**:
```c
Algorithm LasVegas(Problem P):
    while true:
        // Random attempt
        solution = randomAttempt(P)

        // Strict verification
        if verify(solution, P):
            return solution  // Definitely correct

        // Otherwise retry
        // Mathematical analysis of expected attempts...
```

**Time Complexity Analysis**:
```
Expected Time E[T] = Σ P(success at round i) × T(i)
                   = p + 2p(1-p) + 3p(1-p)² + ...
                   = 1/p  (where p = success probability)
```

**Typical Applications**:
- **Random Quick Sort**: Randomly select pivot, average time O(n log n)
- **Skip List**: Randomized balanced linked list, supports O(log n) search
- **Hash Table**: Random hash function reduces collisions
- **Primality Testing**: Random witness verification (Miller-Rabin)
- **Random Minimum Cut**: Karger's minimum cut algorithm

---

**Algorithm Comparison**:

| Dimension | Monte Carlo | Las Vegas |
|------|----------|----------|
| **Result Correctness** | May have errors | Definitely correct |
| **Time Complexity** | Deterministic or fixed | Random, requires expectation analysis |
| **Failure Handling** | Multiple runs, take majority | Retry on failure |
| **Application Tendency** | Verification, Estimation, Simulation | Fast Search, Sorting |

**Selection Guide**:
- If **answer must be correct** and efficient verification exists: Choose **Las Vegas**
- If **single answer can have error** but need quick estimate: Choose **Monte Carlo**
- If need **completely reliable** but allow long running time: **Las Vegas multiple runs**
- If need **quick approximation** and don't mind occasional errors: **Monte Carlo + verification**

## Summary

**Algorithm thinking is the core of problem-solving**. Mastering these basic algorithm thinking approaches means grasping the essence of problem-solving.

Whether it's **Greedy, Divide and Conquer, Dynamic Programming, Backtracking, and Branch and Bound**, or **Search Strategies** and **Randomization Algorithms**, understanding and applying these algorithm thinking approaches will enable you to design and implement solutions to various complex problems more efficiently.

### Algorithm Thinking + Strategy Comparison Table

| Thinking | Definition | Applicable Conditions | Typical Applications |
|------|------|---------|---------|
| [**Greedy**](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/greedy-algorithm) | Select locally optimal at each step | Greedy choice property + Optimal substructure | Fractional knapsack, Minimum spanning tree, Shortest path, Huffman coding, Activity selection |
| [**Divide and Conquer**](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/divide-and-conquer) | Decompose to same-size subproblems, recursively solve, combine results | Subproblems independent, same structure, can combine efficiently | Merge sort, Quick sort, Binary search, Matrix multiplication, Convex hull, Inversion count |
| [**Dynamic Programming**](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/dynamic-programming) | Identify overlapping subproblems, use space for time to avoid recalculation | Overlapping subproblems, optimal substructure (no future dependency) | Knapsack problems, Longest increasing subsequence, Longest common subsequence, Edit distance, Matrix path sum, Climbing stairs, Coin change |
| [**Backtracking**](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/backtracking) | Try each choice, backtrack when path fails, retry | Need enumerate all possibilities, tree/recursive structure, pruning conditions exist | Permutations, Combinations, Subsets, N-Queens, Sudoku, Island count, Maze pathfinding, Phone combinations |
| [**Branch and Bound**](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/branch-and-bound) | Based on backtracking, calculate bounds for nodes, more aggressive pruning | Optimization problem, can quickly calculate bounds | Traveling salesman, 0-1 knapsack optimization, Task assignment, Bin packing, Job scheduling |
| [**Search**](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/search-algorithms) | Systematically explore in state space, transfer from initial to target state | Problem has state transitions, can define target state | Unweighted shortest path, Connectivity, Level traversal, Topological sort, Strongly connected components, Game AI pathfinding |
| [**Randomization**](https://github.com/microwind/algorithms/tree/main/algorithmic-thinking/random-algorithm) | Introduce randomness in algorithm, improve performance or simplify analysis | Need break worst case, accept probabilistic guarantee | Random quick sort, Skip list, Hash table, Miller-Rabin primality test, Minimum cut algorithm |


## Source Code
- Algorithm implementation source code: [https://github.com/microwind/algorithms/](https://github.com/microwind/algorithms/)
