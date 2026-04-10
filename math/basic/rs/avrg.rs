/*
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 数学基础 - 平均值计算 (Average)
 * 计算算术平均值和加权平均值
 * 时间复杂度: O(n)
 */

/**
 * 计算算术平均值
 *
 * 算法原理：
 * - 平均值 = 总和 / 个数
 * - 空数组返回0.0
 *
 * 参数:
 *     numbers: 数值数组
 * 返回:
 *     算术平均值
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
pub fn average(numbers: &[f64]) -> f64 {
    if numbers.is_empty() {
        return 0.0;
    }
    let sum: f64 = numbers.iter().sum();
    sum / numbers.len() as f64
}

/**
 * 安全平均值（防止溢出）
 * 对大整数使用分段计算
 */
pub fn average_safe(a: i64, b: i64) -> f64 {
    a as f64 / 2.0 + b as f64 / 2.0
}

/**
 * 加权平均值
 */
pub fn weighted_average(values: &[f64], weights: &[f64]) -> f64 {
    if values.len() != weights.len() || values.is_empty() {
        return 0.0;
    }
    let mut sum = 0.0;
    let mut weight_sum = 0.0;
    for i in 0..values.len() {
        sum += values[i] * weights[i];
        weight_sum += weights[i];
    }
    if weight_sum == 0.0 {
        return 0.0;
    }
    sum / weight_sum
}

/**
 * 几何平均值
 * 用于计算增长率等
 */
pub fn geometric_mean(numbers: &[f64]) -> f64 {
    if numbers.is_empty() {
        return 0.0;
    }
    let mut product = 1.0;
    for &n in numbers {
        if n <= 0.0 {
            return f64::NAN;
        }
        product *= n;
    }
    product.powf(1.0 / numbers.len() as f64)
}

/**
 * 测试函数
 */
fn test_average() {
    println!("========================================");
    println!("    平均值计算演示 (Average)");
    println!("========================================\n");

    // 算术平均
    println!("算术平均值:");
    println!("----------------------------------------");
    let scores = vec![85.0, 92.0, 78.0, 95.0, 88.0];
    println!("分数: {:?}", scores);
    println!("平均分: {:.2}", average(&scores));

    // 加权平均
    println!("\n加权平均值:");
    println!("----------------------------------------");
    let values = vec![85.0, 90.0, 95.0];
    let weights = vec![0.3, 0.5, 0.2]; // 权重和为1
    println!("数值: {:?}", values);
    println!("权重: {:?}", weights);
    println!("加权平均: {:.2}", weighted_average(&values, &weights));

    // 几何平均
    println!("\n几何平均值:");
    println!("----------------------------------------");
    let growth_rates = vec![1.1, 1.2, 1.15, 1.05]; // 增长率
    println!("增长率: {:?}", growth_rates);
    println!("几何平均增长率: {:.4}", geometric_mean(&growth_rates));

    // 数学性质
    println!("\n========================================");
    println!("平均值类型:");
    println!("========================================");
    println!("• 算术平均: (a₁ + a₂ + ... + aₙ) / n");
    println!("• 几何平均: ⁿ√(a₁ × a₂ × ... × aₙ)");
    println!("• 调和平均: n / (1/a₁ + 1/a₂ + ... + 1/aₙ)");
    println!("• 加权平均: Σ(wᵢ×aᵢ) / Σwᵢ");
    println!("• 关系: 算术平均 ≥ 几何平均 ≥ 调和平均");
}

fn main() {
    test_average();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_average() {
        let numbers = vec![10.0, 20.0, 30.0, 40.0, 50.0];
        assert_eq!(average(&numbers), 30.0);
    }

    #[test]
    fn test_weighted_average() {
        let values = vec![80.0, 90.0];
        let weights = vec![1.0, 1.0];
        assert_eq!(weighted_average(&values, &weights), 85.0);
    }
}
