/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 线性查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

/**
 * 线性查找基础版本 - 查找第一个匹配项
 * 
 * 算法原理：
 * 1. 从数组开头逐个遍历元素
 * 2. 比较当前元素是否等于目标值
 * 3. 找到目标则返回索引，否则继续
 * 4. 遍历结束未找到则返回-1
 * 
 * 适用场景：
 * - 小规模数据集
 * - 无序数据
 * - 需要查找所有匹配项
 * 
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @return 找到返回索引，未找到返回-1
 */
fn linear_search(arr: &[i32], target: i32) -> isize {
    // 逐个遍历查找
    for (i, &value) in arr.iter().enumerate() {
        if value == target {
            return i as isize; // 找到目标，返回索引
        }
    }
    
    -1 // 未找到
}

/**
 * 线性查找 - 查找所有匹配项
 * 
 * 算法思路：
 * 遍历整个数组，收集所有匹配项的索引
 * 适合处理重复元素的情况
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @return 包含所有匹配索引的向量
 */
fn linear_search_all(arr: &[i32], target: i32) -> Vec<usize> {
    let mut result = Vec::new();
    
    // 逐个遍历查找所有匹配项
    for (i, &value) in arr.iter().enumerate() {
        if value == target {
            result.push(i);
        }
    }
    
    result
}

/**
 * 线性查找 - 带哨兵优化版本
 * 
 * 算法优化：
 * 在数组末尾设置哨兵（目标值）
 * 减少每次循环中的边界检查
 * 可以略微提高性能
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @return 找到返回索引，未找到返回-1
 */
fn linear_search_sentinel(arr: &mut Vec<i32>, target: i32) -> isize {
    if arr.is_empty() {
        return -1;
    }
    
    let last = arr[arr.len() - 1]; // 保存最后一个元素
    arr[arr.len() - 1] = target;   // 设置哨兵
    
    let mut i = 0;
    // 由于有哨兵，循环一定会终止
    while arr[i] != target {
        i += 1;
    }
    
    arr[arr.len() - 1] = last; // 恢复最后一个元素
    
    // 检查是否真的找到目标
    if i < arr.len() - 1 || arr[arr.len() - 1] == target {
        return i as isize;
    }
    
    -1
}

/**
 * 线性查找 - 反向查找版本
 * 
 * 算法思路：
 * 从数组末尾开始向前查找
 * 适合查找最后一个匹配项的场景
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @return 找到返回索引，未找到返回-1
 */
fn linear_search_reverse(arr: &[i32], target: i32) -> isize {
    // 从后向前遍历查找
    for i in (0..arr.len()).rev() {
        if arr[i] == target {
            return i as isize; // 找到目标，返回索引
        }
    }
    
    -1 // 未找到
}

/**
 * 线性查找 - 递归版本
 * 
 * 算法思路：
 * 使用递归方式实现线性查找
 * 每次递归处理一个元素
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @param index 当前索引
 * @return 找到返回索引，未找到返回-1
 */
fn linear_search_recursive(arr: &[i32], target: i32, index: usize) -> isize {
    // 递归出口条件
    if index >= arr.len() {
        return -1;
    }
    
    // 检查当前元素
    if arr[index] == target {
        return index as isize;
    }
    
    // 递归查找下一个元素
    linear_search_recursive(arr, target, index + 1)
}

/**
 * 线性查找 - 递归版本（公共接口）
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @return 找到返回索引，未找到返回-1
 */
fn linear_search_recursive_public(arr: &[i32], target: i32) -> isize {
    if arr.is_empty() {
        return -1;
    }
    
    linear_search_recursive(arr, target, 0)
}

/**
 * 线性查找 - 泛型版本
 * 
 * 算法扩展：
 * 支持任意类型的数组查找
 * 使用泛型提高代码复用性
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @return 找到返回索引，未找到返回-1
 */
fn linear_search_generic<T: PartialEq>(arr: &[T], target: &T) -> isize {
    // 逐个遍历查找
    for (i, value) in arr.iter().enumerate() {
        if value == target {
            return i as isize; // 找到目标，返回索引
        }
    }
    
    -1 // 未找到
}

/**
 * 主程序：演示线性查找功能
 */
fn main() {
    println!("=== 线性查找演示 ===\n");
    
    // 测试数据
    let arr = [64, 34, 25, 12, 22, 11, 90, 22];
    let target = 22;
    
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
    let index = linear_search(&arr, target);
    if index != -1 {
        println!("基本查找: 找到于索引 {}", index);
    } else {
        println!("基本查找: 未找到");
    }
    
    // 查找所有匹配项
    println!("\n=== 查找所有匹配项 ===");
    let all_indices = linear_search_all(&arr, target);
    print!("所有匹配位置: ");
    for (i, &idx) in all_indices.iter().enumerate() {
        print!("{} ", idx);
        if i == all_indices.len() - 1 {
            println!("(共{}个)", all_indices.len());
        }
    }
    
    // 反向查找测试
    println!("\n=== 反向查找测试 ===");
    let reverse_index = linear_search_reverse(&arr, target);
    if reverse_index != -1 {
        println!("反向查找: 找到于索引 {}", reverse_index);
    } else {
        println!("反向查找: 未找到");
    }
    
    // 哨兵查找测试
    println!("\n=== 哨兵查找测试 ===");
    let mut arr_copy = arr.to_vec();
    let sentinel_index = linear_search_sentinel(&mut arr_copy, target);
    if sentinel_index != -1 {
        println!("哨兵查找: 找到于索引 {}", sentinel_index);
    } else {
        println!("哨兵查找: 未找到");
    }
    
    // 递归查找测试
    println!("\n=== 递归查找测试 ===");
    let recursive_index = linear_search_recursive_public(&arr, target);
    if recursive_index != -1 {
        println!("递归查找: 找到于索引 {}", recursive_index);
    } else {
        println!("递归查找: 未找到");
    }
    
    // 查找不存在的元素
    println!("\n=== 查找不存在的元素 ===");
    let not_found = linear_search(&arr, 100);
    println!("查找100: {}", if not_found != -1 { "找到" } else { "未找到" });
    
    // 泛型查找测试
    println!("\n=== 泛型查找测试 ===");
    let str_arr = ["apple", "banana", "cherry", "date", "banana"];
    let str_target = "banana";
    
    println!("字符串数组:");
    for (i, &val) in str_arr.iter().enumerate() {
        print!("{} ", val);
        if i == str_arr.len() - 1 {
            println!();
        }
    }
    println!("目标字符串: {}", str_target);
    
    let str_index = linear_search_generic(&str_arr, &str_target);
    if str_index != -1 {
        println!("泛型查找: 找到于索引 {}", str_index);
    } else {
        println!("泛型查找: 未找到");
    }
    
    let mut str_all_indices = Vec::new();
    for (i, val) in str_arr.iter().enumerate() {
        if val == &str_target {
            str_all_indices.push(i);
        }
    }
    print!("所有匹配位置: ");
    for (i, &idx) in str_all_indices.iter().enumerate() {
        print!("{} ", idx);
        if i == str_all_indices.len() - 1 {
            println!("(共{}个)", str_all_indices.len());
        }
    }
    
    // 性能分析
    println!("\n=== 线性查找特点 ===");
    println!("• 算法简单，易于实现");
    println!("• 适用于小规模数据和无序数据");
    println!("• 时间复杂度：O(n)");
    println!("• 空间复杂度：O(1)");
    println!("• 可以查找所有匹配项");
    println!("• 适合处理重复元素");
    
    // 与其他查找算法对比
    println!("\n=== 与其他查找算法对比 ===");
    println!("• 二分查找：O(log n)，但要求数组有序");
    println!("• 哈希查找：O(1)，但需要额外空间");
    println!("• 线性查找：O(n)，但无需预处理");
    println!("• 选择算法取决于数据规模和是否有序");
    
    // 性能测试
    println!("\n=== 性能测试 ===");
    let large_arr: Vec<i32> = (0..10000).collect();
    let test_target = 9999;
    
    let start_time = std::time::Instant::now();
    let perf_index = linear_search(&large_arr, test_target);
    let end_time = std::time::Instant::now();
    
    println!("数组大小: {}", large_arr.len());
    println!("查找目标: {}", test_target);
    println!("查找结果: {}", if perf_index != -1 { "找到" } else { "未找到" });
    println!("执行时间: {:?}", end_time.duration_since(start_time));
}

/*
打印结果
jarry@Mac linear-search % rustc linear_search.rs && ./linear_search
=== 线性查找演示 ===

数组:
64 34 25 12 22 11 90 22 
目标元素: 22

=== 基本查找测试 ===
基本查找: 找到于索引 4

=== 查找所有匹配项 ===
所有匹配位置: 4 7 (共2个)

=== 反向查找测试 ===
反向查找: 找到于索引 7

=== 哨兵查找测试 ===
哨兵查找: 找到于索引 4

=== 递归查找测试 ===
递归查找: 找到于索引 4

=== 查找不存在的元素 ===
查找100: 未找到

=== 泛型查找测试 ===
字符串数组:
apple banana cherry date banana 
目标字符串: banana
泛型查找: 找到于索引 1
所有匹配位置: 1 4 (共2个)

=== 线性查找特点 ===
• 算法简单，易于实现
• 适用于小规模数据和无序数据
• 时间复杂度：O(n)
• 空间复杂度：O(1)
• 可以查找所有匹配项
• 适合处理重复元素

=== 与其他查找算法对比 ===
• 二分查找：O(log n)，但要求数组有序
• 哈希查找：O(1)，但需要额外空间
• 线性查找：O(n)，但无需预处理
• 选择算法取决于数据规模和是否有序

=== 性能测试 ===
数组大小: 10000
查找目标: 9999
查找结果: 找到
执行时间: 4.058µs
*/
