/*
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 数学基础 - 幂运算 (Power)
 * 计算底数的指数次幂
 * 使用快速幂算法（二进制幂）
 * 时间复杂度: O(log n)
 */

/**
 * 快速幂算法（Binary Exponentiation）
 *
 * 算法原理：
 * - 将指数分解为二进制形式
 * - 利用幂的性质：a^(2k) = (a^2)^k
 * - 通过平方和乘法组合得到结果
 *
 * 示例: 计算 a^13
 * 13 = 1101₂ = 8 + 4 + 1
 * a^13 = a^8 × a^4 × a^1
 *
 * 参数:
 *     base: 底数
 *     exp: 指数（可为负数）
 * 返回:
 *     base^exp 的结果
 *
 * 时间复杂度: O(log |exp|)
 * 空间复杂度: O(1)
 */
pub fn power(base: f64, exp: i32) -> f64 {
    if exp < 0 {
        return 1.0 / power(base, -exp);
    }
    if exp == 0 {
        return 1.0;
    }
    let mut result = 1.0;
    let mut current = base;
    let mut e = exp;
    while e > 0 {
        if e & 1 == 1 {
            result *= current;
        }
        current *= current;
        e >>= 1;
    }
    result
}

/**
 * 整数快速幂
 * 计算 (base^exp) % mod
 * 用于大数幂运算取模
 */
pub fn power_mod(base: u64, exp: u64, modulus: u64) -> u64 {
    if modulus == 1 {
        return 0;
    }
    let mut result = 1u64;
    let mut base = base % modulus;
    let mut exp = exp;
    while exp > 0 {
        if exp & 1 == 1 {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp >>= 1;
    }
    result
}

/**
 * 递归版本幂运算
 */
pub fn power_recursive(base: f64, exp: i32) -> f64 {
    if exp < 0 {
        return 1.0 / power_recursive(base, -exp);
    }
    if exp == 0 {
        return 1.0;
    }
    if exp % 2 == 0 {
        let half = power_recursive(base, exp / 2);
        half * half
    } else {
        base * power_recursive(base, exp - 1)
    }
}

/**
 * 测试函数
 */
fn test_power() {
    println!("========================================");
    println!("    幂运算演示 (Power)");
    println!("========================================\n");

    // 基本幂运算
    println!("基本幂运算:");
    println!("----------------------------------------");
    let test_cases = [(2.0, 10), (3.0, 5), (5.0, 3), (2.0, -3), (10.0, 6)];
    for (base, exp) in test_cases {
        let result = power(base, exp);
        println!("{}^{} = {}", base, exp, result);
    }

    // 模幂运算
    println!("\n模幂运算 (用于密码学):");
    println!("----------------------------------------");
    println!("2^100 mod 1000 = {}", power_mod(2, 100, 1000));
    println!("3^50 mod 1000000007 = {}", power_mod(3, 50, 1000000007));

    // 性能对比
    println!("\n========================================");
    println!("性能优势:");
    println!("========================================");
    println!("• 朴素算法: O(n) 次乘法");
    println!("• 快速幂算法: O(log n) 次乘法");
    println!("• 计算 2^1000000:");
    println!("  - 朴素: 需要 1,000,000 次乘法");
    println!("  - 快速幂: 仅需 20 次乘法");

    // 应用场景
    println!("\n应用场景:");
    println!("----------------------------------------");
    println!("• 密码学: RSA加密中的模幂运算");
    println!("• 矩阵快速幂: 斐波那契数列O(log n)解法");
    println!("• 科学计算: 指数增长/衰减模型");
    println!("• 组合数学: 大数幂运算取模");
}

fn main() {
    test_power();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_power() {
        assert_eq!(power(2.0, 10), 1024.0);
        assert_eq!(power(3.0, 3), 27.0);
        assert_eq!(power(2.0, -2), 0.25);
    }

    #[test]
    fn test_power_mod() {
        assert_eq!(power_mod(2, 10, 1000), 24);
        assert_eq!(power_mod(3, 5, 100), 43);
    }
}
