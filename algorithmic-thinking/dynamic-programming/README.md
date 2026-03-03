## 动态规划 Dynamic Programming

### 概述
动态规划（Dynamic Programming, DP）是一种强大的算法设计方法，用于解决具有"最优子结构"和"重叠子问题"的问题。核心思想是将复杂问题分解为重叠的子问题，通过保存（"记忆化"）已计算的子问题结果，避免重复计算，从而大幅提高效率。

动态规划通常用于优化问题（如最长公共子序列、背包问题）和计数问题（如路径计数）。

### 动态规划的两个关键特性
1. **最优子结构**：问题的最优解可以由子问题的最优解组合而成
2. **重叠子问题**：同一个子问题在求解过程中会被计算多次

### 动态规划的两种实现方式
1. **自顶向下（Top-Down）**：递归 + 记忆化，从大问题递归到小问题
2. **自底向上（Bottom-Up）**：迭代 + 表格，从小问题迭代到大问题

### 图形结构示例
以斐波那契数列为例，对比不同方法：
```
未优化递归（重复计算）：
                    fib(5)
                   /      \
                fib(4)    fib(3)
               /    \      /    \
            fib(3) fib(2) fib(2) fib(1)
           /   \    /   \   /   \
        fib(2) fib(1) fib(1) fib(0) ...
        /   \
      fib(1) fib(0)

注意：fib(3) 被计算了两次，fib(2) 被计算了三次！

动态规划（记忆化）：每个子问题只计算一次
```

### 特点

#### 优点
- **效率显著提高**：通过记忆化或表格，避免重复计算
- **通用框架**：适用于众多优化问题
- **渐进式求解**：从简单子问题逐步构建到复杂问题
- **易于理解**：相比贪心更直观

#### 缺点
- **额外空间占用**：需要额外的空间存储表格或备忘录
- **问题分析复杂**：需要识别最优子结构
- **状态定义困难**：选择合适的状态定义可能很困难
- **不是所有问题都适合**：只有具备两个关键特性的问题才能用DP

### 操作方式
- **状态定义**：明确定义每个子问题的状态（通常用数组或字典表示）
- **状态转移方程**：定义状态之间的递推关系
- **初始条件**：确定基础情况的值
- **求解顺序**：自底向上或自顶向下计算所有状态

### 复杂度对比

| 问题 | 朴素递归 | 记忆化DP | 表格DP | 空间优化 |
|------|--------|---------|--------|--------|
| 斐波那契(n) | O(2^n) | O(n) | O(n) | O(1) |
| 背包(n,w) | 指数级 | O(nw) | O(nw) | O(w) |
| 最长公共子序列(m,n) | 指数级 | O(mn) | O(mn) | O(min(m,n)) |
| 编辑距离(m,n) | 指数级 | O(mn) | O(mn) | O(min(m,n)) |

### 应用场景
- **背包问题**：0/1背包、多重背包、完全背包
- **路径问题**：最长递增子序列、最长公共子序列、最短路径
- **数字问题**：硬币兑换、爬楼梯、整数分割
- **字符串问题**：编辑距离、正则匹配、通配符匹配
- **其他问题**：最优二叉搜索树、矩阵链乘法

### 简单例子

#### Python 示例 - 斐波那契
```python
# 方法1：朴素递归 - 低效，O(2^n)
def fib_naive(n):
    """低效的递归方式，会重复计算"""
    if n <= 1:
        return n
    return fib_naive(n - 1) + fib_naive(n - 2)

# 方法2：记忆化（自顶向下）- 高效，O(n)
def fib_memo(n, memo={}):
    """用字典记录已计算的值，避免重复计算"""
    if n in memo:
        return memo[n]
    if n <= 1:
        return n

    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo)
    return memo[n]

# 方法3：表格DP（自底向上）- 最高效，O(n)
def fib_dp(n):
    """用表格从底向上计算，避免递归开销"""
    if n <= 1:
        return n

    dp = [0] * (n + 1)
    dp[1] = 1

    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]

    return dp[n]

# 方法4：空间优化 - O(n) 时间，O(1) 空间
def fib_optimized(n):
    """只需记录前两个值"""
    if n <= 1:
        return n

    prev, curr = 0, 1
    for _ in range(2, n + 1):
        prev, curr = curr, prev + curr

    return curr

print(fib_dp(10))  # 输出: 55
```

#### Python 示例 - 0/1背包
```python
# 0/1背包：在重量限制下，选择物品使价值最大
def knapsack(weights, values, capacity):
    """
    weights: 物品重量列表
    values: 物品价值列表
    capacity: 背包容量
    返回：最大价值
    """
    n = len(weights)
    # dp[i][w] 表示前i个物品，容量为w时的最大价值
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]

    # 遍历每个物品
    for i in range(1, n + 1):
        for w in range(capacity + 1):
            # 不选当前物品
            dp[i][w] = dp[i - 1][w]

            # 选当前物品（如果容量足够）
            if w >= weights[i - 1]:
                dp[i][w] = max(
                    dp[i][w],
                    dp[i - 1][w - weights[i - 1]] + values[i - 1]
                )

    return dp[n][capacity]

# 使用
weights = [2, 3, 4, 5]
values = [3, 4, 5, 6]
capacity = 8
print(knapsack(weights, values, capacity))  # 输出: 13
```

#### Java 示例 - 硬币兑换
```java
public class CoinChange {
    /* 硬币兑换：用最少硬币凑出目标金额 */
    public static int coinChange(int[] coins, int amount) {
        // dp[i] 表示凑出金额i需要的最少硬币数
        int[] dp = new int[amount + 1];

        // 初始化：不可能的情况用特殊值表示
        for (int i = 1; i <= amount; i++) {
            dp[i] = Integer.MAX_VALUE;
        }
        dp[0] = 0;

        // 遍历每个金额
        for (int i = 1; i <= amount; i++) {
            // 尝试每种硬币
            for (int coin : coins) {
                if (coin <= i && dp[i - coin] != Integer.MAX_VALUE) {
                    // 选择这个硬币能否得到更优解
                    dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                }
            }
        }

        return dp[amount] == Integer.MAX_VALUE ? -1 : dp[amount];
    }

    public static void main(String[] args) {
        int[] coins = {1, 2, 5};
        System.out.println(coinChange(coins, 5));   // 输出: 1（5元硬币）
        System.out.println(coinChange(coins, 7));   // 输出: 2（5+2）
    }
}
```

#### C 语言示例 - 编辑距离
```c
#include <stdio.h>
#include <string.h>
#include <math.h>

/* 编辑距离：将一个字符串转换为另一个字符串所需的最少操作数 */
int editDistance(char* word1, char* word2) {
    int m = strlen(word1);
    int n = strlen(word2);

    /* dp[i][j] 表示word1前i个字符转换为word2前j个字符的最少操作数 */
    int dp[m + 1][n + 1];

    /* 初始化 */
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;  /* 需要i次删除操作 */
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;  /* 需要j次插入操作 */
    }

    /* 填充表格 */
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];  /* 字符相同，无需操作 */
            } else {
                int insert = dp[i][j - 1] + 1;      /* 插入 */
                int delete = dp[i - 1][j] + 1;      /* 删除 */
                int replace = dp[i - 1][j - 1] + 1; /* 替换 */

                dp[i][j] = (insert < delete ? insert : delete);
                dp[i][j] = (dp[i][j] < replace ? dp[i][j] : replace);
            }
        }
    }

    return dp[m][n];
}

int main() {
    printf("编辑距离: %d\n", editDistance("horse", "ros"));  /* 输出: 3 */
    return 0;
}
```

#### Go 示例 - 最长递增子序列
```go
package main

import "fmt"

// 最长递增子序列：找到最长的严格递增子序列
func lengthOfLIS(nums []int) int {
    if len(nums) == 0 {
        return 0
    }

    n := len(nums)
    // dp[i] 表示以nums[i]结尾的最长递增子序列长度
    dp := make([]int, n)

    // 初始化：每个元素本身就是一个长度为1的递增子序列
    for i := 0; i < n; i++ {
        dp[i] = 1
    }

    // 对每个位置i，检查所有之前的位置j
    for i := 1; i < n; i++ {
        for j := 0; j < i; j++ {
            if nums[j] < nums[i] {
                // 如果nums[j] < nums[i]，可以扩展以j结尾的子序列
                if dp[j]+1 > dp[i] {
                    dp[i] = dp[j] + 1
                }
            }
        }
    }

    // 返回所有dp值的最大值
    maxLen := 0
    for _, len := range dp {
        if len > maxLen {
            maxLen = len
        }
    }

    return maxLen
}

func main() {
    nums := []int{10, 9, 2, 5, 3, 7, 101, 18}
    fmt.Println(lengthOfLIS(nums))  // 输出: 4 [2,3,7,101]
}
```

### 动态规划的五个步骤

1. **定义状态**：选择合适的数据结构表示问题的状态
   ```
   例：dp[i][w] 表示前i个物品、容量为w的背包问题
   ```

2. **定义状态转移方程**：描述状态之间的递推关系
   ```
   例：dp[i][w] = max(dp[i-1][w], dp[i-1][w-weight[i]] + value[i])
   ```

3. **初始化**：设置基础情况的值
   ```
   例：dp[0][w] = 0（0个物品时，价值为0）
   ```

4. **计算顺序**：确定填表的顺序（自底向上或自顶向下）
   ```
   例：从i=1到n，从w=0到capacity
   ```

5. **提取答案**：从表格中提取最终答案
   ```
   例：返回dp[n][capacity]
   ```

### 常见陷阱
1. **状态定义不当**：状态不能完整表示子问题
2. **转移方程错误**：状态转移关系推导有误
3. **初始条件缺失**：基础情况处理不正确
4. **计算顺序错误**：先计算依赖的状态，否则结果不对
5. **空间浪费**：未进行空间优化

### 学习建议
1. 理解问题的最优子结构和重叠子问题
2. 用文字清晰描述状态转移方程
3. 从小规模例子手工推导过程
4. 先实现朴素版本，再进行空间优化
5. 对比记忆化和表格实现，理解优缺点
6. 积累常见DP问题的解题模板
