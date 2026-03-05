/*
*
 * 0-1 背包问题 - 动态规划的经典应用
 *
 * 时间复杂度: O(n * W)
 * 空间复杂度: O(n * W) 或 O(W)
*/

/*
*
 * 0-1 背包问题 - 二维 DP
*/
function knapsack(weights, values, capacity) {
    const n = weights.length;

    // dp[i][w] 表示前 i 件物品，容量为 w 时的最大价值
    const dp = Array(n + 1).fill(null).map(() => Array(capacity + 1).fill(0));

    // 填充 dp 表，处理每件物品
    for (let i = 1; i <= n; i++) {
        const weight = weights[i - 1];
        const value = values[i - 1];
        // 对于每个容量，选择是否包含当前物品
        for (let w = 0; w <= capacity; w++) {
            if (weight <= w) {
                // 选择或不选择，取最大值
                dp[i][w] = Math.max(
                    dp[i - 1][w],
                    dp[i - 1][w - weight] + value
                );
            } else {
                // 物品太重
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

/*
*
 * 0-1 背包问题 - 空间优化版本
*/
function knapsackOptimized(weights, values, capacity) {
    const n = weights.length;

    // dp[w] 表示容量为 w 时的最大价值
    const dp = Array(capacity + 1).fill(0);

    // 处理每件物品
    for (let i = 0; i < n; i++) {
        const weight = weights[i];
        const value = values[i];

        // 从后向前遍历容量
        for (let w = capacity; w >= weight; w--) {
            dp[w] = Math.max(dp[w], dp[w - weight] + value);
        }
    }

    return dp[capacity];
}

/*
*
 * 0-1 背包问题 - 返回选中物品
*/
function knapsackWithItems(weights, values, capacity) {
    const n = weights.length;

    // 构建 dp 表
    const dp = Array(n + 1).fill(null).map(() => Array(capacity + 1).fill(0));

    for (let i = 1; i <= n; i++) {
        const weight = weights[i - 1];
        const value = values[i - 1];
        // 从前向后遍历容量,更新 dp 表
        for (let w = 0; w <= capacity; w++) {
            if (weight <= w) {
                // 选择或不选择，取最大值
                dp[i][w] = Math.max(
                    dp[i - 1][w],
                    dp[i - 1][w - weight] + value
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // 反向追踪选中的物品
    const selected = [];
    let w = capacity;
    for (let i = n; i > 0; i--) {
        if (dp[i][w] !== dp[i - 1][w]) {
            selected.push(i - 1);
            w -= weights[i - 1];
        }
    }

    return [dp[n][capacity], selected.reverse()];
}

// 测试函数
console.log("=== 0-1 背包问题 ===\n");

// 测试用例1：基本背包问题
console.log("1. 基本背包问题");
const weights = [2, 3, 4, 5];
const values = [3, 4, 5, 6];
const capacity = 8;

console.log("物品重量:", weights);
console.log("物品价值:", values);
console.log("背包容量:", capacity);

const maxValue = knapsack(weights, values, capacity);
console.log("最大价值:", maxValue);
console.log();

// 测试用例2：空间优化版本
console.log("2. 空间优化版本");
const maxValueOpt = knapsackOptimized(weights, values, capacity);
console.log("最大价值（优化）:", maxValueOpt);
console.log();

// 测试用例3：返回选中物品
console.log("3. 返回选中物品");
const [maxVal, selected] = knapsackWithItems(weights, values, capacity);
console.log("最大价值:", maxVal);
console.log("选中物品索引:", selected);
console.log();

// 测试用例4：容量较大
console.log("4. 容量较大的背包");
const weights2 = [1, 2, 3, 4, 5];
const values2 = [1, 3, 5, 7, 9];
const capacity2 = 10;

console.log("物品重量:", weights2);
console.log("物品价值:", values2);
console.log("背包容量:", capacity2);

const maxValue2 = knapsack(weights2, values2, capacity2);
console.log("最大价值:", maxValue2);
