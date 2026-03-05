/*
 * 随机快速排序（Randomized QuickSort）- JavaScript 版本
 *
 * 核心思想：
 * - 与普通快速排序相同的分治结构
 * - 但在每次分区时随机选择枢轴（pivot），避免「最坏输入」导致 O(n²)
 *
 * 平均时间复杂度：O(n log n)
 * 最坏时间复杂度：O(n²)（概率极低）
 * 空间复杂度：O(log n) 递归栈
 */

/**
 * 原地分区：随机选择一个枢轴，并将数组划分为「<= pivot」和「> pivot」两部分
 * @param {number[]} arr
 * @param {number} left
 * @param {number} right
 * @returns {number} 枢轴最终所在的下标
 */
function randomizedPartition(arr, left, right) {
  // 在 [left, right] 中随机选择一个下标作为枢轴
  const randomIdx = left + Math.floor(Math.random() * (right - left + 1));
  // 将随机枢轴元素交换到最右侧
  [arr[randomIdx], arr[right]] = [arr[right], arr[randomIdx]];

  const pivot = arr[right];
  let i = left - 1;

  for (let j = left; j < right; j++) {
    if (arr[j] <= pivot) {
      i++;
      [arr[i], arr[j]] = [arr[j], arr[i]];
    }
  }

  [arr[i + 1], arr[right]] = [arr[right], arr[i + 1]];
  return i + 1;
}

/**
 * 随机快速排序（原地排序）
 * @param {number[]} arr
 * @param {number} [left]
 * @param {number} [right]
 * @returns {number[]} 排序后的同一个数组
 */
function randomizedQuickSort(arr, left = 0, right = arr.length - 1) {
  if (left < right) {
    const pivotIdx = randomizedPartition(arr, left, right);
    randomizedQuickSort(arr, left, pivotIdx - 1);
    randomizedQuickSort(arr, pivotIdx + 1, right);
  }
  return arr;
}

/**
 * 随机选择（QuickSelect）- 平均 O(n) 找到第 k 小元素
 * @param {number[]} arr
 * @param {number} k 第 k 小（0-based）
 */
function randomizedSelect(arr, k, left = 0, right = arr.length - 1) {
  if (left === right) return arr[left];

  const pivotIdx = randomizedPartition(arr, left, right);
  if (k === pivotIdx) {
    return arr[k];
  } else if (k < pivotIdx) {
    return randomizedSelect(arr, k, left, pivotIdx - 1);
  } else {
    return randomizedSelect(arr, k, pivotIdx + 1, right);
  }
}

// 简单演示
if (require.main === module) {
  console.log("========== Randomized QuickSort (JavaScript) ==========");

  const arr = [5, 2, 8, 1, 9, 3, 7, 4, 6];
  console.log("原数组:", arr);
  console.log("排序后:", randomizedQuickSort([...arr]));

  const k = 3;
  const arr2 = [...arr];
  const kth = randomizedSelect(arr2, k);
  console.log(`第 ${k} 小的元素:`, kth);
}

module.exports = { randomizedQuickSort, randomizedSelect };

