/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::time::Instant;

/**
 * 选择排序 - 标准版本
 * 每次找到最小元素放到前面
 */
fn selection_sort1(arr: &mut [i32]) {
    let len = arr.len();
    for i in 0..len - 1 {
        let mut min = arr[i];
        let mut min_idx = i;

        // 在未排序部分找最小元素
        for j in (i + 1)..len {
            if arr[j] < min {
                min = arr[j];
                min_idx = j;
            }
        }

        // 将最小元素交换到已排序部分末尾
        if min_idx != i {
            arr.swap(i, min_idx);
        }
    }
}

/**
 * 选择排序 - 新建数组版本
 * 避免交换操作
 */
fn selection_sort2(arr: Vec<i32>) -> Vec<i32> {
    let mut new_list = Vec::new();
    let mut remaining = arr;

    while !remaining.is_empty() {
        let mut min = remaining[0];
        let mut min_idx = 0;

        // 找到最小元素
        for (j, &item) in remaining.iter().enumerate() {
            if item < min {
                min = item;
                min_idx = j;
            }
        }

        // 添加到新数组
        new_list.push(min);
        // 从原数组删除
        remaining.remove(min_idx);
    }

    new_list
}

/**
 * 选择排序 - 双向选择版本
 * 同时找最小和最大元素
 */
fn selection_sort_bidirectional(arr: &mut [i32]) {
    let len = arr.len();
    let mut left = 0;
    let mut right = len - 1;

    while left < right {
        let mut min_idx = left;
        let mut max_idx = left;

        // 找最小和最大元素
        for i in (left + 1)..=right {
            if arr[i] < arr[min_idx] {
                min_idx = i;
            }
            if arr[i] > arr[max_idx] {
                max_idx = i;
            }
        }

        // 交换最小元素到左端
        if min_idx != left {
            arr.swap(left, min_idx);
            // 如果右端元素被交换，需要更新max_idx
            if max_idx == left {
                max_idx = min_idx;
            }
        }

        // 交换最大元素到右端
        if max_idx != right {
            arr.swap(right, max_idx);
        }

        left += 1;
        right -= 1;
    }
}

fn main() {
    println!("Selection Sort Test:\n");

    let mut data1 = vec![7, 11, -9, 10, -12, 13, 8];
    println!("Original array: {:?}", data1);

    let start = Instant::now();
    selection_sort1(&mut data1);
    println!("Sorted (selection_sort1): {:?}", data1);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let data2 = vec![7, 11, -9, 10, -12, 13, 8];
    println!("Original array: {:?}", data2);

    let start = Instant::now();
    let sorted = selection_sort2(data2);
    println!("Sorted (selection_sort2): {:?}", sorted);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let mut data3 = vec![7, 11, -9, 10, -12, 13, 8];
    println!("Original array: {:?}", data3);

    let start = Instant::now();
    selection_sort_bidirectional(&mut data3);
    println!("Sorted (selection_sort_bidirectional): {:?}", data3);
    println!("Time: {:.6}ms", start.elapsed().as_secs_f64() * 1000.0);
}

/*
rustc -V
rustc 1.70.0 (90c541806 2023-04-27)

rustc selection_sort.rs && ./selection_sort
Selection Sort Test:

Original array: [7, 11, -9, 10, -12, 13, 8]
Sorted (selection_sort1): [-12, -9, 7, 8, 10, 11, 13]
Time: 0.004000ms

Original array: [7, 11, -9, 10, -12, 13, 8]
Sorted (selection_sort2): [-12, -9, 7, 8, 10, 11, 13]
Time: 0.008000ms

Original array: [7, 11, -9, 10, -12, 13, 8]
Sorted (selection_sort_bidirectional): [-12, -9, 7, 8, 10, 11, 13]
Time: 0.003000ms
*/
