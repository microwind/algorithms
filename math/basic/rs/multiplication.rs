/*
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 数学基础 - 乘法运算 (Multiplication)
 * 实现基本的乘法运算和溢出检查
 * 时间复杂度: O(1)
 */

/**
 * 基本乘法运算
 *
 * 参数:
 *     a: 被乘数
 *     b: 乘数
 * 返回:
 *     两数之积
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */
pub fn multiply(a: i32, b: i32) -> i32 {
    a * b
}

/**
 * 安全乘法（溢出检查）
 *
 * 使用Rust内置的checked_mul进行溢出检测
 * 当发生溢出时返回None
 */
pub fn safe_multiply(a: i32, b: i32) -> Option<i32> {
    a.checked_mul(b)
}

/**
 * 批量乘法
 * 计算数组中所有元素的乘积
 */
pub fn product(numbers: &[i32]) -> i64 {
    numbers.iter().fold(1i64, |acc, &x| acc * x as i64)
}

/**
 * 幂运算（使用乘法实现）
 */
pub fn power_by_multiply(base: i32, exp: u32) -> i64 {
    let mut result = 1i64;
    let base = base as i64;
    for _ in 0..exp {
        result *= base;
    }
    result
}

/**
 * 俄罗斯农民乘法（Russian Peasant Multiplication）
 * 不使用乘法运算符实现乘法
 */
pub fn russian_peasant_multiply(mut a: u32, mut b: u32) -> u64 {
    let mut result = 0u64;
    while b > 0 {
        if b & 1 == 1 {
            result += a as u64;
        }
        a <<= 1;
        b >>= 1;
    }
    result
}

/**
 * 测试函数
 */
fn test_multiply() {
    println!("========================================");
    println!("    乘法运算演示 (Multiplication)");
    println!("========================================\n");

    // 基本乘法
    println!("基本乘法:");
    println!("----------------------------------------");
    let test_cases = [(5, 3), (-10, 5), (100, 200), (0, 999), (i32::MAX, 2)];
    for (a, b) in test_cases {
        let result = multiply(a, b);
        let safe_result = safe_multiply(a, b);
        match safe_result {
            Some(val) => println!("{} × {} = {} (安全)", a, b, val),
            None => println!("{} × {} = 溢出! (使用safe_multiply检测到)", a, b),
        }
    }

    // 数组乘积
    println!("\n数组乘积:");
    println!("----------------------------------------");
    let numbers = vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    println!("数组: {:?}", numbers);
    println!("乘积: {}", product(&numbers));
    println!("10! = {}", product(&numbers));

    // 俄罗斯农民乘法
    println!("\n俄罗斯农民乘法:");
    println!("----------------------------------------");
    let pairs = [(13, 12), (25, 8), (100, 50)];
    for (a, b) in pairs {
        let result = russian_peasant_multiply(a, b);
        println!("{} × {} = {} (使用位运算)", a, b, result);
    }

    // 数学性质
    println!("\n========================================");
    println!("乘法数学性质:");
    println!("========================================");
    println!("• 交换律: a × b = b × a");
    println!("• 结合律: (a × b) × c = a × (b × c)");
    println!("• 分配律: a × (b + c) = a × b + a × c");
    println!("• 零元素: a × 0 = 0");
    println!("• 单位元: a × 1 = a");
}

fn main() {
    test_multiply();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_multiply() {
        assert_eq!(multiply(5, 3), 15);
        assert_eq!(multiply(-10, 5), -50);
        assert_eq!(multiply(0, 100), 0);
    }

    #[test]
    fn test_safe_multiply() {
        assert_eq!(safe_multiply(5, 3), Some(15));
        assert_eq!(safe_multiply(i32::MAX, 2), None); // 溢出
    }

    #[test]
    fn test_russian_peasant() {
        assert_eq!(russian_peasant_multiply(13, 12), 156);
        assert_eq!(russian_peasant_multiply(25, 8), 200);
    }
}
