"""
面试题集合

常见的技术面试问题和解答
"""

# 1. LRU 缓存
from collections import OrderedDict

class LRUCache:
    """LRU（最近最少使用）缓存"""
    def __init__(self, capacity):
        self.cache = OrderedDict()
        self.capacity = capacity
    
    def get(self, key):
        if key not in self.cache:
            return -1
        self.cache.move_to_end(key)
        return self.cache[key]
    
    def put(self, key, value):
        if key in self.cache:
            self.cache.move_to_end(key)
        self.cache[key] = value
        if len(self.cache) > self.capacity:
            self.cache.popitem(last=False)

# 2. 单例模式
class Singleton:
    """单例模式实现"""
    _instance = None
    
    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance

# 3. 生产者消费者问题
import threading

class ProducerConsumer:
    """生产者消费者问题"""
    def __init__(self, buffer_size):
        self.buffer = []
        self.buffer_size = buffer_size
        self.lock = threading.Lock()
        self.empty = threading.Condition(self.lock)
        self.full = threading.Condition(self.lock)
    
    def produce(self, item):
        with self.lock:
            while len(self.buffer) >= self.buffer_size:
                self.full.wait()
            self.buffer.append(item)
            print(f"生产: {item}")
            self.empty.notify()
    
    def consume(self):
        with self.lock:
            while len(self.buffer) == 0:
                self.empty.wait()
            item = self.buffer.pop(0)
            print(f"消费: {item}")
            self.full.notify()
            return item

# 4. 数据库连接池
class ConnectionPool:
    """简单的连接池实现"""
    def __init__(self, size):
        self.pool = [f"Connection_{i}" for i in range(size)]
        self.available = threading.Semaphore(size)
        self.lock = threading.Lock()
    
    def acquire(self):
        self.available.acquire()
        with self.lock:
            return self.pool.pop()
    
    def release(self, conn):
        with self.lock:
            self.pool.append(conn)
        self.available.release()

if __name__ == "__main__":
    print("=== 面试题集合 ===\n")
    
    print("1. LRU 缓存")
    cache = LRUCache(2)
    cache.put(1, 1)
    cache.put(2, 2)
    print(f"get(1): {cache.get(1)}")
    
    print("\n2. 单例模式")
    s1 = Singleton()
    s2 = Singleton()
    print(f"s1 is s2: {s1 is s2}")
