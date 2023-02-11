/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
// https://levelup.gitconnected.com/heapsort-for-javascript-newbies-598d25477d55
// http://www.cppcns.com/wangluo/javascript/149148.html
// https://www.programiz.com/dsa/heap-sort
;(function () {
  // 根据完全二叉树结构性质，父子节点与数组下标的关系，通过数组下标i得到节点位置
  const getParent = (i) => Math.floor((i - 1) / 2)
  const getLeft = (i) => 2 * i + 1
  const getRight = (i) => 2 * i + 2

  /**
   * @param {Array<number>} arr
   * @param {number} idx - the index of element
   * @param {number} size - the array's length
   * 始终保持大顶堆特性, 构建大顶堆的递归写法
   */
  function maxHeapify(arr, idx, size) {
    let max = idx
    const left = getLeft(idx)
    const right = getRight(idx)
    if (left < size && arr[left] > arr[max]) {
      max = left
    }
    if (right < size && arr[right] > arr[max]) {
      max = right
    }
    console.log(
      'idx=',
      idx,
      'left=',
      left,
      'right=',
      right,
      'max=',
      max,
      'size=',
      size
    )
    if (max !== idx) {
      // 保持最大堆，如果当前父节点小于子节点，则进行交换
      ;[arr[idx], arr[max]] = [arr[max], arr[idx]]
      // 继续递归执行，直到符合最大堆特性
      maxHeapify(arr, max, size)
    }
  }

  // 构建最大堆的非递归写法，此处可以覆盖上面递归maxHeapify函数
  function maxHeapify(arr, idx, size) {
    let current = arr[idx]
    let child = getLeft(idx)
    // 从当前位置的左节点开始遍历
    for (; child < size; ) {
      console.log(
        'current=',
        current,
        ' idx=',
        idx,
        ' child=',
        child,
        ' size=',
        size
      )
      // 如果左节点小于右节点且小于总长度，则指向右节点
      if (child + 1 < size && arr[child] < arr[child + 1]) {
        child++
      }
      if (arr[child] > current) {
        // 如果子节点大于父节点，将子节点的值赋给父节点
        arr[idx] = arr[child]
        // 当前节点指向该子节点，继续循环
        idx = child
      } else {
        // 子节点小于父节点则跳出循环
        break
      }
      // 遍历子树父节点
      child = getLeft(idx)
    }
    // 赋值为父节点的值
    arr[idx] = current
  }

  function heapSort(arr) {
    const len = arr.length
    // 最底层的父节点
    let parent = getParent(len) - 1
    // 最底层的子节点
    let child = len - 1
    // 从最后的父节点开始遍历，构建大顶堆，并把最大数冒出到堆顶
    while (parent >= 0) {
      maxHeapify(arr, parent, len)
      console.warn('parent sort:', parent, arr)
      parent--
    }
    console.warn('child start:', 'parent=' + parent, ' child=' + child)
    // 自下向上逐个将子节点数与最顶端的数进行交换，并保持最大堆特性
    while (child > 0) {
      // 将顶端的父节点与当前子节点互换
      ;[arr[0], arr[child]] = [arr[child], arr[0]]
      // 自最底层往上遍历构建大顶堆，已经排好序的不再交换
      maxHeapify(arr, 0, child)
      console.warn('child sort:', child, arr)
      child--
    }

    return arr
  }

  const arr = [7, 11, 9, 10, 12, 13, 8]
  console.time('heapSort')
  console.log('sorted:', heapSort(arr))
  console.timeEnd('heapSort')
})()

/*
oringal array: [7, 11, 9, 10, 12, 13, 8]
heap:
              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  12(4)  13(5)  8(6)

父节点步骤
1. maxHeapify: idx= 2 left= 5 right= 6 max= 5 size= 7
              7(0)
          /         \
        11(1)        13(2)
       /    \      /     \
   10(3)  12(4)  9(5)  8(6)

2. maxHeapify: idx= 1 left= 3 right= 4 max= 4 size= 7
              7(0)
          /         \
        12(1)        13(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

3. maxHeapify: idx= 0 left= 1 right= 2 max= 2 size= 7
              13(0)
          /         \
        12(1)        7(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

3.1 maxHeapify recursion: idx= 2 left= 5 right= 6 max= 5 size= 7
              13(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  8(6)

子节点堆排序:
1. swap, child = 6: 
              8(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

1.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 6
              12(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

1.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 4 size= 6
              12(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  7(5)  13(6)

2. swap, child = 5:
              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

2.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 5
              11(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

2.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 3 size= 5
              11(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  8(4)  12(5)  13(6)

3. swap, child = 4:
              8(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

3.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 4
              10(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

3.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 1 size= 4


4. swap, child = 3:
              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

4.1 maxHeapify: idx= 0 left= 1 right= 2 max= 2 size= 3
              9(0)
          /         \
        8(1)        7(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

4.2 maxHeapify recursion: idx= 2 left= 5 right= 6 max= 2 size= 3

5. swap, child = 2:
              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

5.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 2
              8(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

5.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 1 size= 2

6. swap, child = 1:
              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

6.1 maxHeapify: idx= 0 left= 1 right= 2 max= 0 size= 1

*/

/**
jarrys-MacBook-Pro:heapsort jarry$ node heap_sort.js 
current= 9  idx= 2  child= 5  size= 7
parent sort: 2 [ 7, 11, 13, 10, 12, 9, 8 ]
current= 11  idx= 1  child= 3  size= 7
parent sort: 1 [ 7, 12, 13, 10, 11, 9, 8 ]
current= 7  idx= 0  child= 1  size= 7
current= 7  idx= 2  child= 5  size= 7
parent sort: 0 [ 13, 12, 9, 10, 11, 7, 8 ]
child start: parent=-1  child=6
current= 8  idx= 0  child= 1  size= 6
jarrys-MacBook-Pro:heapsort jarry$ node heap_sort.js 
current= 9  idx= 2  child= 5  size= 7
parent sort: 2 [ 7, 11, 13, 10, 12, 9, 8 ]
current= 11  idx= 1  child= 3  size= 7
parent sort: 1 [ 7, 12, 13, 10, 11, 9, 8 ]
current= 7  idx= 0  child= 1  size= 7
current= 7  idx= 2  child= 5  size= 7
parent sort: 0 [ 13, 12, 9, 10, 11, 7, 8 ]
child start: parent=-1  child=6
current= 8  idx= 0  child= 1  size= 6
current= 8  idx= 1  child= 3  size= 6
child sort: 6 [ 12, 11, 9, 10, 8, 7, 13 ]
current= 7  idx= 0  child= 1  size= 5
current= 7  idx= 1  child= 3  size= 5
child sort: 5 [ 11, 10, 9, 7, 8, 12, 13 ]
current= 8  idx= 0  child= 1  size= 4
current= 8  idx= 1  child= 3  size= 4
child sort: 4 [ 10, 8, 9, 7, 11, 12, 13 ]
current= 7  idx= 0  child= 1  size= 3
child sort: 3 [ 9, 8, 7, 10, 11, 12, 13 ]
current= 7  idx= 0  child= 1  size= 2
child sort: 2 [ 8, 7, 9, 10, 11, 12, 13 ]
child sort: 1 [ 7, 8, 9, 10, 11, 12, 13 ]
sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
heapSort: 5.573ms
 */
