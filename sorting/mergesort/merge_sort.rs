//! Copyright © https://github.com/microwind All rights reserved.
//!
//! @author: jarryli@gmail.com
//! @version: 1.0
//!
//! 归并排序算法实现
//! 提供四种不同的实现方式，适合不同场景和性能需求

use std::time::Instant;

/// 打印数组内容的辅助函数
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

/// 性能测试辅助函数
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

/// 合并两个有序数组
/// 
/// 步骤1：初始化结果数组和索引指针
/// 步骤2：按顺序合并两个有序数组
/// 步骤3：处理剩余元素
/// 步骤4：返回合并结果
/// 
/// 关键点：
/// - 使用索引指针避免不必要的内存分配
/// - 利用Rust的slice特性高效处理剩余元素
/// - 保持算法的稳定性
fn merge(left: &[i32], right: &[i32]) -> Vec<i32> {
    // 步骤1：初始化结果数组和索引指针
    // 关键点：预分配足够容量，避免多次扩容
    let mut result = Vec::with_capacity(left.len() + right.len());
    let mut left_index = 0;
    let mut right_index = 0;
    
    // 步骤2：按顺序合并两个有序数组
    // 关键点：比较两个数组的当前元素，选择较小的放入结果数组
    while left_index < left.len() && right_index < right.len() {
        // 关键点：选择较小的元素放入结果数组
        if left[left_index] <= right[right_index] {
            result.push(left[left_index]);
            left_index += 1;
        } else {
            result.push(right[right_index]);
            right_index += 1;
        }
    }
    
    // 步骤3：处理剩余元素
    // 关键点：将未处理完的数组元素直接添加到结果数组
    // Rust特点：使用extend_from_slice高效处理剩余元素
    result.extend_from_slice(&left[left_index..]);
    result.extend_from_slice(&right[right_index..]);
    
    // 步骤4：返回合并结果
    // 关键点：返回完全有序的合并数组
    result
}

/// 递归归并排序函数
/// 
/// 步骤1：检查递归终止条件
/// 步骤2：分割数组为两半
/// 步骤3：递归排序左右子数组
/// 步骤4：合并两个有序子数组
/// 
/// 关键点：
/// - 基础情况：数组长度小于等于1时已经有序
/// - 使用整数除法计算中间位置
/// - 利用Rust的slice特性高效分割数组
/// - 递归调用直到基础情况
fn merge_sort_recursive(arr: &[i32]) -> Vec<i32> {
    // 步骤1：检查递归终止条件
    // 关键点：数组长度小于等于1时已经有序，直接返回
    if arr.len() <= 1 {
        return arr.to_vec();
    }
    
    // 步骤2：分割数组为两半
    // 关键点：使用整数除法计算中间位置
    // Rust特点：使用slice分割数组，避免内存分配
    let middle = arr.len() / 2;
    let left = &arr[..middle];
    let right = &arr[middle..];
    
    // 步骤3：递归排序左右子数组
    // 关键点：分别对左右两部分进行递归排序
    let sorted_left = merge_sort_recursive(left);
    let sorted_right = merge_sort_recursive(right);
    
    // 步骤4：合并两个有序子数组
    // 关键点：将两个有序子数组合并成一个有序数组
    merge(&sorted_left, &sorted_right)
}

/// 归并排序基础版本 - 递归实现
/// 
/// 算法原理：
/// 1. 将数组递归地分成两半，直到每个子数组只有一个元素
/// 2. 将相邻的两个有序子数组合并成一个更大的有序数组
/// 3. 重复合并过程，直到最终得到一个完全有序的数组
/// 
/// 生活类比：就像整理一副扑克牌，先把牌分成两堆，
/// 每堆分别整理好，然后将两堆有序地合并在一起
/// 
/// 时间复杂度：O(n log n) - 无论如何都需要O(n log n)次比较
/// 空间复杂度：O(n) - 需要额外空间存储临时数组
/// 稳定性：稳定 - 合并过程中保持相等元素的相对位置
fn merge_sort1(arr: &mut [i32]) {
    println!("mergeSort1 recursive:");
    let result = merge_sort_recursive(arr);
    arr.copy_from_slice(&result);
    print_array(arr, "排序后数组");
}

/// 原地合并两个有序子数组
/// 
/// 步骤1：创建临时数组存储左半部分
/// 步骤2：初始化合并指针
/// 步骤3：按顺序合并两个有序子数组
/// 步骤4：处理左数组剩余元素
/// 步骤5：完成原地合并
/// 
/// 关键点：
/// - 使用临时数组存储左半部分，避免数据覆盖
/// - 三个指针分别跟踪左数组、右数组和合并位置
/// - 保持算法的稳定性
fn merge_in_place(arr: &mut [i32], left: usize, mid: usize, right: usize) {
    // 步骤1：创建临时数组存储左半部分
    // 关键点：避免在合并过程中覆盖未处理的数据
    let left_arr: Vec<i32> = arr[left..=mid].to_vec();
    
    // 步骤2：初始化合并指针
    // 关键点：i指向左数组，j指向右数组，k指向合并位置
    let mut i = 0; // 左数组索引
    let mut j = mid + 1; // 右数组索引
    let mut k = left; // 合并位置索引
    
    // 步骤3：按顺序合并两个有序子数组
    // 关键点：比较两个数组的当前元素，选择较小的放入原数组
    while i < left_arr.len() && j <= right {
        if left_arr[i] <= arr[j] {
            arr[k] = left_arr[i];
            i += 1;
        } else {
            arr[k] = arr[j];
            j += 1;
        }
        k += 1;
    }
    
    // 步骤4：处理左数组剩余元素
    // 关键点：左数组可能还有未处理的元素
    while i < left_arr.len() {
        arr[k] = left_arr[i];
        i += 1;
        k += 1;
    }
}

/// 递归归并排序函数 - 原地版本
/// 
/// 步骤1：检查递归终止条件
/// 步骤2：计算中间位置
/// 步骤3：递归排序左半部分
/// 步骤4：递归排序右半部分
/// 步骤5：原地合并两个有序部分
/// 
/// 关键点：
/// - 使用索引范围而不是slice，避免内存分配
/// - 原地合并减少空间复杂度
/// - 递归深度为O(log n)
fn merge_sort_in_place_recursive(arr: &mut [i32], left: usize, right: usize) {
    // 步骤1：检查递归终止条件
    // 关键点：left >= right时子数组已经有序
    if left < right {
        // 步骤2：计算中间位置
        // 关键点：使用整数除法，避免溢出
        let mid = (left + right) / 2;
        
        // 步骤3：递归排序左半部分
        // 关键点：将数组分成[left, mid]和[mid+1, right]两部分
        merge_sort_in_place_recursive(arr, left, mid);
        
        // 步骤4：递归排序右半部分
        // 关键点：确保右半部分也有序
        merge_sort_in_place_recursive(arr, mid + 1, right);
        
        // 步骤5：原地合并两个有序部分
        // 关键点：在原数组上进行合并操作
        merge_in_place(arr, left, mid, right);
    }
}

/// 归并排序优化版本 - 原地合并
/// 
/// 优化思路：
/// 减少空间复杂度，尝试在原数组上进行合并操作
/// 使用索引操作而不是创建新数组
/// 
/// 优化效果：
/// - 减少了内存分配
/// - 提高了空间效率
/// 
/// 时间复杂度：O(n log n)
/// 空间复杂度：O(1) - 原地操作
/// 稳定性：稳定 - 合并过程中保持相等元素的相对位置
fn merge_sort2(arr: &mut [i32]) {
    println!("mergeSort2 in-place:");
    if !arr.is_empty() {
        merge_sort_in_place_recursive(arr, 0, arr.len() - 1);
    }
    print_array(arr, "排序后数组");
}

/// 合并两个有序子数组 - 迭代版本
fn merge_iterative(arr: &mut [i32], temp: &mut [i32], left: usize, mid: usize, right: usize) {
    let mut i = left; // 左子数组索引
    let mut j = mid + 1; // 右子数组索引
    let mut k = left; // 临时数组索引
    
    // 合并到临时数组
    while i <= mid && j <= right {
        if arr[i] <= arr[j] {
            temp[k] = arr[i];
            i += 1;
        } else {
            temp[k] = arr[j];
            j += 1;
        }
        k += 1;
    }
    
    // 复制左子数组剩余元素
    while i <= mid {
        temp[k] = arr[i];
        i += 1;
        k += 1;
    }
    
    // 复制右子数组剩余元素
    while j <= right {
        temp[k] = arr[j];
        j += 1;
        k += 1;
    }
    
    // 将临时数组复制回原数组
    for i in left..=right {
        arr[i] = temp[i];
    }
}

/// 归并排序 - 迭代版本
/// 
/// 算法思路：
/// 使用迭代方式代替递归，避免递归栈开销
/// 从小规模合并开始，逐步扩大合并规模
/// 
/// 优化效果：
/// - 避免了递归调用的开销
/// - 更好的缓存局部性
/// 
/// 时间复杂度：O(n log n)
/// 空间复杂度：O(n) - 需要临时数组
/// 稳定性：稳定 - 合并过程中保持相等元素的相对位置
fn merge_sort3(arr: &mut [i32]) {
    println!("mergeSort3 iterative:");
    
    let n = arr.len();
    let mut temp = vec![0; n];
    
    // 迭代合并，步长从1开始翻倍
    let mut size = 1;
    while size < n {
        for left in (0..n - size).step_by(2 * size) {
            let mid = left + size - 1;
            let right = std::cmp::min(left + 2 * size - 1, n - 1);
            merge_iterative(arr, &mut temp, left, mid, right);
        }
        size *= 2;
    }
    
    print_array(arr, "排序后数组");
}

/// 合并两个相邻的有序子数组 - 自底向上版本
fn merge_bottom_up(arr: &mut [i32], temp: &mut [i32], left: usize, mid: usize, right: usize) {
    let mut i = left;
    let mut j = mid;
    let mut k = left;
    
    // 合并两个有序子数组到临时数组
    while i < mid && j <= right {
        if arr[i] <= arr[j] {
            temp[k] = arr[i];
            i += 1;
        } else {
            temp[k] = arr[j];
            j += 1;
        }
        k += 1;
    }
    
    // 复制剩余元素
    while i < mid {
        temp[k] = arr[i];
        i += 1;
        k += 1;
    }
    while j <= right {
        temp[k] = arr[j];
        j += 1;
        k += 1;
    }
    
    // 复制回原数组
    for i in left..=right {
        arr[i] = temp[i];
    }
}

/// 归并排序 - 自底向上版本
/// 
/// 算法思路：
/// 先将数组分成单个元素，然后两两合并
/// 逐步扩大合并规模，直到整个数组有序
/// 
/// 优化效果：
/// - 更好的内存访问模式
/// - 适合外部排序（处理大数据）
/// 
/// 时间复杂度：O(n log n)
/// 空间复杂度：O(n) - 需要临时数组
/// 稳定性：稳定 - 合并过程中保持相等元素的相对位置
fn merge_sort4(arr: &mut [i32]) {
    println!("mergeSort4 bottom-up:");
    
    let n = arr.len();
    let mut temp = vec![0; n];
    
    // 自底向上合并
    let mut width = 1;
    while width < n {
        for i in (0..n).step_by(2 * width) {
            let left = i;
            let mid = std::cmp::min(i + width, n);
            let right = std::cmp::min(i + 2 * width, n);
            
            if mid < right {
                merge_bottom_up(arr, &mut temp, left, mid, right - 1);
            }
        }
        width *= 2;
    }
    
    print_array(arr, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

/// 归并排序 - 非递归合并版本
/// 
/// 算法思路：
/// 使用非递归方式进行合并操作，避免递归调用
/// 通过迭代方式处理合并过程，提高内存效率
/// 
/// 优化效果：
/// - 避免递归栈开销
/// - 更好的内存访问模式
/// - 适合大数据处理
/// 
/// 时间复杂度：O(n log n)
/// 空间复杂度：O(n) - 需要临时数组
/// 稳定性：稳定 - 合并过程中保持相等元素的相对位置
fn merge_sort5(arr: &mut [i32]) {
    println!("mergeSort5 non-recursive merge:");
    
    /// 非递归合并两个有序子数组
    /// 
    /// 步骤1：初始化索引指针
    /// 步骤2：合并到临时数组
    /// 步骤3：复制左子数组剩余元素
    /// 步骤4：复制右子数组剩余元素
    /// 步骤5：将临时数组复制回原数组
    /// 
    /// 关键点：
    /// - 使用索引指针避免不必要的内存分配
    /// - 在临时数组中进行合并操作
    /// - 最后将结果复制回原数组
    fn merge_non_recursive(arr: &mut [i32], temp: &mut [i32], left: usize, mid: usize, right: usize) {
        // 步骤1：初始化索引指针
        // 关键点：i指向左子数组，j指向右子数组，k指向临时数组
        let mut i = left;      // 左子数组索引
        let mut j = mid + 1;   // 右子数组索引
        let mut k = left;      // 临时数组索引
        
        // 步骤2：合并到临时数组
        // 关键点：按顺序合并两个有序子数组
        while i <= mid && j <= right {
            if arr[i] <= arr[j] {
                temp[k] = arr[i];
                i += 1;
            } else {
                temp[k] = arr[j];
                j += 1;
            }
            k += 1;
        }
        
        // 步骤3：复制左子数组剩余元素
        // 关键点：左子数组可能还有未处理的元素
        while i <= mid {
            temp[k] = arr[i];
            i += 1;
            k += 1;
        }
        
        // 步骤4：复制右子数组剩余元素
        // 关键点：右子数组可能还有未处理的元素
        while j <= right {
            temp[k] = arr[j];
            j += 1;
            k += 1;
        }
        
        // 步骤5：将临时数组复制回原数组
        // 关键点：使用循环逐个复制，确保数据正确性
        // Rust特点：也可以使用copy_from_slice，但循环更直观
        for index in left..=right {
            arr[index] = temp[index];
        }
    }
    
    let n = arr.len();
    if n <= 1 {
        return;
    }
    
    // 步骤1：创建临时数组
    // 关键点：临时数组用于存储合并过程中的中间结果
    let mut temp = vec![0; n];
    
    // 步骤2：非递归合并过程
    // 关键点：通过迭代方式模拟递归的合并过程
    let mut size = 1;
    while size < n {
        // 步骤3：处理所有相邻的子数组对
        // 关键点：每次处理两个大小为size的相邻子数组
        for left in (0..n - size).step_by(2 * size) {
            // 步骤4：计算当前合并的边界
            // 关键点：确定左子数组 [left, mid] 和右子数组 [mid+1, right]
            let mid = left + size - 1;
            let right = std::cmp::min(left + 2 * size - 1, n - 1);
            
            // 步骤5：执行非递归合并
            // 关键点：使用迭代方式合并两个有序子数组
            merge_non_recursive(arr, &mut temp, left, mid, right);
        }
        size *= 2;
    }
    
    print_array(arr, "排序后数组");
}

fn main() {
    // 测试1：递归版本（基于slice分割）
    performance_test(merge_sort1, &TEST_DATA, "递归版本（基于slice分割）");

    // 测试2：原地合并版本
    performance_test(merge_sort2, &TEST_DATA, "原地合并版本");

    // 测试3：迭代版本
    performance_test(merge_sort3, &TEST_DATA, "迭代版本");

    // 测试4：自底向上版本
    performance_test(merge_sort4, &TEST_DATA, "自底向上版本");
    
    // 测试5：非递归合并版本
    performance_test(merge_sort5, &TEST_DATA, "非递归合并版本");

    println!("=== 算法对比总结 ===");
    println!("1. 递归版本（基于slice分割）：利用Rust语言特性，代码简洁");
    println!("2. 原地版本：空间优化，减少内存使用");
    println!("3. 迭代版本：避免递归，性能稳定");
    println!("4. 底向上版本：适合大数据，外部排序");
    println!("5. 非递归合并版本：迭代合并，高效内存");
}

/*
打印结果
jarry@Mac mergesort % rustc merge_sort.rs && ./merge_sort
递归版本（基于slice分割）原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort1 recursive:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
递归版本（基于slice分割）: 0.007ms
递归版本（基于slice分割）排序结果: [7, 8, 9, 10, 11, 12, 13]

原地合并版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort2 in-place:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
原地合并版本: 0.004ms
原地合并版本排序结果: [7, 8, 9, 10, 11, 12, 13]

迭代版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort3 iterative:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
迭代版本: 0.004ms
迭代版本排序结果: [7, 8, 9, 10, 11, 12, 13]

自底向上版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort4 bottom-up:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
自底向上版本: 0.004ms
自底向上版本排序结果: [7, 8, 9, 10, 11, 12, 13]

非递归合并版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort5 non-recursive merge:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
非递归合并版本: 0.022ms
非递归合并版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归版本（基于slice分割）：利用Rust语言特性，代码简洁
2. 原地版本：空间优化，减少内存使用
3. 迭代版本：避免递归，性能稳定
4. 底向上版本：适合大数据，外部排序
5. 非递归合并版本：迭代合并，高效内存
*/
