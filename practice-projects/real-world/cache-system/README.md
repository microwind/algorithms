# 缓存系统 | Cache System

**难度**: ⭐⭐ | **标签**: `数据结构` `缓存` `性能优化`

实现高效的缓存系统，包括 LRU 缓存和超时缓存。

## 项目简介

缓存是现代应用系统的重要组件。本项目展示如何实现：
- LRU（最近最少使用）缓存
- 超时自动过期的缓存系统
- 内存有效管理
- 快速查询和更新

## 核心概念

### LRU 缓存原理

```
插入顺序：get(1) → put(2) → get(1) → put(3)

LRU 缓存（容量为2）：
步骤1: put(1,'a')      →  [1]
步骤2: get(1)          →  [1] (1 移到末尾)
步骤3: put(2,'b')      →  [1, 2]
步骤4: get(1)          →  [2, 1] (1 移到末尾)
步骤5: put(3,'c')      →  [1, 3] (2 被淘汰 - 最近最少使用)
```

### 特点对比

| 特性 | HashMap | LRU缓存 | 超时缓存 |
|------|--------|--------|--------|
| 查询速度 | O(1) | O(1) | O(1) |
| 空间管理 | 无限增长 | 固定容量 | 自动清理 |
| 淘汰策略 | 无 | LRU | TTL过期 |
| 应用场景 | 一般数据 | CPU缓存 | 会话存储 |

## 实现特性

### LRU缓存
- **快速访问**：使用 HashMap 实现 O(1) 查询
- **顺序管理**：LinkedHashMap 或 OrderedDict 维护访问顺序
- **容量限制**：超出容量时自动淘汰最少使用的元素

### 超时缓存
- **TTL支持**：每个值都有过期时间
- **自动清理**：访问时检查是否过期
- **灵活配置**：可设置不同的超时时间

## 应用场景
- 数据库查询缓存
- CPU 缓存模拟
- 会话存储
- CDN 缓存
- Web 浏览器缓存

## 简单例子

### Python 示例 - LRU缓存

```python
from collections import OrderedDict

class LRUCache:
    """LRU 缓存系统"""
    def __init__(self, capacity):
        self.cache = OrderedDict()
        self.capacity = capacity

    def get(self, key):
        if key not in self.cache:
            return -1
        # 移到末尾（标记为最近使用）
        self.cache.move_to_end(key)
        return self.cache[key]

    def put(self, key, value):
        if key in self.cache:
            self.cache.move_to_end(key)
        self.cache[key] = value
        # 超出容量时删除最旧的
        if len(self.cache) > self.capacity:
            self.cache.popitem(last=False)

# 使用示例
lru = LRUCache(2)
lru.put(1, 'a')
lru.put(2, 'b')
print(lru.get(1))    # 返回 'a'，1 变成最近使用
lru.put(3, 'c')      # 容量满，删除 2
print(lru.get(2))    # 返回 -1（已淘汰）
```

### Python 示例 - 超时缓存

```python
import time

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
                # 过期时自动删除
                del self.cache[key]
                del self.expiry[key]
        return None

# 使用示例
tc = TimedCache()
tc.set('token', 'abc123', ttl=3600)  # 1小时后过期
print(tc.get('token'))   # 返回 'abc123'
```

## 复杂度分析

| 操作 | LRU缓存 | 超时缓存 |
|------|--------|--------|
| get | O(1) | O(1) |
| put | O(1) | O(1) |
| 空间 | O(capacity) | O(n) |

## 工程实现建议

### 1. 并发安全
```python
import threading
lock = threading.Lock()

def thread_safe_get(self, key):
    with lock:
        return self.get(key)
```

### 2. 持久化
```python
import pickle

def save_cache(self, filename):
    with open(filename, 'wb') as f:
        pickle.dump(self.cache, f)

def load_cache(self, filename):
    with open(filename, 'rb') as f:
        self.cache = pickle.load(f)
```

### 3. 监控指标
```python
class MonitoredCache:
    def __init__(self):
        self.hits = 0
        self.misses = 0

    def hit_rate(self):
        total = self.hits + self.misses
        return self.hits / total if total > 0 else 0
```

## 常见问题

**Q: LRU 缓存与 LFU 缓存有什么区别？**

A:
- LRU（最近最少使用）：淘汰最久未使用的项
- LFU（最不经常使用）：淘汰使用频率最低的项

LFU 更智能但实现更复杂。

**Q: 超时缓存如何防止内存泄漏？**

A:
1. 访问时主动清理过期项
2. 定时后台清理线程
3. 限制缓存大小

## 学习建议
1. 先实现基础的 LRU 缓存，理解 OrderedDict 的使用
2. 再加入超时功能，学会时间管理
3. 考虑多线程安全问题
4. 对比不同实现的性能差异
