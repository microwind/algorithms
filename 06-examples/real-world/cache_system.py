"""
实际应用：缓存系统实现
"""

from collections import OrderedDict
import time

class LRUCache:
    """LRU 缓存系统"""
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

class TimedCache:
    """带过期时间的缓存"""
    def __init__(self):
        self.cache = {}
        self.expiry = {}
    
    def set(self, key, value, ttl):
        self.cache[key] = value
        self.expiry[key] = time.time() + ttl
    
    def get(self, key):
        if key in self.cache:
            if time.time() < self.expiry[key]:
                return self.cache[key]
            else:
                del self.cache[key]
                del self.expiry[key]
        return None

if __name__ == "__main__":
    print("=== 缓存系统示例 ===\n")
    
    # LRU 缓存
    lru = LRUCache(2)
    lru.put(1, 'a')
    lru.put(2, 'b')
    print(f"LRU get(1): {lru.get(1)}")
    lru.put(3, 'c')
    print(f"LRU get(2): {lru.get(2)}")
