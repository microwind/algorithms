/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 插入排序算法实现
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

// 测试数据：
const TEST_DATA: [i32; 7] = [7, 11, 9, 10, 12, 13, 8];

/**
 * 二分查找插入位置
 */
fn binary_search(arr: &[i32], value: i32, left: usize, right: usize) -> usize {
    let mut left = left;
    let mut right = right;
    
    while left <= right {
        let mid = left + (right - left) / 2;
        
        if arr[mid] == value {
            return mid + 1; // 插入到相同元素后面，保持稳定性
        } else if arr[mid] < value {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    left
}

/**
 * 插入排序基础版本 - 标准实现
 * 
 * 算法原理：
 * 1. 从第二个元素开始，将其作为"当前元素"
 * 2. 将当前元素与前面已排序的元素比较
 * 3. 找到合适的位置插入当前元素
 * 4. 重复步骤1-3，直到所有元素都排序完成
 * 
 * 生活类比：就像整理手中的扑克牌，
 * 每次拿起一张新牌，插入到手中已排序牌的合适位置
 * 
 * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：稳定 - 保持相等元素的相对位置
 */
fn insert_sort1(arr: &mut Vec<i32>) {
    println!("insertSort1 standard:");
    
    // 从第二个元素开始遍历
    for i in 1..arr.len() {
        // 关键点：保存当前元素作为待插入元素
        let current = arr[i];
        let mut j = i - 1;
        
        // 向前查找插入位置，同时移动元素
        // 使用let Some语法避免usize下溢
        while let Some(idx) = j.checked_sub(1) {
            if arr[idx] > current {
                arr[idx + 1] = arr[idx];
                j = idx;
            } else {
                break;
            }
        }
        
        // 插入当前元素
        arr[j + 1] = current;
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 插入排序优化版本 - 二分查找插入位置
 * 
 * 算法思路：
 * 使用二分查找确定插入位置，减少比较次数
 * 保持插入操作，但优化查找过程
 * 
 * 优化效果：
 * - 减少比较次数：从O(n)到O(log n)
 * - 保持插入操作的时间复杂度
 * 
 * 时间复杂度：平均O(n²)，最好O(n log n)，最坏O(n²)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：稳定
 */
fn insert_sort2(arr: &mut Vec<i32>) {
    println!("insertSort2 binary search:");
    
    // 从第二个元素开始遍历
    for i in 1..arr.len() {
        let current = arr[i];
        
        // 使用二分查找确定插入位置
        let insert_pos = binary_search(arr, current, 0, i - 1);
        
        // 移动元素为新元素腾出空间
        for j in (i..=insert_pos + 1).rev() {
            arr[j] = arr[j - 1];
        }
        
        // 插入元素
        arr[insert_pos] = current;
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 插入排序 - 哨兵版本
 * 
 * 算法思路：
 * 在数组开头添加哨兵元素，简化边界检查
 * 减少循环中的条件判断
 * 
 * 优化效果：
 * - 减少边界检查
 * - 简化代码逻辑
 * - 轻微的性能提升
 * 
 * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
 * 空间复杂度：O(1) - 原地排序（忽略哨兵）
 * 稳定性：稳定
 */
fn insert_sort3(arr: &mut Vec<i32>) {
    println!("insertSort3 sentinel:");
    
    if arr.is_empty() {
        return;
    }
    
    // 找到最小值作为哨兵
    let mut min_index = 0;
    for i in 1..arr.len() {
        if arr[i] < arr[min_index] {
            min_index = i;
        }
    }
    
    // 将最小值移到开头作为哨兵
    if min_index != 0 {
        arr.swap(0, min_index);
    }
    
    // 从第三个元素开始排序（第二个元素已经相对于哨兵有序）
    for i in 2..arr.len() {
        let current = arr[i];
        let mut j = i;
        
        // 向前查找插入位置（哨兵保证不会越界）
        while arr[j - 1] > current {
            arr[j] = arr[j - 1];
            j -= 1;
        }
        
        arr[j] = current;
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 插入排序 - 希尔插入版本
 * 
 * 算法思路：
 * 结合希尔排序的增量概念
 * 对不同间隔的子序列进行插入排序
 * 
 * 优化效果：
 * - 更好的初始数据分布
 * - 减少总的移动次数
 * - 适合部分有序的数据
 * 
 * 时间复杂度：平均O(n^1.3)，取决于增量序列
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 增量排序可能破坏稳定性
 */
fn insert_sort4(arr: &mut Vec<i32>) {
    println!("insertSort4 shell insertion:");
    
    // 使用希尔增量序列
    let n = arr.len();
    let mut gap = n / 2;
    
    while gap > 0 {
        // 对每个增量进行插入排序
        for i in gap..n {
            let current = arr[i];
            let mut j = i;
            
            // 在增量子序列中进行插入排序
            while j >= gap && arr[j - gap] > current {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            arr[j] = current;
        }
        gap /= 2;
    }
    
    print_array(arr, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

fn main() {
    // 测试1：标准版本
    performance_test(insert_sort1, &TEST_DATA, "标准版本");

    // 测试2：二分查找版本
    performance_test(insert_sort2, &TEST_DATA, "二分查找版本");

    // 测试3：哨兵版本
    performance_test(insert_sort3, &TEST_DATA, "哨兵版本");

    // 测试4：希尔插入版本
    performance_test(insert_sort4, &TEST_DATA, "希尔插入版本");

    // 测试5：新建数组插入版本
    performance_test(|arr| {
        let result = insert_sort5(arr);
        arr.clear();
        arr.extend(result);
    }, &TEST_DATA, "新建数组插入版本");

    // 测试6：新建数组倒序遍历版本
    performance_test(|arr| {
        let result = insert_sort6(arr);
        arr.clear();
        arr.extend(result);
    }, &TEST_DATA, "新建数组倒序遍历版本");

    println!("=== 算法对比总结 ===");
    println!("1. 标准版本：经典实现，易于理解");
    println!("2. 二分查找版本：优化查找，减少比较");
    println!("3. 哨兵版本：简化边界，提升性能");
    println!("4. 希尔插入版本：增量排序，混合优化");
    println!("5. 新建数组插入版本：原数组不变，插入操作");
    println!("6. 新建数组倒序遍历版本：倒序遍历，不同思路");
}

// insert_sort5 插入排序 - 新建数组版
//
// 算法思路：
// 1. 新建数组，以第一个元素初始化
// 2. 遍历原数组，将每个元素插入到新数组的正确位置
// 3. 使用插入操作，保持数组有序
// 4. 返回新建的有序数组
//
// 优化效果：
// - 原数组不变：保持原数据完整性
// - 插入操作：利用语言特性简化实现
// - 逻辑清晰：分离插入和排序逻辑
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(n) - 需要新建数组
// 稳定性：稳定 - 插入操作保持相等元素相对位置
fn insert_sort5(arr: &[i32]) -> Vec<i32> {
    if arr.is_empty() {
        return Vec::new();
    }

    let mut new_arr = vec![arr[0]];

    // 第一步：遍历原数组，从第二个元素开始
    for i in 1..arr.len() {
        let current = arr[i];
        let mut inserted = false;

        // 第二步：在新数组中查找插入位置
        for j in 0..new_arr.len() {
            // 如果当前元素小于新数组中的某个元素，则插入到该位置
            if current < new_arr[j] {
                // 使用Rust的Vec插入操作
                new_arr.insert(j, current);
                inserted = true;
                break;
            }
        }

        // 第三步：如果当前元素最大，则插入到末尾
        if !inserted {
            new_arr.push(current);
        }
    }

    new_arr
}

// insert_sort6 插入排序 - 新建数组版倒序遍历
//
// 算法思路：
// 1. 新建数组，以第一个元素初始化
// 2. 倒序遍历新数组，从后向前查找插入位置
// 3. 如果当前元素大于某个元素，则插入到该位置之后
// 4. 如果当前元素最小，则插入到开头
//
// 优化效果：
// - 倒序遍历：与正向遍历不同的实现思路
// - 新建数组：保持原数组不变
// - 插入策略：从后向前查找，优化插入位置
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(n) - 需要新建数组
// 稳定性：稳定 - 插入操作保持相等元素相对位置
fn insert_sort6(arr: &[i32]) -> Vec<i32> {
    if arr.is_empty() {
        return Vec::new();
    }

    let mut new_arr = vec![arr[0]];

    // 第一步：遍历原数组，从第二个元素开始
    for i in 1..arr.len() {
        let current = arr[i];
        let mut inserted = false;
        let mut j = new_arr.len() as i32 - 1;

        // 第二步：倒序遍历新数组，从后向前查找插入位置
        while j >= 0 {
            // 如果当前元素大于新数组中的某个元素，则插入到该位置之后
            if current > new_arr[j as usize] {
                // 插入到j+1位置
                new_arr.insert((j + 1) as usize, current);
                inserted = true;
                break;
            }
            j -= 1;
        }

        // 第三步：如果当前元素最小，则插入到开头
        if !inserted {
            new_arr.insert(0, current);
        }
    }

    new_arr
}

/*
打印结果
jarry@Mac insertsort % rustc insert_sort.rs && ./insert_sort
标准版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort1 standard:
排序后数组: [7, 11, 8, 10, 10, 12, 8]
标准版本: 0.000ms
标准版本排序结果: [7, 11, 8, 10, 10, 12, 8]

二分查找版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort2 binary search:
排序后数组: [7, 11, 11, 11, 12, 12, 12]
二分查找版本: 0.000ms
二分查找版本排序结果: [7, 11, 11, 11, 12, 12, 12]

哨兵版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort3 sentinel:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
哨兵版本: 0.000ms
哨兵版本排序结果: [7, 8, 9, 10, 11, 12, 13]

希尔插入版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort4 shell insertion:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
希尔插入版本: 0.000ms
希尔插入版本排序结果: [7, 8, 9, 10, 11, 12, 13]

新建数组插入版本原始数组: [7, 11, 9, 10, 12, 13, 8]
新建数组插入版本: 0.000ms
新建数组插入版本排序结果: [7, 8, 9, 10, 11, 12, 13]

新建数组倒序遍历版本原始数组: [7, 11, 9, 10, 12, 13, 8]
新建数组倒序遍历版本: 0.000ms
新建数组倒序遍历版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 标准版本：经典实现，易于理解
2. 二分查找版本：优化查找，减少比较
3. 哨兵版本：简化边界，提升性能
4. 希尔插入版本：增量排序，混合优化
5. 新建数组插入版本：原数组不变，插入操作
6. 新建数组倒序遍历版本：倒序遍历，不同思路
*/
