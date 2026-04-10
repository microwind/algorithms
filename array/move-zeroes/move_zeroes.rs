/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 移动零算法 - Rust实现
 * 
 * 算法原理：
 * 使用双指针技术。write指针记录非零元素应该写入的位置，read指针遍历数组。
 * 当read遇到非零元素时，将其复制到write位置，然后两个指针都前进。
 * 当read遇到零时，只前进read指针。最后将write之后的位置全部填充为零。
 * 
 * 时间复杂度：O(n) - 单次遍历数组
 * 空间复杂度：O(1) - 原地操作
 */

/**
 * 移动零到数组末尾
 * @param nums - 待处理的可变数组引用
 */
fn move_zeroes(nums: &mut [i32]) {
    let mut write = 0;  // 写指针，指向下一个非零元素应该存放的位置
    let mut read = 0;   // 读指针，遍历数组
    let n = nums.len();

    // 第一遍：将所有非零元素移到前面
    while read < n {
        if nums[read] != 0 {
            // 遇到非零元素，写入write位置
            nums[write] = nums[read];
            write += 1;
        }
        read += 1;
    }

    // 第二遍：将write之后的位置填充为零
    while write < n {
        nums[write] = 0;
        write += 1;
    }
}

/**
 * 主函数 - 测试移动零
 */
fn main() {
    let mut nums = vec![0, 1, 0, 3, 12, 0, 5];
    println!("原始数组: {:?}", nums);
    move_zeroes(&mut nums);
    println!("移动零后: {:?}", nums);
}

/**
 * 输出结果：
 * 原始数组: [0, 1, 0, 3, 12, 0, 5]
 * 移动零后: [1, 3, 12, 5, 0, 0, 0]
 */

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_move_zeroes() {
        let mut nums = vec![0, 1, 0, 3, 12, 0, 5];
        move_zeroes(&mut nums);
        assert_eq!(nums, vec![1, 3, 12, 5, 0, 0, 0]);
    }

    #[test]
    fn test_move_zeroes_all_zero() {
        let mut nums = vec![0, 0, 0];
        move_zeroes(&mut nums);
        assert_eq!(nums, vec![0, 0, 0]);
    }

    #[test]
    fn test_move_zeroes_no_zero() {
        let mut nums = vec![1, 2, 3];
        move_zeroes(&mut nums);
        assert_eq!(nums, vec![1, 2, 3]);
    }
}
