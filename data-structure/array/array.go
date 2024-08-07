package main

import "fmt"

func main() {
  // 定义一个包含5个整数的数组
  arr := [5]int{1, 2, 3, 4, 5}

  // 访问数组元素
  fmt.Println("Element at index 2:", arr[2])

  // 修改数组元素
  arr[2] = 10
  fmt.Println("Modified element at index 2:", arr[2])

  // 遍历数组
  for _, value := range arr {
    fmt.Print(value, " ")
  }
  fmt.Println()
}
