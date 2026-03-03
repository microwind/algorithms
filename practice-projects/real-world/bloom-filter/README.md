# 布隆过滤器系统 | Bloom Filter

**难度**: ⭐⭐⭐ | **标签**: `概率数据结构` `大数据` `去重`

用布隆过滤器实现高效的大规模数据去重和检测。

## 项目简介

布隆过滤器是处理大规模数据的利器。本项目展示如何实现：
- URL爬虫去重（避免重复爬取）
- IP黑名单过滤（快速检测恶意IP）
- 缓存穿透防护（防止数据库击穿）
- 垃圾邮件过滤

## 核心概念

### 布隆过滤器原理

```
添加元素 "apple":
  hash1("apple") = 3  → bit[3] = 1
  hash2("apple") = 7  → bit[7] = 1
  hash3("apple") = 11 → bit[11] = 1

检查元素 "apple":
  hash1("apple") = 3  → bit[3] = 1 ✓
  hash2("apple") = 7  → bit[7] = 1 ✓
  hash3("apple") = 11 → bit[11] = 1 ✓
  结果：可能存在

检查元素 "orange":
  hash1("orange") = 3  → bit[3] = 1 ✓
  hash2("orange") = 4  → bit[4] = 0 ✗
  结果：一定不存在
```

### 布隆过滤器 vs Set

| 特性 | Set | 布隆过滤器 |
|------|-----|----------|
| 空间占用 | O(n) | O(1) |
| 时间复杂度 | O(1) | O(1) |
| 误判率 | 0% | <1% |
| 删除元素 | 支持 | 不支持 |
| 适用场景 | 小数据量 | 大数据量 |

## 实际应用场景

### 1. 爬虫URL去重

```python
crawler = URLCrawlerFilter(expected_urls=1000000)

# 爬取URL
urls = [f"http://example.com/page_{i}" for i in range(100)]

# 第一次爬取
for url in urls:
    if not crawler.is_crawled(url):
        crawler.mark_crawled(url)
        # 爬取内容...

# 第二次爬取（检测重复）
for url in urls[:50]:
    if not crawler.is_crawled(url):
        # 重新爬取
    else:
        print(f"跳过已爬URL: {url}")

stats = crawler.get_statistics()
# 去重率: 33.33%
# 节省网络流量和存储空间
```

**优势**:
- 只需 100KB 内存存储 100 万个 URL
- O(1) 快速检查
- <0.1% 误判率（极少重新爬一次）

### 2. IP黑名单过滤

```python
ip_filter = IpBlocklistFilter(expected_ips=1000000)

# 添加黑名单IP
blacklist = ["192.168.1.1", "10.0.0.1", "172.16.0.1"]
for ip in blacklist:
    ip_filter.add_blocked_ip(ip)

# 检查IP
test_ips = ["192.168.1.1", "192.168.1.100", "10.0.0.1"]

for ip in test_ips:
    if ip_filter.is_blocked(ip):
        print(f"❌ 拒绝: {ip}")
    else:
        print(f"✅ 允许: {ip}")
```

**应用**:
- 防火墙规则
- DDoS防护
- 风控系统

**性能**:
```
检查时间: <1μs
内存占用: 125KB (100万IP)
误判率: 0.1%
```

### 3. 缓存穿透防护

```python
cache_guard = CacheAvalanchePrevention(expected_items=100000)

# 初始化：添加存在的数据key
valid_keys = ["user_1", "user_2", "user_3", ...]
for key in valid_keys:
    cache_guard.add_key(key)

# 查询时先用布隆过滤器检查
def get_user(user_id):
    if not cache_guard.query_exists(f"user_{user_id}"):
        # 一定不存在，直接返回404
        return None

    # 可能存在，查询数据库
    return db.query(f"user_{user_id}")
```

**问题解决**:
```
缓存穿透场景：
1. 恶意请求大量不存在的数据
2. 缓存无法命中（因为数据本不存在）
3. 数据库被击穿，服务崩溃

布隆过滤器解决：
1. 先用布隆过滤器检查
2. 如果返回False，一定不存在
3. 直接拒绝，保护数据库
```

### 4. 垃圾邮件过滤

```python
spam_filter = BlacklistFilter(expected_items=10000000)

# 添加已知垃圾发件人
spam_senders = ["spam@evil.com", "ads@fake.com", ...]
for sender in spam_senders:
    spam_filter.add_to_blacklist(sender)

# 检查邮件是否来自垃圾发件人
def should_filter_email(sender):
    if spam_filter.is_blacklisted(sender):
        return True  # 垃圾邮件
    return False     # 正常邮件
```

## 项目结构

```
05-bloom-filter/
├── README.md
├── docs/
│   ├── DESIGN.md
│   └── PARAMETERS.md
├── src/
│   └── python/
│       └── bloom_filter.py
├── tests/
│   └── test_bloom_filter.py
└── requirements.txt
```

## 使用指南

### Python 版本

```bash
# 运行示例
python3 src/python/bloom_filter.py

# 使用 API
from bloom_filter import BloomFilter

# 创建布隆过滤器
bf = BloomFilter(expected_elements=10000, false_positive_rate=0.01)

# 添加元素
bf.add("user_123")
bf.add("user_456")

# 检查元素
if bf.contains("user_123"):
    print("可能存在")
else:
    print("一定不存在")

# 获取统计信息
stats = bf.get_stats()
print(f"大小: {stats['size']}, 哈希数: {stats['hash_count']}")
```

## 性能分析

### 空间对比

| 场景 | 数据量 | Set | 布隆过滤器 | 节省 |
|------|--------|-----|---------|------|
| URL去重 | 100万 | 32MB | 1.2MB | 96% |
| IP检测 | 1000万 | 400MB | 12MB | 97% |
| 垃圾邮件 | 1亿 | 4GB | 120MB | 97% |

### 时间复杂度

| 操作 | 时间 | 说明 |
|------|------|------|
| 添加元素 | O(k) | k=哈希函数个数 |
| 检查元素 | O(k) | k通常=6-8 |
| 获取统计 | O(n) | n=位数组大小 |

### 误判率

| 期望误判率 | 位数组大小 | 哈希函数数 | 实际误判率 |
|----------|----------|---------|----------|
| 1% | 9585 | 6 | 0.73% |
| 0.1% | 143775 | 10 | 0.08% |
| 0.01% | 2167636 | 14 | 0.008% |

**建议**: 误判率设置为 0.01，是空间和准确性的平衡点

## 核心API

### Python

```python
# 创建过滤器
bf = BloomFilter(expected_elements=10000, false_positive_rate=0.01)

# 基础操作
bf.add(item)                        # 添加元素
bf.contains(item)                   # 检查元素
bf.get_stats()                      # 获取统计

# URL爬虫去重
crawler = URLCrawlerFilter(expected_urls=1000000)
crawler.is_crawled(url)             # 检查是否爬过
crawler.mark_crawled(url)           # 标记已爬
crawler.get_statistics()            # 获取统计

# IP黑名单
ip_filter = IpBlocklistFilter(expected_ips=1000000)
ip_filter.add_blocked_ip(ip)        # 添加黑名单IP
ip_filter.is_blocked(ip)            # 检查IP

# 黑名单过滤
blacklist = BlacklistFilter(expected_items=100000)
blacklist.add_to_blacklist(item)    # 添加到黑名单
blacklist.is_blacklisted(item)      # 检查是否黑名单

# 缓存穿透防护
cache_guard = CacheAvalanchePrevention(expected_items=100000)
cache_guard.add_key(key)            # 添加存在的key
cache_guard.query_exists(key)       # 查询key是否存在
```

## 高级主题

### 1. 计数布隆过滤器

支持删除操作：
```python
class CountingBloomFilter:
    def __init__(self):
        self.counter = [0] * size

    def add(self, item):
        for hash_val in hashes(item):
            self.counter[hash_val] += 1

    def remove(self, item):
        for hash_val in hashes(item):
            self.counter[hash_val] -= 1

    def contains(self, item):
        return all(self.counter[h] > 0 for h in hashes(item))
```

### 2. 分层布隆过滤器

处理流式数据：
```
Layer 1: 最近的数据
  ↓
Layer 2: 1天前的数据
  ↓
Layer 3: 1周前的数据
  ↓
Layer 4: 归档数据
```

### 3. 可缩放布隆过滤器

自动扩展：
```python
# 当误判率超过阈值时，添加新层
if current_fpr > target_fpr:
    add_new_layer()
```

## 参数选择指南

### 确定参数

```python
import math

def calculate_parameters(n, p):
    """
    n: 预期元素数
    p: 误判率 (0.01 = 1%)

    返回：(位数组大小, 哈希函数数)
    """
    m = -n * math.log(p) / (math.log(2) ** 2)  # 位数组大小
    k = m / n * math.log(2)                     # 哈希函数数
    return int(m), int(k)

# 示例
m, k = calculate_parameters(n=1000000, p=0.01)
# m=9585776 (1.2MB), k=6
```

## 最佳实践

✅ **DO**:
- 误判率设置为 0.01（平衡点）
- 监控实际误判率
- 结合真实验证（布隆过滤器+数据库）
- 定期重建过滤器

❌ **DON'T**:
- 依赖布隆过滤器的False（可能有误判）
- 试图删除元素（不支持）
- 误判率设过低（浪费空间）
- 不计算参数就使用

## 常见问题

**Q: 布隆过滤器返回False一定是不存在吗？**

A: 是的！这是布隆过滤器最大的优势：
- False → **一定不存在**
- True → **可能存在**（可能误判）

**Q: 如何选择哈希函数数量？**

A: 自动计算或使用经验值：
```
k = (m / n) * ln(2)  ≈ 0.7 * (m / n)

通常 k = 6-8 就足够了
```

**Q: 大数据去重用布隆过滤器还是HyperLogLog？**

A:
- **布隆过滤器**：需要精确去重，支持个体查询
- **HyperLogLog**：只需统计去重数量，节省更多空间

## 扩展练习

1. 实现**计数布隆过滤器** - 支持删除
2. 实现**分层布隆过滤器** - 处理时间序列
3. 实现**可缩放布隆过滤器** - 自动扩展
4. 实现**Cuckoo Filter** - 更好的性能

## 相关资源

- [布隆过滤器原论文](https://dl.acm.org/doi/10.1145/362686.362692)
- [Redis 布隆过滤器实现](https://redis.io/docs/stack/bloom/)
- [HyperLogLog 对比](https://en.wikipedia.org/wiki/HyperLogLog)

---

**最后更新**: 2024-03-02
**作者**: Algorithm Team
**License**: MIT
