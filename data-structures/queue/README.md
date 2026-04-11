# Queue 数据结构概述

Queue（队列）是一种遵循先进先出（FIFO, First In First Out）原则的数据结构。即，第一个插入队列的元素最先被移除。队列通常用于处理需要按照顺序处理的任务。

# 图形结构示例
```c
Front -> [1, 2, 3, 4, 5] <- Rear
```

- 队列的插入（入队）发生在队列的尾部（Rear）。
- 队列的删除（出队）发生在队列的头部（Front）。

### 图形结构

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 15}}}%%
graph LR
    subgraph 队列结构["📦 队列结构 - FIFO"]
        direction LR
        FRONT["👤 Front"] --> E1["[1]"] --> E2["[2]"] --> E3["[3]"] --> E4["[4]"] --> REAR["🔚 Rear"]
    end

    subgraph 入队操作["⬅️ 入队 Enqueue"]
        direction TB
        ENQ["Enqueue(5)"] --> ADD["添加到Rear"] --> NEWQ["[1]-[2]-[3]-[4]-[5]"]
    end

    subgraph 出队操作["➡️ 出队 Dequeue"]
        direction TB
        DEQ["Dequeue()"] --> REM["移除Front"] --> NEWQ2["[2]-[3]-[4]-[5]"]
    end

    classDef front fill:#0b8457,color:#fff,stroke:#065535,stroke-width:2px
    classDef rear fill:#e74c3c,color:#fff,stroke:#c0392b,stroke-width:2px
    classDef elem fill:#3498db,color:#fff,stroke:#2980b9,stroke-width:2px
    classDef op fill:#f39c12,color:#fff,stroke:#e67e22,stroke-width:2px

    class FRONT front
    class REAR rear
    class E1,E2,E3,E4 elem
    class ENQ,DEQ,ADD,REM op
```

---

# 特点

## 优点
- **先进先出**：能够保证任务按照接收到的顺序执行。
- **高效性**：队列操作（入队和出队）具有O(1)的时间复杂度。

## 缺点
- **访问受限**：只能访问队列的头部元素，不能直接访问队列中间或尾部的元素。
- **存储空间有限**：如果队列存储在数组中，可能会面临空间限制，导致内存浪费或容量不足。

# 操作方式

- **入队（Enqueue）**：将一个元素加入队列的尾部。
- **出队（Dequeue）**：将队列头部的元素移除并返回。
- **查看队列头部元素（Peek/Front）**：返回队列头部的元素但不移除它。
- **判断队列是否为空（IsEmpty）**：判断队列中是否有元素。
- **获取队列长度（Size）**：返回队列中元素的数量。


# 队列与栈、链表等数据结构的区别

| 特性           | 队列 (Queue)                | 栈 (Stack)                   | 链表 (Linked List)            |
|----------------|-----------------------------|------------------------------|------------------------------|
| **基本操作**   | 入队（Enqueue）、出队（Dequeue） | 入栈（Push）、出栈（Pop）      | 插入、删除、遍历（Insert/Delete/Traverse）|
| **数据存储方式**| 先进先出（FIFO）             | 后进先出（LIFO）              | 节点存储，通常每个节点包含数据和指向下一个节点的指针 |
| **访问位置**   | 只能访问队头（Front）         | 只能访问栈顶（Top）            | 可随机访问节点                |
| **操作时间复杂度**| O(1)                         | O(1)                          | O(n)（对于查找），O(1)（插入、删除）|
| **空间使用**   | 固定容量（基于数组或链表实现） | 固定容量（基于数组或链表实现） | 动态存储，灵活调整大小         |
| **应用场景**   | 任务调度、广度优先搜索、缓冲区 | 操作系统栈、深度优先搜索      | 动态数据结构、操作系统内存管理|
| **是否支持随机访问** | 不支持（只能访问队头元素）    | 不支持（只能访问栈顶元素）     | 支持（可以按节点顺序遍历）    |
| **插入删除操作位置** | 头部/尾部（根据实现）         | 只在栈顶（Top）               | 任意位置（前面或后面）        |
| **常见实现方式** | 数组或链表实现                | 数组或链表实现                | 数组、双向链表、单向链表等    |


# 应用场景

1. **任务调度**：操作系统中的进程调度，任务按顺序执行。
   - **CPU进程调度**：操作系统使用多级反馈队列管理进程优先级，如 Linux CFS 调度器
   - **线程池任务队列**：Java ThreadPoolExecutor 使用阻塞队列管理待执行任务
   - **消息队列**：RabbitMQ/Kafka 使用队列实现异步消息传递，削峰填谷

2. **缓冲区管理**：网络数据包缓冲、打印任务队列等。
   - **网络数据包缓冲**：TCP 协议栈使用队列缓存待发送/接收的数据包
   - **IO请求队列**：磁盘调度算法（如电梯算法）使用队列管理读写请求
   - **流媒体缓冲**：视频播放器使用队列预加载数据，保证流畅播放

3. **广度优先搜索**：图的遍历过程中，队列用于维护待访问的节点。
   - **最短路径算法**：Dijkstra/BFS 使用队列维护待探索节点
   - **层次遍历**：二叉树层序遍历使用队列记录每层节点
   - **拓扑排序**：Kahn 算法使用队列管理入度为 0 的节点

### 应用场景可视化

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 25, 'rankSpacing': 35, 'padding': 20}}}%%
graph TB
    ROOT(("📤 队列应用场景"))

    ROOT --> SCHED["⏱️ 任务调度"]
    ROOT --> NET["🌐 网络缓冲"]
    ROOT --> BFS["🔍 BFS遍历"]
    ROOT --> PRINT["🖨️ 打印队列"]

    SCHED --> SCHED1["CPU进程调度"]
    SCHED --> SCHED2["线程池任务"]
    SCHED --> SCHED3["消息队列"]

    NET --> NET1["数据包缓冲"]
    NET --> NET2["IO请求队列"]
    NET --> NET3["流媒体缓冲"]

    BFS --> BFS1["最短路径"]
    BFS --> BFS2["层次遍历"]
    BFS --> BFS3["拓扑排序"]

    PRINT --> PRINT1["文档打印"]
    PRINT --> PRINT2["批量处理"]
    PRINT --> PRINT3["优先级队列"]

    classDef root fill:#1a1a2e,color:#fff,stroke:#16213e,stroke-width:3px
    classDef cat fill:#0f3460,color:#fff,stroke:#0a2647,stroke-width:2px
    classDef sub fill:#533483,color:#fff,stroke:#2c1654
    classDef sched fill:#3498db,color:#fff,stroke:#2980b9
    classDef net fill:#2ecc71,color:#fff,stroke:#27ae60
    classDef bfs fill:#e67e22,color:#fff,stroke:#d35400
    classDef print fill:#9b59b6,color:#fff,stroke:#8e44ad

    class ROOT root
    class SCHED,NET,BFS,PRINT cat
    class SCHED1,SCHED2,SCHED3 sched
    class NET1,NET2,NET3 net
    class BFS1,BFS2,BFS3 bfs
    class PRINT1,PRINT2,PRINT3 print
```

---

# 简单例子

### C 语言实现队列

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int value = q->items[q->front];
    for (int i = 0; i < q->rear; i++) {
        q->items[i] = q->items[i + 1];
    }
    q->rear--;
    if (q->rear == -1) {
        q->front = -1;
    }
    return value;
}

int peek(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->front];
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);

    printf("Front: %d\n", peek(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Front after dequeue: %d\n", peek(&q));

    return 0;
}
```

### java 语言实现队列

```java
import java.util.LinkedList;

class Queue {
    private LinkedList<Integer> list;

    public Queue() {
        list = new LinkedList<>();
    }

    // 入队
    public void enqueue(int value) {
        list.addLast(value);
    }

    // 出队
    public int dequeue() {
        if (isEmpty()) {
            System.out.println("Queue is empty");
            return -1;
        }
        return list.removeFirst();
    }

    // 查看队列头部元素
    public int peek() {
        if (isEmpty()) {
            System.out.println("Queue is empty");
            return -1;
        }
        return list.getFirst();
    }

    // 判断队列是否为空
    public boolean isEmpty() {
        return list.isEmpty();
    }

    public static void main(String[] args) {
        Queue q = new Queue();
        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);

        System.out.println("Front: " + q.peek());
        System.out.println("Dequeue: " + q.dequeue());
        System.out.println("Front after dequeue: " + q.peek());
    }
}

```

### js 语言实现队列

```js
class Queue {
    constructor() {
        this.items = [];
    }

    // 入队
    enqueue(value) {
        this.items.push(value);
    }

    // 出队
    dequeue() {
        if (this.isEmpty()) {
            console.log("Queue is empty");
            return null;
        }
        return this.items.shift();
    }

    // 查看队列头部元素
    peek() {
        if (this.isEmpty()) {
            console.log("Queue is empty");
            return null;
        }
        return this.items[0];
    }

    // 判断队列是否为空
    isEmpty() {
        return this.items.length === 0;
    }
}

// 测试
const queue = new Queue();
queue.enqueue(1);
queue.enqueue(2);
queue.enqueue(3);

console.log("Front:", queue.peek());
console.log("Dequeue:", queue.dequeue());
console.log("Front after dequeue:", queue.peek());

```

### go 语言实现队列

```go
package main

import "fmt"

type Queue struct {
	items []int
}

func (q *Queue) enqueue(value int) {
	q.items = append(q.items, value)
}

func (q *Queue) dequeue() int {
	if len(q.items) == 0 {
		fmt.Println("Queue is empty")
		return -1
	}
	front := q.items[0]
	q.items = q.items[1:]
	return front
}

func (q *Queue) peek() int {
	if len(q.items) == 0 {
		fmt.Println("Queue is empty")
		return -1
	}
	return q.items[0]
}

func main() {
	q := &Queue{}
	q.enqueue(1)
	q.enqueue(2)
	q.enqueue(3)

	fmt.Println("Front:", q.peek())
	fmt.Println("Dequeue:", q.dequeue())
	fmt.Println("Front after dequeue:", q.peek())
}

```