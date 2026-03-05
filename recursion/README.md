## 递归 Recursion

### 概述
递归（Recursion）是一种编程技术，其中函数在其定义体内调用自己。递归的核心思想是将一个复杂问题分解为规模更小的相同问题，直到达到基础情况（递归终止条件）。递归是实现分治算法、树遍历、回溯等算法的基础。

### 递归的三个关键要素
递归函数必须包含：
1. **基础情况（Base Case）**：递归终止的条件，避免无限递归
2. **递归情况（Recursive Case）**：函数调用自己，问题规模逐渐缩小
3. **返回值处理**：正确处理递归返回的结果

### 图形结构示例
以阶乘为例，递归调用过程：
```
factorial(5) 计算过程：
factorial(5)
   ├──> factorial(4)
   │      ├──> factorial(3)
   │      │      ├──> factorial(2)
   │      │      │      ├──> factorial(1)
   │      │      │      │      └──> factorial(0) = 1 (基础情况)
   │      │      │      └──> 2 * 1 = 2
   │      │      └──> 3 * 2 = 6
   │      └──> 4 * 6 = 24
   └──> 5 * 24 = 120
```

### 特点

#### 优点
- **代码简洁**：递归代码通常比迭代版本更简洁易读
- **自然映射**：某些问题（如树遍历、分治）天然适合递归实现
- **逻辑清晰**：递归直接反映问题的数学定义
- **分治能力**：易于实现分治算法，如快速排序、归并排序

#### 缺点
- **栈溢出风险**：深递归可能导致栈内存溢出
- **性能开销**：每次函数调用都有开销（参数传递、栈管理）
- **效率较低**：相同问题的递归解往往慢于迭代解
- **重复计算**：未优化的递归（如斐波那契）会有大量重复计算

### 操作方式
- **简单递归**：直接递归调用，如阶乘、斐波那契
- **尾递归**：递归调用是函数的最后一步，某些语言可以优化为迭代
- **分治递归**：将问题分解为子问题，递归求解后合并结果
- **回溯递归**：探索所有可能的解，不满足条件时回退

### 复杂度分析

| 算法 | 时间复杂度 | 空间复杂度 | 描述 |
|------|----------|----------|------|
| 阶乘 | O(n) | O(n) | 递归深度n，每次调用O(1) |
| 斐波那契（无优化） | O(2^n) | O(n) | 大量重复计算 |
| 斐波那契（备忘录） | O(n) | O(n) | 使用缓存避免重复计算 |
| 汉诺塔 | O(2^n) | O(n) | 递归深度n |

### 应用场景
- **树和图遍历**：深度优先搜索（DFS）、树的中序遍历
- **分治算法**：快速排序、归并排序、二分查找
- **动态规划**：斐波那契、背包问题（递归实现）
- **回溯算法**：N皇后、全排列、组合等
- **数学问题**：阶乘、GCD、幂运算

### 简单例子

#### Python 示例 - 阶乘
```python
# 递归方式：简洁，直观反映数学定义
def factorial_recursive(n):
    """递归计算阶乘"""
    if n <= 1:           # 基础情况
        return 1
    return n * factorial_recursive(n - 1)  # 递归情况

# 迭代方式：效率更高
def factorial_iterative(n):
    """迭代计算阶乘"""
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result

# 尾递归方式：可以被优化为迭代
def factorial_tail(n, acc=1):
    """尾递归版本"""
    if n <= 1:
        return acc
    return factorial_tail(n - 1, n * acc)

print(factorial_recursive(5))  # 输出: 120
```

#### C 语言示例 - 递归
```c
#include <stdio.h>

/* 递归计算阶乘 */
long long factorial(int n) {
    if (n == 0) return 1;  /* 基础情况 */
    return n * factorial(n - 1);  /* 递归调用 */
}

/* 递归计算斐波那契数列 */
int fibonacci(int n) {
    if (n <= 1) return n;  /* 基础情况 */
    return fibonacci(n - 1) + fibonacci(n - 2);  /* 递归调用 */
}

int main() {
    printf("5! = %lld\n", factorial(5));       /* 120 */
    printf("fib(10) = %d\n", fibonacci(10));   /* 55 */
    return 0;
}
```

#### Java 示例 - 斐波那契
```java
public class Recursion {
    // 递归方式：简洁但低效
    public static int fibRecursive(int n) {
        if (n <= 1) return n;  // 基础情况
        return fibRecursive(n - 1) + fibRecursive(n - 2);  // 递归调用
    }

    // 优化版：使用备忘录避免重复计算
    public static int fibMemo(int n, int[] memo) {
        if (n <= 1) return n;
        if (memo[n] != 0) return memo[n];  // 已计算过则直接返回
        memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
        return memo[n];
    }

    public static void main(String[] args) {
        System.out.println(fibRecursive(10));  // 55
    }
}
```

#### Go 示例 - 递归
```go
package main

import "fmt"

// 递归计算阶乘
func factorial(n int) int {
    if n == 0 {           // 基础情况
        return 1
    }
    return n * factorial(n - 1)  // 递归调用
}

// 递归计算汉诺塔
func hanoi(n int, from, to, aux string) {
    if n == 1 {           // 基础情况
        fmt.Printf("Move disk 1 from %s to %s\n", from, to)
    } else {              // 递归情况
        hanoi(n - 1, from, aux, to)
        fmt.Printf("Move disk %d from %s to %s\n", n, from, to)
        hanoi(n - 1, aux, to, from)
    }
}

func main() {
    fmt.Println(factorial(5))  // 120
    hanoi(3, "A", "C", "B")    // 汉诺塔求解
}
```

### 递归 vs 迭代对比

| 特性 | 递归 | 迭代 |
|------|------|------|
| 代码可读性 | 通常更简洁 | 代码较长但明显 |
| 时间复杂度 | 可能有重复计算 | 通常线性扫描 |
| 空间复杂度 | O(n) 栈深度 | O(1) 常数空间 |
| 执行效率 | 函数调用开销 | 直接循环，更快 |
| 栈溢出风险 | 深递归时风险大 | 无风险 |
| 适用场景 | 树、分治、回溯 | 简单迭代、累计操作 |

### 优化技巧

#### 1. 备忘录（Memoization）
缓存已计算的结果，避免重复计算：
```python
def fib_memo(n, memo={}):
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo)
    return memo[n]
```

#### 2. 尾递归优化
函数的最后一步是递归调用，某些语言编译器可优化为迭代：
```python
def factorial_tail(n, acc=1):
    if n <= 1:
        return acc
    return factorial_tail(n - 1, n * acc)  # 尾递归
```

#### 3. 动态规划替代
用表格记录中间结果，从底向上计算：
```python
def fib_dp(n):
    dp = [0] * (n + 1)
    dp[1] = 1
    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]
    return dp[n]
```

### 常见陷阱

1. **缺少基础情况**：导致无限递归和栈溢出
2. **基础情况错误**：导致结果不正确
3. **重复计算**：未使用备忘录的递归可能重复计算
4. **深度太深**：大规模输入导致栈溢出
5. **参数传递**：确保参数正确更新以逐步接近基础情况

### 学习建议
1. 理解递归的三要素：基础情况、递归情况、返回值
2. 画出递归树理解函数调用过程
3. 识别何时适合用递归（树、分治、回溯）
4. 学会用备忘录优化递归性能
5. 考虑何时用迭代替代递归以提高效率
