/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 最大子数组和算法（Kadane算法） - Rust实现
 * 
 * 算法原理：
 * Kadane算法是一种动态规划方法。对于每个位置，我们决定：
 * 1. 将当前元素加入之前的子数组
 * 2. 从当前元素开始一个新的子数组
 * 取两者中的较大值作为当前最大子数组和。
 * 
 * 时间复杂度：O(n) - 只需遍历数组一次
 * 空间复杂度：O(1) - 仅使用常数额外空间
 */

/**
 * 最大子数组和（Kadane算法）
 * @param nums - 输入数组切片
 * @returns 最大子数组和
 */
fn max_sub_array(nums: &[i32]) -> i32 {
    if nums.is_empty() {
        return 0;
    }

    let mut max_sum = nums[0];      // 全局最大和
    let mut current_sum = nums[0];    // 当前子数组和

    for &num in &nums[1..] {
        // 决定是将当前元素加入之前的子数组，还是从当前元素开始新子数组
        current_sum = std::cmp::max(current_sum + num, num);
        
        // 更新全局最大和
        max_sum = std::cmp::max(max_sum, current_sum);
    }

    max_sum
}

/**
 * 扩展版本：同时返回子数组的起止索引
 */
struct Result {
    max_sum: i32,
    start: usize,
    end: usize,
}

fn max_sub_array_with_indices(nums: &[i32]) -> Result {
    if nums.is_empty() {
        return Result { max_sum: 0, start: 0, end: 0 };
    }

    let mut max_sum = nums[0];
    let mut current_sum = nums[0];
    let mut current_start = 0;
    let mut start = 0;
    let mut end = 0;

    for (i, &num) in nums.iter().enumerate().skip(1) {
        if current_sum + num < num {
            // 从当前元素开始新子数组
            current_sum = num;
            current_start = i;
        } else {
            // 将当前元素加入之前的子数组
            current_sum += num;
        }

        // 更新全局最大和及索引
        if current_sum > max_sum {
            max_sum = current_sum;
            start = current_start;
            end = i;
        }
    }

    Result { max_sum, start, end }
}

/**
 * 主函数 - 测试最大子数组和
 */
fn main() {
    let nums = vec![-2, 1, -3, 4, -1, 2, 1, -5, 4];
    println!("输入数组: {:?}", nums);

    let result = max_sub_array(&nums);
    println!("最大子数组和: {}", result);

    let res = max_sub_array_with_indices(&nums);
    println!("子数组范围: 索引[{}, {}]", res.start, res.end);
    println!("子数组元素: {:?}", &nums[res.start..=res.end]);
}

/**
 * 输出结果：
 * 输入数组: [-2, 1, -3, 4, -1, 2, 1, -5, 4]
 * 最大子数组和: 6
 * 子数组范围: 索引[3, 6]
 * 子数组元素: [4, -1, 2, 1]
 */

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_max_sub_array() {
        let nums = vec![-2, 1, -3, 4, -1, 2, 1, -5, 4];
        assert_eq!(max_sub_array(&nums), 6);
    }

    #[test]
    fn test_single_element() {
        let nums = vec![5];
        assert_eq!(max_sub_array(&nums), 5);
    }

    #[test]
    fn test_all_negative() {
        let nums = vec![-3, -2, -5, -1];
        assert_eq!(max_sub_array(&nums), -1);
    }
}
