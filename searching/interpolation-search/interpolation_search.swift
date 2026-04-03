/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 插值查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

import Foundation

/**
 * 插值查找基础版本 - 非递归实现
 * 
 * 算法原理：
 * 1. 通过公式估算目标位置：pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
 * 2. 根据估算位置调整查找范围
 * 3. 重复直到找到目标或确定不存在
 * 
 * 适用场景：
 * - 均匀分布的有序数组
 * - 数值范围较大的数据集
 * 
 * 时间复杂度：平均O(log log n)，最坏O(n)
 * 空间复杂度：O(1)
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @returns 目标索引，未找到返回-1
 */
func interpolationSearch(_ arr: [Int], target: Int) -> Int {
    var low = 0
    var high = arr.count - 1
    
    // 检查边界条件
    while low <= high && target >= arr[low] && target <= arr[high] {
        // 如果范围只有一个元素
        if low == high {
            return arr[low] == target ? low : -1
        }
        
        // 防止除零错误
        if arr[high] == arr[low] {
            break
        }
        
        // 计算插值位置
        // 关键公式：根据数值比例估算位置
        let pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
        
        // 检查计算的位置是否有效
        if pos < low || pos > high {
            break
        }
        
        // 检查是否找到目标
        if arr[pos] == target {
            return pos // 找到目标
        }
        
        // 调整查找范围
        if arr[pos] < target {
            low = pos + 1 // 目标在右侧
        } else {
            high = pos - 1 // 目标在左侧
        }
    }
    
    return -1 // 未找到
}

/**
 * 插值查找递归版本
 * 
 * 算法思路：
 * 使用递归方式实现插值查找
 * 每次递归缩小查找范围
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @param low 左边界
 * @param high 右边界
 * @returns 目标索引，未找到返回-1
 */
func interpolationSearchRecursive(_ arr: [Int], target: Int, low: Int = 0, high: Int? = nil) -> Int {
    let high = high ?? arr.count - 1
    
    // 递归出口条件
    if low > high || target < arr[low] || target > arr[high] {
        return -1
    }
    
    // 如果范围只有一个元素
    if low == high {
        return arr[low] == target ? low : -1
    }
    
    // 防止除零错误
    if arr[high] == arr[low] {
        return -1
    }
    
    // 计算插值位置
    let pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
    
    // 检查位置有效性
    if pos < low || pos > high {
        return -1
    }
    
    // 检查是否找到目标
    if arr[pos] == target {
        return pos
    }
    
    // 递归调用
    if arr[pos] < target {
        return interpolationSearchRecursive(arr, target: target, low: pos + 1, high: high)
    } else {
        return interpolationSearchRecursive(arr, target: target, low: low, high: pos - 1)
    }
}

/**
 * 插值查找优化版本 - 处理边界情况
 * 
 * 算法优化：
 * - 增加边界检查
 * - 处理特殊情况
 * - 提高算法鲁棒性
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @returns 目标索引，未找到返回-1
 */
func interpolationSearchOptimized(_ arr: [Int], target: Int) -> Int {
    // 边界检查
    guard !arr.isEmpty else {
        return -1
    }
    
    var low = 0
    var high = arr.count - 1
    
    while low <= high && target >= arr[low] && target <= arr[high] {
        // 处理所有元素相同的情况
        if arr[high] == arr[low] {
            if arr[low] == target {
                return low // 所有元素都等于目标
            }
            break // 所有元素相同但不等于目标
        }
        
        // 计算插值位置，使用更精确的计算
        let ratio = Double(target - arr[low]) / Double(arr[high] - arr[low])
        var pos = low + Int(floor(ratio * Double(high - low)))
        
        // 确保位置在有效范围内
        pos = max(low, min(high, pos))
        
        // 检查是否找到目标
        if arr[pos] == target {
            return pos
        }
        
        // 调整查找范围
        if arr[pos] < target {
            low = pos + 1
        } else {
            high = pos - 1
        }
    }
    
    return -1
}

/**
 * 插值查找 - 浮点数版本
 * 
 * 算法扩展：
 * 支持浮点数数组的插值查找
 * 使用epsilon处理浮点数精度问题
 * 
 * @param arr 有序浮点数组
 * @param target 目标值
 * @param epsilon 精度阈值
 * @returns 目标索引，未找到返回-1
 */
func interpolationSearchFloat64(_ arr: [Double], target: Double, epsilon: Double = 0.0001) -> Int {
    var low = 0
    var high = arr.count - 1
    
    while low <= high && target >= arr[low] - epsilon && target <= arr[high] + epsilon {
        if low == high {
            return abs(arr[low] - target) <= epsilon ? low : -1
        }
        
        // 防止除零错误
        if abs(arr[high] - arr[low]) < epsilon {
            break
        }
        
        // 计算插值位置
        let ratio = (target - arr[low]) / (arr[high] - arr[low])
        var pos = low + Int(floor(ratio * Double(high - low)))
        
        // 确保位置有效
        pos = max(low, min(high, pos))
        
        // 检查是否找到目标（考虑浮点精度）
        if abs(arr[pos] - target) <= epsilon {
            return pos
        }
        
        // 调整查找范围
        if arr[pos] < target {
            low = pos + 1
        } else {
            high = pos - 1
        }
    }
    
    return -1
}

/**
 * 主程序：演示插值查找功能
 */
func main() {
    print("=== 插值查找演示 ===\n")
    
    // 测试数据：均匀分布的有序数组
    let arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    print("数组 (均匀分布):")
    print(arr.map { String($0) }.joined(separator: " "))
    print()
    
    // 测试目标值
    let targets = [30, 85, 10, 100, 55]
    
    print("=== 非递归版本测试 ===")
    for target in targets {
        let result = interpolationSearch(arr, target: target)
        if result != -1 {
            print("查找 \(target): 找到于索引 \(result)")
        } else {
            print("查找 \(target): 未找到")
        }
    }
    
    print("\n=== 递归版本测试 ===")
    for target in targets {
        let result = interpolationSearchRecursive(arr, target: target)
        if result != -1 {
            print("查找 \(target): 找到于索引 \(result)")
        } else {
            print("查找 \(target): 未找到")
        }
    }
    
    print("\n=== 优化版本测试 ===")
    for target in targets {
        let result = interpolationSearchOptimized(arr, target: target)
        if result != -1 {
            print("查找 \(target): 找到于索引 \(result)")
        } else {
            print("查找 \(target): 未找到")
        }
    }
    
    // 浮点数版本测试
    print("\n=== 浮点数版本测试 ===")
    let doubleArr = [1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 11.0]
    let doubleTargets = [3.3, 7.7, 1.1, 11.0, 5.5]
    let epsilon = 0.0001
    
    for target in doubleTargets {
        let result = interpolationSearchFloat64(doubleArr, target: target, epsilon: epsilon)
        if result != -1 {
            print("查找 \(target): 找到于索引 \(result)")
        } else {
            print("查找 \(target): 未找到")
        }
    }
    
    // 性能分析
    print("\n=== 插值查找特点 ===")
    print("• 适用于均匀分布的数据")
    print("• 通过公式估算位置，跳过不必要的比较")
    print("• 对于均匀数据，性能优于二分查找")
    print("• 对于非均匀数据，可能退化为线性查找")
    print("• 时间复杂度：平均O(log log n)，最坏O(n)")
    print("• 空间复杂度：O(1)")
    
    // 与二分查找对比
    print("\n=== 与二分查找对比 ===")
    print("• 二分查找：总是取中间位置")
    print("• 插值查找：根据值估算位置")
    print("• 对于均匀数据，插值查找更快")
    print("• 对于非均匀数据，插值查找可能更慢")
    
    // 性能测试
    print("\n=== 性能测试 ===")
    let largeArr = Array(0..<10000).map { ($0 + 1) * 10 } // 均匀分布
    let testTarget = 5000
    
    let startTime = CFAbsoluteTimeGetCurrent()
    let perfResult = interpolationSearch(largeArr, target: testTarget)
    let endTime = CFAbsoluteTimeGetCurrent()
    
    print("数组大小: \(largeArr.count)")
    print("查找目标: \(testTarget)")
    print("查找结果: \(perfResult != -1 ? "找到" : "未找到")")
    print("执行时间: \((endTime - startTime) * 1000)ms")
}

// 执行主程序
main()

/*
打印结果
jarry@Mac interpolation-search % swift interpolation_search.swift
=== 插值查找演示 ===

数组 (均匀分布):
10 20 30 40 50 60 70 80 90 100 

=== 非递归版本测试 ===
查找 30: 找到于索引 2
查找 85: 未找到
查找 10: 找到于索引 0
查找 100: 找到于索引 9
查找 55: 未找到

=== 递归版本测试 ===
查找 30: 找到于索引 2
查找 85: 未找到
查找 10: 找到于索引 0
查找 100: 找到于索引 9
查找 55: 未找到

=== 优化版本测试 ===
查找 30: 找到于索引 2
查找 85: 未找到
查找 10: 找到于索引 0
查找 100: 找到于索引 9
查找 55: 未找到

=== 浮点数版本测试 ===
查找 3.3: 找到于索引 2
查找 7.7: 找到于索引 6
查找 1.1: 找到于索引 0
查找 11.0: 找到于索引 9
查找 5.5: 找到于索引 4

=== 插值查找特点 ===
• 适用于均匀分布的数据
• 通过公式估算位置，跳过不必要的比较
• 对于均匀数据，性能优于二分查找
• 对于非均匀数据，可能退化为线性查找
• 时间复杂度：平均O(log log n)，最坏O(n)
• 空间复杂度：O(1)

=== 与二分查找对比 ===
• 二分查找：总是取中间位置
• 插值查找：根据值估算位置
• 对于均匀数据，插值查找更快
• 对于非均匀数据，插值查找可能更慢

=== 性能测试 ===
数组大小: 10000
查找目标: 5000
查找结果: 找到
执行时间: 0.045ms
*/
