/*
*
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

// / 硬币兑换 - 求最少硬币数量
pub fn coin_change(coins: &[i32], amount: usize) -> i32 {
    if amount == 0 {
        return 0;
    }

    // dp[i] 表示凑出金额 i 需要的最少硬币数
    // 初始化为 (amount + 1)，表示无法凑出
    let mut dp = vec![amount as i32 + 1; amount + 1];
    dp[0] = 0;

    // 对每个金额进行处理
    for i in 1..=amount {
        // 尝试使用每枚硬币
        for &coin in coins {
            let coin = coin as usize;
            if coin <= i {
                // 如果可以使用该硬币，更新最少数量
                dp[i] = std::cmp::min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    // 如果 dp[amount] > amount，说明无法凑出
    if dp[amount] > amount as i32 {
        -1
    } else {
        dp[amount]
    }
}

// / 硬币兑换 - 返回具体的硬币组合
pub fn coin_change_with_coins(coins: &[i32], amount: usize) -> (i32, Vec<i32>) {
    if amount == 0 {
        return (0, Vec::new());
    }

    // dp[i] 表示凑出金额 i 需要的最少硬币数
    let mut dp = vec![amount as i32 + 1; amount + 1];
    // parent[i] 表示凑出金额 i 时使用的硬币面值
    let mut parent = vec![-1; amount + 1];

    dp[0] = 0;

    // 对每个金额进行处理
    for i in 1..=amount {
        // 尝试使用每枚硬币
        for &coin in coins {
            let coin = coin as usize;
            if coin <= i && dp[i - coin] + 1 < dp[i] {
                dp[i] = dp[i - coin] + 1;
                parent[i] = coin as i32;
            }
        }
    }

    // 如果无法凑出
    if dp[amount] > amount as i32 {
        return (-1, Vec::new());
    }

    // 反向追踪构建硬币组合
    let mut result = Vec::new();
    let mut idx = amount;
    while idx > 0 {
        let coin = parent[idx];
        result.push(coin);
        idx -= coin as usize;
    }

    (dp[amount], result)
}

fn main() {
    println!("=== 硬币兑换问题 ===\n");

    // 测试用例1：基本硬币兑换
    println!("1. 基本硬币兑换");
    let coins1 = vec![1, 2, 5];
    let amount1 = 5;
    println!("硬币面值: {:?}", coins1);
    println!("需要凑出的金额: {}", amount1);
    println!("最少硬币数: {}\n", coin_change(&coins1, amount1));

    // 测试用例2：返回具体的硬币组合
    println!("2. 返回具体的硬币组合");
    let coins2 = vec![1, 2, 5];
    let amount2 = 7;
    println!("硬币面值: {:?}", coins2);
    println!("需要凑出的金额: {}", amount2);
    let (count, combination) = coin_change_with_coins(&coins2, amount2);
    println!("最少硬币数: {}", count);
    println!("硬币组合: {:?}\n", combination);

    // 测试用例3：无法凑出的金额
    println!("3. 无法凑出的金额");
    let coins3 = vec![2, 5];
    let amount3 = 3;
    println!("硬币面值: {:?}", coins3);
    println!("需要凑出的金额: {}", amount3);
    println!("最少硬币数: {}\n", coin_change(&coins3, amount3));

    // 测试用例4：更大的金额
    println!("4. 更大的金额");
    let coins4 = vec![1, 3, 4];
    let amount4 = 10;
    println!("硬币面值: {:?}", coins4);
    println!("需要凑出的金额: {}", amount4);
    let (count4, combination4) = coin_change_with_coins(&coins4, amount4);
    println!("最少硬币数: {}", count4);
    println!("硬币组合: {:?}", combination4);
}
