/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::time::Instant;

/**
 * 归并排序 - 递归分割版本
 * 使用分治法：递归分割后再合并
 */
fn merge_sort1(values: Vec<i32>) -> Vec<i32> {
    if values.len() <= 1 {
        return values;
    }

    let mid = values.len() / 2;
    let left = merge_sort1(values[0..mid].to_vec());
    let right = merge_sort1(values[mid..].to_vec());

    merge(left, right)
}

/**
 * 合并两个已排序的数组
 */
fn merge(mut left: Vec<i32>, mut right: Vec<i32>) -> Vec<i32> {
    let mut result = Vec::new();

    while !left.is_empty() && !right.is_empty() {
        if left[0] <= right[0] {
            result.push(left.remove(0));
        } else {
            result.push(right.remove(0));
        }
    }

    // 添加剩余元素
    result.extend(left);
    result.extend(right);

    result
}

/**
 * 归并排序 - 原地版本
 * 直接修改原数组
 */
fn merge_sort2(arr: &mut [i32]) {
    if arr.len() <= 1 {
        return;
    }

    let mid = arr.len() / 2;
    merge_sort2(&mut arr[0..mid]);
    merge_sort2(&mut arr[mid..]);

    // 合并两个已排序的子数组
    let mut left = arr[0..mid].to_vec();
    let mut right = arr[mid..].to_vec();

    let mut i = 0;
    let mut j = 0;
    let mut k = 0;

    while i < left.len() && j < right.len() {
        if left[i] <= right[j] {
            arr[k] = left[i];
            i += 1;
        } else {
            arr[k] = right[j];
            j += 1;
        }
        k += 1;
    }

    // 复制左侧剩余元素
    while i < left.len() {
        arr[k] = left[i];
        i += 1;
        k += 1;
    }

    // 复制右侧剩余元素
    while j < right.len() {
        arr[k] = right[j];
        j += 1;
        k += 1;
    }
}

fn main() {
    println!("Merge Sort Test:\n");

    let data1 = vec![7, 11, 9, 10, 12, 13, 8];
    println!("Original array: {:?}", data1);

    let start = Instant::now();
    let sorted = merge_sort1(data1);
    println!("Sorted (merge_sort1): {:?}", sorted);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let mut data2 = vec![7, 11, 9, 10, 12, 13, 8];
    println!("Original array: {:?}", data2);

    let start = Instant::now();
    merge_sort2(&mut data2);
    println!("Sorted (merge_sort2): {:?}", data2);
    println!("Time: {:.6}ms", start.elapsed().as_secs_f64() * 1000.0);
}

/*
rustc -V
rustc 1.70.0 (90c541806 2023-04-27)

rustc merge_sort.rs && ./merge_sort
Merge Sort Test:

Original array: [7, 11, 9, 10, 12, 13, 8]
Sorted (merge_sort1): [7, 8, 9, 10, 11, 12, 13]
Time: 0.018000ms

Original array: [7, 11, 9, 10, 12, 13, 8]
Sorted (merge_sort2): [7, 8, 9, 10, 11, 12, 13]
Time: 0.014000ms
*/
