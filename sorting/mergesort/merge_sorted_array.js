/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 合并两个已排序数组算法实现
 * 提供五种不同的合并策略，适合不同场景和性能需求
 * 
 * 算法思路：
 * 1. 双指针法：同时遍历两个数组，逐个比较并合并
 * 2. 插入法（前向）：将一个数组的元素逐个插入到另一个数组中
 * 3. 插入法（后向）：从后往前查找插入位置
 * 4. 双指针法（push）：使用push方法添加元素
 * 5. 合并排序法：先合并数组再进行排序
 * 
 * 时间复杂度：O(n+m) - 双指针法最优
 * 空间复杂度：O(n+m) - 需要额外空间存储结果
 * 稳定性：稳定 - 保持相等元素的相对位置
 */
;(function () {
  /**
   * 合并两个已排序数组 - 双指针法
   * 
   * 算法思路：
   * 使用两个指针分别指向两个数组的起始位置，同时遍历比较
   * 将较小的元素放入结果数组，并移动相应指针，直到其中一个数组遍历完成
   * 最后将剩余数组元素直接复制到结果数组中
   * 
   * 步骤说明：
   * 1. 初始化结果数组和指针
   * 2. 同时遍历两个数组，比较并合并
   * 3. 处理剩余元素
   * 
   * 关键点：
   * - 使用三个指针分别跟踪两个输入数组和一个结果数组
   * - 比较当前元素，选择较小的放入结果数组
   * - 保持算法的稳定性
   * 
   * 时间复杂度：O(n+m) - 每个元素只被访问一次
   * 空间复杂度：O(n+m) - 需要额外空间存储结果
   * 稳定性：稳定 - 保持相等元素的相对位置
   * 
   * @param {number[]} one - 第一个已排序数组
   * @param {number[]} two - 第二个已排序数组
   * @returns {number[]} 合并后的有序数组
   */
  function mergeSorted1(one, two) {
    // 步骤1：初始化结果数组和指针
    // 关键点：结果数组长度为两个数组长度之和
    const result = []
    let i = 0  // 数组1下标
    let j = 0  // 数组2下标
    let k = 0  // 结果数组下标

    const oneLen = one.length
    const twoLen = two.length
    
    // 步骤2：同时遍历两个数组，比较并合并
    // 关键点：当两个数组都还有元素时继续比较
    while (i < oneLen && j < twoLen) {
      // 步骤2.1：比较当前元素并选择较小的
      // 关键点：两两比较，把小的项追加到新数组中，同时移动小的那个数组指针
      // JavaScript特点：简洁的条件判断和赋值
      if (one[i] < two[j]) {
        result[k++] = one[i++]  // 数组1元素较小，移动到结果数组
      } else {
        result[k++] = two[j++]  // 数组2元素较小，移动到结果数组
      }
    }

    // 步骤3：处理剩余元素
    // 关键点：将未处理完的数组元素直接复制到结果数组
    // 处理数组1剩余的项目
    while (i < oneLen) {
      result[k++] = one[i++]  // 直接追加剩余元素
    }

    // 处理数组2剩余的项目
    while (j < twoLen) {
      result[k++] = two[j++]  // 直接追加剩余元素
    }

    return result
  }

  /**
   * 合并两个已排序数组 - 插入法（前向）
   * 
   * 算法思路：
   * 将一个数组的元素逐个插入到另一个数组中
   * 利用JavaScript的splice动态插入特性，在找到合适位置后插入元素
   * 
   * 步骤说明：
   * 1. 遍历第一个数组的每个元素
   * 2. 在第二个数组中从前向后找到插入位置
   * 3. 插入元素并移动后续元素
   * 
   * 关键点：
   * - 利用JavaScript的splice动态插入特性
   * - 需要移动后续元素，时间复杂度较高
   * - 原地操作，空间复杂度低
   * 
   * 时间复杂度：O(n*m) - 最坏情况下每个元素需要遍历整个第二个数组
   * 空间复杂度：O(1) - 在原数组基础上操作
   * 稳定性：稳定 - 保持相等元素的相对位置
   * 
   * @param {number[]} one - 第一个已排序数组
   * @param {number[]} two - 第二个已排序数组
   * @returns {number[]} 合并后的有序数组
   */
  function mergeSorted2(one, two) {
    // 步骤1：初始化变量
    // 关键点：获取数组长度，用于边界检查
    const oneLen = one.length
    let twoLen = two.length
    let j = 0
    
    // 步骤2：遍历第一个数组的每个元素
    // 关键点：将每个元素插入到第二个数组合适位置
    for (let i = 0; i < oneLen; i++) {
      // 步骤2.1：在第二个数组中从前向后找到插入位置
      // 关键点：遍历第二个数组，找到第一个大于等于当前元素的位置
      for (; j < twoLen; j++) {
        // 步骤2.2：比较并插入
        // 关键点：如果当前元素小于数组2的成员项，则插入到数组2中
        if (one[i] < two[j]) {
          // 步骤2.2.1：插入元素
          // 关键点：使用splice在指定位置插入元素
          two.splice(j, 0, one[i])
          twoLen++
          break
        } else {
          // 步骤2.3：处理边界情况
          // 关键点：如果全部比较完成，且数组2里面没有比它还大的，则添加到最后
          if (j === twoLen - 1) {
            two[j + 1] = one[i]
            twoLen++
            break
          }
        }
      }
    }
    return two
  }

  /**
   * 合并两个已排序数组 - 插入法（后向）
   * 
   * 算法思路：
   * 将一个数组的元素逐个插入到另一个数组中
   * 从后往前查找插入位置，减少元素移动次数
   * 
   * 步骤说明：
   * 1. 遍历第一个数组的每个元素
   * 2. 在第二个数组中从后往前找到插入位置
   * 3. 插入元素并移动后续元素
   * 
   * 关键点：
   * - 从后往前查找，减少元素移动次数
   * - 利用JavaScript的splice动态插入特性
   * - 优化点：可以一次性复制剩余元素
   * 
   * 时间复杂度：O(n*m) - 最坏情况下每个元素需要遍历整个第二个数组
   * 空间复杂度：O(1) - 在原数组基础上操作
   * 稳定性：稳定 - 保持相等元素的相对位置
   * 
   * @param {number[]} one - 第一个已排序数组
   * @param {number[]} two - 第二个已排序数组
   * @returns {number[]} 合并后的有序数组
   */
  function mergeSorted3(one, two) {
    // 步骤1：初始化变量
    // 关键点：获取数组长度，用于边界检查
    const oneLen = one.length
    let twoLen = two.length
    
    // 步骤2：遍历第一个数组的每个元素
    // 关键点：将每个元素插入到第二个数组合适位置
    for (let i = 0; i < oneLen; i++) {
      let j = twoLen - 1
      
      // 步骤2.1：在第二个数组中从后往前找到插入位置
      // 关键点：拿数组1的一项作为比较项，逐个跟数组2里的项进行比较
      while (one[i] < two[j]) {
        j--
      }
      
      // 步骤2.2：优化处理
      // 关键点：如果j的位置无变化，说明比较项是数组2里最大的，则可以一次性复制数组1后面全部的项
      if (j === twoLen - 1) {
        const remained = one.slice(i, oneLen)
        two = two.concat(remained)
        break
      }

      // 步骤2.3：插入元素
      // 关键点：把比较项插入到第二个数组里比它小的位置后面
      two.splice(j + 1, 0, one[i])
      twoLen++
    }
    return two
  }

  /**
   * 合并两个已排序数组 - 双指针法（push）
   * 
   * 算法思路：
   * 使用两个指针分别指向两个数组的起始位置，同时遍历比较
   * 使用push方法添加元素到结果数组，代码更简洁
   * 
   * 步骤说明：
   * 1. 初始化结果数组和指针
   * 2. 同时遍历两个数组，比较并合并
   * 3. 处理剩余元素
   * 
   * 关键点：
   * - 使用push方法替代索引赋值，代码更简洁
   * - JavaScript特点：充分利用语言特性
   * - 保持算法的稳定性
   * 
   * 时间复杂度：O(n+m) - 每个元素只被访问一次
   * 空间复杂度：O(n+m) - 需要额外空间存储结果
   * 稳定性：稳定 - 保持相等元素的相对位置
   * 
   * @param {number[]} one - 第一个已排序数组
   * @param {number[]} two - 第二个已排序数组
   * @returns {number[]} 合并后的有序数组
   */
  function mergeSorted4(one, two) {
    // 步骤1：初始化结果数组和指针
    // 关键点：使用空数组存储结果，指针从0开始
    const result = []
    let i = 0  // 数组1下标
    let j = 0  // 数组2下标

    const oneLen = one.length
    const twoLen = two.length
    
    // 步骤2：同时遍历两个数组，比较并合并
    // 关键点：当两个数组都还有元素时继续比较
    while (i < oneLen && j < twoLen) {
      // 步骤2.1：比较当前元素并选择较小的
      // 关键点：使用push方法添加元素，代码更简洁
      if (one[i] < two[j]) {
        result.push(one[i])  // 数组1元素较小，添加到结果数组
        i++
      } else {
        result.push(two[j])  // 数组2元素较小，添加到结果数组
        j++
      }
    }

    // 步骤3：处理剩余元素
    // 关键点：将未处理完的数组元素直接添加到结果数组
    // 处理数组1剩余的项目
    while (i < oneLen) {
      result.push(one[i])  // 直接追加剩余元素
      i++
    }

    // 处理数组2剩余的项目
    while (j < twoLen) {
      result.push(two[j])  // 直接追加剩余元素
      j++
    }

    return result
  }

  /**
   * 合并两个已排序数组 - 合并排序法
   * 
   * 算法思路：
   * 先将两个数组合并成一个数组，然后使用插入排序进行排序
   * 利用第一个数组已排序的特性，从第二个数组开始位置进行排序
   * 
   * 步骤说明：
   * 1. 合并两个数组
   * 2. 从第二个数组开始位置进行插入排序
   * 3. 逐个插入元素到已排序部分
   * 
   * 关键点：
   * - 先合并后排序，实现简单
   * - 利用已排序部分的特性
   * - 使用插入排序，适合小数据量
   * 
   * 时间复杂度：O((n+m)²) - 插入排序的时间复杂度
   * 空间复杂度：O(n+m) - 需要额外空间存储结果
   * 稳定性：稳定 - 插入排序保持相等元素的相对位置
   * 
   * @param {number[]} one - 第一个已排序数组
   * @param {number[]} two - 第二个已排序数组
   * @returns {number[]} 合并后的有序数组
   */
  function mergeSorted5(one, two) {
    // 步骤1：初始化变量
    // 关键点：获取数组长度，用于边界检查
    const oneLen = one.length
    const twoLen = two.length

    // 步骤2：合并数组
    // 关键点：使用concat方法合并两个数组
    const result = one.concat(two)
    
    // 步骤3：插入排序
    // 关键点：从第二个数组开始位置进行排序，利用第一个数组已排序的特性
    for (let i = oneLen; i < oneLen + twoLen; i++) {
      // 步骤3.1：逐个插入元素到已排序部分
      // 关键点：自后往前把当前项与前一项进行比较
      let j = i
      const current = result[i]
      
      // 步骤3.2：比较并移动元素
      // 关键点：如果当前项小于已排序的项，则逐个右移1位
      while (j-- > 0 && current < result[j]) {
        result[j + 1] = result[j]
      }
      
      // 步骤3.3：插入元素
      // 关键点：空出位置插入比较项
      result[j + 1] = current
    }

    return result
  }

  // ==================== 主程序：算法演示和性能测试 ====================

  // 测试数据：
  const arr1 = [-3, 7, 9, 10, 11, 15, 16]
  const arr2 = [-1, 5, 6, 9, 12]

  /**
   * 性能测试辅助函数
   * @param {Function} sortFunc - 排序函数
   * @param {number[]} arr1 - 第一个测试数组
   * @param {number[]} arr2 - 第二个测试数组
   * @param {string} name - 测试名称
   */
  function performanceTest(sortFunc, arr1, arr2, name) {
    console.log(`\n=== ${name} ===`)
    console.log('原始数组1:', arr1)
    console.log('原始数组2:', arr2)
    
    // 开始计时
    console.time(`${name} 排序耗时`)
    const result = sortFunc(arr1.slice(0), arr2.slice(0))
    console.timeEnd(`${name} 排序耗时`)
    
    console.log('合并结果:', result)
  }

  // 测试1：双指针法
  performanceTest(mergeSorted1, arr1, arr2, 'mergeSorted1 双指针法')

  // 测试2：插入法（前向）
  performanceTest(mergeSorted2, arr1, arr2, 'mergeSorted2 插入法（前向）')

  // 测试3：插入法（后向）
  performanceTest(mergeSorted3, arr1, arr2, 'mergeSorted3 插入法（后向）')

  // 测试4：双指针法（push）
  performanceTest(mergeSorted4, arr1, arr2, 'mergeSorted4 双指针法（push）')

  // 测试5：合并排序法
  performanceTest(mergeSorted5, arr1, arr2, 'mergeSorted5 合并排序法')

  console.log('\n=== 算法对比总结 ===')
  console.log('1. 双指针法：时间复杂度O(n+m)，空间复杂度O(n+m)，最优选择')
  console.log('2. 插入法（前向）：时间复杂度O(n*m)，空间复杂度O(1)，适合小数据量')
  console.log('3. 插入法（后向）：时间复杂度O(n*m)，空间复杂度O(1)，减少移动次数')
  console.log('4. 双指针法（push）：时间复杂度O(n+m)，空间复杂度O(n+m)，代码简洁')
  console.log('5. 合并排序法：时间复杂度O((n+m)²)，空间复杂度O(n+m)，逻辑简单')

})();

/*
jarry@Mac mergesort % node merge_sorted_array.js 

=== mergeSorted1 双指针法 ===
原始数组1: [
  -3,  7,  9, 10,
  11, 15, 16
]
原始数组2: [ -1, 5, 6, 9, 12 ]
mergeSorted1 双指针法 排序耗时: 0.024ms
合并结果: [
  -3, -1,  5,  6,  7,
   9,  9, 10, 11, 12,
  15, 16
]

=== mergeSorted2 插入法（前向） ===
原始数组1: [
  -3,  7,  9, 10,
  11, 15, 16
]
原始数组2: [ -1, 5, 6, 9, 12 ]
mergeSorted2 插入法（前向） 排序耗时: 0.025ms
合并结果: [
  -3, -1,  5,  6,  7,
   9,  9, 10, 11, 12,
  15, 16
]

=== mergeSorted3 插入法（后向） ===
原始数组1: [
  -3,  7,  9, 10,
  11, 15, 16
]
原始数组2: [ -1, 5, 6, 9, 12 ]
mergeSorted3 插入法（后向） 排序耗时: 0.021ms
合并结果: [
  -3, -1,  5,  6,  7,
   9,  9, 10, 11, 12,
  15, 16
]

=== mergeSorted4 双指针法（push） ===
原始数组1: [
  -3,  7,  9, 10,
  11, 15, 16
]
原始数组2: [ -1, 5, 6, 9, 12 ]
mergeSorted4 双指针法（push） 排序耗时: 0.016ms
合并结果: [
  -3, -1,  5,  6,  7,
   9,  9, 10, 11, 12,
  15, 16
]

=== mergeSorted5 合并排序法 ===
原始数组1: [
  -3,  7,  9, 10,
  11, 15, 16
]
原始数组2: [ -1, 5, 6, 9, 12 ]
mergeSorted5 合并排序法 排序耗时: 0.019ms
合并结果: [
  -3, -1,  5,  6,  7,
   9,  9, 10, 11, 12,
  15, 16
]

=== 算法对比总结 ===
1. 双指针法：时间复杂度O(n+m)，空间复杂度O(n+m)，最优选择
2. 插入法（前向）：时间复杂度O(n*m)，空间复杂度O(1)，适合小数据量
3. 插入法（后向）：时间复杂度O(n*m)，空间复杂度O(1)，减少移动次数
4. 双指针法（push）：时间复杂度O(n+m)，空间复杂度O(n+m)，代码简洁
5. 合并排序法：时间复杂度O((n+m)²)，空间复杂度O(n+m)，逻辑简单
 */