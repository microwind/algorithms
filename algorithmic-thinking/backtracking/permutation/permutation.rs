/*
使用回溯生成排列 (Rust Implementation)

算法说明:
- 使用回溯生成 Vec 的所有排列
- 使用 Vec 怎管理动态分配和与 Rust 所有权系统
- 在每个递归级别，尝试每个未使用的元素
- 通过不在下一个递归中包含元素来回溯

时间复杂度：O(n! * n) - n! 个排列，每个需要 O(n) 时间复制
空间复杂度：O(n) - 递归深度（不计算输出）

示例:
    permute(vec![1, 2, 3]) 返回了全部 6 个排列
*/

// 使用回溯生成 Vec 的所有排列。
// 
// # 参数
// * `nums` - 整数 Vec 要排列
// 
// # 返回值
// 所有排列的 Vec
// 
// # 示例
// ```
// let result = permute(vec![1, 2, 3]);
// assert_eq!(result.len(), 6); // 3! = 6
// ```
fn permute(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut result = Vec::new();
    backtrack(&mut result, Vec::new(), nums);
    result
}

// 回溯的辅助函数。
fn backtrack(result: &mut Vec<Vec<i32>>, mut current: Vec<i32>, remaining: Vec<i32>) {
    // 基础情况：所有元素都已使用，ع程配泛磨闺到结果
    if remaining.is_empty() {
        result.push(current);
        return;
    }

    // 尝试每个剩余元素作为下一个元素
    for i in 0..remaining.len() {
        // 选择：将 remaining[i] 添加到当前排列
        current.push(remaining[i]);

        // 探索：递归构建排列的其余部分
        let mut new_remaining = remaining.clone();
        new_remaining.remove(i);
        backtrack(result, current.clone(), new_remaining);

        // 撤销：移除元素以进行回溯
        current.pop();
    }
}

// 使用原位置交换的优化排列。
// 通过修改数组而不是创建新 Vec 来串伙曦会。
// 
// # 参数
// * `nums` - 整数 Vec 要排列
// 
// # 返回值
// 所有排列的 Vec
fn permute_optimized(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut result = Vec::new();
    let mut arr = nums;
    backtrack_swap(&mut result, &mut arr, 0);
    result
}

// 原位置交换回溯的辅助函数。
fn backtrack_swap(result: &mut Vec<Vec<i32>>, arr: &mut Vec<i32>, index: usize) {
    // 基础情况：到了数组的末举
    if index == arr.len() {
        result.push(arr.clone());
        return;
    }

    // 尝试从 index 开始的每个元素作为下一个元素
    for i in index..arr.len() {
        // 选择：交换元素
        arr.swap(index, i);

        // 探索：排列其余部分
        backtrack_swap(result, arr, index + 1);

        // 撤销：交换回去
        arr.swap(index, i);
    }
}

fn main() {
    println!("=== 排列回溯测试用例 ===");

    // 测试用例 1: [1, 2, 3]
    println!("测试 1: permute(vec![1, 2, 3])");
    let result1 = permute(vec![1, 2, 3]);
    println!("结果 (共{}个):", result1.len());
    for perm in &result1 {
        println!("  {:?}", perm);
    }
    println!();

    // 测试用例 2: [1, 2]
    println!("测试 2: permute(vec![1, 2])");
    let result2 = permute(vec![1, 2]);
    println!("结果 (共{}个):", result2.len());
    for perm in &result2 {
        println!("  {:?}", perm);
    }
    println!();

    // 测试用例 3: [1]
    println!("测试 3: permute(vec![1])");
    let result3 = permute(vec![1]);
    println!("结果 (共{}个):", result3.len());
    for perm in &result3 {
        println!("  {:?}", perm);
    }
    println!();

    // 测试用例 4: 优化版本 [1, 2, 3, 4]
    println!("测试 4: permute_optimized(vec![1, 2, 3, 4])");
    let result4 = permute_optimized(vec![1, 2, 3, 4]);
    println!("结果 (共{}个):", result4.len());
    println!("前 3 个排列:");
    for i in 0..3 {
        println!("  {:?}", result4[i]);
    }
    println!("后 3 个排列:");
    for i in (result4.len() - 3)..result4.len() {
        println!("  {:?}", result4[i]);
    }
    println!();

    // 测试用例 5: [10, 20, 30]
    println!("测试 5: permute_optimized(vec![10, 20, 30])");
    let result5 = permute_optimized(vec![10, 20, 30]);
    println!("结果 (共{}个):", result5.len());
    for perm in &result5 {
        println!("  {:?}", perm);
    }
}

// jarry@Mac permutation % rustc permutation.rs
// jarry@Mac permutation % ./permutation 
// === 排列回溯测试用例 ===
// 测试 1: permute(vec![1, 2, 3])
// 结果 (共6个):
//   [1, 2, 3]
//   [1, 3, 2]
//   [2, 1, 3]
//   [2, 3, 1]
//   [3, 1, 2]
//   [3, 2, 1]

// 测试 2: permute(vec![1, 2])
// 结果 (共2个):
//   [1, 2]
//   [2, 1]

// 测试 3: permute(vec![1])
// 结果 (共1个):
//   [1]

// 测试 4: permute_optimized(vec![1, 2, 3, 4])
// 结果 (共24个):
// 前 3 个排列:
//   [1, 2, 3, 4]
//   [1, 2, 4, 3]
//   [1, 3, 2, 4]
// 后 3 个排列:
//   [4, 3, 1, 2]
//   [4, 1, 3, 2]
//   [4, 1, 2, 3]

// 测试 5: permute_optimized(vec![10, 20, 30])
// 结果 (共6个):
//   [10, 20, 30]
//   [10, 30, 20]
//   [20, 10, 30]
//   [20, 30, 10]
//   [30, 20, 10]
//   [30, 10, 20]