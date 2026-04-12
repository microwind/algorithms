# 满二叉树（Full Binary Tree）

## 什么是满二叉树？

满二叉树是一种特殊的二叉树，其每一层的节点数都达到最大值。若深度为 k，则节点总数应为 $2^k - 1$ 个。

**特点：**
- 除了最底层外，每个节点都有左右两个子节点
- 树的形状严格对称
- 适用于堆（Heap）等场景
- 可以高效地进行层级遍历和节点访问

## 项目结构

本目录包含满二叉树的多种编程语言实现，展示了不同的构建方式和遍历算法。

### 文件列表

#### 主要实现文件
- `FullBinaryTree.java` - Java实现，包含parent指针和next指针，支持多树串联和无栈遍历
- `full_binary_tree.c` - C实现
- `full_binary_tree.js` - JavaScript实现
- `full_binary_tree.go` - Go实现
- `full_binary_tree.py` - Python实现
- `full_binary_tree.ts` - TypeScript实现
- `full_binary_tree.rs` - Rust实现

#### 辅助实现文件
- `LinkedBuilder.java` - 泛型节点链式构建器
- `TripleNodeBuilder.java` - 三叉节点构建器（包含parent指针）

## 核心功能

### 1. 满二叉树构建
使用递归方式构建指定层数的满二叉树，支持：
- 节点索引占位
- parent指针设置
- 层序编号

### 2. 遍历算法
- **先序遍历**（Pre-order）：根→左→右
- **广度优先遍历**（BFS）：按层级顺序访问节点
- **无栈遍历**：利用parent指针实现无额外空间的遍历

### 3. 高级特性
- **多树串联**：通过next指针将多棵树串联起来
- **从任意节点遍历**：可以从树的任意节点开始遍历整片"森林"
- **层序编号**：按BFS顺序为节点分配连续编号

## 多语言实现对比

| 语言 | 文件名 | 特点 |
|------|--------|------|
| Java | FullBinaryTree.java | 面向对象，泛型支持，完整的parent/next指针 |
| C | full_binary_tree.c | 系统级实现，手动内存管理 |
| JavaScript | full_binary_tree.js | 动态类型，ES6+语法 |
| Go | full_binary_tree.go | 简洁高效，指针操作 |
| Python | full_binary_tree.py | 易读性强，递归自然 |
| TypeScript | full_binary_tree.ts | 类型安全，接口定义 |
| Rust | full_binary_tree.rs | 内存安全，所有权系统 |

## 使用示例

### Java实现示例
```bash
# 编译运行
javac FullBinaryTree.java
java FullBinaryTree
```

### C实现示例
```bash
# 编译运行
gcc full_binary_tree.c -o full_binary_tree
./full_binary_tree
```

### JavaScript实现示例
```bash
# 运行
node full_binary_tree.js
```

### Go实现示例
```bash
# 编译运行
go run full_binary_tree.go
```

### Python实现示例
```bash
# 运行
python full_binary_tree.py
```

### TypeScript实现示例
```bash
# 编译运行
tsc full_binary_tree.ts
node full_binary_tree.js
```

### Rust实现示例
```bash
# 编译运行
rustc full_binary_tree.rs
./full_binary_tree
```

## 算法复杂度

### 构建满二叉树
- 时间复杂度：O(n)，n为节点总数
- 空间复杂度：O(h)，h为树的高度（递归栈）

### 先序遍历
- 时间复杂度：O(n)
- 空间复杂度：O(h)

### 广度优先遍历（BFS）
- 时间复杂度：O(n)
- 空间复杂度：O(w)，w为树的最大宽度

### 无栈遍历
- 时间复杂度：O(n)
- 空间复杂度：O(1)（利用parent指针）

## 扩展阅读

- [二叉树基础](https://en.wikipedia.org/wiki/Binary_tree)
- [完全二叉树 vs 满二叉树](https://en.wikipedia.org/wiki/Binary_tree#Types_of_binary_trees)
- [树遍历算法](https://en.wikipedia.org/wiki/Tree_traversal)

## 许可证

Copyright © https://github.com/microwind All rights reserved.