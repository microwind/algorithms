/*
*
 * 最长递增子序列 (LIS) - 动态规划应用
 *
 * 问题描述：
 * 给定一个无序整数数组，找出其中最长递增子序列的长度
 *
 * 动态规划方程：
 * dp[i] = 1 + max(dp[j]) for all j < i and arr[j] < arr[i]
 *
 * 时间复杂度: O(n²) 基础DP
 * 空间复杂度: O(n)
*/

// / 最长递增子序列 - 基础DP方案
pub fn longest_increasing_subsequence(arr: &[i32]) -> usize {
    if arr.is_empty() {
        return 0;
    }

    let n = arr.len();

    // dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
    let mut dp = vec![1; n];

    // 构建 DP 表
    for i in 1..n {
        for j in 0..i {
            // 如果 arr[j] < arr[i]，可以扩展以 arr[j] 结尾的 LIS
            if arr[j] < arr[i] {
                dp[i] = std::cmp::max(dp[i], dp[j] + 1);
            }
        }
    }

    // 找到最大值
    *dp.iter().max().unwrap_or(&0)
}

// / 最长递增子序列 - 优化方案 (O(n log n))
pub fn longest_increasing_subsequence_optimized(arr: &[i32]) -> usize {
    if arr.is_empty() {
        return 0;
    }

    // tails[i] 是长度为 i+1 的递增子序列的最小末尾元素
    let mut tails = Vec::new();

    for &num in arr {
        // 使用二分查找找到应该替换的位置
        match tails.binary_search(&num) {
            Ok(pos) => {
                // 已存在该元素，替换以保持最小性
                tails[pos] = num;
            }
            Err(pos) => {
                if pos == tails.len() {
                    // 找到了更长的递增子序列
                    tails.push(num);
                } else {
                    // 替换较大的元素，保持 tails 的最小性
                    tails[pos] = num;
                }
            }
        }
    }

    tails.len()
}

// / 最长递增子序列 - 返回子序列本身
pub fn longest_increasing_subsequence_with_sequence(arr: &[i32]) -> (usize, Vec<i32>) {
    if arr.is_empty() {
        return (0, Vec::new());
    }

    let n = arr.len();

    // dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
    let mut dp = vec![1; n];
    // parent[i] 表示以 arr[i] 结尾的 LIS 中，前一个元素的索引
    let mut parent = vec![-1; n];

    // 构建 DP 表
    for i in 1..n {
        for j in 0..i {
            if arr[j] < arr[i] && dp[j] + 1 > dp[i] {
                dp[i] = dp[j] + 1;
                parent[i] = j as i32;
            }
        }
    }

    // 找到最长序列的结尾位置
    let (max_index, &max_length) = dp
        .iter()
        .enumerate()
        .max_by_key(|(_, &val)| val)
        .unwrap_or((0, &0));

    // 反向追踪构建最长子序列
    let mut lis = Vec::new();
    let mut idx = max_index as i32;
    while idx != -1 {
        lis.push(arr[idx as usize]);
        idx = parent[idx as usize];
    }
    lis.reverse();

    (max_length, lis)
}

fn main() {
    println!("=== 最长递增子序列 ===\n");

    // 测试用例1：基本数组
    println!("1. 基本数组");
    let arr1 = vec![10, 9, 2, 5, 3, 7, 101, 18];
    println!("数组: {:?}", arr1);
    println!("LIS 长度（DP）: {}", longest_increasing_subsequence(&arr1));
    println!("LIS 长度（优化）: {}\n", longest_increasing_subsequence_optimized(&arr1));

    // 测试用例2：已排序数组
    println!("2. 已排序数组");
    let arr2 = vec![1, 3, 6, 7, 9, 4, 10, 5, 8];
    println!("数组: {:?}", arr2);
    let (length, lis) = longest_increasing_subsequence_with_sequence(&arr2);
    println!("LIS 长度: {}", length);
    println!("一个 LIS: {:?}\n", lis);

    // 测试用例3：包含重复元素
    println!("3. 包含重复元素");
    let arr3 = vec![1, 3, 3, 4, 5];
    println!("数组: {:?}", arr3);
    println!("LIS 长度: {}\n", longest_increasing_subsequence(&arr3));

    // 测试用例4：单调递减
    println!("4. 单调递减");
    let arr4 = vec![5, 4, 3, 2, 1];
    println!("数组: {:?}", arr4);
    println!("LIS 长度: {}", longest_increasing_subsequence(&arr4));
}

/**
jarry@Mac lis % rustc lis.rs
jarry@Mac lis % ./lis       
=== 最长递增子序列 ===

1. 基本数组
数组: [10, 9, 2, 5, 3, 7, 101, 18]
LIS 长度（DP）: 4
LIS 长度（优化）: 4

2. 已排序数组
数组: [1, 3, 6, 7, 9, 4, 10, 5, 8]
LIS 长度: 6
一个 LIS: [1, 3, 6, 7, 9, 10]

3. 包含重复元素
数组: [1, 3, 3, 4, 5]
LIS 长度: 4

4. 单调递减
数组: [5, 4, 3, 2, 1]
LIS 长度: 1
*/