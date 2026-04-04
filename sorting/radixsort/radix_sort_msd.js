/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序MSD版本实现
 * 递归MSD（最高位优先）实现，基于桶排序
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
 * ## 负数处理
 * - 使用最小值偏移处理负数
 * - 通过arr[i] - min确保索引为正数
 * - 支持包含负数的整数数组排序
 * 
 * ## 实现原理
 * 1. 找出数组中最大的数，确定其位数
 * 2. MSD是从高位开始，依次按照位数的值将数字放入到不同桶中
 * 3. 如果桶里的长度超过1，则通过递归继续按桶排序
 * 4. 当桶里的数据只有1位时添加到原列表对应位置
 * 5. 重复步骤2和3，直到按照最高位排序完成
 */

/**
 * 基数排序，从高到低逐位排序，递归方式，基于桶排序
 * 
 * ## 实现步骤
 * 1. 找出数组中的最大值和最小值
 * 2. 计算数字的位数，确定最高位的基数
 * 3. 调用递归桶排序函数进行排序
 * 
 * @param {Array<number>} arr - 待排序的数字数组
 * @returns {Array<number>} - 排序后的数组
 */
function radixSortMSD(arr) {

    /**
     * 递归桶排序实现基数排序
     * 
     * ## 实现原理
     * - 使用桶排序对指定位数进行排序
     * - 递归处理每个桶中的子数组
     * - 从最高位向最低位逐层处理
     * 
     * @param {Array<number>} arr - 待排序的数组
     * @param {number} exponent - 当前处理的位数基数
     * @returns {Array<number>} - 排序后的数组
     */
    function bucketSort(arr, exponent) {
        // 第一步：输出调试信息
        // 关键点：显示当前排序状态，便于调试
        console.log('origin arr:', arr, 'exponent:', exponent)
        
        // 第二步：递归终止条件检查
        // 关键点：数组为空或长度为1或位数为0时停止递归
        if (!arr || arr.length <= 1 || exponent < 1) {
            return arr
        }
        
        // 第三步：获取数组的最小值
        // 关键点：用于处理负数，计算偏移量
        const min = Math.min.apply(null, arr)
        const range = 10

        console.log('prepared arr:', arr, 'exponent:', exponent)

        // 第四步：初始化桶结构
        // 关键点：定义桶二维数组，长度为10，放入0-9的数字
        const buckets = []
        for (let i = 0; i < range; i++) {
            buckets[i] = []
        }
        
        // 第五步：将数据分配到桶中
        // 关键点：根据数位上的值，把数据追加到对应的桶里，减去min是支持负数
        for (let i = 0, l = arr.length; i < l; i++) {
            const item = arr[i] - min
            const bucketIdx = Math.floor(item / exponent % range)
            
            // 步骤5.1：提前填充空桶或使用时再填充
            // 关键点：确保桶存在
            if (!buckets[bucketIdx]) {
                buckets[bucketIdx] = []
            }
            buckets[bucketIdx].push(arr[i])
        }
        
        console.log('append to buckets:', buckets)

        // 第六步：将每个桶的数据按顺序逐个取出，重新赋值给原数组
        // 关键点：按桶的顺序重新组合数组
        let sortedIdx = 0

        for (let i = 0; i < range; i++) {
            const bucket = buckets[i]
            if (bucket && bucket.length > 0) {
                // 步骤6.1：如果是数组则继续递归调用，位数降低1位
                // 关键点：递归处理下一位
                const sortedBucket = bucketSort(bucket, Math.floor(exponent / range))
                
                // 步骤6.2：把各个桶里的值按顺序赋给原数组
                // 关键点：将递归排序的结果复制回原数组
                sortedBucket.forEach(num => {
                    arr[sortedIdx] = num
                    // console.log('bucket:', bucket, 'sortedBucket:', sortedBucket, 'sortedIdx:', sortedIdx, 'set arr:', arr)
                    sortedIdx += 1
                })
            }
        }
        
        // 第七步：输出当前轮次排序结果
        // 关键点：显示当前位数排序后的数组状态
        console.log('exponent:', exponent, 'sorted arr:', arr)
        return arr
    }

    // 第一步：获取数组的最小值和最大值
    // 关键点：用于确定排序范围和处理负数
    const max = Math.max.apply(null, arr)
    const min = Math.min.apply(null, arr)
    
    // 第二步：计算数字的位数，确定最高位的基数
    // 关键点：获取数字一共有几位，减去min得到最大值，以支持负数
    const numberOfDigits = Math.floor(Math.log10(max - min) + 1)
    const exponent = Math.pow(10, numberOfDigits - 1)
    
    // 第三步：调用递归桶排序
    // 关键点：根据数组最大值，自后向前逐个按数位基数(exponent)比较排序
    return bucketSort(arr, exponent)
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
    const arr1 = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
    
    // 性能测试：记录开始时间
    console.time('radixSortMSD')
    console.log('origin radixSortMSD:', arr1)
    
    // 执行排序
    console.log('radixSortMSD sorted:', radixSortMSD(arr1))
    
    // 输出执行时间
    console.timeEnd('radixSortMSD')
})()

/*
jarry@Mac radixsort % node radix_sort_msd.js 
origin radixSortMSD: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
]
origin arr: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
] exponent: 100000
prepared arr: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
] exponent: 100000
append to buckets: [
  [ -323454 ],
  [],
  [],
  [
      33,  -4, 15,
      43,   7, 10,
    1235, 200
  ],
  [ 87431 ],
  [],
  [],
  [],
  [],
  []
]
origin arr: [ -323454 ] exponent: 10000
origin arr: [
    33,  -4, 15,
    43,   7, 10,
  1235, 200
] exponent: 10000
prepared arr: [
    33,  -4, 15,
    43,   7, 10,
  1235, 200
] exponent: 10000
append to buckets: [
  [
      33,  -4, 15,
      43,   7, 10,
    1235, 200
  ],
  [],
  [],
  [],
  [],
  [],
  [],
  [],
  [],
  []
]
origin arr: [
    33,  -4, 15,
    43,   7, 10,
  1235, 200
] exponent: 1000
prepared arr: [
    33,  -4, 15,
    43,   7, 10,
  1235, 200
] exponent: 1000
append to buckets: [
  [
    33, -4,  15, 43,
     7, 10, 200
  ],
  [ 1235 ],
  [],
  [],
  [],
  [],
  [],
  [],
  [],
  []
]
origin arr: [
  33, -4,  15, 43,
   7, 10, 200
] exponent: 100
prepared arr: [
  33, -4,  15, 43,
   7, 10, 200
] exponent: 100
append to buckets: [ [ 33, -4, 15, 43, 7, 10 ], [], [ 200 ], [], [], [], [], [], [], [] ]
origin arr: [ 33, -4, 15, 43, 7, 10 ] exponent: 10
prepared arr: [ 33, -4, 15, 43, 7, 10 ] exponent: 10
append to buckets: [ [ -4 ], [ 15, 7, 10 ], [], [ 33 ], [ 43 ], [], [], [], [], [] ]
origin arr: [ -4 ] exponent: 1
origin arr: [ 15, 7, 10 ] exponent: 1
prepared arr: [ 15, 7, 10 ] exponent: 1
append to buckets: [
  [ 7 ],  [], [],
  [ 10 ], [], [],
  [],     [], [ 15 ],
  []
]
origin arr: [ 7 ] exponent: 0
origin arr: [ 10 ] exponent: 0
origin arr: [ 15 ] exponent: 0
exponent: 1 sorted arr: [ 7, 10, 15 ]
origin arr: [ 33 ] exponent: 1
origin arr: [ 43 ] exponent: 1
exponent: 10 sorted arr: [ -4, 7, 10, 15, 33, 43 ]
origin arr: [ 200 ] exponent: 10
exponent: 100 sorted arr: [
  -4,  7,  10, 15,
  33, 43, 200
]
origin arr: [ 1235 ] exponent: 100
exponent: 1000 sorted arr: [
   -4,    7, 10,
   15,   33, 43,
  200, 1235
]
exponent: 10000 sorted arr: [
   -4,    7, 10,
   15,   33, 43,
  200, 1235
]
origin arr: [ 87431 ] exponent: 10000
exponent: 100000 sorted arr: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
radixSortMSD sorted: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
radixSortMSD: 11.062ms
*/
