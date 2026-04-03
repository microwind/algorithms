// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// QuickSort 快速排序算法实现
// 提供四种不同的实现方式，适合不同场景和性能需求

import Foundation

// printArray 打印数组内容的辅助函数
func printArray(_ arr: [Int], label: String) {
    print("\(label): [\(arr.map(String.init).joined(separator: ", "))]")
}

// performanceTest 性能测试辅助函数
func performanceTest(_ sortFunc: (inout [Int]) -> Void, arr: [Int], name: String) {
    // 创建数组副本，避免修改原数组
    var testArr = arr
    printArray(testArr, label: "\(name)原始数组")
    
    // 开始计时
    let startTime = CFAbsoluteTimeGetCurrent()
    sortFunc(&testArr)
    let timeElapsed = CFAbsoluteTimeGetCurrent() - startTime
    
    print("\(name): \(String(format: "%.3f", timeElapsed * 1000))ms")
    printArray(testArr, label: "\(name)排序结果")
    print() // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
let testData = [7, 11, 9, 10, 12, 13, 8]

/**
 * Lomuto分区函数
 * @param arr 数组
 * @param low 起始索引
 * @param high 结束索引
 * @return 基准元素的最终位置
 */
func partition(_ arr: inout [Int], low: Int, high: Int) -> Int {
    let pivot = arr[high] // 选择最后一个元素作为基准
    var i = low - 1     // 小于基准的元素的边界
    
    // 遍历数组，将小于基准的元素移到左边
    for j in low..<high {
        // 关键点：找到小于基准的元素
        if arr[j] < pivot {
            i += 1
            // Swift特点：使用swapAt方法
            arr.swapAt(i, j)
        }
    }
    
    // 将基准元素放到正确位置
    arr.swapAt(i + 1, high)
    return i + 1
}

/**
 * 递归快速排序函数
 * @param arr 数组
 * @param low 起始索引
 * @param high 结束索引
 */
func quickSort1Helper(_ arr: inout [Int], low: Int, high: Int) {
    if low < high {
        // 分区并获取基准位置
        let pi = partition(&arr, low: low, high: high)
        
        // 递归排序左半部分
        quickSort1Helper(&arr, low: low, high: pi - 1)
        
        // 递归排序右半部分
        quickSort1Helper(&arr, low: pi + 1, high: high)
    }
}

/**
 * 快速排序基础版本 - Lomuto分区
 * 
 * 算法原理：
 * 1. 选择基准元素（通常选择最后一个元素）
 * 2. 将数组分为两部分：小于基准的元素和大于基准的元素
 * 3. 递归地对两部分进行快速排序
 * 4. 合并结果得到有序数组
 * 
 * 生活类比：就像整理书架，选择一本书作为参考，
 * 把比它薄的书放左边，比它厚的书放右边，
 * 然后对左右两边的书分别重复这个过程
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 */
func quickSort1(_ arr: inout [Int]) {
    print("quickSort1 Lomuto partition:")
    if !arr.isEmpty {
        quickSort1Helper(&arr, low: 0, high: arr.count - 1)
    }
    printArray(arr, label: "排序后数组")
}

/**
 * Hoare分区函数
 * @param arr 数组
 * @param low 起始索引
 * @param high 结束索引
 * @return 分区点
 */
func partitionHoare(_ arr: inout [Int], low: Int, high: Int) -> Int {
    let pivot = arr[low] // 选择第一个元素作为基准
    var i = low - 1
    var j = high + 1
    
    // 从两端向中间扫描
    while true {
        // 从左向右找大于基准的元素
        repeat {
            i += 1
        } while arr[i] < pivot
        
        // 从右向左找小于基准的元素
        repeat {
            j -= 1
        } while arr[j] > pivot
        
        // 关键点：如果指针交叉，分区完成
        if i >= j {
            return j
        }
        
        // 交换元素
        arr.swapAt(i, j)
    }
}

/**
 * 递归快速排序函数
 * @param arr 数组
 * @param low 起始索引
 * @param high 结束索引
 */
func quickSort2Helper(_ arr: inout [Int], low: Int, high: Int) {
    if low < high {
        // 分区并获取分区点
        let pi = partitionHoare(&arr, low: low, high: high)
        
        // 递归排序左半部分
        quickSort2Helper(&arr, low: low, high: pi)
        
        // 递归排序右半部分
        quickSort2Helper(&arr, low: pi + 1, high: high)
    }
}

/**
 * 快速排序优化版本 - Hoare分区
 * 
 * 优化思路：
 * 使用Hoare分区方案，通常比Lomuto更高效
 * 从两端向中间扫描，减少交换次数
 * 
 * 优化效果：
 * - 减少了交换次数
 * - 对于某些数据分布性能更好
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 */
func quickSort2(_ arr: inout [Int]) {
    print("quickSort2 Hoare partition:")
    if !arr.isEmpty {
        quickSort2Helper(&arr, low: 0, high: arr.count - 1)
    }
    printArray(arr, label: "排序后数组")
}

/**
 * 三路分区函数
 * @param arr 数组
 * @param low 起始索引
 * @param high 结束索引
 * @return 分区点 [lt, gt]
 */
func partition3Way(_ arr: inout [Int], low: Int, high: Int) -> (Int, Int) {
    let pivot = arr[low] // 选择第一个元素作为基准
    var lt = low          // 小于基准的边界
    var i = low + 1       // 当前扫描位置
    var gt = high         // 大于基准的边界
    
    // 遍历数组，进行三路分区
    while i <= gt {
        if arr[i] < pivot {
            // 小于基准，交换到左边
            arr.swapAt(lt, i)
            lt += 1
            i += 1
        } else if arr[i] > pivot {
            // 大于基准，交换到右边
            arr.swapAt(i, gt)
            gt -= 1
        } else {
            // 等于基准，直接跳过
            i += 1
        }
    }
    
    return (lt, gt)
}

/**
 * 递归快速排序函数
 * @param arr 数组
 * @param low 起始索引
 * @param high 结束索引
 */
func quickSort3Helper(_ arr: inout [Int], low: Int, high: Int) {
    if low < high {
        // 三路分区
        let (lt, gt) = partition3Way(&arr, low: low, high: high)
        
        // 递归排序小于基准的部分
        quickSort3Helper(&arr, low: low, high: lt - 1)
        
        // 递归排序大于基准的部分
        quickSort3Helper(&arr, low: gt + 1, high: high)
        // 等于基准的部分已经就位，无需处理
    }
}

/**
 * 快速排序 - 三路分区版本
 * 
 * 算法思路：
 * 将数组分为三部分：小于基准、等于基准、大于基准
 * 特别适合包含大量重复元素的数组
 * 
 * 优化效果：
 * - 处理重复元素时效率更高
 * - 避免了重复元素的递归调用
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 */
func quickSort3(_ arr: inout [Int]) {
    print("quickSort3 three-way partition:")
    if !arr.isEmpty {
        quickSort3Helper(&arr, low: 0, high: arr.count - 1)
    }
    printArray(arr, label: "排序后数组")
}

/**
 * 快速排序 - 迭代版本
 * 
 * 算法思路：
 * 使用栈来模拟递归调用
 * 避免递归深度过大导致的栈溢出
 * 
 * 优化效果：
 * - 避免了递归调用的开销
 * - 对于大数据量更稳定
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 显式栈空间
 * 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 */
func quickSort4(_ arr: inout [Int]) {
    print("quickSort4 iterative:")
    
    if arr.isEmpty {
        return
    }
    
    // 创建栈来存储待处理的子数组
    var stack: [Int] = []
    
    // 初始范围入栈
    stack.append(0)
    stack.append(arr.count - 1)
    
    // 处理栈中的所有范围
    while !stack.isEmpty {
        // 出栈获取当前范围
        let high = stack.removeLast()
        let low = stack.removeLast()
        
        // 分区
        let pi = partition(&arr, low: low, high: high)
        
        // 关键点：将左半部分入栈
        if pi > 0 && pi > low {
            stack.append(low)
            stack.append(pi - 1)
        }
        
        // 将右半部分入栈
        if pi < high {
            stack.append(pi + 1)
            stack.append(high)
        }
    }
    
    printArray(arr, label: "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

// 测试1：Lomuto分区版本
performanceTest(quickSort1, arr: testData, name: "Lomuto分区版本")

// 测试2：Hoare分区版本
performanceTest(quickSort2, arr: testData, name: "Hoare分区版本")

// 测试3：三路分区版本
performanceTest(quickSort3, arr: testData, name: "三路分区版本")

// 测试4：迭代版本
performanceTest(quickSort4, arr: testData, name: "迭代版本")

print("=== 算法对比总结 ===")
print("1. Lomuto版本：经典分区，简单易懂")
print("2. Hoare版本：双向扫描，效率更高")
print("3. 三路版本：处理重复，性能优化")
print("4. 迭代版本：避免递归，稳定可靠")

/*
打印结果
jarry@Mac quicksort % swift quick_sort.swift
Lomuto分区版本原始数组: [7, 11, 9, 10, 12, 13, 8]
quickSort1 Lomuto partition:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
Lomuto分区版本: 0.125ms
Lomuto分区版本排序结果: [7, 8, 9, 10, 11, 12, 13]

Hoare分区版本原始数组: [7, 11, 9, 10, 12, 13, 8]
quickSort2 Hoare partition:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
Hoare分区版本: 0.042ms
Hoare分区版本排序结果: [7, 8, 9, 10, 11, 12, 13]

三路分区版本原始数组: [7, 11, 9, 10, 12, 13, 8]
quickSort3 three-way partition:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
三路分区版本: 0.042ms
三路分区版本排序结果: [7, 8, 9, 10, 11, 12, 13]

迭代版本原始数组: [7, 11, 9, 10, 12, 13, 8]
quickSort4 iterative:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
迭代版本: 0.042ms
迭代版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. Lomuto版本：经典分区，简单易懂
2. Hoare版本：双向扫描，效率更高
3. 三路版本：处理重复，性能优化
4. 迭代版本：避免递归，稳定可靠
*/
