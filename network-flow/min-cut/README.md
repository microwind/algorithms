# 最小割算法

## 问题描述

最小割问题是在给定流网络中，找到一个边集，使得删除这些边后源点和汇点不再连通，且这些边的容量之和最小。

## 算法思想

### 核心概念

1. **割**：将顶点集分成两个不相交的集合S和T，源点在S中，汇点在T中
2. **割的容量**：从S到T的所有边的容量之和
3. **最小割**：容量最小的割

### 最大流最小割定理

**定理**：在任意流网络中，最大流的值等于最小割的容量。

### 算法步骤

1. 使用最大流算法（如Edmonds-Karp）计算最大流
2. 在残差网络中，从源点开始BFS/DFS标记可达顶点
3. 可达顶点集合为S，不可达顶点集合为T
4. 从S到T的边即为最小割

## 复杂度分析

- **时间复杂度**: O(VE²)（使用Edmonds-Karp）
- **空间复杂度**: O(V + E)

## 实现列表

| 语言 | 文件名 |
|------|--------|
| C | [min_cut.c](./min_cut.c) |
| Java | [MinCut.java](./MinCut.java) |
| Go | [min_cut.go](./min_cut.go) |
| Python | [min_cut.py](./min_cut.py) |
| JavaScript | [min_cut.js](./min_cut.js) |
| Rust | [min_cut.rs](./min_cut.rs) |
| TypeScript | [MinCut.ts](./MinCut.ts) |

## 应用场景

- 网络可靠性分析
- 图像分割
- 聚类分析
- VLSI设计
- 社交网络分析
