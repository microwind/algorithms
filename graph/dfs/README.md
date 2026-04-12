# 深度优先搜索（DFS）

> 图的深度遍历算法，使用递归或栈实现，适用于路径查找、拓扑排序、连通分量等问题。

## 算法原理

### 核心思想

DFS从一个节点开始，尽可能深地探索，直到无法继续再回溯。

```
递归版本:
1. 访问当前节点，标记为已访问
2. 对每个未访问的邻居递归调用DFS

迭代版本（栈）:
1. 将起始节点压入栈
2. 弹出栈顶节点并访问
3. 将未访问的邻居压入栈
4. 重复直到栈为空
```

### 示例遍历

```
图: 0 -- 1 -- 2
    |    |
    3 -- 4

DFS遍历顺序（从0开始）:
0 → 1 → 2 → 回溯 → 4 → 回溯 → 3

结果: [0, 1, 2, 4, 3]
```

---

## 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|--------|------|
| **时间复杂度** | O(V+E) | V顶点数，E边数 |
| **空间复杂度** | O(V) | 递归栈或显式栈 |

## 算法流程（递归版本）

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 20}}}%%
graph LR
    S(["开始"]) --> INPUT["输入图和起点"]
    INPUT --> INIT["初始化访问标记"]
    INIT --> CALL["调用DFS函数"]
    CALL --> END(["返回遍历结果"])
    
    subgraph DFS函数
        FSTART(["DFS节点u"]) --> CHECK{"u已访问?"}
        CHECK -->|"是"| FEND(["返回"])
        CHECK -->|"否"| MARK["标记u为已访问"]
        MARK --> ADD["加入结果列表"]
        ADD --> NEIGHBOR["遍历u的邻居v"]
        NEIGHBOR --> N_CHECK{"所有邻居处理完?"}
        N_CHECK -->|"否"| FCALL["递归调用DFS v"]
        FCALL --> NEXT["下一个邻居"]
        NEXT --> NEIGHBOR
        N_CHECK -->|"是"| FEND
    end
    
    CALL --> FSTART

    %% 节点样式
    classDef start fill:#ff7f50,color:#fff,stroke:#e5533c,stroke-width:2px
    classDef end1 fill:#ff7f50,color:#fff,stroke:#e5533c,stroke-width:2px
    classDef end2 fill:#20b2aa,color:#fff,stroke:#008080,stroke-width:2px
    classDef decision fill:#6a5acd,color:#fff,stroke:#483d8b,stroke-width:2px
    classDef process fill:#20b2aa,color:#fff,stroke:#008080,stroke-width:2px
    
    %% 应用样式
    class S,END,FSTART,FEND start
    class CHECK,N_CHECK decision
    class INPUT,INIT,CALL,MARK,ADD,NEIGHBOR,FCALL,NEXT process
```

---

## 适用场景

- **路径查找**：迷宫、游戏AI
- **连通分量**：查找所有连通子图
- **拓扑排序**：任务调度
- **环检测**：图中是否存在环
- **回溯算法**：八皇后、数独求解

---

## 实现列表

| 语言 | 文件名 | 说明 |
|------|--------|------|
| C | [graph_dfs.c](./graph_dfs.c) | 递归实现 |
| C | [graph_dfs_iterative.c](./graph_dfs_iterative.c) | 栈实现 |
| Java | [GraphDFS.java](./GraphDFS.java) | 递归/迭代 |
| Go | [graph_dfs.go](./graph_dfs.go) | 栈实现 |
| Python | [graph_dfs.py](./graph_dfs.py) | 简洁实现 |
| JavaScript | [graph_dfs.js](./graph_dfs.js) | 递归实现 |
| TypeScript | [GraphDFS.ts](./GraphDFS.ts) | 类型安全 |
| Rust | [graph_dfs.rs](./graph_dfs.rs) | 迭代器实现 |

---

## 使用示例

### Python 版本
```python
graph = {
    0: [1, 3],
    1: [0, 2, 4],
    2: [1],
    3: [0, 4],
    4: [1, 3]
}
result = dfs(graph, 0)
# [0, 1, 2, 4, 3]
```

---

## 扩展阅读

- 回溯算法框架
- 拓扑排序（Kahn算法）
- 强连通分量（Tarjan算法）
