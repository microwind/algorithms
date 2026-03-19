# 数据结构（Data Structures）

> 数据结构决定了数据的组织方式，是程序的骨架。选对了结构，算法才能高效。
>
> 本目录提供完整的数据结构介绍以及源码例子，供您学习参考。

---

## 1. 分类总览
```mermaid
graph TD
    %% ===== 节点 =====
    DS["数据结构<br/>Data Structures"]

    DS --> L["线性结构"]
    DS --> T["树形结构"]
    DS --> G["图结构"]
    DS --> H["哈希结构"]

    L --> A["数组<br/>Array"]
    L --> LL["链表<br/>LinkedList"]
    L --> S["栈<br/>Stack"]
    L --> Q["队列<br/>Queue"]
    L --> LI["列表<br/>List"]

    T --> BT["二叉树<br/>BinaryTree"]
    T --> HP["堆<br/>Heap"]

    G --> DG["有向图<br/>Directed"]
    G --> UG["无向图<br/>Undirected"]

    H --> HT["哈希表<br/>HashTable"]
    H --> SE["集合<br/>Set"]
    H --> M["映射<br/>Map"]

    %% ===== 样式（Typora兼容写法）=====
    style DS fill:#0b8457,color:#fff,stroke:#16213e,stroke-width:2px

    style L fill:#e6f7ff,stroke:#1890ff
    style A fill:#e6f7ff,stroke:#1890ff
    style LL fill:#e6f7ff,stroke:#1890ff
    style S fill:#e6f7ff,stroke:#1890ff
    style Q fill:#e6f7ff,stroke:#1890ff
    style LI fill:#e6f7ff,stroke:#1890ff

    style T fill:#f6ffed,stroke:#52c41a
    style BT fill:#f6ffed,stroke:#52c41a
    style HP fill:#f6ffed,stroke:#52c41a

    style G fill:#fff7e6,stroke:#fa8c16
    style DG fill:#fff7e6,stroke:#fa8c16
    style UG fill:#fff7e6,stroke:#fa8c16

    style H fill:#fff0f6,stroke:#eb2f96
    style HT fill:#fff0f6,stroke:#eb2f96
    style SE fill:#fff0f6,stroke:#eb2f96
    style M fill:#fff0f6,stroke:#eb2f96
```


| 数据结构 | 目录 | 分类 | 一句话说明 |
|---------|------|------|-----------|
| 数组 Array | [`array/`](./array/) | 线性结构 | 连续内存存储，支持 O(1) 随机访问的最基础线性结构 |
| 链表 Linked List | [`linked/`](./linked/) | 线性结构 | 节点通过指针串联，支持 O(1) 插入删除（含单向/双向/循环） |
| 栈 Stack | [`stack/`](./stack/) | 线性结构 | 后进先出（LIFO），用于函数调用栈、括号匹配、DFS 等场景 |
| 队列 Queue | [`queue/`](./queue/) | 线性结构 | 先进先出（FIFO），用于任务调度、消息队列、BFS 等场景 |
| 列表 List | [`list/`](./list/) | 线性结构 | 有序元素集合，是数组和链表的上层抽象 |
| 哈希表 Hash Table | [`hash/`](./hash/) | 哈希结构 | 通过哈希函数将键映射到存储位置，平均 O(1) 增删查改 |
| 集合 Set | [`set/`](./set/) | 哈希结构 | 无序不重复元素集合，基于哈希表或红黑树实现快速判重 |
| 映射 Map | [`map/`](./map/) | 哈希结构 | 键值对存储，通过唯一键高效查找对应值 |
| 树 Tree | [`tree/`](./tree/) | 树形结构 | 层次化节点结构，广泛用于搜索、排序和索引 |
| 堆 Heap | [`heap/`](./heap/) | 树形结构 | 满足堆性质的完全二叉树，O(1) 取最值，O(log n) 插入删除 |
| 图 Graph | [`graph/`](./graph/) | 图结构 | 由顶点和边组成的网络结构，表示多对多关系 |
| 结构体 Struct | [`struct/`](./struct/) | 基础/复合结构 | 将多种不同类型的数据字段组合为一个复合类型 |

---

## 2. 核心概念

### 2.1 数据结构三要素

| 要素 | 含义 | 示例 |
|------|------|------|
| **逻辑结构** | 数据元素之间的逻辑关系 | 线性、树形、图形、集合 |
| **存储结构** | 数据在内存中的物理存储方式 | 顺序、链式、索引、散列 |
| **数据运算** | 对数据执行的操作 | 增、删、查、改、遍历、排序 |

### 2.2 四种存储方式对比

| 存储方式 | 原理 | 优势 | 劣势 |
|---------|------|------|------|
| **顺序存储** | 物理位置连续 | 随机访问 O(1) | 插入删除需移动元素 |
| **链式存储** | 指针连接离散节点 | 插入删除 O(1) | 访问需遍历 O(n) |
| **索引存储** | 附加索引表加速查找 | 查找效率高 | 额外空间存储索引 |
| **散列存储** | 哈希函数直接定位 | 理想 O(1) 读写 | 存在哈希冲突问题 |

---

## 3. 线性结构

### 3.1 数组（Array）

连续内存中存储固定大小的同类型元素，通过下标直接访问。

```mermaid
graph LR
    subgraph Array["数组 — 连续内存"]
        direction LR
        I0["[0] 10"] --- I1["[1] 20"] --- I2["[2] 30"] --- I3["[3] 40"] --- I4["[4] 50"]
    end

    classDef arr fill:#0f3460,color:#fff,stroke:#0a2647
    class I0,I1,I2,I3,I4 arr
```

| 操作 | 时间复杂度 | 说明 |
|------|-----------|------|
| 访问 | O(1) | 通过索引直接定位 |
| 搜索 | O(n) / O(log n) | 无序遍历 / 有序二分查找 |
| 插入 | O(n) | 需要移动后续元素 |
| 删除 | O(n) | 需要移动后续元素 |

> 详见 [`array/`](./array/)

### 3.2 链表（Linked List）

节点离散存储，每个节点包含数据和指向下一个节点的指针。

```mermaid
graph LR
    subgraph SingleLinked["单向链表"]
        direction LR
        HEAD["head"] --> N1["10"] --> N2["20"] --> N3["30"] --> N4["40"] --> NULL["NULL"]
    end

    subgraph DoubleLinked["双向链表"]
        direction LR
        D1["10"] <--> D2["20"] <--> D3["30"]
    end

    classDef node fill:#0f3460,color:#fff,stroke:#0a2647
    classDef special fill:#1a1a2e,color:#fff,stroke:#16213e

    class N1,N2,N3,N4,D1,D2,D3 node
    class HEAD,NULL special
```

| 操作 | 时间复杂度 | 说明 |
|------|-----------|------|
| 访问 | O(n) | 需要从头遍历 |
| 搜索 | O(n) | 需要逐节点比较 |
| 插入 | O(1) | 已知位置时，修改指针即可 |
| 删除 | O(1) | 已知位置时，修改指针即可 |

> 详见 [`linked/`](./linked/)（含单向、双向、循环、双向循环链表）

### 3.3 栈（Stack）

后进先出（LIFO），只允许在栈顶进行 push/pop 操作。

```mermaid
graph TB
    subgraph Stack["栈 — LIFO"]
        direction TB
        TOP["栈顶 →"] --- S3["30（最后入栈）"]
        S3 --- S2["20"]
        S2 --- S1["10（最先入栈）"]
    end

    PUSH["push(30)"] -.-> TOP
    TOP -.-> POP["pop() → 30"]

    classDef elem fill:#0f3460,color:#fff,stroke:#0a2647
    classDef op fill:#e94560,color:#fff,stroke:#6a2040
    classDef top fill:#1a1a2e,color:#fff,stroke:#16213e

    class S1,S2,S3 elem
    class PUSH,POP op
    class TOP top
```

**典型应用**：函数调用栈、表达式求值（中缀转后缀）、括号匹配、浏览器前进后退、DFS

> 详见 [`stack/`](./stack/)

### 3.4 队列（Queue）

先进先出（FIFO），队尾入队（enqueue），队头出队（dequeue）。

```mermaid
graph LR
    ENQ["enqueue →"] -.-> Q3

    subgraph Queue["队列 — FIFO"]
        direction LR
        Q1["10（队头）"] --- Q2["20"] --- Q3["30（队尾）"]
    end

    Q1 -.-> DEQ["→ dequeue"]

    classDef elem fill:#0f3460,color:#fff,stroke:#0a2647
    classDef op fill:#e94560,color:#fff,stroke:#6a2040

    class Q1,Q2,Q3 elem
    class ENQ,DEQ op
```

**典型应用**：任务调度、消息队列、BFS、缓存淘汰（LRU）

> 详见 [`queue/`](./queue/)

---

## 4. 树形结构

### 4.1 二叉树（Binary Tree）

每个节点最多有两个子节点。包括二叉搜索树（BST）、平衡树（AVL/红黑树）等变体。

```mermaid
graph TD
    N1((1)) --> N2((2))
    N1 --> N3((3))
    N2 --> N4((4))
    N2 --> N5((5))

    classDef root fill:#533483,color:#fff,stroke:#2c1654
    classDef internal fill:#7b5ea7,color:#fff,stroke:#533483
    classDef leaf fill:#a88bcc,color:#fff,stroke:#7b5ea7

    class N1 root
    class N2,N3 internal
    class N4,N5 leaf
```

**四种遍历方式**：

| 遍历 | 顺序 | 结果 |
|------|------|------|
| 前序 | 根 → 左 → 右 | 1 → 2 → 4 → 5 → 3 |
| 中序 | 左 → 根 → 右 | 4 → 2 → 5 → 1 → 3 |
| 后序 | 左 → 右 → 根 | 4 → 5 → 2 → 3 → 1 |
| 层序 | 逐层从上到下 | 1 → 2 → 3 → 4 → 5 |

| 操作 | 时间复杂度（BST 平均） | 最坏 |
|------|----------------------|------|
| 查找 | O(log n) | O(n) |
| 插入 | O(log n) | O(n) |
| 删除 | O(log n) | O(n) |
| 遍历 | O(n) | O(n) |

**典型应用**：文件系统、表达式解析、决策树、数据库索引

> 详见 [`tree/`](./tree/)

### 4.2 堆（Heap）

满足堆性质的完全二叉树。大顶堆：父 >= 子；小顶堆：父 <= 子。底层用数组存储。

```mermaid
graph TD
    H50((50)) --> H30((30))
    H50 --> H20((20))
    H30 --> H15((15))
    H30 --> H10((10))
    H20 --> H8((8))

    classDef max fill:#533483,color:#fff,stroke:#2c1654,stroke-width:2px
    classDef mid fill:#7b5ea7,color:#fff,stroke:#533483
    classDef leaf fill:#a88bcc,color:#fff,stroke:#7b5ea7

    class H50 max
    class H30,H20 mid
    class H15,H10,H8 leaf
```

**数组映射**：节点 `i` 的左子节点 `2i+1`，右子节点 `2i+2`，父节点 `(i-1)/2`

| 操作 | 时间复杂度 |
|------|-----------|
| 获取最值 | O(1) |
| 插入 | O(log n) |
| 删除最值 | O(log n) |
| 建堆 | O(n) |

**典型应用**：优先队列、堆排序、Top K 问题、合并 K 个有序序列

> 详见 [`heap/`](./heap/)

---

## 5. 图形结构

### 图（Graph）

由顶点（Vertex）集合和边（Edge）集合组成，表示多对多的关系。

```mermaid
graph LR
    A((A)) --- B((B))
    A --- C((C))
    B --- C
    C --- D((D))
    C --- E((E))
    D --- E

    classDef node fill:#b83b5e,color:#fff,stroke:#6a2040

    class A,B,C,D,E node
```

**两种存储方式**：

```mermaid
graph LR
    subgraph AdjList["邻接表（省空间）"]
        direction LR
        LA["A → B, C"]
        LB["B → A, C"]
        LC["C → A, B, D, E"]
    end

    subgraph AdjMatrix["邻接矩阵（快查询）"]
        direction LR
        MA["  A B C D E<br/>A[0,1,1,0,0]<br/>B[1,0,1,0,0]<br/>C[1,1,0,1,1]"]
    end

    classDef list fill:#b83b5e,color:#fff,stroke:#6a2040
    classDef matrix fill:#6a2040,color:#fff,stroke:#3d1224

    class LA,LB,LC list
    class MA matrix
```

| 操作 | 时间复杂度 |
|------|-----------|
| DFS/BFS 遍历 | O(V + E) |
| 最短路径（Dijkstra） | O((V + E) log V) |
| 最小生成树（Kruskal/Prim） | O(E log V) |

**典型应用**：社交网络、地图导航、网络路由、任务调度（拓扑排序）

> 详见 [`graph/`](./graph/)

---

## 6. 哈希结构

### 哈希表（Hash Table）

通过哈希函数将键映射到数组索引，实现近似 O(1) 的增删查改。

```mermaid
graph LR
    K1["Key: John"] -->|"hash()"| B0["Bucket 0"]
    K2["Key: Kate"] -->|"hash()"| B2["Bucket 2"]
    K3["Key: Tom"] -->|"hash()"| B4["Bucket 4"]
    K4["Key: Bob"] -->|"hash()"| B0

    B0 --> V1["John:23"]
    V1 --> V4["Bob:30"]
    B2 --> V2["Kate:35"]
    B4 --> V3["Tom:18"]

    classDef key fill:#0b8457,color:#fff,stroke:#065535
    classDef bucket fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef value fill:#16813e,color:#fff,stroke:#0b8457

    class K1,K2,K3,K4 key
    class B0,B2,B4 bucket
    class V1,V2,V3,V4 value
```

**冲突处理**：链地址法（冲突元素组成链表）、开放寻址法（线性探测/二次探测/双哈希）

| 操作 | 平均 | 最坏 |
|------|------|------|
| 插入 | O(1) | O(n) |
| 删除 | O(1) | O(n) |
| 查找 | O(1) | O(n) |

负载因子 `α = n/m`，通常保持 `α < 0.75` 以控制冲突率。

> 哈希表详见 [`hash/`](./hash/) | 集合详见 [`set/`](./set/) | 映射详见 [`map/`](./map/)

---

## 7. 复杂度对比

### 时间复杂度

| 数据结构 | 访问 | 搜索 | 插入 | 删除 | 备注 |
|---------|------|------|------|------|------|
| 数组 | **O(1)** | O(n) | O(n) | O(n) | 有序数组搜索 O(log n) |
| 链表 | O(n) | O(n) | **O(1)** | **O(1)** | 已知位置时 |
| 栈 | O(n) | O(n) | **O(1)** | **O(1)** | 仅栈顶操作 |
| 队列 | O(n) | O(n) | **O(1)** | **O(1)** | 队尾入、队头出 |
| 哈希表 | — | **O(1)** | **O(1)** | **O(1)** | 平均情况，最坏 O(n) |
| 二叉搜索树 | O(log n) | O(log n) | O(log n) | O(log n) | 平衡时，最坏 O(n) |
| 堆 | O(n) | O(n) | O(log n) | O(log n) | 取最值 O(1) |
| 图(邻接表) | O(1) | O(V+E) | O(1) | O(V+E) | — |

### 空间复杂度

| 数据结构 | 空间 | 说明 |
|---------|------|------|
| 数组 | O(n) | 连续存储，可能预分配未使用空间 |
| 链表 | O(n) | 每个节点额外存储指针 |
| 栈 / 队列 | O(n) | 取决于底层实现（数组或链表） |
| 哈希表 | O(n) | 受负载因子影响 |
| 二叉树 | O(n) | 每个节点存储两个子指针 |
| 图 | O(V+E) | 邻接表；邻接矩阵为 O(V^2) |

---

## 8. 如何选择数据结构

```mermaid
graph LR
    START["需要什么操作？"] --> Q1{"键值查找？"}

    Q1 -->|"是"| HT["哈希表 / Map"]
    Q1 -->|"否"| Q2{"需要有序？"}

    Q2 -->|"是"| Q3{"频繁插删？"}
    Q3 -->|"是"| BST["平衡二叉树"]
    Q3 -->|"否"| SA["有序数组 + 二分查找"]

    Q2 -->|"否"| Q4{"访问模式？"}
    Q4 -->|"LIFO"| STK["栈"]
    Q4 -->|"FIFO"| QUE["队列"]
    Q4 -->|"随机访问"| ARR["数组"]
    Q4 -->|"频繁插删"| LL["链表"]
    Q4 -->|"取最值"| HEAP["堆"]
    Q4 -->|"关系网络"| GRAPH["图"]

    classDef question fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef answer fill:#0b8457,color:#fff,stroke:#065535

    class START,Q1,Q2,Q3,Q4 question
    class HT,BST,SA,STK,QUE,ARR,LL,HEAP,GRAPH answer
```

### 常见场景速查

| 场景 | 推荐结构 | 理由 |
|------|---------|------|
| 快速查找 | 哈希表 | 平均 O(1) |
| 有序查找 | 平衡 BST | O(log n) 查找 + 有序遍历 |
| LRU 缓存 | 哈希表 + 双向链表 | O(1) 查找 + O(1) 移动 |
| Top K 问题 | 堆 | O(n log k) |
| 社交网络关系 | 图 | 天然表达多对多关系 |
| 撤销/重做 | 栈 | LIFO 匹配操作顺序 |
| 任务排队 | 队列 | FIFO 保证公平调度 |

---

## 9. 学习路径

```mermaid
graph LR
    subgraph P1["入门"]
        direction TB
        A1["1. 数组"] --> A2["2. 链表"] --> A3["3. 栈和队列"]
    end

    subgraph P2["进阶"]
        direction TB
        B1["4. 哈希表"] --> B2["5. 二叉树"] --> B3["6. 堆"]
    end

    subgraph P3["高级"]
        direction TB
        C1["7. 平衡树 AVL/红黑树"] --> C2["8. 图算法"] --> C3["9. 并查集/线段树/Trie"]
    end

    P1 --> P2 --> P3

    classDef beginner fill:#0f3460,color:#fff,stroke:#0a2647
    classDef intermediate fill:#533483,color:#fff,stroke:#2c1654
    classDef advanced fill:#b83b5e,color:#fff,stroke:#6a2040

    class A1,A2,A3 beginner
    class B1,B2,B3 intermediate
    class C1,C2,C3 advanced
```

### 实践要点

- **手写实现**：每个数据结构的基本操作都亲手写一遍
- **复杂度分析**：养成分析时间/空间复杂度的习惯
- **灵活组合**：实际问题中往往需要组合多种数据结构
- **阅读源码**：参考语言标准库的工业级实现

## 10. 多语言支持

每种数据结构都提供了多语言实现：

| 语言 | 特点 |
|------|------|
| **C** | 底层实现，手动内存管理，深入理解原理 |
| **Java** | 面向对象，标准库（Collections Framework）封装完善 |
| **Go** | 简洁高效，内置 slice 和 map |
| **JavaScript** | 动态类型，数组和对象灵活 |
| **Python** | 语法简洁，内置 list/dict/set 开箱即用 |
| **Rust** | 内存安全，所有权系统保证无数据竞争 |
