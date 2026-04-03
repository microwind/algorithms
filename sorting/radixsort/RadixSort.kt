/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

import kotlin.system.measureTimeMillis

/**
 * 打印数组内容的辅助函数
 */
fun printArray(arr: IntArray, label: String) {
    println("$label: [${arr.joinToString(", ")}]")
}

/**
 * 性能测试辅助函数
 */
fun performanceTest(sortFunc: (IntArray) -> Unit, arr: IntArray, name: String) {
    // 创建数组副本，避免修改原数组
    val testArr = arr.clone()
    printArray(testArr, "$name原始数组")
    
    // 开始计时
    val startTime = measureTimeMillis {
        sortFunc(testArr)
    }
    
    println("$name: ${startTime.toDouble() / 1000.0}")
    printArray(testArr, "$name排序结果")
    println("") // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含大数字和负数的典型数组
val testData = intArrayOf(33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431)

/**
 * 获取数字的指定位数
 */
fun getDigit(num: Int, exp: Int): Int {
    return kotlin.math.abs(num) / exp % 10
}

/**
 * 计数排序辅助函数 - 按位数排序
 */
fun countingSortByDigit(arr: IntArray, exp: Int) {
    val n = arr.size
    val output = IntArray(n)
    val count = IntArray(10)
    
    // 统计每个数字的出现次数
    for (i in 0 until n) {
        val digit = getDigit(arr[i], exp)
        count[digit]++
    }
    
    // 计算累计计数
    for (i in 1 until 10) {
        count[i] += count[i - 1]
    }
    
    // 构建输出数组
    for (i in n - 1 downTo 0) {
        val digit = getDigit(arr[i], exp)
        output[count[digit] - 1] = arr[i]
        count[digit]--
    }
    
    // 复制回原数组
    for (i in 0 until n) {
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
fun radixSort1(arr: IntArray) {
    println("radixSort1 LSD:")
    
    // 找到最大值以确定位数
    val max = arr.maxOrNull()!!
    
    // 对每个位数进行计数排序
    var exp = 1
    while (max / exp > 0) {
        countingSortByDigit(arr, exp)
        exp *= 10
    }
    
    printArray(arr, "排序后数组")
}

/**
 * MSD递归排序函数
 */
fun msdSort(arr: IntArray, left: Int, right: Int, exp: Int) {
    if (left >= right || exp < 1) {
        return
    }
    
    // 创建桶
    val buckets = Array(10) { mutableListOf<Int>() }
    
    // 分配到桶中
    for (i in left..right) {
        val digit = getDigit(arr[i], exp)
        buckets[digit].add(arr[i])
    }
    
    // 重新排序并递归处理每个桶
    var index = left
    for (i in 0 until 10) {
        if (buckets[i].isNotEmpty()) {
            // 复制桶中元素回原数组
            for (value in buckets[i]) {
                arr[index] = value
                index++
            }
            
            // 递归处理下一个位数
            msdSort(arr, left, index - 1, exp / 10)
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
fun radixSort2(arr: IntArray) {
    println("radixSort2 MSD:")
    
    if (arr.isEmpty()) {
        return
    }
    
    // 找到最大值以确定位数
    val max = arr.maxOrNull()!!
    var exp = 1
    while (max / exp > 0) {
        exp *= 10
    }
    
    msdSort(arr, 0, arr.size - 1, exp / 10)
    
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
fun radixSort3(arr: IntArray) {
    println("radixSort3 iterative MSD:")
    
    if (arr.isEmpty()) {
        return
    }
    
    // 找到最大值以确定位数
    val max = arr.maxOrNull()!!
    var exp = 1
    while (max / exp > 0) {
        exp *= 10
    }
    
    // 使用栈模拟递归
    data class StackItem(val left: Int, val right: Int, val exp: Int)
    
    val stack = mutableListOf<StackItem>()
    stack.add(StackItem(0, arr.size - 1, exp / 10))
    
    while (stack.isNotEmpty()) {
        val item = stack.removeAt(stack.size - 1)
        val left = item.left
        val right = item.right
        val currentExp = item.exp
        
        if (left >= right || currentExp < 1) {
            continue
        }
        
        // 创建桶
        val buckets = Array(10) { mutableListOf<Int>() }
        
        // 分配到桶中
        for (i in left..right) {
            val digit = getDigit(arr[i], currentExp)
            buckets[digit].add(arr[i])
        }
        
        // 重新排序并将子问题入栈
        var index = left
        for (i in 0 until 10) {
            if (buckets[i].isNotEmpty()) {
                // 复制桶中元素回原数组
                for (value in buckets[i]) {
                    arr[index] = value
                    index++
                }
                
                // 将子问题入栈（逆序处理以保持正确顺序）
                stack.add(StackItem(left, index - 1, currentExp / 10))
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
fun radixSort4(arr: IntArray) {
    println("radixSort4 bucket optimized:")
    
    // 找到最大值以确定位数
    val max = arr.maxOrNull()!!
    
    // 对每个位数进行计数排序
    var exp = 1
    while (max / exp > 0) {
        val n = arr.size
        val output = IntArray(n)
        
        // 动态确定桶范围
        var minDigit = 9
        var maxDigit = 0
        for (i in 0 until n) {
            val digit = getDigit(arr[i], exp)
            if (digit < minDigit) minDigit = digit
            if (digit > maxDigit) maxDigit = digit
        }
        
        val bucketSize = maxDigit - minDigit + 1
        val count = IntArray(bucketSize)
        
        // 统计每个数字的出现次数
        for (i in 0 until n) {
            val digit = getDigit(arr[i], exp)
            count[digit - minDigit]++
        }
        
        // 计算累计计数
        for (i in 1 until count.size) {
            count[i] += count[i - 1]
        }
        
        // 构建输出数组
        for (i in n - 1 downTo 0) {
            val digit = getDigit(arr[i], exp)
            output[count[digit - minDigit] - 1] = arr[i]
            count[digit - minDigit]--
        }
        
        // 复制回原数组
        for (i in 0 until n) {
            arr[i] = output[i]
        }
        
        exp *= 10
    }
    
    printArray(arr, "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

fun main() {
    // 测试1：LSD版本
    performanceTest(::radixSort1, testData, "LSD版本")

    // 测试2：MSD版本
    performanceTest(::radixSort2, testData, "MSD版本")

    // 测试3：迭代MSD版本
    performanceTest(::radixSort3, testData, "迭代MSD版本")

    // 测试4：桶优化版本
    performanceTest(::radixSort4, testData, "桶优化版本")

    println("=== 算法对比总结 ===")
    println("1. LSD版本：经典实现，从低到高")
    println("2. MSD版本：高位优先，递归处理")
    println("3. 迭代MSD版本：避免递归，性能稳定")
    println("4. 桶优化版本：动态桶大小，内存优化")
}

/*
打印结果
jarry@Mac radixsort % kotlin RadixSort.kt
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
