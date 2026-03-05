/*
使用回溯生成组合 (Rust Implementation)

算法说明:
- 生成从1到n中选取k个元素的所有组合 (C(n,k))
- 使用回溯系统地探索所有选择
- At each step, only consider elements >= current start position
- This prevents duplicate combinations
- When we've selected k elements, add to result

时间复杂度：O(C(n,k) * k)，其中C(n,k)是组合数
空间复杂度：O(k)，用于递归深度和当前组合

示例:
    combine(4, 2) 返回 [
        [1,2], [1,3], [1,4], [2,3], [2,4], [3,4]
    ]
*/

// / 生成从1到n中选取k个元素的所有组合.
// /
// / # Arguments
// / * `n` - 元素的总数（1到n）
// / * `k` - 每个组合的大小
// /
// / # 返回
// / Vector of all combinations
// /
// / # 示例
// / ```
// / let result = combine(4, 2);
// / assert_eq!(result.len(), 6); // C(4,2) = 6
// / ```
fn combine(n: i32, k: i32) -> Vec<Vec<i32>> {
    let mut result = Vec::new();
    backtrack(&mut result, Vec::new(), 1, n, k);
    result
}

// / Helper function for backtracking.
fn backtrack(result: &mut Vec<Vec<i32>>, mut current: Vec<i32>, start: i32, n: i32, k: i32) {
    // 基本情况：组合已完成
    if current.len() == k as usize {
        result.push(current);
        return;
    }

    // 尝试从start到n的每个数字
    for num in start..=n {
        // 选择：将num添加到当前组合
        current.push(num);

        // 探索：构建组合的其余部分
        // 仅数字 >= num+1 以避免重复
        backtrack(result, current.clone(), num + 1, n, k);

        // 取消选择：移除num以进行回溯
        current.pop();
    }
}

// / Optimized combination with early termination.
// / 剪枝不可能产生k个元素的分支.
// /
// / # Arguments
// / * `n` - Total number of elements
// / * `k` - 每个组合的大小
// /
// / # 返回
// / Vector of all combinations
fn combine_optimized(n: i32, k: i32) -> Vec<Vec<i32>> {
    let mut result = Vec::new();
    backtrack_optimized(&mut result, Vec::new(), 1, n, k);
    result
}

// / Helper function for optimized backtracking with pruning.
fn backtrack_optimized(
    result: &mut Vec<Vec<i32>>,
    mut current: Vec<i32>,
    start: i32,
    n: i32,
    k: i32,
) {
    // 基本情况：组合已完成
    if current.len() == k as usize {
        result.push(current);
        return;
    }

    // 优化：提前终止
    // Remaining slots needed: k - current.len()
    // 可用的元素：n - start + 1
    // 如果没有足够的可用元素，则停止
    let remaining = k as usize - current.len();
    let available = (n - start + 1) as usize;
    if available < remaining {
        return;
    }

    // 尝试从start到n的每个数字
    for num in start..=n {
        current.push(num);
        backtrack_optimized(result, current.clone(), num + 1, n, k);
        current.pop();
    }
}

fn main() {
    println!("=== Combination Backtracking Test Cases ===\n");

    // 测试用例 1: combine(4, 2)
    println!("Test 1: combine(4, 2)");
    let result1 = combine(4, 2);
    println!("Result (count={}):", result1.len());
    for combo in &result1 {
        println!("  {:?}", combo);
    }
    println!();

    // 测试用例 2: combine(3, 1)
    println!("Test 2: combine(3, 1)");
    let result2 = combine(3, 1);
    println!("Result (count={}):", result2.len());
    for combo in &result2 {
        println!("  {:?}", combo);
    }
    println!();

    // 测试用例 3: combine(3, 3)
    println!("Test 3: combine(3, 3)");
    let result3 = combine(3, 3);
    println!("Result (count={}):", result3.len());
    for combo in &result3 {
        println!("  {:?}", combo);
    }
    println!();

    // 测试用例 4: combine(5, 3)
    println!("Test 4: combine(5, 3)");
    let result4 = combine(5, 3);
    println!("Result (count={}):", result4.len());
    for combo in &result4 {
        println!("  {:?}", combo);
    }
    println!();

    // 测试用例 5: combine_optimized(6, 2)
    println!("Test 5: combine_optimized(6, 2)");
    let result5 = combine_optimized(6, 2);
    println!("Result (count={}):", result5.len());
    for combo in &result5 {
        println!("  {:?}", combo);
    }
    println!();

    // 测试用例 6: combine_optimized(5, 4)
    println!("Test 6: combine_optimized(5, 4)");
    let result6 = combine_optimized(5, 4);
    println!("Result (count={}):", result6.len());
    for combo in &result6 {
        println!("  {:?}", combo);
    }
}
