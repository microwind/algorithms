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

// Tree 定义堆排序过程中使用的堆结构
type Tree struct {
  arr  []int // 用来存储堆的数据
  size int   // 用来标识堆的大小
}

// 保持最大顶堆特性非递归版
func maxHeapify(tree *Tree, idx int) {
  arr := tree.arr
  var current = arr[idx]
  var child = 2*idx + 1
  // 从当前位置的左节点开始遍历
  for child < tree.size {
    fmt.Println("current=", current, " idx=", idx, " child=", child, " size=", tree.size)
    // 如果左节点小于右节点且小于总长度，则指向右节点
    if child+1 < tree.size && arr[child] < arr[child+1] {
      child++
    }
    if arr[child] > current {
      // 如果子节点大于父节点，将子节点的值赋给父节点
      arr[idx] = arr[child]
      // 当前节点指向该子节点，继续循环
      idx = child
    } else {
      // 子节点小于父节点则跳出循环
      break
    }
    // 遍历子树父节点
    child = 2*idx + 1
  }
  // 当前节点赋值为父节点的值
  arr[idx] = current
}

// 利用堆结构对数组进行排序
func heapSort(arr []int) []int {
  tree := &Tree{}
  tree.arr = arr
  tree.size = len(arr)

  // 构建大顶堆，把最大节点冒出到堆顶，从任意1个父节点开始均可
  var current = (tree.size - 1) / 2
  for ; current >= 0; current-- {
    maxHeapify(tree, current)
  }

  // 从最底层子节点开始排序，置换顶根节点与子节点，并继续构建大顶堆
  for tree.size > 0 {
    // 将最大的数值调整到堆的末尾
    tree.arr[0], tree.arr[tree.size-1] = tree.arr[tree.size-1], tree.arr[0]
    // 减少堆的长度
    tree.size--
    // 由于堆顶元素改变了，而且堆的大小改变了，需要重新调整堆，维持堆的性质
    maxHeapify(tree, 0)
  }
  return tree.arr
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
 这里parent=2，来自(总长度-1)/2，从这个父节点开始构建大顶堆
 1. maxHeapify: parent= 2 left= 5 right= 6 max= 5 size= 7
               7(0)
           /         \
         11(1)        13(2)
        /    \      /     \
    10(3)  12(4)  9(5)  8(6)

 2. maxHeapify: parent= 1 left= 3 right= 4 max= 4 size= 7
               7(0)
           /         \
         12(1)        13(2)
        /    \      /     \
    10(3)  11(4)  9(5)  8(6)

 3. maxHeapify: parent= 0 left= 1 right= 2 max= 2 size= 7
               13(0)
           /         \
         12(1)        7(2)
        /    \      /     \
    10(3)  11(4)  9(5)  8(6)

 3.1 maxHeapify recursion: parent= 2 left= 5 right= 6 max= 5 size= 7
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

 1.1 maxHeapify: parent= 0 left= 1 right= 2 max= 1 size= 6
               12(0)
           /         \
         8(1)        9(2)
        /    \      /     \
    10(3)  11(4)  7(5)  13(6)

 1.2 maxHeapify recursion: parent= 1 left= 3 right= 4 max= 4 size= 6
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

 2.1 maxHeapify: parent= 0 left= 1 right= 2 max= 1 size= 5
               11(0)
           /         \
         7(1)        9(2)
        /    \      /     \
    10(3)  8(4)  12(5)  13(6)

 2.2 maxHeapify recursion: parent= 1 left= 3 right= 4 max= 3 size= 5
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

 3.1 maxHeapify: parent= 0 left= 1 right= 2 max= 1 size= 4
               10(0)
           /         \
         8(1)        9(2)
        /    \      /     \
    7(3)  11(4)  12(5)  13(6)

 3.2 maxHeapify recursion: parent= 1 left= 3 right= 4 max= 1 size= 4

 4. swap, child = 3:
               7(0)
           /         \
         8(1)        9(2)
        /    \      /     \
    10(3)  11(4)  12(5)  13(6)

 4.1 maxHeapify: parent= 0 left= 1 right= 2 max= 2 size= 3
               9(0)
           /         \
         8(1)        7(2)
        /    \      /     \
    10(3)  11(4)  12(5)  13(6)

 4.2 maxHeapify recursion: parent= 2 left= 5 right= 6 max= 2 size= 3

 5. swap, child = 2:
               7(0)
           /         \
         8(1)        9(2)
        /    \      /     \
    10(3)  11(4)  12(5)  13(6)

 5.1 maxHeapify: parent= 0 left= 1 right= 2 max= 1 size= 2
               8(0)
           /         \
         7(1)        9(2)
        /    \      /     \
    10(3)  11(4)  12(5)  13(6)

 5.2 maxHeapify recursion: parent= 1 left= 3 right= 4 max= 1 size= 2

 6. swap, child = 1:
               7(0)
           /         \
         8(1)        9(2)
        /    \      /     \
    10(3)  11(4)  12(5)  13(6)

 6.1 maxHeapify: parent= 0 left= 1 right= 2 max= 0 size= 1

*/

/*
 jarry@jarrys-MacBook-Pro heapsort % go version
 go version go1.19.5 darwin/amd64
 jarry@jarrys-MacBook-Pro heapsort % go run heap_sort.go
 heap sort1:
 parent= 2 left= 5 right= 6 max= 5 size: 7
 parent= 5 left= 11 right= 12 max= 5 size: 7
 parent sort: 2 [7 11 13 10 12 9 8]
 parent= 1 left= 3 right= 4 max= 4 size: 7
 parent= 4 left= 9 right= 10 max= 4 size: 7
 parent sort: 1 [7 12 13 10 11 9 8]
 parent= 0 left= 1 right= 2 max= 2 size: 7
 parent= 2 left= 5 right= 6 max= 5 size: 7
 parent= 5 left= 11 right= 12 max= 5 size: 7
 parent sort: 0 [13 12 9 10 11 7 8]
 child start: parent= -1  child= 6
 parent= 0 left= 1 right= 2 max= 1 size: 6
 parent= 1 left= 3 right= 4 max= 4 size: 6
 parent= 4 left= 9 right= 10 max= 4 size: 6
 child sort: 6 [12 11 9 10 8 7 13]
 parent= 0 left= 1 right= 2 max= 1 size: 5
 parent= 1 left= 3 right= 4 max= 3 size: 5
 parent= 3 left= 7 right= 8 max= 3 size: 5
 child sort: 5 [11 10 9 7 8 12 13]
 parent= 0 left= 1 right= 2 max= 1 size: 4
 parent= 1 left= 3 right= 4 max= 1 size: 4
 child sort: 4 [10 8 9 7 11 12 13]
 parent= 0 left= 1 right= 2 max= 2 size: 3
 parent= 2 left= 5 right= 6 max= 2 size: 3
 child sort: 3 [9 8 7 10 11 12 13]
 parent= 0 left= 1 right= 2 max= 1 size: 2
 parent= 1 left= 3 right= 4 max= 1 size: 2
 child sort: 2 [8 7 9 10 11 12 13]
 parent= 0 left= 1 right= 2 max= 0 size: 1
 child sort: 1 [7 8 9 10 11 12 13]
 [7 8 9 10 11 12 13]
 data1 end. cost: 213.241µs
*/
