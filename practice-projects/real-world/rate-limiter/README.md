# 限流算法 | Rate Limiter

**难度**: ⭐⭐ | **标签**: `算法` `系统设计` `并发控制`

实现高效的限流算法，保护系统资源和提高可用性。

## 项目简介

限流是保护系统的关键技术。本项目展示如何实现：
- 令牌桶限流算法
- 滑动窗口限流算法
- 漏桶算法
- 分布式限流

## 核心概念

### 令牌桶（Token Bucket）

```
初始状态：令牌桶容量=10，填充速率=2个/秒

时间线：
t=0s: [●●●●●●●●●●] (10个令牌)
      请求1: 消耗1个   → [●●●●●●●●●]
      请求2: 消耗1个   → [●●●●●●●●]
      请求3: 消耗1个   → [●●●●●●●]

t=0.5s: 补充1个令牌   → [●●●●●●●●] (8+1=9个)

t=1s: 补充2个令牌    → [●●●●●●●●●●] (满)
      请求4: 消耗1个   → [●●●●●●●●●]

请求3拒绝时的场景：
      令牌不足，拒绝请求
```

### 滑动窗口（Sliding Window）

```
窗口大小：1秒，最大请求数：3

时间线：
t=0.1s: [R _____ _____ ] (1个请求)
t=0.3s: [RR____ _____ ] (2个请求)
t=0.5s: [RRR___ _____ ] (3个请求，达到限制)
t=0.7s: [RRR___ _____ ] (4个请求被拒绝)
t=1.1s: [_____ RR____ ] (窗口移动，旧的过期)
```

### 算法对比

| 特性 | 令牌桶 | 滑动窗口 | 漏桶 |
|------|--------|--------|------|
| 实现复杂度 | 中等 | 简单 | 中等 |
| 突发流量处理 | ✓ 支持 | ✗ 不支持 | ✗ 不支持 |
| 准确性 | 高 | 高 | 高 |
| 内存占用 | O(1) | O(n) | O(1) |
| 应用场景 | API限流 | 按秒计数 | 平滑输出 |

## 实现特性

### 令牌桶
- **自动补充**：按固定速率添加令牌
- **柔性处理**：允许突发流量（桶内有足够令牌）
- **精确控制**：每个请求消耗确定数量的令牌

### 滑动窗口
- **精确统计**：在时间窗口内计数
- **简单实现**：使用队列记录请求时间
- **不支持突发**：严格按限额限制

## 应用场景

### API限流
```
GET /api/users?page=1
Rate-Limit-Limit: 100
Rate-Limit-Remaining: 45
Rate-Limit-Reset: 1609459200
```

### 数据库连接限制
- 防止连接数爆炸
- 保护数据库
- 公平分配资源

### 消息队列限流
- 防止队列溢出
- 平衡生产和消费
- 触发反压（backpressure）

### CDN限流
- 防止单IP濒临
- 反对DDOS攻击
- 保护源站

## 简单例子

### Python 示例 - 令牌桶

```python
import time

class TokenBucket:
    """令牌桶限流"""
    def __init__(self, capacity, refill_rate):
        self.capacity = capacity          # 桶容量
        self.tokens = capacity            # 当前令牌数
        self.refill_rate = refill_rate    # 每秒补充的令牌数
        self.last_refill = time.time()

    def is_allowed(self, tokens=1):
        now = time.time()
        elapsed = now - self.last_refill

        # 根据经过的时间补充令牌
        self.tokens = min(
            self.capacity,
            self.tokens + elapsed * self.refill_rate
        )
        self.last_refill = now

        # 检查是否有足够的令牌
        if self.tokens >= tokens:
            self.tokens -= tokens
            return True
        return False

# 使用示例
bucket = TokenBucket(capacity=10, refill_rate=2)  # 每秒2个令牌
for i in range(15):
    if bucket.is_allowed():
        print(f"请求 {i+1}: 允许")
    else:
        print(f"请求 {i+1}: 拒绝")
    time.sleep(0.1)
```

### Python 示例 - 滑动窗口

```python
import time
from collections import deque

class SlidingWindow:
    """滑动窗口限流"""
    def __init__(self, window_size, max_requests):
        self.window_size = window_size      # 窗口大小（秒）
        self.max_requests = max_requests    # 最大请求数
        self.requests = deque()             # 请求时间队列

    def is_allowed(self):
        now = time.time()

        # 移除窗口外的请求
        while self.requests and self.requests[0] < now - self.window_size:
            self.requests.popleft()

        # 检查是否超出限制
        if len(self.requests) < self.max_requests:
            self.requests.append(now)
            return True
        return False

# 使用示例
window = SlidingWindow(window_size=1.0, max_requests=5)
for i in range(10):
    if window.is_allowed():
        print(f"请求 {i+1}: 允许")
    else:
        print(f"请求 {i+1}: 拒绝")
    time.sleep(0.2)
```

## 复杂度分析

| 算法 | 时间复杂度 | 空间复杂度 |
|------|-----------|----------|
| 令牌桶 | O(1) | O(1) |
| 滑动窗口 | O(n) | O(n) |
| 漏桶 | O(1) | O(1) |

## 工程实现建议

### 1. 分布式限流
使用 Redis 实现多机共享限流：
```python
import redis

class DistributedRateLimiter:
    def __init__(self, redis_client, key, limit, window):
        self.redis = redis_client
        self.key = key
        self.limit = limit
        self.window = window

    def is_allowed(self):
        pipe = self.redis.pipeline()
        now = time.time()

        # Lua脚本实现原子操作
        script = """
        local current = redis.call('incr', KEYS[1])
        if current == 1 then
            redis.call('expire', KEYS[1], ARGV[1])
        end
        return current <= tonumber(ARGV[2])
        """
        return self.redis.eval(script, 1, self.key, self.window, self.limit)
```

### 2. 自适应限流
根据系统负载调整限流策略：
```python
class AdaptiveRateLimiter:
    def __init__(self):
        self.base_limit = 100
        self.cpu_threshold = 80

    def get_limit(self):
        current_cpu = get_cpu_usage()
        if current_cpu > self.cpu_threshold:
            return int(self.base_limit * 0.5)  # 降低限额
        return self.base_limit
```

### 3. 限流策略组合
```python
class CompositeRateLimiter:
    def __init__(self):
        self.bucket = TokenBucket(10, 2)
        self.window = SlidingWindow(1, 5)

    def is_allowed(self):
        return self.bucket.is_allowed() and self.window.is_allowed()
```

## 常见问题

**Q: 令牌桶和漏桶有什么区别？**

A:
- **令牌桶**：补充令牌，请求消耗令牌（支持突发）
- **漏桶**：接收请求，按固定速率处理（不支持突发）

**Q: 如何在分布式系统中实现限流？**

A:
1. 使用 Redis 的 `INCR` + `EXPIRE` 实现
2. 使用 Lua 脚本保证原子性
3. 使用分布式 ID 标识用户

**Q: 限流被触发后如何处理？**

A:
1. 返回 429 Too Many Requests
2. 返回 `Retry-After` 头告诉何时重试
3. 排队等待（使用消息队列）

## 学习建议
1. 先理解令牌桶的基本原理
2. 手工计算几个示例验证逻辑
3. 实现单机版本，测试性能
4. 学习分布式实现和 Redis
5. 考虑实际系统中的应用
