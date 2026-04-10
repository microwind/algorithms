/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组旋转算法 - Rust实现
 */

/**
 * 翻转数组的指定区间
 * @param arr - 待翻转的可变切片
 * @param start - 起始索引
 * @param end - 结束索引
 */
fn reverse(arr: &mut [i32], start: usize, end: usize) {
    let mut left = start;
    let mut right = end;

    while left < right {
        arr.swap(left, right);
        left += 1;
        right -= 1;
    }
}

/**
 * 向右旋转数组k个位置
 * 算法原理：三次翻转法
 *   1. 翻转整个数组
 *   2. 翻转前k个元素
 *   3. 翻转后n-k个元素
 * 时间复杂度：O(n) - 三次线性遍历
 * 空间复杂度：O(1) - 原地操作
 * @param arr - 待旋转的可变数组引用
 * @param k - 旋转位数
 */
fn rotate_array(arr: &mut [i32], k: usize) {
    let n = arr.len();
    if n == 0 {
        return;
    }

    // 处理k大于数组长度的情况
    let k = k % n;
    if k == 0 {
        return;
    }

    // 三次翻转法
    reverse(arr, 0, n - 1); // 翻转整个数组
    reverse(arr, 0, k - 1); // 翻转前k个
    reverse(arr, k, n - 1); // 翻转后n-k个
}

/**
 * 向左旋转数组k个位置
 * @param arr - 待旋转的可变数组引用
 * @param k - 旋转位数
 */
fn rotate_array_left(arr: &mut [i32], k: usize) {
    let n = arr.len();
    if n == 0 {
        return;
    }

    let k = k % n;
    if k == 0 {
        return;
    }

    // 向左旋转k位等价于向右旋转n-k位
    rotate_array(arr, n - k);
}

/**
 * 主函数 - 测试数组旋转
 */
fn main() {
    let mut arr1 = vec![1, 2, 3, 4, 5, 6, 7];
    println!("原始数组: {:?}", arr1);
    rotate_array(&mut arr1, 3);
    println!("向右旋转3位: {:?}", arr1);

    let mut arr2 = vec![1, 2, 3, 4, 5, 6, 7];
    rotate_array_left(&mut arr2, 3);
    println!("向左旋转3位: {:?}", arr2);
}

/**
 * 输出结果：
 * 原始数组: [1, 2, 3, 4, 5, 6, 7]
 * 向右旋转3位: [5, 6, 7, 1, 2, 3, 4]
 * 向左旋转3位: [4, 5, 6, 7, 1, 2, 3]
 */

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_rotate_array() {
        let mut arr = vec![1, 2, 3, 4, 5, 6, 7];
        rotate_array(&mut arr, 3);
        assert_eq!(arr, vec![5, 6, 7, 1, 2, 3, 4]);
    }

    #[test]
    fn test_rotate_array_left() {
        let mut arr = vec![1, 2, 3, 4, 5, 6, 7];
        rotate_array_left(&mut arr, 3);
        assert_eq!(arr, vec![4, 5, 6, 7, 1, 2, 3]);
    }

    #[test]
    fn test_rotate_k_larger_than_n() {
        let mut arr = vec![1, 2, 3];
        rotate_array(&mut arr, 5); // 5 % 3 = 2
        assert_eq!(arr, vec![2, 3, 1]);
    }
}
