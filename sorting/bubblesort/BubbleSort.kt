import kotlin.system.measureTimeMillis

/**
 * 冒泡排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

/**
 * 冒泡排序基础版本 - 升序排列
 * 
 * 算法原理：
 * 1. 从数组左端开始，依次比较相邻元素
 * 2. 若左元素大于右元素，则交换位置
 * 3. 继续向后比较，直到数组末尾
 * 4. 重复以上过程，每轮都会将当前未排序部分的最大值"冒泡"到最后
 * 
 * 生活类比：就像水中的气泡，轻的气泡会自然上浮到水面
 * 在排序中，大的数字会逐渐"上浮"到数组的右侧
 * 
 * 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
 * 空间复杂度：O(1) - 只使用常数个额外变量
 * 稳定性：稳定 - 相等元素的相对位置不会改变
 * 
 * @param arr 待排序的整数数组
 */
fun bubbleSort1(arr: IntArray) {
    println("bubbleSort1 from left to right:")
    val len = arr.size
    // 外循环：控制排序轮数，每轮确定一个最大值的位置
    for (i in 0 until len) {
        // 内循环：控制比较次数，len-i-1 避免重复比较已排序部分
        for (j in 0 until len - i - 1) {
            // 关键点：自左往右每两个进行比较，把大的交换到右侧
            if (arr[j] > arr[j + 1]) {
                // Kotlin特点：使用also作用域函数交换
                arr[j] = arr[j + 1].also { arr[j + 1] = arr[j] }
            }
        }
    }
    printArray(arr, "基础升序版本排序结果")
}

/**
 * 冒泡排序基础版本 - 降序排列
 * 
 * 算法思路：
 * 与升序版本相反，从数组末尾开始比较
 * 每轮将当前未排序部分的最小值"下沉"到左侧
 * 
 * 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
 * 空间复杂度：O(1) - 只使用常数个额外变量
 * 稳定性：稳定 - 相等元素的相对位置不会改变
 * 
 * @param arr 待排序的整数数组
 */
fun bubbleSort2(arr: IntArray) {
    println("bubbleSort2 from right to left:")
    val len = arr.size
    // 外循环：控制排序轮数，每轮确定一个最小值的位置
    for (i in 0 until len) {
        // 内循环：从右向左比较，j > i 避免重复比较已排序部分
        for (j in len - 1 downTo i + 1) {
            // 关键点：自右往左每两个进行比较，把小的交换到右侧
            if (arr[j - 1] < arr[j]) {
                // Kotlin特点：使用also作用域函数交换
                arr[j - 1] = arr[j].also { arr[j] = arr[j - 1] }
            }
        }
    }
    printArray(arr, "基础降序版本排序结果")
}

/**
 * 冒泡排序优化版本
 * 
 * 优化思路：
 * 增加一个标志位，记录某一轮是否发生了元素交换
 * 如果某一轮没有发生任何交换，说明数组已经完全有序
 * 此时可以提前终止排序过程，避免不必要的比较
 * 
 * 优化效果：
 * - 对于完全有序的数组：时间复杂度从 O(n²) 优化到 O(n)
 * - 对于部分有序的数组：也会有明显的性能提升
 * - 对于完全逆序的数组：性能与基础版本相同
 * 
 * 时间复杂度：最好O(n)，最坏O(n²)，空间复杂度：O(1)
 * 稳定性：稳定 - 相等元素的相对位置不会改变
 * 
 * @param arr 待排序的整数数组
 */
fun bubbleSort3(arr: IntArray) {
    println("bubbleSort3 add flag:")
    // 优化点：增加一个标志，如果某一轮没有进行过任何的交换
    // 则说明当前数组已排好序，则不必继续后面的遍历
    val len = arr.size
    var flag = true

    // 外循环：增加 flag 条件，当数组已有序时提前终止
    var i = 0
    while (i < len && flag) {
        flag = false // 每轮开始时重置标志
        // 内循环：控制比较次数，len-i-1 避免重复比较已排序部分
        for (j in 0 until len - i - 1) {
            // 关键点：自左往右每两个进行比较，把大的交换到右侧
            if (arr[j] > arr[j + 1]) {
                flag = true // 发生交换，设置标志
                // Kotlin特点：使用also作用域函数交换
                arr[j] = arr[j + 1].also { arr[j + 1] = arr[j] }
            }
        }
        i++
    }
    printArray(arr, "优化版本排序结果")
}

/**
 * 插入冒泡排序法
 * 
 * 算法思路：
 * 将数组分为两部分：左侧已排序区域，右侧待排序区域
 * 每次从待排序区域取出第一个元素，插入到已排序区域的正确位置
 * 
 * 这种方法结合了插入排序的思想，在某些情况下性能更好
 * 
 * 时间复杂度：O(n²)，空间复杂度：O(1)
 * 稳定性：稳定 - 相等元素的相对位置不会改变
 * 
 * @param arr 待排序的整数数组
 */
fun bubbleSort4(arr: IntArray) {
    println("bubbleSort4:")
    val len = arr.size
    // 外循环：控制排序轮数，i 从 1 开始，因为第 0 个元素默认为已排序
    for (i in 1 until len) {
        // 内循环：在已排序区域中查找插入位置
        for (j in 0 until i) {
            // 关键点：如果待插入元素小于已排序区域的某个元素，则交换
            if (arr[j] > arr[i]) {
                // Kotlin特点：使用also作用域函数交换
                arr[i] = arr[j].also { arr[j] = arr[i] }
            }
        }
    }
    printArray(arr, "插入式版本排序结果")
}

/**
 * 打印数组内容的辅助函数
 * @param arr 要打印的数组
 * @param label 数组的标签说明
 */
fun printArray(arr: IntArray, label: String) {
    println("$label: [${arr.joinToString(", ")}]")
}

/**
 * 性能测试辅助函数
 * @param sortFunc 排序函数
 * @param testData 测试数组
 * @param name 版本名称
 */
fun performanceTest(sortFunc: (IntArray) -> Unit, testData: IntArray, name: String) {
    val testArr = testData.clone()
    printArray(testArr, "${name}原始数组")
    
    val duration = measureTimeMillis {
        sortFunc(testArr)
    }
    
    println("$name: ${duration}ms")
    println()
}

/**
 * 主测试函数
 */
fun main() {
    println("=== 冒泡排序算法演示 ===")
    println()

    val testData = intArrayOf(7, 11, 9, 10, 12, 13, 8)

    // 测试1：基础升序版本
    performanceTest(::bubbleSort1, testData, "基础升序版本")

    // 测试2：基础降序版本
    performanceTest(::bubbleSort2, testData, "基础降序版本")

    // 测试3：优化版本
    performanceTest(::bubbleSort3, testData, "优化版本")

    // 测试4：插入式版本
    performanceTest(::bubbleSort4, testData, "插入式版本")

    println("=== 算法对比总结 ===")
    println("1. 基础版本：简单易懂，适合学习算法原理")
    println("2. 降序版本：展示算法的灵活性，可按需排序")
    println("3. 优化版本：通过标志位优化，适合实际应用")
    println("4. 插入式版本：结合其他排序思想，性能更稳定")
}

/* 打印结果
jarry@Mac bubblesort % kotlinc BubbleSort.kt -include-runtime -d BubbleSort.jar && java -jar BubbleSort.jar
=== 冒泡排序算法演示 ===

基础升序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort1 from left to right:
基础升序版本排序结果: [7, 8, 9, 10, 11, 12, 13]
基础升序版本: 0.xxxms

基础降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort2 from right to left:
基础降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]
基础降序版本: 0.xxxms

优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort3 add flag:
优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]
优化版本: 0.xxxms

插入式版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort4:
插入式版本排序结果: [7, 8, 9, 10, 11, 12, 13]
插入式版本: 0.xxxms

=== 算法对比总结 ===
1. 基础版本：简单易懂，适合学习算法原理
2. 降序版本：展示算法的灵活性，可按需排序
3. 优化版本：通过标志位优化，适合实际应用
4. 插入式版本：结合其他排序思想，性能更稳定
*/
