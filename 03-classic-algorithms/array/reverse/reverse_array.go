package main

import "fmt"

// 反转数组的函数
func reverseArray(arr []int) {
  n := len(arr)
  // 交换数组的前后元素
  for i := 0; i < n/2; i++ {
    arr[i], arr[n-i-1] = arr[n-i-1], arr[i]
  }
}

func main() {
  arr := []int{1, 2, 3, 4, 5} // 初始化数组
  reverseArray(arr)           // 调用反转函数
  fmt.Println(arr)            // 输出反转后的数组
}
