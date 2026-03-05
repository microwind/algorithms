// 0-1背包分支限界法

package main

import (
  "fmt"
  "sort"
)

type Item struct {
  weight int
  value  int
  idx    int
  ratio  float64
}

type KnapsackSolver struct {
  items     []Item
  n         int
  capacity  int
  maxProfit int
  bestItems []bool
  curItems  []bool
}

func NewKnapsackSolver(weights, values []int, capacity int) *KnapsackSolver {
  n := len(weights)
  items := make([]Item, n)
  for i := 0; i < n; i++ {
    items[i] = Item{weights[i], values[i], i, float64(values[i]) / float64(weights[i])}
  }
  // 按价值/重量比降序排序
  sort.Slice(items, func(i, j int) bool {
    return items[i].ratio > items[j].ratio
  })
  return &KnapsackSolver{
    items:     items,
    n:         n,
    capacity:  capacity,
    maxProfit: 0,
    bestItems: make([]bool, n),
    curItems:  make([]bool, n),
  }
}

// 上界估计（分数背包）
func (k *KnapsackSolver) upperBound(idx, weight, profit int) int {
  if weight >= k.capacity {
    return profit
  }
  bound := float64(profit)
  remain := k.capacity - weight
  // 计算分数背包的上界
  for i := idx; i < k.n; i++ {
    item := k.items[i]
    // 若物品重量小于等于剩余容量，则直接加入
    if item.weight <= remain {
      bound += float64(item.value)
      remain -= item.weight
    } else {
      // 否则加入剩余容量的分数部分
      bound += float64(item.value) * float64(remain) / float64(item.weight)
      break
    }
  }
  return int(bound)
}

func (k *KnapsackSolver) branchAndBound(idx, weight, profit int) {
  if k.upperBound(idx, weight, profit) <= k.maxProfit {
    return
  }
  // 基础情况：到达物品列表末尾
  if idx == k.n {
    if profit > k.maxProfit {
      k.maxProfit = profit
      copy(k.bestItems, k.curItems)
    }
    return
  }
  item := k.items[idx]
  // 分支1：选当前物品
  if weight+item.weight <= k.capacity {
    k.curItems[item.idx] = true
    k.branchAndBound(idx+1, weight+item.weight, profit+item.value)
    k.curItems[item.idx] = false
  }
  // 分支2：不选当前物品
  k.branchAndBound(idx+1, weight, profit)
}

func (k *KnapsackSolver) Solve() (int, []int) {
  k.branchAndBound(0, 0, 0)
  selected := []int{}
  // 收集选中的物品索引
  for i, chosen := range k.bestItems {
    if chosen {
      selected = append(selected, i)
    }
  }
  return k.maxProfit, selected
}

func main() {
  fmt.Println("==============================")
  fmt.Println("0-1 Knapsack Optimization (Go)")
  fmt.Println("==============================\n")
  weights := []int{2, 3, 4, 5}
  values := []int{3, 4, 5, 6}
  capacity := 8
  fmt.Println("Test Case 1:")
  fmt.Println("Weights:", weights)
  fmt.Println("Values:", values)
  fmt.Println("Capacity:", capacity)
  solver := NewKnapsackSolver(weights, values, capacity)
  maxProfit, selected := solver.Solve()
  fmt.Println("Maximum Profit:", maxProfit)
  fmt.Println("Selected Items:", selected)
  wSum := 0
  for _, i := range selected {
    wSum += weights[i]
  }
  fmt.Println("Total Weight:", wSum)
  fmt.Println("\n==============================")
  weights2 := []int{5, 4, 3, 4, 2}
  values2 := []int{10, 40, 30, 50, 35}
  capacity2 := 10
  fmt.Println("Test Case 2:")
  fmt.Println("Weights:", weights2)
  fmt.Println("Values:", values2)
  fmt.Println("Capacity:", capacity2)
  solver2 := NewKnapsackSolver(weights2, values2, capacity2)
  maxProfit2, selected2 := solver2.Solve()
  fmt.Println("Maximum Profit:", maxProfit2)
  fmt.Println("Selected Items:", selected2)
  wSum2 := 0
  for _, i := range selected2 {
    wSum2 += weights2[i]
  }
  fmt.Println("Total Weight:", wSum2)
}
