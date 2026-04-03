/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 堆排序算法实现
 * 提供五种不同的实现方式，适合不同场景和性能需求
 */
;

/**
 * 打印数组内容的辅助函数
 * @param {number[]} arr - 要打印的数组
 * @param {string} label - 数组的标签说明
 */
function printArray(arr, label) {
  console.log(`${label}: [${arr.join(', ')}]`);
}

/**
 * 打印堆的树形结构
 * @param {number[]} arr - 堆数组
 * @param {string} title - 标题
 */
function printHeapTree(arr, title) {
  console.log(title);
  console.log(`              ${arr[0]}(0)`);
  console.log(`          /         \\`);
  console.log(`        ${arr[1]}(1)        ${arr[2]}(2)`);
  console.log(`       /    \\      /     \\`);
  console.log(`   ${arr[3]}(3)  ${arr[4]}(4)  ${arr[5]}(5)  ${arr[6]}(6)`);
  console.log('');
}

/**
 * 性能测试辅助函数
 * @param {Function} sortFunc - 排序函数
 * @param {number[]} arr - 测试数组
 * @param {string} name - 测试名称
 */
function performanceTest(sortFunc, arr, name) {
  // 创建数组副本，避免修改原数组
  const testArr = [...arr];
  printArray(testArr, `${name}原始数组`);

  // 开始计时
  console.time(name);
  sortFunc(testArr);
  console.timeEnd(name);

  printArray(testArr, `${name}排序结果`);
  console.log(''); // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
const testData = [7, 11, 9, 10, 12, 13, 8];

/**
 * 堆化辅助函数 - 最大堆
 * 核心逻辑：递归调整子树，确保父节点始终大于子节点
 */
function heapify(arr, n, i) {
  let largest = i; // 初始化最大元素为根节点
  const left = 2 * i + 1; // 左子节点索引
  const right = 2 * i + 2; // 右子节点索引

  // 第一步：比较左子节点
  if (left < n && arr[left] > arr[largest]) {
    largest = left;
  }

  // 第二步：比较右子节点
  if (right < n && arr[right] > arr[largest]) {
    largest = right;
  }

  // 第三步：如果需要交换，执行交换并递归堆化
  if (largest !== i) {
    // 关键点：交换父子节点
    [arr[i], arr[largest]] = [arr[largest], arr[i]];
    heapify(arr, n, largest);
  }
}

/**
 * 堆排序基础版本 - 最大堆
 * 
 * 算法原理：
 * 1. 构建最大堆：将无序数组构建成最大堆结构
 * 2. 交换堆顶：将堆顶元素（最大值）与堆尾元素交换
 * 3. 调整堆：对剩余元素重新堆化，保持堆结构
 * 4. 重复步骤2-3，直到整个数组有序
 * 
 * 生活类比：就像在队伍中挑选最高的人站到最后，
 * 然后在剩下的人中再挑选最高的站到倒数第二个位置，依此类推
 * 
 * 时间复杂度：O(n log n) - 构建堆O(n)，每次堆化O(log n)
 * 空间复杂度：O(1) - 原地排序，不需要额外空间
 * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
 */
function heapSort1(arr) {
  console.log('heapSort1 max-heap:');
  const n = arr.length;

  printHeapTree(arr, 'oringal array:');

  // 第一步：构建最大堆
  console.log('父节点步骤');
  let stepCount = 1;
  // 关键点：从最后一个非叶子节点开始堆化
  for (let i = Math.floor(n / 2) - 1; i >= 0; i--) {
    const left = 2 * i + 1;
    const right = 2 * i + 2;
    let maxIdx = i;

    if (left < n && arr[left] > arr[maxIdx]) maxIdx = left;
    if (right < n && arr[right] > arr[maxIdx]) maxIdx = right;

    console.log(`${stepCount}. maxHeapify: idx= ${i} left= ${left} right= ${right} max= ${maxIdx} size= ${n}`);
    stepCount++;

    if (maxIdx !== i) {
      [arr[i], arr[maxIdx]] = [arr[maxIdx], arr[i]];
      printHeapTree(arr, '');

      // 递归堆化
      heapifyWithSteps(arr, n, maxIdx, stepCount);
      stepCount++;
    }
  }

  // 第二步：逐个取出堆顶元素并排序
  console.log('子节点堆排序:');
  for (let i = n - 1; i > 0; i--) {
    console.log(`${stepCount}. swap, child = ${i}:`);
    // 将堆顶元素（最大）与末尾元素交换
    [arr[0], arr[i]] = [arr[i], arr[0]];
    printHeapTree(arr, '');

    // 第三步：重新调整堆
    heapifyWithSteps(arr, i, 0, stepCount);
    stepCount++;
  }

  console.log(arr);
  return arr;
}

/**
 * 带步骤打印的堆化函数
 */
function heapifyWithSteps(arr, n, i, parentStep) {
  let largest = i;
  const left = 2 * i + 1;
  const right = 2 * i + 2;

  // 第一步：比较左子节点
  if (left < n && arr[left] > arr[largest]) {
    largest = left;
  }

  // 第二步：比较右子节点
  if (right < n && arr[right] > arr[largest]) {
    largest = right;
  }

  // 第三步：如果需要交换，执行交换并递归堆化
  if (largest !== i) {
    // 关键点：交换父子节点
    [arr[i], arr[largest]] = [arr[largest], arr[i]];

    const left = 2 * largest + 1;
    const right = 2 * largest + 2;
    let maxIdx = largest;

    if (left < n && arr[left] > arr[maxIdx]) maxIdx = left;
    if (right < n && arr[right] > arr[maxIdx]) maxIdx = right;

    console.log(`${parentStep}.${largest === 0 ? '1' : largest === 1 ? '2' : largest === 2 ? '3' : largest === 3 ? '4' : largest === 4 ? '5' : largest === 5 ? '6' : '7'} maxHeapify: idx= ${largest} left= ${left} right= ${right} max= ${maxIdx} size= ${n}`);
    printHeapTree(arr, '');

    heapifyWithSteps(arr, n, largest, parentStep);
  }
}

/**
 * 堆化辅助函数 - 最小堆
 * 核心逻辑：递归调整子树，确保父节点始终小于子节点
 */
function heapifyMin(arr, n, i) {
  let smallest = i; // 初始化最小元素为根节点
  const left = 2 * i + 1; // 左子节点索引
  const right = 2 * i + 2; // 右子节点索引

  // 第一步：比较左子节点
  if (left < n && arr[left] < arr[smallest]) {
    smallest = left;
  }

  // 第二步：比较右子节点
  if (right < n && arr[right] < arr[smallest]) {
    smallest = right;
  }

  // 第三步：如果需要交换，执行交换并递归堆化
  if (smallest !== i) {
    [arr[i], arr[smallest]] = [arr[smallest], arr[i]];
    heapifyMin(arr, n, smallest);
  }
}

/**
 * 堆排序优化版本 - 最小堆
 * 
 * 算法思路：
 * 使用最小堆进行排序，最终结果为升序
 * 构建最小堆后，依次取出最小元素放到已排序区域
 * 
 * 优化效果：
 * - 直接得到升序结果，无需反转
 * - 某些场景下更直观
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
 */
function heapSort2(arr) {
  console.log('heapSort2 min-heap:');
  const n = arr.length;
  const sorted = [];

  // 第一步：构建最小堆
  for (let i = Math.floor(n / 2) - 1; i >= 0; i--) {
    heapifyMin(arr, n, i);
  }

  // 第二步：逐个取出最小元素
  for (let i = n - 1; i >= 0; i--) {
    // 将堆顶元素（最小）与末尾元素交换
    [arr[0], arr[i]] = [arr[i], arr[0]];

    // 保存最小元素到排序数组
    sorted.push(arr[i]);

    // 第三步：重新调整堆
    heapifyMin(arr, i, 0);
  }

  // 第四步：将排序结果复制回原数组（升序）
  for (let i = 0; i < sorted.length; i++) {
    arr[i] = sorted[i];
  }

  console.log(arr);
  return arr;
}

/**
 * 堆排序 - 迭代版本
 * 
 * 算法思路：
 * 使用迭代方式实现堆化，避免递归调用
 * 通过循环调整父子节点关系
 * 
 * 优化效果：
 * - 避免了递归调用的开销
 * - 更好的性能表现
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
 */
function heapSort3(arr) {
  console.log('heapSort3 iterative:');
  const n = arr.length;

  // 第一步：构建最大堆（迭代方式）
  for (let i = Math.floor(n / 2) - 1; i >= 0; i--) {
    let current = i;
    while (true) {
      let largest = current;
      const left = 2 * current + 1;
      const right = 2 * current + 2;

      // 比较左子节点
      if (left < n && arr[left] > arr[largest]) {
        largest = left;
      }
      // 比较右子节点
      if (right < n && arr[right] > arr[largest]) {
        largest = right;
      }

      if (largest === current) break;

      // 交换父子节点
      [arr[current], arr[largest]] = [arr[largest], arr[current]];
      current = largest;
    }
  }

  // 第二步：逐个取出堆顶元素
  for (let i = n - 1; i > 0; i--) {
    // 交换堆顶与末尾元素
    [arr[0], arr[i]] = [arr[i], arr[0]];

    // 第三步：迭代堆化
    let current = 0;
    while (true) {
      let largest = current;
      const left = 2 * current + 1;
      const right = 2 * current + 2;

      // 比较左子节点
      if (left < i && arr[left] > arr[largest]) {
        largest = left;
      }
      // 比较右子节点
      if (right < i && arr[right] > arr[largest]) {
        largest = right;
      }

      if (largest === current) break;

      // 交换父子节点
      [arr[current], arr[largest]] = [arr[largest], arr[current]];
      current = largest;
    }
  }

  console.log(arr);
  return arr;
}

/**
 * 堆排序 - 自底向上版本
 * 
 * 算法思路：
 * 从底部开始构建堆，逐步向上调整
 * 使用不同的堆化策略，提高构建效率
 * 
 * 优化效果：
 * - 更高效的堆构建过程
 * - 减少不必要的比较
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
 */
function heapSort4(arr) {
  console.log('heapSort4 bottom-up:');
  const n = arr.length;

  // 第一步：自底向上构建最大堆
  for (let i = 1; i < n; i++) {
    let child = i;
    let parent = Math.floor((child - 1) / 2);

    // 向上调整：确保父节点大于子节点
    while (parent >= 0 && arr[parent] < arr[child]) {
      [arr[parent], arr[child]] = [arr[child], arr[parent]];
      child = parent;
      parent = Math.floor((child - 1) / 2);
      if (child === 0) break;
    }
  }

  // 第二步：逐个取出堆顶元素
  for (let i = n - 1; i > 0; i--) {
    // 交换堆顶与末尾元素
    [arr[0], arr[i]] = [arr[i], arr[0]];

    // 第三步：向下调整
    let parent = 0;
    let child = 1;

    while (child < i) {
      // 选择较大的子节点
      if (child + 1 < i && arr[child] < arr[child + 1]) {
        child++;
      }

      if (arr[parent] >= arr[child]) break;

      // 交换父子节点
      [arr[parent], arr[child]] = [arr[child], arr[parent]];
      parent = child;
      child = 2 * parent + 1;
    }
  }

  console.log(arr);
  return arr;
}


function heapSort5(arr) {
  console.log('heapSort5 non-recursive:');

  // 根据完全二叉树结构性质，父子节点与数组下标的关系，通过数组下标i得到节点位置
  const getParent = (i) => Math.floor((i - 1) / 2);
  const getLeft = (i) => 2 * i + 1;
  const getRight = (i) => 2 * i + 2;

  /**
   * @param {Array<number>} arr
   * @param {number} idx - index of element
   * @param {number} size - array's length
   * 始终保持大顶堆特性, 构建大顶堆的非递归写法
   */
  function maxHeapify(arr, idx, size) {
    const current = arr[idx];
    let child = getLeft(idx);
    // 从当前位置的左节点开始遍历
    for (; child < size;) {
      console.log('current=', current, ' idx=', idx, ' child=', child, ' size=', size);
      // 如果左节点小于右节点且小于总长度，则指向右节点
      if (child + 1 < size && arr[child] < arr[child + 1]) {
        child++;
      }
      if (arr[child] > current) {
        // 如果子节点大于父节点，将子节点的值赋给父节点
        arr[idx] = arr[child];
        // 当前节点指向该子节点，继续循环
        idx = child;
      } else {
        // 子节点小于父节点则跳出循环
        break;
      }
      // 遍历子树父节点
      child = getLeft(idx);
    }
    // 赋值为父节点的值
    arr[idx] = current;
  }

  const len = arr.length;
  // 最底层的父节点
  let parent = getParent(len) - 1;
  // 最底层的子节点
  let child = len - 1;

  // 从最后的父节点开始遍历，构建大顶堆，并把最大数冒出到堆顶
  while (parent >= 0) {
    maxHeapify(arr, parent, len);
    console.warn('parent sort:', parent, arr);
    parent--;
  }

  console.warn('child start:', 'parent=' + parent, ' child=' + child);
  // 自下向上逐个将子节点数与最顶端的数进行交换，并保持最大堆特性
  while (child > 0) {
    // 将顶端的父节点与当前子节点互换
    [arr[0], arr[child]] = [arr[child], arr[0]];
    // 自最底层往上遍历构建大顶堆，已经排好序的不再交换
    maxHeapify(arr, 0, child);
    console.warn('child sort:', child, arr);
    child--;
  }

  printArray(arr, '排序后数组');
  return arr;
}

// ==================== 算法测试和性能对比 ====================

// 测试1：最大堆版本
performanceTest(heapSort1, testData, 'heapSort1 max-heap');

// 测试2：最小堆版本
performanceTest(heapSort2, testData, 'heapSort2 min-heap');

// 测试3：迭代版本
performanceTest(heapSort3, testData, 'heapSort3 iterative');

// 测试4：自底向上版本
performanceTest(heapSort4, testData, 'heapSort4 bottom-up');

// 测试5：非递归版本
performanceTest(heapSort5, testData, 'heapSort5 non-recursive');


console.log('=== 算法对比总结 ===');
console.log('1. heapSort1 max-heap：经典实现，升序排序');
console.log('2. heapSort2 min-heap：反向思维，直观易懂');
console.log('3. heapSort3 iterative：避免递归，性能优化');
console.log('4. heapSort4 bottom-up：高效构建，减少比较');
console.log('5. heapSort5 non-recursive：非递归堆化，父子节点计算函数');

/* 打印结果
jarry@Mac heapsort % node heap_sort.js
heapSort1 max-heap原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort1 max-heap:
oringal array:
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

3. maxHeapify: idx= 1 left= 3 right= 4 max= 4 size= 7

              7(0)
          /         \
        12(1)        13(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

5. maxHeapify: idx= 0 left= 1 right= 2 max= 2 size= 7

              13(0)
          /         \
        12(1)        7(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

6.6 maxHeapify: idx= 5 left= 11 right= 12 max= 5 size= 7

              13(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  8(6)

子节点堆排序:
7. swap, child = 6:

              8(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

7.2 maxHeapify: idx= 1 left= 3 right= 4 max= 4 size= 6

              12(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

7.5 maxHeapify: idx= 4 left= 9 right= 10 max= 4 size= 6

              12(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  7(5)  13(6)

8. swap, child = 5:

              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

8.2 maxHeapify: idx= 1 left= 3 right= 4 max= 3 size= 5

              11(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

8.4 maxHeapify: idx= 3 left= 7 right= 8 max= 3 size= 5

              11(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  8(4)  12(5)  13(6)

9. swap, child = 4:

              8(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

9.2 maxHeapify: idx= 1 left= 3 right= 4 max= 1 size= 4

              10(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

10. swap, child = 3:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

10.3 maxHeapify: idx= 2 left= 5 right= 6 max= 2 size= 3

              9(0)
          /         \
        8(1)        7(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

11. swap, child = 2:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

11.2 maxHeapify: idx= 1 left= 3 right= 4 max= 1 size= 2

              8(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

12. swap, child = 1:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

[
   7,  8,  9, 10,
  11, 12, 13
]
heapSort1 max-heap: 2.402ms
heapSort1 max-heap排序结果: [7, 8, 9, 10, 11, 12, 13]

heapSort2 min-heap原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort2 min-heap:
[
   7,  8,  9, 10,
  11, 12, 13
]
heapSort2 min-heap: 0.103ms
heapSort2 min-heap排序结果: [7, 8, 9, 10, 11, 12, 13]

heapSort3 iterative原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort3 iterative:
[
   7,  8,  9, 10,
  11, 12, 13
]
heapSort3 iterative: 0.22ms
heapSort3 iterative排序结果: [7, 8, 9, 10, 11, 12, 13]

heapSort4 bottom-up原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort4 bottom-up:
[
   7,  8,  9, 10,
  11, 12, 13
]
heapSort4 bottom-up: 0.07ms
heapSort4 bottom-up排序结果: [7, 8, 9, 10, 11, 12, 13]

heapSort5 non-recursive原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort5 non-recursive:
current= 9  idx= 2  child= 5  size= 7
parent sort: 2 [
   7, 11, 13, 10,
  12,  9,  8
]
current= 11  idx= 1  child= 3  size= 7
parent sort: 1 [
   7, 12, 13, 10,
  11,  9,  8
]
current= 7  idx= 0  child= 1  size= 7
current= 7  idx= 2  child= 5  size= 7
parent sort: 0 [
  13, 12, 9, 10,
  11,  7, 8
]
child start: parent=-1  child=6
current= 8  idx= 0  child= 1  size= 6
current= 8  idx= 1  child= 3  size= 6
child sort: 6 [
  12, 11,  9, 10,
   8,  7, 13
]
current= 7  idx= 0  child= 1  size= 5
current= 7  idx= 1  child= 3  size= 5
child sort: 5 [
  11, 10,  9, 7,
   8, 12, 13
]
current= 8  idx= 0  child= 1  size= 4
current= 8  idx= 1  child= 3  size= 4
child sort: 4 [
  10,  8,  9, 7,
  11, 12, 13
]
current= 7  idx= 0  child= 1  size= 3
child sort: 3 [
   9,  8,  7, 10,
  11, 12, 13
]
current= 7  idx= 0  child= 1  size= 2
child sort: 2 [
   8,  7,  9, 10,
  11, 12, 13
]
child sort: 1 [
   7,  8,  9, 10,
  11, 12, 13
]
排序后数组: [7, 8, 9, 10, 11, 12, 13]
heapSort5 non-recursive: 0.461ms
heapSort5 non-recursive排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. heapSort1 max-heap：经典实现，升序排序
2. heapSort2 min-heap：反向思维，直观易懂
3. heapSort3 iterative：避免递归，性能优化
4. heapSort4 bottom-up：高效构建，减少比较
5. heapSort5 non-recursive：非递归堆化，父子节点计算函数
*/