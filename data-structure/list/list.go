package main

import (
  "fmt"
)

// List 结构体
type List struct {
  data     []int
  size     int
  capacity int
}

// 创建 List
func NewList() *List {
  capacity := 10
  return &List{
    data:     make([]int, 0, capacity),
    size:     0,
    capacity: capacity,
  }
}

// 扩展 List 容量
func (l *List) resize(newCapacity int) {
  if newCapacity > l.capacity {
    newData := make([]int, l.size, newCapacity)
    copy(newData, l.data)
    l.data = newData
    l.capacity = newCapacity
  }
}

// 添加元素
func (l *List) Add(value int) {
  if l.size == l.capacity {
    l.resize(l.capacity * 2)
  }
  l.data = append(l.data, value)
  l.size++
}

// 删除最后一个元素
func (l *List) Remove() {
  if l.size > 0 {
    l.data = l.data[:l.size-1]
    l.size--
  }
}

// 获取元素
func (l *List) Get(index int) int {
  if index < 0 || index >= l.size {
    panic("Index out of range")
  }
  return l.data[index]
}

// 获取大小
func (l *List) Size() int {
  return l.size
}

// 获取容量
func (l *List) Capacity() int {
  return l.capacity
}

// 打印列表
func (l *List) Print() {
  fmt.Println("List:", l.data)
}

func main() {
  list := NewList()
  list.Add(10)
  list.Add(20)
  list.Add(30)
  list.Print() // List: [10 20 30]

  fmt.Println("Element at index 1:", list.Get(1)) // 20

  list.Remove()
  list.Print() // List: [10 20]

  fmt.Println("Size:", list.Size())         // 2
  fmt.Println("Capacity:", list.Capacity()) // 10

  list.resize(20)
  fmt.Println("New Capacity:", list.Capacity()) // 20
}

/*
jarry@MacBook-Pro list % go run list.go
List: [10 20 30]
Element at index 1: 20
List: [10 20]
Size: 2
Capacity: 10
New Capacity: 20
*/
