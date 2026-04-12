/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 双链表数据结构 - Go实现
 */

package main

import "fmt"

// 节点结构体
type Node struct {
  data int     // 节点数据
  next *Node   // 指向下一个节点
  prev *Node   // 指向上一个节点
}

// 双链表结构体
type DoublyLinkedList struct {
  head *Node
}

// 向链表尾部添加节点
func (list *DoublyLinkedList) Append(data int) {
  newNode := &Node{data: data}
  if list.head == nil {
    list.head = newNode  // 链表为空，新节点作为头节点
    return
  }
  last := list.head
  for last.next != nil {
    last = last.next  // 找到最后一个节点
  }
  last.next = newNode  // 将新节点链接到尾部
  newNode.prev = last  // 设置新节点的前驱指针
}

// 打印链表内容
func (list *DoublyLinkedList) PrintList() {
  current := list.head
  for current != nil {
    fmt.Printf("%d <-> ", current.data)
    current = current.next  // 移动到下一个节点
  }
  fmt.Println("NULL")
}

func main() {
  list := &DoublyLinkedList{}
  list.Append(1)
  list.Append(2)
  list.Append(3)
  list.PrintList() // 输出：1 <-> 2 <-> 3 <-> NULL
}

/*
jarry@MacBook-Pro linked % go run doubly_linked.go
1 <-> 2 <-> 3 <-> NULL
*/
