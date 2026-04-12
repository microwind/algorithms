"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 
    双向循环链表基础实现（Python）
    功能：结合双向链表和循环链表特性，支持双向循环遍历
    用途：学习最复杂的链表结构，实现双向循环队列等场景
"""

# 节点类
class Node:
    def __init__(self, data):
        self.data = data      # 节点数据
        self.next = None    # 指向下一个节点
        self.prev = None    # 指向上一个节点

# 双向循环链表类
class DoublyCircularLinkedList:
    def __init__(self):
        self.head = None

    # 向链表尾部添加节点
    def append(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node  # 链表为空，新节点作为头节点
            new_node.next = new_node  # 指向自己，形成环
            new_node.prev = new_node  # 指向自己，形成环
            return
        last = self.head
        while last.next != self.head:
            last = last.next  # 找到最后一个节点（其next指向头节点）
        last.next = new_node  # 将新节点链接到尾部
        new_node.prev = last  # 设置新节点的前驱指针
        self.head.prev = new_node  # 更新头节点的前驱指针
        new_node.next = self.head  # 新节点的next指向头节点，维持环状结构

    # 打印链表内容
    def print_list(self):
        if not self.head:
            return
        current = self.head
        while True:
            print(f"{current.data} <-> ", end="")
            current = current.next  # 移动到下一个节点
            if current == self.head:  # 循环直到回到头节点
                break
        print("(back to head)")

dcll = DoublyCircularLinkedList()
dcll.append(1)
dcll.append(2)
dcll.append(3)
dcll.print_list()

"""
jarry@MacBook-Pro linked % python doubly_circular_linked.py
1 <-> 2 <-> 3 <-> (back to head)
"""