/**
 * 回溯算法 - 全排列 (Permutations)
 * 使用递归生成数组的所有排列
 */

/**
 * 生成数组的所有排列
 */
fn permutations(nums: &[i32]) -> Vec<Vec<i32>> {
    let mut result: Vec<Vec<i32>> = Vec::new();
    
    /**
     * 回溯生成排列
     */
    fn backtrack(nums: &[i32], current: &mut Vec<i32>, used: &mut Vec<bool>, result: &mut Vec<Vec<i32>>) {
        // 基础情况：当前排列长度等于输入数组长度
        if current.len() == nums.len() {
            result.push(current.clone());
            return;
        }
        
        // 递归情况：尝试每个元素
        for i in 0..nums.len() {
            // 如果元素已经被使用，跳过
            if used[i] {
                continue;
            }
            
            // 选择元素
            current.push(nums[i]);
            used[i] = true;
            
            // 递归：继续处理
            backtrack(nums, current, used, result);
            
            // 回溯：撤销选择
            current.pop();
            used[i] = false;
        }
    }
    
    let mut current: Vec<i32> = Vec::new();
    let mut used: Vec<bool> = vec![false; nums.len()];
    backtrack(nums, &mut current, &mut used, &mut result);
    result
}

fn main() {
    let nums = vec![1, 2, 3];
    let result = permutations(&nums);
    
    println!("数组 {:?} 的所有排列:", nums);
    
    for (i, perm) in result.iter().enumerate() {
        println!("  {}. {:?}", i + 1, perm);
    }
    
    println!("\n共 {} 种排列", result.len());
}
