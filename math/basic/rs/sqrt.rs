/*
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 数学基础 - 平方根计算 (Square Root)
 * 使用牛顿迭代法计算平方根
 * 时间复杂度: O(log n)
 */

/**
 * 牛顿迭代法计算平方根
 *
 * 算法原理：
 * - 牛顿法（Newton-Raphson）用于求解方程 f(x) = 0
 * - 对于平方根，求解 x² - n = 0
 * - 迭代公式: x_{k+1} = (x_k + n/x_k) / 2
 * - 收敛速度快，二次收敛
 *
 * 参数:
 *     n: 被开方数（非负数）
 *     epsilon: 精度要求
 * 返回:
 *     n的平方根近似值
 *
 * 时间复杂度: O(log(1/ε))
 * 空间复杂度: O(1)
 */
pub fn sqrt_newton(n: f64, epsilon: f64) -> f64 {
    if n < 0.0 {
        panic!("不能对负数开平方");
    }
    if n == 0.0 {
        return 0.0;
    }
    let mut x = n;
    while (x * x - n).abs() > epsilon {
        x = (x + n / x) / 2.0;
    }
    x
}

/**
 * 整数平方根（二分查找法）
 * 返回不大于√n的最大整数
 */
pub fn isqrt(n: u64) -> u64 {
    if n < 2 {
        return n;
    }
    let mut left = 1u64;
    let mut right = n;
    while left < right {
        let mid = (left + right + 1) / 2;
        if mid * mid <= n {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    left
}

/**
 * 测试函数
 */
fn test_sqrt() {
    println!("========================================");
    println!("    平方根计算演示 (Square Root)");
    println!("========================================\n");

    // 基本测试
    println!("牛顿迭代法计算平方根:");
    println!("----------------------------------------");
    let test_cases = [2.0, 3.0, 10.0, 100.0, 0.5, 1e6];
    let epsilon = 1e-10;
    for n in test_cases {
        let result = sqrt_newton(n, epsilon);
        println!("√{} ≈ {} (验证: {}² = {})", n, result, result, result * result);
    }

    // 整数平方根
    println!("\n整数平方根:");
    println!("----------------------------------------");
    let int_cases = [0, 1, 2, 10, 100, 1000, 10000];
    for n in int_cases {
        let result = isqrt(n);
        println!("isqrt({}) = {} ({}² = {} ≤ {} < {}² = {})", 
            n, result, result, result * result, n, result + 1, (result + 1) * (result + 1));
    }

    // 数学性质
    println!("\n========================================");
    println!("平方根性质:");
    println!("========================================");
    println!("• √(ab) = √a × √b");
    println!("• √(a/b) = √a / √b");
    println!("• (√a)² = a");
    println!("• √(a²) = |a|");
    println!("• 牛顿法收敛速度: 二次收敛");
}

fn main() {
    test_sqrt();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_sqrt_newton() {
        let epsilon = 1e-10;
        assert!((sqrt_newton(4.0, epsilon) - 2.0).abs() < epsilon);
        assert!((sqrt_newton(2.0, epsilon) - 1.4142135623730951).abs() < epsilon);
    }

    #[test]
    fn test_isqrt() {
        assert_eq!(isqrt(0), 0);
        assert_eq!(isqrt(1), 1);
        assert_eq!(isqrt(2), 1);
        assert_eq!(isqrt(10), 3);
        assert_eq!(isqrt(100), 10);
    }
}
