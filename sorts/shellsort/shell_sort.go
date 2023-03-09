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
      // 分组按照插入排序
      for j >= gap && current < arr[j-gap] {
        fmt.Println("gap=", gap, "i=", i, " j-gap=", j-gap, " j=", j)
        arr[j] = arr[j-gap]
        j -= gap
      }
      // 交换当前项
      arr[j] = current
      // 调整步长为1/2
    }
    gap = (gap / 2)
  }
  return arr
}

// 2. 希尔排序标准版，基于插入排序进行分组排序，步长按1/2缩减。
func shellSort2(arr []int) []int {
  var arrLen int = len(arr)
  //  设置分组间隔
  var gap int = 1
  // 初始步长按3倍递增，小于1/3数组长度
  for gap < (arrLen / 3) {
    gap = gap*3 + 1
  }
  // 如果间隔大于0，则表示还可以继续分
  for gap > 0 {
    for i := gap; i < arrLen; i++ {
      var current = arr[i]
      var j = i - gap
      // 对子序列按照插入排序
      for ; j >= 0 && arr[j] > current; j -= gap {
        fmt.Println("gap=", gap, "i=", i, " j=", j, " j+gap=", (j + gap))
        arr[j+gap] = arr[j]
      }
      arr[j+gap] = current
    }
    // 步长按3倍缩减
    gap = (gap / 3)
  }
  return arr
}

func main() {
  time1 := time.Now()
  var arr1 = []int{33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431}
  fmt.Println("arr1 origin:", arr1)
  fmt.Println("\r\nshellSort1 sorted:", shellSort1(arr1))
  fmt.Println("arr1. cost:", time.Since(time1))

  time2 := time.Now()
  var arr2 = []int{33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431}
  fmt.Println("arr2 origin:", arr2)
  fmt.Println("\r\nshellSort2 sorted:", shellSort2(arr2))
  fmt.Println("arr2. cost:", time.Since(time2))
}

/**
jarry@jarrys-MacBook-Pro shellsort %
jarry@jarrys-MacBook-Pro shellsort % go run shell_sort.go
arr1 origin: [33 4 15 43 323454 -7 105 1235 200 87431]
gap= 5 i= 5  j-gap= 0  j= 5
gap= 5 i= 9  j-gap= 4  j= 9
gap= 2 i= 5  j-gap= 3  j= 5
gap= 2 i= 6  j-gap= 4  j= 6
gap= 2 i= 8  j-gap= 6  j= 8
gap= 1 i= 5  j-gap= 4  j= 5

shellSort1 sorted: [-7 4 15 33 43 105 200 1235 87431 323454]
arr1. cost: 64.106µs
arr2 origin: [33 4 15 43 323454 -7 105 1235 200 87431]
gap= 4 i= 5  j= 1  j+gap= 5
gap= 4 i= 8  j= 4  j+gap= 8
gap= 1 i= 1  j= 0  j+gap= 1
gap= 1 i= 2  j= 1  j+gap= 2
gap= 1 i= 5  j= 4  j+gap= 5
gap= 1 i= 5  j= 3  j+gap= 4
gap= 1 i= 5  j= 2  j+gap= 3
gap= 1 i= 5  j= 1  j+gap= 2
gap= 1 i= 6  j= 5  j+gap= 6
gap= 1 i= 9  j= 8  j+gap= 9

shellSort2 sorted: [-7 4 15 33 43 105 200 1235 87431 323454]
arr2. cost: 25.913µs
*/
