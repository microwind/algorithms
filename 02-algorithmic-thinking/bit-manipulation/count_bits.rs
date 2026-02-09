/**
 * 计数1位 - Hamming权重
 *
 * 问题：计算整数二进制表示中1的个数
 *
 * 核心思想：
 * - 逐位检查：与1进行AND操作
 * - Brian Kernighan算法：n & (n-1) 移除最右边的1
 * - 预计算查表法（对于频繁调用优化）
 *
 * 时间复杂度: O(log n) 或 O(1) 取决于实现方式
 * 空间复杂度: O(1)
 */

/// 逐位检查：循环检查每一位
fn count_ones_loop(mut n: u32) -> i32 {
    let mut count = 0;
    while n > 0 {
        count += (n & 1) as i32;
        n >>= 1;
    }
    count
}

/// Brian Kernighan算法：移除最右边的1
///
/// 原理：
/// - n & (n-1) 移除n的最右边的1
/// - 重复这个操作直到n为0
/// - 操作次数就是1的个数
/// - 只需O(k)的时间，k是1的个数
fn count_ones_kernighan(mut n: u32) -> i32 {
    let mut count = 0;
    while n > 0 {
        n &= n - 1;  // 移除最右边的1
        count += 1;
    }
    count
}

/// 使用Rust内置函数
fn count_ones_builtin(n: u32) -> i32 {
    n.count_ones() as i32
}

/// 使用查表法（用于频繁调用的优化）
fn count_ones_table(mut n: u32) -> i32 {
    let lookup = (0u32..256)
        .map(|i| count_ones_loop(i))
        .collect::<Vec<_>>();

    let mut count = 0;
    while n > 0 {
        count += lookup[(n & 0xFF) as usize];
        n >>= 8;
    }
    count
}

/// 打印二进制表示
fn print_binary(n: u32) -> String {
    format!("0b{:08b}", n)
}

fn main() {
    println!("=== 计数1位 (Hamming权重) ===\n");

    // 测试用例1：基本用例
    println!("1. 基本用例:");
    let test_nums = vec![0u32, 1, 3, 5, 7, 15, 31, 63, 127, 255];

    for num in test_nums {
        let count = count_ones_loop(num);
        println!("  {:3} {}: {}个1", num, print_binary(num), count);
    }
    println!();

    // 测试用例2：比较不同算法
    println!("2. 不同算法的结果比较:");
    let test_nums2 = vec![1u32, 7, 15, 127, 255, 1023];

    for num in test_nums2 {
        let loop_res = count_ones_loop(num);
        let kern = count_ones_kernighan(num);
        let table = count_ones_table(num);
        let builtin = count_ones_builtin(num);

        println!("  n={:4}: loop={}, kernighan={}, table={}, builtin={}",
                 num, loop_res, kern, table, builtin);
    }
    println!();

    // 测试用例3：大数值
    println!("3. 大数值:");
    let large_nums = vec![
        0xFFFFu32,      // 2^16 - 1
        0xFFFFFu32,     // 2^20 - 1
        0x3FFFFFFFu32,  // 2^30 - 1
    ];

    for num in large_nums {
        let count = count_ones_kernighan(num);
        println!("  0x{:08X}: {}个1", num, count);
    }
    println!();

    // 测试用例4：稀疏1的情况（Kernighan优势明显）
    println!("4. 稀疏1的情况（Kernighan优势明显）:");
    let sparse_nums = vec![1u32, 2, 4, 8, 16, 32, 64, 128, 256];

    for num in sparse_nums {
        let count = count_ones_kernighan(num);
        println!("  {:3} (2^?): {}个1", num, count);
    }
    println!();

    // 测试用例5：特殊值
    println!("5. 特殊值:");
    println!("  0x00000000: {}个1", count_ones_loop(0x00000000u32));
    println!("  0xFFFFFFFF: {}个1", count_ones_loop(0xFFFFFFFFu32));
    println!("  0x80000000: {}个1", count_ones_loop(0x80000000u32));
    println!("  0x00000001: {}个1", count_ones_loop(0x00000001u32));
}
