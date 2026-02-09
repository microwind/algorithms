/**
 * 2的幂 - 位运算和数字性质
 *
 * 问题：
 * 1. 检查一个数是否是2的幂
 * 2. 计算2的幂相关的位操作
 *
 * 核心思想：
 * - 2的幂在二进制表示中只有一个1（1, 2, 4, 8, 16, ...）
 * - n & (n-1) == 0 可以判断是否为2的幂
 * - 利用位运算的性质进行快速计算
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */

/// 判断一个数是否是2的幂
///
/// 原理：
/// - 2的幂的二进制表示只有一个1，其余为0
/// - 例如：8 = 1000 (二进制)
/// - n-1 = 0111 (二进制)
/// - n & (n-1) = 0
fn is_power_of_two(n: i32) -> bool {
    n > 0 && (n & (n - 1)) == 0
}

/// 使用位计数判断（备选方案）
fn is_power_of_two_builtin(n: i32) -> bool {
    if n <= 0 {
        return false;
    }
    n.count_ones() == 1
}

/// 计算2的幂中的位置（幂的指数）
fn power_of_two_exponent(n: i32) -> i32 {
    if !is_power_of_two(n) {
        return -1;
    }

    let mut exp = 0;
    let mut m = n;
    while (m & 1) == 0 {
        m >>= 1;
        exp += 1;
    }
    exp
}

/// 找到大于等于n的最小2的幂
fn next_power_of_two(n: i32) -> i32 {
    if n <= 1 {
        return 1;
    }

    // 如果已经是2的幂，直接返回
    if is_power_of_two(n) {
        return n;
    }

    // 找到下一个2的幂
    let mut m = n - 1;
    m |= m >> 1;
    m |= m >> 2;
    m |= m >> 4;
    m |= m >> 8;
    m |= m >> 16;
    m + 1
}

/// 获取一个2的幂是2的几次方
fn get_exponent(n: i32) -> i32 {
    if !is_power_of_two(n) {
        return -1;
    }

    let mut exp = 0;
    let mut m = n;
    while (m & 1) == 0 {
        exp += 1;
        m >>= 1;
    }
    exp
}

/// 打印二进制表示
fn print_binary(n: i32) -> String {
    format!("0b{:016b}", n)
}

fn main() {
    println!("=== 2的幂 ===\n");

    // 测试用例1：判断是否为2的幂
    println!("1. 判断是否为2的幂:");
    let test_nums = vec![1, 2, 3, 4, 5, 8, 16, 17, 32, 100];

    for num in test_nums {
        let result = if is_power_of_two(num) {
            "是2的幂"
        } else {
            "不是2的幂"
        };
        println!("  {:3}: {}", num, result);
    }
    println!();

    // 测试用例2：获取幂的指数
    println!("2. 获取2的幂中的指数:");
    let power_nums = vec![1, 2, 4, 8, 16, 32, 64, 128, 256];

    for num in power_nums {
        let exp = get_exponent(num);
        println!("  2^{} = {}", exp, num);
    }
    println!();

    // 测试用例3：找下一个2的幂
    println!("3. 找大于等于n的最小2的幂:");
    let test_nums2 = vec![1, 3, 5, 7, 8, 9, 15, 16, 17, 100];

    for num in test_nums2 {
        let next = next_power_of_two(num);
        println!("  n={:3} -> {}", num, next);
    }
    println!();

    // 测试用例4：边界情况
    println!("4. 边界情况:");
    println!("  0 是2的幂: {}", if is_power_of_two(0) { "是" } else { "否" });
    println!("  1 是2的幂: {}", if is_power_of_two(1) { "是" } else { "否" });
    println!("  -8 是2的幂: {}", if is_power_of_two(-8) { "是" } else { "否" });
    println!();

    // 测试用例5：二进制表示
    println!("5. 2的幂的二进制表示:");
    for i in 0..=4 {
        let num = 1 << i;
        println!("  2^{} = {:2} = {}", i, num, print_binary(num));
    }
}
