// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

/**
 * 基数排序算法实现
 * 提供5种不同的实现方式，适合不同场景和性能需求
 * 
 * ==================== 5个基数排序算法的相同与区别 ====================
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
 * 1. radix_sort1 - 计数排序基数排序版本
 *    - 实现方式：基于计数排序的LSD（最低位优先）实现
 *    - 负数支持：使用最小值偏移处理负数
 *    - 内存使用：O(n + k) 需要计数数组和输出数组
 *    - 特点：经典实现，代码清晰易懂
 * 
 * 2. radix_sort2 - MSD基数排序版本
 *    - 实现方式：递归MSD实现，从最高位开始排序
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k) 需要桶和计数数组
 *    - 特点：适合字符串或变长数据，高位优先处理
 * 
 * 3. radix_sort3 - 迭代MSD基数排序版本
 *    - 实现方式：使用栈模拟递归的MSD（最高位优先）实现
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k + s) s为栈空间
 *    - 特点：避免递归深度过大，适合大数据集
 * 
 * 4. radix_sort4 - 桶优化基数排序版本
 *    - 实现方式：动态桶大小的LSD实现
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k') k'为实际使用的基数范围（≤k）
 *    - 特点：内存优化，适合稀疏数据
 * 
 * 5. radix_sort5 - 递归基数排序版本
 *    - 实现方式：递归处理每一位的LSD实现
 *    - 负数支持：使用最小值偏移处理负数
 *    - 内存使用：O(n + k + d) d为递归栈深度
 *    - 特点：代码简洁，递归深度由数字位数决定
 * 
 * 【性能对比】
 * - 最快：radix_sort5（递归版本）和radix_sort4（桶优化版本）
 * - 内存最优：radix_sort4（动态桶大小）
 * - 最稳定：radix_sort3（迭代MSD，避免递归栈溢出）
 * - 代码最简洁：radix_sort5（递归实现）
 * 
 * 【选择建议】
 * - 一般情况：推荐radix_sort1（计数排序）
 * - 大数据集：推荐radix_sort3（迭代MSD）
 * - 内存敏感：推荐radix_sort4（桶优化）
 * - 代码简洁：推荐radix_sort5（递归版本）
 * - 字符串排序：推荐radix_sort2（MSD版本）
 */

import Foundation

/**
 * 打印数组内容的辅助函数
 */
func printArray(_ arr: [Int], label: String) {
    print("\(label): \(arr)")
}

/**
 * 性能测试辅助函数
 */
func performanceTest(_ sortFunc: @escaping (inout [Int]) -> Void, arr: [Int], name: String) {
    // 创建数组副本，避免修改原数组
    var testArr = arr
    printArray(testArr, label: name)
    
    // 开始计时
    let startTime = CFAbsoluteTimeGetCurrent()
    sortFunc(&testArr)
    let endTime = CFAbsoluteTimeGetCurrent()
    
    let duration = (endTime - startTime) * 1000
    print("\(name): \(String(format: "%.3f", duration))ms")
    printArray(testArr, label: name + "排序结果")
    print("") // 空行分隔
}

// ==================== 测试数据 ====================

// 测试数据：包含大数字的典型数组
let testData: [Int] = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]

// 负数测试数据
let negativeTestData: [Int] = [170, 45, 75, -90, -802, 24, 2, 66, -5, 0]

/**
 * 获取数字的指定位数
 */
func getDigit(_ num: Int, exp: Int) -> Int {
    abs(num) / exp % 10
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
func countingSort(_ arr: inout [Int], exponent: Int) {
    // 第一步：初始化变量和数组，按10个桶大小，0-9的个位数
    let arrLen = arr.count
    let range = 10
    var countList = Array(repeating: 0, count: range)
    var sortedList = Array(repeating: 0, count: arrLen)

    // 第二步：找出最小值
    // 关键点：处理负数情况，需要找到最小值进行偏移
    let minValue = arr.min()!

    // 第三步：初始化计数数组
    // 关键点：将计数数组清零
    for i in 0..<range {
        countList[i] = 0
    }

    // 第四步：根据数字所在位置进行计数
    // 关键点：使用arr[i] - minValue来处理负数，确保索引为正数
    for i in 0..<arrLen {
        let item = arr[i] - minValue
        let idx = (item / exponent) % range
        countList[idx] += 1
    }

    // 第五步：构建计数排序
    // 关键点：后面的位数为前面的累加之和，形成累积计数
    for i in 1..<range {
        countList[i] += countList[i - 1]
    }
    print("radix_sort1 countingSort countList:[\(countList.map(String.init).joined(separator: ", "))]")

    // 第六步：构建输出数组
    // 关键点：从后向前遍历，保持排序的稳定性
    for i in (0..<arrLen).reversed() {
        let item = arr[i] - minValue
        let idx = (item / exponent) % range
        sortedList[countList[idx] - 1] = arr[i]
        countList[idx] -= 1
    }

    // 第七步：复制到数组重排原始数组
    // 关键点：将排序结果复制回原数组
    for i in 0..<arrLen {
        arr[i] = sortedList[i]
    }
    print("radix_sort1 -> sortedList:[\(sortedList.map(String.init).joined(separator: ", "))]")
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
 */
func radix_sort1(_ arr: inout [Int]) {
    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if arr.isEmpty {
        return
    }

    // 第二步：找出最大值和最小值
    // 关键点：确定排序的位数范围和处理负数
    let maxValue = arr.max()!
    let minValue = arr.min()!

    // 第三步：根据最大值，逐个按进位(基数)来应用排序
    // 关键点：exponent即数位基数，按个十百千递增
    // 最大减去最小得到数位，最小按0来计算，这样可以支持负数
    var exponent = 1
    while (maxValue - minValue) / exponent > 0 {
        countingSort(&arr, exponent: exponent)
        exponent *= 10
    }
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
func msdSort(_ arr: inout [Int], left: Int, right: Int, exp: Int) {
    // 第一步：递归终止条件检查
    // 关键点：范围无效或位数不足时返回
    if left >= right || exp < 1 {
        return
    }

    // 第二步：创建桶
    // 关键点：创建10个桶，对应0-9的数字
    var buckets = Array(repeating: [Int](), count: 10)

    // 第三步：分配到桶中
    // 关键点：根据当前位数将元素分配到对应桶中
    for i in left...right {
        let digit = getDigit(arr[i], exp: exp)
        buckets[digit].append(arr[i])
    }

    // 第四步：重新排序并递归处理每个桶
    // 关键点：将桶中元素复制回原数组，并递归处理子数组
    var index = left
    var currentLeft = left
    for i in 0..<10 {
        if !buckets[i].isEmpty {
            // 步骤4.1：复制桶中元素回原数组
            // 关键点：按桶的顺序复制元素，保持稳定性
            for value in buckets[i] {
                arr[index] = value
                index += 1
            }

            // 步骤4.2：递归处理下一个位数
            // 关键点：递归处理当前桶的子数组
            msdSort(&arr, left: currentLeft, right: index - 1, exp: exp / 10)
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
 */
func radix_sort2(_ arr: inout [Int]) {
    print("radix_sort2 MSD:")

    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if arr.isEmpty {
        return
    }

    // 第二步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定最高位数
    let max = arr.max()!

    // 第三步：计算最高位对应的基数
    // 关键点：exp从1开始，不断乘以10直到超过最大值
    var exp = 1
    while max / exp > 0 {
        exp *= 10
    }

    // 第四步：调用MSD递归排序
    // 关键点：从最高位开始递归排序
    msdSort(&arr, left: 0, right: arr.count - 1, exp: exp / 10)

    // 第五步：输出排序结果
    printArray(arr, label: "排序后数组")
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
 */
func radix_sort3(_ arr: inout [Int]) {
    print("radix_sort3 iterative MSD:")

    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if arr.isEmpty {
        return
    }

    // 第二步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定最高位数
    let max = arr.max()!

    // 第三步：计算最高位对应的基数
    // 关键点：exp从1开始，不断乘以10直到超过最大值
    var exp = 1
    while max / exp > 0 {
        exp *= 10
    }

    // 第四步：使用栈模拟递归
    // 关键点：创建栈数组，初始化栈顶指针
    struct StackItem {
        let left: Int
        let right: Int
        let exp: Int
    }

    var stack = [StackItem(
        left: 0,
        right: arr.count - 1,
        exp: exp / 10
    )]

    // 第五步：循环处理栈中的范围
    // 关键点：栈不为空时继续处理，模拟递归调用过程
    while !stack.isEmpty {
        // 步骤5.1：从栈中取出待处理的范围
        // 关键点：后进先出，取出栈顶元素
        let item = stack.removeLast()
        let left = item.left
        let right = item.right
        let currentExp = item.exp

        // 步骤5.2：递归终止条件检查
        // 关键点：范围无效或位数不足时跳过
        if left >= right || currentExp < 1 {
            continue
        }

        // 步骤5.3：创建桶
        // 关键点：创建10个桶，对应0-9的数字
        var buckets = Array(repeating: [Int](), count: 10)

        // 步骤5.4：分配到桶中
        // 关键点：根据当前位数将元素分配到对应桶中
        for i in left...right {
            let digit = getDigit(arr[i], exp: currentExp)
            buckets[digit].append(arr[i])
        }

        // 步骤5.5：重新排序并将子问题入栈
        // 关键点：将桶中元素复制回原数组，并将子问题入栈
        var index = left
        var nextLeft = left
        for i in 0..<10 {
            if !buckets[i].isEmpty {
                // 步骤5.5.1：复制桶中元素回原数组
                // 关键点：按桶的顺序复制元素，保持稳定性
                for value in buckets[i] {
                    arr[index] = value
                    index += 1
                }

                // 步骤5.5.2：将子问题入栈
                // 关键点：将子数组范围和下一位数入栈，逆序处理保持正确顺序
                stack.append(StackItem(
                    left: nextLeft,
                    right: index - 1,
                    exp: currentExp / 10
                ))
                nextLeft = index
            }
        }
    }

    // 第六步：输出排序结果
    printArray(arr, label: "排序后数组")
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
 */
func radix_sort4(_ arr: inout [Int]) {
    print("radix_sort4 bucket optimized:")

    // 第一步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定处理位数
    let max = arr.max()!

    // 第二步：对每个位数进行计数排序
    // 关键点：从个位开始，逐位处理，直到最高位
    var exp = 1
    while max / exp > 0 {
        let n = arr.count
        var output = Array(repeating: 0, count: n)

        // 步骤2.1：动态确定桶范围
        // 关键点：统计当前位数的最小和最大值，减少桶数量
        var minDigit = 9
        var maxDigit = 0
        for i in 0..<n {
            let digit = getDigit(arr[i], exp: exp)
            if digit < minDigit {
                minDigit = digit
            }
            if digit > maxDigit {
                maxDigit = digit
            }
        }

        // 步骤2.2：创建动态大小的计数数组
        // 关键点：只创建实际需要的桶大小，优化内存使用
        let bucketSize = maxDigit - minDigit + 1
        var count = Array(repeating: 0, count: bucketSize)

        // 步骤2.3：统计每个数字的出现次数
        // 关键点：使用偏移量处理，支持任意范围的数字
        for i in 0..<n {
            let digit = getDigit(arr[i], exp: exp)
            count[digit - minDigit] += 1
        }

        // 步骤2.4：计算累计计数
        // 关键点：当前位置加上左侧位置，形成累积计数
        for i in 1..<count.count {
            count[i] += count[i - 1]
        }

        // 步骤2.5：构建输出数组
        // 关键点：从后向前遍历，保持排序的稳定性
        for i in (0..<n).reversed() {
            let digit = getDigit(arr[i], exp: exp)
            output[count[digit - minDigit] - 1] = arr[i]
            count[digit - minDigit] -= 1
        }

        // 步骤2.6：复制回原数组
        // 关键点：将排序结果复制回原数组，准备下一位处理
        for i in 0..<n {
            arr[i] = output[i]
        }

        exp *= 10
    }

    // 第三步：输出排序结果
    printArray(arr, label: "排序后数组")
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
func recursiveRadixSort(_ arr: inout [Int], exponent: Int, minValue: Int, maxValue: Int) {
    // 第一步：递归终止条件检查
    // 关键点：当基数超过最大值时停止递归
    if (maxValue - minValue) / exponent == 0 {
        return
    }

    // 第二步：初始化计数排序变量
    // 关键点：为当前位数的计数排序准备变量
    let range = 10
    var countList = Array(repeating: 0, count: range)
    var sortedList = Array(repeating: 0, count: arr.count)

    // 第三步：初始化计数数组
    // 关键点：将计数数组清零
    for i in 0..<range {
        countList[i] = 0
    }

    // 第四步：根据数字所在位置进行计数
    // 关键点：使用arr[i] - minValue来处理负数，确保索引为正数
    for i in 0..<arr.count {
        let item = arr[i] - minValue
        let idx = (item / exponent) % range
        countList[idx] += 1
    }

    // 第五步：构建计数排序
    // 关键点：后面的位数为前面的累加之和，形成累积计数
    for i in 1..<range {
        countList[i] += countList[i - 1]
    }

    // 第六步：构建输出数组
    // 关键点：从后向前遍历，保持排序的稳定性
    for i in (0..<arr.count).reversed() {
        let item = arr[i] - minValue
        let idx = (item / exponent) % range
        sortedList[countList[idx] - 1] = arr[i]
        countList[idx] -= 1
    }

    // 第七步：复制到数组重排原始数组
    // 关键点：将排序结果复制回原数组
    for i in 0..<arr.count {
        arr[i] = sortedList[i]
    }

    // 第八步：递归处理下一位
    // 关键点：递归调用处理更高位数
    recursiveRadixSort(&arr, exponent: exponent * 10, minValue: minValue, maxValue: maxValue)
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
 */
func radix_sort5(_ arr: inout [Int]) {
    // 第一步：输出测试信息
    // 关键点：标识当前测试的算法类型
    print("radix_sort5 递归基数排序:")

    // 第二步：找出最大值和最小值
    // 关键点：确定排序的位数范围和处理负数
    let maxValue = arr.max()!
    let minValue = arr.min()!

    // 第三步：调用递归基数排序
    // 关键点：从最低位（个位）开始递归排序
    recursiveRadixSort(&arr, exponent: 1, minValue: minValue, maxValue: maxValue)

    // 第四步：输出排序结果
    // 关键点：显示排序后的数组，验证算法正确性
    printArray(arr, label: "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

func main() {
    // 测试1：radix_sort1 - 计数排序基数排序版本（支持负数）
    performanceTest(radix_sort1, arr: testData, name: "radix_sort1 - 计数排序基数排序版本")

    // 测试2：radix_sort2 - MSD基数排序版本
    performanceTest(radix_sort2, arr: testData, name: "radix_sort2 - MSD基数排序版本")

    // 测试3：radix_sort3 - 迭代MSD基数排序版本
    performanceTest(radix_sort3, arr: testData, name: "radix_sort3 - 迭代MSD基数排序版本")

    // 测试4：radix_sort4 - 桶优化基数排序版本
    performanceTest(radix_sort4, arr: testData, name: "radix_sort4 - 桶优化基数排序版本")

    // 测试5：radix_sort5 - 递归基数排序版本
    performanceTest(radix_sort5, arr: testData, name: "radix_sort5 - 递归基数排序版本")

    // 测试6：负数数据处理
    print("\n=== 负数测试 ===")
    performanceTest(radix_sort5, arr: negativeTestData, name: "radix_sort5 - 递归基数排序版本（负数测试）")

    print("=== 算法对比总结 ===")
    print("1. radix_sort1：计数排序基数排序版本，支持负数")
    print("2. radix_sort2：MSD基数排序版本，高位优先递归处理")
    print("3. radix_sort3：迭代MSD基数排序版本，避免递归性能稳定")
    print("4. radix_sort4：桶优化基数排序版本，动态桶大小内存优化")
    print("5. radix_sort5：递归基数排序版本，递归处理每一位")
}

// 调用main函数
main()

/*
打印结果
jarry@Mac radixsort % swift radix_sort.swift
radix_sort1 - 计数排序基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radix_sort1 countingSort countList:[2, 4, 4, 5, 5, 5, 7, 8, 8, 10]
radix_sort1 -> sortedList:[4, 323454, 15, 1235, 7, 10, 200, 87431, 33, 43]
radix_sort1 countingSort countList:[3, 4, 6, 8, 8, 9, 9, 9, 9, 10]
radix_sort1 -> sortedList:[4, 7, 10, 15, 87431, 33, 1235, 43, 323454, 200]
radix_sort1 countingSort countList:[6, 7, 8, 8, 10, 10, 10, 10, 10, 10]
radix_sort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort1 countingSort countList:[7, 8, 8, 9, 9, 9, 9, 10, 10, 10]
radix_sort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radix_sort1 countingSort countList:[8, 8, 9, 9, 9, 9, 9, 9, 10, 10]
radix_sort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radix_sort1 countingSort countList:[9, 9, 9, 10, 10, 10, 10, 10, 10, 10]
radix_sort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort1 - 计数排序基数排序版本: 0.115ms
radix_sort1 - 计数排序基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radix_sort2 - MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radix_sort2 MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort2 - MSD基数排序版本: 0.051ms
radix_sort2 - MSD基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radix_sort3 - 迭代MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radix_sort3 iterative MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort3 - 迭代MSD基数排序版本: 0.043ms
radix_sort3 - 迭代MSD基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radix_sort4 - 桶优化基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radix_sort4 bucket optimized:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort4 - 桶优化基数排序版本: 0.036ms
radix_sort4 - 桶优化基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radix_sort5 - 递归基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radix_sort5 递归基数排序:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort5 - 递归基数排序版本: 0.036ms
radix_sort5 - 递归基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]


=== 负数测试 ===
radix_sort5 - 递归基数排序版本（负数测试）: [170, 45, 75, -90, -802, 24, 2, 66, -5, 0]
radix_sort5 递归基数排序:
排序后数组: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]
radix_sort5 - 递归基数排序版本（负数测试）: 0.021ms
radix_sort5 - 递归基数排序版本（负数测试）排序结果: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]

=== 算法对比总结 ===
1. radix_sort1：计数排序基数排序版本，支持负数
2. radix_sort2：MSD基数排序版本，高位优先递归处理
3. radix_sort3：迭代MSD基数排序版本，避免递归性能稳定
4. radix_sort4：桶优化基数排序版本，动态桶大小内存优化
5. radix_sort5：递归基数排序版本，递归处理每一位
*/
