class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None

class DoublyCircularLinkedList:
    def __init__(self):
        self.head = None

    def append(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            new_node.next = new_node
            new_node.prev = new_node
            return
        last = self.head
        while last.next != self.head:
            last = last.next
        last.next = new_node
        new_node.prev = last
        self.head.prev = new_node
        new_node.next = self.head

    def print_list(self):
        if not self.head:
            return
        current = self.head
        while True:
            print(f"{current.data} <-> ", end="")
            current = current.next
            if current == self.head:
                break
        print("(back to head)")

# 使用示例
dcll = DoublyCircularLinkedList()
dcll.append(1)
dcll.append(2)
dcll.append(3)
dcll.print_list()  # 输出：1 <-> 2 <-> 3 <-> (back to head)

"""
jarry@MacBook-Pro linked % python doubly_circular_linked.py
1 <-> 2 <-> 3 <-> (back to head)
"""