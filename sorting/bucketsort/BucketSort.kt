/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 桶排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

import kotlin.system.measureTimeMillis

/**
 * 打印数组内容的辅助函数
 */
fun printArray(arr: IntArray, label: String) {
    println("$label: ${arr.contentToString()}")
}

fun printArray(arr: FloatArray, label: String) {
    println("$label: ${arr.contentToString()}")
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
val testData = intArrayOf(20, 11, 0, -10, 9, 6, 30, 15, 13, 80)

/**
 * 插入排序辅助函数 - 用于桶内排序
 */
fun insertionSort(arr: IntArray) {
    for (i in 1 until arr.size) {
        val key = arr[i]
        var j = i - 1
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]
            j--
        }
        arr[j + 1] = key
    }
}

/**
 * 插入排序辅助函数 - 用于FloatArray桶内排序
 */
fun insertionSort(arr: FloatArray) {
    for (i in 1 until arr.size) {
        val key = arr[i]
        var j = i - 1
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]
            j--
        }
        arr[j + 1] = key
    }
}

/**
 * 桶排序基础版本 - 标准实现
 * 
 * 算法原理：
 * 1. 创建固定数量的桶
 * 2. 将元素分配到对应的桶中
 * 3. 对每个桶内的元素进行排序
 * 4. 合并所有桶的元素得到有序数组
 * 
 * 生活类比：就像整理图书馆的书籍，
 * 先按类别分到不同的书架，再在每个书架内按字母顺序排列
 * 
 * 时间复杂度：平均O(n + k)，最坏O(n²)（所有元素在一个桶中）
 * 空间复杂度：O(n + k) - 需要桶空间
 * 稳定性：稳定 - 桶内排序保持相等元素的相对位置
 */
fun bucketSort1(arr: IntArray) {
    println("bucketSort1 standard:")
    
    if (arr.isEmpty()) {
        return
    }
    
    // 找到最小值和最大值
    val min = arr.minOrNull()!!
    val max = arr.maxOrNull()!!
    
    // 创建桶（这里使用5个桶作为示例）
    val bucketCount = 5
    val buckets = Array(bucketCount) { mutableListOf<Int>() }
    
    // 计算每个桶的范围
    val range = max - min
    val bucketSize = range.toDouble() / bucketCount
    
    // 将元素分配到桶中
    for (value in arr) {
        val bucketIndex = if (value == max) {
            bucketCount - 1
        } else {
            ((value - min).toDouble() / bucketSize).toInt()
        }
        buckets[bucketIndex].add(value)
    }
    
    // 对每个桶进行排序并合并结果
    val result = mutableListOf<Int>()
    
    for (i in 0 until bucketCount) {
        if (buckets[i].isNotEmpty()) {
            // 对桶内元素进行排序
            val bucketArray = buckets[i].toIntArray()
            insertionSort(bucketArray)
            
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

/**
 * 桶排序优化版本 - 动态桶数量
 * 
 * 算法思路：
 * 根据数据大小动态确定桶的数量
 * 更好的负载均衡
 * 减少空桶的数量
 * 
 * 优化效果：
 * - 更好的空间利用率
 * - 更均匀的元素分布
 * 
 * 时间复杂度：平均O(n + k)
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
fun bucketSort2(arr: FloatArray) {
    println("bucketSort2 dynamic buckets:")
    
    if (arr.isEmpty()) {
        return
    }
    
    // 找到最小值和最大值
    val min = arr.minOrNull()!!
    val max = arr.maxOrNull()!!
    
    // 动态计算桶数量（基于数据范围和元素数量）
    val range = max - min
    var bucketCount = arr.size
    if (bucketCount > 10) {
        bucketCount = arr.size / 5
    }
    if (bucketCount < 5) {
        bucketCount = 5
    }
    val bucketSize = range.toDouble() / bucketCount
    
    // 创建桶
    val buckets = Array(bucketCount) { mutableListOf<Float>() }
    
    // 将元素分配到桶中
    for (value in arr) {
        val bucketIndex = if (value == max) {
            bucketCount - 1
        } else {
            ((value - min).toDouble() / bucketSize).toInt()
        }
        buckets[bucketIndex].add(value)
    }
    
    // 对每个桶进行排序并合并结果
    val result = mutableListOf<Float>()
    
    for (i in 0 until bucketCount) {
        if (buckets[i].isNotEmpty()) {
            val bucketArray = buckets[i].toFloatArray()
            insertionSort(bucketArray)
            result.addAll(bucketArray.toList())
        }
    }
    
    // 复制回原数组
    for (i in arr.indices) {
        arr[i] = result[i]
    }
    
    printArray(arr, "排序后数组")
}

/**
 * 桶排序 - 链表实现版本
 * 
 * 算法思路：
 * 使用链表结构实现桶，优化插入操作
 * 适合频繁插入和删除的场景
 * 
 * 优化效果：
 * - 更快的插入操作
 * - 更好的内存管理
 * 
 * 时间复杂度：平均O(n + k)
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
fun bucketSort3(arr: IntArray) {
    println("bucketSort3 linked list:")
    
    if (arr.isEmpty()) {
        return
    }
    
    // 找到最小值和最大值
    val min = arr.minOrNull()!!
    val max = arr.maxOrNull()!!
    
    // 创建桶（使用数组模拟链表）
    val bucketCount = 5
    val buckets = Array(bucketCount) { mutableListOf<Int>() }
    
    // 计算每个桶的范围
    val range = max - min
    val bucketSize = range.toDouble() / bucketCount
    
    // 将元素分配到桶中（保持有序插入）
    for (value in arr) {
        val bucketIndex = if (value == max) {
            bucketCount - 1
        } else {
            ((value - min).toDouble() / bucketSize).toInt()
        }
        
        // 有序插入到桶中
        var inserted = false
        for ((j, existingValue) in buckets[bucketIndex].withIndex()) {
            if (value < existingValue) {
                buckets[bucketIndex].add(j, value)
                inserted = true
                break
            }
        }
        
        if (!inserted) {
            buckets[bucketIndex].add(value)
        }
    }
    
    // 合并所有桶
    val result = mutableListOf<Int>()
    
    for (bucket in buckets) {
        result.addAll(bucket)
    }
    
    // 复制回原数组
    for (i in arr.indices) {
        arr[i] = result[i]
    }
    
    printArray(arr, "排序后数组")
}

/**
 * 桶排序 - 自适应版本
 * 
 * 算法思路：
 * 根据数据分布自动调整桶策略
 * 检测数据分布模式并优化桶分配
 * 
 * 优化效果：
 * - 适应不同数据分布
 * - 自动优化性能
 * 
 * 时间复杂度：平均O(n + k)
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
fun bucketSort4(arr: IntArray) {
    println("bucketSort4 adaptive:")
    
    if (arr.isEmpty()) {
        return
    }
    
    // 分析数据分布
    val min = arr.minOrNull()!!
    val max = arr.maxOrNull()!!
    val range = max - min
    val sum = arr.sum()
    val mean = sum.toDouble() / arr.size
    
    // 检测数据分布均匀性
    val variance = arr.map { value ->
        val diff = value.toDouble() - mean
        diff * diff
    }.sum() / arr.size
    
    // 根据分布情况调整策略
    val bucketCount = if (variance < (range * range).toDouble() / 100.0) {
        // 数据分布均匀，使用较多桶
        var count = arr.size
        if (count > 10) {
            count = arr.size / 5
        }
        count
    } else {
        // 数据分布不均匀，使用较少桶
        var count = arr.size
        if (count > 25) {
            count = (arr.size.toDouble() * 0.316).toInt() // sqrt approximation
        }
        count
    }
    
    val finalBucketCount = maxOf(5, bucketCount, 10)
    val bucketSize = range.toDouble() / finalBucketCount
    
    // 创建桶
    val buckets = Array(finalBucketCount) { mutableListOf<Int>() }
    
    // 将元素分配到桶中
    for (value in arr) {
        val bucketIndex = if (value == max) {
            finalBucketCount - 1
        } else {
            ((value - min).toDouble() / bucketSize).toInt()
        }
        buckets[bucketIndex].add(value)
    }
    
    // 对每个桶进行排序并合并结果
    val result = mutableListOf<Int>()
    
    for (i in 0 until finalBucketCount) {
        if (buckets[i].isNotEmpty()) {
            // 根据桶大小选择排序算法
            val bucketArray = buckets[i].toIntArray()
            if (bucketArray.size <= 10) {
                insertionSort(bucketArray)
            } else {
                bucketArray.sort()
            }
            result.addAll(bucketArray.toList())
        }
    }
    
    // 复制回原数组
    for (i in arr.indices) {
        arr[i] = result[i]
    }
    
    printArray(arr, "排序后数组")
}

/**
 * 桶排序实时冒泡版 - 负数放在第一个桶内排序
 *
 * 算法思路：
 * 1. 计算数组的最大值和最小值
 * 2. 根据数组长度计算桶的大小
 * 3. 将元素分配到桶中，负数放在第1个桶
 * 4. 每次插入后立即对桶内进行冒泡排序
 * 5. 合并所有桶的元素
 *
 * 优化效果：
 * - 每次插入后立即排序桶内元素
 * - 使用冒泡排序保持桶内有序
 * - 插入即排序，无需后续排序步骤
 *
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
fun bucketSort5(arr: IntArray) {
    println("bucketSort5 real-time bubble sorting:")
    
    if (arr.isEmpty()) {
        return
    }
    
    // 第一步：查找数组中的最大值和最小值
    var max = arr[0]
    var min = arr[0]
    for (i in 1 until arr.size) {
        if (arr[i] > max) {
            max = arr[i]
        }
        if (arr[i] < min) {
            min = arr[i]
        }
    }
    
    // 边界处理：处理最大最小值小于等于1的情况
    if (max < 1) {
        max = 1
    }
    if (min < 1) {
        min = 1
    }
    
    // 第二步：确定桶的大小和数量
    val bucketSize = (max - min) / min + 1
    val bucketNumber = (max - min) / bucketSize + 1
    
    // 第三步：初始化桶
    val buckets = Array<MutableList<Int>>(bucketNumber) { mutableListOf() }
    
    // 第四步：将元素分配到对应桶中
    for (item in arr) {
        // 计算元素应该放入的桶索引
        var idx = (item - min) / bucketSize
        
        // 负数处理：负数放在第1个桶
        if (idx < 0) {
            idx = 0
        }
        
        // 插入元素到桶中
        buckets[idx].add(item)
        
        // 实时冒泡排序：对新插入的元素进行冒泡排序
        val bucket = buckets[idx]
        for (j in bucket.size - 1 downTo 1) {
            if (bucket[j] < bucket[j - 1]) {
                // 交换元素
                val temp = bucket[j]
                bucket[j] = bucket[j - 1]
                bucket[j - 1] = temp
            }
        }
    }
    
    // 第五步：合并结果
    val result = mutableListOf<Int>()
    for (bucket in buckets) {
        result.addAll(bucket)
    }
    
    printArray(result.toIntArray(), "排序后数组")
}

/**
 * 桶排序优化版 - 使用更精确的桶分配策略
 *
 * 算法思路：
 * 1. 分析数据分布，计算最优桶数量
 * 2. 使用更精确的桶边界计算
 * 3. 桶内使用快速排序提高效率
 * 4. 支持负数和浮点数
 * 5. 优化内存使用
 *
 * 优化效果：
 * - 智能桶数量计算
 * - 更精确的数据分布处理
 * - 桶内使用快速排序
 * - 更好的边界条件处理
 *
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
fun bucketSort6(arr: IntArray) {
    println("bucketSort6 optimized version:")
    
    if (arr.size <= 1) {
        printArray(arr, "排序后数组")
        return
    }
    
    // 范围计算：计算数据范围
    var min = arr[0]
    var max = arr[0]
    for (i in 1 until arr.size) {
        if (arr[i] < min) {
            min = arr[i]
        }
        if (arr[i] > max) {
            max = arr[i]
        }
    }
    
    // 智能桶数量计算：根据数据规模动态计算
    val bucketNumber = when {
        arr.size < 5 -> arr.size
        arr.size < 100 -> arr.size / 2
        else -> kotlin.math.sqrt(arr.size.toDouble()).toInt()
    }
    
    // 桶大小计算：确保数据均匀分布
    val bucketSize = (max - min) / bucketNumber + 1
    
    // 初始化桶
    val buckets = Array<MutableList<Int>>(bucketNumber) { mutableListOf() }
    
    // 元素分配：将元素分配到对应桶中
    for (item in arr) {
        // 桶索引计算：确保索引在有效范围内
        var idx = (item - min) / bucketSize
        if (idx < 0) {
            idx = 0
        } else if (idx >= bucketNumber) {
            idx = bucketNumber - 1
        }
        
        // 插入元素到桶中
        buckets[idx].add(item)
    }
    
    // 桶内排序：对每个桶进行快速排序
    for (bucket in buckets) {
        if (bucket.size > 1) {
            bucket.sort()
        }
    }
    
    // 结果合并：合并所有桶的元素
    val result = mutableListOf<Int>()
    for (bucket in buckets) {
        result.addAll(bucket)
    }
    
    printArray(result.toIntArray(), "排序后数组")
}


// ==================== 主程序：算法演示和性能测试 ====================

fun main() {
    val testData = intArrayOf(20, 11, 0, -10, 9, 6, 30, 15, 13, 80)
    
    println("=== 桶排序算法演示 ===\n")
    
    // 测试bucketSort1
    performanceTest({ bucketSort1(it.clone()) }, testData, "bucketSort1 with negative numbers:")
    
    // 测试bucketSort2
    val floatTestData = floatArrayOf(0.7f, 0.11f, -0.9f, 0.011f, 0.034f, 0.62f, 0.93f, 0.68f)
    // 为FloatArray创建单独的性能测试
    val testArr2 = floatTestData.clone()
    printArray(testArr2, "bucketSort2 positive numbers only:原始数组")
    val startTime2 = System.nanoTime()
    bucketSort2(testArr2)
    val endTime2 = System.nanoTime()
    println("bucketSort2: ${String.format("%.3f", (endTime2 - startTime2) / 1_000_000.0)}ms")
    printArray(testArr2, "bucketSort2 positive numbers only:排序结果")
    
    // 测试bucketSort3
    performanceTest({ bucketSort3(it.clone()) }, testData, "bucketSort3 with move sorting:")
    
    // 测试bucketSort4
    performanceTest({ bucketSort4(it.clone()) }, testData, "bucketSort4 separate negative sorting:")
    
    // 测试bucketSort5
    performanceTest({ bucketSort5(it.clone()) }, testData, "bucketSort5 real-time bubble sorting:")
    
    // 测试bucketSort6
    performanceTest({ bucketSort6(it.clone()) }, testData, "bucketSort6 optimized version:")
    
    println("=== 算法对比总结 ===")
    println("1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理")
    println("2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好")
    println("3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性")
    println("4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确")
    println("5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序")
    println("6. 优化版本：bucketSort6 - 智能桶数量计算，更精确的数据分布处理")
}

/*
打印结果
jarry@Mac bucketsort % kotlinc BucketSort.kt -include-runtime -d BucketSort.jar && java -jar BucketSort.jar
=== 桶排序算法演示 ===

bucketSort1 with negative numbers:原始数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort1 standard:
排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort1 with negative numbers:: 0.009
bucketSort1 with negative numbers:排序结果: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

bucketSort2 positive numbers only:原始数组: [0.7, 0.11, -0.9, 0.011, 0.034, 0.62, 0.93, 0.68]
bucketSort2 dynamic buckets:
排序后数组: [-0.9, 0.011, 0.034, 0.11, 0.62, 0.68, 0.7, 0.93]
bucketSort2: 0.114ms
bucketSort2 positive numbers only:排序结果: [-0.9, 0.011, 0.034, 0.11, 0.62, 0.68, 0.7, 0.93]
bucketSort3 with move sorting:原始数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort3 linked list:
排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort3 with move sorting:: 0.0
bucketSort3 with move sorting:排序结果: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

bucketSort4 separate negative sorting:原始数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort4 adaptive:
排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort4 separate negative sorting:: 0.0
bucketSort4 separate negative sorting:排序结果: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

bucketSort5 real-time bubble sorting:原始数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort5 real-time bubble sorting:
排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort5 real-time bubble sorting:: 0.0
bucketSort5 real-time bubble sorting:排序结果: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

bucketSort6 optimized version:原始数组: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort6 optimized version:
排序后数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort6 optimized version:: 0.0
bucketSort6 optimized version:排序结果: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

=== 算法对比总结 ===
1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理
2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好
3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性
4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确
5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序
6. 优化版本：bucketSort6 - 智能桶数量计算，更精确的数据分布处理
*/
