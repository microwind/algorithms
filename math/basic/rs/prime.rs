/*
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 数学基础 - 素数判断 (Prime Number)
 * 判断一个数是否为素数
 * 时间复杂度: O(√n)
 */

/**
 * 判断是否为素数
 *
 * 算法原理：
 * - 素数定义：大于1的自然数，除了1和它本身外没有其他因数
 * - 优化：只需检查到√n，因为如果n有大于√n的因数，
 *   则必有对应的小于√n的因数
 * - 跳过偶数（2除外），只检查奇数
 *
 * 参数:
 *     n: 要判断的正整数
 * 返回:
 *     true表示是素数，false表示不是
 *
 * 时间复杂度: O(√n)
 * 空间复杂度: O(1)
 */
pub fn is_prime(n: u32) -> bool {
    if n < 2 {
        return false;
    }
    if n == 2 {
        return true;
    }
    if n % 2 == 0 {
        return false;
    }
    let mut i = 3;
    while i * i <= n {
        if n % i == 0 {
            return false;
        }
        i += 2;
    }
    true
}

/**
 * 生成n以内的所有素数
 * 使用埃拉托斯特尼筛法
 */
pub fn sieve_of_eratosthenes(n: usize) -> Vec<usize> {
    if n < 2 {
        return vec![];
    }
    let mut is_prime = vec![true; n + 1];
    is_prime[0] = false;
    is_prime[1] = false;
    
    for i in 2..=((n as f64).sqrt() as usize) {
        if is_prime[i] {
            let mut j = i * i;
            while j <= n {
                is_prime[j] = false;
                j += i;
            }
        }
    }
    
    is_prime.iter()
        .enumerate()
        .filter_map(|(i, &p)| if p { Some(i) } else { None })
        .collect()
}

/**
 * 获取n的质因数分解
 */
pub fn prime_factors(n: u32) -> Vec<(u32, u32)> {
    let mut n = n;
    let mut factors = Vec::new();
    let mut count = 0;
    
    // 处理因数2
    while n % 2 == 0 {
        count += 1;
        n /= 2;
    }
    if count > 0 {
        factors.push((2, count));
    }
    
    // 处理奇数因数
    let mut i = 3;
    while i * i <= n {
        count = 0;
        while n % i == 0 {
            count += 1;
            n /= i;
        }
        if count > 0 {
            factors.push((i, count));
        }
        i += 2;
    }
    
    // 如果n还是素数
    if n > 1 {
        factors.push((n, 1));
    }
    
    factors
}

/**
 * 测试函数
 */
fn test_prime() {
    println!("========================================");
    println!("    素数判断演示 (Prime Number)");
    println!("========================================\n");

    // 基本素数测试
    println!("100以内的素数:");
    println!("----------------------------------------");
    let primes: Vec<u32> = (2..100).filter(|&n| is_prime(n)).collect();
    for (i, p) in primes.iter().enumerate() {
        print!("{:3}", p);
        if (i + 1) % 10 == 0 {
            println!();
        }
    }
    println!("\n共 {} 个素数", primes.len());

    // 筛法生成素数
    println!("\n筛法生成200以内素数:");
    println!("----------------------------------------");
    let sieve_primes = sieve_of_eratosthenes(200);
    println!("素数个数: {}", sieve_primes.len());
    println!("前20个: {:?}", &sieve_primes[..20]);

    // 质因数分解
    println!("\n质因数分解:");
    println!("----------------------------------------");
    let test_numbers = [12, 100, 360, 1001, 2024];
    for &n in &test_numbers {
        let factors = prime_factors(n);
        let factor_str: Vec<String> = factors.iter()
            .map(|(p, e)| if *e == 1 { format!("{}", p) } else { format!("{}^{}", p, e) })
            .collect();
        println!("{} = {}", n, factor_str.join(" × "));
    }

    // 数学性质
    println!("\n========================================");
    println!("素数性质:");
    println!("========================================");
    println!("• 唯一分解定理: 每个大于1的整数可唯一分解为素数乘积");
    println!("• 素数定理: π(n) ≈ n/ln(n)");
    println!("• 孪生素数: 差为2的素数对，如(3,5), (11,13)");
    println!("• 哥德巴赫猜想: 每个大于2的偶数可表为两素数之和");
}

fn main() {
    test_prime();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_prime() {
        assert!(!is_prime(0));
        assert!(!is_prime(1));
        assert!(is_prime(2));
        assert!(is_prime(17));
        assert!(!is_prime(4));
        assert!(!is_prime(100));
    }

    #[test]
    fn test_prime_factors() {
        assert_eq!(prime_factors(12), vec![(2, 2), (3, 1)]);
        assert_eq!(prime_factors(100), vec![(2, 2), (5, 2)]);
    }
}
