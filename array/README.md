# 数组算法（Array）

数组相关的经典题目与实现，按题型组织，提供多语言可运行代码，适合练习与复习。

## 目录结构

```text
array/
├── reverse/                # 反转数组
├── rotate/                 # 旋转数组
├── unique/                 # 数组去重
├── maximum-subarray/       # 最大子数组和（Kadane）
├── two-sum/                # 两数之和（哈希表）
├── move-zeroes/            # 移动零（双指针）
├── merge-sorted-array/     # 合并两个有序数组（双指针）
└── README.md               # 本文档
```

## 题型与思路

### 1) 基础变换
- **reverse**：双指针头尾交换
```c
left = 0, right = n-1
// left < right 保证不重复交换
while left < right:
    // 交换元素
    swap(arr[left], arr[right])
    left++, right--
```

- **rotate**：原地旋转（可用翻转法）
```c
// 翻转整个数组，再翻转两部分
reverse(arr, 0, k-1)
reverse(arr, k, n-1)
```

- **move_zeroes**：保持非零相对顺序，零移到末尾
```c
write = 0
// 遍历数组，将非零元素移到前面
for read in range(n):
    if arr[read] != 0:
        arr[write] = arr[read]
        write++
// 将剩余位置设为0
while write < n:
    arr[write] = 0
    write++
```

### 2) 查询与去重
- **unique**：使用集合/哈希结构去重
```c
seen = set()
result = []
// 遍历数组，将未见过的元素加入结果
for x in arr:
    // 如果元素未见过，加入结果并标记为已见
    if x not in seen:
        seen.add(x)
        result.append(x)
```

- **two_sum**：哈希表记录已遍历元素，单次扫描求解
```c
hash = {}
// 遍历数组，记录已见过的元素
for i, num in enumerate(arr):
    complement = target - num
    // 如果补数已在哈希表中，返回索引
    if complement in hash:
        return [hash[complement], i]
    hash[num] = i
```

### 3) 动态规划
- **maximum_subarray**：Kadane 算法，维护当前和与全局最大值
```c
current_sum = max_sum = arr[0]
// 遍历数组，维护当前和与全局最大值
for i in range(1, n):
    // 当前和取当前元素与当前和+当前元素的最大值
    current_sum = max(arr[i], current_sum + arr[i])
    // 全局最大值取当前最大值与当前和的最大值
    max_sum = max(max_sum, current_sum)
```

### 4) 双指针合并
- **merge_sorted_array**：从尾部向前填充，避免覆盖未处理元素
```c
i = m-1, j = n-1, k = m+n-1
// 从尾部开始填充，避免覆盖未处理元素
while i >= 0 and j >= 0:
    // 比较两个数组的元素，将较大的元素放到尾部
    if nums1[i] > nums2[j]:
        nums1[k] = nums1[i]
        i--
    // 如果 nums2[j] 较大或相等，将 nums2[j] 放到尾部
    else:
        nums1[k] = nums2[j]
        j--
    k--
```

## 复杂度速查

| 题目 | 典型时间复杂度 | 典型空间复杂度 |
|------|----------------|----------------|
| reverse | O(n) | O(1) |
| rotate | O(n) | O(1) |
| unique | O(n) | O(n) |
| two-sum | O(n) | O(n) |
| move-zeroes | O(n) | O(1) |
| maximum-subarray | O(n) | O(1) |
| merge-sorted-array | O(m+n) | O(1) |
