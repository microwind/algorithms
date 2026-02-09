# 算法思想

本目录包含各种重要的算法思想和设计模式

## 目录结构

```
02-algorithmic-thinking/
├── recursion/              # 递归算法
│   ├── recursion.py/.js    # 递归基础示例
│   ├── fibonacci.py/.c     # 斐波那契数列
│   ├── factorial.py/.c     # 阶乘
│   ├── hanoi.py/.c         # 汉诺塔问题
│   ├── divide.py/.c        # 分治法
│   └── tail-recursion/     # 尾递归优化
│
├── divide-conquer/         # 分治算法
│   └── (包含归并排序、快速排序等)
│
├── dynamic-programming/    # 动态规划
│   ├── dp.py              # DP 基础示例
│   ├── knapsack           # 背包问题
│   └── optimization       # 优化问题
│
├── greedy/                # 贪心算法
│   └── greedy.py          # 贪心策略示例
│
├── backtracking/          # 回溯算法
│   └── backtracking.py    # 回溯模式
│
└── bit-manipulation/      # 位运算
    └── (位操作优化)
```

## 核心概念

### 1. 递归 (Recursion)
- **概念**：函数自己调用自己来解决问题
- **三要素**：基本情况、递归关系、向基本情况发展
- **示例**：阶乘、斐波那契、汉诺塔

### 2. 分治法 (Divide & Conquer)
- **思想**：分解问题 → 递归求解 → 合并结果
- **时间复杂度**：通常为 O(n log n)
- **示例**：归并排序、快速排序

### 3. 动态规划 (Dynamic Programming)
- **条件**：最优子结构、重叠子问题
- **特征**：自底向上或自顶向下
- **示例**：背包问题、最长递增子序列

### 4. 贪心算法 (Greedy)
- **原理**：每步选择当前最优
- **局限**：不保证全局最优
- **示例**：活动选择、最小生成树

### 5. 回溯算法 (Backtracking)
- **应用**：求所有解、某个解
- **特点**：尝试、回退、继续尝试
- **示例**：N 皇后、组合问题

## 文件统计

| 算法思想 | Python | C | Java | Go | JS |
|---------|--------|---|------|----|----|
| 递归 | ✓ | ✓ | ✓ | ✓ | ✓ |
| 分治 | ✓ | ✓ | ✓ | ✓ | ✓ |
| DP | ✓ | - | - | - | - |
| 贪心 | ✓ | - | - | - | - |
| 回溯 | ✓ | - | - | - | - |

## 学习建议

1. 从递归开始，理解基本概念
2. 学习分治法，掌握分解问题的方法
3. 深入动态规划，了解优化思想
4. 实践贪心和回溯，拓宽解题思路

## 运行示例

```bash
# 递归示例
python recursion/recursion.py
python recursion/fibonacci.py
python recursion/hanoi.py

# 动态规划
python dynamic-programming/dp.py

# 贪心算法
python greedy/greedy.py

# 回溯算法
python backtracking/backtracking.py
```

---
**总计**: 16+ 个代码文件，覆盖 5 种主要算法思想
