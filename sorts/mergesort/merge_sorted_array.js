/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
(function () {
  /**
   * 合并两个已排序数组。
   * 新建数组复制法，比较数组1和数组2的当前项，将小的添加到新数组中
   * @param {Arary} one
   * @param {Array} two
   */
  function mergeSorted1 (one, two) {
    const result = []
    // 数组1下标
    let i = 0
    // 数组2下标
    let j = 0
    // 结果数组下标
    let k = 0

    const oneLen = one.length
    const twoLen = two.length
    // 循环遍历两个数组，直到有1个数组里面的全部被比较过
    while (i < oneLen && j < twoLen) {
      // 逐个比较数组1和数组2的项，将小的项添加到新数组中，移动指针再继续下个比较
      if (one[i] < two[j]) {
        result[k++] = one[i++]
      } else {
        result[k++] = two[j++]
      }
      console.log(`while one[i] < two[j] ${i} < ${j}`, result)
    }

    console.log(one, i, oneLen)
    // 如果数组1还有剩余的没有添加完，就全部追加到新数组最后
    while (i < oneLen) {
      result[k++] = one[i++]
    }

    // 如果数组2还有剩余的没有添加完，就全部追加到新数组最后
    while (j < twoLen) {
      result[k++] = two[j++]
    }

    return result
  }

  /**
   * 合并两个已排序数组。
   * 插入法，从第一个数组里取出一项，自前往后逐个与第二个数组项进行比较，插入到第二个数组中
   * @param {Arary} one
   * @param {Array} two
   */
  function mergeSorted2 (one, two) {
    const oneLen = one.length
    let twoLen = two.length
    let j = 0
    for (let i = 0; i < oneLen; i++) {
      for (; j < twoLen; j++) {
        // 从数组1里拿出一项来与数组2逐个(自前往后)进行比较
        // 当遇到比它大的项时，则把它插入到数组2里该项的前面
        // 同时数组2下标与长度增加一位，跳出当前循环，进入下一轮比较
        if (one[i] < two[j]) {
          console.log(`insert ${one[i]} into two at ${j}`)
          two.splice(j, 0, one[i])
          twoLen++
          break
        } else {
          // 如果全部比较完成，且数组2里面没有比它还大的，则添加到最后
          // 也可以一次性添加数组1里面全部剩余项，后面的就无需再比较了
          if (j === twoLen - 1) {
            two[j + 1] = one[i]
            twoLen++
            break
          }
        }
        console.log(`for one[i] < two[j] ${i} vs ${j}`, one[i], two[j], one, two)
      }
    }
    return two
  }

  /**
   * 合并两个已排序数组。
   * 插入法，从第一个数组里取出一项，自后往前逐个与第二个数组项进行比较，插入到第二个数组中
   * @param {Arary} one
   * @param {Array} two
   */
  function mergeSorted3 (one, two) {
    const oneLen = one.length
    let twoLen = two.length
    for (let i = 0; i < oneLen; i++) {
      let j = twoLen - 1
      // 拿数组1的一项作为比较项，逐个跟数组2里的项进行比较
      // 自后往前查找，直到找到比它小的位置，插入到该位置后面
      // 如果没有比它还小的，那么j无变化，就会插入到最后
      while (one[i] < two[j]) {
        j--
      }
      // 优化点: 如果j的位置无变化，说明比较项是数组2里最大的，则可以一次性复制数组1后面全部的项
      if (j === twoLen - 1) {
        const remained = one.slice(i, oneLen)
        console.log('concat remained:', remained)
        two = two.concat(remained)
        break
      }

      // 把比较项插入到第二个数组里比它小的位置后面
      console.log(`insert ${one[i]} into two at ${j + 1}`)
      two.splice(j + 1, 0, one[i])
      twoLen++

      console.log(`while one[i] < two[j] ${i} < ${j}`, one[i], two[j], one, two)
    }
    return two
  }

  /**
   * 合并两个已排序数组。
   * 新建数组复制法，比较数组1和数组2的当前项，将小的添加到新数组中
   * @param {Arary} one
   * @param {Array} two
   */
  function mergeSorted4 (one, two) {
    const result = []
    // 数组1下标
    let i = 0
    // 数组2下标
    let j = 0

    const oneLen = one.length
    const twoLen = two.length
    // 循环遍历两个数组，直到有1个数组里面的全部被比较过
    while (i < oneLen && j < twoLen) {
      // 逐个比较数组1和数组2的项，将小的项添加到新数组中，再继续下个比较
      if (one[i] < two[j]) {
        result.push(one[i])
        i++
      } else {
        result.push(two[j])
        j++
      }
      console.log(`while one[i] < two[j] ${i} < ${j}`, result)
    }

    // 如果数组1还有剩余的没有添加完，就全部追加到新数组最后
    while (i < oneLen) {
      result.push(one[i])
      i++
    }

    // 如果数组2还有剩余的没有添加完，就全部追加到新数组最后
    while (j < twoLen) {
      result.push(two[j])
      j++
    }

    return result
  }

  // test
  console.log('\n\r==== merge sorted array  === \r\n')
  const arr1 = [3, 7, 9, 10, 11, 15, 16]
  const arr2 = [1, 5, 6, 9, 12]
  console.time('mergeSorted1 sorted cost')
  console.log('mergeSorted1 origin:', arr1, arr2)
  console.info('\r\n mergeSorted1 result:', mergeSorted1(arr1.slice(0, arr1.length), arr2.slice(0, arr2.length)))
  console.timeEnd('mergeSorted1 sorted cost')

  console.time('mergeSorted2 sorted cost')
  console.log('mergeSorted2 origin:', arr1, arr2)
  console.info('\r\n mergeSorted2 result:', mergeSorted2(arr1.slice(0, arr1.length), arr2.slice(0, arr2.length)))
  console.timeEnd('mergeSorted2 sorted cost')

  console.time('mergeSorted3 sorted cost')
  console.log('mergeSorted3 origin:', arr1, arr2)
  console.info('\r\n mergeSorted3 result:', mergeSorted3(arr1.slice(0, arr1.length), arr2.slice(0, arr2.length)))
  console.timeEnd('mergeSorted3 sorted cost')

  console.time('mergeSorted4 sorted cost')
  console.log('mergeSorted4 origin:', arr1, arr2)
  console.info('\r\n mergeSorted4 result:', mergeSorted4(arr1.slice(0, arr1.length), arr2.slice(0, arr2.length)))
  console.timeEnd('mergeSorted4 sorted cost')
})()
