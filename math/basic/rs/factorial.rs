/*
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 数学基础 - 阶乘计算 (Factorial)
 * 计算非负整数的阶乘 n!
 * 支持递归、迭代和大数计算
 * 时间复杂度: O(n)
 */

use num_bigint::BigInt;
use num_traits::{One, FromPrimitive};

/**
 * 迭代计算阶乘
 *
 * 算法原理：
 * - n! = 1 × 2 × 3 × ... × n
 * - 0! = 1（空积的定义）
 *
 * 参数:
 *     n: 非负整数（n ≤ 20，避免u64溢出）
 * 返回:
 *     n! 的结果
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
pub fn factorial_iterative(n: u32) -> u64 {
    if n > 20 {
        panic!("n太大，会导致u64溢出，请使用factorial_big");
    }
    
    let mut result: u64 = 1;
    for i in 2..=n {
        result *= i as u64;
    }
    result
}

/**
 * 递归计算阶乘
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n) - 递归栈
 */
pub fn factorial_recursive(n: u32) -> u64 {
    if n <= 1 {
        return 1;
    }
    (n as u64) * factorial_recursive(n - 1)
}

/**
 * 尾递归优化版本
 */
pub fn factorial_tail_recursive(n: u32, accumulator: u64) -> u64 {
    if n <= 1 {
        return accumulator;
    }
    factorial_tail_recursive(n - 1, accumulator * (n as u64))
}

/**
 * 大数阶乘计算
 *
 * 可以计算任意大的阶乘
 */
pub fn factorial_big(n: u64) -> BigInt {
    let mut result = BigInt::one();
    for i in 2..=n {
        result *= BigInt::from_u64(i).unwrap();
    }
    result
}

/**
 * 使用迭代器计算阶乘（函数式风格）
 */
pub fn factorial_iterator(n: u32) -> u64 {
    if n <= 1 {
        return 1;
    }
    (2..=n).map(|x| x as u64).product()
}

/**
 * 排列数 P(n, k) = n! / (n-k)!
 */
pub fn permutation(n: u32, k: u32) -> u64 {
    if k > n {
        panic!("k必须在0到n之间");
    }
    if n > 20 {
        panic!("n太大");
    }
    
    let mut result: u64 = 1;
    for i in (n - k + 1)..=n {
        result *= i as u64;
    }
    result
}

/**
 * 组合数 C(n, k) = n! / (k! × (n-k)!)
 */
pub fn combination(n: u32, k: u32) -> u64 {
    if k > n {
        panic!("k必须在0到n之间");
    }
    
    let k = if k > n / 2 { n - k } else { k };
    
    if n > 20 {
        panic!("n太大");
    }
    
    let mut result: u64 = 1;
    for i in 1..=k {
        result = result * (n - k + i) as u64 / i as u64;
    }
    result
}

/**
 * 双阶乘 n!!
 */
pub fn double_factorial(n: u32) -> u64 {
    if n > 30 {
        panic!("n太大，会导致溢出");
    }
    
    let mut result: u64 = 1;
    let mut i = n;
    while i > 0 {
        result *= i as u64;
        i = if i >= 2 { i - 2 } else { 0 };
    }
    result
}

/**
 * 测试函数
 */
fn test_factorial() {
    println!("==================================================");
    println!("    阶乘计算演示 (Factorial n!) - Rust");
    println!("==================================================");
    println!();
    
    // 阶乘表
    println!("阶乘表 (0! 到 20!):");
    println!("--------------------------------------------------");
    for i in 0..=20 {
        let result = factorial_iterative(i);
        println!("{:2}! = {:20}", i, result);
    }
    
    // 大数阶乘
    println!("\n==================================================");
    println!("大数阶乘 (使用num-bigint):");
    println!("==================================================");
    for n in [50, 100, 200, 500] {
        let fact_n = factorial_big(n);
        let digits = fact_n.to_string().len();
        println!("{}! 的位数: {}", n, digits);
    }
    
    // 显示100!的前50位和后20位
    let fact100 = factorial_big(100);
    let fact100_str = fact100.to_string();
    println!("\n100! = {}...{}", &fact100_str[..50], &fact100_str[fact100_str.len()-20..]);
    
    // 排列组合
    println!("\n==================================================");
    println!("排列组合计算:");
    println!("==================================================");
    println!("P(10, 3) = {} (从10个中取3个排列)", permutation(10, 3));
    println!("C(10, 3) = {} (从10个中取3个组合)", combination(10, 3));
    println!("C(52, 5) = {} (扑克牌5张组合数)", combination(52, 5));
    
    // 双阶乘
    println!("\n==================================================");
    println!("双阶乘:");
    println!("==================================================");
    for n in 1..=15 {
        let df = double_factorial(n);
        println!("{:2}!! = {}", n, df);
    }
    
    // 杨辉三角
    println!("\n==================================================");
    println!("杨辉三角（前8行）:");
    println!("==================================================");
    for n in 0..8 {
        // 前导空格
        for _ in 0..(7-n) {
            print!("  ");
        }
        for k in 0..=n {
            print!("{:4} ", combination(n, k));
        }
        println!();
    }
    
    // 数学性质
    println!("\n==================================================");
    println!("阶乘的数学性质:");
    println!("==================================================");
    println!("• 定义: n! = n × (n-1) × ... × 2 × 1");
    println!("• 递推: n! = n × (n-1)!");
    println!("• 0! = 1（空积的定义）");
    println!("• 增长: 阶乘比指数增长更快");
    println!("• 斯特林近似: n! ≈ √(2πn) × (n/e)^n");
    
    // 应用场景
    println!("\n==================================================");
    println!("应用场景:");
    println!("==================================================");
    println!("• 排列组合: 计算可能性的总数");
    println!("• 概率论: 生日问题、洗牌算法");
    println!("• 泰勒级数: e^x = Σ x^n/n!");
    println!("• 图论: 计算不同图的数量");
    println!("• 密码学: 密钥空间计算");
    
    // Rust特性
    println!("\n==================================================");
    println!("Rust特性:");
    println!("==================================================");
    println!("• 类型安全: 编译时类型检查");
    println!("• 所有权系统: 无垃圾回收的内存安全");
    println!("• 模式匹配: 强大的match表达式");
    println!("• 迭代器: 零开销抽象");
    println!("• 大数支持: num-bigint库");
    println!("• 零成本抽象: 高性能保证");
}

fn main() {
    test_factorial();
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_factorial_basic() {
        assert_eq!(factorial_iterative(0), 1);
        assert_eq!(factorial_iterative(1), 1);
        assert_eq!(factorial_iterative(5), 120);
        assert_eq!(factorial_iterative(10), 3628800);
    }
    
    #[test]
    fn test_permutation() {
        assert_eq!(permutation(5, 2), 20);
        assert_eq!(permutation(10, 3), 720);
    }
    
    #[test]
    fn test_combination() {
        assert_eq!(combination(5, 2), 10);
        assert_eq!(combination(10, 3), 120);
        assert_eq!(combination(52, 5), 2598960);
    }
    
    #[test]
    fn test_double_factorial() {
        assert_eq!(double_factorial(5), 15);  // 5×3×1 = 15
        assert_eq!(double_factorial(6), 48);  // 6×4×2 = 48
    }
}
