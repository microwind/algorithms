## 分治算法 Divide and Conquer

### 概述
分治（Divide and Conquer）是一种重要的算法设计思想，其核心理念是"分而治之"。该算法将一个复杂的大问题分解为规模较小的相同子问题，递归地解决这些子问题，然后将子问题的解合并为原问题的解。分治是许多高效算法（如快速排序、归并排序、二分查找）的基础。

### 分治算法的三个步骤
1. **分解（Divide）**：将问题分解为规模更小的相同子问题
2. **解决（Conquer）**：递归求解这些子问题
3. **合并（Combine）**：将子问题的解合并为原问题的解

### 图形结构示例
以归并排序为例，分治过程：
```
原数组: [38, 27, 43, 3, 9, 82, 10]

分解阶段（Divide）：
           [38, 27, 43, 3, 9, 82, 10]
          /                          \
      [38, 27, 43, 3]          [9, 82, 10]
      /         \              /       \
   [38,27]    [43,3]       [9,82]    [10]
   /    \     /    \       /    \      |
 [38]  [27]  [43]  [3]   [9]  [82]   [10]

合并阶段（Combine）：
 [38]  [27]  [43]  [3]   [9]  [82]   [10]
   \    /     \    /       \    /      /
   [27,38]   [3,43]       [9,82]    [10]
      \        /             \      /
      [3,27,38,43]       [9,10,82]
            \                /
         [3,9,10,27,38,43,82]
```

### 特点

#### 优点
- **高效算法**：产生许多高效算法（快速排序O(n log n)、二分查找O(log n)）
- **并行性**：子问题独立，天然适合并行计算
- **问题分解**：复杂问题清晰分解为子问题
- **最优子结构**：许多问题具有最优子结构，分治自然适用

#### 缺点
- **额外开销**：递归调用和数据合并产生额外开销
- **栈深度**：过多的递归可能导致栈溢出
- **空间复杂度**：通常需要额外空间存储中间结果
- **不是所有问题都适合**：某些问题分治效率不高

### 操作方式
- **递归分解**：将问题递归分解为子问题
- **递归求解**：对每个子问题递归调用相同函数
- **合并结果**：将子问题的结果合并为最终答案

### 复杂度分析

| 算法 | 时间复杂度 | 空间复杂度 | 适用场景 |
|------|----------|----------|--------|
| 二分查找 | O(log n) | O(1) | 已排序数组查找 |
| 归并排序 | O(n log n) | O(n) | 大规模数据排序 |
| 快速排序 | O(n log n) 平均 | O(log n) | 通用排序 |
| 二分幂运算 | O(log n) | O(log n) | 计算幂运算 |

### 应用场景
- **排序算法**：快速排序、归并排序
- **搜索算法**：二分查找、在排序数组中搜索
- **计算问题**：矩阵乘法（Strassen算法）、快速幂
- **其他问题**：最接近的点对、计数逆序对

### 简单例子

#### Python 示例 - 二分查找
```python
# 二分查找：每次排除一半数据，O(log n) 时间复杂度
def binary_search(arr, target):
    """在已排序数组中查找目标值"""
    left, right = 0, len(arr) - 1

    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1  # 目标在右侧
        else:
            right = mid - 1  # 目标在左侧

    return -1  # 未找到

# 递归版二分查找
def binary_search_recursive(arr, target, left, right):
    """递归实现二分查找"""
    if left > right:
        return -1

    mid = (left + right) // 2
    if arr[mid] == target:
        return mid
    elif arr[mid] < target:
        return binary_search_recursive(arr, target, mid + 1, right)
    else:
        return binary_search_recursive(arr, target, left, mid - 1)

# 使用
arr = [1, 3, 5, 7, 9, 11, 13]
print(binary_search(arr, 7))  # 输出: 3
```

#### Python 示例 - 归并排序
```python
# 归并排序：分治算法的经典例子
def merge_sort(arr):
    """归并排序：O(n log n) 时间复杂度"""
    if len(arr) <= 1:
        return arr

    # 分解：将数组分成两部分
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])

    # 合并：合并两个已排序的数组
    return merge(left, right)

def merge(left, right):
    """合并两个已排序数组"""
    result = []
    i, j = 0, 0

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    result.extend(left[i:])
    result.extend(right[j:])
    return result

# 使用
arr = [38, 27, 43, 3, 9, 82, 10]
print(merge_sort(arr))  # 输出: [3, 9, 10, 27, 38, 43, 82]
```

#### C 语言示例 - 二分查找
```c
#include <stdio.h>

/* 二分查找：O(log n) 时间复杂度 */
int binary_search(int arr[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == target) {
            return mid;  /* 找到目标 */
        } else if (arr[mid] < target) {
            left = mid + 1;  /* 目标在右侧 */
        } else {
            right = mid - 1;  /* 目标在左侧 */
        }
    }

    return -1;  /* 未找到 */
}

/* 递归版二分查找 */
int binary_search_recursive(int arr[], int target, int left, int right) {
    if (left > right) {
        return -1;
    }

    int mid = (left + right) / 2;
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binary_search_recursive(arr, target, mid + 1, right);
    } else {
        return binary_search_recursive(arr, target, left, mid - 1);
    }
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("位置: %d\n", binary_search(arr, size, 7));  /* 输出: 3 */
    return 0;
}
```

#### Java 示例 - 快速排序
```java
public class QuickSort {
    /* 快速排序：平均 O(n log n) 时间复杂度 */
    public static void quickSort(int[] arr, int left, int right) {
        if (left < right) {
            // 分解：选择枢纽并分割
            int pivot = partition(arr, left, right);

            // 解决：递归排序左右两部分
            quickSort(arr, left, pivot - 1);
            quickSort(arr, pivot + 1, right);
        }
    }

    /* 分割函数：返回枢纽的最终位置 */
    private static int partition(int[] arr, int left, int right) {
        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        return i + 1;
    }

    public static void main(String[] args) {
        int[] arr = {38, 27, 43, 3, 9, 82, 10};
        quickSort(arr, 0, arr.length - 1);
        for (int x : arr) System.out.print(x + " ");
    }
}
```

#### Go 示例 - 分治
```go
package main

import "fmt"

// 二分查找
func BinarySearch(arr []int, target int) int {
    left, right := 0, len(arr)-1

    for left <= right {
        mid := (left + right) / 2
        if arr[mid] == target {
            return mid
        } else if arr[mid] < target {
            left = mid + 1
        } else {
            right = mid - 1
        }
    }

    return -1
}

// 归并排序
func MergeSort(arr []int) []int {
    if len(arr) <= 1 {
        return arr
    }

    // 分解：分成两部分
    mid := len(arr) / 2
    left := MergeSort(arr[:mid])
    right := MergeSort(arr[mid:])

    // 合并：合并两个已排序的数组
    return Merge(left, right)
}

// 合并函数
func Merge(left, right []int) []int {
    result := make([]int, 0, len(left)+len(right))
    i, j := 0, 0

    for i < len(left) && j < len(right) {
        if left[i] <= right[j] {
            result = append(result, left[i])
            i++
        } else {
            result = append(result, right[j])
            j++
        }
    }

    result = append(result, left[i:]...)
    result = append(result, right[j:]...)
    return result
}

func main() {
    arr := []int{38, 27, 43, 3, 9, 82, 10}
    fmt.Println(MergeSort(arr))  // [3 9 10 27 38 43 82]
}
```

### 分治算法模板

所有分治算法遵循相同的模式：

```python
def divide_conquer(problem):
    # 1. 基础情况：问题足够小，直接求解
    if is_base_case(problem):
        return solve_directly(problem)

    # 2. 分解：将问题分解为子问题
    sub_problems = divide(problem)

    # 3. 解决：递归求解子问题
    sub_results = []
    for sub_problem in sub_problems:
        sub_result = divide_conquer(sub_problem)
        sub_results.append(sub_result)

    # 4. 合并：合并子问题的结果
    result = combine(sub_results)

    return result
```

### 常见陷阱
1. **分解不当**：子问题不能独立求解或不符合原问题结构
2. **合并错误**：子问题的解无法正确合并为原问题的解
3. **基础情况缺失**：导致无限递归
4. **效率不高**：某些问题分治反而增加复杂度

### 学习建议
1. 理解分治的三个步骤：分解、解决、合并
2. 认识问题的最优子结构
3. 画出递归树理解算法过程
4. 分析每个阶段的时间复杂度
5. 比较分治与其他方法的效率差异
6. 实践编写分治算法，解决实际问题