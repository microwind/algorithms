package main

import (
  "fmt"
)

// JobSchedulingSolver 作业调度求解器
type JobSchedulingSolver struct {
  jobTimes        []int
  numMachines     int
  n               int
  minMakespan     int
  bestSchedule    [][]int
  currentSchedule [][]int
  machineTimes    []int
}

// NewJobSchedulingSolver 创建新的作业调度求解器
func NewJobSchedulingSolver(jobTimes []int, numMachines int) *JobSchedulingSolver {
  n := len(jobTimes)
  return &JobSchedulingSolver{
    jobTimes:        jobTimes,
    numMachines:     numMachines,
    n:               n,
    minMakespan:     1<<31 - 1, // Max int
    bestSchedule:    make([][]int, numMachines),
    currentSchedule: make([][]int, numMachines),
    machineTimes:    make([]int, numMachines),
  }
}

// lowerBound 计算下界
func (s *JobSchedulingSolver) lowerBound(jobIdx int) int {
  // 剩余作业的总时间
  remainingTime := 0
  for i := jobIdx; i < s.n; i++ {
    remainingTime += s.jobTimes[i]
  }

  // 当前机器的最大负载
  maxTime := 0
  for _, time := range s.machineTimes {
    if time > maxTime {
      maxTime = time
    }
  }

  // 下界 = 最大负载 + 剩余作业的平均负载
  return maxTime + (remainingTime+s.numMachines-1)/s.numMachines
}

// branchAndBound 分支定界搜索
func (s *JobSchedulingSolver) branchAndBound(jobIdx int) {
  // 剪枝：下界 >= 最优解时跳过
  if s.lowerBound(jobIdx) >= s.minMakespan {
    return
  }

  // 基础情况：所有作业已分配
  if jobIdx == s.n {
    makespan := 0
    for _, time := range s.machineTimes {
      if time > makespan {
        makespan = time
      }
    }

    if makespan < s.minMakespan {
      s.minMakespan = makespan
      // 复制最优调度方案
      for i := 0; i < s.numMachines; i++ {
        s.bestSchedule[i] = make([]int, len(s.currentSchedule[i]))
        copy(s.bestSchedule[i], s.currentSchedule[i])
      }
    }
    return
  }

  // 分支：尝试将作业分配给每台机器
  job := s.jobTimes[jobIdx]

  for machine := 0; machine < s.numMachines; machine++ {
    // 选择：分配作业到机器
    s.currentSchedule[machine] = append(s.currentSchedule[machine], job)
    s.machineTimes[machine] += job

    // 探索：递归处理下一个作业
    s.branchAndBound(jobIdx + 1)

    // 撤销：移除作业
    s.currentSchedule[machine] = s.currentSchedule[machine][:len(s.currentSchedule[machine])-1]
    s.machineTimes[machine] -= job
  }
}

// Solve 求解作业调度问题
func (s *JobSchedulingSolver) Solve() (int, [][]int) {
  s.branchAndBound(0)
  return s.minMakespan, s.bestSchedule
}

// sumSlice 计算数组和
func sumSlice(arr []int) int {
  sum := 0
  for _, v := range arr {
    sum += v
  }
  return sum
}

func main() {
  fmt.Println("============================================================")
  fmt.Println("Job Scheduling Problem (Go Implementation)")
  fmt.Println("============================================================")
  fmt.Println()

  // 测试用例 1
  jobTimes := []int{5, 3, 8, 6, 2}
  numMachines := 2

  fmt.Printf("作业处理时间: %v\n", jobTimes)
  fmt.Printf("机器数量: %d\n", numMachines)
  fmt.Printf("总工作量: %d\n", sumSlice(jobTimes))
  fmt.Println()

  solver := NewJobSchedulingSolver(jobTimes, numMachines)
  makespan, schedule := solver.Solve()

  fmt.Printf("最小完成时间: %d\n", makespan)
  fmt.Println("\n调度方案:")
  for i, jobs := range schedule {
    fmt.Printf("机器 %d: %v (时间: %d)\n", i, jobs, sumSlice(jobs))
  }
  fmt.Println()

  // 测试用例 2
  fmt.Println("============================================================")
  jobTimes2 := []int{7, 5, 5, 4, 3, 2, 2}
  numMachines2 := 3

  fmt.Printf("作业处理时间: %v\n", jobTimes2)
  fmt.Printf("机器数量: %d\n", numMachines2)
  fmt.Printf("总工作量: %d\n", sumSlice(jobTimes2))
  fmt.Println()

  solver2 := NewJobSchedulingSolver(jobTimes2, numMachines2)
  makespan2, schedule2 := solver2.Solve()

  fmt.Printf("最小完成时间: %d\n", makespan2)
  fmt.Println("\n调度方案:")
  for i, jobs := range schedule2 {
    total := sumSlice(jobs)
    fmt.Printf("机器 %d: %v (时间: %d)\n", i, jobs, total)
  }
}
