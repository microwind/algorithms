import kotlin.math.max

/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 计数排序算法实现
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
    printArray(testArr, "${name}原始数组")
    
    // 开始计时
    val startTime = measureTimeMillis {
        sortFunc(testArr)
    }
    
    println("$name: ${startTime.toDouble() / 1000.0}")
    printArray(testArr, "${name}排序结果")
    println("") // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含负数和重复元素的典型数组
val testData = intArrayOf(20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80)

/**
 * 计数排序基础版本 - 标准实现
 * 
 * 算法原理：
 * 1. 统计每个元素出现的次数
 * 2. 计算累计计数以确定元素位置
 * 3. 根据累计计数将元素放到正确位置
 * 4. 从后向前遍历保证稳定性
 * 
 * 生活类比：就像统计班级学生成绩分布，
 * 先统计每个分数段有多少人，然后按分数段排序
 * 
 * 时间复杂度：O(n + k)，n为元素个数，k为数据范围
 * 空间复杂度：O(k) - 需要计数数组
 * 稳定性：稳定 - 从后向前遍历保持相等元素的相对位置
 */
fun countingSort1(arr: IntArray) {
    println("countingSort1 standard:")
    
    if (arr.isEmpty()) {
        return
    }
    
    // 找到最小值和最大值
    val min = arr.minOrNull()!!
    val max = arr.maxOrNull()!!
    val range = max - min + 1
    
    // 创建计数数组
    val count = IntArray(range)
    
    // 统计每个元素出现的次数
    for (i in arr.indices) {
        count[arr[i] - min]++
    }
    
    // 计算累计计数
    for (i in 1 until count.size) {
        count[i] += count[i - 1]
    }
    
    // 创建输出数组
    val output = IntArray(arr.size)
    
    // 从后向前遍历，保证稳定性
    for (i in arr.size - 1 downTo 0) {
        val value = arr[i]
        val index = value - min
        output[count[index] - 1] = value
        count[index]--
    }
    
    // 复制回原数组
    for (i in arr.indices) {
        arr[i] = output[i]
    }
    
    printArray(arr, "排序后数组")
}

/**
 * 计数排序优化版本 - 内存优化
 * 
 * 算法思路：
 * 直接在原数组上进行修改，减少内存使用
 * 使用原地排序技术
 * 
 * 优化效果：
 * - 减少额外空间使用
 * - 更好的缓存性能
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：不稳定 - 原地修改可能影响稳定性
 */
fun countingSort2(arr: IntArray) {
    println("countingSort2 memory optimized:")
    
    if (arr.isEmpty()) {
        return
    }
    
    // 找到最小值和最大值
    val min = arr.minOrNull()!!
    val max = arr.maxOrNull()!!
    val range = max - min + 1
    
    // 创建计数数组
    val count = IntArray(range)
    
    // 统计每个元素出现的次数
    for (value in arr) {
        count[value - min]++
    }
    
    // 直接根据计数重构数组
    var index = 0
    for (i in count.indices) {
        var remaining = count[i]
        while (remaining > 0) {
            arr[index] = i + min
            index++
            remaining--
        }
    }
    
    printArray(arr, "排序后数组")
}

/**
 * 计数排序 - 负数单独处理版本
 * 
 * 算法思路：
 * 专门处理包含负数的情况
 * 分别处理负数和正数部分
 * 
 * 优化效果：
 * - 支持负数排序
 * - 保持算法稳定性
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 */
fun countingSort3(arr: IntArray) {
    println("countingSort3 negative numbers:")
    
    if (arr.isEmpty()) {
        return
    }
    
    // 分离正数和负数
    val negatives = mutableListOf<Int>()
    val positives = mutableListOf<Int>()
    
    for (value in arr) {
        if (value < 0) {
            negatives.add(value)
        } else {
            positives.add(value)
        }
    }
    
    // 排序负数部分（转换为绝对值排序后反转）
    if (negatives.isNotEmpty()) {
        val absNegatives = negatives.map { -it }.toIntArray()
        
        // 使用独立的计数排序逻辑
        if (absNegatives.isNotEmpty()) {
            // 找到最小值和最大值
            val min = absNegatives.minOrNull()!!
            val max = absNegatives.maxOrNull()!!
            val range = max - min + 1
            
            // 创建计数数组
            val count = IntArray(range) { 0 }
            
            // 统计每个元素出现的次数
            for (value in absNegatives) {
                count[value - min]++
            }
            
            // 计算累计计数
            for (i in 1 until count.size) {
                count[i] += count[i - 1]
            }
            
            // 创建输出数组
            val output = IntArray(absNegatives.size)
            
            // 从后向前遍历，保证稳定性
            for (i in absNegatives.indices.reversed()) {
                val value = absNegatives[i]
                val index = value - min
                output[count[index] - 1] = value
                count[index]--
            }
            
            // 反转并恢复负号
            for (i in output.indices) {
                negatives[i] = -output[output.size - 1 - i]
            }
        }
    }
    
    // 排序正数部分
    if (positives.isNotEmpty()) {
        // 使用独立的计数排序逻辑
        if (positives.isNotEmpty()) {
            val posArray = positives.toIntArray()
            
            // 找到最小值和最大值
            val min = posArray.minOrNull()!!
            val max = posArray.maxOrNull()!!
            val range = max - min + 1
            
            // 创建计数数组
            val count = IntArray(range) { 0 }
            
            // 统计每个元素出现的次数
            for (value in posArray) {
                count[value - min]++
            }
            
            // 计算累计计数
            for (i in 1 until count.size) {
                count[i] += count[i - 1]
            }
            
            // 创建输出数组
            val output = IntArray(posArray.size)
            
            // 从后向前遍历，保证稳定性
            for (i in posArray.indices.reversed()) {
                val value = posArray[i]
                val index = value - min
                output[count[index] - 1] = value
                count[index]--
            }
            
            // 复制回正数数组
            for (i in output.indices) {
                positives[i] = output[i]
            }
        }
    }
    
    // 合并结果
    val result = mutableListOf<Int>()
    result.addAll(negatives)
    result.addAll(positives)
    
    // 复制回原数组
    for (i in arr.indices) {
        arr[i] = result[i]
    }
    
    printArray(arr, "排序后数组")
}

/**
 * 计数排序 - 桶优化版本
 * 
 * 算法思路：
 * 使用桶的概念，将相近的数值分组
 * 减少计数数组的大小
 * 适合大数据范围但分布稀疏的情况
 * 
 * 优化效果：
 * - 减少内存使用
 * 提高处理稀疏数据的效率
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 */
fun countingSort4(arr: IntArray) {
    println("countingSort4 bucket optimized:")
    
    if (arr.isEmpty()) {
        return
    }
    
    // 找到最小值和最大值
    val min = arr.minOrNull()!!
    val max = arr.maxOrNull()!!
    val range = max - min + 1
    
    // 确定桶的大小（可以调整以优化性能）
    val bucketSize = max(1, range / 10)
    val bucketCount = max(5, max((range + bucketSize - 1) / bucketSize, 10))
    
    // 创建桶
    val buckets = Array(bucketCount) { mutableListOf<Int>() }
    
    // 将元素分配到桶中
    for (value in arr) {
        val bucketIndex: Int = if (value == max) {
            bucketCount - 1
        } else {
            (value - min) / bucketSize
        }
        buckets[bucketIndex].add(value)
    }
    
    // 对每个桶进行排序并合并结果
    val result = mutableListOf<Int>()
    
    for (i in buckets.indices) {
        if (buckets[i].isNotEmpty()) {
            // 使用独立的计数排序逻辑
            val bucketArray = buckets[i].toIntArray()
            
            if (bucketArray.isNotEmpty()) {
                // 找到最小值和最大值
                val min = bucketArray.minOrNull()!!
                val max = bucketArray.maxOrNull()!!
                val range = max - min + 1
                
                // 创建计数数组
                val count = IntArray(range) { 0 }
                
                // 统计每个元素出现的次数
                for (value in bucketArray) {
                    count[value - min]++
                }
                
                // 计算累计计数
                for (j in 1 until count.size) {
                    count[j] += count[j - 1]
                }
                
                // 创建输出数组
                val output = IntArray(bucketArray.size)
                
                // 从后向前遍历，保证稳定性
                for (j in bucketArray.indices.reversed()) {
                    val value = bucketArray[j]
                    val index = value - min
                    output[count[index] - 1] = value
                    count[index]--
                }
                
                // 复制回桶数组
                for (j in output.indices) {
                    bucketArray[j] = output[j]
                }
            }
            
            // 将排序后的桶内容复制到结果数组
            result.addAll(bucketArray.toList())
        }
    }
    
    // 复制回原数组
    for (i in arr.indices) {
        arr[i] = result[i]
    }
    
    printArray(arr, "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

fun main() {
    // 测试1：标准版本
    performanceTest(::countingSort1, testData, "标准版本")

    // 测试2：内存优化版本
    performanceTest(::countingSort2, testData, "内存优化版本")

    // 测试3：负数处理版本
    performanceTest(::countingSort3, testData, "负数处理版本")

    // 测试4：桶优化版本
    performanceTest(::countingSort4, testData, "桶优化版本")

    println("=== 算法对比总结 ===")
    println("1. 标准版本：经典实现，稳定排序")
    println("2. 内存优化版本：原地修改，节省空间")
    println("3. 负数处理版本：支持负数，功能完整")
    println("4. 桶优化版本：分组处理，适合稀疏数据")
}

/*
打印结果
jarry@Mac countingsort % kotlinc CountingSort.kt -include-runtime -d CountingSort.jar && java -jar CountingSort.jar
标准版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort1 standard:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
标准版本: 0.0
标准版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

内存优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort2 memory optimized:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
内存优化版本: 0.001
内存优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

负数处理版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort3 negative numbers:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
负数处理版本: 0.002
负数处理版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

桶优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort4 bucket optimized:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
桶优化版本: 0.0
桶优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 标准版本：经典实现，稳定排序
2. 内存优化版本：原地修改，节省空间
3. 负数处理版本：支持负数，功能完整
4. 桶优化版本：分组处理，适合稀疏数据
*/
