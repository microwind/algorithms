/**
 * 编辑距离 (Edit Distance / Levenshtein Distance) - 动态规划应用
 *
 * 问题描述：
 * 给定两个字符串，计算从一个字符串转换到另一个字符串所需的最少编辑操作数
 *
 * 动态规划方程：
 * if s1[i-1] == s2[j-1]:
 *     dp[i][j] = dp[i-1][j-1]
 * else:
 *     dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
 *
 * 时间复杂度: O(m * n)
 * 空间复杂度: O(m * n)
 */

/// 编辑距离 - 求最少操作数
pub fn edit_distance(s1: &str, s2: &str) -> usize {
    let s1_chars: Vec<char> = s1.chars().collect();
    let s2_chars: Vec<char> = s2.chars().collect();
    let m = s1_chars.len();
    let n = s2_chars.len();

    // dp[i][j] 表示将 s1[0:i] 转换到 s2[0:j] 的最少操作数
    let mut dp = vec![vec![0; n + 1]; m + 1];

    // 初始化
    for j in 0..=n {
        dp[0][j] = j;
    }
    for i in 0..=m {
        dp[i][0] = i;
    }

    // 填充 DP 表
    for i in 1..=m {
        for j in 1..=n {
            if s1_chars[i - 1] == s2_chars[j - 1] {
                // 字符相同，不需要操作
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // 字符不同，选择最少操作数的方案
                dp[i][j] = 1 + std::cmp::min(
                    std::cmp::min(dp[i - 1][j], dp[i][j - 1]),  // 删除或插入
                    dp[i - 1][j - 1],                            // 替换
                );
            }
        }
    }

    dp[m][n]
}

/// 编辑距离 - 空间优化版本
pub fn edit_distance_optimized(s1: &str, s2: &str) -> usize {
    let s1_chars: Vec<char> = s1.chars().collect();
    let s2_chars: Vec<char> = s2.chars().collect();
    let (mut m, mut n) = (s1_chars.len(), s2_chars.len());

    // 确保第一个字符串是较短的
    let (s1_chars, s2_chars) = if m > n {
        (s2_chars, s1_chars)
    } else {
        (s1_chars, s2_chars)
    };
    if m > n {
        std::mem::swap(&mut m, &mut n);
    }

    // 使用两行数组来计算
    let mut prev = (0..=n).collect::<Vec<_>>();
    let mut curr = vec![0; n + 1];

    for i in 1..=m {
        curr[0] = i;

        for j in 1..=n {
            if s1_chars[i - 1] == s2_chars[j - 1] {
                curr[j] = prev[j - 1];
            } else {
                curr[j] = 1 + std::cmp::min(
                    std::cmp::min(prev[j], curr[j - 1]),  // 删除或插入
                    prev[j - 1],                           // 替换
                );
            }
        }

        // 交换行
        std::mem::swap(&mut prev, &mut curr);
    }

    prev[n]
}

fn main() {
    println!("=== 编辑距离问题 ===\n");

    // 测试用例1：基本编辑距离
    println!("1. 基本编辑距离");
    let s1_1 = "horse";
    let s2_1 = "ros";
    println!("字符串1: {}", s1_1);
    println!("字符串2: {}", s2_1);
    println!("编辑距离: {}\n", edit_distance(s1_1, s2_1));

    // 测试用例2：相同字符串
    println!("2. 相同字符串");
    let s1_2 = "hello";
    let s2_2 = "hello";
    println!("字符串1: {}", s1_2);
    println!("字符串2: {}", s2_2);
    println!("编辑距离: {}\n", edit_distance(s1_2, s2_2));

    // 测试用例3：空字符串
    println!("3. 空字符串");
    let s1_3 = "abc";
    let s2_3 = "";
    println!("字符串1: {}", s1_3);
    println!("字符串2: {}", s2_3);
    println!("编辑距离: {}\n", edit_distance(s1_3, s2_3));

    // 测试用例4：不同长度的字符串
    println!("4. 不同长度的字符串");
    let s1_4 = "intention";
    let s2_4 = "execution";
    println!("字符串1: {}", s1_4);
    println!("字符串2: {}", s2_4);
    println!("编辑距离: {}", edit_distance(s1_4, s2_4));
    println!("编辑距离（优化）: {}", edit_distance_optimized(s1_4, s2_4));
}
