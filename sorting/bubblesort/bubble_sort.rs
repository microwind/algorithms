/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::time::Instant;

/**
 * 冒泡排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

fn bubble_sort1(arr: &mut [i32]) {
    println!("bubbleSort1 from left to right:");
    let len = arr.len();
    // 外循环：控制排序轮数，每轮确定一个最大值的位置
    for i in 0..len {
        // 内循环：控制比较次数，len-i-1 避免重复比较已排序部分
        for j in 0..len - i - 1 {
            // 关键点：自左往右每两个进行比较，把大的交换到右侧
            if arr[j] > arr[j + 1] {
                // Rust特点：使用swap方法交换
                arr.swap(j, j + 1);
            }
        }
    }
    print_array(arr, "基础升序版本排序结果");
}

fn bubble_sort2(arr: &mut [i32]) {
    println!("bubbleSort2 from right to left:");
    let len = arr.len();
    // 外循环：控制排序轮数，每轮确定一个最小值的位置
    for i in 0..len {
        // 内循环：从右向左比较，j > i 避免重复比较已排序部分
        for j in (i + 1..len).rev() {
            // 关键点：自右往左每两个进行比较，把小的交换到右侧
            if arr[j - 1] < arr[j] {
                // Rust特点：使用swap方法交换
                arr.swap(j - 1, j);
            }
        }
    }
    print_array(arr, "基础降序版本排序结果");
}

fn bubble_sort3(arr: &mut [i32]) {
    println!("bubbleSort3 add flag:");
    // 优化点：增加一个标志，如果某一轮没有进行过任何的交换
    // 则说明当前数组已排好序，则不必继续后面的遍历
    let len = arr.len();
    let mut flag = true;

    // 外循环：增加 flag 条件，当数组已有序时提前终止
    for i in 0..len {
        if !flag {
            break;
        }
        flag = false; // 每轮开始时重置标志
        // 内循环：控制比较次数，len-i-1 避免重复比较已排序部分
        for j in 0..len - i - 1 {
            // 关键点：自左往右每两个进行比较，把大的交换到右侧
            if arr[j] > arr[j + 1] {
                flag = true; // 发生交换，设置标志
                // Rust特点：使用swap方法交换
                arr.swap(j, j + 1);
            }
        }
    }
    print_array(arr, "优化版本排序结果");
}

fn bubble_sort4(arr: &mut [i32]) {
    println!("bubbleSort4:");
    let len = arr.len();
    // 外循环：控制排序轮数，i 从 1 开始，因为第 0 个元素默认为已排序
    for i in 1..len {
        // 内循环：在已排序区域中查找插入位置
        for j in 0..i {
            // 关键点：如果待插入元素小于已排序区域的某个元素，则交换
            if arr[j] > arr[i] {
                // Rust特点：使用swap方法交换
                arr.swap(j, i);
            }
        }
    }
    print_array(arr, "插入式版本排序结果");
}

fn print_array(arr: &[i32], label: &str) {
    print!("{}: [", label);
    for (i, &val) in arr.iter().enumerate() {
        if i > 0 {
            print!(", ");
        }
        print!("{}", val);
    }
    println!("]");
}

fn performance_test<F>(sort_func: F, arr: &[i32], name: &str) 
where 
    F: FnOnce(&mut [i32]),
{
    // 创建数组副本，避免修改原数组
    let mut test_arr = arr.to_vec();
    print_array(&test_arr, name);
    
    // 开始计时
    let start = Instant::now();
    sort_func(&mut test_arr);
    let duration = start.elapsed();
    
    print_array(&test_arr, &format!("{}排序结果", name));
    println!("{}: {:.3}ms", name, duration.as_millis());
    println!(); // 空行分隔
}

fn main() {
    // 测试数据：包含重复元素和无序情况的典型数组
    let test_data = [7, 11, 9, 10, 12, 13, 8];
    
    println!("=== 冒泡排序算法演示 ===\n");
    
    // 测试1：基础升序版本
    performance_test(bubble_sort1, &test_data, "基础升序版本");
    
    // 测试2：基础降序版本
    performance_test(bubble_sort2, &test_data, "基础降序版本");
    
    // 测试3：优化版本
    performance_test(bubble_sort3, &test_data, "优化版本");
    
    // 测试4：插入式版本
    performance_test(bubble_sort4, &test_data, "插入式版本");
    
    println!("=== 算法对比总结 ===");
    println!("1. 基础版本：简单易懂，适合学习算法原理");
    println!("2. 降序版本：展示算法的灵活性，可按需排序");
    println!("3. 优化版本：通过标志位优化，适合实际应用");
    println!("4. 插入式版本：结合其他排序思想，性能更稳定");
}

/* 打印结果
jarry@Mac bubblesort % rustc bubble_sort.rs && ./bubble_sort
=== 冒泡排序算法演示 ===

基础升序版本: [7, 11, 9, 10, 12, 13, 8]
bubbleSort1 from left to right:
基础升序版本排序结果: [7, 8, 9, 10, 11, 12, 13]
基础升序版本排序结果: [7, 8, 9, 10, 11, 12, 13]
基础升序版本: 0ms

基础降序版本: [7, 11, 9, 10, 12, 13, 8]
bubbleSort2 from right to left:
基础降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]
基础降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]
基础降序版本: 0ms

优化版本: [7, 11, 9, 10, 12, 13, 8]
bubbleSort3 add flag:
优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]
优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]
优化版本: 0ms

插入式版本: [7, 11, 9, 10, 12, 13, 8]
bubbleSort4:
插入式版本排序结果: [7, 8, 9, 10, 11, 12, 13]
插入式版本排序结果: [7, 8, 9, 10, 11, 12, 13]
插入式版本: 0ms

=== 算法对比总结 ===
1. 基础版本：简单易懂，适合学习算法原理
2. 降序版本：展示算法的灵活性，可按需排序
3. 优化版本：通过标志位优化，适合实际应用
4. 插入式版本：结合其他排序思想，性能更稳定
*/
