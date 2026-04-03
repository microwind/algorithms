// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// InsertSort 插入排序算法实现
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
    
    let duration = (endTime - startTime) * 1000 // 转换为毫秒
    print("\(name): \(String(format: "%.3f", duration))")
    printArray(testArr, label: name + "排序结果")
    print("") // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
let testData: [Int] = [7, 11, 9, 10, 12, 13, 8]

// binarySearch 二分查找插入位置
func binarySearch(_ arr: [Int], value: Int, left: Int, right: Int) -> Int {
    // 检查数组是否为空或范围无效
    if arr.isEmpty || left > right {
        return left
    }
    
    var left = left
    var right = right
    
    // 第一步：二分查找循环
    while left <= right {
        let mid = left + (right - left) / 2
        
        // 第二步：比较中间值与目标值
        if arr[mid] == value {
            return mid + 1 // 插入到相同元素后面，保持稳定性
        } else if arr[mid] < value {
            left = mid + 1
        } else {
            right = mid - 1
        }
    }
    
    // 第三步：返回插入位置
    return left
}

// insertSort1 插入排序基础版本 - 标准实现
//
// 算法思路：
// 1. 从第二个元素开始，将其作为"当前元素"
// 2. 将当前元素与前面已排序的元素比较
// 3. 找到合适的位置插入当前元素
// 4. 重复步骤1-3，直到所有元素都排序完成
//
// 生活类比：就像整理手中的扑克牌，
// 每次拿起一张新牌，插入到手中已排序牌的合适位置
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序
// 稳定性：稳定 - 保持相等元素的相对位置
func insertSort1(_ arr: inout [Int]) {
    print("insertSort1 standard:")
    
    // 第一步：从第二个元素开始遍历
    for i in 1..<arr.count {
        // 关键点：保存当前元素作为待插入元素
        let current = arr[i]
        var j = i - 1
        
        // 第二步：向前查找插入位置，同时移动元素
        while j >= 0 && arr[j] > current {
            // 大元素逐个右移
            arr[j + 1] = arr[j]
            j -= 1
        }
        
        // 第三步：插入当前元素
        arr[j + 1] = current
    }
    
    printArray(arr, label: "排序后数组")
}

// insertSort2 插入排序优化版本 - 二分查找插入位置
//
// 算法思路：
// 使用二分查找确定插入位置，减少比较次数
// 保持插入操作，但优化查找过程
//
// 优化效果：
// - 减少比较次数：从O(n)到O(log n)
// - 保持插入操作的时间复杂度
//
// 时间复杂度：平均O(n²)，最好O(n log n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序
// 稳定性：稳定
func insertSort2(_ arr: inout [Int]) {
    print("insertSort2 binary search:")
    
    // 第一步：从第二个元素开始遍历
    for i in 1..<arr.count {
        let current = arr[i]
        
        // 第二步：使用二分查找确定插入位置
        let insertPos = binarySearch(arr, value: current, left: 0, right: i - 1)
        
        // 第三步：移动元素为新元素腾出空间
        if insertPos < i {
            for j in (insertPos..<i).reversed() {
                arr[j + 1] = arr[j]
            }
            arr[insertPos] = current
        }
        // 如果insertPos == i，元素已经在正确位置，不需要移动
    }
    
    printArray(arr, label: "排序后数组")
}

// insertSort3 插入排序 - 哨兵版本
//
// 算法思路：
// 在数组开头添加哨兵元素，简化边界检查
// 减少循环中的条件判断
//
// 优化效果：
// - 减少边界检查
// - 简化代码逻辑
// - 轻微的性能提升
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序（忽略哨兵）
// 稳定性：稳定
func insertSort3(_ arr: inout [Int]) {
    print("insertSort3 sentinel:")
    
    if arr.isEmpty {
        return
    }
    
    // 第一步：找到最小值作为哨兵
    var minIndex = 0
    for i in 1..<arr.count {
        if arr[i] < arr[minIndex] {
            minIndex = i
        }
    }
    
    // 第二步：将最小值移到开头作为哨兵
    if minIndex != 0 {
        arr.swapAt(0, minIndex)
    }
    
    // 第三步：从第三个元素开始排序（第二个元素已经相对于哨兵有序）
    for i in 2..<arr.count {
        let current = arr[i]
        var j = i
        
        // 向前查找插入位置（哨兵保证不会越界）
        while arr[j - 1] > current {
            arr[j] = arr[j - 1]
            j -= 1
        }
        
        // 第四步：插入当前元素
        arr[j] = current
    }
    
    printArray(arr, label: "排序后数组")
}

// insertSort4 插入排序 - 希尔插入版本
//
// 算法思路：
// 结合希尔排序的增量概念
// 对不同间隔的子序列进行插入排序
//
// 优化效果：
// - 更好的初始数据分布
// - 减少总的移动次数
// - 适合部分有序的数据
//
// 时间复杂度：平均O(n^1.3)，取决于增量序列
// 空间复杂度：O(1) - 原地排序
// 稳定性：不稳定 - 增量排序可能破坏稳定性
func insertSort4(_ arr: inout [Int]) {
    print("insertSort4 shell insertion:")
    
    // 第一步：使用希尔增量序列
    let n = arr.count
    var gap = n / 2
    
    // 第二步：按增量进行分组排序
    while gap > 0 {
        // 对每个增量进行插入排序
        for i in gap..<n {
            let current = arr[i]
            var j = i
            
            // 第三步：在增量子序列中进行插入排序
            while j >= gap && arr[j - gap] > current {
                arr[j] = arr[j - gap]
                j -= gap
            }
            
            arr[j] = current
        }
        gap /= 2
    }
    
    printArray(arr, label: "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

func main() {
    // 测试1：标准版本
    performanceTest(insertSort1, arr: testData, name: "标准版本")

    // 测试2：二分查找版本
    performanceTest(insertSort2, arr: testData, name: "二分查找版本")

    // 测试3：哨兵版本
    performanceTest(insertSort3, arr: testData, name: "哨兵版本")

    // 测试4：希尔插入版本
    performanceTest(insertSort4, arr: testData, name: "希尔插入版本")

    print("=== 算法对比总结 ===")
    print("1. 标准版本：经典实现，易于理解")
    print("2. 二分查找版本：优化查找，减少比较")
    print("3. 哨兵版本：简化边界，提升性能")
    print("4. 希尔插入版本：增量排序，混合优化")
}

// 运行主程序
main()

/*
打印结果
jarry@Mac insertsort % swift insert_sort.swift
标准版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort1 standard:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
标准版本: 0.033
标准版本排序结果: [7, 8, 9, 10, 11, 12, 13]

二分查找版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort2 binary search:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
二分查找版本: 0.018
二分查找版本排序结果: [7, 8, 9, 10, 11, 12, 13]

哨兵版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort3 sentinel:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
哨兵版本: 0.006
哨兵版本排序结果: [7, 8, 9, 10, 11, 12, 13]

希尔插入版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort4 shell insertion:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
希尔插入版本: 0.005
希尔插入版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 标准版本：经典实现，易于理解
2. 二分查找版本：优化查找，减少比较
3. 哨兵版本：简化边界，提升性能
4. 希尔插入版本：增量排序，混合优化
*/