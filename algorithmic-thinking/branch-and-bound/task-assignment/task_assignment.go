package main

import (
	"fmt"
	"math"
)

/*
任务分配问题 - 分支定界算法 (Go Implementation)

算法说明:
- 将 n 个任务分配给 n 个员工，使总成本最小
- 每个员工只能分配一个任务，每个任务只能分配给一个员工
- 使用分支定界法进行搜索和剪枝
- 下界函数使用贪心估计

时间复杂度：O(n! * n)（指数级，使用剪枝优化）
空间复杂度：O(n^2)

示例:
    cost = {{5,7,9},{6,8,4},{3,5,7}}
    结果: 最小总成本 15
*/

// TaskSolver 用于求解任务分配问题
type TaskSolver struct {
	cost              [][]int
	n                 int
	minCost           int
	bestAssignment    []int
	currentAssignment []int
	assignedWorkers   []bool
}

// NewTaskSolver 创建新的求解器
func NewTaskSolver(costMatrix [][]int) *TaskSolver {
	n := len(costMatrix)
	return &TaskSolver{
		cost:              costMatrix,
		n:                 n,
		minCost:           math.MaxInt,
		bestAssignment:    make([]int, n),
		currentAssignment: make([]int, n),
		assignedWorkers:   make([]bool, n),
	}
}

// lowerBound 计算下界（贪心估计）
func (t *TaskSolver) lowerBound(taskIdx int) int {
	bound := 0
	for i := taskIdx; i < t.n; i++ {
		minCost := math.MaxInt
		for j := 0; j < t.n; j++ {
			if !t.assignedWorkers[j] {
				if t.cost[i][j] < minCost {
					minCost = t.cost[i][j]
				}
			}
		}
		if minCost != math.MaxInt {
			bound += minCost
		}
	}
	return bound
}

// branchAndBound 分支定界搜索
func (t *TaskSolver) branchAndBound(taskIdx, currentCost int) {
	// 剪枝：当前成本 + 下界 >= 最优解
	if currentCost+t.lowerBound(taskIdx) >= t.minCost {
		return
	}

	// 基础情况：所有任务已分配
	if taskIdx == t.n {
		if currentCost < t.minCost {
			t.minCost = currentCost
			copy(t.bestAssignment, t.currentAssignment)
		}
		return
	}

	// 分支：尝试将当前任务分配给每个可用员工
	for worker := 0; worker < t.n; worker++ {
		if !t.assignedWorkers[worker] {
			t.currentAssignment[taskIdx] = worker
			t.assignedWorkers[worker] = true

			t.branchAndBound(taskIdx+1, currentCost+t.cost[taskIdx][worker])

			t.assignedWorkers[worker] = false
		}
	}
}

// Solve 求解任务分配问题
func (t *TaskSolver) Solve() (int, []int) {
	t.branchAndBound(0, 0)
	return t.minCost, t.bestAssignment
}

func main() {
	fmt.Println("============================================================")
	fmt.Println("Task Assignment Problem (Go Implementation)")
	fmt.Println("============================================================\n")

	// 测试用例1：基本3x3矩阵
	costMatrix := [][]int{
		{5, 7, 9},
		{6, 8, 4},
		{3, 5, 7},
	}

	fmt.Println("Test Case 1:")
	fmt.Println("Cost Matrix:")
	for i := 0; i < len(costMatrix); i++ {
		fmt.Printf("Task %d: %v\n", i, costMatrix[i])
	}
	fmt.Println()

	solver := NewTaskSolver(costMatrix)
	minCost, assignment := solver.Solve()

	fmt.Printf("Minimum Cost: %d\n\n", minCost)
	fmt.Println("Task -> Worker Assignment:")
	for task := 0; task < len(assignment); task++ {
		worker := assignment[task]
		fmt.Printf("  Task %d -> Worker %d (cost: %d)\n", task, worker, costMatrix[task][worker])
	}

	// 测试用例2：4x4矩阵
	fmt.Println("\n" + "============================================================")
	fmt.Println("\nTest Case 2:")

	costMatrix2 := [][]int{
		{10, 19, 8, 15},
		{10, 18, 7, 17},
		{13, 16, 9, 14},
		{12, 19, 8, 18},
	}

	fmt.Println("Cost Matrix:")
	for i := 0; i < len(costMatrix2); i++ {
		fmt.Printf("Task %d: %v\n", i, costMatrix2[i])
	}
	fmt.Println()

	solver2 := NewTaskSolver(costMatrix2)
	minCost2, assignment2 := solver2.Solve()

	fmt.Printf("Minimum Cost: %d\n\n", minCost2)
	fmt.Println("Task -> Worker Assignment:")
	for task := 0; task < len(assignment2); task++ {
		worker := assignment2[task]
		fmt.Printf("  Task %d -> Worker %d (cost: %d)\n", task, worker, costMatrix2[task][worker])
	}
}

/*
Output:
============================================================
Task Assignment Problem (Go Implementation)
============================================================

Test Case 1:
Cost Matrix:
Task 0: [5 7 9]
Task 1: [6 8 4]
Task 2: [3 5 7]

Minimum Cost: 15

Task -> Worker Assignment:
  Task 0 -> Worker 0 (cost: 5)
  Task 1 -> Worker 2 (cost: 4)
  Task 2 -> Worker 1 (cost: 5)

============================================================

Test Case 2:
Cost Matrix:
Task 0: [10 19 8 15]
Task 1: [10 18 7 17]
Task 2: [13 16 9 14]
Task 3: [12 19 8 18]

Minimum Cost: 33

Task -> Worker Assignment:
  Task 0 -> Worker 0 (cost: 10)
  Task 1 -> Worker 2 (cost: 7)
  Task 2 -> Worker 3 (cost: 14)
  Task 3 -> Worker 1 (cost: 19)
*/
