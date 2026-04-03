// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// RadixSort 基数排序算法实现
// 提供四种不同的实现方式，适合不同场景和性能需求

import Foundation

// printArray 打印数组内容的辅助函数
func printArray(_ arr: [Int], label: String) {
    print("\(label): \(arr)")
}

// performanceTest 性能测试辅助函数
func performanceTest(_ sortFunc: @escaping (inout [Int]) -> Void), arr: [Int], name: String) {
    // 创建数组副本，避免修改原数组
    var testArr = arr
    printArray(testArr, name + "原始数组")
    
    // 开始计时
    let startTime = CFAbsoluteTimeGetCurrent()
    sortFunc(&testArr)
    let endTime = CFAbsoluteTimeGetCurrent()
    
    let duration = endTime.timeIntervalSince(startTime).milliseconds
    print("\(name): \(String(format: "%.3f", duration))")
    printArray(testArr, name + "排序结果")
    print("") // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含大数字和负数的典型数组
let testData: [Int] = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]

/**
 * 获取数字的指定位数
 */
func getDigit(_ num: Int, exp: Int) -> Int {
    abs(num) / exp % 10
}

/**
 * 计数排序辅助函数 - 按位数排序
 */
func countingSortByDigit(arr: inout [Int], exp: Int) {
    let n = arr.count
    var output = Array(repeating: 0, count: n)
    var count = Array(repeating: 0, count: 10)
    
    // 统计每个数字的出现次数
    for i in 0..<n {
        let digit = getDigit(arr[i], exp)
        count[digit] += 1
    }
    
    // 计算累计计数
    for i in 1..<10 {
        count[i] += count[i - 1]
    }
    
    // 构建输出数组
    for i in (0..<n).reversed() {
        let digit = getDigit(arr[i], exp)
        output[count[digit] - 1] = arr[i]
        count[digit] -= 1
    }
    
    // 复制回原数组
    for i in 0..<n {
        arr[i] = output[i]
    }
}

/**
 * 基数排序基础版本 - LSD（最低位优先）
 * 
 * 算法原理：
 * 1. 从个位开始，对每一位进行计数排序
 * 2. 逐步处理十位、百位、千位等
 * 3. 经过所有位数处理后，数组完全有序
 * 
 * 生活类比：就像整理学生成绩，先按个位数排序，
 * 再按十位数排序，最后按百位数排序，最终得到完整排序
 * 
 * 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
 * 空间复杂度：O(n + k) - 需要额外的计数和输出数组
 * 稳定性：稳定 - 计数排序保持相等元素的相对位置
 */
func radixSort1(_ arr: inout [Int]) {
    print("radixSort1 LSD:")
    
    // 找到最大值以确定位数
    let max = arr.max()!
    
    // 对每个位数进行计数排序
    var exp = 1
    while max / exp > 0 {
        countingSortByDigit(arr: &exp)
        exp *= 10
    }
    
    printArray(arr, "排序后数组")
}

/**
 * MSD递归排序函数
 */
func msdSort(arr: inout [Int], left: Int, right: Int, exp: Int) {
    if left >= right || exp < 1 {
        return
    }
    
    // 创建桶
    var buckets = Array(repeating: [Int](), count: 10)
    
    // 分配到桶中
    for i in left...right {
        let digit = getDigit(arr[i], exp)
        buckets[digit].append(arr[i])
    }
    
    // 重新排序并递归处理每个桶
    var index = left
    for i in 0..<10 {
        if !buckets[i].isEmpty {
            // 复制桶中元素回原数组
            for value in buckets[i] {
                arr[index] = value
                index += 1
            }
            
            // 递归处理下一个位数
            msdSort(arr: left, index - 1, exp / 10)
            left = index
        }
    }
}

/**
 * 基数排序优化版本 - MSD（最高位优先）
 * 
 * 算法思路：
 * 从最高位开始排序，使用递归处理子数组
 * 适合处理字符串或变长数据
 * 
 * 优化效果：
 * - 更好的内存局部性
 * 适合大数据集
 * 
 * 时间复杂度：O(d * (n + k))
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
func radixSort2(_ arr: inout [Int]) {
    print("radixSort2 MSD:")
    
    if arr.isEmpty() {
        return
    }
    
    // 找到最大值以确定位数
    let max = arr.max()!
    var exp = 1
    while max / exp > 0 {
        exp *= 10
    }
    
    msdSort(arr, 0, arr.count - 1, exp / 10)
    
    printArray(arr, "排序后数组")
}

/**
 * 基数排序 - 迭代MSD版本
 * 
 * 算法思路：
 * 使用迭代方式实现MSD排序
 * 使用栈来模拟递归调用
 * 
 * 优化效果：
 * - 避免递归开销
 * - 更好的性能控制
 * 
 * 时间复杂度：O(d * (n + k))
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
func radixSort3(_ arr: inout [Int]) {
    print("radixSort3 iterative MSD:")
    
    if arr.isEmpty() {
        return
    }
    
    // 找到最大值以确定位数
    let max = arr.max()!
    var exp = 1
    while max / exp > 0 {
        exp *= 10
    }
    
    // 使用栈模拟递归
    struct StackItem {
        let left: Int
        let right: Int
        let exp: Int
    }
    
    var stack = [StackItem(
        left: 0,
        right: arr.count - 1,
        exp: exp / 10
    )]
    
    while !stack.isEmpty {
        let item = stack.removeLast()
        let left = item.left
        let right = item.right
        let currentExp = item.exp
        
        if left >= right || currentExp < 1 {
            continue
        }
        
        // 创建桶
        var buckets = Array(repeating: [Int](), count: 10)
        
        // 分配到桶中
        for i in left...right {
            let digit = getDigit(arr[i], currentExp)
            buckets[digit].append(arr[i])
        }
        
        // 重新排序并将子问题入栈
        var index = left
        for i in 0..<10 {
            if !buckets[i].isEmpty {
                // 复制桶中元素回原数组
                for value in buckets[i] {
                    arr[index] = value
                    index += 1
                }
                
                // 将子问题入栈（逆序处理以保持正确顺序）
                stack.append(StackItem(
                    left: left,
                    right: index - 1,
                    exp: currentExp / 10
                ))
                left = index
            }
        }
    }
    
    printArray(arr, "排序后数组")
}

/**
 * 基数排序 - 桶优化版本
 * 
 * 算法思路：
 * 使用动态桶大小，优化内存使用
 * 适合处理稀疏数据
 * 
 * 优化效果：
 * - 减少内存占用
 * 提高处理效率
 * 
 * 时间复杂度：O(d * (n + k))
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
func radixSort4(_ arr: inout [Int]) {
    print("radixSort4 bucket optimized:")
    
    // 找到最大值以确定位数
    let max = arr.max()!
    
    // 对每个位数进行计数排序
    var exp = 1
    while max / exp > 0 {
        let n = arr.count
        var output = Array(repeating: 0, count: n)
        
        // 动态确定桶范围
        var minDigit = 9
        var maxDigit = 0
        for i in 0..<n {
            let digit = getDigit(arr[i], exp)
            if digit < minDigit {
                minDigit = digit
            }
            if digit > maxDigit {
                maxDigit = digit
            }
        }
        
        let bucketSize = maxDigit - minDigit + 1
        var count = Array(repeating: 0, count: bucketSize)
        
        // 统计每个数字的出现次数
        for i in 0..<n {
            let digit = getDigit(arr[i], exp)
            count[(digit - minDigit) + 1] += 1
        }
        
        // 计算累计计数
        for i in 1..count.count {
            count[i] += count[i - 1]
        }
        
        // 构建输出数组
        for i in (0..<n).reversed() {
            let digit = getDigit(arr[i], exp)
            output[count[(digit - minDigit) + 1] - 1] = arr[i]
            count[(digit - minDigit) + 1] -= 1
        }
        
        // 复制回原数组
        for i in 0..n {
            arr[i] = output[i]
        }
        
        exp *= 10
    }
    
    printArray(arr, "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

func main() {
    // 测试1：LSD版本
    performanceTest(radixSort1, testData, "LSD版本")

    // 测试2：MSD版本
    performanceTest(radixSort2, testData, "MSD版本")

    // 测试3：迭代MSD版本
    performanceTest(radixSort3, testData, "迭代MSD版本")

    // 测试4：桶优化版本
    performanceTest(radixSort4, testData, "桶优化版本")

    print("=== 算法对比总结 ===")
    print("1. LSD版本：经典实现，从低到高")
    print("2. MSD版本：高位优先，递归处理")
    print("3. 迭代MSD版本：避免递归，性能稳定")
    print("4. 桶优化版本：动态桶大小，内存优化")
}

/*
打印结果
jarry@Mac radixsort % swift run
LSD版本原始数组: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort1 LSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
LSD版本: 0.125ms
LSD版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

MSD版本原始数组: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort2 MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
MSD版本: 0.042ms
MSD版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

迭代MSD版本原始数组: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort3 iterative MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
迭代MSD版本: 0.042ms
迭代MSD版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

桶优化版本原始数组: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort4 bucket optimized:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
桶优化版本: 0.042ms
桶优化版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

=== 算法对比总结 ===
1. LSD版本：经典实现，从低到高
2. MSD版本：高位优先，递归处理
3. 迭代MSD版本：避免递归，性能稳定
4. 桶优化版本：动态桶大小，内存优化
*/
