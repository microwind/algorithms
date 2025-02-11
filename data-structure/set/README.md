# Set 数据结构概述

`Set`（集合）是一种无序的元素集合，其中的每个元素都是唯一的，不允许重复。与数组不同，`Set` 通过高效的查找机制来保证元素的唯一性，通常使用哈希表或红黑树来实现。

# Set 图形结构示例

```c
{ "Alice", "Bob", "Charlie" }
// 在内存中可能存储为（哈希表示例）：
// [哈希桶1] -> "Alice" [哈希桶2] -> "Bob" [哈希桶3] -> "Charlie"
```

# Set 特点

1. **成员唯一性**：

   - `Set` 中的每个值都必须是唯一的，重复的值会被自动忽略。

2. **值的类型**：

   - `Set` 可以包含任何类型的值，包括原始数据类型（如字符串、数字）和对象。

3. **无序性**：

   - `Set` 中的元素没有特定的顺序，这与数组的索引顺序不同。

4. **操作方法**：
   - `Set` 提供了一系列方法来操作集合中的元素，如 `add()`、`delete()`、`has()` 和 `clear()` 等。

# Set 的优缺点

## 优点

- **快速查找**：通常 `O(1)`（哈希表）或 `O(log n)`（红黑树）。
- **唯一性保证**：每个元素在集合中只能出现一次。
- **动态扩展**：多数 `Set` 实现支持自动扩容。

## 缺点

- **内存占用高**：哈希表需要额外存储哈希值和指针。
- **无序存储**（哈希表）/ **较慢的插入和删除**（红黑树）。
- **哈希冲突**可能会降低性能。

# Set 操作方式

- **插入元素**：`set.add(value)`（Java、JavaScript、Python） / `set.insert(value)`（Go）
- **查找元素**：`set.contains(value)`（Java） / `value in set`（Python、JavaScript） / `set[value]`（Go）
- **删除元素**：`set.remove(value)`（Java、Go） / `set.delete(value)`（JavaScript）

# Set 在不同语言中的特性对比

| 语言       | 主要实现                          | 底层结构        | 是否有序                         | 线程安全性                        | 主要操作方式                                 |
| ---------- | --------------------------------- | --------------- | -------------------------------- | --------------------------------- | -------------------------------------------- |
| C          | 手动实现（如哈希表）              | 数组 + 链地址法 | 无序                             | 需手动加锁                        | `add(set, value)` / `contains(set, value)`   |
| C++        | `std::unordered_set` / `std::set` | 哈希表 / 红黑树 | `set` 有序，`unordered_set` 无序 | 非线程安全（需 `std::mutex`）     | `set.insert(value)` / `set.find(value)`      |
| Java       | `HashSet` / `TreeSet`             | 哈希表 / 红黑树 | `TreeSet` 有序，`HashSet` 无序   | `ConcurrentHashMap` 线程安全      | `set.add(value)` / `set.contains(value)`     |
| Go         | `set` 内置类型                    | 哈希表          | 无序                             | 需加锁 (`sync.Mutex`)             | `set[value] = struct{}{}` / `set[value]`     |
| JavaScript | `Set`                             | 哈希表          | 保持插入顺序                     | 非线程安全                        | `set.add(value)` / `set.has(value)`          |
| Python     | `set`                             | 哈希表          | 无序                             | 非线程安全（需 `threading.Lock`） | `set.add(value)` / `value in set`            |
| Rust       | `HashSet` / `BTreeSet`            | 哈希表 / B-树   | `BTreeSet` 有序                  | 非线程安全（需 `Mutex<HashSet>`） | `set.insert(value)` / `set.contains(&value)` |

## Set 不同语言实现

1. **底层结构**：

   - `unordered_set`（C++）、`HashSet`（Java/Rust）、`set`（Python）、`Go set`、`JavaScript Set` **基于哈希表**，支持 `O(1)` 平均查找时间。
   - `set`（C++）、`TreeSet`（Java）、`BTreeSet`（Rust） **基于红黑树或 B-树**，查找时间 `O(log n)`，并保持 **元素的有序性**。

2. **是否有序**：

   - `std::set`（C++）、`Java TreeSet`、`Rust BTreeSet`、`Python set`（3.7+）、`JavaScript Set` **有序**。
   - `unordered_set`（C++）、`Java HashSet`、`Go set`、`C 手动实现哈希表` **无序**。

3. **线程安全性**：

   - `Java ConcurrentHashMap` **线程安全**。
   - `Rust HashSet` 可使用 `Mutex<HashSet>` 保证线程安全。
   - `C++ std::unordered_set` / `std::set` **非线程安全**，需 `std::mutex` 保护。

4. **主要操作**：
   - **插入/更新**：`add()` / `insert()` / `set()` / `set[value] = struct{}{}`.
   - **访问值**：`contains()` / `find()` / `set[value]` / `has()`.
   - **删除元素**：`remove()` / `erase()` / `delete()`.

### 总结：

- **高效查找**：`unordered_set`（C++）、`HashSet`（Java）、`Go set`、`set`（Python）。
- **保持有序**：`std::set`（C++）、`TreeSet`（Java）、`BTreeSet`（Rust）。
- **线程安全**：`ConcurrentHashMap`（Java）、`Mutex<HashSet>`（Rust）。

# Set、List、Queue、Map、Tree、Graph 对比

| 数据结构  | 主要用途                 | 底层结构               | 是否有序    | 是否允许重复元素         | 主要操作                                                           |
| --------- | ------------------------ | ---------------------- | ----------- | ------------------------ | ------------------------------------------------------------------ |
| **List**  | 顺序存储，支持索引访问   | 数组 / 链表            | 有序        | 允许                     | 插入 (`append/push`)、访问 (`get[index]`)、删除 (`remove/pop`)     |
| **Queue** | 先进先出（FIFO）         | 链表 / 环形缓冲区      | 有序        | 允许                     | 入队 (`enqueue/push`)、出队 (`dequeue/pop`)                        |
| **Set**   | 唯一集合，去重           | 哈希表 / 红黑树        | 无序 / 有序 | 不允许                   | 插入 (`insert/add`)、删除 (`remove/delete`)、查找 (`contains`)     |
| **Map**   | 键值对存储，快速查找     | 哈希表 / B-树          | 无序 / 有序 | Key 不重复，Value 可重复 | 插入 (`put/set/insert`)、查找 (`get/find`)、删除 (`remove/delete`) |
| **Tree**  | 层次结构存储，适用于搜索 | 二叉树 / AVL 树 / B-树 | 有序        | 允许                     | 插入 (`insert/add`)、删除 (`remove/delete`)、查找 (`find/search`)  |
| **Graph** | 复杂关系建模，网络结构   | 邻接表 / 邻接矩阵      | 无序 / 有序 | 允许                     | 添加节点 (`addNode`)、添加边 (`addEdge`)、遍历 (`DFS/BFS`)         |

# Set 应用场景

- **去重操作**：如过滤掉重复的用户 ID、关键词等。
- **集合运算**：如求并集、交集和差集。
- **快速查找**：用于判断一个元素是否存在于集合中。
- **集合测试**：在某些场景中，用于检查某元素是否属于某种类别。

# Set 简单例子

## C 语言实现

```c
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 100

typedef struct Entry {
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *buckets[TABLE_SIZE];
} HashSet;

unsigned int hash(int value) {
    return value % TABLE_SIZE;
}

void add(HashSet *set, int value) {
    unsigned int index = hash(value);
    Entry *entry = set->buckets[index];
    while (entry) {
        if (entry->value == value) return; // 已存在则跳过
        entry = entry->next;
    }
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    newEntry->value = value;
    newEntry->next = set->buckets[index];
    set->buckets[index] = newEntry;
}

int contains(HashSet *set, int value) {
    unsigned int index = hash(value);
    Entry *entry = set->buckets[index];
    while (entry) {
        if (entry->value == value) return 1; // 找到返回1
        entry = entry->next;
    }
    return 0; // 未找到返回0
}

int main() {
    HashSet set = {0};
    add(&set, 25);
    add(&set, 30);
    printf("Contains 25: %d\n", contains(&set, 25));
    printf("Contains 40: %d\n", contains(&set, 40));
    return 0;
}
```

## Java 语言使用

```java
import java.util.HashSet;

public class SetExample {
    public static void main(String[] args) {
        HashSet<Integer> set = new HashSet<>();
        set.add(25);
        set.add(30);
        System.out.println("Contains 25: " + set.contains(25));
        System.out.println("Contains 40: " + set.contains(40));
    }
}

```

## Go 语言使用

```go
package main

import "fmt"

func main() {
    set := make(map[int]struct{})
    set[25] = struct{}{}
    set[30] = struct{}{}

    fmt.Println("Contains 25:", contains(set, 25))
    fmt.Println("Contains 40:", contains(set, 40))
}

func contains(set map[int]struct{}, value int) bool {
    _, exists := set[value]
    return exists
}
```

## JS 语言使用

```js
const set = new Set()
set.add(25)
set.add(30)

console.log('Contains 25:', set.has(25))
console.log('Contains 40:', set.has(40))
```
