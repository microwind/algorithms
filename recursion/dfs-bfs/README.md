# 递归实现DFS/BFS（DFS/BFS Recursion）

> 使用递归实现深度优先搜索和广度优先搜索。

## 算法原理

### 递归DFS

DFS天然适合递归实现：
```
1. 标记当前节点为已访问
2. 对每个未访问的邻居递归调用DFS
3. 递归返回时回溯
```

### 递归BFS

BFS通常用队列迭代实现，但也可以用递归模拟：
```
1. 按层处理节点
2. 递归处理下一层
```

---

## 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|--------|------|
| **时间复杂度** | O(V+E) | V顶点数，E边数 |
| **空间复杂度** | O(V) | 递归栈或队列 |

## 算法流程（递归DFS）

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 20}}}%%
graph LR
    S(["开始"]) --> INPUT["输入图和起点"]
    INPUT --> CALL["调用DFS函数"]
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
    class INPUT,CALL,MARK,ADD,NEIGHBOR,FCALL,NEXT process
```

---

## 适用场景

- **树遍历**：递归DFS是标准做法
- **连通分量**：查找连通区域
- **路径搜索**：寻找有效路径
- **拓扑排序**：依赖关系处理

---

## 实现列表

| 语言 | 文件名 | 说明 |
|------|--------|------|
| C | [dfs_bfs_recursive.c](./dfs_bfs_recursive.c) | 递归实现 |
| Java | [DFS_BFS.java](./DFS_BFS.java) | 递归实现 |
| Go | [dfs_bfs_recursive.go](./dfs_bfs_recursive.go) | 递归实现 |
| Python | [dfs_bfs_recursive.py](./dfs_bfs_recursive.py) | 递归实现 |
| JavaScript | [dfs_bfs_recursive.js](./dfs_bfs_recursive.js) | 递归实现 |
| TypeScript | [DFS_BFS_Recursive.ts](./DFS_BFS_Recursive.ts) | 类型安全 |
| Rust | [dfs_bfs_recursive.rs](./dfs_bfs_recursive.rs) | 递归实现 |

---

## 使用示例

### Python 版本
```python
# 递归DFS
dfs_recursive(graph, 0, visited)

# 递归BFS
bfs_recursive(graph, [0], visited)
```

---

## 扩展阅读

- 迭代vs递归实现对比
- 尾递归优化
- 图的遍历应用
