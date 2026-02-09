# 实际应用示例

从基础到高级的实际应用示例代码

## 目录结构

```
06-examples/
├── basic/             # 基础示例
│   ├── sorting_examples.py
│   │   ├── 冒泡排序
│   │   ├── 快速排序
│   │   └── 归并排序
│   └── search_examples.py
│       ├── 线性搜索
│       ├── 二分搜索
│       ├── DFS
│       └── BFS
│
├── advanced/          # 高级示例
│   ├── graph_algorithms.py
│   │   ├── Dijkstra 算法
│   │   ├── Floyd-Warshall
│   │   └── 拓扑排序
│   └── string_algorithms.py
│       ├── KMP 字符串匹配
│       └── 最长公共子序列
│
└── real-world/        # 实际应用
    ├── cache_system.py
    │   ├── LRU 缓存
    │   └── 超时缓存
    └── rate_limiter.py
        ├── 令牌桶限流
        └── 滑动窗口限流
```

## 示例分类

### Basic（基础）
- 常见排序算法的对比
- 基础搜索算法
- 图的遍历

### Advanced（高级）
- 图论高级算法
- 字符串高级算法
- 复杂问题求解

### Real-World（实际应用）
- 缓存系统实现
- 限流算法
- 生产环境常见问题

## 性能对比

### 排序算法
| 算法 | 时间复杂度 | 空间复杂度 | 稳定性 |
|-----|---------|---------|------|
| 冒泡 | O(n²) | O(1) | 稳定 |
| 快速 | O(n log n) | O(log n) | 不稳定 |
| 归并 | O(n log n) | O(n) | 稳定 |

### 搜索算法
| 算法 | 时间复杂度 | 前置条件 |
|-----|---------|--------|
| 线性搜索 | O(n) | 无 |
| 二分搜索 | O(log n) | 已排序 |
| DFS | O(V + E) | 图结构 |
| BFS | O(V + E) | 图结构 |

## 运行示例

```bash
# 基础示例
python basic/sorting_examples.py
python basic/search_examples.py

# 高级示例
python advanced/graph_algorithms.py
python advanced/string_algorithms.py

# 实际应用
python real-world/cache_system.py
python real-world/rate_limiter.py
```

## 学习路径

1. **掌握基础**（1-2周）
   - 排序、搜索算法
   - 理解时间和空间复杂度

2. **进阶学习**（2-3周）
   - 图论算法
   - 字符串高级处理

3. **实战应用**（持续）
   - 系统设计
   - 性能优化

---
**适用场景**：系统设计、性能优化、生产环境问题解决
