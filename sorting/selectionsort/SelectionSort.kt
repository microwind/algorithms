/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 选择排序算法实现
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
    val duration = measureTimeMillis {
        sortFunc(testArr)
    }
    
    println("$name: ${duration}ms")
    printArray(testArr, "${name}排序结果")
    println() // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
val testData = intArrayOf(7, 11, 9, 10, 12, 13, 8)

/**
 * 选择排序基础版本
 * 
 * 算法原理：
 * 1. 将数组分为两部分：左侧已排序区域，右侧待排序区域
 * 2. 每次从待排序区域中选择最小元素
 * 3. 将最小元素与待排序区域的第一个元素交换
 * 4. 重复以上过程，直到所有元素排序完成
 * 
 * 生活类比：就像在队伍中挑选最矮的人站到最前面，
 * 然后在剩下的人中再挑选最矮的站到第二个位置，依此类推
 * 
 * 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
 * 空间复杂度：O(1) - 只使用常数个额外变量
 * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
 */
fun selectionSort1(arr: IntArray) {
    println("selectionSort1 basic:")
    val n = arr.size
    
    // 外循环：控制排序轮数，每轮确定一个最小值的位置
    for (i in 0 until n - 1) {
        var minIndex = i // 记录最小元素的索引
        
        // 内循环：在未排序区域中查找最小元素
        for (j in i + 1 until n) {
            // 关键点：找到更小的元素，更新最小值索引
            if (arr[j] < arr[minIndex]) {
                minIndex = j
            }
        }
        
        // 交换最小元素到当前轮次的起始位置
        if (minIndex != i) {
            // Kotlin特点：使用also进行交换
            arr[i] = arr[minIndex].also { arr[minIndex] = arr[i] }
        }
    }
    printArray(arr, "排序后数组")
}

/**
 * 选择排序降序版本
 * 
 * 算法思路：
 * 与基础版本相反，每次选择最大元素
 * 将最大元素与待排序区域的第一个元素交换
 * 
 * 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
 * 空间复杂度：O(1) - 只使用常数个额外变量
 * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
 */
fun selectionSort2(arr: IntArray) {
    println("selectionSort2 descending:")
    val n = arr.size
    
    // 外循环：控制排序轮数，每轮确定一个最大值的位置
    for (i in 0 until n - 1) {
        var maxIndex = i // 记录最大元素的索引
        
        // 内循环：在未排序区域中查找最大元素
        for (j in i + 1 until n) {
            // 关键点：找到更大的元素，更新最大值索引
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j
            }
        }
        
        // 交换最大元素到当前轮次的起始位置
        if (maxIndex != i) {
            // Kotlin特点：使用also进行交换
            arr[i] = arr[maxIndex].also { arr[maxIndex] = arr[i] }
        }
    }
    printArray(arr, "排序后数组")
}

/**
 * 选择排序优化版本 - 双向选择
 * 
 * 优化思路：
 * 每轮同时选择最小和最大元素
 * 将最小元素放到左侧，最大元素放到右侧
 * 减少排序轮数，提高效率
 * 
 * 优化效果：
 * - 减少了排序轮数，从n轮减少到n/2轮
 * - 每轮需要进行两次查找，但总体效率提升
 * 
 * 时间复杂度：O(n²)，空间复杂度：O(1)
 * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
 */
fun selectionSort3(arr: IntArray) {
    println("selectionSort3 bidirectional:")
    val n = arr.size
    var left = 0
    var right = n - 1
    
    // 外循环：控制排序轮数，每轮确定最小和最大值的位置
    while (left < right) {
        var minIndex = left
        var maxIndex = left
        
        // 内循环：在未排序区域中查找最小和最大元素
        for (i in left..right) {
            // 关键点：同时查找最小和最大元素
            if (arr[i] < arr[minIndex]) {
                minIndex = i
            }
            if (arr[i] > arr[maxIndex]) {
                maxIndex = i
            }
        }
        
        // 交换最小元素到左侧
        if (minIndex != left) {
            arr[left] = arr[minIndex].also { arr[minIndex] = arr[left] }
        }
        
        // 优化点：如果最大元素原本在left位置，经过交换后位置变为minIndex
        if (maxIndex == left) {
            maxIndex = minIndex
        }
        
        // 交换最大元素到右侧
        if (maxIndex != right) {
            arr[right] = arr[maxIndex].also { arr[maxIndex] = arr[right] }
        }
        
        left++
        right--
    }
    printArray(arr, "排序后数组")
}

/**
 * 堆化辅助函数
 */
fun heapify(arr: IntArray, n: Int, i: Int) {
    var largest = i // 初始化最大元素为根节点
    val left = 2 * i + 1 // 左子节点
    val right = 2 * i + 2 // 右子节点
    
    // 如果左子节点大于根节点
    if (left < n && arr[left] > arr[largest]) {
        largest = left
    }
    
    // 如果右子节点大于当前最大节点
    if (right < n && arr[right] > arr[largest]) {
        largest = right
    }
    
    // 如果最大节点不是根节点，交换并继续堆化
    if (largest != i) {
        arr[i] = arr[largest].also { arr[largest] = arr[i] }
        heapify(arr, n, largest)
    }
}

/**
 * 选择排序 - 堆优化版本
 * 
 * 算法思路：
 * 利用堆的性质来快速找到最大/最小元素
 * 每次从堆顶取出最大/最小元素
 * 重新调整堆结构
 * 
 * 时间复杂度：O(n log n)，空间复杂度：O(1)
 * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
 */
fun selectionSort4(arr: IntArray) {
    println("selectionSort4 heap optimized:")
    val n = arr.size
    
    // 构建最大堆
    for (i in n / 2 - 1 downTo 0) {
        heapify(arr, n, i)
    }
    
    // 逐个取出堆顶元素
    for (i in n - 1 downTo 1) {
        // 关键点：交换堆顶元素（最大）与末尾元素
        arr[0] = arr[i].also { arr[i] = arr[0] }
        
        // 重新调整堆
        heapify(arr, i, 0)
    }
    
    printArray(arr, "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

fun main() {
    // 测试1：基础选择版本
    performanceTest(::selectionSort1, testData, "基础选择版本")

    // 测试2：降序版本
    performanceTest(::selectionSort2, testData, "降序版本")

    // 测试3：双向选择版本
    performanceTest(::selectionSort3, testData, "双向选择版本")

    // 测试4：堆优化版本
    performanceTest(::selectionSort4, testData, "堆优化版本")

    println("=== 算法对比总结 ===")
    println("1. 基础版本：简单易懂，适合学习算法原理")
    println("2. 降序版本：展示算法灵活性，可按需排序")
    println("3. 双向版本：同时选择最大最小，效率提升")
    println("4. 堆优化版本：利用堆结构，复杂度优化")
}

/*
打印结果
jarry@Mac selectionsort % kotlinc selection_sort.kt -include-runtime -d selection_sort.jar && java -jar selection_sort.jar
基础选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort1 basic:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
基础选择版本: 1ms
基础选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort2 descending:
排序后数组: [13, 12, 11, 10, 9, 8, 7]
降序版本: 0ms
降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]

双向选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort3 bidirectional:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
双向选择版本: 0ms
双向选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

堆优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort4 heap optimized:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
堆优化版本: 0ms
堆优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 基础版本：简单易懂，适合学习算法原理
2. 降序版本：展示算法灵活性，可按需排序
3. 双向版本：同时选择最大最小，效率提升
4. 堆优化版本：利用堆结构，复杂度优化
*/
