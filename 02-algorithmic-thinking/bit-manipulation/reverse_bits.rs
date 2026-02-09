/**
 * 反转二进制位
 *
 * 问题：反转一个32位整数的二进制表示
 *
 * 核心思想：
 * - 逐位提取和重建
 * - 位操作实现高效反转
 *
 * 时间复杂度: O(32)
 * 空间复杂度: O(1)
 */

/// 逐位反转：从右到左提取，从左到右重建
fn reverse_bits_iterative(mut n: u32) -> u32 {
    let mut result = 0u32;
    for _ in 0..32 {
        // 提取n的最右边一位
        let bit = n & 1;
        // 右移n，处理下一位
        n >>= 1;
        // result左移，为新位腾出空间
        result = (result << 1) | bit;
    }
    result
}

/// 手动位操作：逐位反转
fn reverse_bits_manual(n: u32) -> u32 {
    let mut result = 0u32;
    // 处理32位
    for i in 0..32 {
        // 从n中提取第i位
        if ((n >> i) & 1) == 1 {
            // 在result中设置第(31-i)位
            result |= 1 << (31 - i);
        }
    }
    result
}

/// 按字节反转（4个字节的整数）
fn reverse_bits_byte_by_byte(n: u32) -> u32 {
    let mut result = 0u32;

    // 处理4个字节
    for i in 0..4 {
        // 提取第i个字节
        let byte_val = ((n >> (i * 8)) & 0xFF) as u8;

        // 反转字节内的位
        let mut reversed_byte = 0u8;
        for j in 0..8 {
            if ((byte_val >> j) & 1) == 1 {
                reversed_byte |= 1 << (7 - j);
            }
        }

        // 将反转后的字节放在结果的正确位置
        result |= (reversed_byte as u32) << ((3 - i) * 8);
    }

    result
}

/// 使用查表法反转（针对频繁调用优化）
fn reverse_bits_lookup(n: u32) -> u32 {
    // 预计算0-255的位反转
    let lookup: Vec<u8> = (0u32..256)
        .map(|i| {
            let byte_val = i as u8;
            let mut reversed = 0u8;
            for j in 0..8 {
                if ((byte_val >> j) & 1) == 1 {
                    reversed |= 1 << (7 - j);
                }
            }
            reversed
        })
        .collect();

    let mut result = 0u32;
    for i in 0..4 {
        let byte_val = ((n >> (i * 8)) & 0xFF) as usize;
        let reversed_byte = lookup[byte_val];
        result |= (reversed_byte as u32) << ((3 - i) * 8);
    }

    result
}

/// 打印32位二进制表示
fn print_binary_32(n: u32) -> String {
    format!("0b{:032b}", n)
}

fn main() {
    println!("=== 反转二进制位 ===\n");

    // 测试用例1：基本用例
    println!("1. 基本用例:");
    let test_cases = vec![
        1u32,           // 最右位为1
        2u32,           // 倒数第二位为1
        3u32,           // 最右两位为1
        43261596u32,    // 复杂用例
    ];

    for num in test_cases {
        let result = reverse_bits_iterative(num);

        println!("  输入:   {} ({})", print_binary_32(num), num);
        println!("  输出:   {} ({})\n", print_binary_32(result), result);
    }

    // 测试用例2：比较不同算法
    println!("2. 不同算法的结果比较:");
    let test_nums = vec![0u32, 1, 2, 7, 15, 255, 43261596, 2147483647];

    for num in test_nums {
        let iter = reverse_bits_iterative(num);
        let manual = reverse_bits_manual(num);
        let byte_by_byte = reverse_bits_byte_by_byte(num);
        let lookup = reverse_bits_lookup(num);

        let all_match = iter == manual && manual == byte_by_byte && byte_by_byte == lookup;
        println!("  n={}: 所有算法一致 = {}", num, if all_match { "是" } else { "否" });
    }
    println!();

    // 测试用例3：特殊值
    println!("3. 特殊值:");
    let special = vec![
        (0x00000000u32, "全0"),
        (0xFFFFFFFFu32, "全1"),
        (0x80000000u32, "仅最左位为1"),
        (0x00000001u32, "仅最右位为1"),
        (0x12345678u32, "任意值"),
    ];

    for (num, desc) in special {
        let result = reverse_bits_iterative(num);
        println!("  {:<15}: 0x{:08X} -> 0x{:08X}",
                 desc, num, result);
    }
    println!();

    // 测试用例4：验证对称性（反转两次应该恢复）
    println!("4. 验证反转的对称性（反转两次应该恢复）:");
    let symmetry_nums = vec![1u32, 7, 255, 43261596];

    for num in symmetry_nums {
        let once = reverse_bits_iterative(num);
        let twice = reverse_bits_iterative(once);
        println!("  {}: 反转两次后恢复 = {}", num, if num == twice { "是" } else { "否" });
    }
}
