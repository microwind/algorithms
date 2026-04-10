/*
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 数学基础 - 加法运算 (Addition)
 * 实现基本的加法运算和溢出检查
 * 时间复杂度: O(1)
 */

/**
 * 基本加法运算
 *
 * 算法原理：
 * - 返回两数之和 a + b
 *
 * 参数:
 *     a: 被加数
 *     b: 加数
 * 返回:
 *     两数之和
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */
pub fn add(a: i32, b: i32) -> i32 {
    a + b
}

/**
 * 安全加法（溢出检查）
 *
 * 使用Rust内置的checked_add进行溢出检测
 * 当发生溢出时返回None
 */
pub fn safe_add(a: i32, b: i32) -> Option<i32> {
    a.checked_add(b)
}

/**
 * 批量加法
 * 计算数组中所有元素的和
 */
pub fn sum(numbers: &[i32]) -> i32 {
    numbers.iter().sum()
}

/**
 * 测试函数
 */
fn test_add() {
    println!("========================================");
    println!("    加法运算演示 (Addition)");
    println!("========================================\n");

    // 基本加法测试
    println!("基本加法测试:");
    println!("----------------------------------------");
    let test_cases = [(5, 3), (100, 200), (-10, 15), (0, 0), (i32::MAX, 1)];
    for (a, b) in test_cases {
        let result = add(a, b);
        let safe_result = safe_add(a, b);
        match safe_result {
            Some(val) => println!("{} + {} = {} (安全)", a, b, val),
            None => println!("{} + {} = 溢出! (使用safe_add检测到)", a, b),
        }
    }

    // 数组求和
    println!("\n数组求和:");
    println!("----------------------------------------");
    let numbers = vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    println!("数组: {:?}", numbers);
    println!("总和: {}", sum(&numbers));

    // 数学性质
    println!("\n========================================");
    println!("加法数学性质:");
    println!("========================================");
    println!("• 交换律: a + b = b + a");
    println!("• 结合律: (a + b) + c = a + (b + c)");
    println!("• 零元素: a + 0 = a");
    println!("• 负元素: a + (-a) = 0");
}

fn main() {
    test_add();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_add() {
        assert_eq!(add(5, 3), 8);
        assert_eq!(add(100, 200), 300);
        assert_eq!(add(-10, 15), 5);
    }

    #[test]
    fn test_safe_add() {
        assert_eq!(safe_add(5, 3), Some(8));
        assert_eq!(safe_add(i32::MAX, 1), None); // 溢出
    }

    #[test]
    fn test_sum() {
        assert_eq!(sum(&[1, 2, 3, 4, 5]), 15);
        assert_eq!(sum(&[]), 0);
    }
}
