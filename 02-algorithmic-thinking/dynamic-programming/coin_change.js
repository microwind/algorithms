/**
 * 硬币兑换问题 (Coin Change) - 动态规划应用
 *
 * 问题描述：
 * 给定不同面值的硬币和一个金额，找出使用最少数量的硬币凑出该金额
 *
 * 动态规划方程：
 * dp[i] = min(dp[i], dp[i-coin] + 1) for each coin
 *
 * 时间复杂度: O(n * amount)
 * 空间复杂度: O(amount)
 */

/**
 * 硬币兑换 - 求最少硬币数量
 */
function coinChange(coins, amount) {
    if (amount === 0) return 0;

    // dp[i] 表示凑出金额 i 需要的最少硬币数
    // 初始化为 amount + 1，表示无法凑出
    const dp = Array(amount + 1).fill(amount + 1);
    dp[0] = 0;

    // 对每个金额进行处理
    for (let i = 1; i <= amount; i++) {
        // 尝试使用每枚硬币
        for (const coin of coins) {
            if (coin <= i) {
                // 如果可以使用该硬币，更新最少数量
                dp[i] = Math.min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    // 如果 dp[amount] > amount，说明无法凑出
    return dp[amount] > amount ? -1 : dp[amount];
}

/**
 * 硬币兑换 - 返回具体的硬币组合
 */
function coinChangeWithCoins(coins, amount) {
    if (amount === 0) return [0, []];

    // dp[i] 表示凑出金额 i 需要的最少硬币数
    const dp = Array(amount + 1).fill(amount + 1);
    // parent[i] 表示凑出金额 i 时使用的硬币面值
    const parent = Array(amount + 1).fill(-1);

    dp[0] = 0;

    // 对每个金额进行处理
    for (let i = 1; i <= amount; i++) {
        // 尝试使用每枚硬币
        for (const coin of coins) {
            if (coin <= i && dp[i - coin] + 1 < dp[i]) {
                dp[i] = dp[i - coin] + 1;
                parent[i] = coin;
            }
        }
    }

    // 如果无法凑出
    if (dp[amount] > amount) {
        return [-1, []];
    }

    // 反向追踪构建硬币组合
    const result = [];
    let idx = amount;
    while (idx > 0) {
        const coin = parent[idx];
        result.push(coin);
        idx -= coin;
    }

    return [dp[amount], result];
}

// 测试函数
console.log("=== 硬币兑换问题 ===\n");

// 测试用例1：基本硬币兑换
console.log("1. 基本硬币兑换");
const coins1 = [1, 2, 5];
const amount1 = 5;
console.log("硬币面值:", coins1);
console.log("需要凑出的金额:", amount1);
console.log("最少硬币数:", coinChange(coins1, amount1));
console.log();

// 测试用例2：返回具体的硬币组合
console.log("2. 返回具体的硬币组合");
const coins2 = [1, 2, 5];
const amount2 = 7;
console.log("硬币面值:", coins2);
console.log("需要凑出的金额:", amount2);
const [count, combination] = coinChangeWithCoins(coins2, amount2);
console.log("最少硬币数:", count);
console.log("硬币组合:", combination);
console.log();

// 测试用例3：无法凑出的金额
console.log("3. 无法凑出的金额");
const coins3 = [2, 5];
const amount3 = 3;
console.log("硬币面值:", coins3);
console.log("需要凑出的金额:", amount3);
console.log("最少硬币数:", coinChange(coins3, amount3));
console.log();

// 测试用例4：更大的金额
console.log("4. 更大的金额");
const coins4 = [1, 3, 4];
const amount4 = 10;
console.log("硬币面值:", coins4);
console.log("需要凑出的金额:", amount4);
const [count4, combination4] = coinChangeWithCoins(coins4, amount4);
console.log("最少硬币数:", count4);
console.log("硬币组合:", combination4);
