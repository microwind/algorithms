/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::time::Instant;

/**
 * 堆排序
 * 通过构建大顶堆，然后不断交换堆顶和最后一个元素来实现排序
 */
struct HeapSort;

impl HeapSort {
    fn get_parent(i: usize) -> usize {
        if i == 0 { 0 } else { (i - 1) / 2 }
    }

    fn get_left(i: usize) -> usize {
        2 * i + 1
    }

    fn get_right(i: usize) -> usize {
        2 * i + 2
    }

    /**
     * 维护大顶堆性质
     * 递归调整以idx为根的子树，保持堆的性质
     */
    fn max_heapify(arr: &mut [i32], idx: usize, size: usize) {
        let mut max = idx;
        let left = Self::get_left(idx);
        let right = Self::get_right(idx);

        // 找到父节点和子节点中的最大值
        if left < size && arr[left] > arr[max] {
            max = left;
        }
        if right < size && arr[right] > arr[max] {
            max = right;
        }

        // 如果最大值不是当前节点，交换并递归调整
        if max != idx {
            arr.swap(idx, max);
            Self::max_heapify(arr, max, size);
        }
    }

    /**
     * 构建大顶堆
     * 从最后一个非叶子节点开始，逐个调整为堆
     */
    fn build_max_heap(arr: &mut [i32]) {
        let len = arr.len();
        if len == 0 {
            return;
        }
        let last_parent = if len > 0 { (len - 2) / 2 } else { 0 };

        for i in (0..=last_parent).rev() {
            Self::max_heapify(arr, i, len);
        }
    }

    /**
     * 堆排序：交换堆顶和最后一个元素，重新调整堆
     */
    fn sort_tree(arr: &mut [i32]) {
        let len = arr.len();
        for i in (1..len).rev() {
            // 交换堆顶元素到末尾
            arr.swap(0, i);
            // 重新调整堆
            Self::max_heapify(arr, 0, i);
        }
    }

    /**
     * 执行堆排序
     */
    fn sort(arr: &mut [i32]) {
        Self::build_max_heap(arr);
        Self::sort_tree(arr);
    }
}

fn main() {
    println!("Heap Sort Test:");

    let mut data = vec![7, 11, 9, 10, 12, 13, 8];
    println!("Original array: {:?}", data);

    let start = Instant::now();
    HeapSort::sort(&mut data);
    println!("Sorted: {:?}", data);
    println!("Time: {:.6}ms\n", start.elapsed().as_secs_f64() * 1000.0);

    let mut data2 = vec![20, 11, 9, 5, 30, 30, 15, 13, 80, 30];
    println!("Original array: {:?}", data2);

    let start = Instant::now();
    HeapSort::sort(&mut data2);
    println!("Sorted: {:?}", data2);
    println!("Time: {:.6}ms", start.elapsed().as_secs_f64() * 1000.0);
}

/*
rustc -V
rustc 1.70.0 (90c541806 2023-04-27)

rustc heap_sort.rs && ./heap_sort
Heap Sort Test:
Original array: [7, 11, 9, 10, 12, 13, 8]
Sorted: [7, 8, 9, 10, 11, 12, 13]
Time: 0.008000ms

Original array: [20, 11, 9, 5, 30, 30, 15, 13, 80, 30]
Sorted: [5, 9, 11, 13, 15, 20, 30, 30, 30, 80]
Time: 0.005000ms
*/
