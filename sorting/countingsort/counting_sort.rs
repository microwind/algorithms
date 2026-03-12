/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::time::Instant;

/**
 * 计数排序 - 简化版本
 * 统计每个数值出现的次数，然后按顺序回填
 */
fn counting_sort1(arr: &mut [i32]) -> &mut [i32] {
    if arr.is_empty() {
        return arr;
    }

    let min_value = *arr.iter().min().unwrap();
    let max_value = *arr.iter().max().unwrap();
    let range = (max_value - min_value + 1) as usize;

    // 创建计数数组
    let mut count_list = vec![0; range];

    // 统计每个元素出现的次数
    for &item in arr.iter() {
        let idx = (item - min_value) as usize;
        count_list[idx] += 1;
    }

    // 根据计数重建排序数组
    let mut idx = 0;
    for (i, &count) in count_list.iter().enumerate() {
        for _ in 0..count {
            arr[idx] = i as i32 + min_value;
            idx += 1;
        }
    }

    arr
}

/**
 * 计数排序 - 标准版本，保持稳定性
 * 通过累积计数确定每个元素的最终位置
 */
fn counting_sort2(arr: &mut [i32]) -> Vec<i32> {
    if arr.is_empty() {
        return arr.to_vec();
    }

    let min_value = *arr.iter().min().unwrap();
    let max_value = *arr.iter().max().unwrap();
    let range = (max_value - min_value + 1) as usize;

    // 创建计数数组
    let mut count_list = vec![0; range];

    // 统计每个元素出现的次数
    for &item in arr.iter() {
        let idx = (item - min_value) as usize;
        count_list[idx] += 1;
    }

    // 计算累积计数
    for i in 1..range {
        count_list[i] += count_list[i - 1];
    }

    // 构建输出数组，保持稳定性
    let mut output = vec![0; arr.len()];
    for &item in arr.iter().rev() {
        let idx = (item - min_value) as usize;
        output[count_list[idx] - 1] = item;
        count_list[idx] -= 1;
    }

    output
}

/**
 * 计数排序 - 直接修改数组版本
 */
fn counting_sort3(arr: &mut [i32]) {
    if arr.is_empty() {
        return;
    }

    let min_value = *arr.iter().min().unwrap();
    let max_value = *arr.iter().max().unwrap();
    let range = (max_value - min_value + 1) as usize;

    let mut count_list = vec![0; range];

    // 统计每个元素出现的次数
    for &item in arr.iter() {
        let idx = (item - min_value) as usize;
        count_list[idx] += 1;
    }

    // 根据计数重建排序数组
    let mut idx = 0;
    for (i, &count) in count_list.iter().enumerate() {
        for _ in 0..count {
            arr[idx] = i as i32 + min_value;
            idx += 1;
        }
    }
}

fn main() {
    println!("Counting Sort Test:");

    let mut data1 = vec![3, 4, 15, 3, 3, 7, 10, -2, 1];
    let mut data1_clone = data1.clone();
    println!("Original array: {:?}", data1);

    let start = Instant::now();
    counting_sort1(&mut data1);
    println!("Sorted (counting_sort1): {:?}", data1);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let mut data2 = vec![3, 4, 15, 3, 3, 7, 10, -2, 1];
    println!("Original array: {:?}", data2);

    let start = Instant::now();
    let sorted = counting_sort2(&mut data2);
    println!("Sorted (counting_sort2): {:?}", sorted);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let mut data3 = vec![3, 4, 15, 3, 3, 7, 10, -2, 1];
    println!("Original array: {:?}", data3);

    let start = Instant::now();
    counting_sort3(&mut data3);
    println!("Sorted (counting_sort3): {:?}", data3);
    println!("Time: {:.6}ms", start.elapsed().as_secs_f64() * 1000.0);
}

/*
rustc -V
rustc 1.70.0 (90c541806 2023-04-27)

rustc counting_sort.rs && ./counting_sort
Counting Sort Test:
Original array: [3, 4, 15, 3, 3, 7, 10, -2, 1]
Sorted (counting_sort1): [-2, 1, 3, 3, 3, 4, 7, 10, 15]
Time: 0.010000ms

Original array: [3, 4, 15, 3, 3, 7, 10, -2, 1]
Sorted (counting_sort2): [-2, 1, 3, 3, 3, 4, 7, 10, 15]
Time: 0.005000ms

Original array: [3, 4, 15, 3, 3, 7, 10, -2, 1]
Sorted (counting_sort3): [-2, 1, 3, 3, 3, 4, 7, 10, 15]
Time: 0.003000ms
*/
