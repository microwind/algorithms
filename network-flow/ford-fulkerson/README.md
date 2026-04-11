# Ford-Fulkerson算法

## 问题描述

Ford-Fulkerson算法是一种用于计算流网络中最大流的算法。它通过不断寻找增广路径来增加流量，直到无法找到更多的增广路径为止。

## 算法思想

### 核心原理

1. **增广路径**：在残差网络中寻找从源点到汇点的路径
2. **路径搜索**：可以使用DFS或BFS来寻找增广路径
3. **流量更新**：沿增广路径增加流量
4. **残差网络**：更新残差网络，重复直到无法找到增广路径

### 算法步骤

1. 初始化流量为0
2. 在残差网络中寻找增广路径
3. 如果找到路径，更新流量和残差网络
4. 重复步骤2-3，直到无法找到增广路径
5. 返回最大流量

## 复杂度分析

- **时间复杂度**: O(E * max_flow)，其中E是边数，max_flow是最大流量
- **空间复杂度**: O(V + E)

## 与Edmonds-Karp的区别

Ford-Fulkerson算法可以使用DFS或BFS来寻找增广路径，而Edmonds-Karp专门使用BFS。当使用BFS时，Edmonds-Karp保证了多项式时间复杂度O(VE²)。

## 实现列表

| 语言 | 文件名 |
|------|--------|
| C | [ford_fulkerson.c](./ford_fulkerson.c) |
| Java | [FordFulkerson.java](./FordFulkerson.java) |
| Go | [ford_fulkerson.go](./ford_fulkerson.go) |
| Python | [ford_fulkerson.py](./ford_fulkerson.py) |
| JavaScript | [ford_fulkerson.js](./ford_fulkerson.js) |
| Rust | [ford_fulkerson.rs](./ford_fulkerson.rs) |
| TypeScript | [FordFulkerson.ts](./FordFulkerson.ts) |

## 应用场景

- 网络流量分析
- 最大匹配问题
- 供应链优化
- 资源分配
