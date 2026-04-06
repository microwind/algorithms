/**
 * 回溯算法 - 子集生成 (Subsets)
 * 使用递归生成数组的所有子集
 */

/**
 * 生成数组的所有子集
 */
fn subsets(nums: &[i32]) -> Vec<Vec<i32>> {
    let mut result: Vec<Vec<i32>> = Vec::new();
    
    /**
     * 回溯生成子集
     */
    fn backtrack(nums: &[i32], start: usize, current: &mut Vec<i32>, result: &mut Vec<Vec<i32>>) {
        // 每次递归都将当前子集加入结果
        result.push(current.clone());
        
        // 从start开始尝试每个元素
        for i in start..nums.len() {
            // 选择元素
            current.push(nums[i]);
            
            // 递归：继续处理后面的元素
            backtrack(nums, i + 1, current, result);
            
            // 回溯：撤销选择
            current.pop();
        }
    }
    
    let mut current: Vec<i32> = Vec::new();
    backtrack(nums, 0, &mut current, &mut result);
    result
}

fn main() {
    let nums = vec![1, 2, 3];
    let result = subsets(&nums);
    
    println!("数组 {:?} 的所有子集:", nums);
    println!("共 {} 个子集\n", result.len());
    
    for (i, subset) in result.iter().enumerate() {
        println!("  {}. {:?}", i + 1, subset);
    }
    
    println!("\n递归过程可视化:");
    println!("        []");
    println!("       / | \\");
    println!("     [1] [2] [3]");
    println!("    /  \\      |");
    println!("  [1,2] [1,3] [2,3]");
    println!("   /");
    println!("[1,2,3]");
}
