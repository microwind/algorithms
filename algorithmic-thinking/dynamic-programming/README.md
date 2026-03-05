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

---

### 动态规划代码示例

以下代码涵盖斐波那契数列、硬币兑换、最长递增子序列、0/1 背包、编辑距离等经典 DP 问题，含详细注释与测试：

```python
"""
动态规划（Dynamic Programming）- 分治与记忆化的完美结合

核心思路：
1. 最优子结构：问题的最优解包含其子问题的最优解
2. 重叠子问题：问题分解过程中会重复计算相同的子问题
3. 记忆化存储：缓存子问题的结果避免重复计算

DP 的两种实现方式：
A. 自顶向下(Top-Down)：递归 + 记忆化
B. 自底向上(Bottom-Up)：迭代 + 填表

经典问题与实现：
"""

# 斐波那契数列 - DP
def fibonacci_dp(n):
    if n <= 1:
        return n
    # dp[i] 表示第i个斐波那契数
    dp = [0] * (n + 1)
    # 初始化：F(0) = 0, F(1) = 1
    dp[0], dp[1] = 0, 1
    # 状态转移：F(n) = F(n-1) + F(n-2)
    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]
    return dp[n]

# 钱币兑换 - 背包思想
def coin_change(coins, amount):
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0
    # 遍历每个金额i，更新最小硬币数
    for i in range(1, amount + 1):
        for coin in coins:
            if coin <= i:
                dp[i] = min(dp[i], dp[i - coin] + 1)
    return dp[amount] if dp[amount] != float('inf') else -1

# 最长递增子序列（LIS）
def longest_increasing_subsequence(nums):
    if not nums:
        return 0
    n = len(nums)
    dp = [1] * n
    # 状态转移：如果nums[j] < nums[i]，可以扩展以j结尾的子序列
    for i in range(1, n):
        # 遍历所有之前的元素，更新以i结尾的LIS
        for j in range(i):
            if nums[j] < nums[i]:
                dp[i] = max(dp[i], dp[j] + 1)
    return max(dp)

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

# 编辑距离
def edit_distance(word1, word2):
    m, n = len(word1), len(word2)
    # dp[i][j] 表示 word1 的前 i 个字符转换为 word2 的前 j 个字符的最少操作数
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    # 初始化：将空字符串转换为另一个字符串需要的操作数
    for j in range(n + 1):
        dp[0][j] = j
    # 初始化：将一个字符串转换为空字符串需要的操作数
    for i in range(m + 1):
        dp[i][0] = i
    # 填充dp表：计算转换成本
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if word1[i - 1] == word2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                delete_op = dp[i - 1][j] + 1
                insert_op = dp[i][j - 1] + 1
                replace_op = dp[i - 1][j - 1] + 1
                dp[i][j] = min(delete_op, insert_op, replace_op)
    return dp[m][n]
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
1. **状态定义不清**：没有准确描述每个子问题的状态，导致无法正确递推。
2. **状态转移方程推导错误**：递推关系写错，结果不符合预期。
3. **初始条件遗漏或设置错误**：基础情况没处理好，导致后续状态出错。
4. **计算顺序混乱**：依赖的状态还没算出来就被用到，顺序不对。
5. **空间未优化**：明明可以用一维数组或滚动数组，结果用了多余空间。

### 学习建议
1. 先判断问题是否具备“最优子结构”和“重叠子问题”两个特性。
2. 用自己的话写出状态定义和状态转移方程，确保理解每一步。
3. 多用小例子手算推导，画出状态表或递推过程。
4. 先写出最基础的朴素实现，理解原理后再考虑空间优化。
5. 多练习不同类型的DP题目，积累常见模型和模板。
6. 对比递归记忆化和迭代表格法，体会两者的优缺点和适用场景。
