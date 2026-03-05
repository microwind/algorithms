/*
*
 * 最大XOR对 - 找数组中最大的XOR值
 *
 * 问题：给定一个数组，找到任意两个元素的最大XOR值
 *
 * 核心思想：
 * - 暴力法：比较所有对
 * - 字典树(Trie)：高效地查找最大XOR
 *
 * 时间复杂度:
 * - 暴力法: O(n^2)
 * - Trie方法: O(n * k) 其中k是整数的位数
 *
 * 空间复杂度: O(n * k) for Trie
*/

use std::collections::HashSet;

// / 暴力法：比较所有对
fn max_xor_pair_brute_force(nums: &[i32]) -> i32 {
    let mut max_xor = 0;
    for i in 0..nums.len() {
        for j in i + 1..nums.len() {
            let xor_val = nums[i] ^ nums[j];
            max_xor = max_xor.max(xor_val);
        }
    }
    max_xor
}

// / Trie树节点
#[derive(Default)]
struct TrieNode {
    children: [Option<Box<TrieNode>>; 2],
}

// / 将数字的二进制表示插入Trie树
fn insert_trie(root: &mut TrieNode, num: i32) {
    let mut node = root;
    // 从最高位到最低位遍历
    for i in (0..32).rev() {
        let bit = ((num >> i) & 1) as usize;
        node = &mut node.children[bit].get_or_insert_with(Default::default);
    }
}

// / 找与给定数字最大XOR的数
// /
// / 贪心策略：对于每一位，尽可能走不同的路径以最大化XOR
fn find_max_xor(root: &TrieNode, num: i32) -> i32 {
    let mut node = root;
    let mut max_xor = 0;
    // 从最高位到最低位遍历
    for i in (0..32).rev() {
        let bit = ((num >> i) & 1) as usize;
        // 优先走相反的路径（这样XOR结果该位为1）
        let toggle_bit = 1 - bit;

        if let Some(ref child) = node.children[toggle_bit] {
            max_xor |= 1 << i;
            node = child;
        } else if let Some(ref child) = node.children[bit] {
            node = child;
        } else {
            // 不应该出现这种情况
            break;
        }
    }
    max_xor
}

// / 使用Trie树找最大XOR对
fn max_xor_pair_trie(nums: &[i32]) -> i32 {
    if nums.len() < 2 {
        return 0;
    }

    let mut root = TrieNode::default();

    // 构建Trie树
    for &num in nums {
        insert_trie(&mut root, num);
    }

    let mut max_xor = 0;
    // 对每个数字，找与它最大XOR的数
    for &num in nums {
        let xor_val = find_max_xor(&root, num);
        max_xor = max_xor.max(xor_val);
    }

    max_xor
}

// / 贪心法（不用Trie）：逐位构建答案
fn max_xor_pair_greedy(nums: &[i32]) -> i32 {
    if nums.len() < 2 {
        return 0;
    }

    let mut max_xor = 0;
    let mut prefix_mask = 0;

    // 从最高位到最低位
    for i in (0..32).rev() {
        prefix_mask |= 1 << i;

        // 收集所有数的前缀
        let prefixes: HashSet<i32> = nums.iter()
            .map(|&num| num & prefix_mask)
            .collect();

        // 尝试在当前位设为1
        let temp = max_xor | (1 << i);

        // 检查是否存在两个数的前缀异或为temp
        for &prefix in &prefixes {
            if prefixes.contains(&(temp ^ prefix)) {
                max_xor = temp;
                break;
            }
        }
    }

    max_xor
}

// / 打印数组
fn print_array(arr: &[i32]) -> String {
    format!("[{}]", arr.iter()
        .map(|n| n.to_string())
        .collect::<Vec<_>>()
        .join(", "))
}

fn main() {
    println!("=== 最大XOR对 ===\n");

    // 测试用例1：基本用例
    println!("1. 基本用例:");
    let test_arrays = vec![
        vec![1, 2, 3, 4, 5],
        vec![8, 10, 2],
        vec![14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70],
    ];

    for nums in test_arrays {
        println!("  数组: {}", print_array(&nums));

        let brute = max_xor_pair_brute_force(&nums);
        let trie = max_xor_pair_trie(&nums);
        let greedy = max_xor_pair_greedy(&nums);

        println!("  最大XOR (暴力): {}", brute);
        println!("  最大XOR (Trie): {}", trie);
        println!("  最大XOR (贪心): {}", greedy);
        println!("  所有方法一致: {}\n",
                 if brute == trie && trie == greedy { "是" } else { "否" });
    }

    // 测试用例2：XOR对的详细信息
    println!("2. XOR对的详细信息:");
    let nums2 = vec![1, 2, 3, 4, 5];
    println!("  数组: {}", print_array(&nums2));

    let mut max_xor = 0;
    let mut best_i = 0;
    let mut best_j = 1;
    for i in 0..nums2.len() {
        for j in i + 1..nums2.len() {
            let xor_val = nums2[i] ^ nums2[j];
            if xor_val > max_xor {
                max_xor = xor_val;
                best_i = i;
                best_j = j;
            }
            if xor_val >= 4 {  // 只显示较大的XOR值
                println!("    {} ^ {} = {}", nums2[i], nums2[j], xor_val);
            }
        }
    }
    println!("  最大XOR对: {} ^ {} = {}\n",
             nums2[best_i], nums2[best_j], max_xor);

    // 测试用例3：边界情况
    println!("3. 边界情况:");
    let boundary_tests = vec![
        vec![5],
        vec![5, 3],
        vec![1],
        vec![7, 7],
    ];

    for nums in boundary_tests {
        println!("  数组: {} -> 最大XOR: {}",
                 print_array(&nums), max_xor_pair_trie(&nums));
    }
    println!();

    // 测试用例4：较大数组
    println!("4. 较大数组测试:");
    let large_size = 100;
    let large_nums: Vec<i32> = (1..=large_size).collect();

    let start = std::time::Instant::now();
    let result_greedy = max_xor_pair_greedy(&large_nums);
    let greedy_time = start.elapsed();

    let start = std::time::Instant::now();
    let result_trie = max_xor_pair_trie(&large_nums);
    let trie_time = start.elapsed();

    println!("  数组大小: {}", large_size);
    println!("  贪心法结果: {}, 耗时: {:?}", result_greedy, greedy_time);
    println!("  Trie法结果: {}, 耗时: {:?}", result_trie, trie_time);
}
