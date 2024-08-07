package main

import "fmt"

// 旋转数组
func rotateArray(arr []int, d int) {
  n := len(arr)
  temp := make([]int, d)
  copy(temp, arr[:d])
  for i := 0; i < n-d; i++ {
    arr[i] = arr[i+d]
  }
  for i := 0; i < d; i++ {
    arr[n-d+i] = temp[i]
  }
}

func main() {
  arr := []int{1, 2, 3, 4, 5, 6, 7}
  d := 4
  rotateArray(arr, d)
  fmt.Println("Rotated array:", arr)
}

/*
jarry@jarrys-MacBook-Pro rotate % go run rotate_array.go
Rotated array: [5 6 7 1 2 3 4]
*/
