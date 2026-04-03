// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// MergeSort 归并排序算法实现
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
 * 合并两个有序数组
 * 
 * 步骤1：初始化结果数组和索引指针
 * 步骤2：按顺序合并两个有序数组
 * 步骤3：处理剩余元素
 * 步骤4：返回合并结果
 * 
 * 关键点：
 * - 使用索引指针避免不必要的内存分配
 * - 利用Swift的数组特性高效处理剩余元素
 * - 保持算法的稳定性
 */
func merge(_ left: [Int], _ right: [Int]) -> [Int] {
    // 步骤1：初始化结果数组和索引指针
    // 关键点：预分配足够容量，避免多次扩容
    var result = [Int]()
    var leftIndex = 0
    var rightIndex = 0
    
    // 步骤2：按顺序合并两个有序数组
    // 关键点：比较两个数组的当前元素，选择较小的放入结果数组
    while leftIndex < left.count && rightIndex < right.count {
        // 关键点：选择较小的元素放入结果数组
        if left[leftIndex] <= right[rightIndex] {
            result.append(left[leftIndex])
            leftIndex += 1
        } else {
            result.append(right[rightIndex])
            rightIndex += 1
        }
    }
    
    // 步骤3：处理剩余元素
    // 关键点：将未处理完的数组元素直接添加到结果数组
    // Swift特点：使用append高效处理剩余元素
    while leftIndex < left.count {
        result.append(left[leftIndex])
        leftIndex += 1
    }
    while rightIndex < right.count {
        result.append(right[rightIndex])
        rightIndex += 1
    }
    
    // 步骤4：返回合并结果
    // 关键点：返回完全有序的合并数组
    return result
}

/**
 * 递归归并排序函数
 * 
 * 步骤1：检查递归终止条件
 * 步骤2：分割数组为两半
 * 步骤3：递归排序左右子数组
 * 步骤4：合并两个有序子数组
 * 
 * 关键点：
 * - 基础情况：数组长度小于等于1时已经有序
 * - 使用整数除法计算中间位置
 * - 利用Swift的数组切片特性高效分割数组
 * - 递归调用直到基础情况
 */
func mergeSortRecursive(_ arr: [Int]) -> [Int] {
    // 步骤1：检查递归终止条件
    // 关键点：数组长度小于等于1时已经有序，直接返回
    if arr.count <= 1 {
        return arr
    }
    
    // 步骤2：分割数组为两半
    // 关键点：使用整数除法计算中间位置
    // Swift特点：使用数组切片分割数组，避免内存分配
    let middle = arr.count / 2
    let left = Array(arr[0..<middle])
    let right = Array(arr[middle...])
    
    // 步骤3：递归排序左右子数组
    // 关键点：分别对左右两部分进行递归排序
    let sortedLeft = mergeSortRecursive(left)
    let sortedRight = mergeSortRecursive(right)
    
    // 步骤4：合并两个有序子数组
    // 关键点：将两个有序子数组合并成一个有序数组
    return merge(sortedLeft, sortedRight)
}

/**
 * 归并排序基础版本 - 递归实现
 * 
 * 算法原理：
 * 1. 将数组递归地分成两半，直到每个子数组只有一个元素
 * 2. 将相邻的两个有序子数组合并成一个更大的有序数组
 * 3. 重复合并过程，直到最终得到一个完全有序的数组
 * 
 * 生活类比：就像整理一副扑克牌，先把牌分成两堆，
 * 每堆分别整理好，然后将两堆有序地合并在一起
 * 
 * 时间复杂度：O(n log n) - 无论如何都需要O(n log n)次比较
 * 空间复杂度：O(n) - 需要额外的数组空间来存储合并结果
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
func mergeSort1(_ arr: inout [Int]) {
    print("mergeSort1 recursive:")
    arr = mergeSortRecursive(arr)
    printArray(arr, label: "排序后数组")
}

/**
 * 原地合并两个有序子数组
 * 
 * 步骤1：创建临时数组存储左半部分
 * 步骤2：初始化合并指针
 * 步骤3：按顺序合并两个有序子数组
 * 步骤4：处理左数组剩余元素
 * 步骤5：完成原地合并
 * 
 * 关键点：
 * - 使用临时数组存储左半部分，避免数据覆盖
 * - 三个指针分别跟踪左数组、右数组和合并位置
 * - 保持算法的稳定性
 */
func mergeInPlace(_ arr: inout [Int], left: Int, mid: Int, right: Int) {
    // 步骤1：创建临时数组存储左半部分
    // 关键点：避免在合并过程中覆盖未处理的数据
    let leftArr = Array(arr[left...mid])
    
    // 步骤2：初始化合并指针
    // 关键点：i指向左数组，j指向右数组，k指向合并位置
    var i = 0 // 左数组索引
    var j = mid + 1 // 右数组索引
    var k = left // 合并位置索引
    
    // 步骤3：按顺序合并两个有序子数组
    // 关键点：比较两个数组的当前元素，选择较小的放入原数组
    while i < leftArr.count && j <= right {
        if leftArr[i] <= arr[j] {
            arr[k] = leftArr[i]
            i += 1
        } else {
            arr[k] = arr[j]
            j += 1
        }
        k += 1
    }
    
    // 步骤4：处理左数组剩余元素
    // 关键点：左数组可能还有未处理的元素
    while i < leftArr.count {
        arr[k] = leftArr[i]
        i += 1
        k += 1
    }
}

/**
 * 递归归并排序函数 - 原地版本
 * 
 * 步骤1：检查递归终止条件
 * 步骤2：计算中间位置
 * 步骤3：递归排序左半部分
 * 步骤4：递归排序右半部分
 * 步骤5：原地合并两个有序部分
 * 
 * 关键点：
 * - 使用索引范围而不是数组切片，避免内存分配
 * - 原地合并减少空间复杂度
 * - 递归深度为O(log n)
 */
func mergeSortInPlaceRecursive(_ arr: inout [Int], left: Int, right: Int) {
    // 步骤1：检查递归终止条件
    // 关键点：left >= right时子数组已经有序
    if left < right {
        // 步骤2：计算中间位置
        // 关键点：使用整数除法，避免溢出
        let mid = (left + right) / 2
        
        // 步骤3：递归排序左半部分
        // 关键点：将数组分成[left, mid]和[mid+1, right]两部分
        mergeSortInPlaceRecursive(&arr, left: left, right: mid)
        
        // 步骤4：递归排序右半部分
        // 关键点：确保右半部分也有序
        mergeSortInPlaceRecursive(&arr, left: mid + 1, right: right)
        
        // 步骤5：原地合并两个有序部分
        // 关键点：在原数组上进行合并操作
        mergeInPlace(&arr, left: left, mid: mid, right: right)
    }
}

/**
 * 归并排序优化版本 - 原地合并
 * 
 * 优化思路：
 * 减少空间复杂度，尝试在原数组上进行合并操作
 * 使用索引操作而不是创建新数组
 * 
 * 优化效果：
 * - 减少了内存分配
 * - 提高了空间效率
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(log n) - 仅递归栈空间
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
func mergeSort2(_ arr: inout [Int]) {
    print("mergeSort2 in-place:")
    if !arr.isEmpty {
        mergeSortInPlaceRecursive(&arr, left: 0, right: arr.count - 1)
    }
    printArray(arr, label: "排序后数组")
}

/**
 * 合并两个有序子数组 - 迭代版本
 */
func mergeIterative(_ arr: inout [Int], temp: inout [Int], left: Int, mid: Int, right: Int) {
    var i = left // 左子数组索引
    var j = mid + 1 // 右子数组索引
    var k = left // 临时数组索引
    
    // 合并到临时数组
    while i <= mid && j <= right {
        if arr[i] <= arr[j] {
            temp[k] = arr[i]
            i += 1
        } else {
            temp[k] = arr[j]
            j += 1
        }
        k += 1
    }
    
    // 复制左子数组剩余元素
    while i <= mid {
        temp[k] = arr[i]
        i += 1
        k += 1
    }
    
    // 复制右子数组剩余元素
    while j <= right {
        temp[k] = arr[j]
        j += 1
        k += 1
    }
    
    // 将临时数组复制回原数组
    for i in left...right {
        arr[i] = temp[i]
    }
}

/**
 * 归并排序 - 迭代版本
 * 
 * 算法思路：
 * 使用迭代方式代替递归，避免递归栈开销
 * 从小规模合并开始，逐步扩大合并规模
 * 
 * 优化效果：
 * - 避免了递归调用的开销
 * - 更好的缓存局部性
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n) - 需要临时数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
func mergeSort3(_ arr: inout [Int]) {
    print("mergeSort3 iterative:")
    
    let n = arr.count
    var temp = Array(repeating: 0, count: n)
    
    // 迭代合并，步长从1开始翻倍
    var size = 1
    while size < n {
        for left in stride(from: 0, to: n - size, by: 2 * size) {
            let mid = left + size - 1
            let right = min(left + 2 * size - 1, n - 1)
            mergeIterative(&arr, temp: &temp, left: left, mid: mid, right: right)
        }
        size *= 2
    }
    
    printArray(arr, label: "排序后数组")
}

/**
 * 合并两个相邻的有序子数组 - 自底向上版本
 */
func mergeBottomUp(_ arr: inout [Int], temp: inout [Int], left: Int, mid: Int, right: Int) {
    var i = left
    var j = mid
    var k = left
    
    // 合并两个有序子数组到临时数组
    while i < mid && j <= right {
        if arr[i] <= arr[j] {
            temp[k] = arr[i]
            i += 1
        } else {
            temp[k] = arr[j]
            j += 1
        }
        k += 1
    }
    
    // 复制剩余元素
    while i < mid {
        temp[k] = arr[i]
        i += 1
        k += 1
    }
    while j <= right {
        temp[k] = arr[j]
        j += 1
        k += 1
    }
    
    // 复制回原数组
    for i in left...right {
        arr[i] = temp[i]
    }
}

/**
 * 归并排序 - 自底向上版本
 * 
 * 算法思路：
 * 先将数组分成单个元素，然后两两合并
 * 逐步扩大合并规模，直到整个数组有序
 * 
 * 优化效果：
 * - 更好的内存访问模式
 * - 适合外部排序（处理大数据）
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n) - 需要临时数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
func mergeSort4(_ arr: inout [Int]) {
    print("mergeSort4 bottom-up:")
    
    let n = arr.count
    var temp = Array(repeating: 0, count: n)
    
    // 自底向上合并
    var width = 1
    while width < n {
        for i in stride(from: 0, to: n, by: 2 * width) {
            let left = i
            let mid = min(i + width, n)
            let right = min(i + 2 * width, n)
            
            if mid < right {
                mergeBottomUp(&arr, temp: &temp, left: left, mid: mid, right: right - 1)
            }
        }
        width *= 2
    }
    
    printArray(arr, label: "排序后数组")
}

/**
 * 归并排序 - 非递归合并版本
 * 
 * 算法思路：
 * 使用非递归方式进行合并操作，避免递归调用
 * 通过迭代方式处理合并过程，提高内存效率
 * 
 * 优化效果：
 * - 避免递归栈开销
 * - 更好的内存访问模式
 * - 适合大数据处理
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n) - 需要临时数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
func mergeSort5(_ arr: inout [Int]) {
    print("mergeSort5 non-recursive merge:")
    
    /**
     * 非递归合并两个有序子数组
     * 
     * 步骤1：初始化索引指针
     * 步骤2：合并到临时数组
     * 步骤3：复制左子数组剩余元素
     * 步骤4：复制右子数组剩余元素
     * 步骤5：将临时数组复制回原数组
     * 
     * 关键点：
     * - 使用索引指针避免不必要的内存分配
     * - 在临时数组中进行合并操作
     * - 最后将结果复制回原数组
     */
    func mergeNonRecursive(_ arr: inout [Int], _ temp: inout [Int], left: Int, mid: Int, right: Int) {
        // 步骤1：初始化索引指针
        // 关键点：i指向左子数组，j指向右子数组，k指向临时数组
        var i = left      // 左子数组索引
        var j = mid + 1   // 右子数组索引
        var k = left      // 临时数组索引
        
        // 步骤2：合并到临时数组
        // 关键点：按顺序合并两个有序子数组
        while i <= mid && j <= right {
            if arr[i] <= arr[j] {
                temp[k] = arr[i]
                i += 1
            } else {
                temp[k] = arr[j]
                j += 1
            }
            k += 1
        }
        
        // 步骤3：复制左子数组剩余元素
        // 关键点：左子数组可能还有未处理的元素
        while i <= mid {
            temp[k] = arr[i]
            i += 1
            k += 1
        }
        
        // 步骤4：复制右子数组剩余元素
        // 关键点：右子数组可能还有未处理的元素
        while j <= right {
            temp[k] = arr[j]
            j += 1
            k += 1
        }
        
        // 步骤5：将临时数组复制回原数组
        // 关键点：使用循环逐个复制，确保数据正确性
        // Swift特点：也可以使用赋值操作，但循环更直观
        for index in left...right {
            arr[index] = temp[index]
        }
    }
    
    let n = arr.count
    if n <= 1 {
        return
    }
    
    // 步骤1：创建临时数组
    // 关键点：临时数组用于存储合并过程中的中间结果
    var temp = Array(repeating: 0, count: n)
    
    // 步骤2：非递归合并过程
    // 关键点：通过迭代方式模拟递归的合并过程
    var size = 1
    while size < n {
        // 步骤3：处理所有相邻的子数组对
        // 关键点：每次处理两个大小为size的相邻子数组
        for left in stride(from: 0, to: n - size, by: 2 * size) {
            // 步骤4：计算当前合并的边界
            // 关键点：确定左子数组 [left, mid] 和右子数组 [mid+1, right]
            let mid = left + size - 1
            let right = min(left + 2 * size - 1, n - 1)
            
            // 步骤5：执行非递归合并
            // 关键点：使用迭代方式合并两个有序子数组
            mergeNonRecursive(&arr, &temp, left: left, mid: mid, right: right)
        }
        size *= 2
    }
    
    printArray(arr, label: "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

// 测试1：递归版本（基于slice分割）
performanceTest(mergeSort1, arr: testData, name: "递归版本（基于slice分割）")

// 测试2：原地合并版本
performanceTest(mergeSort2, arr: testData, name: "原地合并版本")

// 测试3：迭代版本
performanceTest(mergeSort3, arr: testData, name: "迭代版本")

// 测试4：自底向上版本
performanceTest(mergeSort4, arr: testData, name: "自底向上版本")

// 测试5：非递归合并版本
performanceTest(mergeSort5, arr: testData, name: "非递归合并版本")

print("=== 算法对比总结 ===")
print("1. 递归版本（基于slice分割）：利用Swift语言特性，代码简洁")
print("2. 原地版本：空间优化，减少内存使用")
print("3. 迭代版本：避免递归，性能稳定")
print("4. 底向上版本：适合大数据，外部排序")
print("5. 非递归合并版本：迭代合并，高效内存")

/*
打印结果
jarry@Mac mergesort % swift merge_sort.swift
递归版本（基于slice分割）原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort1 recursive:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
递归版本（基于slice分割）: 0.035ms
递归版本（基于slice分割）排序结果: [7, 8, 9, 10, 11, 12, 13]

原地合并版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort2 in-place:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
原地合并版本: 0.009ms
原地合并版本排序结果: [7, 8, 9, 10, 11, 12, 13]

迭代版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort3 iterative:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
迭代版本: 0.100ms
迭代版本排序结果: [7, 8, 9, 10, 11, 12, 13]

自底向上版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort4 bottom-up:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
自底向上版本: 0.009ms
自底向上版本排序结果: [7, 8, 9, 10, 11, 12, 13]

非递归合并版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort5 non-recursive merge:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
非递归合并版本: 0.009ms
非递归合并版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归版本（基于slice分割）：利用Swift语言特性，代码简洁
2. 原地版本：空间优化，减少内存使用
3. 迭代版本：避免递归，性能稳定
4. 底向上版本：适合大数据，外部排序
5. 非递归合并版本：迭代合并，高效内存
*/
