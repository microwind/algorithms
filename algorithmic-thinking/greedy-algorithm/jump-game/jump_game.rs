/*
 * 跳跃游戏 - 使用贪心判断能否到达最后一个下标
 *
 * 算法：
 * - 给定一个数组，每个元素表示当前位置最大可跳跃步数
 * - 判断是否可以到达最后一个下标
 * - 贪心策略：维护当前能到达的最远位置
 *
 * 时间复杂度：O(n)（单次遍历）
 * 空间复杂度：O(1)（不计输出）
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

// 判断是否能到达数组的最后一个下标
fn can_jump(nums: &[usize]) -> bool {
    if nums.is_empty() || nums.len() == 1 {
        return true;
    }

    let mut max_reach = 0;

    for (i, &num) in nums.iter().enumerate() {
        // 如果当前位置超过了最远可达位置，则无法继续前进，返回 false
        if i > max_reach {
            return false;
        }

        // 更新当前能到达的最远位置
        max_reach = max_reach.max(i + num);

        // 提前结束：一旦可以到达末尾，立刻返回 true
        if max_reach >= nums.len() - 1 {
            return true;
        }
    }

    max_reach >= nums.len() - 1
}

// 计算到达最后一个下标所需的最少跳跃次数
fn min_jumps(nums: &[usize]) -> i32 {
    if nums.is_empty() || nums.len() == 1 {
        return 0;
    }

    // 先检查是否可以到达终点
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

    // 使用贪心策略计算最少跳跃次数
    let mut jumps = 0;
    let mut current_end = 0;
    let mut farthest = 0;

    // 遍历数组，计算最少跳跃次数
    for (i, &num) in nums[..nums.len() - 1].iter().enumerate() {
        // 更新当前能到达的最远位置
        farthest = farthest.max(i + num);
        // 如果当前位置等于当前结束位置，则跳跃次数加1，并更新当前结束位置

        if i == current_end {
            jumps += 1;
            current_end = farthest;
        }
    }

    jumps
}

// 构造从起点到终点的一条跳跃路径
fn jump_path(nums: &[usize]) -> Vec<usize> {
    if nums.is_empty() {
        return vec![];
    }

    if nums.len() == 1 {
        return vec![0];
    }

    // 先检查是否可以到达终点
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

    // 贪心构造路径
    let mut path = vec![0];
    let mut current_pos = 0;
    // 遍历数组，构造跳跃路径
    while current_pos < nums.len() - 1 {
        // 初始化下一个位置为当前位置
        let mut next_pos = current_pos;
        // 初始化下一个位置能到达的最远位置为当前位置能到达的最远位置
        let mut max_next_reach = current_pos + nums[current_pos];
        // 遍历当前位置能到达的范围内，找到能到达的最远位置
        for i in (current_pos + 1)..=(current_pos + nums[current_pos]).min(nums.len() - 1) {
            // 如果当前位置能到达的最远位置小于当前位置能到达的最远位置，则更新当前位置能到达的最远位置
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

// 综合分析跳跃游戏问题
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
