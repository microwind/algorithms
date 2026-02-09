/**
 * 0-1 背包问题 - 动态规划的经典应用
 *
 * 时间复杂度: O(n * W)
 * 空间复杂度: O(n * W) 或 O(W)
 */

/// 0-1 背包问题 - 二维 DP
pub fn knapsack(weights: &[i32], values: &[i32], capacity: usize) -> i32 {
    let n = weights.len();

    // dp[i][w] 表示前 i 件物品，容量为 w 时的最大价值
    let mut dp = vec![vec![0; capacity + 1]; n + 1];

    // 填充 dp 表
    for i in 1..=n {
        let weight = weights[i - 1] as usize;
        let value = values[i - 1];

        for w in 0..=capacity {
            if weight <= w {
                // 选择或不选择
                dp[i][w] = std::cmp::max(
                    dp[i - 1][w],
                    dp[i - 1][w - weight] + value,
                );
            } else {
                // 物品太重
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    dp[n][capacity]
}

/// 0-1 背包问题 - 空间优化版本
pub fn knapsack_optimized(weights: &[i32], values: &[i32], capacity: usize) -> i32 {
    let n = weights.len();

    // dp[w] 表示容量为 w 时的最大价值
    let mut dp = vec![0; capacity + 1];

    // 处理每件物品
    for i in 0..n {
        let weight = weights[i] as usize;
        let value = values[i];

        // 从后向前遍历容量
        for w in (weight..=capacity).rev() {
            dp[w] = std::cmp::max(dp[w], dp[w - weight] + value);
        }
    }

    dp[capacity]
}

fn main() {
    println!("=== 0-1 背包问题 ===\n");

    // 测试用例1：基本背包问题
    println!("1. 基本背包问题");
    let weights = vec![2, 3, 4, 5];
    let values = vec![3, 4, 5, 6];
    let capacity = 8;

    println!("物品重量: {:?}", weights);
    println!("物品价值: {:?}", values);
    println!("背包容量: {}", capacity);

    let max_value = knapsack(&weights, &values, capacity);
    println!("最大价值: {}\n", max_value);

    // 测试用例2：空间优化版本
    println!("2. 空间优化版本");
    let max_value_opt = knapsack_optimized(&weights, &values, capacity);
    println!("最大价值（优化）: {}\n", max_value_opt);

    // 测试用例3：容量较大
    println!("3. 容量较大的背包");
    let weights2 = vec![1, 2, 3, 4, 5];
    let values2 = vec![1, 3, 5, 7, 9];
    let capacity2 = 10;

    println!("物品重量: {:?}", weights2);
    println!("物品价值: {:?}", values2);
    println!("背包容量: {}", capacity2);

    let max_value2 = knapsack(&weights2, &values2, capacity2);
    println!("最大价值: {}", max_value2);
}
