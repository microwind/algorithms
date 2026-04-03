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

import Foundation

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
func linearSearch<T: Equatable>(_ arr: [T], target: T) -> Int {
    // 边界检查
    guard !arr.isEmpty else {
        return -1
    }
    
    // 逐个遍历查找
    for (index, element) in arr.enumerated() {
        if element == target {
            return index // 找到目标，返回索引
        }
    }
    
    return -1 // 未找到
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
 * @return 包含所有匹配索引的数组
 */
func linearSearchAll<T: Equatable>(_ arr: [T], target: T) -> [Int] {
    var result: [Int] = []
    
    // 边界检查
    guard !arr.isEmpty else {
        return result
    }
    
    // 逐个遍历查找所有匹配项
    for (index, element) in arr.enumerated() {
        if element == target {
            result.append(index)
        }
    }
    
    return result
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
func linearSearchReverse<T: Equatable>(_ arr: [T], target: T) -> Int {
    // 边界检查
    guard !arr.isEmpty else {
        return -1
    }
    
    // 从后向前遍历查找
    for index in (0..<arr.count).reversed() {
        if arr[index] == target {
            return index // 找到目标，返回索引
        }
    }
    
    return -1 // 未找到
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
func linearSearchRecursive<T: Equatable>(_ arr: [T], target: T, index: Int = 0) -> Int {
    // 递归出口条件
    guard index < arr.count else {
        return -1
    }
    
    // 检查当前元素
    if arr[index] == target {
        return index
    }
    
    // 递归查找下一个元素
    return linearSearchRecursive(arr, target: target, index: index + 1)
}

/**
 * 主程序：演示线性查找功能
 */
func main() {
    print("=== 线性查找演示 ===\n")
    
    // 测试数据
    let arr = [64, 34, 25, 12, 22, 11, 90, 22]
    let target = 22
    
    print("数组:")
    print(arr.map { String($0) }.joined(separator: " "))
    print("目标元素: \(target)\n")
    
    // 基本查找测试
    print("=== 基本查找测试 ===")
    let index = linearSearch(arr, target: target)
    if index != -1 {
        print("基本查找: 找到于索引 \(index)")
    } else {
        print("基本查找: 未找到")
    }
    
    // 查找所有匹配项
    print("\n=== 查找所有匹配项 ===")
    let allIndices = linearSearchAll(arr, target: target)
    print("所有匹配位置: \(allIndices.map { String($0) }.joined(separator: " ")) (共\(allIndices.count)个)")
    
    // 反向查找测试
    print("\n=== 反向查找测试 ===")
    let reverseIndex = linearSearchReverse(arr, target: target)
    if reverseIndex != -1 {
        print("反向查找: 找到于索引 \(reverseIndex)")
    } else {
        print("反向查找: 未找到")
    }
    
    // 递归查找测试
    print("\n=== 递归查找测试 ===")
    let recursiveIndex = linearSearchRecursive(arr, target: target)
    if recursiveIndex != -1 {
        print("递归查找: 找到于索引 \(recursiveIndex)")
    } else {
        print("递归查找: 未找到")
    }
    
    // 查找不存在的元素
    print("\n=== 查找不存在的元素 ===")
    let notFound = linearSearch(arr, target: 100)
    print("查找100: \(notFound != -1 ? "找到" : "未找到")")
    
    // 字符串查找测试
    print("\n=== 字符串查找测试 ===")
    let strArr = ["apple", "banana", "cherry", "date", "banana"]
    let strTarget = "banana"
    
    print("字符串数组:")
    print(strArr.joined(separator: " "))
    print("目标字符串: \(strTarget)")
    
    let strIndex = linearSearch(strArr, target: strTarget)
    if strIndex != -1 {
        print("字符串查找: 找到于索引 \(strIndex)")
    } else {
        print("字符串查找: 未找到")
    }
    
    let strAllIndices = linearSearchAll(strArr, target: strTarget)
    print("所有匹配位置: \(strAllIndices.map { String($0) }.joined(separator: " ")) (共\(strAllIndices.count)个)")
    
    // 性能分析
    print("\n=== 线性查找特点 ===")
    print("• 算法简单，易于实现")
    print("• 适用于小规模数据和无序数据")
    print("• 时间复杂度：O(n)")
    print("• 空间复杂度：O(1)")
    print("• 可以查找所有匹配项")
    print("• 适合处理重复元素")
    
    // 与其他查找算法对比
    print("\n=== 与其他查找算法对比 ===")
    print("• 二分查找：O(log n)，但要求数组有序")
    print("• 哈希查找：O(1)，但需要额外空间")
    print("• 线性查找：O(n)，但无需预处理")
    print("• 选择算法取决于数据规模和是否有序")
    
    // 性能测试
    print("\n=== 性能测试 ===")
    let largeArr = Array(0..<10000)
    let testTarget = 9999
    
    let startTime = CFAbsoluteTimeGetCurrent()
    let perfIndex = linearSearch(largeArr, target: testTarget)
    let endTime = CFAbsoluteTimeGetCurrent()
    
    print("数组大小: \(largeArr.count)")
    print("查找目标: \(testTarget)")
    print("查找结果: \(perfIndex != -1 ? "找到" : "未找到")")
    print("执行时间: \((endTime - startTime) * 1000)ms")
}

// 执行主程序
main()

/*
打印结果
jarry@Mac linear-search % swift linear_search.swift
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

=== 递归查找测试 ===
递归查找: 找到于索引 4

=== 查找不存在的元素 ===
查找100: 未找到

=== 字符串查找测试 ===
字符串数组:
apple banana cherry date banana 
目标字符串: banana
字符串查找: 找到于索引 1
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
执行时间: 0.123ms
*/
