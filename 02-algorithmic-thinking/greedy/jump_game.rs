/*
 * Jump Game - Can reach the last index with greedy jumps
 *
 * Algorithm:
 * - Given an array where each element is the maximum jump length from that position
 * - Determine if you can reach the last index
 * - Greedy approach: track the maximum index we can reach so far
 *
 * Time Complexity: O(n) - single pass through array
 * Space Complexity: O(1) - excluding output
 */

#[derive(Debug)]
struct JumpGameAnalysis {
    can_reach: bool,
    min_jumps: i32,
    path: Vec<usize>,
}

impl std::fmt::Display for JumpGameAnalysis {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(
            f,
            "Can reach: {}, Min jumps: {}, Path: {:?}",
            self.can_reach, self.min_jumps, self.path
        )
    }
}

/// Determine if we can reach the last index of the array
fn can_jump(nums: &[usize]) -> bool {
    if nums.is_empty() || nums.len() == 1 {
        return true;
    }

    let mut max_reach = 0;

    for (i, &num) in nums.iter().enumerate() {
        // If current position is beyond what we can reach, return false
        if i > max_reach {
            return false;
        }

        // Update the maximum position we can reach
        max_reach = max_reach.max(i + num);

        // Early termination: if we can reach the end, return true
        if max_reach >= nums.len() - 1 {
            return true;
        }
    }

    max_reach >= nums.len() - 1
}

/// Find the minimum number of jumps needed to reach the last index
fn min_jumps(nums: &[usize]) -> i32 {
    if nums.is_empty() || nums.len() == 1 {
        return 0;
    }

    // Check if reachable
    let mut max_reach = 0;
    for (i, &num) in nums[..nums.len() - 1].iter().enumerate() {
        if i > max_reach {
            return -1;
        }
        max_reach = max_reach.max(i + num);
    }

    if max_reach < nums.len() - 1 {
        return -1;
    }

    // Find minimum jumps using greedy
    let mut jumps = 0;
    let mut current_end = 0;
    let mut farthest = 0;

    for (i, &num) in nums[..nums.len() - 1].iter().enumerate() {
        farthest = farthest.max(i + num);

        if i == current_end {
            jumps += 1;
            current_end = farthest;
        }
    }

    jumps
}

/// Find a path from start to end
fn jump_path(nums: &[usize]) -> Vec<usize> {
    if nums.is_empty() {
        return vec![];
    }

    if nums.len() == 1 {
        return vec![0];
    }

    // Check if reachable
    let mut max_reach = 0;
    for (i, &num) in nums.iter().enumerate() {
        if i > max_reach {
            return vec![];
        }
        max_reach = max_reach.max(i + num);
        if max_reach >= nums.len() - 1 {
            break;
        }
    }

    if max_reach < nums.len() - 1 {
        return vec![];
    }

    // Greedy path construction
    let mut path = vec![0];
    let mut current_pos = 0;

    while current_pos < nums.len() - 1 {
        let mut next_pos = current_pos;
        let mut max_next_reach = current_pos + nums[current_pos];

        for i in (current_pos + 1)..=(current_pos + nums[current_pos]).min(nums.len() - 1) {
            if i + nums[i] > max_next_reach {
                max_next_reach = i + nums[i];
                next_pos = i;
            }
        }

        if next_pos == current_pos {
            return vec![];
        }

        path.push(next_pos);
        current_pos = next_pos;
    }

    path
}

/// Analyze a jump game problem comprehensively
fn analyze_jump_game(nums: &[usize]) -> JumpGameAnalysis {
    JumpGameAnalysis {
        can_reach: can_jump(nums),
        min_jumps: min_jumps(nums),
        path: jump_path(nums),
    }
}

fn test_basic_reachable() {
    println!("\n[Test 1] Reachable - should return true");

    let nums = vec![2, 3, 1, 1, 4];
    let analysis = analyze_jump_game(&nums);

    println!("Input: {:?}", nums);
    println!("{}", analysis);
}

fn test_not_reachable() {
    println!("\n[Test 2] Not reachable - should return false");

    let nums = vec![3, 2, 1, 0, 4];
    let result = can_jump(&nums);

    println!("Input: {:?}", nums);
    println!("Can reach end: {}", result);
}

fn test_single_element() {
    println!("\n[Test 3] Single element");

    let nums = vec![0];
    let result = can_jump(&nums);

    println!("Input: {:?}", nums);
    println!("Can reach end: {}", result);
}

fn test_zero_jump() {
    println!("\n[Test 4] All zeros except last");

    let nums = vec![0, 1];
    let result = can_jump(&nums);

    println!("Input: {:?}", nums);
    println!("Can reach end: {}", result);
}

fn test_large_jumps() {
    println!("\n[Test 5] Large jumps available");

    let nums = vec![10, 0, 0, 0, 0];
    let analysis = analyze_jump_game(&nums);

    println!("Input: {:?}", nums);
    println!("{}", analysis);
}

fn test_multiple_jumps() {
    println!("\n[Test 6] Requires multiple jumps");

    let nums = vec![2, 3, 1, 1, 1];
    let analysis = analyze_jump_game(&nums);

    println!("Input: {:?}", nums);
    println!("{}", analysis);
}

fn test_blocked() {
    println!("\n[Test 7] Blocked at second-to-last");

    let nums = vec![1, 0, 1, 0];
    let result = can_jump(&nums);

    println!("Input: {:?}", nums);
    println!("Can reach end: {}", result);
}

fn test_two_element() {
    println!("\n[Test 8] Two element array");

    let nums = vec![2, 3];
    let analysis = analyze_jump_game(&nums);

    println!("Input: {:?}", nums);
    println!("{}", analysis);
}

fn test_decreasing() {
    println!("\n[Test 9] Large array with decreasing values");

    let nums = vec![5, 4, 3, 2, 1, 0];
    let analysis = analyze_jump_game(&nums);

    println!("Input: {:?}", nums);
    println!("{}", analysis);
}

fn test_complex() {
    println!("\n[Test 10] Complex reachable scenario");

    let nums = vec![2, 5, 0, 0];
    let analysis = analyze_jump_game(&nums);

    println!("Input: {:?}", nums);
    println!("{}", analysis);
}

fn main() {
    println!("==================================================");
    println!("JUMP GAME - Greedy Approach (Rust)");
    println!("==================================================");

    test_basic_reachable();
    test_not_reachable();
    test_single_element();
    test_zero_jump();
    test_large_jumps();
    test_multiple_jumps();
    test_blocked();
    test_two_element();
    test_decreasing();
    test_complex();
}
