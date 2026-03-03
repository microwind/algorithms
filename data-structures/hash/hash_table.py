class HashTable:
    def __init__(self):
        self.table = [None] * 10

    def hash(self, key):
        return key % 10

    def insert(self, key, value):
        index = self.hash(key)
        if self.table[index] is None:
            self.table[index] = []
        for item in self.table[index]:
            if item[0] == key:
                item[1] = value  # 更新值
                return
        self.table[index].append([key, value])

    def search(self, key):
        index = self.hash(key)
        if self.table[index] is not None:
            for item in self.table[index]:
                if item[0] == key:
                    return item[1]
        return -1

    def delete(self, key):
        index = self.hash(key)
        if self.table[index] is not None:
            self.table[index] = [
                item for item in self.table[index] if item[0] != key]

    def print_table(self):
        for i, bucket in enumerate(self.table):
            if bucket:
                print(f"Index {i}: ", end="")
                print(" ".join([f"[{item[0]}:{item[1]}]" for item in bucket]))


hash_table = HashTable()

hash_table.insert(1, 100)
hash_table.insert(2, 200)
hash_table.insert(3, 300)

print("Search key 2:", hash_table.search(2))

hash_table.delete(2)
print("After deleting key 2:")
hash_table.print_table()

"""
jarry@MacBook-Pro hash % python hash_table.py 
Search key 2: 200
After deleting key 2:
Index 1: [1:100]
Index 3: [3:300]
"""
