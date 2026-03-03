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

/**
 * 计数排序标准版
 */
func countingSort1(arr []int) []int {
  // 计算最大值与最小值
  var max = arr[0]
  var min = arr[0]
  var arrLen = len(arr)
  for i := 1; i < arrLen; i++ {
    if arr[i] > max {
      max = arr[i]
    }
    if arr[i] < min {
      min = arr[i]
    }
  }

  // 计数数组的长度在最大和最小差值+1
  var countList = make([]int, max-min+1)
  for i := 0; i < arrLen; i++ {
    // 把下标减去min值，以便减少计数数组的长度，最小项的坐标为0，以此递增
    var idx = arr[i] - min
    // 根据待排序项给对应下标的位置标记加1
    countList[idx] += 1
  }

  var idx = 0
  // 遍历计数数组，覆盖原数组
  for i := 0; i < len(countList); i++ {
    // 下标若大于0，则取出来，如果相同则取多次
    val := countList[i]
    for j := 0; j < val; j++ {
      if val > 0 {
        // 取出的值要+min还原
        arr[idx] = i + min
        idx++
      }
    }
  }

  return arr
}

// 计数排序2
func countingSort2(arr []int) []int {
  var max = arr[0]
  var min = arr[0]
  arrLen := len(arr)
  for i := 1; i < arrLen; i++ {
    if arr[i] > max {
      max = arr[i]
    }
    if arr[i] < min {
      min = arr[i]
    }
  }
  var output = make([]int, arrLen)
  var countList = make([]int, max-min+1)

  // 按每个数组项出现次数计数，从最小项的下标为0
  for _, item := range arr {
    // 当前前减去最小项得到下标，最后取出数据要还原
    var idx = item - min
    countList[idx]++
  }

  // fmt.Println("countList after count: ", countList)
  // 把上一项的值个数存入到当前项，相当于排序
  for i := 1; i < len(countList); i++ {
    countList[i] += countList[i-1]
  }
  // fmt.Println("countList after sort: ", countList)

  // 按位置还原数据，下一个索引记录了上一个的坐标值
  for i := 0; i < arrLen; i++ {
    // 当前项来自原始数组减去-min
    item := arr[i] - min
    // 根据当前项从计数数组里找到目标位置
    idx := countList[item] - 1
    // 输出数据加上min进行还原
    output[idx] = item + min
    // 取出一项计数则减少一个
    countList[item] -= 1

    fmt.Println("[item, idx, countList[idx], output] :", item, idx, countList[idx], output)
  }

  return output
}

// test
func main() {
  fmt.Println("counting sort1:")
  time1 := time.Now()
  data1 := []int{20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80}
  fmt.Println(countingSort1(data1[:]))
  fmt.Println("sort1 end. cost:", time.Since(time1))

  fmt.Println("counting sort2:")
  time2 := time.Now()
  data2 := []int{20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80}
  fmt.Println(countingSort2(data2[:]))
  fmt.Println("sort2 end. cost:", time.Since(time2))
}

/*
jarry@jarrys-MacBook-Pro countingsort % go version
go version go1.19.5 darwin/amd64
jarry@jarrys-MacBook-Pro countingsort % go run counting_sort.go
counting sort1:
[-10 0 6 9 9 11 11 13 15 20 30 80]
sort1 end. cost: 28.526µs
counting sort2:
[item, idx, countList[idx], output] : 30 9 1 [0 0 0 0 0 0 0 0 0 20 0 0]
[item, idx, countList[idx], output] : 21 6 1 [0 0 0 0 0 0 11 0 0 20 0 0]
[item, idx, countList[idx], output] : 10 1 1 [0 0 0 0 0 0 11 0 0 20 0 0]
[item, idx, countList[idx], output] : 0 0 0 [-10 0 0 0 0 0 11 0 0 20 0 0]
[item, idx, countList[idx], output] : 19 4 1 [-10 0 0 0 9 0 11 0 0 20 0 0]
[item, idx, countList[idx], output] : 19 3 1 [-10 0 0 9 9 0 11 0 0 20 0 0]
[item, idx, countList[idx], output] : 16 2 1 [-10 0 6 9 9 0 11 0 0 20 0 0]
[item, idx, countList[idx], output] : 40 10 1 [-10 0 6 9 9 0 11 0 0 20 30 0]
[item, idx, countList[idx], output] : 21 5 1 [-10 0 6 9 9 11 11 0 0 20 30 0]
[item, idx, countList[idx], output] : 25 8 1 [-10 0 6 9 9 11 11 0 15 20 30 0]
[item, idx, countList[idx], output] : 23 7 1 [-10 0 6 9 9 11 11 13 15 20 30 0]
[item, idx, countList[idx], output] : 90 11 2 [-10 0 6 9 9 11 11 13 15 20 30 80]
[-10 0 6 9 9 11 11 13 15 20 30 80]
sort2 end. cost: 137.672µs

==过程模拟==
data2 := []int{2, 1, 5, 3, 2}
fmt.Println(countingSort2(data2[:]))

原始 arr=[2,1,5,3,2]

1、填充计数：
min = 1
countingList=[0,0,0,0,0]
countingList[arr[i]-min] += 1
计数统计：countingList=[1, 2, 1, 0, 1]

2、计数排序：
计数统计：countingList[i] += countingList[i-1]
计数排序：countingList=[1, 3, 4, 4, 5]

3、按位置取出：
loop arr:

0:
    arr[i] = 2
    item = arr[i]-min = 1
    idx = countingList[item] - 1 = 2
    output[idx] = item + min = 2
    countingList[item] -= 1

    output = [0, 0, 2, 0, 0]
    countingList=[1, 2, 4, 4, 5]

1:
    arr[i] = 1
    item = arr[i]-min = 0
    idx = countingList[item] - 1 = 0
    output[idx] = item + min = 1
    countingList[item] -= 1

    output = [1, 0, 2, 0, 0]
    countingList=[0, 2, 4, 4, 5]

2:
    arr[i] = 5
    item = arr[i]-min = 4
    idx = countingList[item] - 1 = 4
    output[idx] = item + min = 5
    countingList[item] -= 1

    output = [1, 0, 2, 0, 5]
    countingList=[0, 2, 4, 4, 4]

3:
    arr[i] = 3
    item = arr[i]-min = 2
    idx = countingList[item] - 1 = 3
    output[idx] = item + min = 3
    countingList[item] -= 1

    output = [1, 0, 2, 3, 5]
    countingList=[0, 2, 3, 4, 4]

4:
    arr[i] = 2
    item = arr[i]-min = 1
    idx = countingList[item] - 1 = 1
    output[idx] = item + min = 2
    countingList[item] -= 1

    output = [1, 2, 2, 3, 5]
    countingList=[0, 1, 3, 4, 4]

*/
