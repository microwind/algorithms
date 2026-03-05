package main

import (
  "fmt"
  "math"
)

/*
旅行商问题 - 分支定界算法 (Go Implementation)

算法说明:
- 找到经过所有城市恰好一次并回到起始城市的最小成本路径
- 使用分支定界法进行搜索和剪枝
- 下界函数使用最小生成树近似

时间复杂度：O(n! * n^2)（指数级，使用剪枝优化）
空间复杂度：O(n^2)

示例:
    graph = {{0,10,15,20},{10,0,35,25},{15,35,0,30},{20,25,30,0}}
    结果: 最小总成本 80
*/

// TSPSolver 用于求解旅行商问题
type TSPSolver struct {
  dist        [][]int
  n           int
  minCost     int
  bestPath    []int
  currentPath []int
  visited     []bool
}

// NewTSPSolver 创建新的求解器
func NewTSPSolver(distMatrix [][]int) *TSPSolver {
  n := len(distMatrix)
  visited := make([]bool, n)
  visited[0] = true
  return &TSPSolver{
    dist:        distMatrix,
    n:           n,
    minCost:     math.MaxInt,
    bestPath:    make([]int, 0),
    currentPath: []int{0},
    visited:     visited,
  }
}

// lowerBound 计算下界（使用最小生成树近似）
func (t *TSPSolver) lowerBound(node, level, currentCost int) int {
  bound := currentCost

  // 从当前节点到未访问城市添加最小成本边
  minEdge := math.MaxInt
  for i := 0; i < t.n; i++ {
    if !t.visited[i] {
      if t.dist[node][i] < minEdge {
        minEdge = t.dist[node][i]
      }
    }
  }

  if minEdge != math.MaxInt {
    bound += minEdge
  }

  // 估计剩余路径的最小成本
  for i := 0; i < t.n; i++ {
    if !t.visited[i] {
      min1, min2 := math.MaxInt, math.MaxInt
      for j := 0; j < t.n; j++ {
        if !t.visited[j] && i != j {
          if t.dist[i][j] < min1 {
            min2 = min1
            min1 = t.dist[i][j]
          } else if t.dist[i][j] < min2 {
            min2 = t.dist[i][j]
          }
        }
      }

      if min2 != math.MaxInt {
        bound += min1
      }
    }
  }

  return bound
}

// branchAndBound 分支定界搜索
func (t *TSPSolver) branchAndBound(node, level, cost int) {
  // 基础情况：找到完整路径（所有城市都被访问）
  if level == t.n {
    totalCost := cost + t.dist[node][0]
    if totalCost < t.minCost {
      t.minCost = totalCost
      t.bestPath = make([]int, len(t.currentPath))
      copy(t.bestPath, t.currentPath)
    }
    return
  }

  // 剪枝：下界 >= 当前最优，跳过此分支
  if t.lowerBound(node, level, cost) >= t.minCost {
    return
  }

  // 分支：探索未访问的城市
  for i := 0; i < t.n; i++ {
    if !t.visited[i] {
      t.visited[i] = true
      t.currentPath = append(t.currentPath, i)

      t.branchAndBound(i, level+1, cost+t.dist[node][i])

      t.currentPath = t.currentPath[:len(t.currentPath)-1]
      t.visited[i] = false
    }
  }
}

// Solve 求解旅行商问题
func (t *TSPSolver) Solve() (int, []int) {
  t.branchAndBound(0, 1, 0)
  result := make([]int, len(t.bestPath)+1)
  copy(result, t.bestPath)
  result[len(t.bestPath)] = 0
  return t.minCost, result
}

func main() {
  fmt.Println("============================================================")
  fmt.Println("Traveling Salesman Problem (Go Implementation)")
  fmt.Println("============================================================\n")

  // 测试用例1：4个城市
  graph := [][]int{
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0},
  }

  fmt.Println("Test Case 1: 4 Cities")
  fmt.Println("Distance Matrix:")
  for i := 0; i < len(graph); i++ {
    fmt.Printf("City %d: %v\n", i, graph[i])
  }
  fmt.Println()

  solver := NewTSPSolver(graph)
  minCost, path := solver.Solve()

  fmt.Printf("Minimum Tour Cost: %d\n\n", minCost)
  fmt.Print("Tour Path: ")
  for i := 0; i < len(path); i++ {
    if i > 0 {
      fmt.Print(" -> ")
    }
    fmt.Print(path[i])
  }
  fmt.Println()

  // 测试用例2：5个城市
  fmt.Println("\n" + "============================================================")
  fmt.Println("\nTest Case 2: 5 Cities")

  graph2 := [][]int{
    {0, 29, 20, 32, 23},
    {29, 0, 21, 37, 18},
    {20, 21, 0, 28, 23},
    {32, 37, 28, 0, 34},
    {23, 18, 23, 34, 0},
  }

  fmt.Println("Distance Matrix:")
  for i := 0; i < len(graph2); i++ {
    fmt.Printf("City %d: %v\n", i, graph2[i])
  }
  fmt.Println()

  solver2 := NewTSPSolver(graph2)
  minCost2, path2 := solver2.Solve()

  fmt.Printf("Minimum Tour Cost: %d\n\n", minCost2)
  fmt.Print("Tour Path: ")
  for i := 0; i < len(path2); i++ {
    if i > 0 {
      fmt.Print(" -> ")
    }
    fmt.Print(path2[i])
  }
  fmt.Println()
}

/*
Output:
============================================================
Traveling Salesman Problem (Go Implementation)
============================================================

Test Case 1: 4 Cities
Distance Matrix:
City 0: [0 10 15 20]
City 1: [10 0 35 25]
City 2: [15 35 0 30]
City 3: [20 25 30 0]

Minimum Tour Cost: 80

Tour Path: 0 -> 1 -> 3 -> 2 -> 0

============================================================

Test Case 2: 5 Cities
Distance Matrix:
City 0: [0 29 20 32 23]
City 1: [29 0 21 37 18]
City 2: [20 21 0 28 23]
City 3: [32 37 28 0 34]
City 4: [23 18 23 34 0]

Minimum Tour Cost: 122

Tour Path: 0 -> 3 -> 2 -> 1 -> 4 -> 0
*/
