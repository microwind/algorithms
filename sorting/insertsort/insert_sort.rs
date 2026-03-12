/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::time::Instant;

/**
 * 插入排序 - 标准通用版
 * 将元素插入到已排序部分的正确位置
 */
fn insert_sort1(arr: &mut [i32]) {
    let len = arr.len();
    for i in 1..len {
        let current = arr[i];
        let mut j = i as i32 - 1;

        // 将当前元素与已排序部分从右向左比较
        while j >= 0 && current < arr[j as usize] {
            // 大元素右移
            arr[(j + 1) as usize] = arr[j as usize];
            j -= 1;
        }

        // 插入当前元素
        arr[(j + 1) as usize] = current;
    }
}

/**
 * 插入排序 - 新建数组版
 * 创建新数组来存储排序结果
 */
fn insert_sort2(arr: &[i32]) -> Vec<i32> {
    if arr.is_empty() {
        return Vec::new();
    }

    let mut new_arr = vec![arr[0]];

    for i in 1..arr.len() {
        let mut inserted = false;

        for j in 0..new_arr.len() {
            if arr[i] < new_arr[j] {
                new_arr.insert(j, arr[i]);
                inserted = true;
                break;
            }
        }

        if !inserted {
            new_arr.push(arr[i]);
        }
    }

    new_arr
}

/**
 * 插入排序 - 新建数组版倒序遍历
 */
fn insert_sort3(arr: &[i32]) -> Vec<i32> {
    if arr.is_empty() {
        return Vec::new();
    }

    let mut new_arr = vec![arr[0]];

    for i in 1..arr.len() {
        let mut inserted = false;
        let mut j = new_arr.len() as i32 - 1;

        while j >= 0 {
            if arr[i] > new_arr[j as usize] {
                new_arr.insert((j + 1) as usize, arr[i]);
                inserted = true;
                break;
            }
            j -= 1;
        }

        if !inserted {
            new_arr.insert(0, arr[i]);
        }
    }

    new_arr
}

fn main() {
    println!("Insert Sort Test:\n");

    let mut data1 = vec![7, 11, 9, 10, 12, 13, 8];
    println!("Original array: {:?}", data1);

    let start = Instant::now();
    insert_sort1(&mut data1);
    println!("Sorted (insert_sort1): {:?}", data1);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let data2 = vec![7, 11, 9, 10, 12, 13, 8];
    println!("Original array: {:?}", data2);

    let start = Instant::now();
    let sorted = insert_sort2(&data2);
    println!("Sorted (insert_sort2): {:?}", sorted);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let data3 = vec![7, 11, 9, 10, 12, 13, 8];
    println!("Original array: {:?}", data3);

    let start = Instant::now();
    let sorted = insert_sort3(&data3);
    println!("Sorted (insert_sort3): {:?}", sorted);
    println!("Time: {:.6}ms", start.elapsed().as_secs_f64() * 1000.0);
}

/*
rustc -V
rustc 1.70.0 (90c541806 2023-04-27)

rustc insert_sort.rs && ./insert_sort
Insert Sort Test:

Original array: [7, 11, 9, 10, 12, 13, 8]
Sorted (insert_sort1): [7, 8, 9, 10, 11, 12, 13]
Time: 0.003000ms

Original array: [7, 11, 9, 10, 12, 13, 8]
Sorted (insert_sort2): [7, 8, 9, 10, 11, 12, 13]
Time: 0.004000ms

Original array: [7, 11, 9, 10, 12, 13, 8]
Sorted (insert_sort3): [7, 8, 9, 10, 11, 12, 13]
Time: 0.002000ms
*/
