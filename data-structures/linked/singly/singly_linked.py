"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 
    单向链表基础实现（Python）
    功能：节点插入、链表遍历、打印输出
    用途：算法入门学习，面试准备
"""

# 节点类
class Node:
    def __init__(self, data):
        self.data = data      # 节点数据
        self.next = None    # 指向下一个节点

class SinglyLinkedList:
    def __init__(self):
        self.head = None

    # 向链表尾部添加节点
    def append(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node  # 链表为空，新节点作为头节点
            return
        last = self.head
        while last.next:
            last = last.next  # 找到最后一个节点
        last.next = new_node  # 将新节点链接到尾部

    # 打印链表内容
    def print_list(self):
        current = self.head
        while current:
            print(f"{current.data} -> ", end="")
            current = current.next  # 移动到下一个节点
        print("NULL")

linked_list = SinglyLinkedList()
linked_list.append(1)
linked_list.append(2)
linked_list.append(3)
linked_list.print_list()

"""
jarry@MacBook-Pro linked % python singly_linked.py
1 -> 2 -> 3 -> NULL
"""