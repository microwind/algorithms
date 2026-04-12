/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description:
 *  本文件实现通用单向链表数据结构，使用Go语言结构体和方法。
 *  解决的问题：
 *  1. 动态数据存储 - 元素数量可自由增减，无需像数组那样预先分配空间
 *  2. 高效插入删除 - 特别是在链表头部进行操作时仅需O(1)时间
 *  3. 内存自动管理 - Go垃圾回收机制自动处理不再使用的节点
 *
 *  提供的功能：
 *  - InsertHead/InsertTail: 在链表头部/尾部插入元素
 *  - Delete: 删除指定值的节点
 *  - Find: 查找指定值是否存在
 *  - PrintList: 遍历并打印链表所有元素
 *  - GetSize: 返回链表当前节点数量
 *
 *  适用场景：需要频繁增删元素、数据量动态变化、无需随机访问的场景
 */

package main

import "fmt"

// 节点结构体
type Node struct {
	data int
	next *Node
}

// 链表结构体
type LinkedList struct {
	head *Node
	size int
}

// 创建链表
func NewLinkedList() *LinkedList {
	return &LinkedList{head: nil, size: 0}
}

// 在头部插入
func (list *LinkedList) InsertHead(data int) {
	newNode := &Node{data: data, next: list.head}
	list.head = newNode
	list.size++
}

// 在尾部插入
func (list *LinkedList) InsertTail(data int) {
	newNode := &Node{data: data, next: nil}
	if list.head == nil {
		list.head = newNode
	} else {
		current := list.head
		for current.next != nil {
			current = current.next
		}
		current.next = newNode
	}
	list.size++
}

// 删除节点
func (list *LinkedList) Delete(data int) bool {
	if list.head == nil {
		return false
	}

	if list.head.data == data {
		list.head = list.head.next
		list.size--
		return true
	}

	current := list.head
	for current.next != nil && current.next.data != data {
		current = current.next
	}

	if current.next != nil {
		current.next = current.next.next
		list.size--
		return true
	}
	return false
}

// 查找节点
func (list *LinkedList) Find(data int) bool {
	current := list.head
	for current != nil {
		if current.data == data {
			return true
		}
		current = current.next
	}
	return false
}

// 打印链表
func (list *LinkedList) PrintList() {
	current := list.head
	for current != nil {
		fmt.Printf("%d -> ", current.data)
		current = current.next
	}
	fmt.Println("NULL")
}

// 获取链表大小
func (list *LinkedList) GetSize() int {
	return list.size
}

func main() {
	list := NewLinkedList()

	list.InsertTail(1)
	list.InsertTail(2)
	list.InsertHead(0)
	list.InsertTail(3)

	fmt.Print("链表内容: ")
	list.PrintList()
	fmt.Printf("链表大小: %d\n", list.GetSize())

	fmt.Printf("查找节点2: %v\n", list.Find(2))

	fmt.Println("删除节点2")
	list.Delete(2)
	fmt.Print("链表内容: ")
	list.PrintList()
}
