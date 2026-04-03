// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// BucketSort 桶排序算法实现
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
let testData: [Int] = [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

/**
 * 插入排序辅助函数 - 用于桶内排序
 */
func insertionSort(_ arr: inout [Int]) {
    for i in 1..<arr.count {
        let key = arr[i]
        var j = i - 1
        
        while j >= 0 && arr[j] > key {
            arr[j + 1] = arr[j]
            j -= 1
        }
        arr[j + 1] = key
    }
}

/**
 * 桶排序基础版本 - 标准实现
 * 
 * 算法原理：
 * 1. 创建固定数量的桶
 * 2. 将元素分配到对应的桶中
 * 3. 对每个桶内的元素进行排序
 * 4. 合并所有桶的元素得到有序数组
 * 
 * 生活类比：就像整理图书馆的书籍，
 * 先按类别分到不同的书架，再在每个书架内按字母顺序排列
 * 
 * 时间复杂度：平均O(n + k)，最坏O(n²)（所有元素在一个桶中）
 * 空间复杂度：O(n + k) - 需要桶空间
 * 稳定性：稳定 - 桶内排序保持相等元素的相对位置
 */
func bucketSort1(_ arr: inout [Int]) {
    print("bucketSort1 standard:")
    
    if arr.isEmpty {
        return
    }
    
    // 找到最小值和最大值
    let min = arr.min()!
    let max = arr.max()!
    
    // 创建桶（这里使用5个桶作为示例）
    let bucketCount = 5
    var buckets = Array(repeating: [Int](), count: bucketCount)
    
    // 计算每个桶的范围
    let range = max - min
    let bucketSize = Double(range) / Double(bucketCount)
    
    // 将元素分配到桶中
    for value in arr {
        let bucketIndex: Int
        if value == max {
            bucketIndex = bucketCount - 1
        } else {
            bucketIndex = Int(Double(value - min) / bucketSize)
        }
        buckets[bucketIndex].append(value)
    }
    
    // 对每个桶进行排序并合并结果
    var result = [Int]()
    
    for i in 0..<bucketCount {
        if !buckets[i].isEmpty {
            // 对桶内元素进行排序
            var bucketArray = buckets[i]
            insertionSort(&bucketArray)
            result.append(contentsOf: bucketArray)
        }
    }
    
    // 复制回原数组
    for i in 0..<arr.count {
        arr[i] = result[i]
    }
    
    printArray(arr, label: "排序后数组")
}

/**
 * 桶排序优化版本 - 动态桶数量
 * 
 * 算法思路：
 * 根据数据大小动态确定桶的数量
 * 更好的负载均衡
 * 减少空桶的数量
 * 
 * 优化效果：
 * - 更好的空间利用率
 * - 更均匀的元素分布
 * 
 * 时间复杂度：平均O(n + k)
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
func bucketSort2(_ arr: inout [Int]) {
    print("bucketSort2 dynamic buckets:")
    
    if arr.isEmpty {
        return
    }
    
    // 找到最小值和最大值
    let min = arr.min()!
    let max = arr.max()!
    
    // 动态计算桶数量（基于数据范围和元素数量）
    let range = max - min
    var bucketCount = arr.count
    if bucketCount > 10 {
        bucketCount = arr.count / 5
    }
    if bucketCount < 5 {
        bucketCount = 5
    }
    let bucketSize = Double(range) / Double(bucketCount)
    
    // 创建桶
    var buckets = Array(repeating: [Int](), count: bucketCount)
    
    // 将元素分配到桶中
    for value in arr {
        let bucketIndex: Int
        if value == max {
            bucketIndex = bucketCount - 1
        } else {
            bucketIndex = Int(Double(value - min) / bucketSize)
        }
        buckets[bucketIndex].append(value)
    }
    
    // 对每个桶进行排序并合并结果
    var result = [Int]()
    
    for i in 0..<bucketCount {
        if !buckets[i].isEmpty {
            var bucketArray = buckets[i]
            insertionSort(&bucketArray)
            result.append(contentsOf: bucketArray)
        }
    }
    
    // 复制回原数组
    for i in 0..<arr.count {
        arr[i] = result[i]
    }
    
    printArray(arr, label: "排序后数组")
}

/**
 * 桶排序 - 链表实现版本
 * 
 * 算法思路：
 * 使用链表结构实现桶，优化插入操作
 * 适合频繁插入和删除的场景
 * 
 * 优化效果：
 * - 更快的插入操作
 * - 更好的内存管理
 * 
 * 时间复杂度：平均O(n + k)
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
func bucketSort3(_ arr: inout [Int]) {
    print("bucketSort3 linked list:")
    
    if arr.isEmpty {
        return
    }
    
    // 找到最小值和最大值
    let min = arr.min()!
    let max = arr.max()!
    
    // 创建桶（使用数组模拟链表）
    let bucketCount = 5
    var buckets = Array(repeating: [Int](), count: bucketCount)
    
    // 计算每个桶的范围
    let range = max - min
    let bucketSize = Double(range) / Double(bucketCount)
    
    // 将元素分配到桶中（保持有序插入）
    for value in arr {
        let bucketIndex: Int
        if value == max {
            bucketIndex = bucketCount - 1
        } else {
            bucketIndex = Int(Double(value - min) / bucketSize)
        }
        
        // 有序插入到桶中
        var inserted = false
        for (j, existingValue) in buckets[bucketIndex].enumerated() {
            if value < existingValue {
                buckets[bucketIndex].insert(value, at: j)
                inserted = true
                break
            }
        }
        
        if !inserted {
            buckets[bucketIndex].append(value)
        }
    }
    
    // 合并所有桶
    var result = [Int]()
    
    for bucket in buckets {
        result.append(contentsOf: bucket)
    }
    
    // 复制回原数组
    for i in 0..<arr.count {
        arr[i] = result[i]
    }
    
    printArray(arr, label: "排序后数组")
}

/**
 * 桶排序 - 自适应版本
 * 
 * 算法思路：
 * 根据数据分布自动调整桶策略
 * 检测数据分布模式并优化桶分配
 * 
 * 优化效果：
 * - 适应不同数据分布
 * - 自动优化性能
 * 
 * 时间复杂度：平均O(n + k)
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
func bucketSort4(_ arr: inout [Int]) {
    print("bucketSort4 adaptive:")
    
    if arr.isEmpty {
        return
    }
    
    // 分析数据分布
    let min = arr.min()!
    let max = arr.max()!
    let range = max - min
    let sum = arr.reduce(0, +)
    let mean = Double(sum) / Double(arr.count)
    
    // 检测数据分布均匀性
    let variance = arr.reduce(0.0) { acc, value in
        let diff = Double(value) - mean
        return acc + diff * diff
    } / Double(arr.count)
    
    // 根据分布情况调整策略
    let bucketCount: Int
    if variance < Double(range * range) / 100.0 {
        // 数据分布均匀，使用较多桶
        bucketCount = Swift.max(5, arr.count / 5, 10)
    } else {
        // 数据分布不均匀，使用较少桶
        bucketCount = Swift.max(5, Int(Double(arr.count) * 0.316), 10)
    }
    
    let bucketSize = Double(range) / Double(bucketCount)
    
    // 创建桶
    var buckets = Array(repeating: [Int](), count: bucketCount)
    
    // 将元素分配到桶中
    for value in arr {
        let bucketIndex: Int
        if value == max {
            bucketIndex = bucketCount - 1
        } else {
            bucketIndex = Int(Double(value - min) / bucketSize)
        }
        buckets[bucketIndex].append(value)
    }
    
    // 对每个桶进行排序并合并结果
    var result = [Int]()
    
    for i in 0..<bucketCount {
        if !buckets[i].isEmpty {
            // 根据桶大小选择排序算法
            var bucketArray = buckets[i]
            if bucketArray.count <= 10 {
                insertionSort(&bucketArray)
            } else {
                bucketArray.sort()
            }
            result.append(contentsOf: bucketArray)
        }
    }
    
    // 复制回原数组
    for i in 0..<arr.count {
        arr[i] = result[i]
    }
    
    printArray(arr, label: "排序后数组")
}

/**
 * 桶排序实时冒泡版 - 负数放在第一个桶内排序
 *
 * 算法思路：
 * 1. 计算数组的最大值和最小值
 * 2. 根据数组长度计算桶的大小
 * 3. 将元素分配到桶中，负数放在第1个桶
 * 4. 每次插入后立即对桶内进行冒泡排序
 * 5. 合并所有桶的元素
 *
 * 优化效果：
 * - 插入即排序，实时保持有序
 * - 桶内始终有序，减少后续排序开销
 * - 适合数据量较小的场景
 */
func bucketSort5(_ arr: inout [Int]) {
    print("bucketSort5 real-time bubble:")
    
    if arr.isEmpty {
        return
    }
    
    let min = arr.min()!
    let max = arr.max()!
    
    // 计算桶的数量和大小
    let bucketSize = Swift.max(1, (max - min) / Swift.max(1, min))
    let bucketCount = Swift.max(1, (max - min) / bucketSize + 1)
    
    // 初始化桶
    var buckets: [[Int]] = Array(repeating: [], count: bucketCount)
    
    // 分配元素到桶中
    for item in arr {
        let idx = Swift.max(0, Swift.min(bucketCount - 1, (item - min) / bucketSize))
        buckets[idx].append(item)
        
        // 实时冒泡排序：对新插入的元素进行冒泡排序
        for j in (1..<buckets[idx].count).reversed() {
            if buckets[idx][j] < buckets[idx][j - 1] {
                buckets[idx].swapAt(j, j - 1)
            }
        }
    }
    
    // 合并结果
    var result: [Int] = []
    for bucket in buckets {
        result.append(contentsOf: bucket)
    }
    
    // 复制回原数组
    for i in 0..<arr.count {
        arr[i] = result[i]
    }
    
    printArray(arr, label: "排序后数组")
}

/**
 * 桶排序智能优化版 - 智能桶数量计算
 *
 * 算法思路：
 * 1. 智能计算桶的数量，根据数据规模动态调整
 * 2. 使用快速排序进行桶内排序
 * 3. 优化的桶分配策略
 * 4. 高效的内存管理
 *
 * 优化效果：
 * - 智能桶数量计算，更精确的数据分布
 * - 快速排序桶内元素，提高排序效率
 * - 适合大数据量的场景
 */
func bucketSort6(_ arr: inout [Int]) {
    print("bucketSort6 optimized:")
    
    if arr.isEmpty {
        return
    }
    
    let min = arr.min()!
    let max = arr.max()!
    
    // 智能计算桶的数量
    let bucketCount: Int
    if arr.count < 5 {
        bucketCount = arr.count
    } else if arr.count < 100 {
        bucketCount = arr.count / 2
    } else {
        bucketCount = Int(sqrt(Double(arr.count)))
    }
    
    let bucketSize = Swift.max(1, (max - min) / bucketCount + 1)
    
    // 初始化桶
    var buckets: [[Int]] = Array(repeating: [], count: bucketCount)
    
    // 分配元素到桶中
    for item in arr {
        let idx = Swift.max(0, Swift.min(bucketCount - 1, (item - min) / bucketSize))
        buckets[idx].append(item)
    }
    
    // 桶内排序（使用内置排序）
    for i in 0..<bucketCount {
        buckets[i].sort()
    }
    
    // 合并结果
    var result: [Int] = []
    for bucket in buckets {
        result.append(contentsOf: bucket)
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
    performanceTest(bucketSort1, arr: testData, name: "标准版本")

    // 测试2：动态桶版本
    performanceTest(bucketSort2, arr: testData, name: "动态桶版本")

    // 测试3：链表版本
    performanceTest(bucketSort3, arr: testData, name: "链表版本")

    // 测试4：自适应版本
    performanceTest(bucketSort4, arr: testData, name: "自适应版本")
    
    // 测试5：实时冒泡版本
    performanceTest(bucketSort5, arr: testData, name: "实时冒泡版本")
    
    // 测试6：智能优化版本
    performanceTest(bucketSort6, arr: testData, name: "智能优化版本")

    print("=== 算法对比总结 ===")
    print("1. 标准版本：固定桶数，简单实现")
    print("2. 动态桶版本：根据数据调整，负载均衡")
    print("3. 链表版本：有序插入，优化操作")
    print("4. 自适应版本：智能分析，自动优化")
    print("5. 实时冒泡版本：插入即排序，实时保持有序")
    print("6. 智能优化版本：智能桶数量计算，更精确的数据分布处理")
}

// 执行测试
main()

/*
打印结果
jarry@Mac bucketsort % swift bucket_sort.swift
标准版本原始数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort1 standard:
排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
标准版本: 0.549
标准版本排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

动态桶版本原始数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort2 dynamic buckets:
排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
动态桶版本: 0.014
动态桶版本排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

链表版本原始数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort3 linked list:
排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
链表版本: 0.282
链表版本排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

自适应版本原始数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort4 adaptive:
排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
自适应版本: 0.016
自适应版本排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

实时冒泡版本原始数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort5 real-time bubble:
排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
实时冒泡版本: 0.024
实时冒泡版本排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

智能优化版本原始数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort6 optimized:
排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
智能优化版本: 0.022
智能优化版本排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 标准版本：固定桶数，简单实现
2. 动态桶版本：根据数据调整，负载均衡
3. 链表版本：有序插入，优化操作
4. 自适应版本：智能分析，自动优化
5. 实时冒泡版本：插入即排序，实时保持有序
6. 智能优化版本：智能桶数量计算，更精确的数据分布处理
*/
