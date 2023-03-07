/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import (
  "fmt"
  "time"
)

// 1. 希尔排序，基于插入排序进行了分组排序
func shellSort1(arr []int) []int {
  var arrLen int = len(arr)
  //  设置分组间隔
  var gap int = (arrLen / 2)
  // 如果间隔大于0，则表示还可以继续分
  for gap > 0 {
    for i := 0; i < arrLen; i++ {
      var current = arr[i]
      var j = i
      fmt.Println("gap=", gap, " j=", j, "arr:", arr)
      // 分组按照插入排序逐个位移
      for j >= gap && current < arr[j-gap] {
        arr[j] = arr[j-gap]
        j -= gap
      }
      // 交换当前项
      arr[j] = current
      // 调整间距为1/2
    }
    gap = (gap / 2)
  }
  return arr
}

func main() {
  time1 := time.Now()
  var arr1 = []int{7, 11, -9, 10, -12, 13, 8}
  fmt.Println("arr1 origin:", arr1)
  fmt.Println("\r\nshellSort1 sorted:", shellSort1(arr1))
  fmt.Println("arr1. cost:", time.Since(time1))

  time2 := time.Now()
  var arr2 = []int{33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431}
  fmt.Println("arr2 origin:", arr2)
  fmt.Println("\r\nshellSort2 sorted:", shellSort1(arr2))
  fmt.Println("arr2. cost:", time.Since(time2))
}

/**
jarry@jarrys-MacBook-Pro shellsort %
jarry@jarrys-MacBook-Pro shellsort % go run shell_sort.go
arr1 origin: [7 11 -9 10 -12 13 8]
gap= 3  j= 0 arr: [7 11 -9 10 -12 13 8]
gap= 3  j= 1 arr: [7 11 -9 10 -12 13 8]
gap= 3  j= 2 arr: [7 11 -9 10 -12 13 8]
gap= 3  j= 3 arr: [7 11 -9 10 -12 13 8]
gap= 3  j= 4 arr: [7 11 -9 10 -12 13 8]
gap= 3  j= 5 arr: [7 -12 -9 10 11 13 8]
gap= 3  j= 6 arr: [7 -12 -9 10 11 13 8]
gap= 1  j= 0 arr: [7 -12 -9 8 11 13 10]
gap= 1  j= 1 arr: [7 -12 -9 8 11 13 10]
gap= 1  j= 2 arr: [-12 7 -9 8 11 13 10]
gap= 1  j= 3 arr: [-12 -9 7 8 11 13 10]
gap= 1  j= 4 arr: [-12 -9 7 8 11 13 10]
gap= 1  j= 5 arr: [-12 -9 7 8 11 13 10]
gap= 1  j= 6 arr: [-12 -9 7 8 11 13 10]

shellSort1 sorted: [-12 -9 7 8 10 11 13]
arr1. cost: 81.404µs
arr2 origin: [33 4 15 43 323454 -7 10 1235 200 87431]
gap= 5  j= 0 arr: [33 4 15 43 323454 -7 10 1235 200 87431]
gap= 5  j= 1 arr: [33 4 15 43 323454 -7 10 1235 200 87431]
gap= 5  j= 2 arr: [33 4 15 43 323454 -7 10 1235 200 87431]
gap= 5  j= 3 arr: [33 4 15 43 323454 -7 10 1235 200 87431]
gap= 5  j= 4 arr: [33 4 15 43 323454 -7 10 1235 200 87431]
gap= 5  j= 5 arr: [33 4 15 43 323454 -7 10 1235 200 87431]
gap= 5  j= 6 arr: [-7 4 15 43 323454 33 10 1235 200 87431]
gap= 5  j= 7 arr: [-7 4 15 43 323454 33 10 1235 200 87431]
gap= 5  j= 8 arr: [-7 4 15 43 323454 33 10 1235 200 87431]
gap= 5  j= 9 arr: [-7 4 15 43 323454 33 10 1235 200 87431]
gap= 2  j= 0 arr: [-7 4 15 43 87431 33 10 1235 200 323454]
gap= 2  j= 1 arr: [-7 4 15 43 87431 33 10 1235 200 323454]
gap= 2  j= 2 arr: [-7 4 15 43 87431 33 10 1235 200 323454]
gap= 2  j= 3 arr: [-7 4 15 43 87431 33 10 1235 200 323454]
gap= 2  j= 4 arr: [-7 4 15 43 87431 33 10 1235 200 323454]
gap= 2  j= 5 arr: [-7 4 15 43 87431 33 10 1235 200 323454]
gap= 2  j= 6 arr: [-7 4 15 33 87431 43 10 1235 200 323454]
gap= 2  j= 7 arr: [-7 4 10 33 15 43 87431 1235 200 323454]
gap= 2  j= 8 arr: [-7 4 10 33 15 43 87431 1235 200 323454]
gap= 2  j= 9 arr: [-7 4 10 33 15 43 200 1235 87431 323454]
gap= 1  j= 0 arr: [-7 4 10 33 15 43 200 1235 87431 323454]
gap= 1  j= 1 arr: [-7 4 10 33 15 43 200 1235 87431 323454]
gap= 1  j= 2 arr: [-7 4 10 33 15 43 200 1235 87431 323454]
gap= 1  j= 3 arr: [-7 4 10 33 15 43 200 1235 87431 323454]
gap= 1  j= 4 arr: [-7 4 10 33 15 43 200 1235 87431 323454]
gap= 1  j= 5 arr: [-7 4 10 15 33 43 200 1235 87431 323454]
gap= 1  j= 6 arr: [-7 4 10 15 33 43 200 1235 87431 323454]
gap= 1  j= 7 arr: [-7 4 10 15 33 43 200 1235 87431 323454]
gap= 1  j= 8 arr: [-7 4 10 15 33 43 200 1235 87431 323454]
gap= 1  j= 9 arr: [-7 4 10 15 33 43 200 1235 87431 323454]

shellSort2 sorted: [-7 4 10 15 33 43 200 1235 87431 323454]
arr2. cost: 218.198µs
*/
