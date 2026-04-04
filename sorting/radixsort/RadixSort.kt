/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序算法实现
 * 提供6种不同的实现方式，适合不同场景和性能需求
 * 
 * ==================== 6个基数排序算法的相同与区别 ====================
 * 
 * 【相同点】
 * 1. 核心原理：都是基于基数排序思想，按位数进行排序
 * 2. 稳定性：所有算法都保持排序的稳定性
 * 3. 基数范围：都使用10进制基数（0-9）
 * 4. 适用场景：都适合整数排序，特别是大范围数字
 * 5. 时间复杂度：理论时间复杂度都是O(d * (n + k))，d为位数，k为基数
 * 
 * 【区别点】
 * 
 * 1. radixSort1 - 计数排序基数排序版本
 *    - 实现方式：基于计数排序的LSD（最低位优先）实现
 *    - 负数支持：使用最小值偏移处理负数
 *    - 内存使用：O(n + k) 需要计数数组和输出数组
 *    - 特点：经典实现，代码清晰易懂
 * 
 * 2. radixSort2 - 内联计数排序基数排序版本
 *    - 实现方式：内联计数排序逻辑的LSD实现
 *    - 负数支持：使用最小值偏移处理负数
 *    - 内存使用：O(n + k) 需要计数数组和输出数组
 *    - 特点：减少函数调用开销，性能略优
 * 
 * 3. radixSort3 - 迭代MSD基数排序版本
 *    - 实现方式：使用栈模拟递归的MSD（最高位优先）实现
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k + s) s为栈空间
 *    - 特点：避免递归深度过大，适合大数据集
 * 
 * 4. radixSort4 - 桶优化基数排序版本
 *    - 实现方式：动态桶大小的LSD实现
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k') k'为实际使用的基数范围（≤k）
 *    - 特点：内存优化，适合稀疏数据
 * 
 * 5. radixSort5 - 递归基数排序版本
 *    - 实现方式：递归处理每一位的LSD实现
 *    - 负数支持：使用最小值偏移处理负数
 *    - 内存使用：O(n + k + d) d为递归栈深度
 *    - 特点：代码简洁，递归深度由数字位数决定
 * 
 * 6. radixSort6 - MSD基数排序版本
 *    - 实现方式：递归MSD实现，从最高位开始排序
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k) 需要桶和计数数组
 *    - 特点：适合字符串或变长数据，高位优先处理
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
    printArray(testArr, name)
    
    // 开始计时
    val startTime = measureTimeMillis {
        sortFunc(testArr)
    }
    
    println("$name: ${startTime.toDouble() / 1000.0}")
    printArray(testArr, "${name}排序结果")
    println("") // 空行分隔
}

// ==================== 测试数据 ====================

// 测试数据：包含大数字的典型数组
val testData = intArrayOf(33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431)

// 负数测试数据
val negativeTestData = intArrayOf(170, 45, 75, -90, -802, 24, 2, 66, -5, 0)

/**
 * 获取数字的指定位数
 */
fun getDigit(num: Int, exp: Int): Int {
    return kotlin.math.abs(num) / exp % 10
}

/**
 * 计数排序，根据基数按位进行计数
 * 
 * ## 算法特点
 * - 按位进行计数排序，支持负数处理
 * - 使用最小值偏移处理负数
 * - 稳定排序：保持相等元素的相对位置
 * - 适用于基数排序的按位处理
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(n + k)，k为基数范围（通常为10）
 * - 空间复杂度：O(n + k) - 需要计数数组和输出数组
 * - 稳定性：稳定 - 计数排序保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @param exponent - 当前处理的位数基数（1, 10, 100, ...）
 */
fun countingSort(arr: IntArray, exponent: Int) {
    // 第一步：初始化变量和数组，按10个桶大小，0-9的个位数
    val arrLen = arr.size
    val bucketRange = 10
    val countList = IntArray(bucketRange)
    val sortedList = IntArray(arrLen)

    // 第二步：找出最小值
    // 关键点：处理负数情况，需要找到最小值进行偏移
    val minValue = arr.minOrNull()!!

    // 第三步：初始化计数数组
    // 关键点：将计数数组清零
    for (i in 0 until bucketRange) {
        countList[i] = 0
    }

    // 第四步：根据数字所在位置进行计数
    // 关键点：使用arr[i] - minValue来处理负数，确保索引为正数
    for (i in 0 until arrLen) {
        val item = arr[i] - minValue
        val idx = (item / exponent) % bucketRange
        countList[idx]++
    }

    // 第五步：构建计数排序
    // 关键点：后面的位数为前面的累加之和，形成累积计数
    for (i in 1 until bucketRange) {
        countList[i] += countList[i - 1]
    }
    println("radixSort1 countingSort countList:[${countList.joinToString(", ")}]")

    // 第六步：构建输出数组
    // 关键点：从后向前遍历，保持排序的稳定性
    for (i in arrLen - 1 downTo 0) {
        val item = arr[i] - minValue
        val idx = (item / exponent) % bucketRange
        sortedList[countList[idx] - 1] = arr[i]
        countList[idx]--
    }

    // 第七步：复制到数组重排原始数组
    // 关键点：将排序结果复制回原数组
    for (i in 0 until arrLen) {
        arr[i] = sortedList[i]
    }
    println("radixSort1 -> sortedList:[${sortedList.joinToString(", ")}]")
}

/**
 * 基数排序，从低位到高位LSD版，基于计数排序
 * 
 * ## 算法特点
 * - 从低位到高位进行排序（LSD - Least Significant Digit）
 * - 基于计数排序实现，支持负数处理
 * - 稳定排序：保持相等元素的相对位置
 * - 适用于整数排序，特别是大范围数字
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
 * - 空间复杂度：O(n + k) - 需要额外的计数和输出数组
 * - 稳定性：稳定 - 计数排序保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return IntArray - 排序后的数组
 */
fun radixSort1(arr: IntArray): IntArray {
    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if (arr.isEmpty()) {
        return arr
    }

    // 第二步：找出最大值和最小值
    // 关键点：确定排序的位数范围和处理负数
    val maxValue = arr.maxOrNull()!!
    val minValue = arr.minOrNull()!!

    // 第三步：根据最大值，逐个按进位(基数)来应用排序
    // 关键点：exponent即数位基数，按个十百千递增
    // 最大减去最小得到数位，最小按0来计算，这样可以支持负数
    var exponent = 1
    while ((maxValue - minValue) / exponent > 0) {
        countingSort(arr, exponent)
        exponent *= 10
    }

    return arr
}

/**
 * 内联计数排序基数排序版本
 * 
 * ## 算法特点
 * - 基于计数排序的LSD实现，内联处理逻辑
 * - 支持负数处理，使用最小值偏移
 * - 稳定排序：保持相等元素的相对位置
 * - 适用于整数排序，特别是大范围数字
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
 * - 空间复杂度：O(n + k) - 需要计数数组和输出数组
 * - 稳定性：稳定 - 计数排序保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return IntArray - 排序后的数组
 */
fun radixSort2(arr: IntArray): IntArray {
    // 第一步：初始化变量
    // 关键点：获取数组长度，设置基数范围
    val arrLen = arr.size
    val range = 10
    val sortedList = IntArray(arrLen)

    // 第二步：找出最大值
    // 关键点：遍历数组找出最大值，用于确定位数
    val max = arr.maxOrNull()!!

    // 第三步：找出最小值以支持负数
    // 关键点：处理负数情况，需要找到最小值进行偏移
    val min = arr.minOrNull()!!

    // 第四步：根据基数求得当前项目对应位置的数值，并给对应计数数组位置加1
    // 关键点：从1开始，每10进位，逐位进行比较和排序，一直到最大减去最小数
    var exponent = 1
    while ((max - min) / exponent > 0) {
        // 步骤4.1：创建计数数组
        // 关键点：计数数组长度为10，0-9一共10个数字
        val countList = IntArray(range)

        // 步骤4.2：根据基数得到当前位数，并给计数数组对应位置加1
        // 关键点：使用arr[i] - min来处理负数，确保索引为正数
        for (i in 0 until arrLen) {
            val item = arr[i] - min
            val idx = (item / exponent) % range
            countList[idx]++
        }

        // 步骤4.3：计数排序构建
        // 关键点：自前往后，逐个将上一项的值存入当前项
        for (i in 1 until range) {
            countList[i] += countList[i - 1]
        }

        println("radixSort2 -> countList:[${countList.joinToString(", ")}]")

        // 步骤4.4：根据计数数组按顺序取出排序内容
        // 关键点：从后向前遍历，保持排序的稳定性
        for (i in arrLen - 1 downTo 0) {
            val item = arr[i] - min
            val idx = (item / exponent) % range
            sortedList[countList[idx] - 1] = arr[i]
            countList[idx]--
        }

        println("radixSort2 -> sortedList:[${sortedList.joinToString(", ")}]")

        // 步骤4.5：将新顺序赋值给原数组
        // 关键点：将排序结果复制回原数组，准备下一位处理
        for (i in 0 until arr.size) {
            arr[i] = sortedList[i]
        }
        
        exponent *= range
    }

    return sortedList
}

/**
 * 迭代MSD基数排序版本
 * 
 * ## 算法特点
 * - 使用栈模拟递归，避免递归深度过大
 * - 从最高位开始排序（MSD - Most Significant Digit）
 * - 桶排序实现，动态分配内存
 * - 适合处理大数据集
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数
 * - 空间复杂度：O(n + k + s) - s为栈空间
 * - 稳定性：稳定 - 保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return IntArray - 排序后的数组
 */
fun radixSort5(arr: IntArray): IntArray {
    println("radixSort5 iterative MSD:")

    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if (arr.isEmpty()) {
        return arr
    }

    // 第二步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定最高位数
    val max = arr.maxOrNull()!!

    // 第三步：计算最高位对应的基数
    // 关键点：exp从1开始，不断乘以10直到超过最大值
    var exp = 1
    while (max / exp > 0) {
        exp *= 10
    }

    // 第四步：使用栈模拟递归
    // 关键点：创建栈数组，初始化栈顶指针
    data class StackItem(val left: Int, val right: Int, val exp: Int)
    
    val stack = mutableListOf<StackItem>()
    stack.add(StackItem(0, arr.size - 1, exp / 10))

    // 第五步：循环处理栈中的范围
    // 关键点：栈不为空时继续处理，模拟递归调用过程
    while (stack.isNotEmpty()) {
        // 步骤5.1：从栈中取出待处理的范围
        // 关键点：后进先出，取出栈顶元素
        val item = stack.removeAt(stack.size - 1)
        val stackLeft = item.left
        val right = item.right
        val currentExp = item.exp

        // 步骤5.2：递归终止条件检查
        // 关键点：范围无效或位数不足时跳过
        if (stackLeft >= right || currentExp < 1) {
            continue
        }

        // 步骤5.3：创建桶
        // 关键点：创建10个桶，对应0-9的数字
        val buckets = Array(10) { mutableListOf<Int>() }

        // 步骤5.4：分配到桶中
        // 关键点：根据当前位数将元素分配到对应桶中
        for (i in stackLeft..right) {
            val digit = getDigit(arr[i], currentExp)
            buckets[digit].add(arr[i])
        }

        // 步骤5.5：重新排序并将子问题入栈
        // 关键点：将桶中元素复制回原数组，并将子问题入栈
        var index = stackLeft
        var nextLeft = stackLeft
        for (i in 0 until 10) {
            if (buckets[i].isNotEmpty()) {
                // 步骤5.5.1：复制桶中元素回原数组
                // 关键点：按桶的顺序复制元素，保持稳定性
                for (value in buckets[i]) {
                    arr[index] = value
                    index++
                }

                // 步骤5.5.2：将子问题入栈
                // 关键点：将子数组范围和下一位数入栈，逆序处理保持正确顺序
                stack.add(StackItem(nextLeft, index - 1, currentExp / 10))
                nextLeft = index
            }
        }
    }

    // 第六步：输出排序结果
    printArray(arr, "排序后数组")
    return arr
}

/**
 * 递归基数排序辅助函数
 * 
 * ## 算法特点
 * - 递归处理每一位的计数排序
 * - 从最低位开始递归到最高位
 * - 基于计数排序实现
 * - 使用计数排序作为基础
 * 
 * @param arr - 待排序的数字数组
 * @param exponent - 当前处理的位数基数
 * @param minValue - 数组最小值，用于负数处理
 * @param maxValue - 数组最大值，用于确定递归终止条件
 */
fun recursiveRadixSort(arr: IntArray, exponent: Int, minValue: Int, maxValue: Int) {
    // 第一步：递归终止条件检查
    // 关键点：当基数超过最大值时停止递归
    if ((maxValue - minValue) / exponent == 0) {
        return
    }

    // 第二步：初始化计数排序变量
    // 关键点：为当前位数的计数排序准备变量
    val range = 10
    val countList = IntArray(range)
    val sortedList = IntArray(arr.size)

    // 第三步：初始化计数数组
    // 关键点：将计数数组清零
    for (i in 0 until range) {
        countList[i] = 0
    }

    // 第四步：根据数字所在位置进行计数
    // 关键点：使用arr[i] - minValue来处理负数，确保索引为正数
    for (i in 0 until arr.size) {
        val item = arr[i] - minValue
        val idx = (item / exponent) % range
        countList[idx]++
    }

    // 第五步：构建计数排序
    // 关键点：后面的位数为前面的累加之和，形成累积计数
    for (i in 1 until range) {
        countList[i] += countList[i - 1]
    }

    // 第六步：构建输出数组
    // 关键点：从后向前遍历，保持排序的稳定性
    for (i in arr.size - 1 downTo 0) {
        val item = arr[i] - minValue
        val idx = (item / exponent) % range
        sortedList[countList[idx] - 1] = arr[i]
        countList[idx]--
    }

    // 第七步：复制到数组重排原始数组
    // 关键点：将排序结果复制回原数组
    for (i in 0 until arr.size) {
        arr[i] = sortedList[i]
    }

    // 第八步：递归处理下一位
    // 关键点：递归调用处理更高位数
    recursiveRadixSort(arr, exponent * 10, minValue, maxValue)
}

/**
 * 递归基数排序版本
 * 
 * ## 算法特点
 * - 使用递归处理每一位的排序
 * - 基于计数排序的LSD实现
 * - 支持负数处理
 * - 递归深度由数字位数决定
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
 * - 空间复杂度：O(n + k + d) - 需要额外空间和递归栈
 * - 稳定性：稳定 - 计数排序保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return IntArray - 排序后的数组
 */
fun radixSort3(arr: IntArray): IntArray {
    // 第一步：输出测试信息
    // 关键点：标识当前测试的算法类型
    println("radixSort3 递归基数排序:")

    // 第二步：找出最大值和最小值
    // 关键点：确定排序的位数范围和处理负数
    val maxValue = arr.maxOrNull()!!
    val minValue = arr.minOrNull()!!

    // 第三步：调用递归基数排序
    // 关键点：从最低位（个位）开始递归排序
    recursiveRadixSort(arr, 1, minValue, maxValue)

    // 第四步：输出排序结果
    // 关键点：显示排序后的数组，验证算法正确性
    printArray(arr, "排序后数组")
    return arr
}

/**
 * 桶优化基数排序版本
 * 
 * ## 算法特点
 * - 使用动态桶大小，优化内存使用
 * - 适合处理稀疏数据
 * - 减少不必要的内存分配
 * - 提高处理效率
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为实际使用的基数范围
 * - 空间复杂度：O(n + k') - k'为实际使用的基数范围（≤k）
 * - 稳定性：稳定 - 保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return IntArray - 排序后的数组
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


/**
 * MSD递归排序函数
 * 
 * ## 算法特点
 * - 从最高位开始排序（MSD - Most Significant Digit）
 * - 使用递归处理子数组
 * - 桶排序实现，动态分配内存
 * - 适合处理字符串或变长数据
 * 
 * @param arr - 待排序的数字数组
 * @param left - 左边界索引
 * @param right - 右边界索引
 * @param exp - 当前处理的位数基数
 */
fun msdSort(arr: IntArray, left: Int, right: Int, exp: Int) {
    // 第一步：递归终止条件检查
    // 关键点：范围无效或位数不足时返回
    if (left >= right || exp < 1) {
        return
    }
    
    // 第二步：创建桶
    // 关键点：创建10个桶，对应0-9的数字
    val buckets = Array(10) { mutableListOf<Int>() }
    
    // 第三步：分配到桶中
    // 关键点：根据当前位数将元素分配到对应桶中
    for (i in left..right) {
        val digit = getDigit(arr[i], exp)
        buckets[digit].add(arr[i])
    }
    
    // 第四步：重新排序并递归处理每个桶
    // 关键点：将桶中元素复制回原数组，并递归处理子数组
    var index = left
    var currentLeft = left
    for (i in 0 until 10) {
        if (buckets[i].isNotEmpty()) {
            // 步骤4.1：复制桶中元素回原数组
            // 关键点：按桶的顺序复制元素，保持稳定性
            for (value in buckets[i]) {
                arr[index] = value
                index++
            }
            
            // 步骤4.2：递归处理下一个位数
            // 关键点：递归处理当前桶的子数组
            msdSort(arr, currentLeft, index - 1, exp / 10)
            currentLeft = index
        }
    }
}

/**
 * MSD基数排序版本
 * 
 * ## 算法特点
 * - 从最高位开始排序（MSD - Most Significant Digit）
 * - 使用递归处理子数组
 * - 桶排序实现，动态分配内存
 * - 适合处理字符串或变长数据
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数
 * - 空间复杂度：O(n + k) - 需要桶和计数数组
 * - 稳定性：稳定 - 保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return IntArray - 排序后的数组
 */
fun radixSort6(arr: IntArray): IntArray {
    println("radixSort6 MSD:")
    
    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if (arr.isEmpty()) {
        return arr
    }
    
    // 第二步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定最高位数
    val max = arr.maxOrNull()!!

    // 第三步：计算最高位对应的基数
    // 关键点：exp从1开始，不断乘以10直到超过最大值
    var exp = 1
    while (max / exp > 0) {
        exp *= 10
    }
    
    // 第四步：调用MSD递归排序
    // 关键点：从最高位开始递归排序
    msdSort(arr, 0, arr.size - 1, exp / 10)
    
    // 第五步：输出排序结果
    printArray(arr, "排序后数组")
    return arr
}

// ==================== 算法测试和性能对比 ====================

fun main() {
    // 测试1：radixSort1 - 计数排序基数排序版本（支持负数）
    performanceTest(::radixSort1, testData, "radixSort1 - 计数排序基数排序版本")

    // 测试2：radixSort2 - 内联计数排序基数排序版本（支持负数）
    performanceTest(::radixSort2, testData, "radixSort2 - 内联计数排序基数排序版本")

    // 测试3：radixSort3 - 递归基数排序版本（支持负数）
    performanceTest(::radixSort3, testData, "radixSort3 - 递归基数排序版本")

    // 测试4：radixSort4 - MSD基数排序版本
    performanceTest(::radixSort6, testData, "radixSort4 - MSD基数排序版本")

    // 测试5：radixSort5 - 迭代MSD基数排序版本
    performanceTest(::radixSort5, testData, "radixSort5 - 迭代MSD基数排序版本")

    // 测试6：radixSort6 - 桶优化基数排序版本
    performanceTest(::radixSort4, testData, "radixSort6 - 桶优化基数排序版本")

    // 测试7：负数数据处理
    println("\n=== 负数测试 ===")
    performanceTest(::radixSort3, negativeTestData, "radixSort3 - 递归基数排序版本（负数测试）")

    println("=== 算法对比总结 ===")
    println("1. radixSort1：计数排序基数排序版本，支持负数")
    println("2. radixSort2：内联计数排序基数排序版本，支持负数")
    println("3. radixSort3：递归基数排序版本，递归处理每一位")
    println("4. radixSort4：MSD基数排序版本，高位优先递归处理")
    println("5. radixSort5：迭代MSD基数排序版本，避免递归性能稳定")
    println("6. radixSort6：桶优化基数排序版本，动态桶大小内存优化")
}

/*
打印结果
jarry@Mac radixsort % kotlinc RadixSort.kt -include-runtime -d RadixSort.jar && java -jar RadixSort.jar
radixSort1 - 计数排序基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort1 countingSort countList:[2, 4, 4, 5, 5, 5, 7, 8, 8, 10]
radixSort1 -> sortedList:[4, 323454, 15, 1235, 7, 10, 200, 87431, 33, 43]
radixSort1 countingSort countList:[3, 4, 6, 8, 8, 9, 9, 9, 9, 10]
radixSort1 -> sortedList:[4, 7, 10, 15, 87431, 33, 1235, 43, 323454, 200]
radixSort1 countingSort countList:[6, 7, 8, 8, 10, 10, 10, 10, 10, 10]
radixSort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort1 countingSort countList:[7, 8, 8, 9, 9, 9, 9, 10, 10, 10]
radixSort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radixSort1 countingSort countList:[8, 8, 9, 9, 9, 9, 9, 9, 10, 10]
radixSort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radixSort1 countingSort countList:[9, 9, 9, 10, 10, 10, 10, 10, 10, 10]
radixSort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort1 - 计数排序基数排序版本: 0.001
radixSort1 - 计数排序基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort2 - 内联计数排序基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort2 -> countList:[2, 4, 4, 5, 5, 5, 7, 8, 8, 10]
radixSort2 -> sortedList:[4, 323454, 15, 1235, 7, 10, 200, 87431, 33, 43]
radixSort2 -> countList:[3, 4, 6, 8, 8, 9, 9, 9, 9, 10]
radixSort2 -> sortedList:[4, 7, 10, 15, 87431, 33, 1235, 43, 323454, 200]
radixSort2 -> countList:[6, 7, 8, 8, 10, 10, 10, 10, 10, 10]
radixSort2 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort2 -> countList:[7, 8, 8, 9, 9, 9, 9, 10, 10, 10]
radixSort2 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radixSort2 -> countList:[8, 8, 9, 9, 9, 9, 9, 9, 10, 10]
radixSort2 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radixSort2 -> countList:[9, 9, 9, 10, 10, 10, 10, 10, 10, 10]
radixSort2 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort2 - 内联计数排序基数排序版本: 0.0
radixSort2 - 内联计数排序基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort3 - 递归基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort3 递归基数排序:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort3 - 递归基数排序版本: 0.001
radixSort3 - 递归基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort4 - MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort6 MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort4 - MSD基数排序版本: 0.0
radixSort4 - MSD基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort5 - 迭代MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort5 iterative MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort5 - 迭代MSD基数排序版本: 0.0
radixSort5 - 迭代MSD基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort6 - 桶优化基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort4 bucket optimized:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort6 - 桶优化基数排序版本: 0.0
radixSort6 - 桶优化基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]


=== 负数测试 ===
radixSort3 - 递归基数排序版本（负数测试）: [170, 45, 75, -90, -802, 24, 2, 66, -5, 0]
radixSort3 递归基数排序:
排序后数组: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]
radixSort3 - 递归基数排序版本（负数测试）: 0.0
radixSort3 - 递归基数排序版本（负数测试）排序结果: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]

=== 算法对比总结 ===
1. radixSort1：计数排序基数排序版本，支持负数
2. radixSort2：内联计数排序基数排序版本，支持负数
3. radixSort3：递归基数排序版本，递归处理每一位
4. radixSort4：MSD基数排序版本，高位优先递归处理
5. radixSort5：迭代MSD基数排序版本，避免递归性能稳定
6. radixSort6：桶优化基数排序版本，动态桶大小内存优化
*/
