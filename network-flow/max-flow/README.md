# 最大流算法

## 问题描述

最大流问题是在给定的流网络中，找到从源点到汇点的最大可能流量。这是一个经典的图论问题，有广泛的应用。

## 算法思想

### 核心概念

1. **流网络**：有向图，每条边有容量限制
2. **流**：满足容量约束和流量守恒的边流量分配
3. **源点和汇点**：流的起点和终点
4. **最大流**：从源点到汇点的最大可能流量

### 算法选择

常用的最大流算法包括：
- **Ford-Fulkerson**：使用DFS寻找增广路径
- **Edmonds-Karp**：使用BFS寻找增广路径（保证多项式时间）
- **Dinic**：使用层次图和多路增广（更高效）

## 最大流最小割定理

**定理**：在任意流网络中，最大流的值等于最小割的容量。

这意味着：
- 最大流 = 最小割
- 可以通过求解最大流来找到最小割
- 反之亦然

## 复杂度分析

- **Ford-Fulkerson**: O(E * max_flow)
- **Edmonds-Karp**: O(VE²)
- **Dinic**: O(V²E)

## 实现列表

| 语言 | 文件名 |
|------|--------|
| C | [max_flow.c](./max_flow.c) |
| Java | [MaxFlow.java](./MaxFlow.java) |
| Go | [max_flow.go](./max_flow.go) |
| Python | [max_flow.py](./max_flow.py) |
| JavaScript | [max_flow.js](./max_flow.js) |
| Rust | [max_flow.rs](./max_flow.rs) |
| TypeScript | [MaxFlow.ts](./MaxFlow.ts) |

## 应用场景

- 网络流量优化
- 供应链管理
- 匹配问题
- 图像分割
- 电路设计
