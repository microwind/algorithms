# 单向链表 (Singly Linked List)

## 概述

单向链表是最基础的链表结构，每个节点包含数据部分和指向下一个节点的指针（next）。从头节点开始，可以通过指针访问链表中的每个元素，只有一个方向的链接。

## 结构特点

```
Head -> Node1 -> Node2 -> Node3 -> NULL
```

- 每个节点包含：数据 + next指针
- 尾节点的next指向NULL
- 只能从头到尾单向遍历

## 文件列表

| 文件名 | 语言 |
|--------|------|
| singly_linked.c | C |
| singly_linked.js | JavaScript |
| singly_linked.py | Python |
| SinglyLinked.java | Java |
| singly_linked.go | Go |
| singly_linked.rs | Rust |
| singly_linked.ts | TypeScript |

## 适用场景

- 简单的数据存储和基本操作
- 内存占用敏感的场景
- 不需要反向遍历的应用

## 优缺点

**优点：**
- 内存占用少（每个节点只有一个指针）
- 结构简单，易于实现
- 插入/删除操作快（头部操作O(1)）

**缺点：**
- 只能单向遍历
- 访问第n个元素需要O(n)时间
- 不适合需要反向操作的场景
