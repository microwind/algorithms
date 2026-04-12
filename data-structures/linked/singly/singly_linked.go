/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description:
 *  单向链表基础实现（Go）
 *  功能：节点追加、链表打印
 *  用途：学习Go语言指针操作，链表基础概念
 */

package main

import "fmt"

// 节点结构体
type Node struct {
  data int     // 节点数据
  next *Node   // 指向下一个节点
}

// 单链表结构体
type SinglyLinkedList struct {
  head *Node
}

// 向链表尾部添加节点
func (list *SinglyLinkedList) Append(data int) {
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
}

// 打印链表内容
func (list *SinglyLinkedList) PrintList() {
  current := list.head
  for current != nil {
    fmt.Printf("%d -> ", current.data)
    current = current.next  // 移动到下一个节点
  }
  fmt.Println("NULL")
}

func main() {
  list := &SinglyLinkedList{}
  list.Append(1)
  list.Append(2)
  list.Append(3)
  list.PrintList()
}

/*
jarry@MacBook-Pro linked % go run singly_linked.go
1 -> 2 -> 3 -> NULL
*/
