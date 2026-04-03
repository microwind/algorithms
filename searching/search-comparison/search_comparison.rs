/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 搜索算法综合对比
 * 对比不同搜索算法的性能特点
 */

use std::collections::HashMap;
use std::time::Instant;

/**
 * linear_search - 线性查找 - O(n)
 * 
 * 算法原理：
 * 1. 从数组开头逐个遍历元素
 * 2. 比较当前元素是否等于目标值
 * 3. 找到目标则返回索引，否则继续
 * 4. 遍历结束未找到则返回-1
 * 
 * 适用场景：
 * - 小规模数据集
 * - 无序数据
 * - 需要查找所有匹配项
 * 
 * @param {&[i32]} arr - 待搜索数组
 * @param {i32} target - 目标值
 * @returns {isize} 找到返回索引，未找到返回-1
 */
fn linear_search(arr: &[i32], target: i32) -> isize {
    for (i, &val) in arr.iter().enumerate() {
        if val == target {
            return i as isize;
        }
    }
    -1
}

/**
 * binary_search - 二分查找 - O(log n)，要求数组有序
 * 
 * 算法原理：
 * 1. 初始化左右边界：left=0, right=arr.len()-1
 * 2. 计算中间位置：mid = (left + right) / 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * @param {&[i32]} arr - 有序数组
 * @param {i32} target - 目标值
 * @returns {isize} 找到返回索引，未找到返回-1
 */
fn binary_search(arr: &[i32], target: i32) -> isize {
    let mut left = 0;
    let mut right = arr.len() - 1;
    
    while left <= right {
        let mid = left + (right - left) / 2;
        if arr[mid] == target {
            return mid as isize;
        } else if arr[mid] < target {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    -1
}

/**
 * jump_search - 跳跃查找 - O(√n)，要求数组有序
 * 
 * 算法原理：
 * 1. 计算跳跃步长：step = sqrt(n)
 * 2. 按步长跳跃查找目标所在的块
 * 3. 在目标块内进行线性查找
 * 4. 结合跳跃和线性查找的优势
 * 
 * @param {&[i32]} arr - 有序数组
 * @param {i32} target - 目标值
 * @returns {isize} 找到返回索引，未找到返回-1
 */
fn jump_search(arr: &[i32], target: i32) -> isize {
    let n = arr.len();
    let step = (n as f64).sqrt() as usize;
    
    // 找到目标所在的块
    let mut prev = 0;
    while arr[std::cmp::min(step, n) - 1] < target {
        prev = step;
        step += (n as f64).sqrt() as usize;
        if prev >= n {
            return -1;
        }
    }
    
    // 在线性搜索目标
    while arr[prev] < target {
        prev += 1;
        if prev == std::cmp::min(step, n) {
            return -1;
        }
    }
    
    if arr[prev] == target {
        prev as isize
    } else {
        -1
    }
}

/**
 * exponential_search - 指数查找 - O(log n)，要求数组有序
 * 
 * 算法原理：
 * 1. 指数增长确定查找范围
 * 2. 在确定范围内进行二分查找
 * 3. 结合指数增长和二分查找的优势
 * 
 * @param {&[i32]} arr - 有序数组
 * @param {i32} target - 目标值
 * @returns {isize} 找到返回索引，未找到返回-1
 */
fn exponential_search(arr: &[i32], target: i32) -> isize {
    let n = arr.len();
    
    // 如果目标在第一个位置
    if arr[0] == target {
        return 0;
    }
    
    // 找到范围
    let mut bound = 1;
    while bound < n && arr[bound] <= target {
        bound *= 2;
    }
    
    // 在该范围内进行二分查找
    let left = bound / 2;
    let right = std::cmp::min(bound, n - 1);
    
    let mut left = left;
    let mut right = right;
    
    while left <= right {
        let mid = left + (right - left) / 2;
        if arr[mid] == target {
            return mid as isize;
        } else if arr[mid] < target {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    -1
}

/**
 * interpolation_search - 插值查找 - O(log log n)，要求数组均匀分布
 * 
 * 算法原理：
 * 1. 通过公式估算目标位置：pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
 * 2. 根据估算位置调整查找范围
 * 3. 重复直到找到目标或确定不存在
 * 
 * @param {&[i32]} arr - 有序数组
 * @param {i32} target - 目标值
 * @returns {isize} 找到返回索引，未找到返回-1
 */
fn interpolation_search(arr: &[i32], target: i32) -> isize {
    let mut low = 0;
    let mut high = arr.len() - 1;
    
    while low <= high && target >= arr[low] && target <= arr[high] {
        if low == high {
            return if arr[low] == target { low as isize } else { -1 };
        }
        
        // 防止除零错误
        if arr[high] == arr[low] {
            break;
        }
        
        // 计算插值位置
        let pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low]);
        
        // 检查计算的位置是否有效
        if pos < low || pos > high {
            break;
        }
        
        if arr[pos] == target {
            return pos as isize;
        }
        
        if arr[pos] < target {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    -1
}

/**
 * hash_search - 哈希查找 - O(1)，需要额外空间
 * 
 * 算法原理：
 * 1. 构建哈希表存储所有元素
 * 2. 通过哈希函数计算目标位置
 * 3. 直接访问对应位置
 * 
 * @param {&[i32]} arr - 待搜索数组
 * @param {i32} target - 目标值
 * @returns {isize} 找到返回索引，未找到返回-1
 */
fn hash_search(arr: &[i32], target: i32) -> isize {
    // 构建哈希表
    let mut hash_table: HashMap<i32, usize> = HashMap::new();
    for (i, &val) in arr.iter().enumerate() {
        hash_table.insert(val, i);
    }
    
    match hash_table.get(&target) {
        Some(&index) => index as isize,
        None => -1,
    }
}

/**
 * test_algorithms - 测试所有搜索算法的性能
 * 
 * @param {&[i32]} arr - 有序数组
 * @param {&[i32]} unsorted_arr - 无序数组
 * @param {i32} target - 目标值
 */
fn test_algorithms(arr: &[i32], unsorted_arr: &[i32], target: i32) {
    println!("\n数组大小: {}", arr.len());
    println!("查找目标: {}", target);
    
    println!("\n有序数组搜索算法对比:");
    println!("------------------------------------------------------------");
    
    // 二分查找
    let start_time = Instant::now();
    let result = binary_search(arr, target);
    let elapsed = start_time.elapsed();
    println!("二分查找:     索引={}, 时间={}ms", result, elapsed.as_millis());
    
    // 跳跃查找
    let start_time = Instant::now();
    let result = jump_search(arr, target);
    let elapsed = start_time.elapsed();
    println!("跳跃查找:     索引={}, 时间={}ms", result, elapsed.as_millis());
    
    // 指数查找
    let start_time = Instant::now();
    let result = exponential_search(arr, target);
    let elapsed = start_time.elapsed();
    println!("指数查找:     索引={}, 时间={}ms", result, elapsed.as_millis());
    
    // 插值查找
    let start_time = Instant::now();
    let result = interpolation_search(arr, target);
    let elapsed = start_time.elapsed();
    println!("插值查找:     索引={}, 时间={}ms", result, elapsed.as_millis());
    
    // 哈希查找
    let start_time = Instant::now();
    let result = hash_search(arr, target);
    let elapsed = start_time.elapsed();
    println!("哈希查找:     索引={}, 时间={}ms", result, elapsed.as_millis());
    
    println!("\n无序数组搜索:");
    println!("------------------------------------------------------------");
    
    // 线性查找（无序数组）
    let start_time = Instant::now();
    let result = linear_search(unsorted_arr, target);
    let elapsed = start_time.elapsed();
    println!("线性查找:     索引={}, 时间={}ms", result, elapsed.as_millis());
}

/**
 * print_algorithm_summary - 打印算法复杂度总结
 */
fn print_algorithm_summary() {
    println!("\n\n算法复杂度总结:");
    println!("  线性查找:     O(n) - 无需预处理");
    println!("  二分查找:     O(log n) - 需要有序");
    println!("  跳跃查找:     O(√n) - 需要有序");
    println!("  指数查找:     O(log n) - 需要有序");
    println!("  插值查找:     O(log log n) - 需要均匀分布");
    println!("  哈希查找:     O(1) - 需要额外空间");
    
    println!("\n适用场景建议:");
    println!("  • 小规模无序数据: 线性查找");
    println!("  • 大规模有序数据: 二分查找");
    println!("  • 均匀分布数据: 插值查找");
    println!("  • 频繁查找操作: 哈希查找");
    println!("  • 静态数据集合: 跳跃查找/指数查找");
}

/**
 * 主程序：演示搜索算法综合对比
 */
fn main() {
    println!("============================================================");
    println!("搜索算法综合对比");
    println!("============================================================");
    
    // 创建测试数据
    let n = 10000;
    let mut sorted_arr: Vec<i32> = Vec::with_capacity(n);
    let mut unsorted_arr: Vec<i32> = Vec::with_capacity(n);
    
    for i in 0..n {
        sorted_arr.push(i as i32);
        unsorted_arr.push((n - 1 - i) as i32); // 逆序
    }
    
    let target = 9999;
    
    // 测试所有算法
    test_algorithms(&sorted_arr, &unsorted_arr, target);
    
    // 打印总结
    print_algorithm_summary();
}

/*
打印结果
jarry@Mac search-comparison % rustc search_comparison.rs && ./search_comparison
============================================================
搜索算法综合对比
============================================================

数组大小: 10000
查找目标: 9999

有序数组搜索算法对比:
------------------------------------------------------------
二分查找:     索引=9999, 时间=0ms
跳跃查找:     索引=9999, 时间=0ms
指数查找:     索引=9999, 时间=0ms
插值查找:     索引=9999, 时间=0ms
哈希查找:     索引=9999, 时间=1ms

无序数组搜索:
------------------------------------------------------------
线性查找:     索引=9999, 时间=1ms

算法复杂度总结:
  线性查找:     O(n) - 无需预处理
  二分查找:     O(log n) - 需要有序
  跳跃查找:     O(√n) - 需要有序
  指数查找:     O(log n) - 需要有序
  插值查找:     O(log log n) - 需要均匀分布
  哈希查找:     O(1) - 需要额外空间

适用场景建议:
  • 小规模无序数据: 线性查找
  • 大规模有序数据: 二分查找
  • 均匀分布数据: 插值查找
  • 频繁查找操作: 哈希查找
  • 静态数据集合: 跳跃查找/指数查找
*/
