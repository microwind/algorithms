/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 合并有序数组算法 - Rust实现
 * 
 * 算法原理：
 * 从两个数组的末尾开始向前合并。使用三个指针：
 * - i: 指向nums1有效元素的末尾
 * - j: 指向nums2的末尾
 * - k: 指向合并后数组的末尾
 * 
 * 每次比较nums1[i]和nums2[j]，将较大的放到nums1[k]位置。
 * 这样可以避免覆盖nums1中未处理的元素。
 * 
 * 时间复杂度：O(m+n) - m和n分别是两个数组的长度
 * 空间复杂度：O(1) - 原地合并
 */

/**
 * 合并两个有序数组
 * @param nums1 - 第一个数组（足够空间容纳两个数组元素）
 * @param m - nums1中有效元素数量
 * @param nums2 - 第二个数组
 * @param n - nums2中元素数量
 */
fn merge(nums1: &mut [i32], m: usize, nums2: &[i32], n: usize) {
    // 从末尾开始合并
    let mut i: isize = m as isize - 1;        // nums1有效元素末尾
    let mut j: isize = n as isize - 1;        // nums2末尾
    let mut k: isize = (m + n) as isize - 1;  // 合并后数组末尾

    // 当两个数组都还有元素时
    while i >= 0 && j >= 0 {
        if nums1[i as usize] > nums2[j as usize] {
            nums1[k as usize] = nums1[i as usize];
            i -= 1;
        } else {
            nums1[k as usize] = nums2[j as usize];
            j -= 1;
        }
        k -= 1;
    }

    // 如果nums2还有剩余元素，复制到nums1前面
    while j >= 0 {
        nums1[k as usize] = nums2[j as usize];
        j -= 1;
        k -= 1;
    }
    // nums1剩余元素已经在正确位置，无需处理
}

/**
 * 主函数 - 测试合并有序数组
 */
fn main() {
    let mut nums1 = vec![1, 2, 3, 0, 0, 0];
    let nums2 = vec![2, 5, 6];
    let m = 3;
    let n = 3;

    println!("nums1: {:?}", &nums1[..m]);
    println!("nums2: {:?}", nums2);

    merge(&mut nums1, m, &nums2, n);

    println!("合并后: {:?}", nums1);
}

/**
 * 输出结果：
 * nums1: [1, 2, 3]
 * nums2: [2, 5, 6]
 * 合并后: [1, 2, 2, 3, 5, 6]
 */

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_merge() {
        let mut nums1 = vec![1, 2, 3, 0, 0, 0];
        let nums2 = vec![2, 5, 6];
        merge(&mut nums1, 3, &nums2, 3);
        assert_eq!(nums1, vec![1, 2, 2, 3, 5, 6]);
    }

    #[test]
    fn test_merge_empty_nums2() {
        let mut nums1 = vec![1, 2, 3];
        let nums2: Vec<i32> = vec![];
        merge(&mut nums1, 3, &nums2, 0);
        assert_eq!(nums1, vec![1, 2, 3]);
    }

    #[test]
    fn test_merge_nums2_smaller() {
        let mut nums1 = vec![2, 5, 6, 0, 0, 0];
        let nums2 = vec![1, 2, 3];
        merge(&mut nums1, 3, &nums2, 3);
        assert_eq!(nums1, vec![1, 2, 2, 3, 5, 6]);
    }
}
