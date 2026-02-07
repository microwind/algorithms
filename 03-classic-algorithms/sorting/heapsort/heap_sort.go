/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import (
  "fmt"
  "time"
)

/* 根据完全二叉树结构性质，父子节点与数组下标的关系，通过数组下标i得到节点位置 */

// 获取父节点
func getParent(i int) int {
  return int((i - 1) / 2)
}

// 获取左节点
func getLeft(i int) int {
  return 2*i + 1
}

// 获取右节点
func getRight(i int) int {
  return 2*i + 2
}

// 始终保持大顶堆特性, 构建大顶堆的递归写法
func maxHeapify(arr []int, idx int, size int) {
  var max = idx
  var left = getLeft(idx)
  var right = getRight(idx)
  // 获取最大数的位置
  if left < size && arr[left] > arr[max] {
    max = left
  }
  if right < size && arr[right] > arr[max] {
    max = right
  }
  fmt.Println("idx=", idx, "left=", left, "right=", right, "max=", max, "size:", size)
  if max != idx {
    // 保持最大顶堆，如果当前父节点小于子节点，则进行交换
    arr[idx], arr[max] = arr[max], arr[idx]
    // 继续递归执行，直到整棵树符合最大堆特性
    maxHeapify(arr, max, size)
  }
}

// 堆排序算法
func heapSort(arr []int) []int {
  var arrLen = len(arr)
  // 最底层的父节点
  var parent = getParent(arrLen) - 1
  // 最底层的子节点
  var child = arrLen - 1
  // 从最后的父节点开始遍历，把最大的那个父节点冒出到堆顶
  for ; parent >= 0; parent-- {
    maxHeapify(arr, parent, arrLen)
    fmt.Println("parent sort:", parent, arr)
  }
  fmt.Println("child start:", "parent=", parent, " child=", child)
  // 从子节点往上开始交换和保持大顶堆
  for child > 0 {
    // 将顶端的父节点与当前子节点互换
    arr[0], arr[child] = arr[child], arr[0]
    // 自最底层往上遍历排序
    maxHeapify(arr, 0, child)
    fmt.Println("child sort:", child, arr)
    child--
  }
  return arr
}

// test
func main() {
  fmt.Println("heap sort1:")
  time1 := time.Now()
  data1 := []int{7, 11, 9, 10, 12, 13, 8}
  fmt.Println(heapSort(data1[:]))
  fmt.Println("data1 end. cost:", time.Since(time1))
}

/*
oringal array: [7, 11, 9, 10, 12, 13, 8]
heap:
              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  12(4)  13(5)  8(6)

父节点步骤，构建大顶堆，父节点要大于左右子节点
1. maxHeapify: idx= 2 left= 5 right= 6 max= 5 size= 7
              7(0)
          /         \
        11(1)        13(2)
       /    \      /     \
   10(3)  12(4)  9(5)  8(6)

2. maxHeapify: idx= 1 left= 3 right= 4 max= 4 size= 7
              7(0)
          /         \
        12(1)        13(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

3. maxHeapify: idx= 0 left= 1 right= 2 max= 2 size= 7
              13(0)
          /         \
        12(1)        7(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

3.1 maxHeapify recursion: idx= 2 left= 5 right= 6 max= 5 size= 7
              13(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  8(6)

子节点堆排序:
1. swap, child = 6:
              8(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

1.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 6
              12(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

1.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 4 size= 6
              12(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  7(5)  13(6)

2. swap, child = 5:
              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

2.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 5
              11(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

2.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 3 size= 5
              11(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  8(4)  12(5)  13(6)

3. swap, child = 4:
              8(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

3.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 4
              10(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

3.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 1 size= 4

4. swap, child = 3:
              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

4.1 maxHeapify: idx= 0 left= 1 right= 2 max= 2 size= 3
              9(0)
          /         \
        8(1)        7(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

4.2 maxHeapify recursion: idx= 2 left= 5 right= 6 max= 2 size= 3

5. swap, child = 2:
              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

5.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 2
              8(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

5.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 1 size= 2

6. swap, child = 1:
              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

6.1 maxHeapify: idx= 0 left= 1 right= 2 max= 0 size= 1

*/

/*
jarry@jarrys-MacBook-Pro heapsort % go version
go version go1.19.5 darwin/amd64
jarry@jarrys-MacBook-Pro heapsort % go run heap_sort.go
heap sort1:
idx= 2 left= 5 right= 6 max= 5 size: 7
idx= 5 left= 11 right= 12 max= 5 size: 7
parent sort: 2 [7 11 13 10 12 9 8]
idx= 1 left= 3 right= 4 max= 4 size: 7
idx= 4 left= 9 right= 10 max= 4 size: 7
parent sort: 1 [7 12 13 10 11 9 8]
idx= 0 left= 1 right= 2 max= 2 size: 7
idx= 2 left= 5 right= 6 max= 5 size: 7
idx= 5 left= 11 right= 12 max= 5 size: 7
parent sort: 0 [13 12 9 10 11 7 8]
child start: parent= -1  child= 6
idx= 0 left= 1 right= 2 max= 1 size: 6
idx= 1 left= 3 right= 4 max= 4 size: 6
idx= 4 left= 9 right= 10 max= 4 size: 6
child sort: 6 [12 11 9 10 8 7 13]
idx= 0 left= 1 right= 2 max= 1 size: 5
idx= 1 left= 3 right= 4 max= 3 size: 5
idx= 3 left= 7 right= 8 max= 3 size: 5
child sort: 5 [11 10 9 7 8 12 13]
idx= 0 left= 1 right= 2 max= 1 size: 4
idx= 1 left= 3 right= 4 max= 1 size: 4
child sort: 4 [10 8 9 7 11 12 13]
idx= 0 left= 1 right= 2 max= 2 size: 3
idx= 2 left= 5 right= 6 max= 2 size: 3
child sort: 3 [9 8 7 10 11 12 13]
idx= 0 left= 1 right= 2 max= 1 size: 2
idx= 1 left= 3 right= 4 max= 1 size: 2
child sort: 2 [8 7 9 10 11 12 13]
idx= 0 left= 1 right= 2 max= 0 size: 1
child sort: 1 [7 8 9 10 11 12 13]
[7 8 9 10 11 12 13]
data1 end. cost: 213.241µs
*/
