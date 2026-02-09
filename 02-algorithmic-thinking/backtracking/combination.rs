/*
Combination Generator using Backtracking (Rust Implementation)

Algorithm Explanation:
- Generate all combinations of k elements from 1 to n (C(n,k))
- Use backtracking to systematically explore all choices
- At each step, only consider elements >= current start position
- This prevents duplicate combinations
- When we've selected k elements, add to result

Time Complexity: O(C(n,k) * k) where C(n,k) is the number of combinations
Space Complexity: O(k) for recursion depth and current combination

Example:
    combine(4, 2) returns [
        [1,2], [1,3], [1,4], [2,3], [2,4], [3,4]
    ]
*/

/// Generate all combinations of k elements from 1 to n.
///
/// # Arguments
/// * `n` - Total number of elements (1 to n)
/// * `k` - Size of each combination
///
/// # Returns
/// Vector of all combinations
///
/// # Example
/// ```
/// let result = combine(4, 2);
/// assert_eq!(result.len(), 6); // C(4,2) = 6
/// ```
fn combine(n: i32, k: i32) -> Vec<Vec<i32>> {
    let mut result = Vec::new();
    backtrack(&mut result, Vec::new(), 1, n, k);
    result
}

/// Helper function for backtracking.
fn backtrack(result: &mut Vec<Vec<i32>>, mut current: Vec<i32>, start: i32, n: i32, k: i32) {
    // Base case: combination is complete
    if current.len() == k as usize {
        result.push(current);
        return;
    }

    // Try each number from start to n
    for num in start..=n {
        // Choose: add num to current combination
        current.push(num);

        // Explore: build rest of combination
        // Only numbers >= num+1 to avoid duplicates
        backtrack(result, current.clone(), num + 1, n, k);

        // Unchoose: remove num for backtracking
        current.pop();
    }
}

/// Optimized combination with early termination.
/// Prunes branches that can't possibly yield k elements.
///
/// # Arguments
/// * `n` - Total number of elements
/// * `k` - Size of each combination
///
/// # Returns
/// Vector of all combinations
fn combine_optimized(n: i32, k: i32) -> Vec<Vec<i32>> {
    let mut result = Vec::new();
    backtrack_optimized(&mut result, Vec::new(), 1, n, k);
    result
}

/// Helper function for optimized backtracking with pruning.
fn backtrack_optimized(
    result: &mut Vec<Vec<i32>>,
    mut current: Vec<i32>,
    start: i32,
    n: i32,
    k: i32,
) {
    // Base case: combination is complete
    if current.len() == k as usize {
        result.push(current);
        return;
    }

    // Optimization: early termination
    // Remaining slots needed: k - current.len()
    // Elements available: n - start + 1
    // If not enough elements available, stop
    let remaining = k as usize - current.len();
    let available = (n - start + 1) as usize;
    if available < remaining {
        return;
    }

    // Try each number from start to n
    for num in start..=n {
        current.push(num);
        backtrack_optimized(result, current.clone(), num + 1, n, k);
        current.pop();
    }
}

fn main() {
    println!("=== Combination Backtracking Test Cases ===\n");

    // Test Case 1: combine(4, 2)
    println!("Test 1: combine(4, 2)");
    let result1 = combine(4, 2);
    println!("Result (count={}):", result1.len());
    for combo in &result1 {
        println!("  {:?}", combo);
    }
    println!();

    // Test Case 2: combine(3, 1)
    println!("Test 2: combine(3, 1)");
    let result2 = combine(3, 1);
    println!("Result (count={}):", result2.len());
    for combo in &result2 {
        println!("  {:?}", combo);
    }
    println!();

    // Test Case 3: combine(3, 3)
    println!("Test 3: combine(3, 3)");
    let result3 = combine(3, 3);
    println!("Result (count={}):", result3.len());
    for combo in &result3 {
        println!("  {:?}", combo);
    }
    println!();

    // Test Case 4: combine(5, 3)
    println!("Test 4: combine(5, 3)");
    let result4 = combine(5, 3);
    println!("Result (count={}):", result4.len());
    for combo in &result4 {
        println!("  {:?}", combo);
    }
    println!();

    // Test Case 5: combine_optimized(6, 2)
    println!("Test 5: combine_optimized(6, 2)");
    let result5 = combine_optimized(6, 2);
    println!("Result (count={}):", result5.len());
    for combo in &result5 {
        println!("  {:?}", combo);
    }
    println!();

    // Test Case 6: combine_optimized(5, 4)
    println!("Test 6: combine_optimized(5, 4)");
    let result6 = combine_optimized(5, 4);
    println!("Result (count={}):", result6.len());
    for combo in &result6 {
        println!("  {:?}", combo);
    }
}
