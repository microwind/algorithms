/*
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 数学基础 - 最大值最小值 (Max & Min)
 * 计算两个数或数组的最大值和最小值
 * 时间复杂度: O(1) 或 O(n)
 */

/**
 * 计算两个整数的最大值
 *
 * 参数:
 *     a: 第一个整数
 *     b: 第二个整数
 * 返回:
 *     较大的那个数
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */
pub fn max(a: i32, b: i32) -> i32 {
    if a > b { a } else { b }
}

/**
 * 计算两个整数的最小值
 */
pub fn min(a: i32, b: i32) -> i32 {
    if a < b { a } else { b }
}

/**
 * 计算数组中的最大值
 */
pub fn max_of_slice(numbers: &[i32]) -> i32 {
    *numbers.iter().max().unwrap_or(&0)
}

/**
 * 计算数组中的最小值
 */
pub fn min_of_slice(numbers: &[i32]) -> i32 {
    *numbers.iter().min().unwrap_or(&0)
}

/**
 * 计算最大值和最小值（同时返回）
 */
pub fn min_max(numbers: &[i32]) -> (i32, i32) {
    if numbers.is_empty() {
        return (0, 0);
    }
    let mut min_val = numbers[0];
    let mut max_val = numbers[0];
    for &n in numbers.iter().skip(1) {
        if n < min_val {
            min_val = n;
        }
        if n > max_val {
            max_val = n;
        }
    }
    (min_val, max_val)
}

/**
 * 测试函数
 */
fn test_max_min() {
    println!("========================================");
    println!("    最大值最小值演示 (Max & Min)");
    println!("========================================\n");

    // 两数比较
    println!("两数比较:");
    println!("----------------------------------------");
    let pairs = [(5, 3), (-10, -5), (100, 100), (42, 24)];
    for (a, b) in pairs {
        println!("max({}, {}) = {}, min({}, {}) = {}", a, b, max(a, b), a, b, min(a, b));
    }

    // 数组极值
    println!("\n数组极值:");
    println!("----------------------------------------");
    let numbers = vec![23, 56, 12, 89, 34, 7, 91, 18];
    println!("数组: {:?}", numbers);
    println!("最大值: {}", max_of_slice(&numbers));
    println!("最小值: {}", min_of_slice(&numbers));
    let (min_val, max_val) = min_max(&numbers);
    println!("同时计算: min={}, max={}", min_val, max_val);

    // 应用场景
    println!("\n========================================");
    println!("应用场景:");
    println!("========================================");
    println!("• 数据统计: 找出数据集中的极值");
    println!("• 图像处理: 归一化像素值");
    println!("• 算法设计: 分治法中的子问题合并");
    println!("• 游戏开发: 碰撞检测边界框");
}

fn main() {
    test_max_min();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_max() {
        assert_eq!(max(5, 3), 5);
        assert_eq!(max(-10, -5), -5);
        assert_eq!(max(100, 100), 100);
    }

    #[test]
    fn test_min() {
        assert_eq!(min(5, 3), 3);
        assert_eq!(min(-10, -5), -10);
    }

    #[test]
    fn test_min_max() {
        let numbers = vec![3, 1, 4, 1, 5, 9, 2, 6];
        let (min_val, max_val) = min_max(&numbers);
        assert_eq!(min_val, 1);
        assert_eq!(max_val, 9);
    }
}
