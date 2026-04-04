/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序桶优化版本实现
 * 基于桶排序的LSD（最低位优先）实现，动态桶大小优化
 * 
 * ## 算法特点
 * - 从低位到高位进行排序（LSD - Least Significant Digit）
 * - 使用桶排序实现，动态分配内存
 * - 适合处理稀疏数据，减少不必要的内存分配
 * - 支持负数处理
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数
 * - 空间复杂度：O(n + k') - k'为实际使用的基数范围（≤k）
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
 * 3. 按照桶顺序重新给数组排序
 * 4. 重复步骤2和3，直到排序完成
 */

/**
 * 基数排序，从低到高逐位对比，基于桶排序，注意与基于计数排序的区别
 * 
 * ## 实现步骤
 * 1. 找出数组中的最大值和最小值
 * 2. 根据最大值，逐个按进位(基数)来应用排序，从个位到高位
 * 3. 对每一位进行桶排序处理
 * 4. 将桶中的数据按顺序重新赋值给原数组
 * 
 * @param {Array<number>} arr - 待排序的数字数组
 * @returns {Array<number>} - 排序后的数组
 */
function radixSortBucket(arr) {
    // 第一步：获取数组的最小值和最大值
    // 关键点：用于确定排序范围和处理负数
    const min = Math.min.apply(null, arr)
    const max = Math.max.apply(null, arr)
    
    // 第二步：根据最大值，逐个按进位(基数)来应用排序
    // 关键点：exponent即基数，按个十百千递增
    // 最大减去最小得到数位，最小按0来计算，这样可以支持负数
    for (let exponent = 1; Math.floor((max - min) / exponent) > 0; exponent *= 10) {
        
        // 步骤2.1：初始化桶结构
        // 关键点：创建10个桶对应0-9的数字
        const bucketList = []
        const range = 10
        
        // 步骤2.2：将数据分配到对应的桶中
        // 关键点：支持负数减去最小值来分布桶
        for (let i = 0, l = arr.length; i < l; i++) {
            const item = arr[i] - min
            // 根据数位上的值，把数据追加到对应的桶里
            const idx = Math.floor((item / exponent) % range)
            if (!bucketList[idx]) {
                bucketList[idx] = []
            }
            bucketList[idx].push(arr[i])
        }
        
        console.log('bucketList:', bucketList, 'arr:', arr)

        // 步骤2.3：将每个桶的数据按顺序逐个取出，重新赋值给原数组
        // 关键点：按桶的顺序重新组合数组
        let sortedIndex = 0
        for (let i = 0; i < range; i++) {
            const item = bucketList[i]
            if (item) {
                item.forEach(number => {
                    arr[sortedIndex] = number
                    sortedIndex += 1
                })
            }
        }
        console.log('bucketList sorted:', bucketList, 'arr:', arr)
    }
    
    return arr
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
    console.time('radixSortBucket')
    console.log('origin radixSortBucket:', arr1)
    
    // 执行排序
    console.log('radixSortBucket sorted:', radixSortBucket(arr1))
    
    // 输出执行时间
    console.timeEnd('radixSortBucket')
})()

/**
jarry@Mac radixsort % node radix_sort_bucket.js
origin radixSortBucket: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
]
bucketList: [
  [ -4, -323454 ],
  [ 7 ],
  <2 empty items>,
  [ 10, 200 ],
  [ 87431 ],
  <1 empty item>,
  [ 33, 43 ],
  <1 empty item>,
  [ 15, 1235 ]
] arr: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
]
bucketList sorted: [
  [ -4, -323454 ],
  [ 7 ],
  <2 empty items>,
  [ 10, 200 ],
  [ 87431 ],
  <1 empty item>,
  [ 33, 43 ],
  <1 empty item>,
  [ 15, 1235 ]
] arr: [
    -4, -323454,     7,
    10,     200, 87431,
    33,      43,    15,
  1235
]
bucketList: [
  [ -323454 ],
  <4 empty items>,
  [ -4, 200 ],
  [ 7, 10, 15 ],
  <1 empty item>,
  [ 87431, 33, 1235 ],
  [ 43 ]
] arr: [
    -4, -323454,     7,
    10,     200, 87431,
    33,      43,    15,
  1235
]
bucketList sorted: [
  [ -323454 ],
  <4 empty items>,
  [ -4, 200 ],
  [ 7, 10, 15 ],
  <1 empty item>,
  [ 87431, 33, 1235 ],
  [ 43 ]
] arr: [
  -323454, -4,  200,
        7, 10,   15,
    87431, 33, 1235,
       43
]
bucketList: [
  [ -323454 ],
  <3 empty items>,
  [ -4, 7, 10, 15, 33, 43 ],
  <1 empty item>,
  [ 200, 1235 ],
  <1 empty item>,
  [ 87431 ]
] arr: [
  -323454, -4,  200,
        7, 10,   15,
    87431, 33, 1235,
       43
]
bucketList sorted: [
  [ -323454 ],
  <3 empty items>,
  [ -4, 7, 10, 15, 33, 43 ],
  <1 empty item>,
  [ 200, 1235 ],
  <1 empty item>,
  [ 87431 ]
] arr: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
bucketList: [
  [ -323454, 87431 ],
  <2 empty items>,
  [
    -4,  7,  10, 15,
    33, 43, 200
  ],
  [ 1235 ]
] arr: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
bucketList sorted: [
  [ -323454, 87431 ],
  <2 empty items>,
  [
    -4,  7,  10, 15,
    33, 43, 200
  ],
  [ 1235 ]
] arr: [
  -323454, 87431,  -4,
        7,    10,  15,
       33,    43, 200,
     1235
]
bucketList: [
  [ -323454 ],
  [ 87431 ],
  [
     -4,    7, 10,
     15,   33, 43,
    200, 1235
  ]
] arr: [
  -323454, 87431,  -4,
        7,    10,  15,
       33,    43, 200,
     1235
]
bucketList sorted: [
  [ -323454 ],
  [ 87431 ],
  [
     -4,    7, 10,
     15,   33, 43,
    200, 1235
  ]
] arr: [
  -323454, 87431,  -4,
        7,    10,  15,
       33,    43, 200,
     1235
]
bucketList: [
  [ -323454 ],
  <2 empty items>,
  [
     -4,    7, 10,
     15,   33, 43,
    200, 1235
  ],
  [ 87431 ]
] arr: [
  -323454, 87431,  -4,
        7,    10,  15,
       33,    43, 200,
     1235
]
bucketList sorted: [
  [ -323454 ],
  <2 empty items>,
  [
     -4,    7, 10,
     15,   33, 43,
    200, 1235
  ],
  [ 87431 ]
] arr: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
radixSortBucket sorted: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
radixSortBucket: 4.525ms
 */