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

// 方式1, 递归新建数组版本。无需交换，每个分区都是新数组，数量庞大
func quickSort1(arr []int) []int {
  // 数组长度为1就不再分级
  if len(arr) <= 1 {
    return arr
  }
  fmt.Println("split array:", arr)

  left := make([]int, 0)
  right := make([]int, 0)
  // 设置中间数
  var midIndex = len(arr) / 2
  var pivot = arr[midIndex]

  for i := 0; i < len(arr); i++ {
    fmt.Println("i=", i, " midIndex=", midIndex, " pivot=", pivot, " arr[]=", arr)
    // 当中间基数等于i时，跳过当前。中间数递归完成时合并
    if midIndex == i {
      continue
    }
    // 当前数组里面的项小于基数则添加到左侧
    if arr[i] < pivot {
      left = append(left, arr[i])
      // 大于等于则添加到右侧
    } else {
      right = append(right, arr[i])
    }
  }

  arr = append(quickSort1(left), pivot)
  arr = append(arr, quickSort1(right)...)
  fmt.Println("sorted array:", arr)
  // 递归调用遍历左侧和右侧，再将中间值连接起来
  return arr
}

/**
quick_sort1 recursion step:

      f([7, 11, 9, 10, 12, 13, 8])
            /       10          \
      f([7, 9, 8])           f([11, 12, 13])
        /   9    \             /    12     \
   f([7, 8])    f([])       f([11])       f[13]
   /   8  \
f([7]) f([])
  [7]
*/

// 把数组分按照基准值分为左右两部分，再返回新的中间位置作为排序的pivot
func partition(arr []int, left int, right int) int {
  // pivot基准可以任意挑选，这里取右侧
  var pivotIndex = right
  var pivot = arr[pivotIndex]
  var partitionIndex = left - 1
  for i := left; i < right; i++ {
    // 如果小于基准则进行交换
    if arr[i] < pivot {
      partitionIndex++
      arr[partitionIndex], arr[i] = arr[i], arr[partitionIndex]
    }
  }
  partitionIndex++
  arr[partitionIndex], arr[pivotIndex] = arr[pivotIndex], arr[partitionIndex]
  fmt.Println("partitionIndex=", partitionIndex, "arr[partitionIndex]=", arr[partitionIndex], arr[left:partitionIndex], arr[partitionIndex:right])
  return partitionIndex
}

// 方式2, 标准递归版本。左右不断分区交换，无需新建数组。
func quickSort2(arr []int, left int, right int) []int {
  if left < right {
    var pivot = partition(arr, left, right)
    quickSort2(arr, left, pivot-1)
    quickSort2(arr, pivot+1, right)
  }
  return arr
}

// 方式3, 标准递归版本。需要左右不断交换，无需新建数组。
func quickSort3(arr []int, left int, right int) []int {
  var i = left
  var j = right
  var midIndex = (i + j) / 2
  var pivot = arr[midIndex]

  // 当左侧小于等于右侧则表示还有值没有对比，需要继续
  for i <= j {
    // 当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
    for arr[i] < pivot {
      fmt.Println("arr[i] < pivot:", " i=", i, " j=", j, " pivot=", pivot)
      i++
    }
    // 当前右侧大于基准时左移，直到找出比基准值小的位置来
    for arr[j] > pivot {
      fmt.Println("arr[j] > pivot:", " i=", i, " j=", j, " pivot=", pivot)
      j--
    }

    fmt.Println("  left=", left, " right=", right, " i=", i, " j=", j, " midIndex=", midIndex, " pivot=", pivot, " arr[]=", arr)

    // 当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
    if i <= j {
      arr[i], arr[j] = arr[j], arr[i]
      // 缩小搜查范围，直到左侧都小于基数，右侧都大于基数
      i++
      j--
    }
  }

  // 左侧小于基数位置，不断递归左边部分
  if left < j {
    fmt.Println("left < j:recursion:  left=", left, " right=", right, " i=", i, " j=", j, "arr[]", arr)
    quickSort3(arr, left, j)
  }
  // 基数位置小于右侧，不断递归右侧部分
  if i < right {
    fmt.Println("i < right:recursion:  left=", left, " right=", right, " i=", i, " j=", j, "arr[]", arr)
    quickSort3(arr, i, right)
  }

  return arr
}

// 方式4, 非递归版本。需要交换，无需新建数组，利用stack或queue遍历。
func quickSort4(arr []int, left int, right int) []int {
  var stack = make([]int, 0)
  var i int
  var j int
  var midIndex int
  var pivot int
  // 与标准递归版相同，只是将递归改为遍历栈的方式
  // 先将左右各取一个入栈
  stack = append(stack, left)
  stack = append(stack, right)

  for len(stack) > 0 {
    // 如果栈内还有数据，则一并马上取出，其他逻辑与标准递归版同
    right = stack[len(stack)-1]
    j = right
    stack = stack[:len(stack)-1]

    left = stack[len(stack)-1]
    i = left
    stack = stack[:len(stack)-1]

    midIndex = int((i + j) / 2)
    pivot = arr[midIndex]
    for i <= j {
      for arr[i] < pivot {
        fmt.Println("arr[i] < pivot:", " i=", i, " j=", j, " pivot=", pivot, "arr[]=", arr)
        i++
      }
      for arr[j] > pivot {
        fmt.Println("arr[j] > pivot:", " i=", i, " j=", j, " pivot=", pivot, "arr[]=", arr)
        j--
      }

      if i <= j {
        arr[j], arr[i] = arr[i], arr[j]
        i++
        j--
      }
    }
    if left < j {
      // 与递归版不同，这里添加到栈中，以便继续循环
      fmt.Println("left < j:recursion:  left=", left, " right=", right, " i=", i, " j=", j, "arr[]=", arr)
      stack = append(stack, left)
      stack = append(stack, j)
    }
    if i < right {
      fmt.Println("i < right:recursion:  left=", left, " right=", right, " i=", i, " j=", j, "arr[]=", arr)
      stack = append(stack, i)
      stack = append(stack, right)
    }
  }
  return arr
}

func main() {
  time1 := time.Now()
  var arr1 = []int{7, 11, 9, 10, 12, 13, 8}
  fmt.Println("quick1 origin:", arr1)
  fmt.Println("\r\nquickSort1 sorted:", quickSort1(arr1))
  fmt.Println("quick1. cost:", time.Since(time1))

  time2 := time.Now()
  var arr2 = []int{7, 11, 9, 10, 12, 13, 8}
  fmt.Println("quick2 origin:", arr2)
  fmt.Println("\r\nquickSort2 sorted:", quickSort2(arr2, 0, len(arr2)-1))
  fmt.Println("quick2. cost:", time.Since(time2))

  time3 := time.Now()
  var arr3 = []int{7, 11, 9, 10, 12, 13, 8}
  fmt.Println("quick3 origin:", arr3)
  fmt.Println("\r\nquickSort3 sorted:", quickSort3(arr3, 0, len(arr3)-1))
  fmt.Println("quick3. cost:", time.Since(time3))

  time4 := time.Now()
  var arr4 = []int{7, 11, 9, 10, 12, 13, 8}
  fmt.Println("quick4 origin:", arr4)
  fmt.Println("\r\nquickSort4 sorted:", quickSort4(arr4, 0, len(arr4)-1))
  fmt.Println("quick4. cost:", time.Since(time4))

}

/*
jarry@jarrys-MacBook-Pro quicksort % go run quick_sort.go
quick1 origin: [7 11 9 10 12 13 8]
split array: [7 11 9 10 12 13 8]
i= 0  midIndex= 3  pivot= 10  arr[]= [7 11 9 10 12 13 8]
i= 1  midIndex= 3  pivot= 10  arr[]= [7 11 9 10 12 13 8]
i= 2  midIndex= 3  pivot= 10  arr[]= [7 11 9 10 12 13 8]
i= 3  midIndex= 3  pivot= 10  arr[]= [7 11 9 10 12 13 8]
i= 4  midIndex= 3  pivot= 10  arr[]= [7 11 9 10 12 13 8]
i= 5  midIndex= 3  pivot= 10  arr[]= [7 11 9 10 12 13 8]
i= 6  midIndex= 3  pivot= 10  arr[]= [7 11 9 10 12 13 8]
split array: [7 9 8]
i= 0  midIndex= 1  pivot= 9  arr[]= [7 9 8]
i= 1  midIndex= 1  pivot= 9  arr[]= [7 9 8]
i= 2  midIndex= 1  pivot= 9  arr[]= [7 9 8]
split array: [7 8]
i= 0  midIndex= 1  pivot= 8  arr[]= [7 8]
i= 1  midIndex= 1  pivot= 8  arr[]= [7 8]
sorted array: [7 8]
sorted array: [7 8 9]
split array: [11 12 13]
i= 0  midIndex= 1  pivot= 12  arr[]= [11 12 13]
i= 1  midIndex= 1  pivot= 12  arr[]= [11 12 13]
i= 2  midIndex= 1  pivot= 12  arr[]= [11 12 13]
sorted array: [11 12 13]
sorted array: [7 8 9 10 11 12 13]

quickSort1 sorted: [7 8 9 10 11 12 13]
quick1. cost: 125.788µs
quick2 origin: [7 11 9 10 12 13 8]
partitionIndex= 1 arr[partitionIndex]= 8 [7] [8 9 10 12 13]
partitionIndex= 4 arr[partitionIndex]= 11 [9 10] [11 13]
partitionIndex= 3 arr[partitionIndex]= 10 [9] []
partitionIndex= 5 arr[partitionIndex]= 12 [] [12]

quickSort2 sorted: [7 8 9 10 11 12 13]
quick2. cost: 14.256µs
quick3 origin: [7 11 9 10 12 13 8]
arr[i] < pivot:  i= 0  j= 6  pivot= 10
  left= 0  right= 6  i= 1  j= 6  midIndex= 3  pivot= 10  arr[]= [7 11 9 10 12 13 8]
arr[i] < pivot:  i= 2  j= 5  pivot= 10
arr[j] > pivot:  i= 3  j= 5  pivot= 10
arr[j] > pivot:  i= 3  j= 4  pivot= 10
  left= 0  right= 6  i= 3  j= 3  midIndex= 3  pivot= 10  arr[]= [7 8 9 10 12 13 11]
left < j:recursion:  left= 0  right= 6  i= 4  j= 2 arr[] [7 8 9 10 12 13 11]
arr[i] < pivot:  i= 0  j= 2  pivot= 8
arr[j] > pivot:  i= 1  j= 2  pivot= 8
  left= 0  right= 2  i= 1  j= 1  midIndex= 1  pivot= 8  arr[]= [7 8 9 10 12 13 11]
i < right:recursion:  left= 0  right= 6  i= 4  j= 2 arr[] [7 8 9 10 12 13 11]
arr[i] < pivot:  i= 4  j= 6  pivot= 13
  left= 4  right= 6  i= 5  j= 6  midIndex= 5  pivot= 13  arr[]= [7 8 9 10 12 13 11]
left < j:recursion:  left= 4  right= 6  i= 6  j= 5 arr[] [7 8 9 10 12 11 13]
  left= 4  right= 5  i= 4  j= 5  midIndex= 4  pivot= 12  arr[]= [7 8 9 10 12 11 13]

quickSort3 sorted: [7 8 9 10 11 12 13]
quick3. cost: 107.965µs
quick4 origin: [7 11 9 10 12 13 8]
arr[i] < pivot:  i= 0  j= 6  pivot= 10 arr[]= [7 11 9 10 12 13 8]
arr[i] < pivot:  i= 2  j= 5  pivot= 10 arr[]= [7 8 9 10 12 13 11]
arr[j] > pivot:  i= 3  j= 5  pivot= 10 arr[]= [7 8 9 10 12 13 11]
arr[j] > pivot:  i= 3  j= 4  pivot= 10 arr[]= [7 8 9 10 12 13 11]
left < j:recursion:  left= 0  right= 6  i= 4  j= 2 arr[]= [7 8 9 10 12 13 11]
i < right:recursion:  left= 0  right= 6  i= 4  j= 2 arr[]= [7 8 9 10 12 13 11]
arr[i] < pivot:  i= 4  j= 6  pivot= 13 arr[]= [7 8 9 10 12 13 11]
left < j:recursion:  left= 4  right= 6  i= 6  j= 5 arr[]= [7 8 9 10 12 11 13]
arr[i] < pivot:  i= 0  j= 2  pivot= 8 arr[]= [7 8 9 10 11 12 13]
arr[j] > pivot:  i= 1  j= 2  pivot= 8 arr[]= [7 8 9 10 11 12 13]

quickSort4 sorted: [7 8 9 10 11 12 13]
quick4. cost: 51.774µs
*/
