## 贪心算法 Greedy Algorithm

### 概述
贪心算法（Greedy Algorithm）是一种在每个步骤中做出局部最优选择，期望从而获得全局最优解的算法设计方法。与动态规划需要保存历史信息不同，贪心算法通常更简单高效，但只适用于具有"贪心选择性质"的问题。

贪心算法的核心思想：**每一步都选择当前看起来最优的选择**。

### 贪心算法的两个关键条件
1. **贪心选择性质**：全局最优解可以由局部最优选择组成，即前面的选择不会影响后面子问题的最优解
2. **最优子结构**：问题的最优解由子问题的最优解组成

### 图形结构示例
以活动选择为例（选择最多不重叠的活动）：
```
活动列表（按结束时间排序）：
活动   开始时间   结束时间
  1      0        5    ✓ 选择（最早结束）
  2      1        3    ✓ 选择（不与1重叠）
  3      3        9    ✗ 跳过（与2重叠）
  4      4        10   ✗ 跳过（与2重叠）
  5      6        8    ✓ 选择（不与2重叠）
  6      7        11   ✗ 跳过（与5重叠）
  7      9        12   ✓ 选择（不与5重叠）

最终选择：活动1、2、5、7（共4个）
```

### 特点

#### 优点

#### 缺点

### 操作方式

### 贪心 vs 动态规划

| 特性 | 贪心算法 | 动态规划 |
|------|--------|---------|
| 最优子结构 | 需要 | 需要 |
| 贪心选择性 | 需要 | 不需要 |
| 时间复杂度 | 通常更低 | 通常更高 |
| 空间复杂度 | 通常O(1) | 通常O(n) |
| 代码复杂度 | 较简单 | 较复杂 |
| 正确性保证 | 需要证明 | 容易验证 |

### 应用场景

### 简单例子

#### Python 示例 - 活动选择
```python
# 活动选择：选择最多不重叠的活动
def activity_selection(activities):
    """
    选择最多不重叠的活动
    活动格式：(开始时间, 结束时间)
    策略：按结束时间排序，贪心选择最早结束的活动
    """
    # 按结束时间排序
    activities.sort(key=lambda x: x[1])

    # 选择第一个活动
    selected = [activities[0]]
    last_end = activities[0][1]

    # 贪心选择后续活动
    for i in range(1, len(activities)):
        start, end = activities[i]
        # 如果当前活动不与已选活动冲突，则选择
        if start >= last_end:
            selected.append(activities[i])
            last_end = end

    return selected

# 使用
activities = [(1, 3), (0, 5), (3, 9), (4, 10), (6, 8), (7, 11), (9, 12)]
result = activity_selection(activities)
print(f"选择了 {len(result)} 个活动: {result}")
# 输出: 选择了 4 个活动: [(0, 5), (6, 8), (9, 12)]
```

#### Python 示例 - 硬币兑换（贪心）
```python
# 硬币兑换：贪心选择最大面值硬币
def coin_change_greedy(coins, amount):
    """
    贪心兑换硬币（仅在特定币种组合下有效，如{1,5,10,25}）
    """
    coins.sort(reverse=True)  # 从大到小排序
    count = 0
    remaining = amount

    for coin in coins:
        # 贪心选择：尽可能多地使用当前最大硬币
        if coin <= remaining:
            count += remaining // coin
            remaining %= coin

    return count if remaining == 0 else -1

# 使用
coins = [25, 10, 5, 1]
print(coin_change_greedy(coins, 41))  # 输出: 5（25+10+5+1）
```

#### Python 示例 - 跳跃游戏
```python
# 跳跃游戏：能否到达数组末尾
def can_jump(nums):
    """
    从索引0开始，每次可以跳跃nums[i]步
    贪心策略：记录能到达的最远位置
    """
    max_reach = 0  # 能到达的最远位置

    for i in range(len(nums)):
        # 如果当前位置超出可达范围，无法继续
        if i > max_reach:
            return False

        # 更新能到达的最远位置
        max_reach = max(max_reach, i + nums[i])

        # 如果已能到达末尾，直接返回
        if max_reach >= len(nums) - 1:
            return True

    return False

# 使用
print(can_jump([2, 3, 1, 1, 4]))    # 输出: True
print(can_jump([3, 2, 1, 0, 4]))    # 输出: False
```

#### Java 示例 - 区间覆盖
```java
import java.util.*;

public class IntervalCoverage {
    /* 区间覆盖：用最少数量的区间覆盖目标范围 */
    public static int minIntervals(int[][] intervals, int start, int end) {
        // 按起点排序
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));

        int count = 0;
        int currentEnd = start;
        int i = 0;

        while (currentEnd < end) {
            int maxEnd = currentEnd;

            // 找到所有起点在currentEnd之前且终点最远的区间
            while (i < intervals.length && intervals[i][0] <= currentEnd) {
                maxEnd = Math.max(maxEnd, intervals[i][1]);
                i++;
            }

            // 如果没有找到有效的区间，无法覆盖
            if (maxEnd == currentEnd) {
                return -1;
            }

            // 选择这个区间
            count++;
            currentEnd = maxEnd;
        }

        return count;
    }

    public static void main(String[] args) {
        int[][] intervals = {{1, 3}, {2, 4}, {3, 5}, {4, 6}};
        System.out.println(minIntervals(intervals, 1, 6));  // 输出: 2
    }
}
```

#### C 语言示例 - 活动选择
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
    int id;
} Activity;

/* 比较函数：按结束时间排序 */
int compare(const void* a, const void* b) {
    Activity* act1 = (Activity*)a;
    Activity* act2 = (Activity*)b;
    return act1->end - act2->end;
}

/* 活动选择：选择最多不重叠的活动 */
int activity_selection(Activity* activities, int n, int* selected) {
    // 按结束时间排序
    qsort(activities, n, sizeof(Activity), compare);

    // 选择第一个活动
    selected[0] = activities[0].id;
    int count = 1;
    int last_end = activities[0].end;

    // 贪心选择后续活动
    for (int i = 1; i < n; i++) {
        if (activities[i].start >= last_end) {
            selected[count++] = activities[i].id;
            last_end = activities[i].end;
        }
    }

    return count;
}

int main() {
    Activity activities[] = {
        {1, 3, 1}, {0, 5, 2}, {3, 9, 3},
        {4, 10, 4}, {6, 8, 5}, {7, 11, 6}, {9, 12, 7}
    };
    int n = 7;
    int selected[7];

    int count = activity_selection(activities, n, selected);
    printf("选择了 %d 个活动: ", count);
    for (int i = 0; i < count; i++) {
        printf("%d ", selected[i]);
    }
    printf("\n");

    return 0;
}
```

#### Go 示例 - 贪心
```go
package main

import (
    "fmt"
    "sort"
)

// 活动定义
type Activity struct {
    Start int
    End   int
}

// 活动选择：贪心选择最多不重叠的活动
func ActivitySelection(activities []Activity) []Activity {
    // 按结束时间排序
    sort.Slice(activities, func(i, j int) bool {
        return activities[i].End < activities[j].End
    })

    // 选择第一个活动
    selected := []Activity{activities[0]}
    lastEnd := activities[0].End

    // 贪心选择后续活动
    for i := 1; i < len(activities); i++ {
        if activities[i].Start >= lastEnd {
            selected = append(selected, activities[i])
            lastEnd = activities[i].End
        }
    }

    return selected
}

func main() {
    activities := []Activity{
        {1, 3}, {0, 5}, {3, 9}, {4, 10}, {6, 8}, {7, 11}, {9, 12},
    }

    result := ActivitySelection(activities)
    fmt.Printf("选择了 %d 个活动\n", len(result))
}
```

### 贪心算法的通用框架

```python
def greedy_algorithm(problem):
    # 1. 预处理：排序或初始化
    candidates = preprocess(problem)

    # 2. 初始化结果
    result = []

    # 3. 迭代做出贪心选择
    while candidates is not empty:
        # 选择当前最优的候选
        choice = select_best_candidate(candidates)

        # 检查是否可行
        if is_feasible(result, choice):
            # 加入结果
            result.append(choice)
            # 更新剩余候选
            candidates = remove_incompatible(candidates, choice)
        else:
            # 移除不可行的候选
            candidates.remove(choice)

    return result
```

### 常见陷阱
1. **贪心选择标准不当**：选择的标准不能保证全局最优
2. **忽视约束条件**：没有正确处理问题的约束
3. **缺少可行性检查**：没有验证选择的可行性
4. **错误假设**：对问题性质的假设错误
5. **没有反例验证**：未用反例验证贪心的正确性

### 学习建议
1. 理解问题是否具有贪心选择性质
2. 明确贪心的选择标准（通常通过排序实现）
3. 用小例子手工验证贪心选择的正确性
4. 尝试寻找反例来证伪不合适的贪心策略
5. 对比贪心和其他方法（如动态规划）的结果
6. 学会证明贪心的正确性（数学归纳法）
