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

// 基数排序，从高到低逐位排序，基于桶排序

func radixSort(arr []int) []int {
  var amount = 10
  maxValue := max(arr)
  exponent := pow(amount, getNumberOfDigits(maxValue)-1)

  bucketSortMSD(arr, exponent)
  return arr
}

func bucketSortMSD(arr []int, exponent int) []int {
  var amount = 10
  if exponent < 1 {
    return arr
  }

  if len(arr) <= 1 {
    return arr
  }
  fmt.Println("origin arr:", arr, "exponent: ", exponent)

  buckets := [][]int{}
  minValue := getMinValue(arr, exponent)

  // 支持负数
  offset := 0
  if minValue < 0 {
    offset = 0 - minValue
  }

  // 填充空桶
  for i := 0; i < (amount + offset); i++ {
    buckets = append(buckets, []int{})
  }

  // 获取数组项指定数位的值，放入到对应桶中，桶的下标即顺序
  for idx, num := range arr {
    bucketIdx := getDigit(arr, idx, exponent) + offset
    buckets[bucketIdx] = append(buckets[bucketIdx], num)
  }
  fmt.Println("append to buckets: ", buckets)

  sortedIdx := 0
  for _, bucket := range buckets {
    if len(bucket) <= 0 {
      continue
    }
    // 递归遍历所有的桶，由里而外逐个桶进行排序
    sortedBucket := bucketSortMSD(bucket, exponent/amount)
    // 把各个桶里的值按顺序赋给原数组
    for _, num := range sortedBucket {
      arr[sortedIdx] = num
      fmt.Println("bucket:", bucket, "sortedBucket: ", sortedBucket, "sortedIdx:", sortedIdx, "set arr: ", arr)
      sortedIdx += 1
    }
  }
  fmt.Println("exponent: ", exponent, "sorted arr: ", arr)

  return arr
}

// 获取数字位数
func getNumberOfDigits(num int) int {
  numberOfDigits := 0
  for num > 0 {
    numberOfDigits += 1
    num /= 10
  }
  return numberOfDigits
}

// 获取绝对值
func abs(value int) int {
  if value < 0 {
    return -value
  }
  return value
}

// 获取数组最大值
func max(arr []int) int {
  maxValue := arr[0]
  for i := 1; i < len(arr); i++ {
    if arr[i] > maxValue {
      maxValue = arr[i]
    }
  }
  return maxValue
}

// 计算数字次幂
func pow(a int, power int) int {
  result := 1
  for i := 0; i < power; i++ {
    result *= a
  }
  return result
}

// 获取数组项指定数位的最小值
func getMinValue(arr []int, exponent int) int {
  minValue := getDigit(arr, 0, exponent)
  for i := 1; i < len(arr); i++ {
    element := getDigit(arr, i, exponent)
    if minValue > element {
      minValue = element
    }
  }
  return minValue
}

// 获取数字指定数位的值，超出数位补0，负数返回负数
// 如: 1024, 百位: 100 => 返回 0
// 如: -2048, 千位: 1000 => 返回 -2
func getDigit(arr []int, idx int, exponent int) int {
  element := arr[idx]
  digit := abs(element) / exponent % 10
  if element < 0 {
    return -digit
  }
  return digit
}

// test
func main() {
  // fmt.Println("radix sort1:")
  // time1 := time.Now()
  // data1 := []int{33, 4, 115, 143}
  // fmt.Println(radixSort(data1[:]))
  // fmt.Println("sort1 end. cost:", time.Since(time1))

  fmt.Println("radix sort2:")
  time2 := time.Now()
  data2 := []int{33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431}
  fmt.Println(radixSort(data2[:]))
  fmt.Println("sort2 end. cost:", time.Since(time2))
}

/*
jarry@jarrys-MacBook-Pro radixsort % go version
go version go1.19.5 darwin/amd64
jarry@jarrys-MacBook-Pro radixsort % go run radix_sort_msd.go
radix sort1:
origin arr: [33 4 115 143] exponent:  100
append to buckets:  [[33 4] [115 143] [] [] [] [] [] [] [] []]
origin arr: [33 4] exponent:  10
append to buckets:  [[4] [] [] [33] [] [] [] [] [] []]
jarry@jarrys-MacBook-Pro radixsort % go run radix_sort_msd.go
jarry@jarrys-MacBook-Pro radixsort % go run radix_sort_msd.go
radix sort1:
origin arr: [33 4 115 143] exponent:  100
append to buckets:  [[33 4] [115 143] [] [] [] [] [] [] [] []]
origin arr: [33 4] exponent:  10
append to buckets:  [[4] [] [] [33] [] [] [] [] [] []]
bucket: [4] sortedBucket:  [4] sortedIdx: 0 set arr:  [4 4]
bucket: [33] sortedBucket:  [33] sortedIdx: 1 set arr:  [4 33]
exponent:  10 sorted arr:  [4 33]
bucket: [4 33] sortedBucket:  [4 33] sortedIdx: 0 set arr:  [4 4 115 143]
bucket: [4 33] sortedBucket:  [4 33] sortedIdx: 1 set arr:  [4 33 115 143]
origin arr: [115 143] exponent:  10
append to buckets:  [[] [115] [] [] [143] [] [] [] [] []]
bucket: [115] sortedBucket:  [115] sortedIdx: 0 set arr:  [115 143]
bucket: [143] sortedBucket:  [143] sortedIdx: 1 set arr:  [115 143]
exponent:  10 sorted arr:  [115 143]
bucket: [115 143] sortedBucket:  [115 143] sortedIdx: 2 set arr:  [4 33 115 143]
bucket: [115 143] sortedBucket:  [115 143] sortedIdx: 3 set arr:  [4 33 115 143]
exponent:  100 sorted arr:  [4 33 115 143]
[4 33 115 143]
sort1 end. cost: 118.781µs
radix sort2:
origin arr: [33 -4 15 43 -323454 7 10 1235 200 87431] exponent:  10000
append to buckets:  [[-323454] [] [33 -4 15 43 7 10 1235 200] [] [] [] [] [] [] [] [87431] []]
bucket: [-323454] sortedBucket:  [-323454] sortedIdx: 0 set arr:  [-323454 -4 15 43 -323454 7 10 1235 200 87431]
origin arr: [33 -4 15 43 7 10 1235 200] exponent:  1000
append to buckets:  [[33 -4 15 43 7 10 200] [1235] [] [] [] [] [] [] [] []]
origin arr: [33 -4 15 43 7 10 200] exponent:  100
append to buckets:  [[33 -4 15 43 7 10] [] [200] [] [] [] [] [] [] []]
origin arr: [33 -4 15 43 7 10] exponent:  10
append to buckets:  [[-4 7] [15 10] [] [33] [43] [] [] [] [] []]
origin arr: [-4 7] exponent:  1
append to buckets:  [[-4] [] [] [] [] [] [] [] [] [] [] [7] [] []]
bucket: [-4] sortedBucket:  [-4] sortedIdx: 0 set arr:  [-4 7]
bucket: [7] sortedBucket:  [7] sortedIdx: 1 set arr:  [-4 7]
exponent:  1 sorted arr:  [-4 7]
bucket: [-4 7] sortedBucket:  [-4 7] sortedIdx: 0 set arr:  [-4 -4 15 43 7 10]
bucket: [-4 7] sortedBucket:  [-4 7] sortedIdx: 1 set arr:  [-4 7 15 43 7 10]
origin arr: [15 10] exponent:  1
append to buckets:  [[10] [] [] [] [] [15] [] [] [] []]
bucket: [10] sortedBucket:  [10] sortedIdx: 0 set arr:  [10 10]
bucket: [15] sortedBucket:  [15] sortedIdx: 1 set arr:  [10 15]
exponent:  1 sorted arr:  [10 15]
bucket: [10 15] sortedBucket:  [10 15] sortedIdx: 2 set arr:  [-4 7 10 43 7 10]
bucket: [10 15] sortedBucket:  [10 15] sortedIdx: 3 set arr:  [-4 7 10 15 7 10]
bucket: [33] sortedBucket:  [33] sortedIdx: 4 set arr:  [-4 7 10 15 33 10]
bucket: [43] sortedBucket:  [43] sortedIdx: 5 set arr:  [-4 7 10 15 33 43]
exponent:  10 sorted arr:  [-4 7 10 15 33 43]
bucket: [-4 7 10 15 33 43] sortedBucket:  [-4 7 10 15 33 43] sortedIdx: 0 set arr:  [-4 -4 15 43 7 10 200]
bucket: [-4 7 10 15 33 43] sortedBucket:  [-4 7 10 15 33 43] sortedIdx: 1 set arr:  [-4 7 15 43 7 10 200]
bucket: [-4 7 10 15 33 43] sortedBucket:  [-4 7 10 15 33 43] sortedIdx: 2 set arr:  [-4 7 10 43 7 10 200]
bucket: [-4 7 10 15 33 43] sortedBucket:  [-4 7 10 15 33 43] sortedIdx: 3 set arr:  [-4 7 10 15 7 10 200]
bucket: [-4 7 10 15 33 43] sortedBucket:  [-4 7 10 15 33 43] sortedIdx: 4 set arr:  [-4 7 10 15 33 10 200]
bucket: [-4 7 10 15 33 43] sortedBucket:  [-4 7 10 15 33 43] sortedIdx: 5 set arr:  [-4 7 10 15 33 43 200]
bucket: [200] sortedBucket:  [200] sortedIdx: 6 set arr:  [-4 7 10 15 33 43 200]
exponent:  100 sorted arr:  [-4 7 10 15 33 43 200]
bucket: [-4 7 10 15 33 43 200] sortedBucket:  [-4 7 10 15 33 43 200] sortedIdx: 0 set arr:  [-4 -4 15 43 7 10 1235 200]
bucket: [-4 7 10 15 33 43 200] sortedBucket:  [-4 7 10 15 33 43 200] sortedIdx: 1 set arr:  [-4 7 15 43 7 10 1235 200]
bucket: [-4 7 10 15 33 43 200] sortedBucket:  [-4 7 10 15 33 43 200] sortedIdx: 2 set arr:  [-4 7 10 43 7 10 1235 200]
bucket: [-4 7 10 15 33 43 200] sortedBucket:  [-4 7 10 15 33 43 200] sortedIdx: 3 set arr:  [-4 7 10 15 7 10 1235 200]
bucket: [-4 7 10 15 33 43 200] sortedBucket:  [-4 7 10 15 33 43 200] sortedIdx: 4 set arr:  [-4 7 10 15 33 10 1235 200]
bucket: [-4 7 10 15 33 43 200] sortedBucket:  [-4 7 10 15 33 43 200] sortedIdx: 5 set arr:  [-4 7 10 15 33 43 1235 200]
bucket: [-4 7 10 15 33 43 200] sortedBucket:  [-4 7 10 15 33 43 200] sortedIdx: 6 set arr:  [-4 7 10 15 33 43 200 200]
bucket: [1235] sortedBucket:  [1235] sortedIdx: 7 set arr:  [-4 7 10 15 33 43 200 1235]
exponent:  1000 sorted arr:  [-4 7 10 15 33 43 200 1235]
bucket: [-4 7 10 15 33 43 200 1235] sortedBucket:  [-4 7 10 15 33 43 200 1235] sortedIdx: 1 set arr:  [-323454 -4 15 43 -323454 7 10 1235 200 87431]
bucket: [-4 7 10 15 33 43 200 1235] sortedBucket:  [-4 7 10 15 33 43 200 1235] sortedIdx: 2 set arr:  [-323454 -4 7 43 -323454 7 10 1235 200 87431]
bucket: [-4 7 10 15 33 43 200 1235] sortedBucket:  [-4 7 10 15 33 43 200 1235] sortedIdx: 3 set arr:  [-323454 -4 7 10 -323454 7 10 1235 200 87431]
bucket: [-4 7 10 15 33 43 200 1235] sortedBucket:  [-4 7 10 15 33 43 200 1235] sortedIdx: 4 set arr:  [-323454 -4 7 10 15 7 10 1235 200 87431]
bucket: [-4 7 10 15 33 43 200 1235] sortedBucket:  [-4 7 10 15 33 43 200 1235] sortedIdx: 5 set arr:  [-323454 -4 7 10 15 33 10 1235 200 87431]
bucket: [-4 7 10 15 33 43 200 1235] sortedBucket:  [-4 7 10 15 33 43 200 1235] sortedIdx: 6 set arr:  [-323454 -4 7 10 15 33 43 1235 200 87431]
bucket: [-4 7 10 15 33 43 200 1235] sortedBucket:  [-4 7 10 15 33 43 200 1235] sortedIdx: 7 set arr:  [-323454 -4 7 10 15 33 43 200 200 87431]
bucket: [-4 7 10 15 33 43 200 1235] sortedBucket:  [-4 7 10 15 33 43 200 1235] sortedIdx: 8 set arr:  [-323454 -4 7 10 15 33 43 200 1235 87431]
bucket: [87431] sortedBucket:  [87431] sortedIdx: 9 set arr:  [-323454 -4 7 10 15 33 43 200 1235 87431]
exponent:  10000 sorted arr:  [-323454 -4 7 10 15 33 43 200 1235 87431]
[-323454 -4 7 10 15 33 43 200 1235 87431]
sort2 end. cost: 213.955µs
*/
