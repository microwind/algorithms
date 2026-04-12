# 循环链表 (Circular Linked List)

## 概述

循环链表是指链表的最后一个节点的指针指向头节点，形成一个环。循环链表可以是单向的，也可以是双向的，常用于需要循环遍历的场景。

## 结构特点

```
Head -> Node1 -> Node2 -> Node3 -> Head (尾指向头)
```

- 每个节点包含：数据 + next指针
- 尾节点的next指向头节点，形成环
- 可以从任意节点遍历整个链表
- 没有NULL结尾

## 文件列表

| 文件名 | 语言 |
|--------|------|
| circular_linked.c | C |
| circular_linked.js | JavaScript |
| circular_linked.py | Python |
| CircularLinked.java | Java |
| circular_linked.go | Go |
| circular_linked.rs | Rust |
| circular_linked.ts | TypeScript |

## 适用场景

- 环形队列实现
- 循环遍历的场景（如轮询调度）
- 约瑟夫环问题
- 循环缓冲区

## 优缺点

**优点：**
- 适合循环使用，避免了尾部的特殊情况
- 可以从任意节点开始遍历整个链表
- 实现环形数据结构自然方便

**缺点：**
- 只支持从头到尾遍历（单向循环）
- 需要特殊处理终止条件（避免死循环）
- 不容易访问前一个节点
