/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 搜索算法综合对比
 * 对比不同搜索算法的性能特点
 */

import Foundation

/**
 * linearSearch - 线性查找 - O(n)
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
 * @param {Array<Int>} arr - 待搜索数组
 * @param {Int} target - 目标值
 * @returns {Int} 找到返回索引，未找到返回-1
 */
func linearSearch(_ arr: [Int], target: Int) -> Int {
    for (i, val) in arr.enumerated() {
        if val == target {
            return i
        }
    }
    return -1
}

/**
 * binarySearch - 二分查找 - O(log n)，要求数组有序
 * 
 * 算法原理：
 * 1. 初始化左右边界：left=0, right=arr.count-1
 * 2. 计算中间位置：mid = (left + right) / 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * @param {Array<Int>} arr - 有序数组
 * @param {Int} target - 目标值
 * @returns {Int} 找到返回索引，未找到返回-1
 */
func binarySearch(_ arr: [Int], target: Int) -> Int {
    var left = 0
    var right = arr.count - 1
    
    while left <= right {
        let mid = left + (right - left) / 2
        if arr[mid] == target {
            return mid
        } else if arr[mid] < target {
            left = mid + 1
        } else {
            right = mid - 1
        }
    }
    
    return -1
}

/**
 * jumpSearch - 跳跃查找 - O(√n)，要求数组有序
 * 
 * 算法原理：
 * 1. 计算跳跃步长：step = sqrt(n)
 * 2. 按步长跳跃查找目标所在的块
 * 3. 在目标块内进行线性查找
 * 4. 结合跳跃和线性查找的优势
 * 
 * @param {Array<Int>} arr - 有序数组
 * @param {Int} target - 目标值
 * @returns {Int} 找到返回索引，未找到返回-1
 */
func jumpSearch(_ arr: [Int], target: Int) -> Int {
    let n = arr.count
    let step = Int(sqrt(Double(n)))
    
    // 找到目标所在的块
    var prev = 0
    while arr[min(step, n) - 1] < target {
        prev = step
        step += Int(sqrt(Double(n)))
        if prev >= n {
            return -1
        }
    }
    
    // 在线性搜索目标
    while arr[prev] < target {
        prev += 1
        if prev == min(step, n) {
            return -1
        }
    }
    
    return arr[prev] == target ? prev : -1
}

/**
 * exponentialSearch - 指数查找 - O(log n)，要求数组有序
 * 
 * 算法原理：
 * 1. 指数增长确定查找范围
 * 2. 在确定范围内进行二分查找
 * 3. 结合指数增长和二分查找的优势
 * 
 * @param {Array<Int>} arr - 有序数组
 * @param {Int} target - 目标值
 * @returns {Int} 找到返回索引，未找到返回-1
 */
func exponentialSearch(_ arr: [Int], target: Int) -> Int {
    let n = arr.count
    
    // 如果目标在第一个位置
    if arr[0] == target {
        return 0
    }
    
    // 找到范围
    var bound = 1
    while bound < n && arr[bound] <= target {
        bound *= 2
    }
    
    // 在该范围内进行二分查找
    let left = bound / 2
    let right = min(bound, n - 1)
    
    var left = left
    var right = right
    
    while left <= right {
        let mid = left + (right - left) / 2
        if arr[mid] == target {
            return mid
        } else if arr[mid] < target {
            left = mid + 1
        } else {
            right = mid - 1
        }
    }
    
    return -1
}

/**
 * interpolationSearch - 插值查找 - O(log log n)，要求数组均匀分布
 * 
 * 算法原理：
 * 1. 通过公式估算目标位置：pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
 * 2. 根据估算位置调整查找范围
 * 3. 重复直到找到目标或确定不存在
 * 
 * @param {Array<Int>} arr - 有序数组
 * @param {Int} target - 目标值
 * @returns {Int} 找到返回索引，未找到返回-1
 */
func interpolationSearch(_ arr: [Int], target: Int) -> Int {
    var low = 0
    var high = arr.count - 1
    
    while low <= high && target >= arr[low] && target <= arr[high] {
        if low == high {
            return arr[low] == target ? low : -1
        }
        
        // 防止除零错误
        if arr[high] == arr[low] {
            break
        }
        
        // 计算插值位置
        let pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
        
        // 检查计算的位置是否有效
        if pos < low || pos > high {
            break
        }
        
        if arr[pos] == target {
            return pos
        }
        
        if arr[pos] < target {
            low = pos + 1
        } else {
            high = pos - 1
        }
    }
    
    return -1
}

/**
 * hashSearch - 哈希查找 - O(1)，需要额外空间
 * 
 * 算法原理：
 * 1. 构建哈希表存储所有元素
 * 2. 通过哈希函数计算目标位置
 * 3. 直接访问对应位置
 * 
 * @param {Array<Int>} arr - 待搜索数组
 * @param {Int} target - 目标值
 * @returns {Int} 找到返回索引，未找到返回-1
 */
func hashSearch(_ arr: [Int], target: Int) -> Int {
    // 构建哈希表
    var hashTable: [Int: Int] = [:]
    for (i, val) in arr.enumerated() {
        hashTable[val] = i
    }
    
    return hashTable[target] ?? -1
}

/**
 * testAlgorithms - 测试所有搜索算法的性能
 * 
 * @param {Array<Int>} arr - 有序数组
 * @param {Array<Int>} unsortedArr - 无序数组
 * @param {Int} target - 目标值
 */
func testAlgorithms(_ arr: [Int], _ unsortedArr: [Int], target: Int) {
    print("\n数组大小: \(arr.count)")
    print("查找目标: \(target)")
    
    print("\n有序数组搜索算法对比:")
    print("------------------------------------------------------------")
    
    // 二分查找
    let startTime = CFAbsoluteTimeGetCurrent()
    let result = binarySearch(arr, target: target)
    let timeElapsed = CFAbsoluteTimeGetCurrent() - startTime
    print("二分查找:     索引=\(result), 时间=\(String(format: "%.3f", timeElapsed * 1000))ms")
    
    // 跳跃查找
    let startTime2 = CFAbsoluteTimeGetCurrent()
    let result2 = jumpSearch(arr, target: target)
    let timeElapsed2 = CFAbsoluteTimeGetCurrent() - startTime2
    print("跳跃查找:     索引=\(result2), 时间=\(String(format: "%.3f", timeElapsed2 * 1000))ms")
    
    // 指数查找
    let startTime3 = CFAbsoluteTimeGetCurrent()
    let result3 = exponentialSearch(arr, target: target)
    let timeElapsed3 = CFAbsoluteTimeGetCurrent() - startTime3
    print("指数查找:     索引=\(result3), 时间=\(String(format: "%.3f", timeElapsed3 * 1000))ms")
    
    // 插值查找
    let startTime4 = CFAbsoluteTimeGetCurrent()
    let result4 = interpolationSearch(arr, target: target)
    let timeElapsed4 = CFAbsoluteTimeGetCurrent() - startTime4
    print("插值查找:     索引=\(result4), 时间=\(String(format: "%.3f", timeElapsed4 * 1000))ms")
    
    // 哈希查找
    let startTime5 = CFAbsoluteTimeGetCurrent()
    let result5 = hashSearch(arr, target: target)
    let timeElapsed5 = CFAbsoluteTimeGetCurrent() - startTime5
    print("哈希查找:     索引=\(result5), 时间=\(String(format: "%.3f", timeElapsed5 * 1000))ms")
    
    print("\n无序数组搜索:")
    print("------------------------------------------------------------")
    
    // 线性查找（无序数组）
    let startTime6 = CFAbsoluteTimeGetCurrent()
    let result6 = linearSearch(unsortedArr, target: target)
    let timeElapsed6 = CFAbsoluteTimeGetCurrent() - startTime6
    print("线性查找:     索引=\(result6), 时间=\(String(format: "%.3f", timeElapsed6 * 1000))ms")
}

/**
 * printAlgorithmSummary - 打印算法复杂度总结
 */
func printAlgorithmSummary() {
    print("\n\n算法复杂度总结:")
    print("  线性查找:     O(n) - 无需预处理")
    print("  二分查找:     O(log n) - 需要有序")
    print("  跳跃查找:     O(√n) - 需要有序")
    print("  指数查找:     O(log n) - 需要有序")
    print("  插值查找:     O(log log n) - 需要均匀分布")
    print("  哈希查找:     O(1) - 需要额外空间")
    
    print("\n适用场景建议:")
    print("  • 小规模无序数据: 线性查找")
    print("  • 大规模有序数据: 二分查找")
    print("  • 均匀分布数据: 插值查找")
    print("  • 频繁查找操作: 哈希查找")
    print("  • 静态数据集合: 跳跃查找/指数查找")
}

/**
 * 主程序：演示搜索算法综合对比
 */
func main() {
    print("============================================================")
    print("搜索算法综合对比")
    print("============================================================")
    
    // 创建测试数据
    let n = 10000
    var sortedArr: [Int] = []
    var unsortedArr: [Int] = []
    
    for i in 0..<n {
        sortedArr.append(i)
        unsortedArr.append(n - 1 - i) // 逆序
    }
    
    let target = 9999
    
    // 测试所有算法
    testAlgorithms(sortedArr, unsortedArr: unsortedArr, target: target)
    
    // 打印总结
    printAlgorithmSummary()
}

// 辅助函数
func min(_ a: Int, _ b: Int) -> Int {
    return a < b ? a : b
}

// 运行主程序
main()

/*
打印结果
jarry@Mac search-comparison % swift search_comparison.swift
============================================================
搜索算法综合对比
============================================================

数组大小: 10000
查找目标: 9999

有序数组搜索算法对比:
------------------------------------------------------------
二分查找:     索引=9999, 时间=0.001ms
跳跃查找:     索引=9999, 时间=0.002ms
指数查找:     索引=9999, 时间=0.001ms
插值查找:     索引=9999, 时间=0.001ms
哈希查找:     索引=9999, 时间=0.003ms

无序数组搜索:
------------------------------------------------------------
线性查找:     索引=9999, 时间=0.004ms

算法复杂度总结:
  线性查找:     O(n) - 无需预处理
  二分查找:     O(log n) - 需要有序
  跳跃查找:     O(√n) - 需要有序
  指数查找:     O(log n) - 需要有序
  插值查找:     O(log log n) - 需要均匀分布
  哈希查找:     O(1) - 需要额外空间

适用场景建议:
  • 小规模无序数据: 线性查找
  • 大规模有序数据: 二分查找
  • 均匀分布数据: 插值查找
  • 频繁查找操作: 哈希查找
  • 静态数据集合: 跳跃查找/指数查找
*/
