/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description 快速排序算法实现集合
 * 
 * 本文件包含7种不同的快速排序实现，涵盖了快速排序的主要算法变体：
 * 
 * ## 算法分类
 * 1. 按实现方式分类：
 *    - 递归新建数组版本：创建新数组进行分区，稳定排序
 *    - 递归交换版本：原地交换，高效排序
 *    - 非递归栈模拟版本：避免递归深度过大
 * 
 * 2. 按分区策略分类：
 *    - 中间基准：选择中间元素作为基准，避免最坏情况
 *    - 左侧基准：选择第一个元素作为基准，Hoare分区
 *    - 右侧基准：选择最后一个元素作为基准，Lomuto分区
 *    - 三路分区：处理重复元素，提高效率
 * 
 * 3. 按扫描方式分类：
 *    - 单向扫描：从左向右一次性扫描
 *    - 双向扫描：左右指针同时向中间移动
 *    - 三路扫描：处理小于、等于、大于基准的元素
 * 
 * ## 性能特点
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) ~ O(n) 递归调用栈 + 额外空间
 * - 稳定性：大部分不稳定，只有新建数组版本稳定
 * 
 * ## 使用建议
 * - 数据量小：推荐递归版本，代码简洁
 * - 数据量大：推荐非递归版本，避免栈溢出
 * - 重复元素多：推荐三路分区版本，性能更优
 * - 需要稳定排序：推荐新建数组版本
 * 
 * ## 测试数据
 * 默认测试数据：[7, 11, 9, 10, 12, 13, 8]
 * 包含重复元素测试：可修改测试数据验证三路分区优势
 */

import kotlin.system.measureTimeMillis

// ==================== 辅助函数 ====================

/**
 * 打印数组内容的辅助函数
 * 
 * 功能：以格式化的方式输出数组内容
 * 
 * @param arr - 要打印的数字数组
 * @param label - 数组的标签说明，用于标识输出
 */
fun printArray(arr: IntArray, label: String) {
    println("$label: [${arr.joinToString(", ")}]")
}

/**
 * 性能测试函数
 * 
 * 功能：测试排序算法的性能，包括执行时间和正确性验证
 * 
 * @param sortFunc - 排序函数，接受数组并返回排序后的数组
 * @param arr - 测试用的原始数组
 * @param name - 测试名称，用于输出标识和性能统计
 */
fun performanceTest(sortFunc: (IntArray) -> Unit, arr: IntArray, name: String) {
    // 创建数组副本，避免修改原数组
    val testArr = arr.clone()
    println("$name origin:")
    printArray(testArr, "")
    
    // 开始计时并执行排序
    val duration = measureTimeMillis {
        sortFunc(testArr)
    }
    
    // 输出结果
    println("$name: ${duration}ms")
    printArray(testArr, "quickSort${name.last()} sorted")
    println() // 空行分隔
}

// ==================== 算法实现 ====================

/**
 * 快速排序1 - 递归新建数组版本
 * 
 * ## 算法特点
 * - 无需交换，每个分区都是新数组
 * - 使用中间元素作为基准，避免最坏情况
 * - 内存友好：不修改原数组，返回新数组
 * - 稳定排序：保持相等元素的相对位置
 * 
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(n log n) - 递归调用栈 + 新数组空间
 * - 稳定性：稳定 - 保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return 排序后的数字数组
 */
/*
quick_sort1 递归步骤:

      f([7, 11, 9, 10, 12, 13, 8])
            /       10          \
      f([7, 9, 8])           f([11, 12, 13])
        /   9    \             /    12     \
   f([7, 8])    f([])       f([11])       f[13]
   /   8  \
f([7]) f([])
  [7]
*/
fun quickSort1(arr: IntArray): IntArray {
    // 第一步：递归终止条件
    // 关键点：数组长度<=1时已经有序，直接返回
    if (arr.size <= 1) {
        return arr
    }

    // 第二步：选择基准并分区
    println("split array: ${arr.contentToString()}")
    val left = mutableListOf<Int>()
    val right = mutableListOf<Int>()
    // 关键点：设置中间数作为基准，避免最坏情况
    val midIndex = arr.size / 2
    val pivot = arr[midIndex]

    // 第三步：遍历数组，按基准值分区
    for (i in arr.indices) {
        // 关键点：跳过基准元素本身，避免重复处理
        if (midIndex == i) {
            continue
        }
        // 关键点：小于基准的放左边，大于等于的放右边
        if (arr[i] < pivot) {
            left.add(arr[i])
        } else {
            right.add(arr[i])
        }
    }

    // 第四步：递归排序并合并
    // 关键点：先递归左数组，再添加基准，最后递归右数组
    val leftSorted = quickSort1(left.toIntArray())
    val rightSorted = quickSort1(right.toIntArray())
    
    val result = leftSorted + pivot + rightSorted
    println("sorted array: ${result.contentToString()}")
    return result
}

/**
 * 快速排序2 - 标准递归版本
 *
 * ## 算法特点
 * - 需要左右不断交换，无需新建数组
 * - 使用中间元素作为基准
 * - 双向扫描：左右指针相向移动
 * - 效率较高：减少不必要的交换
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param low - 起始索引
 * @param high - 结束索引
 * @return 排序后的数字数组
 */
fun quickSort2(arr: IntArray, low: Int, high: Int): IntArray {
    // 第一步：递归终止条件检查
    // 关键点：low >= high时已经有序，直接返回
    if (low >= high) {
        return arr
    }

    // 第二步：初始化指针和基准
    var i = if (low > 0) low else 0
    var j = high
    // 关键点：确定中间位置，基于中间位置不停左右交换
    val midIndex = (i + j) / 2
    val pivot = arr[midIndex]

    println(" i=$i, j=$j, midIndex=$midIndex, pivot=$pivot  arr[]=${arr.contentToString()}")

    // 第三步：双向扫描分区
    // 关键点：当左侧小于等于右侧则表示还有值没有对比，需要继续
    while (i <= j) {
        // 步骤3.1：左指针扫描，找到大于基准的元素
        // 关键点：当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
        while (arr[i] < pivot) {
            println("arr[i] < pivot: i=$i, j=$j, pivot=$pivot")
            i++
        }
        // 步骤3.2：右指针扫描，找到小于基准的元素
        // 关键点：当前右侧大于基准时左移，直到找出比基准值小的位置来
        while (arr[j] > pivot) {
            println("arr[i] > pivot: i=$i, j=$j, pivot=$pivot")
            j--
        }

        println("low=$low, high=$high, i=$i, j=$j, pivot=$pivot")

        // 步骤3.3：交换元素
        // 关键点：当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
        if (i <= j) {
            val tmp = arr[j]
            arr[j] = arr[i]
            arr[i] = tmp
            // 关键点：缩小搜查范围，直到左侧都小于基数，右侧都大于基数
            i++
            j--
        }
    }

    // 第四步：递归处理左右子数组
    // 步骤4.1：递归处理左子数组
    // 关键点：左侧小于基数位置，不断递归左边部分
    if (low < j) {
        println("  low < j:recursion: low=$low, high=$high, i=$i, j=$j, midIndex=$midIndex, pivot=$pivot")
        quickSort2(arr, low, j)
    }
    // 步骤4.2：递归处理右子数组
    // 关键点：基数位置小于右侧，不断递归右侧部分
    if (i < high) {
        println("  i < high:recursion: low=$low, high=$high, i=$i, j=$j, midIndex=$midIndex, pivot=$pivot")
        quickSort2(arr, i, high)
    }

    return arr
}

/**
 * 快速排序3 - 非递归版本
 * 
 * ## 算法特点
 * - 需要交换，无需新建数组，利用stack或queue遍历
 * - 使用栈模拟递归调用
 * - 避免递归深度过大导致的栈溢出
 * - 稳定可靠：适合大数据量排序
 * 
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(n) - 显式栈空间
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @param low - 起始索引
 * @param high - 结束索引
 * @return 排序后的数字数组
 */
fun quickSort3(arr: IntArray, low: Int, high: Int): IntArray {
    // 第一步：初始化参数
    // 关键点：设置默认值，确保函数可以单独调用
    val stack = mutableListOf<Int>()
    var i: Int
    var j: Int
    var midIndex: Int
    var pivot: Int
    var tmp: Int
    
    // 第二步：创建栈用于存储待处理的子数组范围
    // 关键点：使用数组模拟栈结构，避免递归调用
    // 与标准递归版相同，只是将递归改为遍历栈的方式
    // 先将左右各取一个入栈
    stack.add(low)
    stack.add(high)

    // 第三步：循环处理栈中的范围
    // 关键点：栈不为空时继续处理，模拟递归调用过程
    while (stack.isNotEmpty()) {
        // 步骤3.1：从栈中取出待处理的范围
        // 关键点：如果栈内还有数据，则一并马上取出，其他逻辑与标准递归版同
        val rightVal = stack.removeAt(stack.size - 1)
        val leftVal = stack.removeAt(stack.size - 1)
        
        // 步骤3.2：获取基准位置
        // 关键点：使用中间元素作为基准
        midIndex = (leftVal + rightVal) / 2
        pivot = arr[midIndex]

        // 步骤3.3：分区过程
        // 关键点：左右指针相向移动，进行分区
        i = leftVal
        j = rightVal
        while (i <= j) {
            // 步骤3.3.1：左指针扫描，找到大于基准的元素
            // 关键点：当左侧小于基准时查找位置右移
            while (arr[i] < pivot) {
                println("arr[i] < pivot: i=$i, j=$j, pivot=$pivot")
                i++
            }
            // 步骤3.3.2：右指针扫描，找到小于基准的元素
            // 关键点：当前右侧大于基准时左移
            while (arr[j] > pivot) {
                println("arr[i] > pivot: i=$i, j=$j, pivot=$pivot")
                j--
            }

            println("low=$leftVal, high=$rightVal, i=$i, j=$j, pivot=$pivot")

            // 步骤3.3.3：交换元素
            // 关键点：当左侧位置小于右侧时，将数据交换
            if (i <= j) {
                tmp = arr[j]
                arr[j] = arr[i]
                arr[i] = tmp
                i++
                j--
            }
        }
        // 步骤3.4：子区间入栈
        // 关键点：将分区后的子范围重新入栈，继续处理
        if (leftVal < j) {
            // 关键点：左子数组有数据，入栈待处理
            // 与递归版不同，这里添加到栈中，以便继续循环
            println("  low < j:recursion: low=$leftVal, high=$rightVal, i=$i, j=$j, midIndex=$midIndex, pivot=$pivot")
            stack.add(leftVal)
            stack.add(j)
        }
        if (i < rightVal) {
            // 关键点：右子数组有数据，入栈待处理
            println("  i < high:recursion: low=$leftVal, high=$rightVal, i=$i, j=$j, midIndex=$midIndex, pivot=$pivot")
            stack.add(i)
            stack.add(rightVal)
        }
    }

    // 第四步：返回排序后的数组
    // 关键点：所有范围处理完成，数组已排序
    return arr
}

/**
 * 标准分区函数
 * 
 * ## 算法特点
 * - 使用右侧元素作为基准（Lomuto分区）
 * - 单向扫描：从左到右扫描
 * - 分区指针：记录小于基准区域的边界
 * - 基准归位：最后将基准元素放到正确位置
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(n) - 单次分区时间
 * - 空间复杂度：O(1) - 原地分区
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @return 基准元素的最终位置
 */
fun partition(arr: IntArray, left: Int, right: Int): Int {
    // 第一步：选择基准（这里取右侧）
    // 基准值可以是left与right之间的任意值，再将基准值移动至最左或最右即可。
    val pivotIndex = right
    val pivot = arr[pivotIndex]
    var partitionIndex = left - 1

    // 第二步：遍历数组进行分区
    for (i in left until right) {
        // 关键点：将小于基准的元素交换到左侧
        if (arr[i] < pivot) {
            // 将小于基准值的数据交换到左侧，分区下标右移1位
            partitionIndex += 1
            val tmp = arr[partitionIndex]
            arr[partitionIndex] = arr[i]
            arr[i] = tmp
        }
    }

    // 第三步：将基准放到正确位置
    partitionIndex += 1
    // 最后将基准值交换到交换下标处，以此分割左右
    val tmp = arr[partitionIndex]
    arr[partitionIndex] = arr[pivotIndex]
    arr[pivotIndex] = tmp
    println("partition: partitionIndex=$partitionIndex arr[partitionIndex]=${arr[partitionIndex]} left=$left right=$right")
    return partitionIndex
}

/**
 * 快速排序4 - 标准递归版本
 *
 * ## 算法特点
 * - 左右不断分区交换，无需新建数组
 * - 使用Lomuto分区方案
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param start - 起始索引
 * @param end - 结束索引
 * @return 排序后的数字数组
 */
fun quickSort4(arr: IntArray, start: Int, end: Int): IntArray {
    // 第一步：递归终止条件检查
    // 关键点：start < end时还需要排序，否则已经有序
    if (start < end) {
        // 第二步：分区并获取基准位置
        // 关键点：使用partition函数将数组分为两部分
        val pivot = partition(arr, start, end)

        // 第三步：递归排序左半部分
        // 关键点：排序基准左边的元素
        quickSort4(arr, 0, pivot - 1)

        // 第四步：递归排序右半部分
        // 关键点：排序基准右边的元素
        quickSort4(arr, pivot + 1, end)
    }
    return arr
}

/**
 * Lomuto分区函数
 *
 * ## 算法特点
 * - 使用最后一个元素作为基准
 * - 单向扫描：从左到右扫描
 * - 分区指针：记录小于基准区域的边界
 * - 基准归位：最后将基准元素放到正确位置
 *
 * ## 复杂度分析
 * - 时间复杂度：O(n) - 单次分区时间
 * - 空间复杂度：O(1) - 原地分区
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param low - 起始索引
 * @param high - 结束索引
 * @return 基准元素的最终位置
 */
fun partitionLomuto(arr: IntArray, low: Int, high: Int): Int {
    // 第一步：初始化基准和指针
    val pivot = arr[high] // 最后一个元素作为基准
    var i = low - 1 // 小于基准的元素的边界

    // 第二步：遍历数组进行分区
    for (j in low until high) {
        // 关键点：将小于基准的元素交换到左侧
        if (arr[j] < pivot) {
            i++
            val tmp = arr[i]
            arr[i] = arr[j]
            arr[j] = tmp
        }
    }

    // 第三步：将基准放到正确位置
    val tmp = arr[i + 1]
    arr[i + 1] = arr[high]
    arr[high] = tmp
    return i + 1
}

/**
 * 快速排序5 - Lomuto分区递归版本
 *
 * ## 算法特点
 * - 使用Lomuto分区方案
 * - 最后一个元素作为基准
 * - 单向扫描：从左到右扫描
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @return 排序后的数字数组
 */
fun quickSort5(arr: IntArray, left: Int, right: Int): IntArray {
    // 第一步：递归终止条件检查
    if (left >= right) {
        return arr
    }

    // 第二步：获取基准位置
    val pi = partitionLomuto(arr, left, right)

    // 第三步：递归排序左右子数组
    if (pi > 0) {
        quickSort5(arr, left, pi - 1)
    }
    quickSort5(arr, pi + 1, right)
    return arr
}

/**
 * 快速排序6 - Hoare分区递归版本
 *
 * ## 算法特点
 * - 使用Hoare分区方案
 * - 第一个元素作为基准
 * - 双向扫描：左右指针相向移动
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @return 排序后的数字数组
 */
fun quickSort6(arr: IntArray, left: Int, right: Int): IntArray {
    // 第一步：递归终止条件检查
    if (left >= right) {
        return arr
    }

    // 第二步：初始化指针和基准
    var i = left
    var j = right
    val pivot = arr[left] // 第一个元素作为基准

    // 第三步：双向扫描分区
    while (i <= j) {
        // 左指针：找到大于基准的元素
        while (arr[i] < pivot) {
            i++
        }
        // 右指针：找到小于基准的元素
        while (arr[j] > pivot) {
            j--
        }
        // 交换元素
        if (i <= j) {
            val tmp = arr[i]
            arr[i] = arr[j]
            arr[j] = tmp
            i++
            j--
        }
    }

    // 第四步：递归处理左右子数组
    quickSort6(arr, left, j)
    quickSort6(arr, i, right)
    return arr
}

/**
 * 快速排序7 - 三路分区递归版本
 *
 * ## 算法特点
 * - 使用第一个元素作为基准
 * - 三路分区：处理重复元素，提高效率
 * - 递归优化：减少递归调用次数
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @return 排序后的数字数组
 */
fun quickSort7(arr: IntArray, left: Int, right: Int): IntArray {
    // 第一步：递归终止条件检查
    if (left >= right) {
        return arr
    }

    // 第二步：初始化基准和三路指针
    val pivot = arr[left] // 第一个元素作为基准
    var lt = left // 小于基准的右边界
    var i = left + 1 // 当前遍历指针
    var gt = right // 大于基准的左边界

    // 第三步：三路分区
    while (i <= gt) {
        if (arr[i] < pivot) {
            // 步骤3.1：小于基准，交换到左边
            val tmp = arr[lt]
            arr[lt] = arr[i]
            arr[i] = tmp
            lt++
            i++
        } else if (arr[i] > pivot) {
            // 步骤3.2：大于基准，交换到右边
            val tmp = arr[i]
            arr[i] = arr[gt]
            arr[gt] = tmp
            gt--
        } else {
            // 步骤3.3：等于基准，直接跳过
            i++
        }
    }

    // 第四步：递归处理左右子数组
    if (lt > 0) {
        quickSort7(arr, left, lt - 1)
    }
    quickSort7(arr, gt + 1, right)
    // 等于基准的部分已经就位，无需处理
    return arr
}

// ==================== 算法测试和性能对比 ====================

fun main() {
    // 测试数据：
    val testData = intArrayOf(7, 11, 9, 10, 12, 13, 8)

    // 测试1：递归新建数组版本
    performanceTest({ arr -> quickSort1(arr) }, testData, "sort1")

    // 测试2：标准递归版本
    performanceTest({ arr -> quickSort2(arr, 0, arr.size - 1) }, testData, "sort2")

    // 测试3：非递归版本
    performanceTest({ arr -> quickSort3(arr, 0, arr.size - 1) }, testData, "sort3")

    // 测试4：标准递归版本
    performanceTest({ arr -> quickSort4(arr, 0, arr.size - 1) }, testData, "sort4")

    // 测试5：Lomuto分区递归版本
    performanceTest({ arr -> quickSort5(arr, 0, arr.size - 1) }, testData, "sort5")

    // 测试6：Hoare分区递归版本
    performanceTest({ arr -> quickSort6(arr, 0, arr.size - 1) }, testData, "sort6")

    // 测试7：三路分区递归版本
    performanceTest({ arr -> quickSort7(arr, 0, arr.size - 1) }, testData, "sort7")

    println("=== 算法对比总结 ===")
    println("1. 递归新建数组版本：中间基准，新建数组，稳定排序")
    println("2. 标准递归版本：中间基准，双向扫描，原地交换")
    println("3. 非递归版本：栈模拟，避免递归，双向扫描")
    println("4. 标准递归版本：右侧基准，原地交换，Lomuto分区")
    println("5. Lomuto分区递归版本：最后基准，单向扫描")
    println("6. Hoare分区递归版本：第一个基准，双向扫描")
    println("7. 三路分区递归版本：第一个基准，三路分区")
}

/*
打印结果
jarry@Mac quicksort % kotlinc QuickSort.kt -include-runtime -d QuickSort.jar && java -jar QuickSort.jar
sort1 origin:
: [7, 11, 9, 10, 12, 13, 8]
split array: [7, 11, 9, 10, 12, 13, 8]
split array: [7, 9, 8]
split array: [7, 8]
sorted array: [7, 8]
sorted array: [7, 8, 9]
split array: [11, 12, 13]
sorted array: [11, 12, 13]
sorted array: [7, 8, 9, 10, 11, 12, 13]
sort1: 6ms
quickSort1 sorted: [7, 11, 9, 10, 12, 13, 8]

sort2 origin:
: [7, 11, 9, 10, 12, 13, 8]
 i=0, j=6, midIndex=3, pivot=10  arr[]=[7, 11, 9, 10, 12, 13, 8]
arr[i] < pivot: i=0, j=6, pivot=10
low=0, high=6, i=1, j=6, pivot=10
arr[i] < pivot: i=2, j=5, pivot=10
arr[i] > pivot: i=3, j=5, pivot=10
arr[i] > pivot: i=3, j=4, pivot=10
low=0, high=6, i=3, j=3, pivot=10
  low < j:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
 i=0, j=2, midIndex=1, pivot=8  arr[]=[7, 8, 9, 10, 12, 13, 11]
arr[i] < pivot: i=0, j=2, pivot=8
arr[i] > pivot: i=1, j=2, pivot=8
low=0, high=2, i=1, j=1, pivot=8
  i < high:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
 i=4, j=6, midIndex=5, pivot=13  arr[]=[7, 8, 9, 10, 12, 13, 11]
arr[i] < pivot: i=4, j=6, pivot=13
low=4, high=6, i=5, j=6, pivot=13
  low < j:recursion: low=4, high=6, i=6, j=5, midIndex=5, pivot=13
 i=4, j=5, midIndex=4, pivot=12  arr[]=[7, 8, 9, 10, 12, 11, 13]
low=4, high=5, i=4, j=5, pivot=12
sort2: 1ms
quickSort2 sorted: [7, 8, 9, 10, 11, 12, 13]

sort3 origin:
: [7, 11, 9, 10, 12, 13, 8]
arr[i] < pivot: i=0, j=6, pivot=10
low=0, high=6, i=1, j=6, pivot=10
arr[i] < pivot: i=2, j=5, pivot=10
arr[i] > pivot: i=3, j=5, pivot=10
arr[i] > pivot: i=3, j=4, pivot=10
low=0, high=6, i=3, j=3, pivot=10
  low < j:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
  i < high:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
arr[i] < pivot: i=4, j=6, pivot=13
low=4, high=6, i=5, j=6, pivot=13
  low < j:recursion: low=4, high=6, i=6, j=5, midIndex=5, pivot=13
low=4, high=5, i=4, j=5, pivot=12
arr[i] < pivot: i=0, j=2, pivot=8
arr[i] > pivot: i=1, j=2, pivot=8
low=0, high=2, i=1, j=1, pivot=8
sort3: 1ms
quickSort3 sorted: [7, 8, 9, 10, 11, 12, 13]

sort4 origin:
: [7, 11, 9, 10, 12, 13, 8]
partition: partitionIndex=1 arr[partitionIndex]=8 left=0 right=6
partition: partitionIndex=4 arr[partitionIndex]=11 left=2 right=6
partition: partitionIndex=3 arr[partitionIndex]=10 left=0 right=3
partition: partitionIndex=2 arr[partitionIndex]=9 left=0 right=2
partition: partitionIndex=1 arr[partitionIndex]=8 left=0 right=1
partition: partitionIndex=5 arr[partitionIndex]=12 left=5 right=6
partition: partitionIndex=4 arr[partitionIndex]=11 left=0 right=4
partition: partitionIndex=3 arr[partitionIndex]=10 left=0 right=3
partition: partitionIndex=2 arr[partitionIndex]=9 left=0 right=2
partition: partitionIndex=1 arr[partitionIndex]=8 left=0 right=1
sort4: 0ms
quickSort4 sorted: [7, 8, 9, 10, 11, 12, 13]

sort5 origin:
: [7, 11, 9, 10, 12, 13, 8]
sort5: 0ms
quickSort5 sorted: [7, 8, 9, 10, 11, 12, 13]

sort6 origin:
: [7, 11, 9, 10, 12, 13, 8]
sort6: 0ms
quickSort6 sorted: [7, 8, 9, 10, 11, 12, 13]

sort7 origin:
: [7, 11, 9, 10, 12, 13, 8]
sort7: 0ms
quickSort7 sorted: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归新建数组版本：中间基准，新建数组，稳定排序
2. 标准递归版本：中间基准，双向扫描，原地交换
3. 非递归版本：栈模拟，避免递归，双向扫描
4. 标准递归版本：右侧基准，原地交换，Lomuto分区
5. Lomuto分区递归版本：最后基准，单向扫描
6. Hoare分区递归版本：第一个基准，双向扫描
7. 三路分区递归版本：第一个基准，三路分区
*/
