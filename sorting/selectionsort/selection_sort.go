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

// 标准版
func selectionSort1(arr []int) []int {
  var min = arr[0]
  var minIdx = 0
  var tmp = -1
  var arrLen = len(arr)
  for i := 0; i < arrLen-1; i++ {
    min = arr[i]
    minIdx = i
    var j = i + 1
    for ; j < arrLen; j++ {
      // 从待排序列表中找到最小值和位置，用作交换
      if arr[j] < min {
        min = arr[j]
        minIdx = j
      }
    }
    fmt.Println("i=", i, " j=", j, "min=", min, "minIdx=", minIdx, "arr[]=", arr)
    // 将待排序里最小值交换到已排序最后面
    if minIdx != i {
      tmp = arr[i]
      arr[i] = min
      arr[minIdx] = tmp
    }
  }

  return arr
}

// 新建数组版，无需交换
func selectionSort2(arr []int) []int {

  var min = arr[0]
  var minIdx = 0
  var arrLen = len(arr)
  var newArr = make([]int, 0)
  for i := 0; i < arrLen; i++ {
    min = arr[i]
    minIdx = i
    var j = i + 1
    for ; j < arrLen; j++ {
      // 找到并记录下最小值和位置
      if arr[j] < min {
        min = arr[j]
        minIdx = j
      }
    }
    fmt.Println("i=", i, " j=", j, "min=", min, "minIdx=", minIdx, "arr[]=", arr)
    // 将待排序里最小值添加到新数组中去
    newArr = append(newArr, min)
    // 原数组中删除对应的项
    arr = append(arr[:minIdx], arr[minIdx+1:]...)
    arrLen--
    i--
  }

  return newArr
}

func main() {
  time1 := time.Now()
  var arr1 = []int{7, 11, -9, 10, -12, 13, 8}
  fmt.Println("selection1 origin:", arr1)
  fmt.Println("\r\nselectionSort1 sorted:", selectionSort1(arr1))
  fmt.Println("selection1. cost:", time.Since(time1))

  time2 := time.Now()
  var arr2 = []int{7, 11, -9, 10, -12, 13, 8}
  fmt.Println("selection2 origin:", arr2)
  fmt.Println("\r\nselectionSort2 sorted:", selectionSort2(arr2))
  fmt.Println("selection2. cost:", time.Since(time2))
}

/**
jarry@jarrys-MacBook-Pro selectionsort % go run selection_sort.go
selection1 origin: [7 11 -9 10 -12 13 8]
i= 0  j= 7 min= -12 minIdx= 4 arr[]= [7 11 -9 10 -12 13 8]
i= 1  j= 7 min= -9 minIdx= 2 arr[]= [-12 11 -9 10 7 13 8]
i= 2  j= 7 min= 7 minIdx= 4 arr[]= [-12 -9 11 10 7 13 8]
i= 3  j= 7 min= 8 minIdx= 6 arr[]= [-12 -9 7 10 11 13 8]
i= 4  j= 7 min= 10 minIdx= 6 arr[]= [-12 -9 7 8 11 13 10]
i= 5  j= 7 min= 11 minIdx= 6 arr[]= [-12 -9 7 8 10 13 11]

selectionSort1 sorted: [-12 -9 7 8 10 11 13]
selection1. cost: 61.625µs
selection2 origin: [-12 -9 7 8 10 11 13]
i= 0  j= 7 min= -12 minIdx= 4 arr[]= [7 11 -9 10 -12 13 8]
i= 0  j= 6 min= -9 minIdx= 2 arr[]= [7 11 -9 10 13 8]
i= 0  j= 5 min= 7 minIdx= 0 arr[]= [7 11 10 13 8]
i= 0  j= 4 min= 8 minIdx= 3 arr[]= [11 10 13 8]
i= 0  j= 3 min= 10 minIdx= 1 arr[]= [11 10 13]
i= 0  j= 2 min= 11 minIdx= 0 arr[]= [11 13]
i= 0  j= 1 min= 13 minIdx= 0 arr[]= [13]

selectionSort2 sorted: [-12 -9 7 8 10 11 13]
selection2. cost: 24.798µs
*/
