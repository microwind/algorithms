class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class CircularLinkedList:
    def __init__(self):
        self.head = None

    def append(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            new_node.next = self.head
            return
        last = self.head
        while last.next != self.head:
            last = last.next
        last.next = new_node
        new_node.next = self.head

    def print_list(self):
        if not self.head:
            return
        current = self.head
        while True:
            print(f"{current.data} -> ", end="")
            current = current.next
            if current == self.head:
                break
        print("(back to head)")

# 使用示例
cll = CircularLinkedList()
cll.append(1)
cll.append(2)
cll.append(3)
cll.print_list()  # 输出：1 -> 2 -> 3 -> (back to head)

"""
jarry@MacBook-Pro linked % python circular_linked.py
1 -> 2 -> 3 -> (back to head)
"""