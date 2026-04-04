/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序扁平化版本实现
 * 基于桶排序的LSD（最低位优先）实现，利用JS数组展开来还原数组
 * 
 * ## 算法特点
 * - 从低位到高位进行排序（LSD - Least Significant Digit）
 * - 使用桶排序实现，利用数组扁平化
 * - 支持负数处理
 * - 使用现代JS的flat()方法或自定义flatten函数
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数
 * - 空间复杂度：O(n + k) - 需要桶和临时数组
 * - 稳定性：稳定 - 保持相等元素的相对位置
 * 
 * ## 负数处理
 * - 使用最小值偏移处理负数
 * - 通过arr[i] - min确保索引为正数
 * - 支持包含负数的整数数组排序
 * 
 * ## 实现原理
 * 1. 找出数组中最大的数，确定其位数
 * 2. LSD是低位到高位，依次按照位数的值将数字放入到不同桶中
 * 3. 使用数组扁平化将桶中的数据重新组合
 * 4. 重复步骤2和3，直到排序完成
 */

/**
 * 基数排序，从低到高逐位数位对比排序，基于桶排序，利用JS数组展开来还原数组
 * 
 * ## 实现步骤
 * 1. 找出数组中的最大值和最小值
 * 2. 根据最大值，逐个按进位(基数)来应用排序，从个位到高位
 * 3. 对每一位进行桶排序处理
 * 4. 使用数组扁平化将桶中的数据重新组合
 * 
 * @param {Array<number>} arr - 待排序的数字数组
 * @returns {Array<number>} - 排序后的数组
 */
function radixSort2(arr) {

    /**
     * 获取数字指定位置的数
     * 
     * @param {number} num - 要处理的数字
     * @param {number} position - 位数位置（1=个位，2=十位，...）
     * @returns {number} - 指定位数的值
     */
    function getDigit(num, position) {
        const digit = Math.floor(num / Math.pow(10, position - 1)) % 10
        return digit
    }

    /**
     * 获取数组最大数字的位数
     * 
     * @param {number} num - 要处理的数字
     * @returns {number} - 数字的位数
     */
    function getNumberLength(num) {
        let maxLength = 0
        while (num > 0) {
            maxLength++
            num /= 10
        }
        return maxLength
    }

    // 第一步：获取数组的最小值和最大值
    // 关键点：用于确定排序范围和处理负数
    const max = Math.max.apply(null, arr)
    const min = Math.min.apply(null, arr)
    
    // 第二步：找出数组中最大数的长度
    // 关键点：可以通过计算或直接换成字符串求长度，减去min以便支持负数
    // const maxLength = (max - min).toString().length
    const maxLength = getNumberLength(max - min)

    // 第三步：按位数循环处理
    // 关键点：从个位开始，逐位处理到最高位
    for (let i = 0; i < maxLength; i++) {
        
        // 步骤3.1：每位数准备10个空数组，用于放数字0-9
        // 关键点：创建桶结构
        const buckets = Array.from({
            length: 10
        }, () => [])

        // 步骤3.2：遍历数组将数位上的数放入对应桶里
        // 关键点：根据当前位数分配到对应的桶
        for (let j = 0, l = arr.length; j < l; j++) {
            const item = (arr[j] - min)
            
            // 从后往前获取数位上的数字，通过字符串方式或计算的方式
            // const numStr = item.toString().charAt(item.length - 1 - i)
            // const num = Number(numStr)

            // 从后往前获取第x位置的数，通过计算的方式
            const num = getDigit(item, i + 1)
            
            // 当前位数如果不为空则添加到基数桶中
            // console.log('radixSort2:', 'i=', i, 'j=', j, 'item=', item, 'num=', num, 'buckets=', buckets)
            if (num !== isNaN) {
                buckets[num].push((arr[j]))
            }
        }

        // 步骤3.3：将桶逐级展开取出数字
        // 关键点：使用数组扁平化重新组合数组
        if (buckets.flat) {
            // 步骤3.3.1：使用现代JS的flat()方法
            // 关键点：ES2019+的特性，直接扁平化数组
            arr = buckets.flat()
        } else {
            // 步骤3.3.2：使用自定义flatten函数
            // 关键点：兼容旧版本JS的扁平化实现
            arr = flatten(buckets)
        }
    }

    return arr
}

/**
 * 自定义数组展开函数，与默认flatten功能一样，循环调用，非递归写法
 * 
 * @param {Array} input - 要扁平化的数组
 * @returns {Array} - 扁平化后的数组
 */
const flatten = (input) => {
    const stack = [...input]
    const res = []
    while (stack.length) {
        const next = stack.pop()
        if (Array.isArray(next)) {
            stack.push(...next)
        } else {
            res.push(next)
        }
    }
    return res.reverse()
}

/**
 * 数组展开，与flatten功能一样，这是递归实现
 * 
 * @param {Array} input - 要扁平化的数组
 * @param {number} depth - 扁平化深度
 * @param {Array} stack - 结果栈
 * @returns {Array} - 扁平化后的数组
 */
const flat = (input, depth = 1, stack = []) => {
    for (const item of input) {
        if (Array.isArray(item) && depth > 0) {
            flat(item, depth - 1, stack)
        } else {
            stack.push(item)
        }
    }
    return stack
}

/**
 * 测试函数
 * 
 * ## 测试内容
 * - 包含负数的整数数组排序
 * - 性能测试和时间统计
 * - 排序结果验证
 */
(function () {
    // 测试数据：包含正数和负数的混合数组
    const arr2 = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
    
    // 性能测试：记录开始时间
    console.time('radixSort2')
    console.log('origin radixSort2:', arr2)
    
    // 执行排序
    console.log('radixSort2 sorted:', radixSort2(arr2))
    
    // 输出执行时间
    console.timeEnd('radixSort2')
})()

/**
jarry@Mac radixsort % node radix_sort_flat.js 
origin radixSort2: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
]
radixSort2 sorted: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
 */