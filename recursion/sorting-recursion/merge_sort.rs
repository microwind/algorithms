/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 递归排序算法示例 - 归并排序
 * 
 * 算法特点：
 * - 分治法将数组分成两半
 * - 递归排序后合并
 * - 时间复杂度: O(n log n)，空间复杂度: O(n)
 * 
 * 学习重点：理解递归在排序算法中的应用
 */

/**
 * 合并两个有序数组
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param left 左数组
 * @param right 右数组
 * @return 合并后的有序数组
 */
fn merge(left: &[i32], right: &[i32]) -> Vec<i32> {
    let mut result = Vec::new();
    let mut i = 0;
    let mut j = 0;
    
    // 比较并合并
    while i < left.len() && j < right.len() {
        if left[i] <= right[j] {
            result.push(left[i]);
            i += 1;
        } else {
            result.push(right[j]);
            j += 1;
        }
    }
    
    // 添加剩余元素
    while i < left.len() {
        result.push(left[i]);
        i += 1;
    }
    
    while j < right.len() {
        result.push(right[j]);
        j += 1;
    }
    
    result
}

/**
 * 递归归并排序
 * 时间复杂度: O(n log n)，空间复杂度: O(n)
 * @param arr 要排序的数组
 * @return 排序后的数组
 */
fn merge_sort(arr: &[i32]) -> Vec<i32> {
    // 基本情况：单个元素或空数组
    if arr.len() <= 1 {
        return arr.to_vec();
    }
    
    // 分治：将数组分成两半
    let mid = arr.len() / 2;
    let left_half = &arr[..mid];
    let right_half = &arr[mid..];
    
    // 递归排序并合并
    let left_sorted = merge_sort(left_half);
    let right_sorted = merge_sort(right_half);
    
    merge(&left_sorted, &right_sorted)
}

/**
 * 主函数 - 测试归并排序
 */
fn main() {
    // 测试1：普通数组
    let test_array = [64, 34, 25, 12, 22, 11, 90, 88];
    println!("1. 递归归并排序:");
    println!("   原数组: {:?}", test_array);
    let sorted_array = merge_sort(&test_array);
    println!("   排序后: {:?}", sorted_array);
    println!("===");
    
    // 测试2：已排序数组
    let sorted_input = [1, 2, 3, 4, 5, 6, 7, 8];
    println!("2. 边界测试 - 已排序数组:");
    println!("   原数组: {:?}", sorted_input);
    let sorted_result = merge_sort(&sorted_input);
    println!("   排序后: {:?}", sorted_result);
    println!("===");
    
    // 测试3：单个元素
    let single_element = [42];
    println!("3. 边界测试 - 单个元素:");
    println!("   原数组: {:?}", single_element);
    let single_result = merge_sort(&single_element);
    println!("   排序后: {:?}", single_result);
    println!("===");
    
    // 测试4：空数组
    let empty_array: [i32; 0] = [];
    println!("4. 边界测试 - 空数组:");
    println!("   原数组: {:?}", empty_array);
    let empty_result = merge_sort(&empty_array);
    println!("   排序后: {:?}", empty_result);
    println!("===");
}

/*打印结果
jarry@Mac sorting-recursion % rustc merge_sort.rs && ./merge_sort
1. 递归归并排序:
   原数组: [64, 34, 25, 12, 22, 11, 90, 88]
   排序后: [11, 12, 22, 25, 34, 64, 88, 90]
===
2. 边界测试 - 已排序数组:
   原数组: [1, 2, 3, 4, 5, 6, 7, 8]
   排序后: [1, 2, 3, 4, 5, 6, 7, 8]
===
3. 边界测试 - 单个元素:
   原数组: [42]
   排序后: [42]
===
4. 边界测试 - 空数组:
   原数组: []
   排序后: []
===
*/
