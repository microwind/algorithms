/**
 * 单数问题 - 使用XOR技巧找到单个数字
 *
 * 问题：给定一个整数数组，其中除了一个元素出现一次外，
 * 其他元素都出现两次。找到只出现一次的那个元素。
 *
 * 核心思想：
 * - XOR 的性质：a ^ a = 0, a ^ 0 = a
 * - 对所有元素进行XOR操作，两个相同的数会相消，留下单个数字
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */

use std::collections::HashMap;

/// 使用XOR技巧找到单个数字
///
/// 原理：
/// - 0 ^ x = x
/// - x ^ x = 0
/// - XOR满足交换律和结合律
/// - 对所有数字XOR，重复数字相消，留下单个数字
///
/// 时间复杂度: O(n)
/// 空间复杂度: O(1)
fn single_number_xor(nums: &[i32]) -> i32 {
    let mut result = 0;
    for &num in nums {
        result ^= num;
    }
    result
}

/// 使用哈希表统计频数（备选方案）
///
/// 时间复杂度: O(n)
/// 空间复杂度: O(n)
fn single_number_hash(nums: &[i32]) -> i32 {
    let mut count = HashMap::new();
    for &num in nums {
        *count.entry(num).or_insert(0) += 1;
    }

    for (&num, &cnt) in &count {
        if cnt == 1 {
            return num;
        }
    }

    -1
}

/// 排序后相邻比较（备选方案）
///
/// 时间复杂度: O(n log n)
/// 空间复杂度: O(1)
fn single_number_sort(nums: &[i32]) -> i32 {
    let mut sorted = nums.to_vec();
    sorted.sort_unstable();

    for i in (0..sorted.len() - 1).step_by(2) {
        if sorted[i] != sorted[i + 1] {
            return sorted[i];
        }
    }

    sorted[sorted.len() - 1]
}

fn main() {
    println!("=== 单数问题 ===\n");

    // 测试用例1：基本用例
    println!("1. 基本用例:");
    let nums1 = vec![2, 2, 1];
    println!("  数组: {:?}", nums1);
    println!("  单数: {}\n", single_number_xor(&nums1));

    // 测试用例2：较大数组
    println!("2. 较大数组:");
    let nums2 = vec![4, 1, 2, 1, 2];
    println!("  数组: {:?}", nums2);
    println!("  单数: {}\n", single_number_xor(&nums2));

    // 测试用例3：负数
    println!("3. 包含负数:");
    let nums3 = vec![-1, -1, 5, 5, 3];
    println!("  数组: {:?}", nums3);
    println!("  单数: {}\n", single_number_xor(&nums3));

    // 测试用例4：单个元素
    println!("4. 单个元素:");
    let nums4 = vec![42];
    println!("  数组: {:?}", nums4);
    println!("  单数: {}\n", single_number_xor(&nums4));

    // 性能对比
    println!("5. 不同方法的结果比较:");
    let nums5 = vec![7, 7, 8, 8, 9];
    println!("  数组: {:?}", nums5);
    println!("  XOR方法: {}", single_number_xor(&nums5));
    println!("  哈希方法: {}", single_number_hash(&nums5));
    println!("  排序方法: {}", single_number_sort(&nums5));
}
