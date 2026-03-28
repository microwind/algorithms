/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::time::Instant;

/**
 * 桶排序 - 简化版本
 * 将数据分配到有限数量的桶中，然后对每个桶中的数据进行排序
 */
fn bucket_sort(arr: &mut [i32]) -> &mut [i32] {
    if arr.is_empty() {
        return arr;
    }

    let max_val = *arr.iter().max().unwrap();
    let min_val = *arr.iter().min().unwrap();
    let range = (max_val - min_val) as usize + 1;

    // 创建桶
    let mut buckets: Vec<Vec<i32>> = vec![Vec::new(); range];

    // 将元素放入对应的桶中
    for &item in arr.iter() {
        let idx = (item - min_val) as usize;
        buckets[idx].push(item);
    }

    // 对每个桶进行排序，并回填原数组
    let mut idx = 0;
    for bucket in buckets.iter_mut() {
        bucket.sort();
        for &item in bucket.iter() {
            arr[idx] = item;
            idx += 1;
        }
    }

    arr
}

/**
 * 桶排序 - 带分桶数量控制
 */
fn bucket_sort_with_bucket_count(arr: &mut [i32], bucket_count: usize) -> &mut [i32] {
    if arr.is_empty() || bucket_count == 0 {
        return arr;
    }

    let max_val = *arr.iter().max().unwrap();
    let min_val = *arr.iter().min().unwrap();
    let range = (max_val - min_val) as f64;
    let bucket_size = (range / bucket_count as f64).ceil() as i32 + 1;

    // 创建指定数量的桶
    let mut buckets: Vec<Vec<i32>> = vec![Vec::new(); bucket_count];

    // 将元素放入对应的桶中
    for &item in arr.iter() {
        let mut idx = ((item - min_val) / bucket_size) as usize;
        idx = idx.min(bucket_count - 1);
        buckets[idx].push(item);
    }

    // 对每个桶进行排序，并回填原数组
    let mut idx = 0;
    for bucket in buckets.iter_mut() {
        bucket.sort();
        for &item in bucket.iter() {
            arr[idx] = item;
            idx += 1;
        }
    }

    arr
}

fn main() {
    println!("Bucket Sort Test:");

    let mut data1 = vec![20, 11, 9, 5, 30, 30, 15, 13, 80, 30];
    println!("Original array: {:?}", data1);

    let start = Instant::now();
    bucket_sort(&mut data1);
    println!("Sorted: {:?}", data1);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let mut data2 = vec![20, 11, 9, 5, 30, 30, 15, 13, 80, 30];
    println!("Original array: {:?}", data2);

    let start = Instant::now();
    bucket_sort_with_bucket_count(&mut data2, 5);
    println!("Sorted with 5 buckets: {:?}", data2);
    println!("Time: {:.6}ms", start.elapsed().as_secs_f64() * 1000.0);
}

/*
rustc -V
rustc 1.70.0 (90c541806 2023-04-27)

rustc bucket_sort.rs && ./bucket_sort
Bucket Sort Test:
Original array: [20, 11, 9, 5, 30, 30, 15, 13, 80, 30]
Sorted: [5, 9, 11, 13, 15, 20, 30, 30, 30, 80]
Time: 0.025000ms

Original array: [20, 11, 9, 5, 30, 30, 15, 13, 80, 30]
Sorted with 5 buckets: [5, 9, 11, 13, 15, 20, 30, 30, 30, 80]
Time: 0.015000ms
*/
