# 两数之和（Two Sum）

> 在数组中找到两个数，使其和等于目标值。这是 LeetCode 经典题目，也是哈希表应用的典型场景。

## 算法概述

两数之和问题是要在一个数组中找到两个元素，使它们的和等于给定的目标值，并返回这两个元素的索引。这是 LeetCode 上最经典的题目之一，也是哈希表应用的标准场景，展示了如何利用哈希表将时间复杂度从 O(n²) 优化到 O(n)。

### 问题定义

给定一个整数数组 `nums` 和一个目标值 `target`，在数组中找出和为目标值的两个整数，并返回它们的数组下标。假设每种输入只会对应一个答案，且不能使用相同的元素两次。

### 问题意义

- **哈希表应用**：这是学习哈希表应用的标准入门问题
- **算法优化**：从暴力解法 O(n²) 优化到哈希表法 O(n)，展示算法优化思路
- **面试经典**：这是技术面试中最常考的题目之一
- **扩展基础**：三数之和、四数之和等问题都是在此基础上扩展

### 典型应用场景

- **配对问题**：寻找满足特定条件的数字对
- **数据匹配**：在数据集中查找互补项，如寻找互补颜色
- **金融计算**：寻找特定金额的组合，如汇率套利
- **游戏开发**：寻找满足条件的游戏元素组合，如装备搭配

## 算法原理

使用**哈希表辅助查找**：
1. 遍历数组，对于每个元素 `num`
2. 计算补数 `complement = target - num`
3. 检查补数是否已在哈希表中
   - 如果在，返回当前索引和补数索引
   - 如果不在，将当前元素及其索引存入哈希表

### 示例演示（target=9）

```
初始数组: [2, 7, 11, 15], target=9

遍历过程:
┌────────┬────────────────────┬──────────────────────┐
│  元素  │   补数=target-元素  │     哈希表状态       │
├────────┼────────────────────┼──────────────────────┤
│   2    │   9-2=7            │    {} → {2:0}       │
│   7    │   9-7=2 ✓存在!     │  返回 [0,1]         │
└────────┴────────────────────┴──────────────────────┘

结果: [0, 1] （元素2和7，下标0和1）
```

---

## 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|--------|------|
| **时间复杂度** | O(n) | 单次遍历数组，哈希表查找 O(1) |
| **空间复杂度** | O(n) | 哈希表存储已遍历元素 |
| **稳定性** | - | 返回第一个找到的结果 |

### 其他解法对比

| 解法 | 时间复杂度 | 空间复杂度 | 说明 |
|------|-----------|-----------|------|
| 暴力枚举 | O(n²) | O(1) | 双重循环 |
| 哈希表法 | O(n) | O(n) | 推荐解法 |
| 双指针法 | O(n log n) | O(1) | 需要数组已排序 |

---

## 流程图

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 5}}}%%
graph LR
    S(["开始"]) --> INIT["创建哈希表<br/>i = 0"]
    INIT --> LOOP{"i < n?"}
    LOOP -->|"否"| NOTFOUND(["未找到"])
    LOOP -->|"是"| CALC["补数 = target - arr[i]"]
    CALC --> CHECK{"补数在哈希表中?"}
    CHECK -->|"是"| FOUND(["返回结果<br/>[hash[补数], i]"])
    CHECK -->|"否"| STORE["存入哈希表<br/>arr[i]:i"]
    STORE --> INC["i++"]
    INC --> LOOP

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef decision fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647
    classDef end fill:#e94560,color:#fff,stroke:#c81e45

    class S start
    class NOTFOUND,FOUND end
    class LOOP,CHECK decision
    class INIT,CALC,STORE,INC process
```

---

## 适用场景

- **配对问题**：寻找满足条件的数字对
- **数据匹配**：在数据集中查找互补项
- **金融计算**：寻找特定金额的组合
- **游戏开发**：寻找满足条件的游戏元素组合

---

## 实现列表

| 语言 | 文件名 | 说明 |
|------|--------|------|
| C | [two_sum.c](./two_sum.c) | 手动实现哈希表 |
| Java | [TwoSum.java](./TwoSum.java) | HashMap 实现 |
| Go | [two_sum.go](./two_sum.go) | map 实现 |
| Python | [two_sum.py](./two_sum.py) | dict 实现 |
| JavaScript | [two_sum.js](./two_sum.js) | Object/Map 实现 |
| TypeScript | [TwoSum.ts](./TwoSum.ts) | Map 实现 |
| Rust | [two_sum.rs](./two_sum.rs) | HashMap 实现 |

---

## 使用示例

### C 版本
```c
int nums[] = {2, 7, 11, 15};
int target = 9;
int* result = twoSum(nums, 4, target, &returnSize);
// 结果: [0, 1]
```

### Python 版本
```python
nums = [2, 7, 11, 15]
target = 9
result = two_sum(nums, target)
# 结果: [0, 1]
```

---

## 扩展阅读

- 三数之和问题可以在两数之和基础上扩展
- 如果数组已排序，可以使用双指针法优化空间
- 哈希表法是时间最优解，适用于大部分场景
