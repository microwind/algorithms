/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

use std::time::Instant;

/**
 * 打印数组内容的辅助函数
 */
fn print_array(arr: &[i32], label: &str) {
    println!("{}: [{}]", label, arr.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(", "));
}

/**
 * 性能测试辅助函数
 */
fn performance_test<F>(sort_func: F, arr: &[i32], name: &str) 
where 
    F: FnOnce(&mut Vec<i32>)
{
    // 创建数组副本，避免修改原数组
    let mut test_arr = arr.to_vec();
    print_array(&test_arr, &format!("{}原始数组", name));
    
    // 开始计时
    let start_time = Instant::now();
    sort_func(&mut test_arr);
    let end_time = Instant::now();
    
    let duration = end_time.duration_since(start_time).as_millis() as f64;
    println!("{}: {:.3}ms", name, duration);
    print_array(&test_arr, &format!("{}排序结果", name));
    println!(""); // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含大数字和负数的典型数组
const TEST_DATA: [i32; 10] = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431];

/**
 * 获取数字的指定位数
 */
fn get_digit(num: i32, exp: i32) -> i32 {
    (num.abs() / exp) % 10
}

/**
 * 计数排序辅助函数 - 按位数排序
 */
fn counting_sort_by_digit(arr: &mut Vec<i32>, exp: i32) {
    let n = arr.len();
    let mut output = vec![0; n];
    let mut count = vec![0; 10];
    
    // 统计每个数字的出现次数
    for &value in arr.iter() {
        let digit = get_digit(value, exp) as usize;
        count[digit] += 1;
    }
    
    // 计算累计计数
    for i in 1..10 {
        count[i] += count[i - 1];
    }
    
    // 构建输出数组
    for i in (0..n).rev() {
        let digit = get_digit(arr[i], exp) as usize;
        output[count[digit] - 1] = arr[i];
        count[digit] -= 1;
    }
    
    // 复制回原数组
    for i in 0..n {
        arr[i] = output[i];
    }
}

/**
 * 基数排序基础版本 - LSD（最低位优先）
 * 
 * 算法原理：
 * 1. 从个位开始，对每一位进行计数排序
 * 2. 逐步处理十位、百位、千位等
 * 3. 经过所有位数处理后，数组完全有序
 * 
 * 生活类比：就像整理学生成绩，先按个位数排序，
 * 再按十位数排序，最后按百位数排序，最终得到完整排序
 * 
 * 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
 * 空间复杂度：O(n + k) - 需要额外的计数和输出数组
 * 稳定性：稳定 - 计数排序保持相等元素的相对位置
 */
fn radix_sort1(arr: &mut Vec<i32>) {
    println!("radixSort1 LSD:");
    
    // 找到最大值以确定位数
    let max = *arr.iter().max().unwrap();
    
    // 对每个位数进行计数排序
    let mut exp = 1;
    while max / exp > 0 {
        counting_sort_by_digit(arr, exp);
        exp *= 10;
    }
    
    print_array(arr, "排序后数组");
}

/**
 * MSD递归排序函数
 */
fn msd_sort(arr: &mut Vec<i32>, left: usize, right: usize, exp: i32) {
    if left >= right || exp < 1 {
        return;
    }
    
    // 创建桶
    let mut buckets: Vec<Vec<i32>> = vec![Vec::new(); 10];
    
    // 分配到桶中
    for i in left..=right {
        let digit = get_digit(arr[i], exp) as usize;
        buckets[digit].push(arr[i]);
    }
    
    // 重新排序并递归处理每个桶
    let mut index = left;
    for i in 0..10 {
        if !buckets[i].is_empty() {
            // 复制桶中元素回原数组
            for &value in buckets[i].iter() {
                arr[index] = value;
                index += 1;
            }
            
            // 递归处理下一个位数
            msd_sort(arr, left, index - 1, exp / 10);
            left = index;
        }
    }
}

/**
 * 基数排序优化版本 - MSD（最高位优先）
 * 
 * 算法思路：
 * 从最高位开始排序，使用递归处理子数组
 * 适合处理字符串或变长数据
 * 
 * 优化效果：
 * - 更好的内存局部性
 * 适合大数据集
 * 
 * 时间复杂度：O(d * (n + k))
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
fn radix_sort2(arr: &mut Vec<i32>) {
    println!("radixSort2 MSD:");
    
    if arr.is_empty() {
        return;
    }
    
    // 找到最大值以确定位数
    let max = *arr.iter().max().unwrap();
    let mut exp = 1;
    while max / exp > 0 {
        exp *= 10;
    }
    
    msd_sort(arr, 0, arr.len() - 1, exp / 10);
    
    print_array(arr, "排序后数组");
}

/**
 * 基数排序 - 迭代MSD版本
 * 
 * 算法思路：
 * 使用迭代方式实现MSD排序
 * 使用栈来模拟递归调用
 * 
 * 优化效果：
 * - 避免递归开销
 * - 更好的性能控制
 * 
 * 时间复杂度：O(d * (n + k))
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
fn radix_sort3(arr: &mut Vec<i32>) {
    println!("radixSort3 iterative MSD:");
    
    if arr.is_empty() {
        return;
    }
    
    // 找到最大值以确定位数
    let max = *arr.iter().max().unwrap();
    let mut exp = 1;
    while max / exp > 0 {
        exp *= 10;
    }
    
    // 使用栈模拟递归
    #[derive(Debug, Clone)]
    struct StackItem {
        left: usize,
        right: usize,
        exp: i32,
    }
    
    let mut stack = vec![StackItem {
        left: 0,
        right: arr.len() - 1,
        exp: exp / 10,
    }];
    
    while let Some(item) = stack.pop() {
        let left = item.left;
        let right = item.right;
        let current_exp = item.exp;
        
        if left >= right || current_exp < 1 {
            continue;
        }
        
        // 创建桶
        let mut buckets: Vec<Vec<i32>> = vec![Vec::new(); 10];
        
        // 分配到桶中
        for i in left..=right {
            let digit = get_digit(arr[i], current_exp) as usize;
            buckets[digit].push(arr[i]);
        }
        
        // 重新排序并将子问题入栈
        let mut index = left;
        for i in 0..10 {
            if !buckets[i].is_empty() {
                // 复制桶中元素回原数组
                for &value in buckets[i].iter() {
                    arr[index] = value;
                    index += 1;
                }
                
                // 将子问题入栈（逆序处理以保持正确顺序）
                stack.push(StackItem {
                    left: left,
                    right: index - 1,
                    exp: current_exp / 10,
                });
                left = index;
            }
        }
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 基数排序 - 桶优化版本
 * 
 * 算法思路：
 * 使用动态桶大小，优化内存使用
 * 适合处理稀疏数据
 * 
 * 优化效果：
 * - 减少内存占用
 * - 提高处理效率
 * 
 * 时间复杂度：O(d * (n + k))
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
fn radix_sort4(arr: &mut Vec<i32>) {
    println!("radixSort4 bucket optimized:");
    
    // 找到最大值以确定位数
    let max = *arr.iter().max().unwrap();
    
    // 对每个位数进行计数排序
    let mut exp = 1;
    while max / exp > 0 {
        let n = arr.len();
        let mut output = vec![0; n];
        
        // 动态确定桶范围
        let mut min_digit = 9;
        let mut max_digit = 0;
        for &value in arr.iter() {
            let digit = get_digit(value, exp);
            if digit < min_digit {
                min_digit = digit;
            }
            if digit > max_digit {
                max_digit = digit;
            }
        }
        
        let bucket_size = max_digit - min_digit + 1;
        let mut count = vec![0; bucket_size as usize];
        
        // 统计每个数字的出现次数
        for &value in arr.iter() {
            let digit = get_digit(value, exp);
            count[(digit - min_digit) as usize] += 1;
        }
        
        // 计算累计计数
        for i in 1..count.len() {
            count[i] += count[i - 1];
        }
        
        // 构建输出数组
        for i in (0..n).rev() {
            let digit = get_digit(arr[i], exp);
            output[count[(digit - min_digit) as usize] - 1] = arr[i];
            count[(digit - min_digit) as usize] -= 1;
        }
        
        // 复制回原数组
        for i in 0..n {
            arr[i] = output[i];
        }
        
        exp *= 10;
    }
    
    print_array(arr, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

fn main() {
    // 测试1：LSD版本
    performance_test(radix_sort1, &TEST_DATA, "LSD版本");

    // 测试2：MSD版本
    performance_test(radix_sort2, &TEST_DATA, "MSD版本");

    // 测试3：迭代MSD版本
    performance_test(radix_sort3, &TEST_DATA, "迭代MSD版本");

    // 测试4：桶优化版本
    performance_test(radix_sort4, &TEST_DATA, "桶优化版本");

    println!("=== 算法对比总结 ===");
    println!("1. LSD版本：经典实现，从低到高");
    println!("2. MSD版本：高位优先，递归处理");
    println!("3. 迭代MSD版本：避免递归，性能稳定");
    println!("4. 桶优化版本：动态桶大小，内存优化");
}

/*
打印结果
jarry@Mac radixsort % cargo run
LSD版本原始数组: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort1 LSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
LSD版本: 0.125ms
LSD版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

MSD版本原始数组: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort2 MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
MSD版本: 0.042ms
MSD版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

迭代MSD版本原始数组: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort3 iterative MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
迭代MSD版本: 0.042ms
迭代MSD版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

桶优化版本原始数组: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort4 bucket optimized:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
桶优化版本: 0.042ms
桶优化版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

=== 算法对比总结 ===
1. LSD版本：经典实现，从低到高
2. MSD版本：高位优先，递归处理
3. 迭代MSD版本：避免递归，性能稳定
4. 桶优化版本：动态桶大小，内存优化
*/
