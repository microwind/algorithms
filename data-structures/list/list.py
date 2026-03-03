class List:
    def __init__(self):
        self.capacity = 10
        self.data = [None] * self.capacity
        self.size = 0

    def resize(self, new_capacity):
        if new_capacity > self.capacity:
            new_data = [None] * new_capacity
            for i in range(self.size):
                new_data[i] = self.data[i]
            self.data = new_data
            self.capacity = new_capacity

    def add(self, value):
        # Python 数组会自动扩容，实际无需resize，这里只是为了演示
        if self.size == self.capacity:
            self.resize(self.capacity * 2)
        # self.data.append(value)
        self.data[self.size] = value
        self.size += 1

    def remove(self):
        if self.size > 0:
            self.size -= 1

    def get(self, index):
        if index < 0 or index >= self.size:
            raise IndexError("Index out of range")
        return self.data[index]

    def size(self):
        return self.size

    def capacity(self):
        return self.capacity

    def print_list(self):
        print("List:", self.data[:self.size])

# 使用示例
lst = List()
lst.add(10)
lst.add(20)
lst.add(30)
lst.print_list()  # List: [10, 20, 30]

print("Element at index 1:", lst.get(1))  # 20

lst.remove()
lst.print_list()  # List: [10, 20]

print("Size:", lst.size)  # 2
print("Capacity:", lst.capacity)  # 10

lst.resize(20)
print("New Capacity:", lst.capacity)  # 20

"""
jarry@MacBook-Pro list % python list.py 
List: [10, 20, 30]
Element at index 1: 20
List: [10, 20]
Size: 2
Capacity: 10
New Capacity: 20
"""