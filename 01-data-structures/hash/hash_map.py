INITIAL_CAPACITY = 10
LOAD_FACTOR = 0.75

class Entry:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None

class HashMap:
    def __init__(self):
        self.size = 0
        self.capacity = INITIAL_CAPACITY
        self.table = [None] * self.capacity

    def hash(self, key):
        hash_value = 0
        for char in key:
            hash_value = (hash_value * 31) + ord(char)
        return hash_value % self.capacity

    def resize(self):
        # py list无需动态扩容
        new_capacity = self.capacity * 2
        new_table = [None] * new_capacity

        for i in range(self.capacity):
            entry = self.table[i]
            while entry:
                new_index = self.hash(entry.key) % new_capacity
                new_entry = Entry(entry.key, entry.value)
                new_entry.next = new_table[new_index]
                new_table[new_index] = new_entry
                entry = entry.next

        self.table = new_table
        self.capacity = new_capacity

    def put(self, key, value):
        if self.size / self.capacity > LOAD_FACTOR:
            self.resize()

        index = self.hash(key)
        entry = self.table[index]

        while entry:
            if entry.key == key:
                entry.value = value
                return
            entry = entry.next

        new_entry = Entry(key, value)
        new_entry.next = self.table[index]
        self.table[index] = new_entry
        self.size += 1

    def get(self, key):
        index = self.hash(key)
        entry = self.table[index]
        while entry:
            if entry.key == key:
                return entry.value
            entry = entry.next
        return -1

    def delete(self, key):
        index = self.hash(key)
        entry = self.table[index]
        prev = None

        while entry:
            if entry.key == key:
                if prev:
                    prev.next = entry.next
                else:
                    self.table[index] = entry.next
                self.size -= 1
                return
            prev = entry
            entry = entry.next

# 测试
map_obj = HashMap()
map_obj.put("apple", 10)
map_obj.put("banana", 20)
map_obj.put("orange", 30)

print("apple:", map_obj.get("apple"))
print("banana:", map_obj.get("banana"))
print("grape:", map_obj.get("grape"))

map_obj.delete("banana")
print("banana after delete:", map_obj.get("banana"))

"""
jarry@MacBook-Pro hash % python hash_map.py 
apple: 10
banana: 20
grape: -1
banana after delete: -1
"""