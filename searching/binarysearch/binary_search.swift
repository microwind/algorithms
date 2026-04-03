/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 二分查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

import Foundation

/**
 * 二分查找基础版本 - 非递归实现
 * 
 * 算法原理：
 * 1. 确定查找范围：left = 0, right = arr.count - 1
 * 2. 计算中间位置：mid = (left + right) / 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * 生活类比：就像在字典中查单词，
 * 每次都翻到中间位置，然后根据字母顺序决定向前还是向后翻
 * 
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)
 * 前提条件：数组必须有序
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @return 目标索引，未找到返回-1
 */
func binarySearch1(_ arr: [Int], target: Int) -> Int {
    var left = 0
    var right = arr.count - 1
    
    // 查找区间长度小于1时停止
    while left <= right {
        // 计算中间位置，防止整数溢出
        let midIndex = left + (right - left) / 2
        let mid = arr[midIndex]
        
        // 中间项等于目标项则返回下标
        if target == mid {
            return midIndex
        } else if target > mid {
            // 大于中间项，查找右侧
            left = midIndex + 1
        } else {
            // 小于中间项，查找左侧
            right = midIndex - 1
        }
    }
    
    return -1 // 未找到
}

/**
 * 二分查找递归版本
 * 
 * 算法思路：
 * 使用递归方式实现二分查找
 * 每次递归缩小查找范围
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @param left 左边界
 * @param right 右边界
 * @return 目标索引，未找到返回-1
 */
func binarySearch2(_ arr: [Int], target: Int, left: Int = 0, right: Int? = nil) -> Int {
    let right = right ?? arr.count - 1
    
    // 递归出口条件
    if left > right {
        return -1
    }
    
    // 计算中间位置
    let midIndex = left + (right - left) / 2
    let mid = arr[midIndex]
    
    // 中间值等于目标值，找到目标
    if target == mid {
        return midIndex
    } else if target > mid {
        // 目标大于中间值，递归查找右半部分
        return binarySearch2(arr, target: target, left: midIndex + 1, right: right)
    } else {
        // 目标小于中间值，递归查找左半部分
        return binarySearch2(arr, target: target, left: left, right: midIndex - 1)
    }
}

/**
 * 二分查找 - 查找第一个匹配项
 * 
 * 算法思路：
 * 当数组中有重复元素时，查找第一个出现的元素
 * 找到目标后继续向左查找，确保是第一个
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @return 第一个匹配项的索引，未找到返回-1
 */
func binarySearchFirst(_ arr: [Int], target: Int) -> Int {
    var left = 0
    var right = arr.count - 1
    var result = -1
    
    while left <= right {
        let midIndex = left + (right - left) / 2
        let mid = arr[midIndex]
        
        if target == mid {
            result = midIndex // 记录找到的位置
            right = midIndex - 1 // 继续向左查找
        } else if target > mid {
            left = midIndex + 1
        } else {
            right = midIndex - 1
        }
    }
    
    return result
}

/**
 * 二分查找 - 查找最后一个匹配项
 * 
 * 算法思路：
 * 当数组中有重复元素时，查找最后一个出现的元素
 * 找到目标后继续向右查找，确保是最后一个
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @return 最后一个匹配项的索引，未找到返回-1
 */
func binarySearchLast(_ arr: [Int], target: Int) -> Int {
    var left = 0
    var right = arr.count - 1
    var result = -1
    
    while left <= right {
        let midIndex = left + (right - left) / 2
        let mid = arr[midIndex]
        
        if target == mid {
            result = midIndex // 记录找到的位置
            left = midIndex + 1 // 继续向右查找
        } else if target > mid {
            left = midIndex + 1
        } else {
            right = midIndex - 1
        }
    }
    
    return result
}

/**
 * 二分查找 - 泛型版本
 * 
 * 算法扩展：
 * 支持任意可比较类型的数组查找
 * 使用泛型提高代码复用性
 * 
 * @param arr 有序数组
 * @param target 目标值
 * @return 目标索引，未找到返回-1
 */
func binarySearchGeneric<T: Comparable>(_ arr: [T], target: T) -> Int {
    var left = 0
    var right = arr.count - 1
    
    while left <= right {
        let midIndex = left + (right - left) / 2
        let mid = arr[midIndex]
        
        if target == mid {
            return midIndex
        } else if target > mid {
            left = midIndex + 1
        } else {
            right = midIndex - 1
        }
    }
    
    return -1
}

/**
 * 主程序：演示二分查找功能
 */
func main() {
    print("=== 二分查找演示 ===\n")
    
    // 测试数据：有序数组
    let arr = [2, 3, 8, 10, 10, 13, 20, 25, 30, 35]
    let target = 10
    
    print("数组:")
    print(arr.map { String($0) }.joined(separator: " "))
    print("目标元素: \(target)\n")
    
    // 基本查找测试
    print("=== 基本查找测试 ===")
    let index1 = binarySearch1(arr, target: target)
    if index1 != -1 {
        print("非递归查找: 找到于索引 \(index1)")
    } else {
        print("非递归查找: 未找到")
    }
    
    // 递归查找测试
    print("\n=== 递归查找测试 ===")
    let index2 = binarySearch2(arr, target: target)
    if index2 != -1 {
        print("递归查找: 找到于索引 \(index2)")
    } else {
        print("递归查找: 未找到")
    }
    
    // 查找第一个匹配项
    print("\n=== 查找第一个匹配项 ===")
    let firstIndex = binarySearchFirst(arr, target: target)
    if firstIndex != -1 {
        print("第一个匹配: 找到于索引 \(firstIndex)")
    } else {
        print("第一个匹配: 未找到")
    }
    
    // 查找最后一个匹配项
    print("\n=== 查找最后一个匹配项 ===")
    let lastIndex = binarySearchLast(arr, target: target)
    if lastIndex != -1 {
        print("最后一个匹配: 找到于索引 \(lastIndex)")
    } else {
        print("最后一个匹配: 未找到")
    }
    
    // 查找不存在的元素
    print("\n=== 查找不存在的元素 ===")
    let notFound = binarySearch1(arr, target: 100)
    print("查找100: \(notFound != -1 ? "找到" : "未找到")")
    
    // 泛型查找测试
    print("\n=== 泛型查找测试 ===")
    let strArr = ["apple", "banana", "cherry", "date", "elderberry"]
    let strTarget = "cherry"
    
    print("字符串数组:")
    print(strArr.joined(separator: " "))
    print("目标字符串: \(strTarget)")
    
    let strIndex = binarySearchGeneric(strArr, target: strTarget)
    if strIndex != -1 {
        print("泛型查找: 找到于索引 \(strIndex)")
    } else {
        print("泛型查找: 未找到")
    }
    
    // 性能分析
    print("\n=== 二分查找特点 ===")
    print("• 算法高效，时间复杂度O(log n)")
    print("• 要求数组必须有序")
    print("• 空间复杂度：O(1)")
    print("• 适合大规模数据查找")
    print("• 可以处理重复元素")
    
    // 与其他查找算法对比
    print("\n=== 与其他查找算法对比 ===")
    print("• 线性查找：O(n)，无需预处理")
    print("• 二分查找：O(log n)，要求数组有序")
    print("• 哈希查找：O(1)，但需要额外空间")
    print("• 插值查找：O(log log n)，要求数据均匀分布")
    print("• 选择算法取决于数据规模和特性")
    
    // 性能测试
    print("\n=== 性能测试 ===")
    let largeArr = Array(0..<100000)
    let testTarget = 99999
    
    let startTime = CFAbsoluteTimeGetCurrent()
    let perfIndex = binarySearch1(largeArr, target: testTarget)
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
jarry@Mac binarysearch % swift binary_search.swift
=== 二分查找演示 ===

数组:
2 3 8 10 10 13 20 25 30 35 
目标元素: 10

=== 基本查找测试 ===
非递归查找: 找到于索引 3

=== 递归查找测试 ===
递归查找: 找到于索引 3

=== 查找第一个匹配项 ===
第一个匹配: 找到于索引 3

=== 查找最后一个匹配项 ===
最后一个匹配: 找到于索引 4

=== 查找不存在的元素 ===
查找100: 未找到

=== 泛型查找测试 ===
字符串数组:
apple banana cherry date elderberry 
目标字符串: cherry
泛型查找: 找到于索引 2

=== 二分查找特点 ===
• 算法高效，时间复杂度O(log n)
• 要求数组必须有序
• 空间复杂度：O(1)
• 适合大规模数据查找
• 可以处理重复元素

=== 与其他查找算法对比 ===
• 线性查找：O(n)，无需预处理
• 二分查找：O(log n)，要求数组有序
• 哈希查找：O(1)，但需要额外空间
• 插值查找：O(log log n)，要求数据均匀分布
• 选择算法取决于数据规模和特性

=== 性能测试 ===
数组大小: 100000
查找目标: 99999
查找结果: 找到
执行时间: 0.089ms
*/
