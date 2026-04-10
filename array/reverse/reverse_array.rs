/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组反转算法 - Rust实现
 */

/**
 * 反转数组
 * 算法原理：使用双指针技术，头尾指针向中间移动并交换元素
 * 时间复杂度：O(n) - 只需遍历数组的一半
 * 空间复杂度：O(1) - 原地操作，不使用额外空间
 * @param arr - 待反转的可变数组引用
 */
fn reverse_array(arr: &mut [i32]) {
    let mut left = 0;
    let mut right = arr.len();

    // 左右指针向中间移动，交换元素
    while left < right {
        // 使用标准库swap方法交换元素
        arr.swap(left, right - 1);
        left += 1;
        right -= 1;
    }
}

/**
 * 主函数 - 测试数组反转
 */
fn main() {
    let mut arr = vec![1, 2, 3, 4, 5];
    println!("原始数组: {:?}", arr);
    reverse_array(&mut arr);
    println!("反转后数组: {:?}", arr);
}

/**
 * 输出结果：
 * 原始数组: [1, 2, 3, 4, 5]
 * 反转后数组: [5, 4, 3, 2, 1]
 */

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_reverse_array() {
        let mut arr = vec![1, 2, 3, 4, 5];
        reverse_array(&mut arr);
        assert_eq!(arr, vec![5, 4, 3, 2, 1]);
    }

    #[test]
    fn test_reverse_empty() {
        let mut arr: Vec<i32> = vec![];
        reverse_array(&mut arr);
        assert_eq!(arr, vec![]);
    }

    #[test]
    fn test_reverse_single() {
        let mut arr = vec![42];
        reverse_array(&mut arr);
        assert_eq!(arr, vec![42]);
    }
}
