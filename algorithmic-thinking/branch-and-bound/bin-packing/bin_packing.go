package main

import (
  "fmt"
  "sort"
)

// 装箱问题 - 分支定界算法 (Go)
type BinPackingSolver struct {
  items        []int
  binCapacity  int
  n            int
  minBins      int
  bestPacking  [][]int
  currentBins  [][]int
  machineTimes []int
}

func NewBinPackingSolver(items []int, capacity int) *BinPackingSolver {
  sorted := make([]int, len(items))
  copy(sorted, items)
  sort.Sort(sort.Reverse(sort.IntSlice(sorted)))

  return &BinPackingSolver{
    items:       sorted,
    binCapacity: capacity,
    n:           len(items),
    minBins:     len(items),
  }
}

func (b *BinPackingSolver) lowerBound(itemIdx int) int {
  totalWeight := 0
  for i := itemIdx; i < b.n; i++ {
    totalWeight += b.items[i]
  }
  return (totalWeight + b.binCapacity - 1) / b.binCapacity
}

func sumSlice(s []int) int {
  sum := 0
  for _, v := range s {
    sum += v
  }
  return sum
}

func (b *BinPackingSolver) branchAndBound(itemIdx int) {
  if len(b.currentBins)+b.lowerBound(itemIdx) >= b.minBins {
    return
  }

  if itemIdx == b.n {
    if len(b.currentBins) < b.minBins {
      b.minBins = len(b.currentBins)
      b.bestPacking = make([][]int, len(b.currentBins))
      for i, bin := range b.currentBins {
        b.bestPacking[i] = make([]int, len(bin))
        copy(b.bestPacking[i], bin)
      }
    }
    return
  }

  item := b.items[itemIdx]
  placed := false

  for binIdx := 0; binIdx < len(b.currentBins); binIdx++ {
    if sumSlice(b.currentBins[binIdx])+item <= b.binCapacity {
      b.currentBins[binIdx] = append(b.currentBins[binIdx], item)
      b.branchAndBound(itemIdx + 1)
      b.currentBins[binIdx] = b.currentBins[binIdx][:len(b.currentBins[binIdx])-1]
      placed = true
      break
    }
  }

  if !placed && len(b.currentBins) < b.minBins {
    b.currentBins = append(b.currentBins, []int{item})
    b.branchAndBound(itemIdx + 1)
    b.currentBins = b.currentBins[:len(b.currentBins)-1]
  }
}

func (b *BinPackingSolver) Solve() (int, [][]int) {
  b.branchAndBound(0)
  return b.minBins, b.bestPacking
}

func main() {
  items := []int{7, 5, 5, 3, 3, 3, 2}
  capacity := 10

  fmt.Println("Bin Packing Problem (Go)")
  fmt.Printf("Items: %v, Capacity: %d\n", items, capacity)

  solver := NewBinPackingSolver(items, capacity)
  numBins, packing := solver.Solve()

  fmt.Printf("\nMinimum Bins: %d\n", numBins)
  for i, bin := range packing {
    fmt.Printf("Bin %d: %v (weight: %d)\n", i, bin, sumSlice(bin))
  }
}

/**
jarry@Mac bin-packing % go run bin_packing.go
Bin Packing Problem (Go)
Items: [7 5 5 3 3 3 2], Capacity: 10

Minimum Bins: 3
Bin 0: [7 3] (weight: 10)
Bin 1: [5 5] (weight: 10)
Bin 2: [3 3 2] (weight: 8)
*/
