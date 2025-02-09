class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class SinglyLinkedList:
    def __init__(self):
        self.head = None

    def append(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            return
        last = self.head
        while last.next:
            last = last.next
        last.next = new_node

    def print_list(self):
        current = self.head
        while current:
            print(f"{current.data} -> ", end="")
            current = current.next
        print("NULL")

# 使用示例
linked_list = SinglyLinkedList()
linked_list.append(1)
linked_list.append(2)
linked_list.append(3)
linked_list.print_list()  # 输出：1 -> 2 -> 3 -> NULL

"""
jarry@MacBook-Pro linked % python singly_linked.py
1 -> 2 -> 3 -> NULL
"""