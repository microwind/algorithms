/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 两数之和算法 - Rust实现
 * 
 * 算法原理：
 * 使用哈希表辅助查找。遍历数组时，对于每个元素，计算目标值与当前元素的差值（补数），
 * 检查补数是否已在哈希表中。如果在，则找到答案；否则将当前元素存入哈希表。
 * 
 * 时间复杂度：O(n) - 只需遍历数组一次
 * 空间复杂度：O(n) - 哈希表存储
 */

use std::collections::HashMap;

/**
 * 两数之和
 * @param nums - 输入数组
 * @param target - 目标和
 * @returns 返回两个数的索引元组Option
 */
fn two_sum(nums: &[i32], target: i32) -> Option<(usize, usize)> {
    // 使用HashMap存储已遍历的元素及其索引
    let mut map: HashMap<i32, usize> = HashMap::new();

    for (i, &num) in nums.iter().enumerate() {
        // 计算补数
        let complement = target - num;

        // 检查补数是否已在哈希表中
        if let Some(&index) = map.get(&complement) {
            // 找到答案，返回两个索引
            return Some((index, i));
        }

        // 将当前元素及其索引存入哈希表
        map.insert(num, i);
    }

    // 未找到答案
    None
}

/**
 * 主函数 - 测试两数之和
 */
fn main() {
    let nums = vec![2, 7, 11, 15];
    let target = 9;

    match two_sum(&nums, target) {
        Some((i, j)) => {
            println!("目标值: {}", target);
            println!("结果索引: [{}, {}]", i, j);
            println!("对应数值: {} + {} = {}", nums[i], nums[j], target);
        }
        None => println!("未找到答案"),
    }
}

/**
 * 输出结果：
 * 目标值: 9
 * 结果索引: [0, 1]
 * 对应数值: 2 + 7 = 9
 */

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_two_sum() {
        let nums = vec![2, 7, 11, 15];
        let result = two_sum(&nums, 9);
        assert_eq!(result, Some((0, 1)));
    }

    #[test]
    fn test_two_sum_not_found() {
        let nums = vec![1, 2, 3];
        let result = two_sum(&nums, 10);
        assert_eq!(result, None);
    }

    #[test]
    fn test_two_sum_negative() {
        let nums = vec![-1, -2, -3, -4, -5];
        let result = two_sum(&nums, -8);
        assert_eq!(result, Some((2, 4)));
    }
}
