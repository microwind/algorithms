# 双向循环链表 (Doubly Circular Linked List)

## 概述

双向循环链表是双向链表的扩展，尾节点的指针指向头节点，头节点的指针指向尾节点，形成一个双向的环。这是最灵活的链表结构，支持双向遍历和循环访问。

## 结构特点

```
Head <-> Node1 <-> Node2 <-> Node3 <-> Head (循环互指)
```

- 每个节点包含：数据 + next指针 + prev指针
- 尾节点的next指向头节点
- 头节点的prev指向尾节点
- 支持双向循环遍历

## 文件列表

| 文件名 | 语言 |
|--------|------|
| doubly_circular_linked.c | C |
| doubly_circular_linked.js | JavaScript |
| doubly_circular_linked.py | Python |
| DoublyCircularLinked.java | Java |
| doubly_circular_linked.go | Go |
| doubly_circular_linked.rs | Rust |
| doubly_circular_linked.ts | TypeScript |

## 适用场景

- 双向环形队列
- 需要双向遍历的循环场景
- 高级调度算法
- 双向循环缓冲区
- 音乐播放器的循环播放列表

## 优缺点

**优点：**
- 支持双向环形遍历，最灵活
- 可以从任意节点向任意方向遍历
- 没有NULL结尾，处理更统一
- 头尾操作都是O(1)

**缺点：**
- 内存占用最大（每个节点两个指针）
- 结构最复杂
- 需要特别注意循环终止条件
- 实现和维护成本最高
