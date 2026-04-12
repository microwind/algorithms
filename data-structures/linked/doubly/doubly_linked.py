"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 
    双向链表基础实现（Python）
    功能：支持双向遍历的链表，包含prev和next指针
    用途：学习双向链表，实现音乐播放列表等功能
"""

# 节点类
class Node:
    def __init__(self, data):
        self.data = data      # 节点数据
        self.next = None    # 指向下一个节点
        self.prev = None    # 指向上一个节点

# 双链表类
class DoublyLinkedList:
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
        new_node.prev = last  # 设置新节点的前驱指针

    # 打印链表内容
    def print_list(self):
        current = self.head
        while current:
            print(f"{current.data} <-> ", end="")
            current = current.next  # 移动到下一个节点
        print("NULL")

dll = DoublyLinkedList()
dll.append(1)
dll.append(2)
dll.append(3)
dll.print_list()

"""
jarry@MacBook-Pro linked % python doubly_linked.py 
1 <-> 2 <-> 3 <-> NULL
"""