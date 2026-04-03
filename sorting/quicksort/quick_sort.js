/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
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
;
(function () {

  // ==================== 辅助函数 ====================

  /**
   * 打印数组内容的辅助函数
   * 
   * 功能：以格式化的方式输出数组内容
   * 
   * @param {number[]} arr - 要打印的数字数组
   * @param {string} label - 数组的标签说明，用于标识输出
   * @returns {void} 无返回值
   */
  function printArray(arr, label) {
    console.log(`${label}: [${arr.join(', ')}]`);
  }

  /**
   * 性能测试函数
   * 
   * 功能：测试排序算法的性能，包括执行时间和正确性验证
   * 
   * @param {Function} sortFunc - 排序函数，接受数组并返回排序后的数组
   * @param {number[]} arr - 测试用的原始数组
   * @param {string} name - 测试名称，用于输出标识和性能统计
   * @returns {void} 无返回值
   */
  function performanceTest(sortFunc, arr, name) {
    // 创建数组副本，避免修改原数组
    const testArr = [...arr];
    printArray(testArr, `${name}原始数组`);
    
    // 开始计时并执行排序
    const start = Date.now();
    const sortedArr = sortFunc(testArr);
    const duration = Date.now() - start;
    
    // 输出结果
    console.log(`${name}: ${duration}ms`);
    printArray(sortedArr, `${name}排序结果`);
    console.log(); // 空行分隔
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
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数字数组
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
  function quickSort1(arr) {
    // 第一步：递归终止条件
    // 关键点：数组长度<=1时已经有序，直接返回
    if (arr.length <= 1) {
      return arr
    }

    // 第二步：选择基准并分区
    console.log('split array:', arr)
    const left = []
    const right = []
    // 关键点：设置中间数作为基准，避免最坏情况
    var midIndex = Math.floor(arr.length / 2)
    var pivot = arr[midIndex]

    // 第三步：遍历数组，按基准值分区
    for (var i = 0, l = arr.length; i < l; i++) {
      // 关键点：跳过基准元素本身，避免重复处理
      if (midIndex === i) {
        continue
      }
      // 关键点：小于基准的放左边，大于等于的放右边
      if (arr[i] < pivot) {
        left.push(arr[i])
      } else {
        right.push(arr[i])
      }
    }

    // 第四步：递归排序并合并
    // 关键点：先递归左数组，再添加基准，最后递归右数组
    arr = quickSort1(left).concat(pivot, quickSort1(right))
    console.log('sorted array:', arr)
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
   * @param {number[]} arr - 待排序的数字数组
   * @param {number} left - 起始索引
   * @param {number} right - 结束索引
   * @returns {number} 基准元素的最终位置
   */
  function partition(arr, left, right) {
    // 第一步：选择基准（这里取右侧）
    // 基准值可以是left与right之间的任意值，再将基准值移动至最左或最右即可。
    var pivotIndex = right
    var pivot = arr[pivotIndex]
    var partitionIndex = left - 1

    // 第二步：遍历数组进行分区
    for (var i = left; i < right; i++) {
      // 关键点：将小于基准的元素交换到左侧
      if (arr[i] < pivot) {
        partitionIndex++
        if (partitionIndex !== i) {
          [arr[partitionIndex], arr[i]] = [arr[i], arr[partitionIndex]]
        }
      }
    }

    // 第三步：将基准放到正确位置
    partitionIndex++
    [arr[partitionIndex], arr[pivotIndex]] = [arr[pivotIndex], arr[partitionIndex]]
    console.log('partitioned arr=', arr, 'partitionIndex:', partitionIndex,
      'left=', arr.slice(left, partitionIndex), 'arr[partitionIndex]=', arr[partitionIndex],
      'right=', arr.slice(partitionIndex, right + 1), arr)
    return partitionIndex
  }

  /**
   * 快速排序2 - 标准递归版本
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
   * @param {number[]} arr - 待排序的数字数组
   * @param {number} left - 起始索引
   * @param {number} right - 结束索引
   * @returns {number[]} 排序后的数组
   */
  function quickSort2(arr, left, right) {
    // 第一步：初始化参数
    left = left !== undefined ? left : 0
    right = right !== undefined ? right : arr.length - 1
    
    // 第二步：递归终止条件检查
    // 关键点：left < right时还需要排序，否则已经有序
    if (left < right) {
      // 第三步：分区并获取基准位置
      // 关键点：使用partition函数将数组分为两部分
      var pivot = partition(arr, left, right)

      // 第四步：递归排序左半部分
      // 关键点：排序基准左边的元素
      quickSort2(arr, left, pivot - 1)

      // 第五步：递归排序右半部分
      // 关键点：排序基准右边的元素
      quickSort2(arr, pivot + 1, right)
    }
    return arr
  }

  /**
   * 快速排序3 - 双向扫描递归版本
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
   * @param {number[]} arr - 待排序的数字数组
   * @param {number} left - 起始索引
   * @param {number} right - 结束索引
   * @returns {number[]} 排序后的数组
   */
  function quickSort3(arr, left, right) {
    // 第一步：初始化指针和基准
    var i = left = left !== undefined ? left : 0
    var j = right = right !== undefined ? right : arr.length - 1
    // 关键点：确定中间位置，基于中间位置不停左右交换
    var midIndex = Math.floor((i + j) / 2)
    var pivot = arr[midIndex]

    // 第二步：双向扫描分区
    // 关键点：当左侧小于等于右侧则表示还有值没有对比，需要继续
    while (i <= j) {
      // 步骤2.1：左指针扫描，找到大于基准的元素
      // 关键点：当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
      while (arr[i] < pivot) {
        console.log('arr[i] < pivot:', ' i=' + i + ' j=' + j + ' pivot=' + pivot)
        i++
      }
      // 步骤2.2：右指针扫描，找到小于基准的元素
      // 关键点：当前右侧大于基准时左移，直到找出比基准值小的位置来
      while (arr[j] > pivot) {
        console.log('arr[j] > pivot:', ' i=' + i + ' j=' + j + ' pivot=' + pivot)
        j--
      }

      console.log('  left=' + left + ' right=' + right + ' i=' + i + ' j=' + j + ' midIndex=' + midIndex + ' pivot=' + pivot + ' arr[]=' + arr)

      // 步骤2.3：交换元素
      // 关键点：当左侧位置小于等于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
      if (i <= j) {
        [arr[i], arr[j]] = [arr[j], arr[i]]
        // 关键点：缩小搜查范围，直到左侧都小于基数，右侧都大于基数
        i++
        j--
      }
    }

    // 第三步：递归处理左右子数组
    // 步骤3.1：递归处理左子数组
    // 关键点：左侧小于基数位置，不断递归左边部分
    if (left < j) {
      console.log('left < j:recursion:  left=' + left + ' right=' + right + ' i=' + i + ' j=' + j + 'arr[]' + arr)
      quickSort3(arr, left, j)
    }
    // 步骤3.2：递归处理右子数组
    // 关键点：基数位置小于右侧，不断递归右侧部分
    if (i < right) {
      console.log('i < right:recursion:  left=' + left + ' right=' + right + ' i=' + i + ' j=' + j + 'arr[]' + arr)
      quickSort3(arr, i, right)
    }

    return arr
  }

  /**
   * 快速排序4 - 非递归版本
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
   * @param {number[]} arr - 待排序的数字数组
   * @param {number} left - 起始索引
   * @param {number} right - 结束索引
   * @returns {number[]} 排序后的数组
   */
  function quickSort4(arr, left, right) {
    // 第一步：初始化参数
    // 关键点：设置默认值，确保函数可以单独调用
    left = left !== undefined ? left : 0
    right = right !== undefined ? right : arr.length - 1

    // 第二步：创建栈用于存储待处理的子数组范围
    // 关键点：使用数组模拟栈结构，避免递归调用
    const stack = []
    
    // 第三步：初始入栈
    // 关键点：将整个数组的左右边界入栈，作为初始处理范围
    stack.push(left)
    stack.push(right)

    // 第四步：循环处理栈中的范围
    // 关键点：栈不为空时继续处理，模拟递归调用过程
    while (stack.length) {
      // 步骤4.1：从栈中取出待处理的范围
      // 关键点：后进先出，先取出right，再取出left
      right = stack.pop()
      left = stack.pop()

      // 步骤4.2：获取基准位置
      // 关键点：使用Lomuto分区方案，将数组分为两部分
      const pi = partitionLomuto(arr, left, right)

      // 步骤4.3：左子数组入栈
      // 关键点：将分区后的左子范围重新入栈，继续处理
      if (left < pi - 1) {
        // 关键点：左子数组有数据，入栈待处理
        stack.push(left)
        stack.push(pi - 1)
      }

      // 步骤4.4：右子数组入栈
      // 关键点：将分区后的右子范围重新入栈，继续处理
      if (pi + 1 < right) {
        // 关键点：右子数组有数据，入栈待处理
        stack.push(pi + 1)
        stack.push(right)
      }
    }

    // 第五步：返回排序后的数组
    // 关键点：所有范围处理完成，数组已排序
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
   * @param {number[]} arr - 待排序的数字数组
   * @param {number} low - 起始索引
   * @param {number} high - 结束索引
   * @returns {number} 基准元素的最终位置
   */
  function partitionLomuto(arr, low, high) {
    // 第一步：初始化基准和指针
    const pivot = arr[high]; // 最后一个元素作为基准
    let i = low - 1; // 小于基准的元素的边界

    // 第二步：遍历数组进行分区
    for (let j = low; j < high; j++) {
      // 关键点：将小于基准的元素交换到左侧
      if (arr[j] < pivot) {
        i++;
        [arr[i], arr[j]] = [arr[j], arr[i]];
      }
    }

    // 第三步：将基准放到正确位置
    [arr[i + 1], arr[high]] = [arr[high], arr[i + 1]];
    return i + 1;
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
   * @param {number[]} arr - 待排序的数字数组
   * @param {number} left - 起始索引
   * @param {number} right - 结束索引
   * @returns {number[]} 排序后的数组
   */
  function quickSort5(arr, left, right) {
    // 第一步：递归终止条件检查
    if (left >= right) {
      return arr;
    }

    // 第二步：获取基准位置
    const pi = partitionLomuto(arr, left, right);

    // 第三步：递归排序左右子数组
    quickSort5(arr, left, pi - 1);
    quickSort5(arr, pi + 1, right);

    return arr;
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
   * @param {number[]} arr - 待排序的数字数组
   * @param {number} left - 起始索引
   * @param {number} right - 结束索引
   * @returns {number[]} 排序后的数组
   */
  function quickSort6(arr, left, right) {
    // 第一步：递归终止条件检查
    if (left >= right) {
      return arr;
    }

    // 第二步：初始化指针和基准
    let i = left;
    let j = right;
    const pivot = arr[left]; // 第一个元素作为基准

    // 第三步：双向扫描分区
    while (i <= j) {
      // 左指针：找到大于基准的元素
      while (arr[i] < pivot) {
        i++;
      }

      // 右指针：找到小于基准的元素
      while (arr[j] > pivot) {
        j--;
      }

      // 交换元素
      if (i <= j) {
        [arr[i], arr[j]] = [arr[j], arr[i]];
        i++;
        j--;
      }
    }

    // 第四步：递归处理左右子数组
    quickSort6(arr, left, j);
    quickSort6(arr, i, right);

    return arr;
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
   * @param {number[]} arr - 待排序的数字数组
   * @param {number} left - 起始索引
   * @param {number} right - 结束索引
   * @returns {number[]} 排序后的数组
   */
  function quickSort7(arr, left, right) {
    // 第一步：递归终止条件检查
    if (left >= right) {
      return arr;
    }

    // 第二步：初始化基准和三路指针
    const pivot = arr[left]; // 第一个元素作为基准
    let lt = left; // 小于基准的右边界
    let i = left + 1; // 当前遍历指针
    let gt = right; // 大于基准的左边界

    // 第三步：三路分区
    while (i <= gt) {
      if (arr[i] < pivot) {
        // 步骤3.1：小于基准，交换到左边
        [arr[lt], arr[i]] = [arr[i], arr[lt]];
        lt++;
        i++;
      } else if (arr[i] > pivot) {
        // 步骤3.2：大于基准，交换到右边
        [arr[i], arr[gt]] = [arr[gt], arr[i]];
        gt--;
      } else {
        // 步骤3.3：等于基准，直接跳过
        i++;
      }
    }

    // 第四步：递归处理左右子数组
    quickSort7(arr, left, lt - 1);
    quickSort7(arr, gt + 1, right);
    // 等于基准的部分已经就位，无需处理

    return arr;
  }

  // ==================== 算法测试和性能对比 ====================

  // 测试数据：
  const testData = [7, 11, 9, 10, 12, 13, 8];

  // 测试1：递归新建数组版本
  performanceTest(quickSort1, testData, '递归新建数组版本');

  // 测试2：标准递归版本
  performanceTest(function (arr) {
    return quickSort2(arr, 0, arr.length - 1)
  }, testData, '标准递归版本');

  // 测试3：双向扫描递归版本
  performanceTest(function (arr) {
    return quickSort3(arr, 0, arr.length - 1)
  }, testData, '双向扫描递归版本');

  // 测试4：非递归版本
  performanceTest(function (arr) {
    return quickSort4(arr, 0, arr.length - 1)
  }, testData, '非递归版本');

  // 测试5：Lomuto分区递归版本
  performanceTest(function (arr) {
    return quickSort5(arr, 0, arr.length - 1)
  }, testData, 'Lomuto分区递归版本');

  // 测试6：Hoare分区递归版本
  performanceTest(function (arr) {
    return quickSort6(arr, 0, arr.length - 1)
  }, testData, 'Hoare分区递归版本');

  // 测试7：三路分区递归版本
  performanceTest(function (arr) {
    return quickSort7(arr, 0, arr.length - 1)
  }, testData, '三路分区递归版本');

  console.log('=== 算法对比总结 ===');
  console.log('1. 递归新建数组版本：中间基准，新建数组，稳定排序');
  console.log('2. 标准递归版本：右侧基准，原地交换，Lomuto分区');
  console.log('3. 双向扫描递归版本：中间基准，双向扫描，原地交换');
  console.log('4. 非递归版本：栈模拟，避免递归，双向扫描');
  console.log('5. Lomuto分区递归版本：最后基准，单向扫描');
  console.log('6. Hoare分区递归版本：第一个基准，双向扫描');
  console.log('7. 三路分区递归版本：第一个基准，三路分区');
})();

/*打印结果
jarry@Mac quicksort % node quick_sort.js
递归新建数组版本原始数组: [7, 11, 9, 10, 12, 13, 8]
split array: [
   7, 11, 9, 10,
  12, 13, 8
]
split array: [ 7, 9, 8 ]
split array: [ 7, 8 ]
sorted array: [ 7, 8 ]
sorted array: [ 7, 8, 9 ]
split array: [ 11, 12, 13 ]
sorted array: [ 11, 12, 13 ]
sorted array: [
   7,  8,  9, 10,
  11, 12, 13
]
递归新建数组版本: 2ms
递归新建数组版本排序结果: [7, 8, 9, 10, 11, 12, 13]

标准递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
partitioned arr= [
   7,  8,  9, 10,
  12, 13, 11
] partitionIndex: 1 left= [ 7 ] arr[partitionIndex]= 8 right= [ 8, 9, 10, 12, 13, 11 ] [
   7,  8,  9, 10,
  12, 13, 11
]
partitioned arr= [
   7,  8,  9, 10,
  11, 13, 12
] partitionIndex: 4 left= [ 9, 10 ] arr[partitionIndex]= 11 right= [ 11, 13, 12 ] [
   7,  8,  9, 10,
  11, 13, 12
]
partitioned arr= [
   7,  8,  9, 10,
  11, 13, 12
] partitionIndex: 3 left= [ 9 ] arr[partitionIndex]= 10 right= [ 10 ] [
   7,  8,  9, 10,
  11, 13, 12
]
partitioned arr= [
   7,  8,  9, 10,
  11, 12, 13
] partitionIndex: 5 left= [] arr[partitionIndex]= 12 right= [ 12, 13 ] [
   7,  8,  9, 10,
  11, 12, 13
]
标准递归版本: 2ms
标准递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

双向扫描递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
arr[i] < pivot:  i=0 j=6 pivot=10
  left=0 right=6 i=1 j=6 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
arr[i] < pivot:  i=2 j=5 pivot=10
arr[j] > pivot:  i=3 j=5 pivot=10
arr[j] > pivot:  i=3 j=4 pivot=10
  left=0 right=6 i=3 j=3 midIndex=3 pivot=10 arr[]=7,8,9,10,12,13,11
left < j:recursion:  left=0 right=6 i=4 j=2arr[]7,8,9,10,12,13,11
arr[i] < pivot:  i=0 j=2 pivot=8
arr[j] > pivot:  i=1 j=2 pivot=8
  left=0 right=2 i=1 j=1 midIndex=1 pivot=8 arr[]=7,8,9,10,12,13,11
i < right:recursion:  left=0 right=6 i=4 j=2arr[]7,8,9,10,12,13,11
arr[i] < pivot:  i=4 j=6 pivot=13
  left=4 right=6 i=5 j=6 midIndex=5 pivot=13 arr[]=7,8,9,10,12,13,11
left < j:recursion:  left=4 right=6 i=6 j=5arr[]7,8,9,10,12,11,13
  left=4 right=5 i=4 j=5 midIndex=4 pivot=12 arr[]=7,8,9,10,12,11,13
双向扫描递归版本: 0ms
双向扫描递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

非递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
非递归版本: 0ms
非递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

Lomuto分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
Lomuto分区递归版本: 0ms
Lomuto分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

Hoare分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
Hoare分区递归版本: 0ms
Hoare分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

三路分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
三路分区递归版本: 0ms
三路分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归新建数组版本：中间基准，新建数组，稳定排序
2. 标准递归版本：右侧基准，原地交换，Lomuto分区
3. 双向扫描递归版本：中间基准，双向扫描，原地交换
4. 非递归版本：栈模拟，避免递归，双向扫描
5. Lomuto分区递归版本：最后基准，单向扫描
6. Hoare分区递归版本：第一个基准，双向扫描
7. 三路分区递归版本：第一个基准，三路分区
*/