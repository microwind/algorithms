/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::time::Instant;

/**
 * 桶排序支持负数版本 - 负数放在第1个桶里排序
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值（取绝对值）
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 将元素分配到对应桶中，负数统一放在第1个桶
 * 4. 在每个桶内进行插入排序
 * 5. 合并所有桶的元素
 * 
 * 特点：
 * - 支持负数：负数统一放在第1个桶处理
 * - 插入排序：桶内使用插入排序
 * - 统一处理：使用绝对值计算桶分配
 */
fn bucket_sort1(arr: &mut Vec<i32>) -> Vec<i32> {
    println!("bucketSort1 with negative numbers:");
    
    if arr.len() <= 1 {
        println!("{:?}", arr);
        return arr.clone();
    }
    
    // 第一步：计算数组最大值和最小值（取绝对值）
    let mut max = arr[0];
    let mut min = arr[0];
    for &item in arr.iter() {
        if item.abs() > max.abs() {
            max = item;
        }
        if item.abs() < min.abs() {
            min = item;
        }
    }

    // 第二步：计算桶的数量和大小
    let min_abs = if min.abs() == 0 { 1 } else { min.abs() }; // 防止除零
    let bucket_count = (max.abs() - min_abs) / min_abs + 2; // +2是为了包含负数桶
    let bucket_size = min_abs;
    
    // 第三步：初始化桶
    let mut buckets: Vec<Vec<i32>> = Vec::with_capacity(bucket_count as usize);
    for _ in 0..bucket_count {
        buckets.push(Vec::new());
    }

    // 第四步：将元素分配到对应桶中
    for &item in arr.iter() {
        let bucket_index = if item < 0 {
            0 // 负数统一放在第1个桶
        } else {
            ((item - min) / bucket_size + 1) as usize // 正数从第2个桶开始
        };
        
        // 边界检查
        let bucket_index = bucket_index.min(buckets.len() - 1);
        
        // 插入排序到桶中
        let bucket = &mut buckets[bucket_index];
        let pos = bucket.iter().position(|&x| x > item).unwrap_or(bucket.len());
        bucket.insert(pos, item);
    }

    // 第五步：合并所有桶的元素
    let mut output = Vec::new();
    for bucket in buckets {
        for item in bucket {
            output.push(item);
        }
    }
    
    println!("{:?}", output);
    output
}

/**
 * 桶排序正数专用版本 - 只处理正数的桶排序
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值（只考虑正数）
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 将正数元素分配到对应桶中
 * 4. 在每个桶内进行插入排序
 * 5. 合并所有桶的元素
 * 
 * 特点：
 * - 正数专用：专门为正数优化
 * - 精确分配：桶分配更精确
 * - 性能较好：减少不必要的计算
 */
fn bucket_sort2(arr: &mut Vec<i32>) -> Vec<i32> {
    println!("bucketSort2 positive numbers only:");
    
    if arr.len() <= 1 {
        println!("{:?}", arr);
        return arr.clone();
    }
    
    // 第一步：计算数组最大值和最小值
    let mut max = arr[0];
    let mut min = arr[0];
    for &item in arr.iter() {
        if item > max {
            max = item;
        }
        if item < min {
            min = item;
        }
    }

    // 第二步：计算桶的数量和大小
    let min_positive = if min <= 0 { 1 } else { min }; // 防止除零
    let bucket_count = ((max - min_positive) / min_positive + 1) as usize;
    let bucket_size = min_positive;
    
    // 第三步：初始化桶
    let mut buckets: Vec<Vec<i32>> = Vec::with_capacity(bucket_count);
    for _ in 0..bucket_count {
        buckets.push(Vec::new());
    }

    // 第四步：将元素分配到对应桶中
    for &item in arr.iter() {
        let mut bucket_index = if item < 0 {
            0 // 负数统一放在第1个桶
        } else {
            ((item - min_positive) / bucket_size + 1) as usize // 正数从第2个桶开始
        };
        
        // 边界检查
        bucket_index = bucket_index.min(bucket_count - 1);
        
        // 插入排序到桶中
        let bucket = &mut buckets[bucket_index];
        let pos = bucket.iter().position(|&x| x > item).unwrap_or(bucket.len());
        bucket.insert(pos, item);
    }

    // 第五步：合并所有桶的元素
    let mut output = Vec::new();
    for bucket in buckets {
        for item in bucket {
            output.push(item);
        }
    }
    
    println!("{:?}", output);
    output
}

/**
 * 桶排序挪动排序版本 - 使用挪动插入保持排序稳定性
 * 
 * 算法原理：
 * 1. 手动遍历计算数组最大值和最小值
 * 2. 根据数组长度计算桶的数量和大小
 * 3. 将元素分配到对应桶中，支持负数
 * 4. 使用挪动排序而非数组修改进行桶内排序
 * 5. 合并所有桶的元素
 * 
 * 特点：
 * - 挪动排序：使用挪动插入而非直接修改
 * - 排序稳定：保持相等元素的相对位置
 * - 支持负数：负数统一处理
 */
fn bucket_sort3(arr: &mut Vec<i32>) -> Vec<i32> {
    println!("bucketSort3 with move sorting:");
    
    if arr.len() <= 1 {
        println!("{:?}", arr);
        return arr.clone();
    }
    
    // 第一步：计算数组最大值和最小值
    let mut max = arr[0];
    let mut min = arr[0];
    for &item in arr.iter() {
        if item > max {
            max = item;
        }
        if item < min {
            min = item;
        }
    }

    // 第二步：计算桶的数量和大小
    let bucket_count = arr.len(); // 桶数量等于数组长度
    let bucket_size = (max - min) / bucket_count as i32 + 1;
    
    // 第三步：初始化桶
    let mut buckets: Vec<Vec<i32>> = Vec::with_capacity(bucket_count);
    for _ in 0..bucket_count {
        buckets.push(Vec::new());
    }

    // 第四步：将元素分配到对应桶中
    for &item in arr.iter() {
        let mut bucket_index = ((item - min) / bucket_size) as usize;
        
        // 边界检查
        bucket_index = bucket_index.min(bucket_count - 1);
        
        // 挪动插入到桶中
        let bucket = &mut buckets[bucket_index];
        let pos = bucket.iter().position(|&x| x > item).unwrap_or(bucket.len());
        bucket.insert(pos, item);
    }

    // 第五步：合并所有桶的元素
    let mut output = Vec::new();
    for bucket in buckets {
        for item in bucket {
            output.push(item);
        }
    }
    
    println!("{:?}", output);
    output
}

/**
 * 桶排序负数单独版本 - 负数单独优化处理
 * 
 * 算法原理：
 * 1. 分别处理正数和负数
 * 2. 负数转换为正数进行桶排序
 * 3. 正数正常进行桶排序
 * 4. 合并负数（逆序）和正数
 * 
 * 特点：
 * - 负数单独：负数单独优化处理
 * - 排序精确：更精确的排序逻辑
 * - 分类处理：正负数分别优化
 */
fn bucket_sort4(arr: &mut Vec<i32>) -> Vec<i32> {
    println!("bucketSort4 separate negative sorting:");
    
    if arr.len() <= 1 {
        println!("{:?}", arr);
        return arr.clone();
    }
    
    // 第一步：分离正数和负数
    let mut positive = Vec::new();
    let mut negative = Vec::new();
    
    for &item in arr.iter() {
        if item >= 0 {
            positive.push(item);
        } else {
            negative.push(-item); // 负数转为正数
        }
    }

    // 第二步：分别排序正数和负数
    if !positive.is_empty() {
        positive = bucket_sort1(&mut positive);
    }
    if !negative.is_empty() {
        negative = bucket_sort1(&mut negative);
    }

    // 第三步：合并结果（负数要逆序并还原符号）
    let mut output = Vec::new();
    for &item in negative.iter().rev() {
        output.push(-item);
    }
    for &item in positive.iter() {
        output.push(item);
    }
    
    println!("{:?}", output);
    output
}

/**
 * 桶排序实时冒泡版本 - 插入即排序，实时保持有序
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值
 * 2. 初始化桶
 * 3. 将元素分配到桶中，立即进行冒泡排序
 * 4. 合并所有桶的元素
 * 
 * 特点：
 * - 实时排序：插入即排序
 * - 冒泡优化：使用冒泡排序维护有序性
 * - 即时维护：实时保持桶内有序
 */
fn bucket_sort5(arr: &mut Vec<i32>) -> Vec<i32> {
    println!("bucketSort5 real-time bubble sorting:");
    
    if arr.len() <= 1 {
        println!("{:?}", arr);
        return arr.clone();
    }
    
    // 第一步：计算数组最大值和最小值
    let mut max = arr[0];
    let mut min = arr[0];
    for &item in arr.iter() {
        if item > max {
            max = item;
        }
        if item < min {
            min = item;
        }
    }

    // 第二步：计算桶的数量和大小
    let min_positive = if min <= 0 { 1 } else { min }; // 防止除零
    let bucket_count = ((max - min_positive) / min_positive + 1) as usize;
    let bucket_size = min_positive;
    
    // 第三步：初始化桶
    let mut buckets: Vec<Vec<i32>> = Vec::with_capacity(bucket_count);
    for _ in 0..bucket_count {
        buckets.push(Vec::new());
    }

    // 第四步：将元素分配到对应桶中，实时冒泡排序
    for &item in arr.iter() {
        let mut bucket_index = if item < 0 {
            0 // 负数统一放在第1个桶
        } else {
            ((item - min_positive) / bucket_size + 1) as usize // 正数从第2个桶开始
        };
        
        // 边界检查
        bucket_index = bucket_index.min(bucket_count - 1);
        
        // 直接添加到桶末尾
        let bucket = &mut buckets[bucket_index];
        bucket.push(item);
        
        // 实时冒泡排序
        let mut j = bucket.len() - 1;
        while j > 0 && bucket[j] < bucket[j - 1] {
            bucket.swap(j, j - 1);
            j -= 1;
        }
    }

    // 第五步：合并所有桶的元素
    let mut output = Vec::new();
    for bucket in buckets {
        for item in bucket {
            output.push(item);
        }
    }
    
    println!("{:?}", output);
    output
}

/**
 * 桶排序原版标准版本 - 来自bucket_sort_old.rs的标准实现
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 将元素分配到对应桶中
 * 4. 对每个桶进行排序
 * 5. 合并所有桶的元素
 * 
 * 特点：
 * - 原版标准：经典的桶排序算法
 * - 简单直接：直接使用sort()排序
 * - 高效实现：减少不必要的复杂性
 */
fn bucket_sort6(arr: &mut Vec<i32>) -> Vec<i32> {
    println!("bucketSort6 original standard version:");
    
    if arr.is_empty() {
        println!("{:?}", arr);
        return arr.clone();
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

    // 对每个桶进行排序，并合并结果
    let mut output = Vec::new();
    for bucket in buckets.iter_mut() {
        bucket.sort();
        for &item in bucket.iter() {
            output.push(item);
        }
    }

    println!("{:?}", output);
    output
}

/**
 * 桶排序原版标志位版本 - 来自bucket_sort_old.rs的标志位实现
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 创建指定数量的桶
 * 4. 将元素分配到对应桶中
 * 5. 对每个桶进行排序
 * 6. 合并所有桶的元素
 * 
 * 特点：
 * - 原版标志位：使用固定桶数量的实现
 * - 桶数量控制：可控制桶的数量
 * - 负载均衡：更好的数据分布
 */
fn bucket_sort7(arr: &mut Vec<i32>) -> Vec<i32> {
    println!("bucketSort7 original flag version:");
    
    if arr.is_empty() || arr.len() == 0 {
        println!("{:?}", arr);
        return arr.clone();
    }

    let max_val = *arr.iter().max().unwrap();
    let min_val = *arr.iter().min().unwrap();
    let range = (max_val - min_val) as f64;
    let bucket_size = (range / 5.0).ceil() as i32 + 1; // 使用5个桶

    // 创建指定数量的桶
    let mut buckets: Vec<Vec<i32>> = vec![Vec::new(); 5];

    // 将元素放入对应的桶中
    for &item in arr.iter() {
        let mut idx = ((item - min_val) / bucket_size) as usize;
        idx = idx.min(4); // 确保索引在0-4范围内
        buckets[idx].push(item);
    }

    // 对每个桶进行排序，并合并结果
    let mut output = Vec::new();
    for bucket in buckets.iter_mut() {
        bucket.sort();
        for &item in bucket.iter() {
            output.push(item);
        }
    }

    println!("{:?}", output);
    output
}

/**
 * 性能测试函数 - 统一测试所有桶排序版本
 */
fn performance_test(test_data: &Vec<i32>) {
    println!("=== 桶排序算法演示 ===\n");
    
    println!("arrData origin: {:?}", test_data);
    
    // 测试1: bucket_sort1
    let start = Instant::now();
    let result1 = bucket_sort1(&mut test_data.clone());
    let elapsed1 = start.elapsed();
    println!("bucketSort1: {:.3}ms", elapsed1.as_millis());
    println!("排序结果: {:?}", result1);
    
    println!("\n");
    
    // 测试2: bucket_sort2
    let start = Instant::now();
    println!("arrData origin: {:?}", test_data);
    let result2 = bucket_sort2(&mut test_data.clone());
    let elapsed2 = start.elapsed();
    println!("bucketSort2: {:.3}ms", elapsed2.as_millis());
    println!("排序结果: {:?}", result2);
    
    println!("\n");
    
    // 测试3: bucket_sort3
    let start = Instant::now();
    println!("arrData origin: {:?}", test_data);
    let result3 = bucket_sort3(&mut test_data.clone());
    let elapsed3 = start.elapsed();
    println!("bucketSort3: {:.3}ms", elapsed3.as_millis());
    println!("排序结果: {:?}", result3);
    
    println!("\n");
    
    // 测试4: bucket_sort4
    let start = Instant::now();
    println!("arrData origin: {:?}", test_data);
    let result4 = bucket_sort4(&mut test_data.clone());
    let elapsed4 = start.elapsed();
    println!("bucketSort4: {:.3}ms", elapsed4.as_millis());
    println!("排序结果: {:?}", result4);
    
    println!("\n");
    
    // 测试5: bucket_sort5
    let start = Instant::now();
    println!("arrData origin: {:?}", test_data);
    let result5 = bucket_sort5(&mut test_data.clone());
    let elapsed5 = start.elapsed();
    println!("bucketSort5: {:.3}ms", elapsed5.as_millis());
    println!("排序结果: {:?}", result5);
    
    println!("\n");
    
    // 测试6: bucket_sort6
    let start = Instant::now();
    println!("arrData origin: {:?}", test_data);
    let result6 = bucket_sort6(&mut test_data.clone());
    let elapsed6 = start.elapsed();
    println!("bucketSort6: {:.3}ms", elapsed6.as_millis());
    println!("排序结果: {:?}", result6);
    
    println!("\n");
    
    // 测试7: bucket_sort7
    let start = Instant::now();
    println!("arrData origin: {:?}", test_data);
    let result7 = bucket_sort7(&mut test_data.clone());
    let elapsed7 = start.elapsed();
    println!("bucketSort7: {:.3}ms", elapsed7.as_millis());
    println!("排序结果: {:?}", result7);
    
    println!("\n=== 算法对比总结 ===");
    println!("1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理");
    println!("2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好");
    println!("3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性");
    println!("4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确");
    println!("5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序");
    println!("6. 原版标准版本：bucketSort6 - 原版标准桶排序实现，直接排序");
    println!("7. 原版标志位版本：bucketSort7 - 原版标志位实现，固定桶数量");
}

fn main() {
    let arr_data = vec![20, 11, 0, -10, 9, 6, 30, 15, 13, 80];
    
    performance_test(&arr_data);
}

/* 打印结果
jarry@Mac bucketsort % rustc bucket_sort.rs && ./bucket_sort
=== 桶排序算法演示 ===

arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort1 with negative numbers:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort1: 0ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort2 positive numbers only:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort2: 0ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort3 with move sorting:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort3: 0ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort4 separate negative sorting:
bucketSort1 with negative numbers:
[0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort1 with negative numbers:
[10]
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort4: 0ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort5 real-time bubble sorting:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort5: 0ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort6 original standard version:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort6: 0ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort7 original flag version:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort7: 0ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理
2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好
3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性
4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确
5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序
6. 原版标准版本：bucketSort6 - 原版标准桶排序实现，直接排序
7. 原版标志位版本：bucketSort7 - 原版标志位实现，固定桶数量
*/
