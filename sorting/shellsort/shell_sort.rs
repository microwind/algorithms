/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::time::Instant;

/**
 * 希尔排序 - 标准版本
 * 基于插入排序进行分组排序，步长按1/2缩减
 */
fn shell_sort1(arr: &mut [i32]) {
    let size = arr.len();
    let mut gap = size / 2;

    // 按步长递减排序
    while gap > 0 {
        for i in gap..size {
            let current = arr[i];
            let mut j = i;

            // 对每个子序列进行插入排序
            while j >= gap && current < arr[j - gap] {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            // 插入当前元素
            arr[j] = current;
        }

        // 步长减半
        gap = gap / 2;
    }
}

/**
 * 希尔排序 - 优化版本
 * 使用3x+1步长序列
 */
fn shell_sort2(arr: &mut [i32]) {
    let size = arr.len();
    let mut gap = 1;

    // 计算初始步长：3x+1序列
    while gap < (size / 3) {
        gap = gap * 3 + 1;
    }

    // 按步长递减排序
    while gap > 0 {
        for i in gap..size {
            let current = arr[i];
            let mut j = i as i32 - gap as i32;

            // 对每个子序列进行插入排序
            while j >= 0 && arr[j as usize] > current {
                arr[(j + gap as i32) as usize] = arr[j as usize];
                j -= gap as i32;
            }

            // 插入当前元素
            arr[(j + gap as i32) as usize] = current;
        }

        // 步长按3倍缩减
        gap = gap / 3;
    }
}

/**
 * 希尔排序 - Knuth序列版本
 * 使用Knuth序列：1, 4, 13, 40, 121, ...
 */
fn shell_sort_knuth(arr: &mut [i32]) {
    let size = arr.len();

    // 计算Knuth序列的最大步长
    let mut gap = 1;
    while gap <= size / 3 {
        gap = gap * 3 + 1;
    }

    // 按步长递减排序
    while gap > 0 {
        for i in gap..size {
            let current = arr[i];
            let mut j = i as i32 - gap as i32;

            // 对每个子序列进行插入排序
            while j >= 0 && arr[j as usize] > current {
                arr[(j + gap as i32) as usize] = arr[j as usize];
                j -= gap as i32;
            }

            // 插入当前元素
            arr[(j + gap as i32) as usize] = current;
        }

        // 步长按3倍缩减
        gap = gap / 3;
    }
}

fn main() {
    println!("Shell Sort Test:\n");

    let mut data1 = vec![33, 4, 15, 43, 323, -7, 10, 125, 200, 87];
    println!("Original array: {:?}", data1);

    let start = Instant::now();
    shell_sort1(&mut data1);
    println!("Sorted (shell_sort1): {:?}", data1);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let mut data2 = vec![33, 4, 15, 43, 323, -7, 10, 125, 200, 87];
    println!("Original array: {:?}", data2);

    let start = Instant::now();
    shell_sort2(&mut data2);
    println!("Sorted (shell_sort2): {:?}", data2);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let mut data3 = vec![33, 4, 15, 43, 323, -7, 10, 125, 200, 87];
    println!("Original array: {:?}", data3);

    let start = Instant::now();
    shell_sort_knuth(&mut data3);
    println!("Sorted (shell_sort_knuth): {:?}", data3);
    println!("Time: {:.6}ms", start.elapsed().as_secs_f64() * 1000.0);
}

/*
rustc -V
rustc 1.70.0 (90c541806 2023-04-27)

rustc shell_sort.rs && ./shell_sort
Shell Sort Test:

Original array: [33, 4, 15, 43, 323, -7, 10, 125, 200, 87]
Sorted (shell_sort1): [-7, 4, 10, 15, 33, 43, 87, 125, 200, 323]
Time: 0.004000ms

Original array: [33, 4, 15, 43, 323, -7, 10, 125, 200, 87]
Sorted (shell_sort2): [-7, 4, 10, 15, 33, 43, 87, 125, 200, 323]
Time: 0.003000ms

Original array: [33, 4, 15, 43, 323, -7, 10, 125, 200, 87]
Sorted (shell_sort_knuth): [-7, 4, 10, 15, 33, 43, 87, 125, 200, 323]
Time: 0.002000ms
*/
