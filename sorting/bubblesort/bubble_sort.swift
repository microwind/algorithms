// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0
import Foundation

// BubbleSort 冒泡排序算法实现
// 提供四种不同的实现方式，适合不同场景和性能需求

// bubbleSort1 冒泡排序基础版本 - 升序排列
//
// 算法思路：
// 1. 从数组左端开始，依次比较相邻元素
// 2. 若左元素大于右元素，则交换位置
// 3. 继续向后比较，直到数组末尾
// 4. 重复以上过程，每轮都会将当前未排序部分的最大值"冒泡"到最后
//
// 生活类比：就像水中的气泡，轻的气泡会自然上浮到水面
// 在排序中，大的数字会逐渐"上浮"到数组的右侧
//
// 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
// 空间复杂度：O(1) - 只使用常数个额外变量
// 稳定性：稳定 - 相等元素的相对位置不会改变
func bubbleSort1(_ list: inout [Int]) {
    print("bubbleSort1 from left to right:")
    let len = list.count
    // 第一步：外循环控制排序轮数，每轮确定一个最大值的位置
    for i in 0..<len {
        // 内循环：控制比较次数，len-i-1 避免重复比较已排序部分
        for j in 0..<len - i - 1 {
            // 关键点：自左往右每两个进行比较，把大的交换到右侧
            if list[j] > list[j + 1] {
                // Swift特点：使用swapAt方法交换
                list.swapAt(j, j + 1)
            }
        }
    }
    printArray(list, "基础升序版本排序结果")
}

// bubbleSort2 冒泡排序基础版本 - 降序排列
//
// 算法思路：
// 与升序版本相反，从数组末尾开始比较
// 每轮将当前未排序部分的最小值"下沉"到左侧
//
// 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
// 空间复杂度：O(1) - 只使用常数个额外变量
// 稳定性：稳定 - 相等元素的相对位置不会改变
func bubbleSort2(_ list: inout [Int]) {
    print("bubbleSort2 from right to left:")
    let len = list.count
    // 第一步：外循环控制排序轮数，每轮确定一个最小值的位置
    for i in 0..<len {
        // 第二步：内循环从右向左比较，j > i 避免重复比较已排序部分
        for j in (i + 1..<len).reversed() {
            // 关键点：自右往左每两个进行比较，把小的交换到右侧
            if list[j - 1] < list[j] {
                // Swift特点：使用swapAt方法交换
                list.swapAt(j - 1, j)
            }
        }
    }
    printArray(list, "基础降序版本排序结果")
}

// bubbleSort3 冒泡排序优化版本
//
// 优化思路：
// 增加一个标志位，记录某一轮是否发生了元素交换
// 如果某一轮没有发生任何交换，说明数组已经完全有序
// 此时可以提前终止排序过程，避免不必要的比较
//
// 优化效果：
// - 对于完全有序的数组：时间复杂度从 O(n²) 优化到 O(n)
// - 对于部分有序的数组：也会有明显的性能提升
// - 对于完全逆序的数组：性能与基础版本相同
//
// 时间复杂度：最好O(n)，最坏O(n²)，空间复杂度：O(1)
// 稳定性：稳定 - 相等元素的相对位置不会改变
func bubbleSort3(_ list: inout [Int]) {
    print("bubbleSort3 add flag:")
    // 第一步：优化点：增加一个标志，如果某一轮没有进行过任何的交换
    // 则说明当前数组已排好序，则不必继续后面的遍历
    let len = list.count
    var flag = true

    // 第二步：外循环增加 flag 条件，当数组已有序时提前终止
    for i in 0..<len {
        if !flag {
            break
        }
        flag = false // 每轮开始时重置标志
        // 第三步：内循环控制比较次数，len-i-1 避免重复比较已排序部分
        for j in 0..<len - i - 1 {
            // 关键点：自左往右每两个进行比较，把大的交换到右侧
            if list[j] > list[j + 1] {
                flag = true // 发生交换，设置标志
                // Swift特点：使用swapAt方法交换
                list.swapAt(j, j + 1)
            }
        }
    }
    printArray(list, "优化版本排序结果")
}

// bubbleSort4 插入思想+交换排序，并非严格冒泡
//
// 算法思路：
// 将数组分为两部分：左侧已排序区域，右侧待排序区域
// 每次从待排序区域取出第一个元素，插入到已排序区域的正确位置
//
// 这种方法结合了插入排序的思想，在某些情况下性能更好
//
// 时间复杂度：O(n²)，空间复杂度：O(1)
// 稳定性：稳定 - 相等元素的相对位置不会改变
func bubbleSort4(_ list: inout [Int]) {
    print("bubbleSort4:")
    let len = list.count
    // 外循环：控制排序轮数，i 从 1 开始，因为第 0 个元素默认为已排序
    for i in 1..<len {
        // 内循环：在已排序区域中查找插入位置
        for j in 0..<i {
            // 关键点：如果待插入元素小于已排序区域的某个元素，则交换
            if list[j] > list[i] {
                // Swift特点：使用swapAt方法交换
                list.swapAt(j, i)
            }
        }
    }
    printArray(list, "插入式版本排序结果")
}

/**
 * 冒泡排序标准版本 - 来自C old版本的标准实现
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 将元素分配到对应桶中
 * 4. 对每个桶进行排序
 * 5. 合并所有桶的元素
 * 
 * 特点：
 * - 标准：经典的冒泡排序算法
 * - 简单直接：直接使用swapAt排序
 * - 高效实现：减少不必要的复杂性
 * 
 * - Parameter list: 待排序的整数数组
 */
func bubbleSort5(_ list: inout [Int]) {
    print("bubbleSort5 original standard version:")
    let len = list.count
    
    // 外循环：控制排序轮数，每轮确定一个最大值的位置
    for i in 0..<len {
        // 内循环：控制比较次数，len-i-1 避免重复比较已排序部分
        for j in 0..<len - i - 1 {
            // 关键点：自左往右每两个进行比较，把大的交换到右侧
            if list[j] > list[j + 1] {
                // Swift特点：使用swapAt方法交换
                list.swapAt(j, j + 1)
            }
        }
    }
    printArray(list, "标准版本排序结果")
}

/**
 * 冒泡排序标志位版本 - 来自C old版本的标志位实现
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 创建指定数量的桶
 * 4. 将元素分配到对应桶中
 * 5. 对每个桶进行排序
 * 6. 合并所有桶的元素
 * 
 * 特点：
 * - 标志位：使用固定桶数量的实现
 * - 桶数量控制：可控制桶的数量
 * - 负载均衡：更好的数据分布
 * 
 * - Parameter list: 待排序的整数数组
 */
func bubbleSort6(_ list: inout [Int]) {
    print("bubbleSort6 original flag version:")
    let len = list.count
    var flag = true

    // 外循环：增加 flag 条件，当数组已有序时提前终止
    for i in 0..<len {
        if !flag {
            break
        }
        flag = false // 每轮开始时重置标志
        // 内循环：控制比较次数，len-i-1 避免重复比较已排序部分
        for j in 0..<len - i - 1 {
            // 关键点：自左往右每两个进行比较，把大的交换到右侧
            if list[j] > list[j + 1] {
                flag = true // 发生交换，设置标志
                // Swift特点：使用swapAt方法交换
                list.swapAt(j, j + 1)
            }
        }
    }
    printArray(list, "标志位版本排序结果")
}

/**
 * 打印数组内容的辅助函数
 * - Parameter list: 要打印的数组
 * - Parameter label: 数组的标签说明
 */
func printArray(_ list: [Int], _ label: String) {
    print("\(label): [\(list.map(String.init).joined(separator: ", "))]")
}

/**
 * 性能测试辅助函数
 * - Parameter sortFunc: 排序函数
 * - Parameter list: 测试数组
 * - Parameter name: 版本名称
 */
func performanceTest(_ sortFunc: (inout [Int]) -> Void, _ list: [Int], _ name: String) {
    var testList = list
    printArray(testList, "\(name)原始数组")
    
    let startTime = CFAbsoluteTimeGetCurrent()
    sortFunc(&testList)
    let endTime = CFAbsoluteTimeGetCurrent()
    
    let duration = (endTime - startTime) * 1000
    print("\(name): \(String(format: "%.3f", duration))ms")
    print()
}

/**
 * 主测试函数
 */
func main() {
    print("=== 冒泡排序算法演示 ===")
    print()

    let testData = [7, 11, 9, 10, 12, 13, 8]

    // 测试1：基础升序版本
    performanceTest(bubbleSort1, testData, "基础升序版本")

    // 测试2：基础降序版本
    performanceTest(bubbleSort2, testData, "基础降序版本")

    // 测试3：优化版本
    performanceTest(bubbleSort3, testData, "优化版本")

    // 测试4：插入式版本
    performanceTest(bubbleSort4, testData, "插入式版本")

    // 测试5：标准版本
    performanceTest(bubbleSort5, testData, "标准版本")

    // 测试6：标志位版本
    performanceTest(bubbleSort6, testData, "标志位版本")

    print("=== 算法对比总结 ===")
    print("1. 基础版本：简单易懂，适合学习算法原理")
    print("2. 降序版本：展示算法的灵活性，可按需排序")
    print("3. 优化版本：通过标志位优化，适合实际应用")
    print("4. 插入式版本：结合其他排序思想，性能更稳定")
    print("5. 标准版本：标准冒泡排序实现，直接排序")
    print("6. 标志位版本：标志位实现，固定桶数量")
}

// 执行测试
main()

/* 打印结果
jarry@Mac bubblesort % swift bubble_sort.swift
=== 冒泡排序算法演示 ===

基础升序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort1 from left to right:
基础升序版本排序结果: [7, 8, 9, 10, 11, 12, 13]
基础升序版本: 0.029ms

基础降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort2 from right to left:
基础降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]
基础降序版本: 0.016ms

优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort3 add flag:
优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]
优化版本: 0.007ms

插入式版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort4:
插入式版本排序结果: [7, 8, 9, 10, 11, 12, 13]
插入式版本: 0.006ms

标准版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort5 original standard version:
标准版本排序结果: [7, 8, 9, 10, 11, 12, 13]
标准版本: 0.006ms

标志位版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort6 original flag version:
标志位版本排序结果: [7, 8, 9, 10, 11, 12, 13]
标志位版本: 0.006ms

=== 算法对比总结 ===
1. 基础版本：简单易懂，适合学习算法原理
2. 降序版本：展示算法的灵活性，可按需排序
3. 优化版本：通过标志位优化，适合实际应用
4. 插入式版本：结合其他排序思想，性能更稳定
5. 标准版本：标准冒泡排序实现，直接排序
6. 标志位版本：标志位实现，固定桶数量
*/
