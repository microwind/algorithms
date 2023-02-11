/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
(function () {

  /**
   * 桶排序支持负数，负数放在第1个桶里排序
   */
  function bucketSort1(arr) {
    const max = Math.max(...arr)
    let min = Math.min.apply(this, arr)
    if (min < max && min <= 0) min = 1
    // 设置桶的数量，可以任意设置，也可以根据最大、最小值来设置
    const bucketNumber = Math.abs(Math.floor((max - min) / min)) + 1
    const bucketSize = Math.abs(Math.floor((max - min) / bucketNumber)) + 1
    const buckets = []
    let idx
    arr.forEach((item, i) => {
      // 当前项除以桶数取整，决定应该放在某个桶内
      idx = Math.floor((item - min) / bucketSize)
      // 负数全放在第一个桶里，相当于负数按照插入方式排序
      idx = idx > 0 ? idx : 0
      // console.log('bucketSort1 bucketNumber=' + bucketNumber, 'bucketSize=' + bucketSize, 'idx=' + idx)
      if (!buckets[idx]) {
        buckets[idx] = []
        buckets[idx].push(item)
      } else {
        let len = buckets[idx].length
        while (len--) {
          // 自后往前遍历，如果数字大于数组中的项则插入其后
          if (item > buckets[idx][len]) {
            buckets[idx].splice(len + 1, 0, item)
            break
            // 如果数字最小则插入到最前
          } else if (len === 0) {
            buckets[idx].unshift(item)
          }
        }
      }
    })

    // 按照下标和顺序取出桶内的数字，回填到一个数组中
    let output = []
    buckets.forEach((bucketItem) => {
      if (bucketItem) {
        output = output.concat(bucketItem)
      }
    })
    return output
  }

  /**
   * 桶排序标准版，不支持负数
   */
  function bucketSort2(arr) {
    const max = Math.max(...arr)
    let min = Math.min(...arr)
    if (min < max && min <= 0) min = 1
    // 设置桶的数量，可以任意设置，也可以根据最小值来设置
    const size = Math.floor(arr.length / 2)
    let bucketNumber = Math.abs(Math.floor((max - min) / min)) + 1
    bucketNumber = bucketNumber < size ? bucketNumber : size
    const bucketSize = Math.abs(Math.floor((max - min) / bucketNumber)) + 1
    const buckets = []
    let idx
    arr.forEach((item) => {
      // 当前项除以桶间距取整，决定应该放在某个桶内
      idx = Math.floor((item - min) / bucketSize)
      // 如支持负数可把负数全放在第一个桶内
      // idx = idx < 0 ? 0 : idx
      // console.log('bucketSort2 bucketNumber=' + bucketNumber, 'bucketSize=' + bucketSize, 'idx=' + idx)
      if (!buckets[idx]) {
        buckets[idx] = []
        buckets[idx].push(item)
      } else {
        let len = buckets[idx].length
        // 只能遍历下标为0的项，负数相当于丢弃
        while (len--) {
          // 自后往前遍历，如果数字大于数组中的项则插入其后
          if (item > buckets[idx][len]) {
            buckets[idx].splice(len + 1, 0, item)
            break
            // 如果数字最小则插入到最前
          } else if (len === 0) {
            buckets[idx].unshift(item)
          }
        }
      }
    })
    // 按照下标和顺序取出桶内的数字，回填到一个数组中
    let output = []
    buckets.forEach((bucketItem) => {
      if (bucketItem) {
        output = output.concat(bucketItem)
      }
    })
    return output
  }

  /**
   * 桶排序标准版，负数放入第一个桶，挪动排序
   */
  function bucketSort3(arr) {
    let max = arr[0]
    let min = arr[0]
    // 得到最大与最小值
    for (let i = 0, len = arr.length; i < len; i++) {
      if (arr[i] > max) {
        max = arr[i]
      }
      if (arr[i] < min) {
        min = arr[i]
      }
    }
    if (max <= 0) max = 1
    if (min < max && min <= 0) min = 1
    // 设置桶的数量，可以任意设置，也可以根据最大小值来设置
    const bucketNumber = Math.abs(Math.floor((max - min) / min)) + 1
    const bucketSize = Math.abs(Math.floor((max - min) / bucketNumber)) + 1
    // 桶列表与桶下标
    const buckets = []
    let idx
    let item

    for (let i = 0, len = arr.length; i < len; i++) {
      // 排序数字除以桶数得到下标，以此来决定分配到哪个桶里面
      item = arr[i]
      idx = Math.floor((item - min) / bucketSize)
      // 负数全部放入第一桶
      if (idx < 0) {
        idx = 0
      }
      // console.log('bucketSort3 bucketNumber=' + bucketNumber, 'bucketSize=' + bucketSize, 'idx=' + idx)
      // 每个桶都是一个数组，若不存在则创建并放入数字
      if (!Array.isArray(buckets[idx])) {
        buckets[idx] = []
        buckets[idx].push(item)
      } else {
        // 如果桶内已有数字，先留出最后一个空位，然后按照顺序插入
        let len = buckets[idx].length
        buckets[idx].length = len + 1
        while (len--) {
          if (item < buckets[idx][len]) {
            // 如果插入的数字小于当前项，则将当前项逐个往后挪
            buckets[idx][len + 1] = buckets[idx][len]
            if (len === 0) {
              buckets[idx][0] = item
            }
          } else {
            // 如果大于等于当前项，则插入到当前项后面，循环中止
            buckets[idx][len + 1] = item
            break
          }
        }
      }
    }
    // 按照下标和顺序取出桶内的数字，回填到数组中
    const output = []
    // 把数组内容取出
    for (let i = 0, len = buckets.length; i < len; i++) {
      const bucketItem = buckets[i]
      if (bucketItem) {
        let j = 0
        const bucketItemLen = bucketItem.length
        while (j < bucketItemLen) {
          output.push(bucketItem[j])
          j++
        }
      }
    }
    return output
  }

  /**
   * 桶排序标准版，负数单独排序
   */
  function bucketSort4(arr) {
    let max = arr[0]
    let min = arr[0]
    // 得到最大与最小值
    for (let i = 0, len = arr.length; i < len; i++) {
      if (arr[i] > max) {
        max = arr[i]
      }
      if (arr[i] < min) {
        min = arr[i]
      }
    }
    if (min < max && min <= 0) min = 1
    // 设置桶的数量，可以任意设置，也可以根据最大小值来设置
    const bucketNumber = Math.abs(Math.floor((max - min) / min)) + 1
    const bucketSize = Math.abs(Math.floor((max - min) / bucketNumber)) + 1
    // 桶列表与桶下标
    const buckets = []
    let idx
    let item
    // 支持小数，如果要支持负数，则需要将负数下标单独存取，见注释
    const negativeList = []

    for (let i = 0, len = arr.length; i < len; i++) {
      // 排序数字除以桶数得到下标，以此来决定分配到哪个桶里面
      item = arr[i]
      idx = Math.floor((item - min) / bucketSize)
      // console.log('bucketSort4 bucketNumber=' + bucketNumber, 'bucketSize=' + bucketSize, 'idx=' + idx)
      // 如果要支持负数则需要添加到负数下标列表中去
      if (idx < 0) {
        negativeList.push(item)
        continue
      }
      // 每个桶都是一个数组，若不存在则创建并放入数字
      if (!Array.isArray(buckets[idx])) {
        buckets[idx] = []
        buckets[idx].push(item)
      } else {
        // 如果桶内已有数字，先留出最后一个空位，然后按照顺序插入
        let len = buckets[idx].length
        buckets[idx].length = len + 1
        while (len--) {
          if (item < buckets[idx][len]) {
            // 如果插入的数字小于当前项，则将当前项逐个往后挪
            buckets[idx][len + 1] = buckets[idx][len]
            if (len === 0) {
              buckets[idx][0] = item
            }
          } else {
            // 如果大于等于当前项，则插入到当前项后面，循环中止
            buckets[idx][len + 1] = item
            break
          }
        }
      }
    }
    // 按照下标和顺序取出桶内的数字，回填到数组中
    const output = []
    // 先把负数排序然后逐个取出，这里将负数单独出来排序了
    negativeList.sort((a, b) => {
      return a - b
    })
    for (let i = 0, len = negativeList.length; i < len; i++) {
      output.push(negativeList[i])
    }
    // 把数组内容取出
    for (let i = 0, len = buckets.length; i < len; i++) {
      const bucketItem = buckets[i]
      if (bucketItem) {
        let j = 0
        const bucketItemLen = bucketItem.length
        while (j < bucketItemLen) {
          output.push(bucketItem[j])
          j++
        }
      }
    }
    return output
  }

  /**
   * 桶排序标准版，负数放在第一个桶内排序
   */
  function bucketSort5(arr) {
    function swap(list, i, j) {
      const temp = list[i]
      list[i] = list[j]
      list[j] = temp
    }
    const max = Math.max(...arr)
    const min = Math.min(...arr)
    const buckets = []
    // 桶的容量大小可以是大于1的任意值，可根据数组内容来确定，这里用最大项与最小项的差比上数组长度取整
    const bucketSize = Math.floor((max - min) / arr.length)
    for (let i = 0; i < arr.length; i++) {
      // index是桶的下标，数字除以桶数得到
      let index = Math.floor(arr[i] / bucketSize)
      if (index < 0) {
        index = 0
      }
      if (!buckets[index]) {
        buckets[index] = []
      }
      // 把数据添加到对应桶中
      buckets[index].push(arr[i])
      let l = buckets[index].length
      // console.log('bucketSort5 bucketSize=' + bucketSize, 'arr[i]=' + arr[i], 'index=' + index, buckets)
      // 添加之后立即遍历当前区间的桶，给桶内的数据按冒泡排序，保证该桶内是排好顺序的
      while (l > 0) {
        // console.log('bucketSort5 swap:', l, buckets[index], buckets[index][l], buckets[index][l - 1], arr)
        if (buckets[index][l] < buckets[index][l - 1]) {
          swap(buckets[index], l, l - 1)
        }
        l--
      }
    }
    // 将各桶的数据回填到新数组
    let wrapBuckets = []
    for (let i = 0; i < buckets.length; i++) {
      if (buckets[i] !== undefined) {
        wrapBuckets = wrapBuckets.concat(buckets[i])
      }
    }
    return wrapBuckets
  }

  // test
  const arr1 = [2, 11, 9, 30, 15, 13, 80]
  const arr2 = [3, 4.3, 15, -2.1, -2, -2.1, 2, 3.2, 3, -7, 10]
  console.time('bucketSort1-arr1')
  console.log('arr1 origin:', arr1)
  console.log('bucketSort1-arr1 sorted:', bucketSort1(arr1))
  console.timeEnd('bucketSort1-arr1')

  console.time('bucketSort1-arr2')
  console.log('arr2 origin:', arr2)
  console.log('bucketSort1-arr2 sorted:', bucketSort1(arr2))
  console.timeEnd('bucketSort1-arr2')

  console.log('\r\n')

  console.time('bucketSort2-arr1')
  console.log('arr1 origin:', arr1)
  console.log('bucketSort2-arr1 sorted:', bucketSort2(arr1))
  console.timeEnd('bucketSort2-arr1')
  console.time('bucketSort2-arr2')
  console.log('arr2 origin:', arr2)
  console.log('bucketSort2-arr1 sorted:', bucketSort2(arr2))
  console.timeEnd('bucketSort2-arr2')

  console.log('\r\n')

  console.time('bucketSort3-arr1')
  console.log('arr1 origin:', arr1)
  console.log('bucketSort3-arr1 sorted:', bucketSort3(arr1))
  console.timeEnd('bucketSort3-arr1')
  console.time('bucketSort3-arr2')
  console.log('arr2 origin:', arr2)
  console.log('bucketSort3-arr1 sorted:', bucketSort3(arr2))
  console.timeEnd('bucketSort3-arr2')

  console.log('\r\n')

  console.time('bucketSort4-arr1')
  console.log('arr1 origin:', arr1)
  console.log('bucketSort4-arr1 sorted:', bucketSort4(arr1))
  console.timeEnd('bucketSort4-arr1')
  console.time('bucketSort4-arr2')
  console.log('arr2 origin:', arr2)
  console.log('bucketSort4-arr2 sorted:', bucketSort4(arr2))
  console.timeEnd('bucketSort4-arr2')

  console.log('\r\n')

  console.time('bucketSort5-arr1')
  console.log('arr1 origin:', arr1)
  console.log('bucketSort5-arr1 sorted:', bucketSort5(arr1))
  console.timeEnd('bucketSort5-arr1')
  console.time('bucketSort5-arr2')
  console.log('arr2 origin:', arr2)
  console.log('bucketSort5-arr2 sorted:', bucketSort5(arr2))
  console.timeEnd('bucketSort5-arr2')

})()

/**
jarry@192 bucketsort % node bucket_sort.js
arr1 origin: [
   2, 11,  9, 30,
  15, 13, 80
]
bucketSort1-arr1 sorted: [
   2,  9, 11, 13,
  15, 30, 80
]
bucketSort1-arr1: 8.244ms
arr2 origin: [
   3,  4.3, 15, -2.1,
  -2, -2.1,  2,  3.2,
   3,   -7, 10
]
bucketSort1-arr2 sorted: [
   -7, -2.1, -2.1,  -2,
    2,    3,    3, 3.2,
  4.3,   10,   15
]
bucketSort1-arr2: 0.586ms


arr1 origin: [
   2, 11,  9, 30,
  15, 13, 80
]
bucketSort2-arr1 sorted: [
   2,  9, 11, 13,
  15, 30, 80
]
bucketSort2-arr1: 0.546ms
arr2 origin: [
   3,  4.3, 15, -2.1,
  -2, -2.1,  2,  3.2,
   3,   -7, 10
]
bucketSort2-arr1 sorted: [
    2,  3,  3, 3.2,
  4.3, 10, 15
]
bucketSort2-arr2: 0.467ms


arr1 origin: [
   2, 11,  9, 30,
  15, 13, 80
]
bucketSort3-arr1 sorted: [
   2,  9, 11, 13,
  15, 30, 80
]
bucketSort3-arr1: 0.495ms
arr2 origin: [
   3,  4.3, 15, -2.1,
  -2, -2.1,  2,  3.2,
   3,   -7, 10
]
bucketSort3-arr1 sorted: [
   -7, -2.1, -2.1,  -2,
    2,    3,    3, 3.2,
  4.3,   10,   15
]
bucketSort3-arr2: 0.3ms


arr1 origin: [
   2, 11,  9, 30,
  15, 13, 80
]
bucketSort4-arr1 sorted: [
   2,  9, 11, 13,
  15, 30, 80
]
bucketSort4-arr1: 0.356ms
arr2 origin: [
   3,  4.3, 15, -2.1,
  -2, -2.1,  2,  3.2,
   3,   -7, 10
]
bucketSort4-arr2 sorted: [
   -7, -2.1, -2.1,  -2,
    2,    3,    3, 3.2,
  4.3,   10,   15
]
bucketSort4-arr2: 0.292ms


arr1 origin: [
   2, 11,  9, 30,
  15, 13, 80
]
bucketSort5-arr1 sorted: [
   2,  9, 11, 13,
  15, 30, 80
]
bucketSort5-arr1: 0.241ms
arr2 origin: [
   3,  4.3, 15, -2.1,
  -2, -2.1,  2,  3.2,
   3,   -7, 10
]
bucketSort5-arr2 sorted: [
   -7, -2.1, -2.1,  -2,
    2,    3,    3, 3.2,
  4.3,   10,   15
]
bucketSort5-arr2: 0.292ms
*/