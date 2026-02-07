class Set:
    INITIAL_CAPACITY = 16  # 初始哈希表容量
    LOAD_FACTOR = 0.75  # 负载因子

    def __init__(self):
        self.capacity = Set.INITIAL_CAPACITY
        self.size = 0
        self.buckets = [[] for _ in range(self.capacity)]  # 初始化哈希桶数组，每个桶是一个列表

    # FNV-1a 哈希函数（用于计算哈希值）
    def fnv_hash(self, key):
        hash = 2166136261  # 初始哈希值
        for byte in str(key).encode('utf-8'):  # 将 key 转为字符串并计算每个字节的哈希值
            hash ^= byte
            hash *= 16777619
        return hash & 0xFFFFFFFF  # 强制转换为无符号整数

    # 扩容 Set
    def resize(self):
        new_capacity = self.capacity * 2
        new_buckets = [[] for _ in range(new_capacity)]

        # 重新哈希所有元素
        for i in range(self.capacity):
            for key in self.buckets[i]:
                new_index = self.fnv_hash(key) % new_capacity
                new_buckets[new_index].append(key)

        # 更新容量和桶数组
        self.capacity = new_capacity
        self.buckets = new_buckets

    # 添加元素到 Set
    def add(self, key):
        # python无需扩容
        # 判断是否需要扩容
        if self.size / self.capacity > Set.LOAD_FACTOR:
            self.resize()  # 扩容

        index = self.fnv_hash(key) % self.capacity
        bucket = self.buckets[index]

        # 查找桶中是否已经有相同的元素
        if key in bucket:
            print(f"Exist node: index={index} key={key}")
            return  # 已存在则不添加

        # 没有找到相同的元素，进行插入
        bucket.append(key)
        self.size += 1

        # 打印调试信息：打印插入后的 node
        print(f"Adding node: index={index} key={key}")

    # 检查元素是否在 Set 中
    def contains(self, key):
        index = self.fnv_hash(key) % self.capacity
        return key in self.buckets[index]

    # 删除元素
    def remove(self, key):
        index = self.fnv_hash(key) % self.capacity
        bucket = self.buckets[index]

        if key in bucket:
            bucket.remove(key)
            self.size -= 1
            print(f"Removed node: key={key}")

    # 获取 Set 中的元素个数
    def size(self):
        return self.size

    # 遍历 Set 并打印元素
    def print(self):
        for i in range(self.capacity):
            for key in self.buckets[i]:
                print(key)

# 测试
set = Set()
values = [10, 20, 20, 30, 40, 40, 50]

# 添加元素
for value in values:
    set.add(value)

# 打印 Set 内容
set.print()

# 检查元素是否存在
print("Contains 30?", set.contains(30))

# 删除元素
set.remove(30)
set.print()
# print("set:", set)

"""
jarry@MacBook-Pro set % python set.py
Adding node: index=4 key=10
Adding node: index=15 key=20
Exist node: index=15 key=20
Adding node: index=6 key=30
Adding node: index=9 key=40
Exist node: index=9 key=40
Adding node: index=0 key=50
50
10
30
40
20
Contains 30? True
Removed node: key=30
50
10
40
20
"""
