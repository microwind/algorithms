class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None

class DoublyLinkedList:
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
        new_node.prev = last

    def print_list(self):
        current = self.head
        while current:
            print(f"{current.data} <-> ", end="")
            current = current.next
        print("NULL")

# 使用示例
dll = DoublyLinkedList()
dll.append(1)
dll.append(2)
dll.append(3)
dll.print_list()  # 输出：1 <-> 2 <-> 3 <-> NULL

"""
jarry@MacBook-Pro linked % python doubly_linked.py 
1 <-> 2 <-> 3 <-> NULL
"""