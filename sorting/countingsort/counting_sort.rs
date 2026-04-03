/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 计数排序算法实现
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

// 测试数据：包含负数和重复元素的典型数组
const TEST_DATA: [i32; 12] = [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80];

/**
 * 计数排序基础版本 - 标准实现
 * 
 * 算法原理：
 * 第一步：找到最小值和最大值，确定数据范围
 * 第二步：创建计数数组，统计每个元素出现的次数
 * 第三步：计算累计计数以确定元素位置
 * 第四步：从后向前遍历，根据累计计数将元素放到正确位置
 * 
 * 生活类比：就像统计班级学生成绩分布，
 * 先统计每个分数段有多少人，然后按分数段排序
 * 
 * 时间复杂度：O(n + k)，n为元素个数，k为数据范围
 * 空间复杂度：O(k) - 需要计数数组
 * 稳定性：稳定 - 从后向前遍历保持相等元素的相对位置
 */
fn counting_sort1(arr: &mut Vec<i32>) {
    println!("countingSort1 standard:");
    
    if arr.is_empty() {
        return;
    }
    
    // 第一步：找到最小值和最大值，确定数据范围
    let min = *arr.iter().min().unwrap();
    let max = *arr.iter().max().unwrap();
    let range = max - min + 1;
    
    // 第二步：创建计数数组，统计每个元素出现的次数
    let mut count = vec![0; range as usize];
    
    // 统计每个元素出现的次数
    for &value in arr.iter() {
        // 将元素值转换为计数数组索引（支持负数）
        count[(value - min) as usize] += 1;
    }
    
    // 第三步：计算累计计数以确定元素位置
    for i in 1..count.len() {
        count[i] += count[i - 1];
    }
    
    // 第四步：从后向前遍历，根据累计计数将元素放到正确位置
    let mut output = vec![0; arr.len()];
    
    // 从后向前遍历，保证稳定性
    for i in (0..arr.len()).rev() {
        let value = arr[i];
        let index = (value - min) as usize;
        // 根据累计计数确定最终位置
        output[count[index] - 1] = value;
        // 减少计数，为重复元素预留位置
        count[index] -= 1;
    }
    
    // 复制回原数组
    for i in 0..arr.len() {
        arr[i] = output[i];
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 计数排序优化版本 - 内存优化
 * 
 * 算法思路：
 * 第一步：找到最小值和最大值，确定数据范围
 * 第二步：创建计数数组，统计每个元素出现的次数
 * 第三步：直接根据计数重构数组，省去累加步骤
 * 
 * 优化效果：
 * - 减少额外空间使用
 * - 更好的缓存性能
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：不稳定 - 原地修改可能影响稳定性
 */
fn counting_sort2(arr: &mut Vec<i32>) {
    println!("countingSort2 memory optimized:");
    
    if arr.is_empty() {
        return;
    }
    
    // 第一步：找到最小值和最大值，确定数据范围
    let min = *arr.iter().min().unwrap();
    let max = *arr.iter().max().unwrap();
    let range = max - min + 1;
    
    // 第二步：创建计数数组，统计每个元素出现的次数
    let mut count = vec![0; range as usize];
    
    // 统计每个元素出现的次数
    for &value in arr.iter() {
        // 将元素值转换为计数数组索引（支持负数）
        count[(value - min) as usize] += 1;
    }
    
    // 第三步：直接根据计数重构数组，省去累加步骤
    let mut index = 0;
    for (i, &count_value) in count.iter().enumerate() {
        let mut remaining = count_value;
        // 根据计数值重复放入元素
        while remaining > 0 {
            // 将索引转换回原值并放入数组
            arr[index] = (i as i32) + min;
            index += 1;
            remaining -= 1;
        }
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 计数排序 - 负数单独处理版本
 * 
 * 算法思路：
 * 第一步：分离正数和负数，分别处理
 * 第二步：对负数部分转换为绝对值进行排序，然后反转并恢复负号
 * 第三步：对正数部分使用标准计数排序
 * 第四步：合并排序后的负数和正数部分
 * 
 * 优化效果：
 * - 支持负数排序
 * - 保持算法稳定性
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 */
fn counting_sort3(arr: &mut Vec<i32>) {
    println!("countingSort3 negative numbers:");
    
    if arr.is_empty() {
        return;
    }
    
    // 第一步：分离正数和负数，分别处理
    let mut negatives = Vec::new();
    let mut positives = Vec::new();
    
    for &value in arr.iter() {
        if value < 0 {
            negatives.push(value);
        } else {
            positives.push(value);
        }
    }
    
    // 第二步：对负数部分转换为绝对值进行排序，然后反转并恢复负号
    if !negatives.is_empty() {
        let abs_negatives: Vec<i32> = negatives.iter().map(|&x| -x).collect();
        
        // 使用独立的计数排序逻辑
        if !abs_negatives.is_empty() {
            // 找到最小值和最大值
            let min = *abs_negatives.iter().min().unwrap();
            let max = *abs_negatives.iter().max().unwrap();
            let range = max - min + 1;
            
            // 创建计数数组
            let mut count = vec![0; range as usize];
            
            // 统计每个元素出现的次数
            for &value in abs_negatives.iter() {
                count[(value - min) as usize] += 1;
            }
            
            // 计算累计计数
            for i in 1..count.len() {
                count[i] += count[i - 1];
            }
            
            // 从后向前遍历，保证稳定性
            let mut output = vec![0; abs_negatives.len()];
            for i in (0..abs_negatives.len()).rev() {
                let value = abs_negatives[i];
                let index = (value - min) as usize;
                output[count[index] - 1] = value;
                count[index] -= 1;
            }
            
            // 反转并恢复负号（负数排序后应该是从大到小，所以要反转）
            for i in 0..output.len() {
                negatives[i] = -output[output.len() - 1 - i];
            }
        }
    }
    
    // 第三步：对正数部分使用标准计数排序
    if !positives.is_empty() {
        // 使用独立的计数排序逻辑
        if !positives.is_empty() {
            // 找到最小值和最大值
            let min = *positives.iter().min().unwrap();
            let max = *positives.iter().max().unwrap();
            let range = max - min + 1;
            
            // 创建计数数组
            let mut count = vec![0; range as usize];
            
            // 统计每个元素出现的次数
            for &value in positives.iter() {
                count[(value - min) as usize] += 1;
            }
            
            // 计算累计计数
            for i in 1..count.len() {
                count[i] += count[i - 1];
            }
            
            // 从后向前遍历，保证稳定性
            let mut output = vec![0; positives.len()];
            for i in (0..positives.len()).rev() {
                let value = positives[i];
                let index = (value - min) as usize;
                output[count[index] - 1] = value;
                count[index] -= 1;
            }
            
            // 复制回正数数组
            for i in 0..output.len() {
                positives[i] = output[i];
            }
        }
    }
    
    // 第四步：合并排序后的负数和正数部分
    let mut result = Vec::new();
    result.extend_from_slice(&negatives);
    result.extend_from_slice(&positives);
    
    // 复制回原数组
    for i in 0..arr.len() {
        arr[i] = result[i];
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 计数排序 - 桶优化版本
 * 
 * 算法思路：
 * 第一步：找到最小值和最大值，确定数据范围和桶参数
 * 第二步：创建多个桶，将相近的数值分组
 * 第三步：对每个桶进行计数排序
 * 第四步：合并所有桶的排序结果
 * 
 * 优化效果：
 * - 减少内存使用
 * - 提高处理稀疏数据的效率
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 */
fn counting_sort4(arr: &mut Vec<i32>) {
    println!("countingSort4 bucket optimized:");
    
    if arr.is_empty() {
        return;
    }
    
    // 第一步：找到最小值和最大值，确定数据范围和桶参数
    let min = *arr.iter().min().unwrap();
    let max = *arr.iter().max().unwrap();
    let range = max - min + 1;
    
    // 确定桶的大小（可以调整以优化性能）
    let bucket_size = std::cmp::max(1, range / 10);
    let bucket_count = (range + bucket_size - 1) / bucket_size;
    
    // 第二步：创建多个桶，将相近的数值分组
    let mut buckets: Vec<Vec<i32>> = vec![Vec::new(); bucket_count as usize];
    
    // 将元素分配到桶中
    for &value in arr.iter() {
        // 根据值计算桶索引
        let bucket_index = (value - min) / bucket_size;
        buckets[bucket_index as usize].push(value);
    }
    
    // 第三步：对每个桶进行计数排序
    // 第四步：合并所有桶的排序结果
    let mut result = Vec::new();
    
    for bucket in buckets.iter_mut() {
        if !bucket.is_empty() {
            // 使用独立的计数排序逻辑
            if !bucket.is_empty() {
                // 找到最小值和最大值
                let min = *bucket.iter().min().unwrap();
                let max = *bucket.iter().max().unwrap();
                let range = max - min + 1;
                
                // 创建计数数组
                let mut count = vec![0; range as usize];
                
                // 统计每个元素出现的次数
                for &value in bucket.iter() {
                    count[(value - min) as usize] += 1;
                }
                
                // 计算累计计数
                for i in 1..count.len() {
                    count[i] += count[i - 1];
                }
                
                // 从后向前遍历，保证稳定性
                let mut output = vec![0; bucket.len()];
                for i in (0..bucket.len()).rev() {
                    let value = bucket[i];
                    let index = (value - min) as usize;
                    output[count[index] - 1] = value;
                    count[index] -= 1;
                }
                
                // 复制回桶
                for i in 0..output.len() {
                    bucket[i] = output[i];
                }
            }
            
            // 第四步：合并所有桶的排序结果
            result.extend_from_slice(bucket);
        }
    }
    
    // 复制回原数组
    for i in 0..arr.len() {
        arr[i] = result[i];
    }
    
    print_array(arr, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

fn main() {
    // 测试1：标准版本
    performance_test(counting_sort1, &TEST_DATA, "标准版本");

    // 测试2：内存优化版本
    performance_test(counting_sort2, &TEST_DATA, "内存优化版本");

    // 测试3：负数处理版本
    performance_test(counting_sort3, &TEST_DATA, "负数处理版本");

    // 测试4：桶优化版本
    performance_test(counting_sort4, &TEST_DATA, "桶优化版本");

    println!("=== 算法对比总结 ===");
    println!("1. 标准版本：经典实现，稳定排序");
    println!("2. 内存优化版本：原地修改，节省空间");
    println!("3. 负数处理版本：支持负数，功能完整");
    println!("4. 桶优化版本：分组处理，适合稀疏数据");
}

/*
打印结果
jarry@Mac countingsort % rustc counting_sort.rs && ./counting_sort
标准版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort1 standard:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
标准版本: 0.000ms
标准版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

内存优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort2 memory optimized:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
内存优化版本: 0.000ms
内存优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

负数处理版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort3 negative numbers:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
负数处理版本: 0.000ms
负数处理版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

桶优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort4 bucket optimized:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
桶优化版本: 0.000ms
桶优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 标准版本：经典实现，稳定排序
2. 内存优化版本：原地修改，节省空间
3. 负数处理版本：支持负数，功能完整
4. 桶优化版本：分组处理，适合稀疏数据
*/
