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

// 选择排序优化版，同时找出最小和最大值进行交换，可减少1半遍历
// 把数列分为前中后三个区间，分别代表最小已排序、中间待排序以及最大已排序区间
// 遍历中间待排序同时找最大和最小值，分别交换到最小值区间和最大值区间
func selectionSort(arr []int) []int {

  var minValue int
  var maxValue int
  var minIdx int
  var maxIdx int
  var minListIdx int
  var maxListIdx int

  var arrLen = len(arr)
  for i := 0; i < arrLen-1; i++ {
    // 待排序里面初始最小值和下标
    minIdx = i
    minValue = arr[minIdx]
    // 待排序里面初始最大值和下标
    maxIdx = i
    maxValue = arr[maxIdx]
    // 最小和最大序列里最新待交换的下标
    // 最小序列的下标从0开始，自前往后递加
    minListIdx = minIdx
    // 最大序列的下标从数组最后1位开始，自后往前递减
    maxListIdx = arrLen - 1 - i
    // 如果最小和最大下标相同，说明只剩下1个数字，则终止循环
    if minListIdx == maxListIdx {
      break
    }

    // 逐一遍历待排序区间，找出最小和最大值
    // 待排序区间在最小值序列和和最大值序列之间
    // 待比较区间的下标j从i+1开始，到最大已排序前结束
    for j := i + 1; j < arrLen-i; j++ {
      // 从待排序列表中分别找到最小值和最大值
      if arr[j] < minValue {
        minIdx = j
        minValue = arr[minIdx]
      } else if arr[j] > maxValue {
        maxIdx = j
        maxValue = arr[maxIdx]
      }
    }

    // 如果最小值等于最小序列待交换的值，且最大值等于最大序列里待交换的值，则跳过
    if arr[minIdx] == arr[minListIdx] && arr[maxIdx] == arr[maxListIdx] {
      continue
    }
    fmt.Println("minValue=", minValue, " maxValue=", maxValue, " minIdx=", minIdx, " maxIdx=", maxIdx, " minListIdx=", minListIdx, " maxListIdx=", maxListIdx)
    // 先交换小值，再交换大值
    arr[minListIdx], arr[minIdx] = arr[minIdx], arr[minListIdx]
    // 如果最大值被交换了，则需要更新最大值的下标
    if arr[minIdx] == maxValue {
      maxIdx = minIdx
    }
    arr[maxListIdx], arr[maxIdx] = arr[maxIdx], arr[maxListIdx]
  }

  return arr
}

func main() {
  time1 := time.Now()
  var arr1 = []int{7, 11, -9, 10, -12, 13, 8}
  fmt.Println("arr1 origin:", arr1)
  fmt.Println("\r\narr1 sorted:", selectionSort(arr1))
  fmt.Println("arr1. cost:", time.Since(time1))

  time2 := time.Now()
  var arr2 = []int{7, 11, 121, -9, 545, 110, -210, 1245, -132, 192, 153, 19, 8}
  fmt.Println("arr2 origin:", arr2)
  fmt.Println("\r\narr2 sorted:", selectionSort(arr2))
  fmt.Println("arr2. cost:", time.Since(time2))

  time3 := time.Now()
  var arr3 = []int{57, 311, 131, -9, 415, 10, 1330, 1245, -12, 1942, 123, 129, 80}
  fmt.Println("arr3 origin:", arr3)
  fmt.Println("\r\narr3 sorted:", selectionSort(arr3))
  fmt.Println("arr3. cost:", time.Since(time3))
}

/**
jarry@jarrys-MacBook-Pro selectionsort % go run selection_sort2.go
arr1 origin: [7 11 -9 10 -12 13 8]
minValue= -12  maxValue= 13  minIdx= 4  maxIdx= 5  minListIdx= 0  maxListIdx= 6
minValue= -9  maxValue= 11  minIdx= 2  maxIdx= 1  minListIdx= 1  maxListIdx= 5
minValue= 7  maxValue= 10  minIdx= 4  maxIdx= 3  minListIdx= 2  maxListIdx= 4

arr1 sorted: [-12 -9 7 8 10 11 13]
arr1. cost: 55.112µs
arr2 origin: [7 11 121 -9 545 110 -210 1245 -132 192 153 19 8]
minValue= -210  maxValue= 1245  minIdx= 6  maxIdx= 7  minListIdx= 0  maxListIdx= 12
minValue= -132  maxValue= 545  minIdx= 8  maxIdx= 4  minListIdx= 1  maxListIdx= 11
minValue= -9  maxValue= 192  minIdx= 3  maxIdx= 9  minListIdx= 2  maxListIdx= 10
minValue= 7  maxValue= 153  minIdx= 6  maxIdx= 9  minListIdx= 3  maxListIdx= 9
minValue= 8  maxValue= 121  minIdx= 7  maxIdx= 6  minListIdx= 4  maxListIdx= 8
minValue= 11  maxValue= 110  minIdx= 6  maxIdx= 5  minListIdx= 5  maxListIdx= 7

arr2 sorted: [-210 -132 -9 7 8 11 19 110 121 153 192 545 1245]
arr2. cost: 23.548µs
arr3 origin: [57 311 131 -9 415 10 1330 1245 -12 1942 123 129 80]
minValue= -12  maxValue= 1942  minIdx= 8  maxIdx= 9  minListIdx= 0  maxListIdx= 12
minValue= -9  maxValue= 1330  minIdx= 3  maxIdx= 6  minListIdx= 1  maxListIdx= 11
minValue= 10  maxValue= 1245  minIdx= 5  maxIdx= 7  minListIdx= 2  maxListIdx= 10
minValue= 57  maxValue= 415  minIdx= 8  maxIdx= 4  minListIdx= 3  maxListIdx= 9
minValue= 123  maxValue= 131  minIdx= 7  maxIdx= 5  minListIdx= 5  maxListIdx= 7

arr3 sorted: [-12 -9 10 57 80 123 129 131 311 415 1245 1330 1942]
arr3. cost: 45.676µs
*/
