# 双向链表 (Doubly Linked List)

## 概述

双向链表每个节点包含三个部分：数据部分、指向下一个节点的指针（next）和指向前一个节点的指针（prev）。支持从任一方向进行遍历，既可以从头到尾遍历，也可以从尾到头遍历。

## 结构特点

```
NULL <- Node1 <-> Node2 <-> Node3 -> NULL
```

- **节点结构**：每个节点包含数据域 + prev指针 + next指针
- **双向遍历**：支持从头到尾或从尾到头遍历
- **内存布局**：非连续存储，前后双向链接
- **边界处理**：头节点的prev和尾节点的next都指向NULL

### 图形结构

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 15}}}%%
graph LR
    subgraph 双向链表结构["🔗 双向链表结构"]
        direction LR
        NULL1["NULL"] <-- PREV1 --> NODE1["Node1\nData: A"] <-- PREV2 --> NODE2["Node2\nData: B"] <-- PREV3 --> NODE3["Node3\nData: C"] <-- PREV4 --> NULL2["NULL"]
        NODE1 --> NEXT1 --> NODE2 --> NEXT2 --> NODE3
    end

    classDef nullnode fill:#95a5a6,color:#fff,stroke:#7f8c8d
    classDef node fill:#0b8457,color:#fff,stroke:#065535,stroke-width:2px

    class NULL1,NULL2 nullnode
    class NODE1,NODE2,NODE3 node
```

### 操作复杂度

| 操作 | 时间复杂度 | 说明 |
|------|-----------|------|
| 头部插入/删除 | O(1) | 只需修改头指针 |
| 尾部插入/删除 | O(1) | 维护尾指针即可 |
| 中间删除 | O(1) | 已知节点位置时 |
| 查找元素 | O(n) | 需顺序遍历 |
| 双向遍历 | O(n) | 支持前后双向 |

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

- **LRU缓存**：快速移动节点到头部，O(1)删除
- **双端队列**：Deque实现，两端O(1)操作
- **浏览器历史**：前进后退导航功能
- **音乐播放列表**：上一首/下一首切换
- **文本编辑器**：撤销/重做功能

### 应用场景可视化

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 25, 'rankSpacing': 35, 'padding': 20}}}%%
graph TB
    ROOT(("🔗 双向链表应用场景"))

    ROOT --> LRU["📦 LRU缓存"]
    ROOT --> DEQUE["📬 双端队列"]
    ROOT --> BROWSER["🌐 浏览器历史"]
    ROOT --> MUSIC["🎵 音乐播放"]

    LRU --> LRU1["O(1)移动节点"]
    LRU --> LRU2["快速删除"]
    LRU --> LRU3["维护访问顺序"]

    DEQUE --> DEQUE1["两端O(1)插入"]
    DEQUE --> DEQUE2["两端O(1)删除"]
    DEQUE --> DEQUE3["队列+栈组合"]

    BROWSER --> BROW1["前进导航"]
    BROWSER --> BROW2["后退导航"]
    BROWSER --> BROW3["历史记录"]

    MUSIC --> MUS1["上一首"]
    MUSIC --> MUS2["下一首"]
    MUSIC --> MUS3["随机播放"]

    classDef root fill:#1a1a2e,color:#fff,stroke:#16213e,stroke-width:3px
    classDef cat fill:#0f3460,color:#fff,stroke:#0a2647,stroke-width:2px
    classDef sub fill:#0b8457,color:#fff,stroke:#065535

    class ROOT root
    class LRU,DEQUE,BROWSER,MUSIC cat
    class LRU1,LRU2,LRU3,DEQUE1,DEQUE2,DEQUE3,BROW1,BROW2,BROW3,MUS1,MUS2,MUS3 sub
```

## 优缺点

**优点：**
- **双向遍历**：支持从头到尾或反向遍历
- **O(1)删除**：已知节点位置时直接删除
- **尾部操作快**：维护尾指针后O(1)操作
- **灵活性高**：可向前或向后移动

**缺点：**
- **内存占用大**：每个节点需要两个指针
- **实现复杂**：需要维护prev和next指针
- **插入操作繁琐**：需修改前后节点的指针
- **指针易出错**：容易出现指针悬挂问题

## 简单示例

### C 语言
```c
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 创建节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// 头部插入
void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head) (*head)->prev = newNode;
    *head = newNode;
}
```

### Java
```java
class Node {
    int data;
    Node prev, next;
    Node(int data) { this.data = data; }
}

class DoublyLinkedList {
    Node head, tail;
    
    void insertAtHead(int data) {
        Node newNode = new Node(data);
        newNode.next = head;
        if (head != null) head.prev = newNode;
        head = newNode;
        if (tail == null) tail = newNode;
    }
}
```

### Python
```python
class Node:
    def __init__(self, data):
        self.data = data
        self.prev = None
        self.next = None

class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
    
    def insert_at_head(self, data):
        new_node = Node(data)
        new_node.next = self.head
        if self.head:
            self.head.prev = new_node
        self.head = new_node
        if not self.tail:
            self.tail = new_node
```

### JavaScript
```javascript
class Node {
    constructor(data) {
        this.data = data;
        this.prev = null;
        this.next = null;
    }
}

class DoublyLinkedList {
    constructor() {
        this.head = null;
        this.tail = null;
    }
    
    insertAtHead(data) {
        const newNode = new Node(data);
        newNode.next = this.head;
        if (this.head) this.head.prev = newNode;
        this.head = newNode;
        if (!this.tail) this.tail = newNode;
    }
}
```
