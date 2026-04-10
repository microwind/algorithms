/*
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 数学基础 - 斐波那契数列 (Fibonacci Sequence)
 * 计算斐波那契数列的第n项
 * 时间复杂度: O(n)
 */

/**
 * 迭代法计算斐波那契数
 *
 * 算法原理：
 * - F(0) = 0, F(1) = 1
 * - F(n) = F(n-1) + F(n-2)
 * - 使用迭代避免递归栈溢出
 *
 * 参数:
 *     n: 第n项（非负整数）
 * 返回:
 *     第n个斐波那契数
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
pub fn fibonacci(n: u32) -> u64 {
    if n <= 1 {
        return n as u64;
    }
    let mut a: u64 = 0;
    let mut b: u64 = 1;
    for _ in 2..=n {
        let temp = a + b;
        a = b;
        b = temp;
    }
    b
}

/**
 * 递归法计算斐波那契数
 *
 * 时间复杂度: O(2^n) - 指数级
 * 空间复杂度: O(n) - 递归栈深度
 */
pub fn fibonacci_recursive(n: u32) -> u64 {
    if n <= 1 {
        return n as u64;
    }
    fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)
}

/**
 * 生成斐波那契数列
 * 返回前n项的数组
 */
pub fn fibonacci_sequence(n: usize) -> Vec<u64> {
    let mut sequence = Vec::with_capacity(n);
    if n == 0 {
        return sequence;
    }
    sequence.push(0);
    if n == 1 {
        return sequence;
    }
    sequence.push(1);
    for i in 2..n {
        let next = sequence[i - 1] + sequence[i - 2];
        sequence.push(next);
    }
    sequence
}

/**
 * 测试函数
 */
fn test_fibonacci() {
    println!("========================================");
    println!("    斐波那契数列演示 (Fibonacci)");
    println!("========================================\n");

    // 基本测试
    println!("前20项斐波那契数:");
    println!("----------------------------------------");
    for i in 0..20 {
        let result = fibonacci(i);
        print!("F({})={} ", i, result);
        if (i + 1) % 5 == 0 {
            println!();
        }
    }

    // 数列生成
    println!("\n\n生成数列（前15项）:");
    println!("----------------------------------------");
    let sequence = fibonacci_sequence(15);
    println!("{:?}", sequence);

    // 数学性质
    println!("\n========================================");
    println!("斐波那契数列性质:");
    println!("========================================");
    println!("• 黄金比例: F(n+1)/F(n) → φ ≈ 1.618");
    println!("• 求和性质: F(0)+F(1)+...+F(n) = F(n+2) - 1");
    println!("• 平方和: F(0)²+F(1)²+...+F(n)² = F(n)×F(n+1)");
    println!("• 卡西尼恒等式: F(n+1)×F(n-1) - F(n)² = (-1)ⁿ");

    // 黄金比例逼近
    println!("\n黄金比例逼近:");
    println!("----------------------------------------");
    for n in [10, 20, 30, 40] {
        let ratio = fibonacci(n + 1) as f64 / fibonacci(n) as f64;
        println!("F({})/F({}) = {:.10}", n + 1, n, ratio);
    }
}

fn main() {
    test_fibonacci();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_fibonacci() {
        assert_eq!(fibonacci(0), 0);
        assert_eq!(fibonacci(1), 1);
        assert_eq!(fibonacci(10), 55);
        assert_eq!(fibonacci(20), 6765);
    }

    #[test]
    fn test_fibonacci_sequence() {
        let seq = fibonacci_sequence(10);
        assert_eq!(seq, vec![0, 1, 1, 2, 3, 5, 8, 13, 21, 34]);
    }
}
