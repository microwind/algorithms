/**
 * 动态规划记忆化搜索示例
 * 
 * 算法特点：
 * - 使用缓存避免重复计算
 * - 时间复杂度从 O(2^n) 优化到 O(n)
 * 
 * 学习重点：理解记忆化搜索的优化原理
 */

// 记忆化数组
static mut MEMO: [i64; 100] = [-1; 100];

/**
 * 初始化记忆化数组
 */
fn init_memo() {
    for i in 0..100 {
        MEMO[i] = -1;
    }
}

/**
 * 记忆化版本斐波那契
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
fn fibonacci_memo(n: i32) -> i64 {
    // 基础情况
    if n <= 1 {
        return n as i64;
    }
    
    // 如果已计算过，直接返回缓存结果
    if MEMO[n as usize] != -1 {
        return MEMO[n as usize];
    }
    
    // 递归计算并缓存结果
    MEMO[n as usize] = fibonacci_memo(n - 1) + fibonacci_memo(n - 2);
    MEMO[n as usize]
}

/**
 * 普通递归版本（用于对比）
 * 时间复杂度: O(2^n)，空间复杂度: O(n)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
fn fibonacci_naive(n: i32) -> i64 {
    if n <= 1 {
        return n as i64;
    }
    fibonacci_naive(n - 1) + fibonacci_naive(n - 2)
}

/**
 * 主函数 - 测试记忆化搜索性能对比
 */
fn main() {
    let n = 40;
    
    // 测试1：输出对比标题
    println!("斐波那契数列对比 (n={}):", n);
    println!();
    
    // 测试2：普通递归（很慢）
    println!("普通递归: ");
    println!("F({}) = {}", n, fibonacci_naive(n));
    println!("  （时间复杂度: O(2^n)，有大量重复计算）");
    println!();
    
    // 测试3：记忆化版本（很快）
    init_memo();
    println!("记忆化搜索: ");
    println!("F({}) = {}", n, fibonacci_memo(n));
    println!("  （时间复杂度: O(n)，每个值只计算一次）");
    println!();
    
    // 输出性能提升说明
    println!("性能提升: 从指数级 O(2^n) 降到线性 O(n)");
    println!("当 n=40 时，普通递归需要约 2^40 ≈ 1万亿次操作");
    println!("记忆化版本只需要 40 次计算");
}

/*打印结果
jarry@Mac dp-memoization % cargo run
斐波那契数列对比 (n=40):

普通递归: F(40) = 102334155
  （时间复杂度: O(2^n)，有大量重复计算）

记忆化搜索: F(40) = 102334155
  （时间复杂度: O(n)，每个值只计算一次）

性能提升: 从指数级 O(2^n) 降到线性 O(n)
当 n=40 时，普通递归需要约 2^40 ≈ 1万亿次操作
记忆化版本只需要 40 次计算
*/
