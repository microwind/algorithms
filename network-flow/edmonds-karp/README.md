# Edmonds-Karp算法

## 问题描述

Edmonds-Karp算法是Ford-Fulkerson算法的一种实现，使用BFS来寻找增广路径，保证了多项式时间复杂度。

## 算法思想

### 核心原理

1. **增广路径**：在残差网络中寻找从源点到汇点的路径
2. **BFS搜索**：使用广度优先搜索寻找最短增广路径
3. **流量更新**：沿增广路径增加流量
4. **残差网络**：更新残差网络，重复直到无法找到增广路径

### 算法步骤

1. 初始化流量为0
2. 在残差网络中使用BFS寻找增广路径
3. 如果找到路径，更新流量和残差网络
4. 重复步骤2-3，直到无法找到增广路径
5. 返回最大流量

## 复杂度分析

- **时间复杂度**: O(VE²)，其中V是顶点数，E是边数
- **空间复杂度**: O(V + E)

## 实现列表

| 语言 | 文件名 |
|------|--------|
| C | [edmonds_karp.c](./edmonds_karp.c) |
| Java | [EdmondsKarp.java](./EdmondsKarp.java) |
| Go | [edmonds_karp.go](./edmonds_karp.go) |
| Python | [edmonds_karp.py](./edmonds_karp.py) |
| JavaScript | [edmonds_karp.js](./edmonds_karp.js) |
| Rust | [edmonds_karp.rs](./edmonds_karp.rs) |
| TypeScript | [EdmondsKarp.ts](./EdmondsKarp.ts) |

## 应用场景

- 网络流量分析
- 最大匹配问题
- 供应链优化
- 资源分配

## 与Ford-Fulkerson的区别

Edmonds-Karp使用BFS寻找最短增广路径，而Ford-Fulkerson可以使用DFS。这保证了Edmonds-Karp的运行时间是多项式的。
