package main

import "fmt"

// 定义节点结构
type Node struct {
  data int
  next *Node
}

// 循环链表结构
type CircularLinkedList struct {
  head *Node
}

// 向链表尾部添加节点
func (list *CircularLinkedList) Append(data int) {
  newNode := &Node{data: data}
  if list.head == nil {
    list.head = newNode
    newNode.next = list.head
    return
  }
  last := list.head
  for last.next != list.head {
    last = last.next
  }
  last.next = newNode
  newNode.next = list.head
}

// 打印链表内容
func (list *CircularLinkedList) PrintList() {
  if list.head == nil {
    return
  }
  current := list.head
  for {
    fmt.Printf("%d -> ", current.data)
    current = current.next
    if current == list.head {
      break
    }
  }
  fmt.Println("(back to head)")
}

func main() {
  list := &CircularLinkedList{}
  list.Append(1)
  list.Append(2)
  list.Append(3)
  list.PrintList() // 输出：1 -> 2 -> 3 -> (back to head)
}

/*
jarry@MacBook-Pro linked % go run circular_linked.go
1 -> 2 -> 3 -> (back to head)
*/
