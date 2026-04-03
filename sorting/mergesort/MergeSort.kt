/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 归并排序算法实现
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
 * 合并两个有序数组
 * 
 * 步骤1：初始化结果数组和索引指针
 * 步骤2：按顺序合并两个有序数组
 * 步骤3：处理剩余元素
 * 步骤4：返回合并结果
 * 
 * 关键点：
 * - 使用索引指针避免不必要的内存分配
 * - 利用Kotlin的集合特性高效处理剩余元素
 * - 保持算法的稳定性
 */
fun merge(left: IntArray, right: IntArray): IntArray {
    // 步骤1：初始化结果数组和索引指针
    // 关键点：使用mutableListOf动态构建结果数组
    val result = mutableListOf<Int>()
    var leftIndex = 0
    var rightIndex = 0
    
    // 步骤2：按顺序合并两个有序数组
    // 关键点：比较两个数组的当前元素，选择较小的放入结果数组
    while (leftIndex < left.size && rightIndex < right.size) {
        // 关键点：选择较小的元素放入结果数组
        if (left[leftIndex] <= right[rightIndex]) {
            result.add(left[leftIndex])
            leftIndex++
        } else {
            result.add(right[rightIndex])
            rightIndex++
        }
    }
    
    // 步骤3：处理剩余元素
    // 关键点：将未处理完的数组元素直接添加到结果数组
    // Kotlin特点：使用addAll高效处理剩余元素
    while (leftIndex < left.size) {
        result.add(left[leftIndex])
        leftIndex++
    }
    while (rightIndex < right.size) {
        result.add(right[rightIndex])
        rightIndex++
    }
    
    // 步骤4：返回合并结果
    // 关键点：将 MutableList 转换为 IntArray
    return result.toIntArray()
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
 * - 利用Kotlin的数组切片特性高效分割数组
 * - 递归调用直到基础情况
 */
fun mergeSortRecursive(arr: IntArray): IntArray {
    // 步骤1：检查递归终止条件
    // 关键点：数组长度小于等于1时已经有序，直接返回
    if (arr.size <= 1) {
        return arr
    }
    
    // 步骤2：分割数组为两半
    // 关键点：使用整数除法计算中间位置
    // Kotlin特点：使用sliceArray分割数组，避免内存分配
    val middle = arr.size / 2
    val left = arr.sliceArray(0 until middle)
    val right = arr.sliceArray(middle until arr.size)
    
    // 步骤3：递归排序左右子数组
    // 关键点：分别对左右两部分进行递归排序
    val sortedLeft = mergeSortRecursive(left)
    val sortedRight = mergeSortRecursive(right)
    
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
fun mergeSort1(arr: IntArray) {
    println("mergeSort1 recursive:")
    val result = mergeSortRecursive(arr)
    result.copyInto(arr)
    printArray(arr, "排序后数组")
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
fun mergeInPlace(arr: IntArray, left: Int, mid: Int, right: Int) {
    // 步骤1：创建临时数组存储左半部分
    // 关键点：避免在合并过程中覆盖未处理的数据
    val leftArr = arr.sliceArray(left..mid)
    
    // 步骤2：初始化合并指针
    // 关键点：i指向左数组，j指向右数组，k指向合并位置
    var i = 0 // 左数组索引
    var j = mid + 1 // 右数组索引
    var k = left // 合并位置索引
    
    // 步骤3：按顺序合并两个有序子数组
    // 关键点：比较两个数组的当前元素，选择较小的放入原数组
    while (i < leftArr.size && j <= right) {
        if (leftArr[i] <= arr[j]) {
            arr[k] = leftArr[i]
            i++
        } else {
            arr[k] = arr[j]
            j++
        }
        k++
    }
    
    // 步骤4：处理左数组剩余元素
    // 关键点：左数组可能还有未处理的元素
    while (i < leftArr.size) {
        arr[k] = leftArr[i]
        i++
        k++
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
fun mergeSortInPlaceRecursive(arr: IntArray, left: Int, right: Int) {
    // 步骤1：检查递归终止条件
    // 关键点：left >= right时子数组已经有序
    if (left < right) {
        // 步骤2：计算中间位置
        // 关键点：使用整数除法，避免溢出
        val mid = (left + right) / 2
        
        // 步骤3：递归排序左半部分
        // 关键点：将数组分成[left, mid]和[mid+1, right]两部分
        mergeSortInPlaceRecursive(arr, left, mid)
        
        // 步骤4：递归排序右半部分
        // 关键点：确保右半部分也有序
        mergeSortInPlaceRecursive(arr, mid + 1, right)
        
        // 步骤5：原地合并两个有序部分
        // 关键点：在原数组上进行合并操作
        mergeInPlace(arr, left, mid, right)
    }
}

/**
 * 归并排序优化版本 - 原地合并
 * 
 * 算法思路：
 * 采用分而治之(divide - conquer)的步骤
 * 1. 分解（Divide），把待排序元素的序列分解为两个子序列，以中间2分, 每个子序列包括一半成员。
 * 2. 解决（Conquer），对每个子序列分别调用归并操作, 进行递归或非递归循环操作，完成内部排序。
 * 3. 合并（Combine），合并两个排好序的子序列，生成排序结果。
 * 
 * 优化效果：
 * - 减少了内存分配
 * - 提高了空间效率
 * 
 * 时间复杂度：O(n log n) - 无论如何都需要O(n log n)次比较
 * 空间复杂度：O(n) - 需要临时数组存储合并结果
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
fun mergeSort2(arr: IntArray) {
    println("mergeSort2 in-place (user version):")
    
    /**
     * 合并两个有序子数组
     * 
     * 步骤1：建立临时数组
     * 步骤2：初始化指针
     * 步骤3：按顺序合并两个有序子数组
     * 步骤4：处理剩余元素
     * 步骤5：将排序结果复制回原数组
     * 
     * 关键点：
     * - 使用临时数组避免数据覆盖
     * - 三个指针分别跟踪左数组、右数组和临时数组
     * - 保持算法的稳定性
     */
    class MergeInPlace {
        fun merge(arr: IntArray, left: Int, mid: Int, right: Int) {
            // 步骤1：建立临时数组
            // 关键点：临时数组大小等于当前合并范围
            val temp = IntArray(right - left + 1)
            
            // 步骤2：初始化指针
            // 关键点：i指向左数组，j指向右数组，k指向临时数组
            var i = left      // 左侧指针
            var j = mid + 1   // 右侧指针
            var k = 0        // 临时数组指针
            
            // 步骤3：按顺序合并两个有序子数组
            // 关键点：比较左右数组的当前元素，选择较小的放入临时数组
            // 当左指针小于中间，且右指针不大于最右侧时
            while (i <= mid && j <= right) {
                // 如果左侧小于右侧，将数移到临时数组中左侧
                if (arr[i] <= arr[j]) {
                    temp[k++] = arr[i++]
                // 否则移动到临时数组右侧
                } else {
                    temp[k++] = arr[j++]
                }
            }
            
            // 步骤4：处理剩余元素
            // 关键点：将未处理完的数组元素直接添加到临时数组
            // 如果左边数组还有数据，就把左侧剩余都放入到新数组后面
            while (i <= mid) {
                temp[k++] = arr[i++]
            }
            // 如果右侧数组还有数据，把剩下的数据放入到新数组后面
            while (j <= right) {
                temp[k++] = arr[j++]
            }
            
            // 步骤5：将排序结果复制回原数组
            // 关键点：使用循环逐个复制，确保数据正确性
            var x = 0
            var leftCopy = left
            while (leftCopy <= right) {
                arr[leftCopy++] = temp[x++]
            }
            println("arr:${arr.contentToString()}")
        }
        
        /**
         * 递归归并排序函数
         * 
         * 步骤1：检查递归终止条件
         * 步骤2：计算中间值
         * 步骤3：递归排序左半部分
         * 步骤4：递归排序右半部分
         * 步骤5：合并排序结果
         * 
         * 关键点：
         * - 使用索引范围而不是数组拷贝，减少内存分配
         * - 递归深度为O(log n)
         * - 分治策略的应用
         */
        fun mergeSort(arr: IntArray, left: Int, right: Int): IntArray {
            // 步骤1：检查递归终止条件
            // 关键点：left >= right时子数组已经有序
            println("mergeSort left=$left right=$right")
            if (left < right) {
                println("mergeSort left<right left=$left right=$right")
                
                // 步骤2：计算中间值
                // 关键点：使用整数除法，避免溢出
                val mid = (left + right) / 2
                
                // 步骤3：递归排序左半部分
                // 关键点：将数组分成[left, mid]和[mid+1, right]两部分
                mergeSort(arr, left, mid)
                
                // 步骤4：递归排序右半部分
                // 关键点：确保右半部分也有序
                mergeSort(arr, mid + 1, right)
                
                // 步骤5：合并排序结果
                // 关键点：将两个有序子数组合并成一个有序数组
                merge(arr, left, mid, right)
            }
            return arr
        }
    }
    
    val merger = MergeInPlace()
    merger.mergeSort(arr, 0, arr.size - 1)
    printArray(arr, "排序后数组")
}

/**
 * 合并两个有序子数组 - 迭代版本
 */
fun mergeIterative(arr: IntArray, temp: IntArray, left: Int, mid: Int, right: Int) {
    var i = left // 左子数组索引
    var j = mid + 1 // 右子数组索引
    var k = left // 临时数组索引
    
    // 合并到临时数组
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i]
            i++
        } else {
            temp[k] = arr[j]
            j++
        }
        k++
    }
    
    // 复制左子数组剩余元素
    while (i <= mid) {
        temp[k] = arr[i]
        i++
        k++
    }
    
    // 复制右子数组剩余元素
    while (j <= right) {
        temp[k] = arr[j]
        j++
        k++
    }
    
    // 将临时数组复制回原数组
    for (index in left..right) {
        arr[index] = temp[index]
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
fun mergeSort3(arr: IntArray) {
    println("mergeSort3 iterative:")
    
    val n = arr.size
    val temp = IntArray(n)
    
    // 迭代合并，步长从1开始翻倍
    var size = 1
    while (size < n) {
        for (left in 0 until n - size step 2 * size) {
            val mid = left + size - 1
            val right = minOf(left + 2 * size - 1, n - 1)
            mergeIterative(arr, temp, left, mid, right)
        }
        size *= 2
    }
    
    printArray(arr, "排序后数组")
}

/**
 * 合并两个相邻的有序子数组 - 自底向上版本
 */
fun mergeBottomUp(arr: IntArray, temp: IntArray, left: Int, mid: Int, right: Int) {
    var i = left
    var j = mid
    var k = left
    
    // 合并两个有序子数组到临时数组
    while (i < mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i]
            i++
        } else {
            temp[k] = arr[j]
            j++
        }
        k++
    }
    
    // 复制剩余元素
    while (i < mid) {
        temp[k] = arr[i]
        i++
        k++
    }
    while (j <= right) {
        temp[k] = arr[j]
        j++
        k++
    }
    
    // 复制回原数组
    for (index in left..right) {
        arr[index] = temp[index]
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
fun mergeSort4(arr: IntArray) {
    println("mergeSort4 bottom-up:")
    
    val n = arr.size
    val temp = IntArray(n)
    
    // 自底向上合并
    var width = 1
    while (width < n) {
        for (i in 0 until n step 2 * width) {
            val left = i
            val mid = minOf(i + width, n)
            val right = minOf(i + 2 * width, n)
            
            if (mid < right) {
                mergeBottomUp(arr, temp, left, mid, right - 1)
            }
        }
        width *= 2
    }
    
    printArray(arr, "排序后数组")
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
 * 时间复杂度：O(n log n) - 无论如何都需要O(n log n)次比较
 * 空间复杂度：O(n) - 需要临时数组存储合并结果
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
fun mergeSort5(arr: IntArray) {
    println("mergeSort5 non-recursive merge:")
    
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
    fun mergeNonRecursive(arr: IntArray, temp: IntArray, left: Int, mid: Int, right: Int) {
        // 步骤1：初始化索引指针
        // 关键点：i指向左子数组，j指向右子数组，k指向临时数组
        var i = left      // 左子数组索引
        var j = mid + 1   // 右子数组索引
        var k = left      // 临时数组索引
        
        // 步骤2：合并到临时数组
        // 关键点：按顺序合并两个有序子数组
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k] = arr[i]
                i++
            } else {
                temp[k] = arr[j]
                j++
            }
            k++
        }
        
        // 步骤3：复制左子数组剩余元素
        // 关键点：左子数组可能还有未处理的元素
        while (i <= mid) {
            temp[k] = arr[i]
            i++
            k++
        }
        
        // 步骤4：复制右子数组剩余元素
        // 关键点：右子数组可能还有未处理的元素
        while (j <= right) {
            temp[k] = arr[j]
            j++
            k++
        }
        
        // 步骤5：将临时数组复制回原数组
        // 关键点：使用循环逐个复制，确保数据正确性
        // Kotlin特点：也可以使用copyInto，但循环更直观
        for (index in left..right) {
            arr[index] = temp[index]
        }
    }
    
    val n = arr.size
    if (n <= 1) {
        return
    }
    
    // 步骤1：创建临时数组
    // 关键点：临时数组用于存储合并过程中的中间结果
    val temp = IntArray(n)
    
    // 步骤2：非递归合并过程
    // 关键点：通过迭代方式模拟递归的合并过程
    var size = 1
    while (size < n) {
        // 步骤3：处理所有相邻的子数组对
        // 关键点：每次处理两个大小为size的相邻子数组
        for (left in 0 until n - size step 2 * size) {
            // 步骤4：计算当前合并的边界
            // 关键点：确定左子数组 [left, mid] 和右子数组 [mid+1, right]
            val mid = left + size - 1
            val right = minOf(left + 2 * size - 1, n - 1)
            
            // 步骤5：执行非递归合并
            // 关键点：使用迭代方式合并两个有序子数组
            mergeNonRecursive(arr, temp, left, mid, right)
        }
        size *= 2
    }
    
    printArray(arr, "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

fun main() {
    // 测试1：递归版本（基于slice分割）
    performanceTest(::mergeSort1, testData, "递归版本（基于slice分割）")

    // 测试2：原地合并版本
    performanceTest(::mergeSort2, testData, "原地合并版本")

    // 测试3：迭代版本
    performanceTest(::mergeSort3, testData, "迭代版本")

    // 测试4：自底向上版本
    performanceTest(::mergeSort4, testData, "自底向上版本")
    
    // 测试5：非递归合并版本
    performanceTest(::mergeSort5, testData, "非递归合并版本")

    println("=== 算法对比总结 ===")
    println("1. 递归版本（基于slice分割）：利用Kotlin语言特性，代码简洁")
    println("2. 原地版本：分而治之，逻辑清晰")
    println("3. 迭代版本：避免递归，性能稳定")
    println("4. 底向上版本：适合大数据，外部排序")
    println("5. 非递归合并版本：迭代合并，高效内存")
}

/*
打印结果
jarry@Mac mergesort % kotlinc MergeSort.kt -include-runtime -d MergeSort.jar && java -jar MergeSort.jar
递归版本（基于slice分割）原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort1 recursive:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
递归版本（基于slice分割）: 4ms
递归版本（基于slice分割）排序结果: [7, 8, 9, 10, 11, 12, 13]

原地合并版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort2 in-place (user version):
mergeSort left=0 right=6
mergeSort left<right left=0 right=6
mergeSort left=0 right=3
mergeSort left<right left=0 right=3
mergeSort left=0 right=1
mergeSort left<right left=0 right=1
mergeSort left=0 right=0
mergeSort left=1 right=1
arr:[7, 11, 9, 10, 12, 13, 8]
mergeSort left=2 right=3
mergeSort left<right left=2 right=3
mergeSort left=2 right=2
mergeSort left=3 right=3
arr:[7, 11, 9, 10, 12, 13, 8]
arr:[7, 9, 10, 11, 12, 13, 8]
mergeSort left=4 right=6
mergeSort left<right left=4 right=6
mergeSort left=4 right=5
mergeSort left<right left=4 right=5
mergeSort left=4 right=4
mergeSort left=5 right=5
arr:[7, 9, 10, 11, 12, 13, 8]
mergeSort left=6 right=6
arr:[7, 9, 10, 11, 8, 12, 13]
arr:[7, 8, 9, 10, 11, 12, 13]
排序后数组: [7, 8, 9, 10, 11, 12, 13]
原地合并版本: 0ms
原地合并版本排序结果: [7, 8, 9, 10, 11, 12, 13]

迭代版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort3 iterative:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
迭代版本: 0ms
迭代版本排序结果: [7, 8, 9, 10, 11, 12, 13]

自底向上版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort4 bottom-up:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
自底向上版本: 0ms
自底向上版本排序结果: [7, 8, 9, 10, 11, 12, 13]

非递归合并版本原始数组: [7, 11, 9, 10, 12, 13, 8]
mergeSort5 non-recursive merge:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
非递归合并版本: 0ms
非递归合并版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归版本（基于slice分割）：利用Kotlin语言特性，代码简洁
2. 原地版本：分而治之，逻辑清晰
3. 迭代版本：避免递归，性能稳定
4. 底向上版本：适合大数据，外部排序
5. 非递归合并版本：迭代合并，高效内存
*/
