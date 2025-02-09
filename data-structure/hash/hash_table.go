package main

import "fmt"

const TABLE_SIZE = 10

type Node struct {
  key   int
  value int
  next  *Node
}

type HashTable struct {
  table [TABLE_SIZE]*Node
}

// 多项式哈希函数
func (h *HashTable) hash(key int) int {
  hash := 0
  base := 31
  for key > 0 {
    hash = (hash*base + key%10) % TABLE_SIZE
    key /= 10
  }
  return hash
}

func (h *HashTable) insert(key int, value int) {
  index := h.hash(key)
  newNode := &Node{key: key, value: value}
  newNode.next = h.table[index]
  h.table[index] = newNode
}

func (h *HashTable) search(key int) int {
  index := h.hash(key)
  current := h.table[index]
  for current != nil {
    if current.key == key {
      return current.value
    }
    current = current.next
  }
  return -1
}

func (h *HashTable) delete(key int) {
  index := h.hash(key)
  current := h.table[index]
  var prev *Node
  for current != nil {
    if current.key == key {
      if prev == nil {
        h.table[index] = current.next
      } else {
        prev.next = current.next
      }
      return
    }
    prev = current
    current = current.next
  }
}

func (h *HashTable) printTable() {
  for i, node := range h.table {
    if node != nil {
      fmt.Printf("Index %d: ", i)
      for node != nil {
        fmt.Printf("[%d:%d] ", node.key, node.value)
        node = node.next
      }
      fmt.Println()
    }
  }
}

func main() {
  hashTable := &HashTable{}

  hashTable.insert(1, 100)
  hashTable.insert(2, 200)
  hashTable.insert(3, 300)

  fmt.Println("Search key 2:", hashTable.search(2))

  hashTable.delete(2)
  fmt.Println("After deleting key 2:")
  hashTable.printTable()
}

/*
jarry@MacBook-Pro hash % go run hash_table.go
Search key 2: 200
After deleting key 2:
Index 1: [1:100]
Index 3: [3:300]
*/
