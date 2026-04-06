/**
 * 斐波那契数列多实现方式教学示例
 * 
 * 包含四种实现：
 * - 纯递归：O(2^n) 时间复杂度
 * - 记忆化递归：O(n) 时间复杂度
 * - 动态规划：O(n) 时间复杂度
 * - 优化DP：O(n) 时间复杂度，O(1) 空间复杂度
 * 
 * 核心公式：F(n) = F(n-1) + F(n-2), F(0) = 0, F(1) = 1
 * 
 * 学习重点：掌握不同优化策略的性能差异
 */
use std::collections::HashMap;

// 记忆化缓存
lazy_static mut MEMO: std::sync::Mutex<HashMap<i32, i64>> = std::sync::Mutex::new(HashMap::new());

/**
 * 纯递归实现 - 最慢版本
 * 时间复杂度: O(2^n)，空间复杂度: O(n)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
fn fib_naive(n: i32) -> i64 {
    // 基本情况
    if n <= 1 {
        return n as i64;
    }
    
    // 递归调用
    fib_naive(n - 1) + fib_naive(n - 2)
}

/**
 * 记忆化递归实现 - 推荐版本
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
fn fib_memo(n: i32) -> i64 {
    let mut memo = MEMO.lock().unwrap();
    
    // 检查缓存
    if let Some(&val) = memo.get(&n) {
        return *val;
    }
    
    // 基本情况
    if n <= 1 {
        memo.insert(n, n as i64);
        return n as i64;
    }
    
    // 计算并缓存结果
    let result = fib_memo(n - 1) + fib_memo(n - 2);
    memo.insert(n, result);
    result
}

/**
 * 动态规划实现
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
fn fib_dp(n: i32) -> i64 {
    // 基本情况
    if n <= 1 {
        return n as i64;
    }
    
    // DP数组
    let mut dp = vec![0i64; (n + 1) as usize];
    dp[0] = 0;
    dp[1] = 1;
    
    // 填充DP数组
    for i in 2..=n {
        dp[i as usize] = dp[i - 1] + dp[i - 2];
    }
    
    dp[n as usize]
}

/**
 * 优化动态规划实现 - 空间优化
 * 时间复杂度: O(n)，空间复杂度: O(1)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
fn fib_optimized(n: i32) -> i64 {
    // 基本情况
    if n <= 1 {
        return n as i64;
    }
    
    // 前两个数
    let (mut prev, mut curr) = (0i64, 1i64);
    
    // 迭代计算
    for _ in 2..=n {
        let next = prev + curr;
        prev = curr;
        curr = next;
    }
    
    curr
}

/**
 * 主函数 - 性能对比测试
 */
fn main() {
    let n = 30i32;
    println!("计算第 {} 个斐波那契数", n);
    
    // 测试记忆化递归
    println!("记忆化递归: {}", fib_memo(n));
    
    // 测试动态规划
    println!("动态规划: {}", fib_dp(n));
    
    // 测试优化DP
    println!("优化DP: {}", fib_optimized(n));
}
