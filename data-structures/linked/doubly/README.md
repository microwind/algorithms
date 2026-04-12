# 双向链表 (Doubly Linked List)

## 概述

双向链表每个节点包含三个部分：数据部分、指向下一个节点的指针（next）和指向前一个节点的指针（prev）。支持从任一方向进行遍历，既可以从头到尾遍历，也可以从尾到头遍历。

## 结构特点

```
NULL <- Node1 <-> Node2 <-> Node3 -> NULL
```

- 每个节点包含：数据 + next指针 + prev指针
- 头节点的prev指向NULL
- 尾节点的next指向NULL
- 支持双向遍历

## 文件列表

| 文件名 | 语言 |
|--------|------|
| doubly_linked.c | C |
| doubly_linked.js | JavaScript |
| doubly_linked.py | Python |
| DoublyLinked.java | Java |
| doubly_linked.go | Go |
| doubly_linked.rs | Rust |
| doubly_linked.ts | TypeScript |

## 适用场景

- 需要双向遍历的应用
- 频繁在任意位置插入/删除的场景
- 实现双端队列（Deque）
- LRU缓存实现

## 优缺点

**优点：**
- 支持双向遍历
- 可以在O(1)时间内删除已知节点
- 支持从尾部快速插入/删除

**缺点：**
- 内存占用较大（每个节点多一个指针）
- 实现复杂度稍高（需要维护双向指针）
