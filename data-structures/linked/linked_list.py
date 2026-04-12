"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 
    本文件实现通用单向链表数据结构，使用Python面向对象编程。
    解决的问题：
    1. 动态数据存储 - 元素数量可自由增减，无需预先分配空间
    2. 高效插入删除 - 特别是在链表头部进行操作时仅需O(1)
    3. 简化内存管理 - Python自动垃圾回收，无需手动释放内存
    
    提供的功能：
    - insert_head/insert_tail: 在链表头部/尾部插入元素
    - delete: 删除指定值的节点
    - find: 查找指定值是否存在
    - print_list: 遍历并打印链表所有元素
    - get_size: 返回链表当前节点数量
    
    适用场景：算法学习、面试准备、需要频繁增删的数据处理
"""

# 节点类
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

# 链表类
class LinkedList:
    def __init__(self):
        self.head = None
        self._size = 0
    
    # 在头部插入
    def insert_head(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node
        self._size += 1
    
    # 在尾部插入
    def insert_tail(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
        self._size += 1
    
    # 删除节点
    def delete(self, data):
        if not self.head:
            return False
        
        if self.head.data == data:
            self.head = self.head.next
            self._size -= 1
            return True
        
        current = self.head
        while current.next and current.next.data != data:
            current = current.next
        
        if current.next:
            current.next = current.next.next
            self._size -= 1
            return True
        return False
    
    # 查找节点
    def find(self, data):
        current = self.head
        while current:
            if current.data == data:
                return True
            current = current.next
        return False
    
    # 打印链表
    def print_list(self):
        current = self.head
        while current:
            print(f"{current.data} -> ", end="")
            current = current.next
        print("NULL")
    
    # 获取链表大小
    def get_size(self):
        return self._size

# 测试
if __name__ == "__main__":
    lst = LinkedList()
    lst.insert_tail(1)
    lst.insert_tail(2)
    lst.insert_head(0)
    lst.insert_tail(3)
    
    print("链表内容:", end=" ")
    lst.print_list()
    print(f"链表大小: {lst.get_size()}")
    print(f"查找节点2: {'找到' if lst.find(2) else '未找到'}")
    
    print("删除节点2")
    lst.delete(2)
    print("链表内容:", end=" ")
    lst.print_list()
