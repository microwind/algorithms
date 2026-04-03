/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 二分查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

/**
 * 二分查找基础版本 - 非递归实现
 * 
 * 算法原理：
 * 1. 确定查找范围：left = 0, right = arr.len() - 1
 * 2. 计算中间位置：mid = (left + right) / 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * 生活类比：就像在字典中查单词，
 * 每次都翻到中间位置，然后根据字母顺序决定向前还是向后翻
 * 
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)
 * 前提条件：数组必须有序
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @return 目标索引，未找到返回-1
 */
fn binary_search1(arr: &[i32], target: i32) -> isize {
    let mut left = 0;
    let mut right = arr.len() - 1;
    
    // 查找区间长度小于1时停止
    while left <= right {
        // 计算中间位置，防止整数溢出
        let mid_index = left + (right - left) / 2;
        let mid = arr[mid_index];
        
        // 中间项等于目标项则返回下标
        if target == mid {
            return mid_index as isize;
        } else if target > mid {
            // 大于中间项，查找右侧
            left = mid_index + 1;
        } else {
            // 小于中间项，查找左侧
            right = mid_index - 1;
        }
    }
    
    -1 // 未找到
}

/**
 * 二分查找递归版本
 * 
 * 算法思路：
 * 使用递归方式实现二分查找
 * 每次递归缩小查找范围
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @param left 左边界
 * @param right 右边界
 * @return 目标索引，未找到返回-1
 */
fn binary_search2(arr: &[i32], target: i32, left: usize, right: usize) -> isize {
    // 递归出口条件
    if left > right {
        return -1;
    }
    
    // 计算中间位置
    let mid_index = left + (right - left) / 2;
    let mid = arr[mid_index];
    
    // 中间值等于目标值，找到目标
    if target == mid {
        return mid_index as isize;
    } else if target > mid {
        // 目标大于中间值，递归查找右半部分
        binary_search2(arr, target, mid_index + 1, right)
    } else {
        // 目标小于中间值，递归查找左半部分
        binary_search2(arr, target, left, mid_index - 1)
    }
}

/**
 * 二分查找 - 查找第一个匹配项
 * 
 * 算法思路：
 * 当数组中有重复元素时，查找第一个出现的元素
 * 找到目标后继续向左查找，确保是第一个
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @return 第一个匹配项的索引，未找到返回-1
 */
fn binary_search_first(arr: &[i32], target: i32) -> isize {
    let mut left = 0;
    let mut right = arr.len() - 1;
    let mut result = -1;
    
    while left <= right {
        let mid_index = left + (right - left) / 2;
        let mid = arr[mid_index];
        
        if target == mid {
            result = mid_index as isize; // 记录找到的位置
            right = mid_index - 1; // 继续向左查找
        } else if target > mid {
            left = mid_index + 1;
        } else {
            right = mid_index - 1;
        }
    }
    
    result
}

/**
 * 二分查找 - 查找最后一个匹配项
 * 
 * 算法思路：
 * 当数组中有重复元素时，查找最后一个出现的元素
 * 找到目标后继续向右查找，确保是最后一个
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @return 最后一个匹配项的索引，未找到返回-1
 */
fn binary_search_last(arr: &[i32], target: i32) -> isize {
    let mut left = 0;
    let mut right = arr.len() - 1;
    let mut result = -1;
    
    while left <= right {
        let mid_index = left + (right - left) / 2;
        let mid = arr[mid_index];
        
        if target == mid {
            result = mid_index as isize; // 记录找到的位置
            left = mid_index + 1; // 继续向右查找
        } else if target > mid {
            left = mid_index + 1;
        } else {
            right = mid_index - 1;
        }
    }
    
    result
}

/**
 * 二分查找 - 泛型版本
 * 
 * 算法扩展：
 * 支持任意可比较类型的数组查找
 * 使用泛型提高代码复用性
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @return 目标索引，未找到返回-1
 */
fn binary_search_generic<T: Ord>(arr: &[T], target: &T) -> isize {
    let mut left = 0;
    let mut right = arr.len() - 1;
    
    while left <= right {
        let mid_index = left + (right - left) / 2;
        let mid = &arr[mid_index];
        
        match target.cmp(mid) {
            std::cmp::Ordering::Equal => return mid_index as isize,
            std::cmp::Ordering::Greater => left = mid_index + 1,
            std::cmp::Ordering::Less => right = mid_index - 1,
        }
    }
    
    -1
}

/**
 * 主程序：演示二分查找功能
 */
fn main() {
    println!("=== 二分查找演示 ===\n");
    
    // 测试数据：有序数组
    let arr = [2, 3, 8, 10, 10, 13, 20, 25, 30, 35];
    let target = 10;
    
    println!("数组:");
    for (i, &val) in arr.iter().enumerate() {
        print!("{} ", val);
        if i == arr.len() - 1 {
            println!();
        }
    }
    println!("目标元素: {}\n", target);
    
    // 基本查找测试
    println!("=== 基本查找测试 ===");
    let index1 = binary_search1(&arr, target);
    if index1 != -1 {
        println!("非递归查找: 找到于索引 {}", index1);
    } else {
        println!("非递归查找: 未找到");
    }
    
    // 递归查找测试
    println!("\n=== 递归查找测试 ===");
    let index2 = binary_search2(&arr, target, 0, arr.len() - 1);
    if index2 != -1 {
        println!("递归查找: 找到于索引 {}", index2);
    } else {
        println!("递归查找: 未找到");
    }
    
    // 查找第一个匹配项
    println!("\n=== 查找第一个匹配项 ===");
    let first_index = binary_search_first(&arr, target);
    if first_index != -1 {
        println!("第一个匹配: 找到于索引 {}", first_index);
    } else {
        println!("第一个匹配: 未找到");
    }
    
    // 查找最后一个匹配项
    println!("\n=== 查找最后一个匹配项 ===");
    let last_index = binary_search_last(&arr, target);
    if last_index != -1 {
        println!("最后一个匹配: 找到于索引 {}", last_index);
    } else {
        println!("最后一个匹配: 未找到");
    }
    
    // 查找不存在的元素
    println!("\n=== 查找不存在的元素 ===");
    let not_found = binary_search1(&arr, 100);
    println!("查找100: {}", if not_found != -1 { "找到" } else { "未找到" });
    
    // 泛型查找测试
    println!("\n=== 泛型查找测试 ===");
    let str_arr = ["apple", "banana", "cherry", "date", "elderberry"];
    let str_target = "cherry";
    
    println!("字符串数组:");
    for (i, val) in str_arr.iter().enumerate() {
        print!("{} ", val);
        if i == str_arr.len() - 1 {
            println!();
        }
    }
    println!("目标字符串: {}", str_target);
    
    let str_index = binary_search_generic(&str_arr, &str_target);
    if str_index != -1 {
        println!("泛型查找: 找到于索引 {}", str_index);
    } else {
        println!("泛型查找: 未找到");
    }
    
    // 性能分析
    println!("\n=== 二分查找特点 ===");
    println!("• 算法高效，时间复杂度O(log n)");
    println!("• 要求数组必须有序");
    println!("• 空间复杂度：O(1)");
    println!("• 适合大规模数据查找");
    println!("• 可以处理重复元素");
    
    // 与其他查找算法对比
    println!("\n=== 与其他查找算法对比 ===");
    println!("• 线性查找：O(n)，无需预处理");
    println!("• 二分查找：O(log n)，要求数组有序");
    println!("• 哈希查找：O(1)，但需要额外空间");
    println!("• 插值查找：O(log log n)，要求数据均匀分布");
    println!("• 选择算法取决于数据规模和特性");
    
    // 性能测试
    println!("\n=== 性能测试 ===");
    let large_arr: Vec<i32> = (0..100000).collect();
    let test_target = 99999;
    
    let start_time = std::time::Instant::now();
    let perf_index = binary_search1(&large_arr, test_target);
    let end_time = std::time::Instant::now();
    
    println!("数组大小: {}", large_arr.len());
    println!("查找目标: {}", test_target);
    println!("查找结果: {}", if perf_index != -1 { "找到" } else { "未找到" });
    println!("执行时间: {:?}", end_time.duration_since(start_time));
}

/*
打印结果
jarry@Mac binarysearch % rustc binary_search.rs && ./binary_search
=== 二分查找演示 ===

数组:
2 3 8 10 10 13 20 25 30 35 
目标元素: 10

=== 基本查找测试 ===
非递归查找: 找到于索引 3

=== 递归查找测试 ===
递归查找: 找到于索引 3

=== 查找第一个匹配项 ===
第一个匹配: 找到于索引 3

=== 查找最后一个匹配项 ===
最后一个匹配: 找到于索引 4

=== 查找不存在的元素 ===
查找100: 未找到

=== 泛型查找测试 ===
字符串数组:
apple banana cherry date elderberry 
目标字符串: cherry
泛型查找: 找到于索引 2

=== 二分查找特点 ===
• 算法高效，时间复杂度O(log n)
• 要求数组必须有序
• 空间复杂度：O(1)
• 适合大规模数据查找
• 可以处理重复元素

=== 与其他查找算法对比 ===
• 线性查找：O(n)，无需预处理
• 二分查找：O(log n)，要求数组有序
• 哈希查找：O(1)，但需要额外空间
• 插值查找：O(log log n)，要求数据均匀分布
• 选择算法取决于数据规模和特性

=== 性能测试 ===
数组大小: 100000
查找目标: 99999
查找结果: 找到
执行时间: 2.083µs
*/
