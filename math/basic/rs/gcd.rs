/*
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 数学基础 - 最大公约数和最小公倍数 (GCD & LCM)
 * 使用欧几里得算法计算GCD
 * 时间复杂度: O(log(min(a, b)))
 */

/**
 * 最大公约数 (GCD) - 欧几里得算法
 *
 * 算法原理：
 * - gcd(a, b) = gcd(b, a mod b)
 * - 当b为0时，gcd(a, 0) = a
 * - 辗转相除，直到余数为0
 *
 * 参数:
 *     a: 第一个正整数
 *     b: 第二个正整数
 * 返回:
 *     两数的最大公约数
 *
 * 时间复杂度: O(log(min(a, b)))
 * 空间复杂度: O(1)
 */
pub fn gcd(a: u32, b: u32) -> u32 {
    let mut a = a;
    let mut b = b;
    while b != 0 {
        let temp = b;
        b = a % b;
        a = temp;
    }
    a
}

/**
 * 递归版本GCD
 */
pub fn gcd_recursive(a: u32, b: u32) -> u32 {
    if b == 0 {
        return a;
    }
    gcd_recursive(b, a % b)
}

/**
 * 最小公倍数 (LCM)
 *
 * 公式: lcm(a, b) = |a × b| / gcd(a, b)
 * 为避免溢出，先除后乘: (a / gcd) × b
 */
pub fn lcm(a: u32, b: u32) -> u32 {
    if a == 0 || b == 0 {
        return 0;
    }
    (a / gcd(a, b)) * b
}

/**
 * 扩展欧几里得算法
 * 返回 (g, x, y) 使得 ax + by = gcd(a, b)
 */
pub fn extended_gcd(a: i64, b: i64) -> (i64, i64, i64) {
    if b == 0 {
        return (a, 1, 0);
    }
    let (g, x1, y1) = extended_gcd(b, a % b);
    let x = y1;
    let y = x1 - (a / b) * y1;
    (g, x, y)
}

/**
 * 批量GCD
 * 计算数组中所有元素的最大公约数
 */
pub fn gcd_of_slice(numbers: &[u32]) -> u32 {
    if numbers.is_empty() {
        return 0;
    }
    numbers.iter().fold(numbers[0], |acc, &x| gcd(acc, x))
}

/**
 * 测试函数
 */
fn test_gcd() {
    println!("========================================");
    println!("    GCD/LCM演示 (最大公约数/最小公倍数)");
    println!("========================================\n");

    // 基本GCD测试
    println!("最大公约数计算:");
    println!("----------------------------------------");
    let test_cases = [(48, 18), (56, 98), (100, 75), (17, 13), (0, 5)];
    for (a, b) in test_cases {
        let g = gcd(a, b);
        let l = lcm(a, b);
        println!("gcd({}, {}) = {}, lcm({}, {}) = {}", a, b, g, a, b, l);
    }

    // 扩展欧几里得
    println!("\n扩展欧几里得算法:");
    println!("----------------------------------------");
    let (a, b) = (30, 12);
    let (g, x, y) = extended_gcd(a, b);
    println!("{} × {} + {} × {} = {} (gcd)", a, x, b, y, g);
    println!("验证: {} + {} = {}", a * x, b * y, a * x + b * y);

    // 数学性质
    println!("\n========================================");
    println!("数学性质:");
    println!("========================================");
    println!("• 交换律: gcd(a, b) = gcd(b, a)");
    println!("• 结合律: gcd(a, gcd(b, c)) = gcd(gcd(a, b), c)");
    println!("• 分配律: gcd(a, lcm(b, c)) = lcm(gcd(a, b), gcd(a, c))");
    println!("• 互素: gcd(a, b) = 1 表示a和b互素");
    println!("• 贝祖定理: 存在x,y使得 ax + by = gcd(a, b)");
}

fn main() {
    test_gcd();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_gcd() {
        assert_eq!(gcd(48, 18), 6);
        assert_eq!(gcd(56, 98), 14);
        assert_eq!(gcd(17, 13), 1);
    }

    #[test]
    fn test_lcm() {
        assert_eq!(lcm(4, 6), 12);
        assert_eq!(lcm(5, 7), 35);
    }

    #[test]
    fn test_extended_gcd() {
        let (g, x, y) = extended_gcd(30, 12);
        assert_eq!(g, 6);
        assert_eq!(30 * x + 12 * y, 6);
    }
}
