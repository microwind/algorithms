/*
 * 零钱兑换问题 - 贪心算法
 *
 * 算法：
 * - 使用贪心策略：每次选择不超过剩余金额的最大面值硬币
 * - 持续用最大面值硬币去抵扣，直到金额为 0
 * - 注意：这种贪心解并不总是最优
 */

#[derive(Debug)]
struct CoinChangeResult {
    count: i32,
    coins: Vec<i32>,
}

impl std::fmt::Display for CoinChangeResult {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        if self.count == -1 {
            write!(f, "Impossible")
        } else {
            write!(f, "{} coins: {:?}", self.count, self.coins)
        }
    }
}

// 使用贪心算法求最少硬币数（不一定最优）
fn coin_change_greedy(coins: &[i32], amount: i32) -> CoinChangeResult {
    if amount == 0 {
        return CoinChangeResult {
            count: 0,
            coins: vec![],
        };
    }

    // 将硬币面值按降序排序
    let mut sorted_coins = coins.to_vec();
    sorted_coins.sort_by(|a, b| b.cmp(a));

    let mut count = 0;
    let mut coins_used = vec![];
    let mut remaining = amount;

    // 尽量多用当前面额的硬币，直到剩余金额小于当前面额
    for coin in sorted_coins {
        while remaining >= coin {
            remaining -= coin;
            coins_used.push(coin);
            count += 1;
        }
    }

    if remaining != 0 {
        return CoinChangeResult {
            count: -1,
            coins: vec![],
        };
    }

    CoinChangeResult {
        count,
        coins: coins_used,
    }
}

// 使用动态规划求最少硬币数（一定最优）
fn coin_change_dp(coins: &[i32], amount: i32) -> CoinChangeResult {
    if amount == 0 {
        return CoinChangeResult {
            count: 0,
            coins: vec![],
        };
    }

    let n = (amount + 1) as usize;
    let mut dp = vec![i32::MAX; n];
    dp[0] = 0;
    let mut parent = vec![-1; n];

    // 对每个金额进行处理, 尝试使用每枚硬币
    for curr_amount in 1..=amount as usize {
        for &coin in coins {
            // 如果当前硬币面额小于等于当前金额，并且当前金额减去当前硬币面额的值不为最大值，则更新当前金额的最少硬币数
            if coin as usize <= curr_amount && dp[curr_amount - coin as usize] != i32::MAX {
                // 如果当前金额减去当前硬币面额的值的最少硬币数加1小于当前金额的最少硬币数，则更新当前金额的最少硬币数
                if dp[curr_amount - coin as usize] + 1 < dp[curr_amount] {
                    dp[curr_amount] = dp[curr_amount - coin as usize] + 1;
                    parent[curr_amount] = coin;
                }
            }
        }
    }

    if dp[amount as usize] == i32::MAX {
        return CoinChangeResult {
            count: -1,
            coins: vec![],
        };
    }

    // 还原一组最优解中使用的硬币
    let mut coins_used = vec![];
    let mut curr = amount as usize;
    while curr > 0 {
        let coin = parent[curr] as usize;
        coins_used.push(parent[curr]);
        curr -= coin;
    }

    CoinChangeResult {
        count: dp[amount as usize],
        coins: coins_used,
    }
}

fn compare_greedy_vs_dp(coins: &[i32], amount: i32) {
    let greedy = coin_change_greedy(coins, amount);
    let dp = coin_change_dp(coins, amount);

    println!("Coins: {:?}, Amount: {}", coins, amount);
    println!("Greedy: {}", greedy);
    println!("DP:     {}", dp);

    if greedy.count != -1 && dp.count != -1 {
        if greedy.count == dp.count {
            println!("✓ Greedy is optimal for this input");
        } else {
            println!(
                "✗ Greedy is suboptimal (difference: {})",
                greedy.count - dp.count
            );
        }
    }
    println!();
}

fn test_standard_coins() {
    println!("\n[Test 1] US Coins (greedy optimal)");
    let result = coin_change_greedy(&[1, 5, 10, 25], 41);
    println!("Coins: [1, 5, 10, 25], Amount: 41");
    println!("Result: {}", result);
}

fn test_greedy_fails1() {
    println!("\n[Test 2] Greedy fails case");
    compare_greedy_vs_dp(&[1, 3, 4], 6);
}

fn test_greedy_fails2() {
    println!("\n[Test 3] Another greedy fails case");
    compare_greedy_vs_dp(&[1, 7, 10], 11);
}

fn test_greedy_optimal() {
    println!("\n[Test 4] Greedy optimal case");
    compare_greedy_vs_dp(&[1, 5, 10, 25], 30);
}

fn test_impossible_amount() {
    println!("\n[Test 5] Impossible amount (no 1-cent coin)");
    let result = coin_change_greedy(&[5, 10, 25], 11);
    println!("Coins: [5, 10, 25], Amount: 11");
    println!("Result: {}", result);
}

fn test_zero_amount() {
    println!("\n[Test 6] Zero amount");
    let result = coin_change_greedy(&[1, 5, 10], 0);
    println!("Coins: [1, 5, 10], Amount: 0");
    println!("Result: {}", result);
}

fn test_single_coin_type() {
    println!("\n[Test 7] Single coin type");
    compare_greedy_vs_dp(&[7], 21);
}

fn test_large_amount() {
    println!("\n[Test 8] Large amount");
    let result = coin_change_greedy(&[1, 5, 10, 25, 50], 158);
    println!("Coins: [1, 5, 10, 25, 50], Amount: 158");
    println!("Result: {}", result);
}

fn test_non_standard_coins() {
    println!("\n[Test 9] Non-standard coins where greedy fails");
    compare_greedy_vs_dp(&[1, 3, 4, 5], 13);
}

fn test_edge_case() {
    println!("\n[Test 10] Larger denomination problem");
    compare_greedy_vs_dp(&[2, 5, 10], 11);
}

fn main() {
    println!("==================================================");
    println!("COIN CHANGE - Greedy vs DP Comparison (Rust)");
    println!("==================================================");

    test_standard_coins();
    test_greedy_fails1();
    test_greedy_fails2();
    test_greedy_optimal();
    test_impossible_amount();
    test_zero_amount();
    test_single_coin_type();
    test_large_amount();
    test_non_standard_coins();
    test_edge_case();
}
