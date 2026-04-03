// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// CountingSort 计数排序算法实现
// 提供四种不同的实现方式，适合不同场景和性能需求

import Foundation

// printArray 打印数组内容的辅助函数
func printArray(_ arr: [Int], label: String) {
    print("\(label): \(arr)")
}

// performanceTest 性能测试辅助函数
func performanceTest(_ sortFunc: @escaping (inout [Int]) -> Void, arr: [Int], name: String) {
    // 创建数组副本，避免修改原数组
    var testArr = arr
    printArray(testArr, label: name + "原始数组")
    
    // 开始计时
    let startTime = CFAbsoluteTimeGetCurrent()
    sortFunc(&testArr)
    let endTime = CFAbsoluteTimeGetCurrent()
    
    let duration = (endTime - startTime) * 1000
    print("\(name): \(String(format: "%.3f", duration))")
    printArray(testArr, label: name + "排序结果")
    print("") // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含负数和重复元素的典型数组
let testData: [Int] = [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]

/**
 * 计数排序基础版本 - 标准实现
 * 
 * 算法原理：
 * 1. 统计每个元素出现的次数
 * 2. 计算累计计数以确定元素位置
 * 3. 根据累计计数将元素放到正确位置
 * 4. 从后向前遍历保证稳定性
 * 
 * 生活类比：就像统计班级学生成绩分布，
 * 先统计每个分数段有多少人，然后按分数段排序
 * 
 * 时间复杂度：O(n + k)，n为元素个数，k为数据范围
 * 空间复杂度：O(k) - 需要计数数组
 * 稳定性：稳定 - 从后向前遍历保持相等元素的相对位置
 */
func countingSort1(_ arr: inout [Int]) {
    print("countingSort1 standard:")
    
    if arr.isEmpty {
        return
    }
    
    // 找到最小值和最大值
    let min = arr.min()!
    let max = arr.max()!
    let range = max - min + 1
    
    // 创建计数数组
    var count = Array(repeating: 0, count: range)
    
    // 统计每个元素出现的次数
    for value in arr {
        count[value - min] += 1
    }
    
    // 计算累计计数
    for i in 1..<count.count {
        count[i] += count[i - 1]
    }
    
    // 创建输出数组
    var output = Array(repeating: 0, count: arr.count)
    
    // 从后向前遍历，保证稳定性
    for i in (0..<arr.count).reversed() {
        let value = arr[i]
        let index = value - min
        output[count[index] - 1] = value
        count[index] -= 1
    }
    
    // 复制回原数组
    for i in 0..<arr.count {
        arr[i] = output[i]
    }
    
    printArray(arr, label: "排序后数组")
}

/**
 * 计数排序优化版本 - 内存优化
 * 
 * 算法思路：
 * 直接在原数组上进行修改，减少内存使用
 * 使用原地排序技术
 * 
 * 优化效果：
 * - 减少额外空间使用
 * - 更好的缓存性能
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：不稳定 - 原地修改可能影响稳定性
 */
func countingSort2(_ arr: inout [Int]) {
    print("countingSort2 memory optimized:")
    
    if arr.isEmpty {
        return
    }
    
    // 找到最小值和最大值
    let min = arr.min()!
    let max = arr.max()!
    let range = max - min + 1
    
    // 创建计数数组
    var count = Array(repeating: 0, count: range)
    
    // 统计每个元素出现的次数
    for value in arr {
        count[value - min] += 1
    }
    
    // 直接根据计数重构数组
    var index = 0
    for (i, countValue) in count.enumerated() {
        var remaining = countValue
        while remaining > 0 {
            arr[index] = i + min
            index += 1
            remaining -= 1
        }
    }
    
    printArray(arr, label: "排序后数组")
}

/**
 * 计数排序 - 负数单独处理版本
 * 
 * 算法思路：
 * 专门处理包含负数的情况
 * 分别处理负数和正数部分
 * 
 * 优化效果：
 * - 支持负数排序
 * - 保持算法稳定性
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 */
func countingSort3(_ arr: inout [Int]) {
    print("countingSort3 negative numbers:")
    
    if arr.isEmpty {
        return
    }
    
    // 分离正数和负数
    var negatives = [Int]()
    var positives = [Int]()
    
    for value in arr {
        if value < 0 {
            negatives.append(value)
        } else {
            positives.append(value)
        }
    }
    
    // 排序负数部分（转换为绝对值排序后反转）
    if !negatives.isEmpty {
        let absNegatives = negatives.map { -$0 }
        
        // 使用独立的计数排序逻辑
        if !absNegatives.isEmpty {
            // 找到最小值和最大值
            let min = absNegatives.min()!
            let max = absNegatives.max()!
            let range = max - min + 1
            
            // 创建计数数组
            var count = Array(repeating: 0, count: range)
            
            // 统计每个元素出现的次数
            for value in absNegatives {
                count[value - min] += 1
            }
            
            // 计算累计计数
            for i in 1..<count.count {
                count[i] += count[i - 1]
            }
            
            // 创建输出数组
            var output = Array(repeating: 0, count: absNegatives.count)
            
            // 从后向前遍历，保证稳定性
            for i in (0..<absNegatives.count).reversed() {
                let value = absNegatives[i]
                let index = value - min
                output[count[index] - 1] = value
                count[index] -= 1
            }
            
            // 反转并恢复负号
            for i in 0..<output.count {
                negatives[i] = -output[output.count - 1 - i]
            }
        }
    }
    
    // 排序正数部分
    if !positives.isEmpty {
        // 使用独立的计数排序逻辑
        if !positives.isEmpty {
            // 找到最小值和最大值
            let min = positives.min()!
            let max = positives.max()!
            let range = max - min + 1
            
            // 创建计数数组
            var count = Array(repeating: 0, count: range)
            
            // 统计每个元素出现的次数
            for value in positives {
                count[value - min] += 1
            }
            
            // 计算累计计数
            for i in 1..<count.count {
                count[i] += count[i - 1]
            }
            
            // 创建输出数组
            var output = Array(repeating: 0, count: positives.count)
            
            // 从后向前遍历，保证稳定性
            for i in (0..<positives.count).reversed() {
                let value = positives[i]
                let index = value - min
                output[count[index] - 1] = value
                count[index] -= 1
            }
            
            // 复制回正数数组
            for i in 0..<output.count {
                positives[i] = output[i]
            }
        }
    }
    
    // 合并结果
    var result = [Int]()
    result.append(contentsOf: negatives)
    result.append(contentsOf: positives)
    
    // 复制回原数组
    for i in 0..<arr.count {
        arr[i] = result[i]
    }
    
    printArray(arr, label: "排序后数组")
}

/**
 * 计数排序 - 桶优化版本
 * 
 * 算法思路：
 * 使用桶的概念，将相近的数值分组
 * 减少计数数组的大小
 * 适合大数据范围但分布稀疏的情况
 * 
 * 优化效果：
 * - 减少内存使用
 * 提高处理稀疏数据的效率
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 */
func countingSort4(_ arr: inout [Int]) {
    print("countingSort4 bucket optimized:")
    
    if arr.isEmpty {
        return
    }
    
    // 找到最小值和最大值
    let min = arr.min()!
    let max = arr.max()!
    let range = max - min + 1
    
    // 确定桶的大小（可以调整以优化性能）
    let bucketSize = Swift.max(1, range / 10)
    var bucketCount = (range + bucketSize - 1) / bucketSize
    bucketCount = Swift.max(5, bucketCount, 10)
    
    // 创建桶
    var buckets = Array(repeating: [Int](), count: bucketCount)
    
    // 将元素分配到桶中
    for value in arr {
        let bucketIndex: Int
        if value == max {
            bucketIndex = bucketCount - 1
        } else {
            bucketIndex = (value - min) / bucketSize
        }
        buckets[bucketIndex].append(value)
    }
    
    // 对每个桶进行排序并合并结果
    var result = [Int]()
    
    for i in 0..<bucketCount {
        if !buckets[i].isEmpty {
            // 使用独立的计数排序逻辑
            var bucketArray = buckets[i]
            
            if !bucketArray.isEmpty {
                // 找到最小值和最大值
                let min = bucketArray.min()!
                let max = bucketArray.max()!
                let range = max - min + 1
                
                // 创建计数数组
                var count = Array(repeating: 0, count: range)
                
                // 统计每个元素出现的次数
                for value in bucketArray {
                    count[value - min] += 1
                }
                
                // 计算累计计数
                for j in 1..<count.count {
                    count[j] += count[j - 1]
                }
                
                // 创建输出数组
                var output = Array(repeating: 0, count: bucketArray.count)
                
                // 从后向前遍历，保证稳定性
                for j in (0..<bucketArray.count).reversed() {
                    let value = bucketArray[j]
                    let index = value - min
                    output[count[index] - 1] = value
                    count[index] -= 1
                }
                
                // 复制回桶数组
                for j in 0..<output.count {
                    bucketArray[j] = output[j]
                }
            }
            
            // 将排序后的桶内容复制到结果数组
            result.append(contentsOf: bucketArray)
        }
    }
    
    // 复制回原数组
    for i in 0..<arr.count {
        arr[i] = result[i]
    }
    
    printArray(arr, label: "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

func main() {
    // 测试1：标准版本
    performanceTest(countingSort1, arr: testData, name: "标准版本")

    // 测试2：内存优化版本
    performanceTest(countingSort2, arr: testData, name: "内存优化版本")

    // 测试3：负数处理版本
    performanceTest(countingSort3, arr: testData, name: "负数处理版本")

    // 测试4：桶优化版本
    performanceTest(countingSort4, arr: testData, name: "桶优化版本")

    print("=== 算法对比总结 ===")
    print("1. 标准版本：经典实现，稳定排序")
    print("2. 内存优化版本：原地修改，节省空间")
    print("3. 负数处理版本：支持负数，功能完整")
    print("4. 桶优化版本：分组处理，适合稀疏数据")
}

main()

/*
打印结果
jarry@Mac countingsort % swift counting_sort.swift
标准版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort1 standard:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
标准版本: 0.065
标准版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

内存优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort2 memory optimized:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
内存优化版本: 0.025
内存优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

负数处理版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort3 negative numbers:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
负数处理版本: 0.030
负数处理版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

桶优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort4 bucket optimized:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
桶优化版本: 0.030
桶优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 标准版本：经典实现，稳定排序
2. 内存优化版本：原地修改，节省空间
3. 负数处理版本：支持负数，功能完整
4. 桶优化版本：分组处理，适合稀疏数据
*/
