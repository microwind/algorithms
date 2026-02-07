package main

import (
  "fmt"
  "hash/fnv"
)

// Set 结构体，使用 map 模拟哈希桶
// 提供基本的集合操作，包括添加、删除、查找等

type Set struct {
  buckets    map[uint32][]interface{}            // 用map表示哈希桶
  size       int                                 // 当前集合大小
  hashFunc   func(interface{}) uint32            // 哈希函数
  equalsFunc func(interface{}, interface{}) bool // 比较函数
}

// 默认哈希函数（使用 FNV-1a 哈希算法）
func defaultHashFunc(key interface{}) uint32 {
  h := fnv.New32a()
  fmt.Fprintf(h, "%v", key)
  return h.Sum32()
}

// 默认比较函数（直接比较值是否相等）
func defaultEqualsFunc(a, b interface{}) bool {
  return a == b
}

// 创建一个新的 Set
func NewSet() *Set {
  return &Set{
    buckets:    make(map[uint32][]interface{}),
    size:       0,
    hashFunc:   defaultHashFunc,
    equalsFunc: defaultEqualsFunc,
  }
}

// 添加元素到 Set
func (s *Set) Add(key interface{}) {
  hash := s.hashFunc(key)
  for _, k := range s.buckets[hash] {
    // 如果元素已存在，则不添加
    if s.equalsFunc(k, key) {
      fmt.Printf("Exist element: hash=%u key=%d value=%d\n", hash, key, s.buckets[hash])
      return
    }
  }
  s.buckets[hash] = append(s.buckets[hash], key)
  s.size++
  // 打印调试信息：打印插入后的元素
  fmt.Printf("Adding element: hash=%u key=%d value=%d\n", hash, key, s.buckets[hash])
}

// 检查元素是否在 Set 中
func (s *Set) Contains(key interface{}) bool {
  hash := s.hashFunc(key)
  for _, k := range s.buckets[hash] {
    if s.equalsFunc(k, key) {
      return true
    }
  }
  return false
}

// 从 Set 中删除元素
func (s *Set) Remove(key interface{}) {
  hash := s.hashFunc(key)
  for i, k := range s.buckets[hash] {
    if s.equalsFunc(k, key) {
      s.buckets[hash] = append(s.buckets[hash][:i], s.buckets[hash][i+1:]...)
      s.size--
      return
    }
  }
}

// 获取 Set 的大小
func (s *Set) Size() int {
  return s.size
}

// 打印 Set 中的所有元素
func (s *Set) Print() {
  for _, bucket := range s.buckets {
    for _, key := range bucket {
      fmt.Printf("%v ", key)
    }
  }
  fmt.Println()
}

func main() {
  // 创建一个 Set
  set := NewSet()
  values := []int{10, 20, 20, 30, 40, 40, 50}

  // 添加元素
  for _, v := range values {
    set.Add(v)
  }

  // 打印 Set 内容
  set.Print()

  // 检查元素是否存在
  fmt.Println("Contains 30?", set.Contains(30))

  // 删除元素
  set.Remove(30)
  set.Print()
}

/*
jarry@MacBook-Pro set % go run set.go
Adding element: hash=%!u(uint32=468396612) key=10 value=[10]
Adding element: hash=%!u(uint32=2381486463) key=20 value=[20]
Exist element: hash=%!u(uint32=2381486463) key=20 value=[20]
Adding element: hash=%!u(uint32=2280673654) key=30 value=[30]
Adding element: hash=%!u(uint32=2313390249) key=40 value=[40]
Exist element: hash=%!u(uint32=2313390249) key=40 value=[40]
Adding element: hash=%!u(uint32=2212577440) key=50 value=[50]
10 20 30 40 50
Contains 30? true
10 20 40 50
*/
