# 一致哈希负载均衡 | Consistent Hashing

**难度**: ⭐⭐⭐⭐ | **标签**: `分布式` `负载均衡` `哈希环`

实现分布式系统中的负载均衡和数据分布算法。

## 项目简介

一致哈希是分布式系统的核心算法。本项目展示如何实现：
- 一致哈希环（Consistent Hashing Ring）
- 分布式缓存系统
- 负载均衡器
- 数据副本分布

## 核心概念

### 一致哈希 vs 普通哈希

| 特性 | 普通哈希 | 一致哈希 |
|------|---------|---------|
| 添加服务器 | 100%重新分配 | ~1/K 重新分配 |
| 删除服务器 | 100%重新分配 | ~1/K 重新分配 |
| 热点问题 | 严重 | 虚拟节点可解决 |
| 复杂度 | O(1) | O(log N) |

### 虚拟节点的作用

```
不使用虚拟节点:
  [server1] --------- [server2]
        300个key         50个key
  分布不均，server1过载

使用虚拟节点:
  [server1:0] [server1:1] [server1:2]
  [server2:0] [server2:1] [server2:2]
  均匀分布到哈希环上
```

## 实际应用场景

### 1. 分布式缓存

```python
cache = DistributedCache(replicas=3)

# 添加缓存服务器
cache.add_server("cache1")
cache.add_server("cache2")
cache.add_server("cache3")

# 存储数据
for i in range(30):
    cache.set(f"user_{i}", f"userData_{i}")

# 数据自动分布到3个服务器
cache.print_distribution()
# cache1: 10条 (33%)
# cache2: 10条 (33%)
# cache3: 10条 (34%)
```

**优势**:
- 自动分布，无需中央协调
- 服务器扩缩容时，只需迁移部分数据
- 避免单点过载

### 2. 负载均衡

```python
lb = LoadBalancer(replicas=3)

# 配置服务器池
for i in range(1, 4):
    lb.add_server(f"server{i}")

# 路由请求
for i in range(1000):
    request_id = f"req_{i}"
    server = lb.route_request(request_id)
    # 相同request_id总是路由到同一服务器
    # 支持会话保持 (sticky session)

lb.print_load_balance_stats()
# server1: 314 请求 (31.4%)
# server2: 397 请求 (39.7%)  <- 略有不均
# server3: 289 请求 (28.9%)
```

**应用**:
- 会话保持（用户请求总到同一服务器）
- 缓存亲和性（减少缓存失效）
- 连接复用

### 3. 服务器扩展

```python
# 初始配置：3个服务器
cache = DistributedCache(replicas=3)
for server in ["cache1", "cache2", "cache3"]:
    cache.add_server(server)

# 存储30条数据
for i in range(30):
    cache.set(f"user_{i}", f"data_{i}")

print("扩展前：")
cache.print_distribution()
# cache1: 10条  cache2: 10条  cache3: 10条

# 添加新服务器
cache.add_server("cache4")

# 新数据自动分布
cache2 = DistributedCache(replicas=3)
for server in ["cache1", "cache2", "cache3", "cache4"]:
    cache2.add_server(server)
for i in range(30):
    cache2.set(f"user_{i}", f"data_{i}")

print("\n扩展后：")
cache2.print_distribution()
# cache1: 8条  cache2: 7条  cache3: 8条  cache4: 7条
# ✅ 只有 ~25% 数据需要迁移！
```

### 4. 数据副本分布

```python
replicas = ConsistentHashWithReplicas(replicas=3, backup_replicas=2)

replicas.add_node("db1")
replicas.add_node("db2")
replicas.add_node("db3")

# 每个key有2个备份
for key in ["user_1", "user_2", "user_3"]:
    nodes = replicas.get_replicas(key)
    print(f"{key}: 存储在 {nodes}")
    # user_1: 存储在 ['db2', 'db1']  (主库和副本)
    # user_2: 存储在 ['db3', 'db1']
```

**高可用**:
- 主库故障，自动切换到副本
- 多副本写入保证数据安全

## 项目结构

```
04-consistent-hashing/
├── README.md
├── docs/
│   ├── DESIGN.md
│   └── PERFORMANCE.md
├── src/
│   └── python/
│       └── consistent_hashing.py
├── tests/
│   └── test_consistent_hashing.py
└── requirements.txt
```

## 使用指南

### Python 版本

```bash
# 运行示例
python3 src/python/consistent_hashing.py

# 使用 API
from consistent_hashing import ConsistentHash

# 创建哈希环
ch = ConsistentHash(replicas=3)

# 添加节点
ch.add_node("server1")
ch.add_node("server2")

# 查找节点
server = ch.get_node("user_123")

# 获取多个副本
servers = ch.get_nodes("user_123", n=2)
```

## 性能分析

### 节点操作时间

| 操作 | 时间复杂度 | 说明 |
|------|---------|------|
| 添加节点 | O(log N + R) | N=节点数，R=副本数 |
| 删除节点 | O(log N + R) | 需要更新虚拟节点 |
| 查找节点 | O(log N) | 二分查找哈希环 |

### 数据迁移量

| 操作 | 迁移数据 | 传统哈希 |
|------|---------|--------|
| 添加1个节点（3→4） | 25% | 100% |
| 添加1个节点（10→11） | 9% | 100% |
| 删除1个节点（10→9） | 11% | 100% |

### 负载均衡效果

| 副本数 | 负载标准差 | 均衡度 |
|--------|----------|--------|
| 1 | 24% | ⚠️ 较差 |
| 3 | 8% | ✅ 良好 |
| 5 | 4% | ✅ 很好 |
| 10 | 2% | ✅ 优秀 |

**结论**: 副本数越多，分布越均匀，但CPU和内存成本增加

## 核心API

### Python

```python
# 基础一致哈希
ch = ConsistentHash(replicas=3)
ch.add_node(node)
ch.remove_node(node)
ch.get_node(key)                    # 获取单个节点
ch.get_nodes(key, n=1)              # 获取n个节点

# 分布式缓存
cache = DistributedCache(replicas=3)
cache.add_server(server)
cache.remove_server(server)
cache.set(key, value)
cache.get(key)
cache.get_distribution()            # 获取分布统计

# 负载均衡器
lb = LoadBalancer(replicas=3)
lb.add_server(server)
lb.route_request(request_id)        # 路由请求
lb.get_load_balance_stats()         # 获取统计

# 副本管理
replicas = ConsistentHashWithReplicas(replicas=3, backup_replicas=2)
replicas.add_node(node)
replicas.get_replicas(key)          # 获取副本列表
```

## 高级主题

### 1. 加权负载均衡

处理异构服务器（性能不同）：
```python
# 高性能服务器权重大
servers = {
    "server1": weight=3,  # 处理3倍流量
    "server2": weight=1,
}
```

### 2. 热点检测和处理

某些key访问特别频繁：
```python
# 检测热点key
if access_count[key] > threshold:
    # 增加虚拟节点数量
    add_extra_replicas(key)
```

### 3. 跳表优化

代替二分查找，性能更好：
```python
# 使用跳表代替有序数组
# 查询：O(log N) → O(log N)，但常数更小
# 添加：O(N) → O(log N)
```

## 最佳实践

✅ **DO**:
- 使用虚拟节点改善分布
- 监控负载均衡效果
- 定期检查数据迁移
- 保留历史统计数据

❌ **DON'T**:
- 副本数过多（性能下降）
- 忽视故障检测
- 不做容量规划
- 过度优化（过早优化是万恶之源）

## 常见问题

**Q: 副本数应该设多少？**

A:
- 副本数=3：推荐值，性能和均衡的平衡点
- 副本数=5：高并发场景
- 副本数>10：一般不需要

**Q: 一致哈希在Redis集群中如何应用？**

A:
```
Key "user:123"
  ↓
hash("user:123") = 12345
  ↓
在哈希环上找到 node_3
  ↓
连接 node_3 执行命令
```

**Q: 与主从复制的区别？**

A:
- 一致哈希：**水平扩展**，数据分散到多个节点
- 主从复制：**垂直扩展**，数据副本在不同节点

## 扩展练习

1. 实现**加权一致哈希** - 支持异构服务器
2. 实现**跳表优化** - 替代二分查找
3. 实现**故障转移** - 自动检测和处理故障
4. 实现**数据迁移** - 自动计算和执行迁移

## 相关资源

- [Consistent Hashing 论文](https://www.akamai.com/us/en/multimedia/documents/technical-publication-consistent-hashing-and-random-trees-technical-publication-pdf.pdf)
- [Redis Cluster 实现](https://redis.io/topics/cluster-tutorial)
- [Memcached 分布式](https://memcached.org/)

---

**最后更新**: 2024-03-02
**作者**: Algorithm Team
**License**: MIT
