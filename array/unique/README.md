# 数组去重 (Array Unique)

## 概述

数组去重是指从数组中移除重复的元素，只保留唯一的元素。这是编程中常见的操作，有多种实现方式，每种方式在时间复杂度和空间复杂度上都有所不同。

## 实现方式对比

| 方法 | 时间复杂度 | 空间复杂度 | 是否保持原顺序 | 适用场景 |
|------|------------|------------|----------------|----------|
| 哈希表/集合 | O(n) | O(n) | ✓ | 大多数情况 |
| 双指针 | O(n) | O(1) | ✓ | 已排序数组 |
| 暴力枚举 | O(n²) | O(1) | ✓ | 小数组 |
| 排序后去重 | O(n log n) | O(1) | ✗ | 可接受顺序改变 |

## 核心算法思路

### 1. 哈希表/集合方法
```c
Set seen = {}
List result = []
for x in array:
    if x not in seen:
        seen.add(x)
        result.append(x)
```

### 2. 双指针方法（已排序数组）
```c
i = 0  // 慢指针
for j in range(1, n):  // 快指针
    if array[j] != array[i]:
        i++
        array[i] = array[j]
return array[0:i+1]
```

### 3. 暴力枚举方法
```c
List result = []
for i in range(n):
    is_duplicate = false
    for j in range(i):
        if array[i] == array[j]:
            is_duplicate = true
            break
    if not is_duplicate:
        result.append(array[i])
```

## 应用场景

- **数据清洗**：移除重复的记录
- **统计分析**：确保数据唯一性
- **缓存优化**：避免重复计算
- **用户输入处理**：过滤重复选项

## 文件说明

本目录包含多种编程语言的数组去重实现：

- **C**: `unique.c` - 使用哈希表和双指针两种方法
- **Go**: `unique.go` - 使用map和slice的高效实现
- **Java**: `UniqueArray.java` - 面向对象的多种实现方式
- **JavaScript**: `unique.js` - ES6+的现代实现
- **Python**: `unique.py` - 使用set和列表推导式
- **Rust**: `unique.rs` - 内存安全的实现
- **TypeScript**: `UniqueArray.ts` - 类型安全的实现
- **Dart**: `unique.dart` - Flutter/Dart应用

## 运行示例

### C语言
```bash
cd array/unique
gcc unique.c -o unique
./unique
```

### Go
```bash
cd array/unique
go run unique.go
```

### Java
```bash
cd array/unique
javac UniqueArray.java
java UniqueArray
```

### JavaScript
```bash
cd array/unique
node unique.js
```

### Python
```bash
cd array/unique
python unique.py
```

### Rust
```bash
cd array/unique
rustc unique.rs
./unique
```

## 性能建议

1. **优先使用哈希表方法**：大多数情况下性能最佳
2. **数组已排序时使用双指针**：空间复杂度最优
3. **小数组可用暴力方法**：代码简单，常数因子小
4. **考虑内存限制**：哈希表需要额外空间

## 扩展思考

- 如何处理自定义对象的去重？
- 如何在流式数据中进行去重？
- 如何统计重复元素的次数？
- 如何保持相对顺序的同时进行原地去重？