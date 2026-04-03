/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 桶排序算法实现
 * 提供六种不同的实现方式，适合不同场景和性能需求
 */
;
(function () {

  /**
   * 桶排序支持负数版本 - 负数放在第1个桶里排序
   * 
   * 算法原理：
   * 1. 计算数组最大值和最小值（取绝对值）
   * 2. 根据最大最小值计算桶的数量和大小
   * 3. 将元素分配到对应桶中，负数统一放在第1个桶
   * 4. 在每个桶内进行插入排序
   * 5. 合并所有桶的元素
   * 
   * 生活类比：就像整理图书馆的书籍，
   * 先按类别分到不同的书架，再在每个书架内按字母顺序排列
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function bucketSort1(arr) {
    console.log('bucketSort1 with negative numbers:')
    
    // 第一步：计算数组最大值和最小值（取绝对值）
    let max = Math.max(...arr)
    let min = Math.min.apply(this, arr)
    max = Math.abs(max)
    min = Math.abs(min)
    if (max < min) {
      const tmp = max
      max = min
      min = tmp
    }
    
    // 第二步：根据最大最小值计算桶的数量和大小
    const bucketNumber = Math.abs(Math.floor((max - min) / min)) + 1
    const bucketSize = Math.abs(Math.floor((max - min) / bucketNumber)) + 1
    const buckets = []
    let idx
    
    // 第三步：将元素分配到对应桶中，负数统一放在第1个桶
    arr.forEach((item, i) => {
      // 关键点：当前项除以桶数取整，决定应该放在某个桶内
      idx = Math.floor((item - min) / bucketSize)
      // 负数处理：负数全放在第一个桶里，按照插入方式排序
      idx = idx > 0 ? idx : 0
      
      // 第四步：桶内插入排序
      if (!buckets[idx]) {
        buckets[idx] = []
        buckets[idx].push(item)
      } else {
        let len = buckets[idx].length
        // 插入排序：自后往前遍历，找到合适的插入位置
        while (len--) {
          // 比较逻辑：如果数字大于数组中的项则插入其后
          if (item > buckets[idx][len]) {
            // JS特点：使用splice插入元素
            buckets[idx].splice(len + 1, 0, item)
            break
          } else if (len === 0) {
            // 边界处理：如果数字最小则插入到最前
            buckets[idx].unshift(item)
          }
        }
      }
    })

    // 第五步：合并所有桶的元素
    let output = []
    buckets.forEach((bucketItem) => {
      if (bucketItem) {
        output = output.concat(bucketItem)
      }
    })
    console.log(output)
    return output
  }

  /**
   * 桶排序标准版 - 不支持负数
   * 
   * 算法思路：
   * 1. 计算数组的最大值和最小值
   * 2. 处理最小值小于等于0的情况（设为1），避免负数问题
   * 3. 动态计算桶的数量和大小，基于数组长度优化
   * 4. 将元素分配到对应桶中
   * 5. 桶内使用插入排序
   * 6. 合并所有桶的元素
   * 
   * 优化效果：
   * - 桶分配更精确，性能较好
   * - 动态桶数量，适应不同数据规模
   * - 不支持负数，避免复杂的边界处理
   * 
   * @param {number[]} arr - 待排序的数字数组（仅支持正数）
   * @returns {number[]} 排序后的数组
   */
  function bucketSort2(arr) {
    console.log('bucketSort2 positive numbers only:')
    
    // 第一步：计算数组的最大值和最小值
    const max = Math.max(...arr)
    let min = Math.min(...arr)

    // 第二步：处理最小值小于等于0的情况，避免负数问题
    if (min < max && min <= 0) min = 1

    // 第三步：动态计算桶的数量和大小，基于数组长度优化
    const size = Math.floor(arr.length / 2)
    let bucketNumber = Math.abs(Math.floor((max - min) / min)) + 1
    bucketNumber = bucketNumber < size ? bucketNumber : size
    const bucketSize = Math.abs(Math.floor((max - min) / bucketNumber)) + 1
    const buckets = []
    let idx

    // 第四步：将元素分配到对应桶中
    arr.forEach((item) => {
      // 桶索引：计算元素应该放入的桶索引
      idx = Math.floor((item - min) / bucketSize)
      // 注释掉的负数支持代码（本版本不支持负数）
      // idx = idx < 0 ? 0 : idx

      // 第五步：桶内插入排序
      if (!buckets[idx]) {
        buckets[idx] = []
        buckets[idx].push(item)
      } else {
        let len = buckets[idx].length
        // 插入排序：从后往前遍历，找到合适的插入位置
        while (len--) {
          // 比较逻辑：如果数字大于数组中的项则插入其后
          if (item > buckets[idx][len]) {
            // JS特点：使用splice插入元素
            buckets[idx].splice(len + 1, 0, item)
            break
          } else if (len === 0) {
            // 边界处理：如果数字最小则插入到最前
            buckets[idx].unshift(item)
          }
        }
      }
    })

    // 第六步：合并所有桶的元素
    let output = []
    buckets.forEach((bucketItem) => {
      if (bucketItem) {
        output = output.concat(bucketItem)
      }
    })
    console.log(output)
    return output
  }

  /**
   * 桶排序挪动排序版 - 负数放入第一个桶
   * 
   * 算法思路：
   * 1. 手动遍历数组获取最大最小值
   * 2. 处理最大最小值小于等于0的情况
   * 3. 计算桶的数量和大小
   * 4. 将元素分配到桶中，负数放入第一个桶
   * 5. 桶内使用挪动排序（类似插入排序）
   * 6. 合并所有桶的元素
   * 
   * 优化效果：
   * - 使用挪动排序而非直接修改数组
   * - 手动计算最大最小值，更可控
   * - 支持负数，负数统一处理
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function bucketSort3(arr) {
    console.log('bucketSort3 with move sorting:')
    
    // 第一步：手动遍历数组获取最大最小值
    let max = arr[0]
    let min = arr[0]

    // 手动遍历：获取数组最大最小值，避免使用Math.max/min
    for (let i = 0, len = arr.length; i < len; i++) {
      // 最大值：如果当前元素大于max，则更新max
      if (arr[i] > max) {
        max = arr[i]
      }
      // 最小值：如果当前元素小于min，则更新min
      if (arr[i] < min) {
        min = arr[i]
      }
    }

    // 第二步：处理最大最小值小于等于0的情况
    if (max <= 0) max = 1
    if (min <= 0) min = 1

    // 第三步：根据最大最小值计算桶的数量和大小
    const bucketNumber = Math.abs(Math.floor((max - min) / min)) + 1
    const bucketSize = Math.abs(Math.floor((max - min) / bucketNumber)) + 1
    const buckets = []
    let idx
    let item

    // 第四步：元素分配，遍历数组，将元素分配到对应桶中
    for (let i = 0, len = arr.length; i < len; i++) {
      item = arr[i]
      // 桶索引：计算元素应该放入的桶索引
      idx = Math.floor((item - min) / bucketSize)

      // 负数处理：负数全部放入第一个桶
      if (idx < 0) {
        idx = 0
      }

      // 每个桶都是一个数组，若不存在则创建
      if (!Array.isArray(buckets[idx])) {
        buckets[idx] = []
        buckets[idx].push(item)
      } else {
        // 第五步：挪动排序，使用挪动排序插入元素，避免splice开销
        let len = buckets[idx].length
        buckets[idx].length = len + 1
        while (len--) {
          // 比较逻辑：如果插入的数字小于当前项，则将当前项逐个往后挪
          if (item < buckets[idx][len]) {
            // 挪动操作：将当前项向后挪动一位
            buckets[idx][len + 1] = buckets[idx][len]
            // 边界处理：如果挪到最前面，直接插入
            if (len === 0) {
              buckets[idx][0] = item
            }
          } else {
            // 插入操作：如果大于等于当前项，则插入到当前项后面，循环中止
            buckets[idx][len + 1] = item
            break
          }
        }
      }
    }

    // 第六步：合并结果，按照桶的顺序合并所有元素
    const output = []
    for (let i = 0, len = buckets.length; i < len; i++) {
      const bucketItem = buckets[i]
      if (bucketItem) {
        let j = 0
        const bucketItemLen = bucketItem.length
        // 元素复制：将桶内元素逐个复制到结果数组
        while (j < bucketItemLen) {
          output.push(bucketItem[j])
          j++
        }
      }
    }
    console.log(output)
    return output
  }

  /**
   * 桶排序负数单独处理版 - 负数单独排序
   * 
   * 算法思路：
   * 1. 手动遍历获取最大最小值
   * 2. 处理最小值小于等于0的情况
   * 3. 计算桶的数量和大小
   * 4. 将正数分配到桶中，负数单独收集
   * 5. 负数单独排序后先输出
   * 6. 输出正数桶的元素
   * 
   * 优化效果：
   * - 负数和正数分别优化，排序更精确
   * - 负数使用Array.sort排序，效率更高
   * - 最终结果先输出负数再输出正数
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function bucketSort4(arr) {
    console.log('bucketSort4 separate negative sorting:')
    
    // 第一步：手动遍历获取最大最小值
    let max = arr[0]
    let min = arr[0]

    // 手动遍历：获取数组最大最小值，避免使用Math.max/min
    for (let i = 0, len = arr.length; i < len; i++) {
      // 最大值：如果当前元素大于max，则更新max
      if (arr[i] > max) {
        max = arr[i]
      }
      // 最小值：如果当前元素小于min，则更新min
      if (arr[i] < min) {
        min = arr[i]
      }
    }

    // 第二步：处理最小值小于等于0的情况
    if (min < max && min <= 0) min = 1

    // 第三步：根据最大最小值计算桶的数量和大小
    const bucketNumber = Math.abs(Math.floor((max - min) / min)) + 1
    const bucketSize = Math.abs(Math.floor((max - min) / bucketNumber)) + 1
    const buckets = []
    let idx
    let item

    // 第四步：创建单独的负数数组
    const negativeList = []

    // 第五步：元素分配，遍历数组，将元素分配到对应桶中
    for (let i = 0, len = arr.length; i < len; i++) {
      item = arr[i]
      // 分类处理：负数单独收集，正数放入桶中
      if (item < 0) {
        // 负数收集：将负数添加到负数列表
        negativeList.push(item)
      } else {
        // 桶索引：计算正数应该放入的桶索引
        idx = Math.floor((item - min) / bucketSize)

        // 桶初始化：如果桶不存在则创建
        if (!Array.isArray(buckets[idx])) {
          buckets[idx] = []
        }
        // 正数分配：将正数放入对应桶中
        buckets[idx].push(item)
      }
    }

    // 第六步：负数排序，使用Array.sort对负数进行排序
    negativeList.sort((a, b) => a - b)

    // 第七步：结果合并，先输出负数，再输出正数
    const output = []

    // 负数输出：将排序后的负数逐个添加到结果数组
    for (let i = 0, len = negativeList.length; i < len; i++) {
      output.push(negativeList[i])
    }

    // 正数输出：按照桶的顺序输出正数
    for (let i = 0, len = buckets.length; i < len; i++) {
      const bucketItem = buckets[i]
      if (bucketItem) {
        let j = 0
        const bucketItemLen = bucketItem.length
        // 元素复制：将桶内元素逐个复制到结果数组
        while (j < bucketItemLen) {
          output.push(bucketItem[j])
          j++
        }
      }
    }
    console.log(output)
    return output
  }

  /**
   * 桶排序实时冒泡版 - 负数放在第一个桶内排序
   * 
   * 算法思路：
   * 1. 计算数组的最大值和最小值
   * 2. 根据数组长度计算桶的大小
   * 3. 将元素分配到桶中，负数放在第1个桶
   * 4. 每次插入后立即对桶内进行冒泡排序
   * 5. 合并所有桶的元素
   * 
   * 优化效果：
   * - 每次插入后立即排序桶内元素
   * - 使用冒泡排序保持桶内有序
   * - 插入即排序，无需后续排序步骤
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function bucketSort5(arr) {
    console.log('bucketSort5 real-time bubble sorting:')
    
    // 第一步：定义交换函数
    function swap(list, i, j) {
      const temp = list[i]
      list[i] = list[j]
      list[j] = temp
    }

    // 第二步：计算数组的最大值和最小值
    const max = Math.max(...arr)
    const min = Math.min(...arr)
    const buckets = []
    let idx

    // 第三步：根据数组长度计算桶的大小
    const bucketSize = Math.floor((max - min) / arr.length) + 1

    // 第四步：元素分配，遍历数组，将元素分配到对应桶中
    for (let i = 0, len = arr.length; i < len; i++) {
      // 桶索引：计算元素应该放入的桶索引
      idx = Math.floor((arr[i] - min) / bucketSize)

      // 负数处理：负数放在第1个桶
      if (idx < 0) {
        idx = 0
      }

      // 桶初始化：如果桶不存在则创建
      if (!Array.isArray(buckets[idx])) {
        buckets[idx] = []
      }

      // 元素插入：将元素插入到桶中
      buckets[idx].push(arr[i])

      // 第五步：实时排序，插入后立即对桶内进行冒泡排序
      const bucketLen = buckets[idx].length
      // 冒泡排序：从后往前比较，确保桶内有序
      for (let j = bucketLen - 1; j > 0; j--) {
        // 比较交换：如果前一个元素大于后一个元素，则交换
        if (buckets[idx][j] < buckets[idx][j - 1]) {
          // 交换操作：调用交换函数
          swap(buckets[idx], j, j - 1)
        }
      }
    }

    // 第六步：结果合并，将各桶的数据合并到新数组
    let wrapBuckets = []
    for (let i = 0; i < buckets.length; i++) {
      if (buckets[i] !== undefined) {
        wrapBuckets = wrapBuckets.concat(buckets[i])
      }
    }
    console.log(wrapBuckets)
    return wrapBuckets
  }

  /**
   * 桶排序优化版 - 使用更精确的桶分配策略
   * 
   * 算法思路：
   * 1. 分析数据分布，计算最优桶数量
   * 2. 使用更精确的桶边界计算
   * 3. 桶内使用快速排序提高效率
   * 4. 支持负数和浮点数
   * 5. 优化内存使用
   * 
   * 优化效果：
   * - 智能桶数量计算
   * - 更精确的数据分布处理
   * - 桶内使用快速排序
   * - 更好的边界条件处理
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function bucketSort6(arr) {
    console.log('bucketSort6 optimized version:')
    if (arr.length <= 1) return arr.slice();
    
    // 第一步：计算数据范围
    const min = Math.min(...arr);
    const max = Math.max(...arr);
    const range = max - min;
    
    // 第二步：智能计算，基于数据分布和数组大小计算最优桶数量
    const optimalBucketCount = Math.max(5, Math.min(arr.length, Math.ceil(Math.sqrt(arr.length))));
    const bucketSize = range / optimalBucketCount;
    
    // 第三步：桶创建，创建指定数量的桶
    const buckets = Array.from({length: optimalBucketCount}, () => []);
    
    // 第四步：元素分配，分配元素到对应桶中
    for (const value of arr) {
      let bucketIndex;
      
      // 边界处理：处理最大值和最小值的特殊情况
      if (value === max) {
        bucketIndex = optimalBucketCount - 1;
      } else if (value === min) {
        bucketIndex = 0;
      } else {
        bucketIndex = Math.floor((value - min) / bucketSize);
      }
      
      // 索引检查：确保索引在有效范围内
      bucketIndex = Math.max(0, Math.min(optimalBucketCount - 1, bucketIndex));
      
      // 元素插入：将元素放入对应桶中
      buckets[bucketIndex].push(value);
    }
    
    // 第五步：桶内排序，对每个桶进行排序并合并
    const result = [];
    for (const bucket of buckets) {
      if (bucket.length > 0) {
        // 快速排序：使用JavaScript内置排序
        bucket.sort((a, b) => a - b);
        result.push(...bucket);
      }
    }
    
    console.log(result);
    return result;
  }

  // ==================== 测试代码 ====================

  const arrData = [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

  console.log('=== 桶排序算法演示 ===\n')

  // 测试bucketSort1
  console.time('bucketSort1')
  console.log('arrData origin:', arrData)
  console.log('bucketSort1 sorted:', bucketSort1(arrData))
  console.timeEnd('bucketSort1')

  console.log('\r\n')

  // 测试bucketSort2
  console.time('bucketSort2')
  console.log('arrData origin:', arrData)
  console.log('bucketSort2 sorted:', bucketSort2(arrData))
  console.timeEnd('bucketSort2')

  console.log('\r\n')

  // 测试bucketSort3
  console.time('bucketSort3')
  console.log('arrData origin:', arrData)
  console.log('bucketSort3 sorted:', bucketSort3(arrData))
  console.timeEnd('bucketSort3')

  console.log('\r\n')

  // 测试bucketSort4
  console.time('bucketSort4')
  console.log('arrData origin:', arrData)
  console.log('bucketSort4 sorted:', bucketSort4(arrData))
  console.timeEnd('bucketSort4')

  console.log('\r\n')

  // 测试bucketSort5
  console.time('bucketSort5')
  console.log('arrData origin:', arrData)
  console.log('bucketSort5 sorted:', bucketSort5(arrData))
  console.timeEnd('bucketSort5')

  // 测试bucketSort6
  console.time('bucketSort6')
  console.log('arrData origin:', arrData)
  console.log('bucketSort6 sorted:', bucketSort6(arrData))
  console.timeEnd('bucketSort6')

  console.log('\r\n=== 算法对比总结 ===')
  console.log('1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理')
  console.log('2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好')
  console.log('3. 挪动排序版本：bucketSort3 - 避免splice开销，更稳定')
  console.log('4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确')
  console.log('5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序')
  console.log('6. 优化版本：bucketSort6 - 智能桶数量计算，更精确的数据分布处理')

  // ==================== 算法对比分析 ====================

  console.log('\r\n=== 桶排序算法对比分析 ===')
  console.log('\n1. bucketSort1 - 支持负数版本')
  console.log('   特点：使用绝对值计算桶范围，负数统一放入第1个桶')
  console.log('   优点：支持负数，处理混合数据')
  console.log('   缺点：桶分配可能不精确，负数都在一个桶内')
  console.log('   适用：包含负数的混合数据排序')

  console.log('\n2. bucketSort2 - 正数专用版本')
  console.log('   特点：不支持负数，动态计算桶数量')
  console.log('   优点：桶分配更精确，性能较好')
  console.log('   缺点：不支持负数，负数会被丢弃')
  console.log('   适用：纯正数数据排序')

  console.log('\n3. bucketSort3 - 挪动排序版本')
  console.log('   特点：使用挪动排序而非splice，手动计算最大最小值')
  console.log('   优点：避免splice性能开销，更稳定')
  console.log('   缺点：实现复杂，性能不一定更好')
  console.log('   适用：需要避免splice操作的场景')

  console.log('\n4. bucketSort4 - 负数单独处理版本')
  console.log('   特点：负数单独收集排序，正数使用桶排序')
  console.log('   优点：负数和正数分别优化，排序更精确')
  console.log('   缺点：需要额外空间存储负数')
  console.log('   适用：负数和正数分布差异大的数据')

  console.log('\n5. bucketSort5 - 实时冒泡排序版本')
  console.log('   特点：每次插入后立即对桶内进行冒泡排序')
  console.log('   优点：桶内始终保持有序，插入即排序')
  console.log('   缺点：插入操作性能开销大')
  console.log('   适用：需要实时保持桶内有序的场景')

  console.log('\n6. bucketSort6 - 优化版本')
  console.log('   特点：智能桶数量计算，更精确的数据分布处理')
  console.log('   优点：桶分配更精确，性能较好')
  console.log('   缺点：实现复杂度稍高')
  console.log('   适用：需要更精确桶分配的场景')

  console.log('\n=== 重复性分析 ===')
  console.log('bucketSort1 和 bucketSort3：')
  console.log('  - 都支持负数')
  console.log('  - 都将负数放入第1个桶')
  console.log('  - 区别：bucketSort1用绝对值计算，bucketSort3用挪动排序')
  console.log('  - 重复度：中等（思路相似，实现不同）')

  console.log('\nbucketSort2 和其他版本：')
  console.log('  - 唯一不支持负数的版本')
  console.log('  - 重复度：低（功能差异明显）')

  console.log('\nbucketSort4 和其他版本：')
  console.log('  - 唯一将负数单独排序的版本')
  console.log('  - 重复度：低（处理方式独特）')

  console.log('\nbucketSort5 和其他版本：')
  console.log('  - 唯一使用实时冒泡排序的版本')
  console.log('  - 重复度：低（排序方式独特）')

  console.log('\nbucketSort6 和其他版本：')
  console.log('  - 唯一使用智能桶数量计算的版本')
  console.log('  - 重复度：低（优化策略独特）')

  console.log('\n=== 推荐使用场景 ===')
  console.log('• 通用场景：bucketSort1（支持负数，实现简单）')
  console.log('• 正数数据：bucketSort2（性能较好，桶分配精确）')
  console.log('• 性能敏感：bucketSort3（避免splice开销）')
  console.log('• 大量负数：bucketSort4（负数单独优化）')
  console.log('• 实时排序：bucketSort5（插入即排序）')
  console.log('• 精确分配：bucketSort6（智能桶数量计算）')

  console.log('\r\n=== 桶排序算法对比分析 ===')
  console.log('\n1. bucketSort1 - 支持负数版本')
  console.log('   特点：使用绝对值计算桶范围，负数统一放入第1个桶')
  console.log('   优点：支持负数，处理混合数据')
  console.log('   缺点：桶分配可能不精确，负数都在一个桶内')
  console.log('   适用：包含负数的混合数据排序')

  console.log('\n2. bucketSort2 - 正数专用版本')
  console.log('   特点：不支持负数，动态计算桶数量')
  console.log('   优点：桶分配更精确，性能较好')
  console.log('   缺点：不支持负数，负数会被丢弃')
  console.log('   适用：纯正数数据排序')

  console.log('\n3. bucketSort3 - 挪动排序版本')
  console.log('   特点：使用挪动排序而非splice，手动计算最大最小值')
  console.log('   优点：避免splice性能开销，更稳定')
  console.log('   缺点：实现复杂，性能不一定更好')
  console.log('   适用：需要避免splice操作的场景')

  console.log('\n4. bucketSort4 - 负数单独处理版本')
  console.log('   特点：负数单独收集排序，正数使用桶排序')
  console.log('   优点：负数和正数分别优化，排序更精确')
  console.log('   缺点：需要额外空间存储负数')
  console.log('   适用：负数和正数分布差异大的数据')

  console.log('\n5. bucketSort5 - 实时冒泡排序版本')
  console.log('   特点：每次插入后立即对桶内进行冒泡排序')
  console.log('   优点：桶内始终保持有序，插入即排序')
  console.log('   缺点：插入操作性能开销大')
  console.log('   适用：需要实时保持桶内有序的场景')

  console.log('\n6. bucketSort6 - 优化版本')
  console.log('   特点：智能桶数量计算，更精确的数据分布处理')
  console.log('   优点：桶分配更精确，性能较好')
  console.log('   缺点：实现复杂度稍高')
  console.log('   适用：需要更精确桶分配的场景')

  console.log('\n=== 重复性分析 ===')
  console.log('bucketSort1 和 bucketSort3：')
  console.log('  - 都支持负数')
  console.log('  - 都将负数放入第1个桶')
  console.log('  - 区别：bucketSort1用绝对值计算，bucketSort3用挪动排序')
  console.log('  - 重复度：中等（思路相似，实现不同）')

  console.log('\nbucketSort2 和其他版本：')
  console.log('  - 唯一不支持负数的版本')
  console.log('  - 重复度：低（功能差异明显）')

  console.log('\nbucketSort4 和其他版本：')
  console.log('  - 唯一将负数单独排序的版本')
  console.log('  - 重复度：低（处理方式独特）')

  console.log('\nbucketSort5 和其他版本：')
  console.log('  - 唯一使用实时冒泡排序的版本')
  console.log('  - 重复度：低（排序方式独特）')

  console.log('\nbucketSort6 和其他版本：')
  console.log('  - 唯一使用智能桶数量计算的版本')
  console.log('  - 重复度：低（优化策略独特）')

  console.log('\n=== 推荐使用场景 ===')
  console.log('• 通用场景：bucketSort1（支持负数，实现简单）')
  console.log('• 正数数据：bucketSort2（性能较好，桶分配精确）')
  console.log('• 性能敏感：bucketSort3（避免splice开销）')
  console.log('• 大量负数：bucketSort4（负数单独优化）')
  console.log('• 实时排序：bucketSort5（插入即排序）')
  console.log('• 精确分配：bucketSort6（智能桶数量计算）')

})()

/* 打印结果
jarry@Mac bucketsort % node bucket_sort.js
=== 桶排序算法演示 ===

arrData origin: [
  20, 11,  0, -10,  9,
   6, 30, 15,  13, 80
]
bucketSort1 with negative numbers:
[
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
]
bucketSort1 sorted: [
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
]
bucketSort1: 1.761ms


arrData origin: [
  20, 11,  0, -10,  9,
   6, 30, 15,  13, 80
]
bucketSort2 positive numbers only:
[
   6,  9, 11, 13,
  15, 20, 30, 80
]
bucketSort2 sorted: [
   6,  9, 11, 13,
  15, 20, 30, 80
]
bucketSort2: 0.171ms


arrData origin: [
  20, 11,  0, -10,  9,
   6, 30, 15,  13, 80
]
bucketSort3 with move sorting:
[
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
]
bucketSort3 sorted: [
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
]
bucketSort3: 0.139ms


arrData origin: [
  20, 11,  0, -10,  9,
   6, 30, 15,  13, 80
]
bucketSort4 separate negative sorting:
[
  -10,  6,  9, 11, 13,
   15, 20, 30, 80
]
bucketSort4 sorted: [
  -10,  6,  9, 11, 13,
   15, 20, 30, 80
]
bucketSort4: 0.1ms


arrData origin: [
  20, 11,  0, -10,  9,
   6, 30, 15,  13, 80
]
bucketSort5 real-time bubble sorting:
[
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
]
bucketSort5 sorted: [
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
]
bucketSort5: 0.089ms
arrData origin: [
  20, 11,  0, -10,  9,
   6, 30, 15,  13, 80
]
bucketSort6 optimized version:
[
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
]
bucketSort6 sorted: [
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
]
bucketSort6: 0.105ms

=== 算法对比总结 ===
1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理
2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好
3. 挪动排序版本：bucketSort3 - 避免splice开销，更稳定
4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确
5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序
6. 优化版本：bucketSort6 - 智能桶数量计算，更精确的数据分布处理

=== 桶排序算法对比分析 ===

1. bucketSort1 - 支持负数版本
   特点：使用绝对值计算桶范围，负数统一放入第1个桶
   优点：支持负数，处理混合数据
   缺点：桶分配可能不精确，负数都在一个桶内
   适用：包含负数的混合数据排序

2. bucketSort2 - 正数专用版本
   特点：不支持负数，动态计算桶数量
   优点：桶分配更精确，性能较好
   缺点：不支持负数，负数会被丢弃
   适用：纯正数数据排序

3. bucketSort3 - 挪动排序版本
   特点：使用挪动排序而非splice，手动计算最大最小值
   优点：避免splice性能开销，更稳定
   缺点：实现复杂，性能不一定更好
   适用：需要避免splice操作的场景

4. bucketSort4 - 负数单独处理版本
   特点：负数单独收集排序，正数使用桶排序
   优点：负数和正数分别优化，排序更精确
   缺点：需要额外空间存储负数
   适用：负数和正数分布差异大的数据

5. bucketSort5 - 实时冒泡排序版本
   特点：每次插入后立即对桶内进行冒泡排序
   优点：桶内始终保持有序，插入即排序
   缺点：插入操作性能开销大
   适用：需要实时保持桶内有序的场景

6. bucketSort6 - 优化版本
   特点：智能桶数量计算，更精确的数据分布处理
   优点：桶分配更精确，性能较好
   缺点：实现复杂度稍高
   适用：需要更精确桶分配的场景

=== 重复性分析 ===
bucketSort1 和 bucketSort3：
  - 都支持负数
  - 都将负数放入第1个桶
  - 区别：bucketSort1用绝对值计算，bucketSort3用挪动排序
  - 重复度：中等（思路相似，实现不同）

bucketSort2 和其他版本：
  - 唯一不支持负数的版本
  - 重复度：低（功能差异明显）

bucketSort4 和其他版本：
  - 唯一将负数单独排序的版本
  - 重复度：低（处理方式独特）

bucketSort5 和其他版本：
  - 唯一使用实时冒泡排序的版本
  - 重复度：低（排序方式独特）

bucketSort6 和其他版本：
  - 唯一使用智能桶数量计算的版本
  - 重复度：低（优化策略独特）

=== 推荐使用场景 ===
• 通用场景：bucketSort1（支持负数，实现简单）
• 正数数据：bucketSort2（性能较好，桶分配精确）
• 性能敏感：bucketSort3（避免splice开销）
• 大量负数：bucketSort4（负数单独优化）
• 实时排序：bucketSort5（插入即排序）
• 精确分配：bucketSort6（智能桶数量计算）

=== 桶排序算法对比分析 ===

1. bucketSort1 - 支持负数版本
   特点：使用绝对值计算桶范围，负数统一放入第1个桶
   优点：支持负数，处理混合数据
   缺点：桶分配可能不精确，负数都在一个桶内
   适用：包含负数的混合数据排序

2. bucketSort2 - 正数专用版本
   特点：不支持负数，动态计算桶数量
   优点：桶分配更精确，性能较好
   缺点：不支持负数，负数会被丢弃
   适用：纯正数数据排序

3. bucketSort3 - 挪动排序版本
   特点：使用挪动排序而非splice，手动计算最大最小值
   优点：避免splice性能开销，更稳定
   缺点：实现复杂，性能不一定更好
   适用：需要避免splice操作的场景

4. bucketSort4 - 负数单独处理版本
   特点：负数单独收集排序，正数使用桶排序
   优点：负数和正数分别优化，排序更精确
   缺点：需要额外空间存储负数
   适用：负数和正数分布差异大的数据

5. bucketSort5 - 实时冒泡排序版本
   特点：每次插入后立即对桶内进行冒泡排序
   优点：桶内始终保持有序，插入即排序
   缺点：插入操作性能开销大
   适用：需要实时保持桶内有序的场景

6. bucketSort6 - 优化版本
   特点：智能桶数量计算，更精确的数据分布处理
   优点：桶分配更精确，性能较好
   缺点：实现复杂度稍高
   适用：需要更精确桶分配的场景

=== 重复性分析 ===
bucketSort1 和 bucketSort3：
  - 都支持负数
  - 都将负数放入第1个桶
  - 区别：bucketSort1用绝对值计算，bucketSort3用挪动排序
  - 重复度：中等（思路相似，实现不同）

bucketSort2 和其他版本：
  - 唯一不支持负数的版本
  - 重复度：低（功能差异明显）

bucketSort4 和其他版本：
  - 唯一将负数单独排序的版本
  - 重复度：低（处理方式独特）

bucketSort5 和其他版本：
  - 唯一使用实时冒泡排序的版本
  - 重复度：低（排序方式独特）

bucketSort6 和其他版本：
  - 唯一使用智能桶数量计算的版本
  - 重复度：低（优化策略独特）

=== 推荐使用场景 ===
• 通用场景：bucketSort1（支持负数，实现简单）
• 正数数据：bucketSort2（性能较好，桶分配精确）
• 性能敏感：bucketSort3（避免splice开销）
• 大量负数：bucketSort4（负数单独优化）
• 实时排序：bucketSort5（插入即排序）
• 精确分配：bucketSort6（智能桶数量计算）
*/