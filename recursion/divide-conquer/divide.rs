/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 分治算法示例 - 数组求和
 * 
 * 算法特点：
 * - 分治法将问题分解为子问题
 * - 递归解决子问题后合并结果
 * - 时间复杂度: O(n)，空间复杂度: O(log n)
 * 
 * 学习重点：理解分治算法的递归实现
 */

/**
 * 递归计算数组元素和
 * 时间复杂度: O(n)，空间复杂度: O(log n)
 * @param arr 数组
 * @param left 左边界
 * @param right 右边界
 * @return 数组和
 */
fn divide_sum(arr: &[i32], left: usize, right: usize) -> i32 {
    // 基本情况：单个元素
    if left == right {
        return arr[left];
    }
    
    // 分治：将数组分成两半
    let mid = (left + right) / 2;
    let left_sum = divide_sum(arr, left, mid);
    let right_sum = divide_sum(arr, mid + 1, right);
    
    // 合并：返回两半的和
    left_sum + right_sum
}

/**
 * 主函数 - 测试分治算法
 */
fn main() {
    // 测试1：数组求和
    let test_array = [1, 2, 3, 4, 5, 6, 7, 8];
    println!("1. 分治算法 - 数组求和:");
    println!("   数组: [{:?}]", test_array);
    println!("   求和结果: {}", divide_sum(&test_array, 0, test_array.len() - 1));
    println!("===");
    
    // 测试2：空数组
    let empty_array: [i32; 0] = [];
    println!("2. 边界测试 - 空数组:");
    println!("   数组: [{:?}]", empty_array);
    if !empty_array.is_empty() {
        println!("   求和结果: {}", divide_sum(&empty_array, 0, empty_array.len() - 1));
    } else {
        println!("   求和结果: 0");
    }
    println!("===");
    
    // 测试3：单个元素
    let single_array = [42];
    println!("3. 边界测试 - 单个元素:");
    println!("   数组: [{:?}]", single_array);
    println!("   求和结果: {}", divide_sum(&single_array, 0, single_array.len() - 1));
    println!("===");
}

/*打印结果
jarry@Mac divide-conquer % rustc divide.rs && ./divide
1. 分治算法 - 数组求和:
   数组: [1, 2, 3, 4, 5, 6, 7, 8]
   求和结果: 36
===
2. 边界测试 - 空数组:
   数组: []
   求和结果: 0
===
3. 边界测试 - 单个元素:
   数组: [42]
   求和结果: 42
===
*/
