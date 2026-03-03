# 数据结构实现参考

常见数据结构的实现示例，按类型组织，包含清晰的注释说明和可运行的示例代码。

## 目录结构

```
data-structures/
├── array/              # 数组
├── stack/              # 栈（后进先出 LIFO）
├── queue/              # 队列（先进先出 FIFO）
├── list/               # 动态列表
├── linked/             # 链表变体
│   ├── singly_linked        # 单向链表
│   ├── doubly_linked        # 双向链表
│   ├── circular_linked      # 循环单向链表
│   └── doubly_circular_linked # 双向循环链表
├── tree/               # 二叉树（前序/中序/后序遍历）
├── heap/               # 堆（大顶/小顶堆）
├── hash/               # 哈希表 & HashMap
├── map/                # 映射表
├── set/                # 集合（不重复元素）
├── graph/              # 图（DFS/BFS）
├── struct/             # 结构体/对象示例
└── README.md           # 本文档
```

## 数据结构类型

### 线性结构
- **数组** - O(1) 访问，O(n) 插入/删除
- **列表** - 动态数组，自动扩容
- **栈** - LIFO，用于递归、表达式求值
- **队列** - FIFO，用于任务调度、BFS
- **链表** - O(1) 插入/删除，O(n) 访问
  - 单向、双向、循环、双向循环

### 树形结构
- **二叉树** - 递归遍历（前序/中序/后序）
- **堆** - 完全二叉树（大顶/小顶堆）

### 哈希结构
- **哈希表** - O(1) 查询，链地址法处理冲突
- **HashMap** - 自动扩容
- **Map** - 键值对映射
- **Set** - 去重集合

### 图结构
- **图** - 邻接表表示，DFS/BFS 遍历

### 其他
- **Struct** - 结构体/对象示例，继承和多态

## 时间复杂度对比

| 数据结构 | 访问 | 搜索 | 插入 | 删除 |
|---------|------|------|------|------|
| 数组 | O(1) | O(n) | O(n) | O(n) |
| 链表 | O(n) | O(n) | O(1)* | O(1)* |
| 栈/队列 | O(n) | O(n) | O(1) | O(1) |
| 堆 | O(n) | O(n) | O(log n) | O(log n) |
| 哈希表 | N/A | O(1) | O(1) | O(1) |
| 二叉树 | O(log n)* | O(log n)* | O(log n)* | O(log n)* |

*已知位置或平衡条件下

## 运行示例

### JavaScript
```bash
node array/array.js
node stack/stack.js
node tree/tree.js
node heap/heap.js
node hash/hash_table.js
node map/map.js
node set/set.js
node graph/graph.js
node struct/struct.js
```

### Python
```bash
python array/array.py
python stack/stack.py
python tree/tree.py
python heap/heap.py
python hash/hash_table.py
python map/map.py
python set/set.py
python graph/graph.py
python struct/struct.py
```

## 文件特点

✅ **完整的注释** - 概念、性能分析、应用场景
✅ **双语支持** - JavaScript 和 Python
✅ **可运行示例** - 每个文件都包含测试代码
✅ **性能标注** - 时间和空间复杂度

## 学习建议

1. **基础** → 数组 → 链表 → 栈 → 队列
2. **进阶** → 二叉树 → 堆
3. **应用** → 哈希表 → 图

---
**总计**: 37个文件 (JavaScript 19 + Python 18)
**语言**: JavaScript + Python
**用途**: 学习和参考数据结构实现
