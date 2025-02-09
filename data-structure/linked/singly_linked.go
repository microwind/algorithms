package main

import "fmt"

// 定义节点结构
type Node struct {
  data int
  next *Node
}

// 单向链表结构
type SinglyLinkedList struct {
  head *Node
}

// 向链表尾部添加节点
func (list *SinglyLinkedList) Append(data int) {
  newNode := &Node{data: data}
  if list.head == nil {
    list.head = newNode
    return
  }
  last := list.head
  for last.next != nil {
    last = last.next
  }
  last.next = newNode
}

// 打印链表内容
func (list *SinglyLinkedList) PrintList() {
  current := list.head
  for current != nil {
    fmt.Printf("%d -> ", current.data)
    current = current.next
  }
  fmt.Println("NULL")
}

func main() {
  list := &SinglyLinkedList{}
  list.Append(1)
  list.Append(2)
  list.Append(3)
  list.PrintList() // 输出：1 -> 2 -> 3 -> NULL
}

/*
jarry@MacBook-Pro linked % go run singly_linked.go
1 -> 2 -> 3 -> NULL
*/
