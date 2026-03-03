class Map:
    def __init__(self):
        self.entries = []
        self.size = 0
        self.capacity = 10

    # 重新分配容量
    def resize_map(self, new_capacity):
        self.capacity = new_capacity

    # 插入键值对（如果存在则更新）
    def put(self, key, value):
        for entry in self.entries:
            if entry['key'] == key:
                entry['value'] = value  # 更新值
                return
        if self.size >= self.capacity:
            self.resize_map(self.capacity * 2)
        self.entries.append({'key': key, 'value': value})
        self.size += 1

    # 查找键
    def get(self, key):
        for entry in self.entries:
            if entry['key'] == key:
                return entry['value']
        return -1  # 未找到

    # 删除键
    def delete(self, key):
        for i in range(self.size):
            if self.entries[i]['key'] == key:
                self.entries.pop(i)
                self.size -= 1
                return


# 测试
map = Map()

map.put("apple", 10)
map.put("banana", 20)
map.put("orange", 30)

print("apple:", map.get("apple"))
print("banana:", map.get("banana"))
print("grape:", map.get("grape"))

map.delete("banana")
print("banana after delete:", map.get("banana"))

"""
jarry@MacBook-Pro map % python map.py 
apple: 10
banana: 20
grape: -1
banana after delete: -1
"""
