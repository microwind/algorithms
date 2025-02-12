package main

import (
  "fmt"
)

var step int = 0

// 递归分解数组，最小粒度为2个
func divide(arr []int) []int {
  fmt.Println("start:", arr)
  if len(arr) < 2 {
    return arr
  }

  mid := len(arr) / 2
  left := divide(arr[:mid])
  right := divide(arr[mid:])

  step += 1
  fmt.Printf("after: %d -> %v %v %v\n", step, arr, left, right)

  return append(left, right...)
}

func main() {
  arr := []int{3, 1, 2, 5, 6, 4}
  divide(arr)
}

/*
jarry@MacBook-Pro recursion % go run divide.go
start: [3 1 2 5 6 4]
start: [3 1 2]
start: [3]
start: [1 2]
start: [1]
start: [2]
after: 1 -> [1 2] [1] [2]
after: 2 -> [3 1 2] [3] [1 2]
start: [5 6 4]
start: [5]
start: [6 4]
start: [6]
start: [4]
after: 3 -> [6 4] [6] [4]
after: 4 -> [5 6 4] [5] [6 4]
after: 5 -> [3 1 2 5 6 4] [3 1 2] [5 6 4]
*/
