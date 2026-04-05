/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 希尔排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

use std::time::Instant;

/**
 * 打印数组内容的辅助函数
 */
fn print_array(arr: &[i32], label: &str) {
    println!("{}: [{}]", label, arr.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(", "));
}

/**
 * 性能测试辅助函数
 */
fn performance_test<F>(sort_func: F, arr: &[i32], name: &str) 
where 
    F: FnOnce(&mut Vec<i32>)
{
    // 创建数组副本，避免修改原数组
    let mut test_arr = arr.to_vec();
    print_array(&test_arr, &format!("{}原始数组", name));
    
    // 开始计时
    let start_time = Instant::now();
    sort_func(&mut test_arr);
    let end_time = Instant::now();
    
    let duration = end_time.duration_since(start_time).as_millis() as f64;
    println!("{}: {:.3}ms", name, duration);
    print_array(&test_arr, &format!("{}排序结果", name));
    println!(""); // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含大数字和负数的典型数组
const TEST_DATA: [i32; 10] = [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431];

/**
 * 希尔排序基础版本 - 原始Shell序列
 * 
 * 算法原理：
 * 1. 选择一个增量序列，如 n/2, n/4, ..., 1
 * 2. 对每个增量进行插入排序，但只比较相距增量的元素
 * 3. 逐步减小增量，直到增量为1，此时数组基本有序
 * 4. 最后一次插入排序完成整个排序过程
 * 
 * 生活类比：就像整理一副扑克牌，先按间隔几张牌进行分组整理，
 * 然后逐步缩小间隔，最后对相邻的牌进行精细整理
 * 
 * 时间复杂度：平均O(n^1.3)，最坏O(n²)，取决于增量序列
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 相距增量的元素交换可能改变相等元素的相对位置
 */
fn shell_sort1(arr: &mut Vec<i32>) {
    println!("shellSort1 original sequence:");
    let n = arr.len();
    
    // 原始Shell序列：n/2, n/4, ..., 1
    let mut gap = n / 2;
    while gap > 0 {
        // 对每个增量进行插入排序
        for i in gap..n {
            // 关键点：保存当前元素，与前面相距gap的元素比较
            let temp = arr[i];
            let mut j = i;
            
            // 向前查找插入位置
            while j >= gap && arr[j - gap] > temp {
                println!("gap={} i={} j-gap={} j={} arr:{:?}", gap, i, j - gap, j, arr);
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            // 插入元素
            arr[j] = temp;
        }
        gap /= 2;
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 希尔排序优化版本 - Knuth序列
 * 
 * 算法思路：
 * 使用Knuth提出的增量序列：1, 4, 13, 40, ...
 * 公式：gap = 3 * gap + 1，然后反向递减
 * 
 * 优化效果：
 * - 更好的增量序列，减少比较次数
 * - 理论上更优的时间复杂度
 * 
 * 时间复杂度：平均O(n^1.25)，比原始序列更优
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 插入排序的不稳定性继承
 */
fn shell_sort2(arr: &mut Vec<i32>) {
    println!("shellSort2 Knuth sequence:");
    let n = arr.len();
    
    // 计算初始增量（Knuth序列）
    let mut gap = 1;
    while gap < n / 3 {
        gap = 3 * gap + 1; // 1, 4, 13, 40, 121, ...
    }
    
    // 反向递减处理
    while gap > 0 {
        // 对每个增量进行插入排序
        for i in gap..n {
            let temp = arr[i];
            let mut j = i;
            
            // 向前查找插入位置
            while j >= gap && arr[j - gap] > temp {
                println!("gap={} i={} j-gap={} j={} arr:{:?}", gap, i, j - gap, j, arr);
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            // 插入当前元素
            arr[j] = temp;
        }
        gap /= 3;
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 希尔排序 - Hibbard序列
 * 
 * 算法思路：
 * 使用Hibbard序列：1, 3, 7, 15, 31, ...
 * 公式：gap = 2^k - 1
 * 
 * 优化效果：
 * - 更好的增量分布
 * 理论时间复杂度为O(n^(3/2))
 * 
 * 时间复杂度：平均O(n^1.5)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 插入排序的不稳定性继承
 */
fn shell_sort3(arr: &mut Vec<i32>) {
    println!("shellSort3 Hibbard sequence:");
    let n = arr.len();
    
    // 生成Hibbard序列
    let mut gaps = Vec::new();
    let mut k = 1;
    
    loop {
        let gap = 2_i32.pow(k) - 1; // 2^k - 1
        if gap >= n as i32 {
            break;
        }
        gaps.push(gap);
        k += 1;
    }
    
    // 反向使用序列
    for g in (0..gaps.len()).rev() {
        let gap = gaps[g] as usize;
        
        // 对每个增量进行插入排序
        for i in gap..n {
            let temp = arr[i];
            let mut j = i;
            
            // 向前查找插入位置
            while j >= gap && arr[j - gap] > temp {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            arr[j] = temp;
        }
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 希尔排序 - Sedgewick序列
 * 
 * 算法思路：
 * 使用Sedgewick序列：1, 5, 19, 41, 109, ...
 * 结合4^k + 3*2^(k-1) + 1和9*2^k - 9*2^(k/2) + 1
 * 
 * 优化效果：
 * - 最优的增量序列之一
 * - 更好的性能表现
 * 
 * 时间复杂度：平均O(n^1.25)，接近最优
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 插入排序的不稳定性继承
 */
fn shell_sort4(arr: &mut Vec<i32>) {
    println!("shellSort4 Sedgewick sequence:");
    let n = arr.len();
    
    // 生成Sedgewick序列
    // 使用简化版本：1, 5, 19, 41, 109, 209, 505, 929, 2161
    let sedgewick_gaps = [1, 5, 19, 41, 109, 209, 505, 929, 2161];
    let mut gaps = Vec::new();
    
    for gap in sedgewick_gaps.iter() {
        if *gap < n as i32 {
            gaps.push(*gap);
        }
    }
    
    // 反向使用序列
    for g in (0..gaps.len()).rev() {
        let gap = gaps[g] as usize;
        
        // 对每个增量进行插入排序
        for i in gap..n {
            let temp = arr[i];
            let mut j = i;
            
            // 向前查找插入位置
            while j >= gap && arr[j - gap] > temp {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            // 插入到对应位置
            arr[j] = temp;
        }
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 希尔排序 - 递归版本（尾递归实现）
 * 
 * 算法思路：
 * 递归处理增量（分组）序列，每个增量插入排序
 * 增量序列采用 gap/2（希尔原始序列）
 * 
 * 递归结构：
 * - 外层尾递归：处理递减的增量序列
 * - 内层循环：对每个位置进行插入排序
 */
fn shell_sort5(arr: &mut [i32], gap: usize) {
    // 递归终止条件
    if gap <= 0 {
        return;
    }
    
    // 对当前增量（分组）进行插入排序
    let n = arr.len();
    for i in gap..n {
        let temp = arr[i];
        let mut j = i;
        
        // 向前查找插入位置
        while j >= gap && arr[j - gap] > temp {
            arr[j] = arr[j - gap];
            j -= gap;
        }
        
        // 插入到对应位置
        arr[j] = temp;
    }
    
    // 尾递归调用：递归是函数的最后操作
    shell_sort5(arr, gap / 2);
}

// ==================== 算法测试和性能对比 ====================

fn main() {
    // 测试1：原始Shell序列
    performance_test(shell_sort1, &TEST_DATA, "原始Shell序列");

    // 测试2：Knuth序列
    performance_test(shell_sort2, &TEST_DATA, "Knuth序列");

    // 测试3：Hibbard序列
    performance_test(shell_sort3, &TEST_DATA, "Hibbard序列");

    // 测试4：Sedgewick序列
    performance_test(shell_sort4, &TEST_DATA, "Sedgewick序列");

    // 测试5：递归版本（尾递归）
    println!("shellSort5 递归版本:");
    let mut test_data_copy = TEST_DATA.clone();
    let gap = test_data_copy.len() / 2;
    shell_sort5(&mut test_data_copy, gap);
    print_array(&test_data_copy, "递归版本");

    println!("=== 算法对比总结 ===");
    println!("1. 原始Shell序列：简单实现，易于理解");
    println!("2. Knuth序列：经典优化，性能提升");
    println!("3. Hibbard序列：数学优化，理论更优");
    println!("4. Sedgewick序列：最优序列，性能最佳");
    println!("5. 递归版本：尾递归优化实现");
}

/*
打印结果
jarry@Mac shellsort % rustc shell_sort.rs && shell_sort
原始Shell序列原始数组: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort1 original sequence:
gap=5 i=5 j-gap=0 j=5 arr:[33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
gap=5 i=9 j-gap=4 j=9 arr:[-7, 4, 15, 43, 323454, 33, 105, 1235, 200, 87431]
gap=2 i=5 j-gap=3 j=5 arr:[-7, 4, 15, 43, 87431, 33, 105, 1235, 200, 323454]
gap=2 i=6 j-gap=4 j=6 arr:[-7, 4, 15, 33, 87431, 43, 105, 1235, 200, 323454]
gap=2 i=8 j-gap=6 j=8 arr:[-7, 4, 15, 33, 105, 43, 87431, 1235, 200, 323454]
gap=1 i=5 j-gap=4 j=5 arr:[-7, 4, 15, 33, 105, 43, 200, 1235, 87431, 323454]
排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
原始Shell序列: 0.000ms
原始Shell序列排序结果: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

Knuth序列原始数组: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort2 Knuth sequence:
gap=4 i=5 j-gap=1 j=5 arr:[33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
gap=4 i=8 j-gap=4 j=8 arr:[33, -7, 15, 43, 323454, 4, 105, 1235, 200, 87431]
gap=1 i=1 j-gap=0 j=1 arr:[33, -7, 15, 43, 200, 4, 105, 1235, 323454, 87431]
gap=1 i=2 j-gap=1 j=2 arr:[-7, 33, 15, 43, 200, 4, 105, 1235, 323454, 87431]
gap=1 i=5 j-gap=4 j=5 arr:[-7, 15, 33, 43, 200, 4, 105, 1235, 323454, 87431]
gap=1 i=5 j-gap=3 j=4 arr:[-7, 15, 33, 43, 200, 200, 105, 1235, 323454, 87431]
gap=1 i=5 j-gap=2 j=3 arr:[-7, 15, 33, 43, 43, 200, 105, 1235, 323454, 87431]
gap=1 i=5 j-gap=1 j=2 arr:[-7, 15, 33, 33, 43, 200, 105, 1235, 323454, 87431]
gap=1 i=6 j-gap=5 j=6 arr:[-7, 4, 15, 33, 43, 200, 105, 1235, 323454, 87431]
gap=1 i=9 j-gap=8 j=9 arr:[-7, 4, 15, 33, 43, 105, 200, 1235, 323454, 87431]
排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
Knuth序列: 0.000ms
Knuth序列排序结果: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

Hibbard序列原始数组: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort3 Hibbard sequence:
排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
Hibbard序列: 0.000ms
Hibbard序列排序结果: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

Sedgewick序列原始数组: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort4 Sedgewick sequence:
排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
Sedgewick序列: 0.000ms
Sedgewick序列排序结果: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

shellSort5 递归版本:
递归版本: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
=== 算法对比总结 ===
1. 原始Shell序列：简单实现，易于理解
2. Knuth序列：经典优化，性能提升
3. Hibbard序列：数学优化，理论更优
4. Sedgewick序列：最优序列，性能最佳
5. 递归版本：尾递归优化实现
*/
