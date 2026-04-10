# 记忆化技术（Memoization）

> 通过存储已计算结果来避免重复计算，优化递归算法。

## 导航

| [算法原理](#算法原理) | [复杂度分析](#复杂度分析) | [实现列表](#实现列表) |

---

## 算法原理

### 核心思想

```
1. 检查问题是否已解决
2. 如果已解决，直接返回存储的结果
3. 否则计算结果并存储
4. 返回结果
```

### 对比

| 方法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|-----------|-----------|------|
| 朴素递归 | O(2^n) | O(n)栈 | 重复计算 |
| 记忆化递归 | O(n) | O(n) | 自顶向下 |
| 动态规划 | O(n) | O(n)或O(1) | 自底向上 |

---

## 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|--------|------|
| **时间复杂度** | O(n) | 每个子问题只计算一次 |
| **空间复杂度** | O(n) | 存储结果+递归栈 |

---

## 适用场景

- **重叠子问题**：斐波那契、组合数
- **递归优化**：避免重复计算
- **动态规划铺垫**：理解DP的基础

---

## 实现列表

| 语言 | 文件名 | 说明 |
|------|--------|------|
| C | [memoization.c](./memoization.c) | 数组存储 |
| Java | [Memoization.java](./Memoization.java) | HashMap |
| Go | [memoization.go](./memoization.go) | map实现 |
| Python | [memoization.py](./memoization.py) | lru_cache |
| JavaScript | [memoization.js](./memoization.js) | 对象存储 |
| TypeScript | [Memoization.ts](./Memoization.ts) | Map存储 |
| Rust | [memoization.rs](./memoization.rs) | HashMap |

---

## 使用示例

### Python 版本
```python
from functools import lru_cache

# 自动记忆化
@lru_cache(maxsize=None)
def fibonacci(n):
    if n < 2: return n
    return fibonacci(n-1) + fibonacci(n-2)

# 手动记忆化
memo = {}
def fib_manual(n):
    if n in memo: return memo[n]
    if n < 2: return n
    memo[n] = fib_manual(n-1) + fib_manual(n-2)
    return memo[n]
```

---

## 扩展阅读

- 与动态规划的区别
- 自顶向下vs自底向上
- 记忆化在图算法中的应用
