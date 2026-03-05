# 数组算法（Array）

数组相关的经典题目与实现，按题型组织，提供多语言可运行代码，适合练习与复习。

## 目录结构

```text
array/
├── reverse/                # 反转数组
├── rotate/                 # 旋转数组
├── unique/                 # 数组去重
├── maximum_subarray/       # 最大子数组和（Kadane）
├── two_sum/                # 两数之和（哈希表）
├── move_zeroes/            # 移动零（双指针）
├── merge_sorted_array/     # 合并两个有序数组（双指针）
└── README.md               # 本文档
```

## 题型与思路

### 1) 基础变换
- **reverse**：双指针头尾交换
- **rotate**：原地旋转（可用翻转法）
- **move_zeroes**：保持非零相对顺序，零移到末尾

### 2) 查询与去重
- **unique**：使用集合/哈希结构去重
- **two_sum**：哈希表记录已遍历元素，单次扫描求解

### 3) 动态规划
- **maximum_subarray**：Kadane 算法，维护当前和与全局最大值

### 4) 双指针合并
- **merge_sorted_array**：从尾部向前填充，避免覆盖未处理元素

## 复杂度速查

| 题目 | 典型时间复杂度 | 典型空间复杂度 |
|------|----------------|----------------|
| reverse | O(n) | O(1) |
| rotate | O(n) | O(1) |
| unique | O(n) | O(n) |
| two_sum | O(n) | O(n) |
| move_zeroes | O(n) | O(1) |
| maximum_subarray | O(n) | O(1) |
| merge_sorted_array | O(m+n) | O(1) |

## 运行示例

```bash
# 两数之和
python array/two_sum/two_sum.py
node array/two_sum/two_sum.js
go run array/two_sum/two_sum.go

# 移动零
python array/move_zeroes/move_zeroes.py
node array/move_zeroes/move_zeroes.js
go run array/move_zeroes/move_zeroes.go

# 合并有序数组
python array/merge_sorted_array/merge_sorted_array.py
node array/merge_sorted_array/merge_sorted_array.js
go run array/merge_sorted_array/merge_sorted_array.go
```

---
建议学习顺序：**reverse → unique → two_sum → move_zeroes → rotate → maximum_subarray → merge_sorted_array**
