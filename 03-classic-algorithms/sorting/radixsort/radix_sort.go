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

// 1. 基数排序简版，基于计数排序的基础上，按数字的每个位置来排序
func countingSort(arr []int, exponent int) []int {
  var arrLen = len(arr)
  var amount = 10
  var countList = make([]int, amount)

  for i := 0; i < arrLen; i++ {
    var item = arr[i]
    // 根据基数取得数位上的值，并给对应计数数组加1
    var idx = (item / exponent) % amount
    countList[idx] += 1
  }

  // 后面的位数为前面的累加之和
  for i := 1; i < amount; i++ {
    countList[i] += countList[i-1]
  }
  fmt.Println("radixSort1 countList:", countList)

  var sortedList = make([]int, arrLen)
  // 补齐位数，根据计数数组按顺序取得排序内容
  for i := arrLen - 1; i >= 0; i-- {
    var idx = (arr[i] / exponent) % amount
    sortedList[countList[idx]-1] = arr[i]
    countList[idx] -= 1
  }

  // 根据新顺序重新调整原数组
  for i := 0; i < arrLen; i++ {
    arr[i] = sortedList[i]
  }

  return sortedList
}

func radixSort1(arr []int) []int {
  max := arr[0]
  for i := 1; i < len(arr); i++ {
    if arr[i] > max {
      max = arr[i]
    }
  }
  // 根据最大值，逐个按进位(基数)来应用排序，基数步长为10。
  for exponent := 1; (max / exponent) > 0; exponent *= 10 {
    countingSort(arr, exponent)
  }
  return arr
}

// 2. 基数排序LSD版，计算最小值，基于计数排序实现
func radixSort2(arr []int) []int {
  var arrLen = len(arr)
  // 基数exponent按10进位，amount为10
  var amount = 10
  var sortedList = make([]int, arrLen)
  var max = arr[0]
  for i := 0; i < arrLen; i++ {
    if arr[i] > max {
      max = arr[i]
    }
  }
  var min = arr[0]
  for i := 0; i < arrLen; i++ {
    if arr[i] < min {
      min = arr[i]
    }
  }

  // 根据基数求得当前项目对应位置的数值，并给对应计数数组位置加1
  // 按最大值补齐数位，基数exponent按10进位
  for exponent := 1; ((max - min) / exponent) > 0; exponent *= amount {

    // 计数数组，长度为10，0-9一共10个数字
    countList := make([]int, amount)
    // 根据基数得到当前位数，并给计数数组对应位置加1
    for i := 0; i < arrLen; i++ {
      var item = arr[i] - min
      var idx = (item / exponent) % amount
      countList[idx] += 1
    }

    // 计数排序构建，自前往后，逐个将上一项的值存入当前项
    for i := 1; i < amount; i++ {
      countList[i] += countList[i-1]
    }

    fmt.Println("radixSort2 -> countList:", countList)

    // 根据计数数组按顺序取出排序内容
    for i := arrLen - 1; i >= 0; i-- {
      item := arr[i] - min
      var idx = (item / exponent) % amount
      sortedList[countList[idx]-1] = arr[i]
      countList[idx] -= 1
    }

    // 将新顺序赋值给原数组
    for i := 0; i < arrLen; i++ {
      arr[i] = sortedList[i]
    }
  }

  return arr
}

// test
func main() {
  fmt.Println("radix sort1:")
  time1 := time.Now()
  data1 := []int{33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431}
  fmt.Println(radixSort1(data1[:]))
  fmt.Println("sort1 end. cost:", time.Since(time1))

  fmt.Println("radix sort2:")
  time2 := time.Now()
  data2 := []int{33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431}
  fmt.Println(radixSort2(data2[:]))
  fmt.Println("sort2 end. cost:", time.Since(time2))
}

/*
jarry@jarrys-MacBook-Pro radixsort % go version
go version go1.19.5 darwin/amd64
jarry@jarrys-MacBook-Pro radixsort % go run radix_sort.go
radix sort1:
radixSort1 countList: [2 3 3 5 7 9 9 10 10 10]
radixSort1 countList: [3 5 5 8 9 10 10 10 10 10]
radixSort1 countList: [6 6 8 8 10 10 10 10 10 10]
radixSort1 countList: [7 8 8 9 9 9 9 10 10 10]
radixSort1 countList: [8 8 9 9 9 9 9 9 10 10]
radixSort1 countList: [9 9 9 10 10 10 10 10 10 10]
[4 7 10 15 33 43 200 1235 87431 323454]
sort1 end. cost: 40.616µs
radix sort2:
radixSort2 -> countList: [2 3 3 3 5 6 6 8 8 10]
radixSort2 -> countList: [1 1 1 1 1 3 6 6 9 10]
radixSort2 -> countList: [1 1 1 1 7 7 9 9 10 10]
radixSort2 -> countList: [2 2 2 9 10 10 10 10 10 10]
radixSort2 -> countList: [1 2 10 10 10 10 10 10 10 10]
radixSort2 -> countList: [1 1 1 9 10 10 10 10 10 10]
[-323454 -4 7 10 15 33 43 200 1235 87431]
sort2 end. cost: 20.759µs
*/
