/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description:
 *  双向循环链表基础实现（Go）
 *  功能：结合双向链表和循环链表特性，支持双向循环遍历
 *  用途：学习最复杂的链表结构，实现高级调度算法
 */

package main

import "fmt"

// 节点结构体
type Node struct {
  data int     // 节点数据
  next *Node   // 指向下一个节点
  prev *Node   // 指向上一个节点
}

// 双向循环链表结构体
type DoublyCircularLinkedList struct {
  head *Node
}

// 向链表尾部添加节点
func (list *DoublyCircularLinkedList) Append(data int) {
  newNode := &Node{data: data}
  if list.head == nil {
    list.head = newNode  // 链表为空，新节点作为头节点
    newNode.next = newNode  // 指向自己，形成环
    newNode.prev = newNode  // 指向自己，形成环
    return
  }
  last := list.head
  for last.next != list.head {
    last = last.next  // 找到最后一个节点（其next指向头节点）
  }
  last.next = newNode  // 将新节点链接到尾部
  newNode.prev = last  // 设置新节点的前驱指针
  list.head.prev = newNode  // 更新头节点的前驱指针
  newNode.next = list.head  // 新节点的next指向头节点，维持环状结构
}

// 打印链表内容
func (list *DoublyCircularLinkedList) PrintList() {
  if list.head == nil {
    return
  }
  current := list.head
  for {
    fmt.Printf("%d <-> ", current.data)
    current = current.next  // 移动到下一个节点
    if current == list.head {  // 循环直到回到头节点
      break
    }
  }
  fmt.Println("(back to head)")
}

func main() {
  list := &DoublyCircularLinkedList{}
  list.Append(1)
  list.Append(2)
  list.Append(3)
  list.PrintList()
}

/*
jarry@MacBook-Pro linked % go run doubly_circular_linked.go
1 <-> 2 <-> 3 <-> (back to head)
*/
