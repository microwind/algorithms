/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import "fmt"

/**
 * 插入排序标准版
 */
func insertSort1(arr []int) []int {
  var j int
  var current int
  var l = len(arr)

  for i := 0; i < l; i++ {
    // 当前项为第1项
    current = arr[i]
    // j是已排序的末尾位置
    j = i - 1

    // 内循环用来遍历已排序区间
    // 将该项自右往左与已排序项逐个对比，当遇到比自己大的项时，则将该位置逐项右移
    // 直到遇到小于等于自己的项则停止移动，表示插入成功
    fmt.Println("i=", i, " j=", j, "current=", current, "arr[i]=", arr[i], "arr[]=", arr)
    for j >= 0 && current < arr[j] {
      // 逐项右移，以便空出插入项
      arr[j+1] = arr[j]
      j--
    }

    // 没有比自己大的项了，则插入到当前位置
    arr[j+1] = current
  }
  return arr
}

/**
 * 插入排序降序版
 */
func insertSort2(arr []int) []int {
  for i := 0; i < len(arr); i++ {
    var current = arr[i]
    var j = i - 1
    fmt.Println("i=", i, " j=", j, "current=", current, "arr[i]=", arr[i], "arr[j + 1]=", arr[j+1], "arr[]=", arr)
    for ; j >= 0; j-- {
      // 当前项比已排序的内容要大，则逐个右移，空出位置
      if current > arr[j] {
        arr[j+1] = arr[j]
      } else {
        // 当小于已排序内容，则跳出循环
        break
      }
    }
    arr[j+1] = current
  }
  return arr
}

/**
 * 插入排序直接插入法，利用copy函数
 */
func insertSort3(arr []int) []int {
  for i, current := range arr {
    var j = i - 1
    isMin := true
    fmt.Println("i=", i, " j=", j, "current=", current, "arr[i]=", arr[i], "arr[j + 1]=", arr[j+1], "arr[]=", arr)
    for j >= 0 {
      // 当前项比已排序的内容要大，则插入其后
      if current > arr[j] {
        // 将j至i全部项整体右移1位
        copy(arr[j+1:i+1], arr[j:i])
        arr[j+1] = current
        isMin = false
        break
      }
      j -= 1
    }
    // 如果当前项最小则插入到已排序的最前面
    if isMin {
      copy(arr[1:i+1], arr[0:i])
      arr[0] = current
    }
  }
  return arr
}

func main() {
  fmt.Println("insert sort1:")
  data := [...]int{7, 11, 9, 10, 12, 13, 8}
  data2 := [...]int{3, 4, 15, -2, -2, -1, 2, 6, 3, -7, 10}
  fmt.Println(insertSort1(data[:]))
  fmt.Println(insertSort1(data2[:]))

  fmt.Println("insert sort2:")
  data = [...]int{7, 11, 9, 10, 12, 13, 8}
  data2 = [...]int{3, 4, 15, -2, -2, -1, 2, 6, 3, -7, 10}
  fmt.Println(insertSort2(data[:]))
  fmt.Println(insertSort2(data2[:]))

  fmt.Println("insert sort3:")
  data = [...]int{7, 11, 9, 10, 12, 13, 8}
  data2 = [...]int{3, 4, 15, -2, -2, -1, 2, 6, 3, -7, 10}
  fmt.Println(insertSort3(data[:]))
  fmt.Println(insertSort3(data2[:]))
}

/* execute test
jarry@jarrys-MacBook-Pro insertsort % go run insert_sort.go
insert sort1:
i= 0  j= -1 current= 7 arr[i]= 7 arr[]= [7 11 9 10 12 13 8]
i= 1  j= 0 current= 11 arr[i]= 11 arr[]= [7 11 9 10 12 13 8]
i= 2  j= 1 current= 9 arr[i]= 9 arr[]= [7 11 9 10 12 13 8]
i= 3  j= 2 current= 10 arr[i]= 10 arr[]= [7 9 11 10 12 13 8]
i= 4  j= 3 current= 12 arr[i]= 12 arr[]= [7 9 10 11 12 13 8]
i= 5  j= 4 current= 13 arr[i]= 13 arr[]= [7 9 10 11 12 13 8]
i= 6  j= 5 current= 8 arr[i]= 8 arr[]= [7 9 10 11 12 13 8]
[7 8 9 10 11 12 13]
i= 0  j= -1 current= 3 arr[i]= 3 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 1  j= 0 current= 4 arr[i]= 4 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 2  j= 1 current= 15 arr[i]= 15 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 3  j= 2 current= -2 arr[i]= -2 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 4  j= 3 current= -2 arr[i]= -2 arr[]= [-2 3 4 15 -2 -1 2 6 3 -7 10]
i= 5  j= 4 current= -1 arr[i]= -1 arr[]= [-2 -2 3 4 15 -1 2 6 3 -7 10]
i= 6  j= 5 current= 2 arr[i]= 2 arr[]= [-2 -2 -1 3 4 15 2 6 3 -7 10]
i= 7  j= 6 current= 6 arr[i]= 6 arr[]= [-2 -2 -1 2 3 4 15 6 3 -7 10]
i= 8  j= 7 current= 3 arr[i]= 3 arr[]= [-2 -2 -1 2 3 4 6 15 3 -7 10]
i= 9  j= 8 current= -7 arr[i]= -7 arr[]= [-2 -2 -1 2 3 3 4 6 15 -7 10]
i= 10  j= 9 current= 10 arr[i]= 10 arr[]= [-7 -2 -2 -1 2 3 3 4 6 15 10]
[-7 -2 -2 -1 2 3 3 4 6 10 15]
insert sort2:
i= 0  j= -1 current= 7 arr[i]= 7 arr[j + 1]= 7 arr[]= [7 11 9 10 12 13 8]
i= 1  j= 0 current= 11 arr[i]= 11 arr[j + 1]= 11 arr[]= [7 11 9 10 12 13 8]
i= 2  j= 1 current= 9 arr[i]= 9 arr[j + 1]= 9 arr[]= [11 7 9 10 12 13 8]
i= 3  j= 2 current= 10 arr[i]= 10 arr[j + 1]= 10 arr[]= [11 9 7 10 12 13 8]
i= 4  j= 3 current= 12 arr[i]= 12 arr[j + 1]= 12 arr[]= [11 10 9 7 12 13 8]
i= 5  j= 4 current= 13 arr[i]= 13 arr[j + 1]= 13 arr[]= [12 11 10 9 7 13 8]
i= 6  j= 5 current= 8 arr[i]= 8 arr[j + 1]= 8 arr[]= [13 12 11 10 9 7 8]
[13 12 11 10 9 8 7]
i= 0  j= -1 current= 3 arr[i]= 3 arr[j + 1]= 3 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 1  j= 0 current= 4 arr[i]= 4 arr[j + 1]= 4 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 2  j= 1 current= 15 arr[i]= 15 arr[j + 1]= 15 arr[]= [4 3 15 -2 -2 -1 2 6 3 -7 10]
i= 3  j= 2 current= -2 arr[i]= -2 arr[j + 1]= -2 arr[]= [15 4 3 -2 -2 -1 2 6 3 -7 10]
i= 4  j= 3 current= -2 arr[i]= -2 arr[j + 1]= -2 arr[]= [15 4 3 -2 -2 -1 2 6 3 -7 10]
i= 5  j= 4 current= -1 arr[i]= -1 arr[j + 1]= -1 arr[]= [15 4 3 -2 -2 -1 2 6 3 -7 10]
i= 6  j= 5 current= 2 arr[i]= 2 arr[j + 1]= 2 arr[]= [15 4 3 -1 -2 -2 2 6 3 -7 10]
i= 7  j= 6 current= 6 arr[i]= 6 arr[j + 1]= 6 arr[]= [15 4 3 2 -1 -2 -2 6 3 -7 10]
i= 8  j= 7 current= 3 arr[i]= 3 arr[j + 1]= 3 arr[]= [15 6 4 3 2 -1 -2 -2 3 -7 10]
i= 9  j= 8 current= -7 arr[i]= -7 arr[j + 1]= -7 arr[]= [15 6 4 3 3 2 -1 -2 -2 -7 10]
i= 10  j= 9 current= 10 arr[i]= 10 arr[j + 1]= 10 arr[]= [15 6 4 3 3 2 -1 -2 -2 -7 10]
[15 10 6 4 3 3 2 -1 -2 -2 -7]
insert sort3:
i= 0  j= -1 current= 7 arr[i]= 7 arr[j + 1]= 7 arr[]= [7 11 9 10 12 13 8]
i= 1  j= 0 current= 11 arr[i]= 11 arr[j + 1]= 11 arr[]= [7 11 9 10 12 13 8]
i= 2  j= 1 current= 9 arr[i]= 9 arr[j + 1]= 9 arr[]= [7 11 9 10 12 13 8]
i= 3  j= 2 current= 10 arr[i]= 10 arr[j + 1]= 10 arr[]= [7 9 11 10 12 13 8]
i= 4  j= 3 current= 12 arr[i]= 12 arr[j + 1]= 12 arr[]= [7 9 10 11 12 13 8]
i= 5  j= 4 current= 13 arr[i]= 13 arr[j + 1]= 13 arr[]= [7 9 10 11 12 13 8]
i= 6  j= 5 current= 8 arr[i]= 8 arr[j + 1]= 8 arr[]= [7 9 10 11 12 13 8]
[7 8 9 10 11 12 13]
i= 0  j= -1 current= 3 arr[i]= 3 arr[j + 1]= 3 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 1  j= 0 current= 4 arr[i]= 4 arr[j + 1]= 4 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 2  j= 1 current= 15 arr[i]= 15 arr[j + 1]= 15 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 3  j= 2 current= -2 arr[i]= -2 arr[j + 1]= -2 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 4  j= 3 current= -2 arr[i]= -2 arr[j + 1]= -2 arr[]= [-2 3 4 15 -2 -1 2 6 3 -7 10]
i= 5  j= 4 current= -1 arr[i]= -1 arr[j + 1]= -1 arr[]= [-2 -2 3 4 15 -1 2 6 3 -7 10]
i= 6  j= 5 current= 2 arr[i]= 2 arr[j + 1]= 2 arr[]= [-2 -2 -1 3 4 15 2 6 3 -7 10]
i= 7  j= 6 current= 6 arr[i]= 6 arr[j + 1]= 6 arr[]= [-2 -2 -1 2 3 4 15 6 3 -7 10]
i= 8  j= 7 current= 3 arr[i]= 3 arr[j + 1]= 3 arr[]= [-2 -2 -1 2 3 4 6 15 3 -7 10]
i= 9  j= 8 current= -7 arr[i]= -7 arr[j + 1]= -7 arr[]= [-2 -2 -1 2 3 3 4 6 15 -7 10]
i= 10  j= 9 current= 10 arr[i]= 10 arr[j + 1]= 10 arr[]= [-7 -2 -2 -1 2 3 3 4 6 15 10]
[-7 -2 -2 -1 2 3 3 4 6 10 15]
*/
