/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::time::Instant;

/**
 * 基数排序 - 计数排序辅助函数
 * 按指定位数进行计数排序
 */
fn counting_sort(arr: &mut [i32], exponent: i32) {
    let amount = 10; // 0-9的数字
    let arr_len = arr.len();
    let min_value = *arr.iter().min().unwrap();

    let mut count_list = vec![0; amount as usize];
    let mut sorted_list = vec![0; arr_len];

    // 统计当前位数的计数
    for i in 0..arr_len {
        let index = ((arr[i] - min_value) / exponent % amount) as usize;
        count_list[index] += 1;
    }

    // 计算累积计数
    for i in 1..amount as usize {
        count_list[i] += count_list[i - 1];
    }

    // 构建输出数组
    let mut i = arr_len as i32 - 1;
    while i >= 0 {
        let index = ((arr[i as usize] - min_value) / exponent % amount) as usize;
        sorted_list[count_list[index] - 1] = arr[i as usize];
        count_list[index] -= 1;
        i -= 1;
    }

    // 复制回原数组
    for i in 0..arr_len {
        arr[i] = sorted_list[i];
    }
}

/**
 * 基数排序 - LSD版本
 * 从低位到高位逐位排序
 */
fn radix_sort(arr: &mut [i32]) {
    if arr.is_empty() {
        return;
    }

    let max_value = *arr.iter().max().unwrap();
    let min_value = *arr.iter().min().unwrap();
    let mut exponent = 1;
    let max_number = max_value - min_value;

    // 按位数循环处理
    while max_number / exponent > 0 {
        counting_sort(arr, exponent);
        exponent *= 10;
    }
}

/**
 * 基数排序 - 支持负数的版本
 */
fn radix_sort_with_negative(arr: &mut [i32]) {
    if arr.is_empty() {
        return;
    }

    // 分离负数和正数
    let mut negatives = Vec::new();
    let mut positives = Vec::new();

    for &item in arr.iter() {
        if item < 0 {
            negatives.push(-item);
        } else {
            positives.push(item);
        }
    }

    // 分别排序
    if !negatives.is_empty() {
        radix_sort(&mut negatives);
        negatives.reverse();
        for i in 0..negatives.len() {
            negatives[i] = -negatives[i];
        }
    }

    if !positives.is_empty() {
        radix_sort(&mut positives);
    }

    // 合并
    let mut idx = 0;
    for &item in negatives.iter() {
        arr[idx] = item;
        idx += 1;
    }
    for &item in positives.iter() {
        arr[idx] = item;
        idx += 1;
    }
}

fn main() {
    println!("Radix Sort Test:\n");

    let mut data1 = vec![33, 4, 15, 43, 323, 7, 10, 125, 200, 87];
    println!("Original array: {:?}", data1);

    let start = Instant::now();
    radix_sort(&mut data1);
    println!("Sorted: {:?}", data1);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let mut data2 = vec![33, -4, 15, 43, -323, 7, 10, 125, 200, 87];
    println!("Original array (with negative): {:?}", data2);

    let start = Instant::now();
    radix_sort_with_negative(&mut data2);
    println!("Sorted: {:?}", data2);
    println!("Time: {:.6}ms", start.elapsed().as_secs_f64() * 1000.0);
}

/*
rustc -V
rustc 1.70.0 (90c541806 2023-04-27)

rustc radix_sort.rs && ./radix_sort
Radix Sort Test:

Original array: [33, 4, 15, 43, 323, 7, 10, 125, 200, 87]
Sorted: [4, 7, 10, 15, 33, 43, 87, 125, 200, 323]
Time: 0.015000ms

Original array (with negative): [33, -4, 15, 43, -323, 7, 10, 125, 200, 87]
Sorted: [-323, -4, 7, 10, 15, 33, 43, 87, 125, 200]
Time: 0.008000ms
*/
