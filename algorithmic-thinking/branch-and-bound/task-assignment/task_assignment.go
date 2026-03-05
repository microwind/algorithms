package taskassignment
// 任务分配问题 - 分支定界算法 (Go)
package main

import (
	"fmt"
	"math"
)

type TaskSolver struct {
	cost              [][]int
	n                 int
	minCost           int
	bestAssignment    []int
	currentAssignment []int
	assignedWorkers   []bool
}

func NewTaskSolver(costMatrix [][]int) *TaskSolver {
	n := len(costMatrix)
	return &TaskSolver{
		cost:              costMatrix,
		n:                 n,
		minCost:           math.MaxInt32,
		bestAssignment:    make([]int, n),
		currentAssignment: make([]int, n),
		assignedWorkers:   make([]bool, n),
	}
}

func (t *TaskSolver) lowerBound(taskIdx int) int {
	bound := 0
	for i := taskIdx; i < t.n; i++ {
		minCost := math.MaxInt32
		for j := 0; j < t.n; j++ {
			if !t.assignedWorkers[j] {
				if t.cost[i][j] < minCost {
					minCost = t.cost[i][j]
				}
			}
		}
		if minCost != math.MaxInt32 {
			bound += minCost
		}
	}
	return bound
}

func (t *TaskSolver) branchAndBound(taskIdx, currentCost int) {
	if currentCost+t.lowerBound(taskIdx) >= t.minCost {
		return












































}	}		fmt.Printf("  %d -> %d (cost: %d)\n", task, worker, costMatrix[task][worker])	for task, worker := range assignment {	fmt.Println("Task -> Worker:")	fmt.Printf("Minimum Cost: %d\n", minCost)	minCost, assignment := solver.Solve()	solver := NewTaskSolver(costMatrix)	fmt.Println("Task Assignment Problem (Go)")	}		{3, 5, 7},		{6, 8, 4},		{5, 7, 9},	costMatrix := [][]int{func main() {}	return t.minCost, t.bestAssignment	t.branchAndBound(0, 0)func (t *TaskSolver) Solve() (int, []int) {}	}		}			t.assignedWorkers[worker] = false			t.branchAndBound(taskIdx+1, currentCost+t.cost[taskIdx][worker])			t.assignedWorkers[worker] = true			t.currentAssignment[taskIdx] = worker		if !t.assignedWorkers[worker] {	for worker := 0; worker < t.n; worker++ {	}		return		}			copy(t.bestAssignment, t.currentAssignment)			t.minCost = currentCost		if currentCost < t.minCost {	if taskIdx == t.n {	}