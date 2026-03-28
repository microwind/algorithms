/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::time::Instant;

/**
 * 快速排序 - 递归新建数组版本
 * 无需交换，每个分区都是新数组
 */
fn quick_sort1(arr: Vec<i32>) -> Vec<i32> {
    if arr.len() <= 1 {
        return arr;
    }

    let mid_index = arr.len() / 2;
    let pivot = arr[mid_index];
    let mut left = Vec::new();
    let mut right = Vec::new();

    for (i, &item) in arr.iter().enumerate() {
        if i == mid_index {
            continue;
        }
        if item < pivot {
            left.push(item);
        } else {
            right.push(item);
        }
    }

    let mut result = quick_sort1(left);
    result.push(pivot);
    result.extend(quick_sort1(right));
    result
}

/**
 * 快速排序 - 标准递归版本
 * 原地分区交换
 */
fn quick_sort2(arr: &mut [i32], left: usize, right: usize) {
    if left >= right {
        return;
    }

    let mut i = left;
    let mut j = right as i32;
    let mid_index = (left + right) / 2;
    let pivot = arr[mid_index];

    while (i as i32) <= j {
        while arr[i] < pivot {
            i += 1;
        }
        while arr[j as usize] > pivot {
            j -= 1;
        }

        if (i as i32) <= j {
            arr.swap(i, j as usize);
            i += 1;
            j -= 1;
        }
    }

    if left < j as usize {
        quick_sort2(arr, left, j as usize);
    }
    if (i) < right {
        quick_sort2(arr, i, right);
    }
}

/**
 * 快速排序 - 分区函数
 * 选择右侧元素为基准，将小于基准的移到左侧
 */
fn partition(arr: &mut [i32], left: usize, right: usize) -> usize {
    let pivot = arr[right];
    let mut partition_index = left as i32 - 1;

    for i in left..right {
        if arr[i] < pivot {
            partition_index += 1;
            arr.swap(i, partition_index as usize);
        }
    }

    partition_index += 1;
    arr.swap(right, partition_index as usize);
    partition_index as usize
}

/**
 * 快速排序 - 分区交换版本
 */
fn quick_sort3(arr: &mut [i32], left: usize, right: usize) {
    if left < right {
        let pivot = partition(arr, left, right);
        if pivot > 0 {
            quick_sort3(arr, left, pivot - 1);
        }
        quick_sort3(arr, pivot + 1, right);
    }
}

fn main() {
    println!("Quick Sort Test:\n");

    let data1 = vec![7, 11, 9, 10, 12, 13, 8];
    println!("Original array: {:?}", data1);

    let start = Instant::now();
    let sorted = quick_sort1(data1);
    println!("Sorted (quick_sort1): {:?}", sorted);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let mut data2 = vec![7, 11, 9, 10, 12, 13, 8];
    println!("Original array: {:?}", data2);

    let start = Instant::now();
    quick_sort2(&mut data2, 0, data2.len() - 1);
    println!("Sorted (quick_sort2): {:?}", data2);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let mut data3 = vec![7, 11, 9, 10, 12, 13, 8];
    println!("Original array: {:?}", data3);

    let start = Instant::now();
    quick_sort3(&mut data3, 0, data3.len() - 1);
    println!("Sorted (quick_sort3): {:?}", data3);
    println!("Time: {:.6}ms", start.elapsed().as_secs_f64() * 1000.0);
}

/*
rustc -V
rustc 1.70.0 (90c541806 2023-04-27)

rustc quick_sort.rs && ./quick_sort
Quick Sort Test:

Original array: [7, 11, 9, 10, 12, 13, 8]
Sorted (quick_sort1): [7, 8, 9, 10, 11, 12, 13]
Time: 0.025000ms

Original array: [7, 11, 9, 10, 12, 13, 8]
Sorted (quick_sort2): [7, 8, 9, 10, 11, 12, 13]
Time: 0.008000ms

Original array: [7, 11, 9, 10, 12, 13, 8]
Sorted (quick_sort3): [7, 8, 9, 10, 11, 12, 13]
Time: 0.003000ms
*/
