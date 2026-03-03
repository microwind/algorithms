/*
使用回溯生成排列 (Rust Implementation)

算法说明:
- Generate all permutations of a vector using backtracking
- Use Vec for dynamic allocation and Rust's ownership system
- At each recursion level, try each unused element
- Backtrack by not including the element in the next recursion

Time Complexity: O(n! * n) - n! permutations, each taking O(n) to copy
Space Complexity: O(n) - recursion depth (not counting output)

示例:
    permute(vec![1, 2, 3]) returns all 6 permutations
*/

// / Generate all permutations of a vector using backtracking.
// /
// / # Arguments
// / * `nums` - Vector of integers to permute
// /
// / # 返回
// / Vector of all permutations
// /
// / # 示例
// / ```
// / let result = permute(vec![1, 2, 3]);
// / assert_eq!(result.len(), 6); // 3! = 6
// / ```
fn permute(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut result = Vec::new();
    backtrack(&mut result, Vec::new(), nums);
    result
}

// / Helper function for backtracking.
fn backtrack(result: &mut Vec<Vec<i32>>, mut current: Vec<i32>, remaining: Vec<i32>) {
    // Base case: all elements used, add copy to result
    if remaining.is_empty() {
        result.push(current);
        return;
    }

    // Try each remaining element as the next element
    for i in 0..remaining.len() {
        // Choose: add remaining[i] to current permutation
        current.push(remaining[i]);

        // Explore: recursively build rest of permutation
        let mut new_remaining = remaining.clone();
        new_remaining.remove(i);
        backtrack(result, current.clone(), new_remaining);

        // Unchoose: remove the element for backtracking
        current.pop();
    }
}

// / Optimized permutation using in-place swapping.
// / More efficient by modifying the array instead of creating new vectors.
// /
// / # Arguments
// / * `nums` - Vector of integers to permute
// /
// / # 返回
// / Vector of all permutations
fn permute_optimized(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut result = Vec::new();
    let mut arr = nums;
    backtrack_swap(&mut result, &mut arr, 0);
    result
}

// / Helper function for in-place swap backtracking.
fn backtrack_swap(result: &mut Vec<Vec<i32>>, arr: &mut Vec<i32>, index: usize) {
    // Base case: reached end of array
    if index == arr.len() {
        result.push(arr.clone());
        return;
    }

    // Try each element from index onwards as the next element
    for i in index..arr.len() {
        // Choose: swap elements
        arr.swap(index, i);

        // Explore: permute the rest
        backtrack_swap(result, arr, index + 1);

        // Unchoose: swap back
        arr.swap(index, i);
    }
}

fn main() {
    println!("=== Permutation Backtracking Test Cases ===\n");

    // 测试用例 1: [1, 2, 3]
    println!("Test 1: permute(vec![1, 2, 3])");
    let result1 = permute(vec![1, 2, 3]);
    println!("Result (count={}):", result1.len());
    for perm in &result1 {
        println!("  {:?}", perm);
    }
    println!();

    // 测试用例 2: [1, 2]
    println!("Test 2: permute(vec![1, 2])");
    let result2 = permute(vec![1, 2]);
    println!("Result (count={}):", result2.len());
    for perm in &result2 {
        println!("  {:?}", perm);
    }
    println!();

    // 测试用例 3: [1]
    println!("Test 3: permute(vec![1])");
    let result3 = permute(vec![1]);
    println!("Result (count={}):", result3.len());
    for perm in &result3 {
        println!("  {:?}", perm);
    }
    println!();

    // 测试用例 4: Optimized version with [1, 2, 3, 4]
    println!("Test 4: permute_optimized(vec![1, 2, 3, 4])");
    let result4 = permute_optimized(vec![1, 2, 3, 4]);
    println!("Result (count={}):", result4.len());
    println!("First 3 permutations:");
    for i in 0..3 {
        println!("  {:?}", result4[i]);
    }
    println!("Last 3 permutations:");
    for i in (result4.len() - 3)..result4.len() {
        println!("  {:?}", result4[i]);
    }
    println!();

    // 测试用例 5: [10, 20, 30]
    println!("Test 5: permute_optimized(vec![10, 20, 30])");
    let result5 = permute_optimized(vec![10, 20, 30]);
    println!("Result (count={}):", result5.len());
    for perm in &result5 {
        println!("  {:?}", perm);
    }
}
