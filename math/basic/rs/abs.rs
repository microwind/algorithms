/*
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 数学基础 - 绝对值计算 (Absolute Value)
 * 计算数值的绝对值
 * 时间复杂度: O(1)
 */

/**
 * 计算整数的绝对值
 *
 * 算法原理：
 * - 正数：绝对值就是其本身
 * - 负数：绝对值是其相反数
 * - 零：绝对值是零
 *
 * 参数:
 *     n: 要求绝对值的整数
 * 返回:
 *     n的绝对值
 *
 * 时间复杂度: O(1) - 常数时间
 * 空间复杂度: O(1) - 常数空间
 *
 * 注意：对于i32::MIN，-n会溢出，使用wrapping_neg或checked_abs
 */
pub fn absolute_value(n: i32) -> i32 {
    n.abs()
}

/**
 * 使用模式匹配的绝对值
 */
pub fn absolute_value_match(n: i32) -> i32 {
    match n {
        x if x < 0 => -x,
        x => x,
    }
}

/**
 * 安全的绝对值（处理溢出）
 */
pub fn absolute_value_safe(n: i32) -> Option<i32> {
    n.checked_abs()
}

/**
 * 泛型绝对值（适用于所有有符号整数类型）
 */
pub fn absolute_value_generic<T: num_traits::Signed>(n: T) -> T {
    n.abs()
}

/**
 * 浮点数绝对值
 */
pub fn absolute_value_f64(n: f64) -> f64 {
    n.abs()
}

/**
 * 测试函数
 */
fn test_absolute_value() {
    println!("========================================");
    println!("    绝对值计算演示 (Absolute Value)");
    println!("========================================\n");

    // 测试用例
    let test_cases: [i32; 6] = [-42, 0, 100, -999999, i32::MAX, i32::MIN];

    println!("整数测试:");
    println!("----------------------------------------");
    for &num in &test_cases {
        let result = absolute_value(num);
        let safe_result = absolute_value_safe(num);
        match safe_result {
            Some(val) => println!("输入: {:12} | 绝对值: {:12}", num, val),
            None => println!("输入: {:12} | 溢出: i32::MIN无法取绝对值", num),
        }
    }

    // 浮点数测试
    let float_cases: [f64; 4] = [-3.14, 2.718, -0.0, 1e10];
    println!("\n浮点数测试:");
    println!("----------------------------------------");
    for &num in &float_cases {
        let result = absolute_value_f64(num);
        println!("输入: {:12.3} | 绝对值: {:12.3}", num, result);
    }

    // 数学性质
    println!("\n========================================");
    println!("数学性质:");
    println!("========================================");
    println!("• 非负性: |x| ≥ 0");
    println!("• 正定性: |x| = 0 当且仅当 x = 0");
    println!("• 对称性: |-x| = |x|");
    println!("• 三角不等式: |x + y| ≤ |x| + |y|");
    println!("• 乘法性质: |x × y| = |x| × |y|");

    // 应用场景
    println!("\n========================================");
    println!("应用场景:");
    println!("========================================");
    println!("• 距离计算: 曼哈顿距离、欧几里得距离");
    println!("• 误差分析: 绝对误差、相对误差");
    println!("• 数值比较: 比较浮点数精度");
    println!("• 向量运算: 向量的模（长度）");

    // Rust特性
    println!("\n========================================");
    println!("Rust安全特性:");
    println!("========================================");
    println!("• 溢出检查: i32::MIN.abs()会panic在debug模式");
    println!("• 安全版本: checked_abs()返回Option");
    println!("• wrapping版本: wrapping_abs()允许回绕");
    println!("• 类型安全: 编译时保证类型正确性");

    // 代码示例
    println!("\n========================================");
    println!("Rust代码示例:");
    println!("========================================");
    println!(r#"
// 计算两点间曼哈顿距离
fn manhattan_distance(x1: i32, y1: i32, x2: i32, y2: i32) -> i32 {
    (x2 - x1).abs() + (y2 - y1).abs()
}

// 误差比较
fn roughly_equal(a: f64, b: f64, epsilon: f64) -> bool {
    (a - b).abs() < epsilon
}

// 泛型版本
fn abs_generic<T: num_traits::Signed>(n: T) -> T {
    n.abs()
}
"#);
}

fn main() {
    test_absolute_value();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_abs_positive() {
        assert_eq!(absolute_value(42), 42);
    }

    #[test]
    fn test_abs_negative() {
        assert_eq!(absolute_value(-42), 42);
    }

    #[test]
    fn test_abs_zero() {
        assert_eq!(absolute_value(0), 0);
    }

    #[test]
    fn test_abs_safe_overflow() {
        assert_eq!(absolute_value_safe(i32::MIN), None);
    }
}
