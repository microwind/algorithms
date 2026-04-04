/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 选择排序算法实现
 * 提供五种不同的实现方式，适合不同场景和性能需求
 */

use std::time::Instant;

/**
 * 打印数组内容的辅助函数
 */
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

/**
 * 性能测试辅助函数
 */
fn performance_test<F>(sort_func: F, arr: &[i32], name: &str) 
where 
    F: Fn(&mut [i32]),
{
    // 创建数组副本，避免修改原数组
    let mut test_arr = arr.to_vec();
    print_array(&test_arr, &format!("{}原始数组", name));
    
    // 开始计时
    let start = Instant::now();
    sort_func(&mut test_arr);
    let duration = start.elapsed();
    
    println!("{}: {:.3}ms", name, duration.as_micros() as f64 / 1000.0);
    print_array(&test_arr, &format!("{}排序结果", name));
    println!(); // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
const TEST_DATA: [i32; 7] = [7, 11, 9, 10, 12, 13, 8];

/**
 * 选择排序基础版本 - 标准版：原地交换
 *
 * 算法原理：
 * 1. 将数组分为两部分：左侧已排序区域，右侧待排序区域
 * 2. 每次从待排序区域中选择最小元素
 * 3. 将最小元素与待排序区域的第一个元素交换
 * 4. 重复以上过程，直到所有元素排序完成
 *
 * ## 实现步骤
 * 1. 外循环遍历数组，每轮确定一个最小值的位置
 * 2. 内循环在未排序区域中查找最小元素
 * 3. 记录最小值和其索引位置
 * 4. 将最小元素交换到当前轮次的起始位置
 */
fn selection_sort1(arr: &mut [i32]) {
    println!("selection_sort1 basic:");
    let len = arr.len();
    // 外循环：每轮确定一个最小值
    for i in 0..len - 1 {
        let mut min = arr[i];
        let mut min_idx = i;

        // 内循环：在未排序部分找最小元素
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
 * 选择排序新建数组版本 - 无需交换
 *
 * 算法思路：
 * 1. 创建一个新数组来存储排序结果
 * 2. 每次从原数组中找到最小值
 * 3. 将最小值添加到新数组
 * 4. 从原数组中删除该最小值
 * 5. 重复直到原数组为空
 *
 * ## 实现步骤
 * 1. 初始化新数组和剩余数组
 * 2. 外循环控制选择轮数
 * 3. 内循环查找当前最小值
 * 4. 将最小值添加到新数组
 * 5. 从原数组中移除已选择的元素
 * 6. 重复直到原数组为空
 */
fn selection_sort2(arr: Vec<i32>) -> Vec<i32> {
    println!("selection_sort2 new array:");
    let mut new_list = Vec::new();
    let mut remaining = arr;

    // 外循环：每次选择一个最小值
    while !remaining.is_empty() {
        let mut min = remaining[0];
        let mut min_idx = 0;

        // 内循环：找最小元素
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
 * 选择排序降序版本
 *
 * 算法思路：
 * 与基础版本相反，每次选择最大元素
 * 将最大元素与待排序区域的第一个元素交换
 *
 * ## 实现步骤
 * 1. 外循环控制排序轮数，每轮确定一个最大值的位置
 * 2. 内循环在未排序区域中查找最大元素
 * 3. 记录最大值和其索引位置
 * 4. 将最大元素交换到当前轮次的起始位置
 */
fn selection_sort3(arr: &mut [i32]) {
    println!("selection_sort3 descending:");
    let len = arr.len();
    
    // 外循环：每轮确定一个最大值
    for i in 0..len - 1 {
        let mut max_index = i;
        
        // 内循环：在未排序区域查找最大值
        for j in (i + 1)..len {
            if arr[j] > arr[max_index] {
                max_index = j;
            }
        }
        
        // 交换最大元素到正确位置
        if max_index != i {
            arr.swap(i, max_index);
        }
    }
    print_array(arr, "排序后数组");
}

/**
 * 选择排序优化版本 - 双向选择
 *
 * 优化思路：
 * 每轮同时选择最小和最大元素
 * 将最小元素放到左侧，最大元素放到右侧
 * 减少排序轮数，提高效率
 *
 * ## 实现步骤
 * 1. 初始化左右边界指针
 * 2. 外循环控制排序轮数，同时处理两端
 * 3. 内循环在未排序区域中查找最小和最大元素
 * 4. 交换最小元素到左侧，最大元素到右侧
 * 5. 调整边界指针
 */
fn selection_sort4(arr: &mut [i32]) {
    println!("selection_sort4 bidirectional:");
    let len = arr.len();
    let mut left = 0;
    let mut right = len - 1;

    // 外循环：同时处理左右两端
    while left < right {
        let mut min_idx = left;
        let mut max_idx = left;

        // 内循环：找最小和最大元素
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
    print_array(arr, "排序后数组");
}

/**
 * 选择排序 - 堆优化版本
 *
 * 算法思路：
 * 利用堆的性质来快速找到最大/最小元素
 * 每次从堆顶取出最大/最小元素
 * 重新调整堆结构
 *
 * ## 实现步骤
 * 1. 构建最大堆
 * 2. 逐个取出堆顶元素（最大值）
 * 3. 将堆顶元素与末尾元素交换
 * 4. 重新调整堆结构
 * 5. 重复直到堆为空
 */
fn selection_sort5(arr: &mut [i32]) {
    println!("selection_sort5 heap optimized:");
    let len = arr.len();
    
    // 构建最大堆
    for i in (0..len / 2).rev() {
        heapify(arr, len, i);
    }
    
    // 逐个取出堆顶元素
    for i in (1..len).rev() {
        // 交换堆顶与末尾元素
        arr.swap(0, i);
        
        // 重新调整堆
        heapify(arr, i, 0);
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 堆化辅助函数
 */
fn heapify(arr: &mut [i32], n: usize, i: usize) {
    let mut largest = i;
    let left = 2 * i + 1;
    let right = 2 * i + 2;
    
    // 如果左子节点大于根节点
    if left < n && arr[left] > arr[largest] {
        largest = left;
    }
    
    // 如果右子节点大于当前最大节点
    if right < n && arr[right] > arr[largest] {
        largest = right;
    }
    
    // 如果最大节点不是根节点，交换并继续堆化
    if largest != i {
        arr.swap(i, largest);
        heapify(arr, n, largest);
    }
}

// ==================== 算法测试和性能对比 ====================

fn main() {
    println!("\n=== 算法性能对比 ===");
    
    // 测试1：基础选择版本（直接测试，不使用performance_test）
    println!("基础选择版本原始数组:");
    print_array(&TEST_DATA, "");
    let mut temp_arr1 = TEST_DATA.to_vec();
    let start1 = Instant::now();
    selection_sort1(&mut temp_arr1);
    let end1 = start1.elapsed();
    println!("基础选择版本: {:.3}ms", end1.as_micros() as f64 / 1000.0);
    println!("基础选择版本排序结果:");
    print_array(&temp_arr1, "");
    println!();

    // 测试2：新建数组版本（直接测试，不使用performance_test）
    println!("新建数组版本原始数组:");
    print_array(&TEST_DATA, "");
    let temp_arr2 = TEST_DATA.to_vec();
    let start2 = Instant::now();
    let result2 = selection_sort2(temp_arr2);
    let end2 = start2.elapsed();
    println!("新建数组版本: {:.3}ms", end2.as_micros() as f64 / 1000.0);
    println!("新建数组版本排序结果:");
    print_array(&result2, "");
    println!();

    // 测试3：降序版本
    performance_test(selection_sort3, &TEST_DATA, "降序版本");

    // 测试4：双向选择版本
    performance_test(selection_sort4, &TEST_DATA, "双向选择版本");

    // 测试5：堆优化版本
    performance_test(selection_sort5, &TEST_DATA, "堆优化版本");

    println!("=== 算法对比总结 ===");
    println!("1. 基础版本：标准版，原地交换，包含详细调试信息");
    println!("2. 新建数组版本：无需交换，避免交换操作");
    println!("3. 降序版本：展示算法灵活性，可按需排序");
    println!("4. 双向版本：同时选择最大最小，效率提升");
    println!("5. 堆优化版本：利用堆结构，复杂度优化");
}
/*打印结果
jarry@Mac selectionsort % rustc selection_sort.rs && ./selection_sort

=== 算法性能对比 ===
基础选择版本原始数组:
: [7, 11, 9, 10, 12, 13, 8]
selection_sort1 basic:
基础选择版本: 0.001ms
基础选择版本排序结果:
: [7, 8, 9, 10, 11, 12, 13]

新建数组版本原始数组:
: [7, 11, 9, 10, 12, 13, 8]
selection_sort2 new array:
新建数组版本: 0.003ms
新建数组版本排序结果:
: [7, 8, 9, 10, 11, 12, 13]

降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selection_sort3 descending:
排序后数组: [13, 12, 11, 10, 9, 8, 7]
降序版本: 0.001ms
降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]

双向选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selection_sort4 bidirectional:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
双向选择版本: 0.001ms
双向选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

堆优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selection_sort5 heap optimized:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
堆优化版本: 0.002ms
堆优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 基础版本：标准版，原地交换，包含详细调试信息
2. 新建数组版本：无需交换，避免交换操作
3. 降序版本：展示算法灵活性，可按需排序
4. 双向版本：同时选择最大最小，效率提升
5. 堆优化版本：利用堆结构，复杂度优化
*/