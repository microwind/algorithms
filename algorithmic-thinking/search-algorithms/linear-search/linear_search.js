/*
 * 线性搜索（Linear Search）- JavaScript 版本
 *
 * 适用场景：
 * - 小规模数组
 * - 无序数据
 * - 只需要简单查找，不追求极致性能
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

/**
 * 在线性表中查找第一个等于目标值的元素下标
 * @param {any[]} arr - 待搜索数组
 * @param {any} target - 目标值
 * @returns {number} 找到时的下标，未找到返回 -1
 */
function linearSearch(arr, target) {
  for (let i = 0; i < arr.length; i++) {
    if (arr[i] === target) {
      return i;
    }
  }
  return -1;
}

/**
 * 查找数组中所有等于目标值的下标
 * @param {any[]} arr
 * @param {any} target
 * @returns {number[]} 所有匹配下标构成的数组
 */
function linearSearchAll(arr, target) {
  const indices = [];
  for (let i = 0; i < arr.length; i++) {
    if (arr[i] === target) {
      indices.push(i);
    }
  }
  return indices;
}

// 简单演示
if (require.main === module) {
  console.log("========== Linear Search (JavaScript) ==========");
  const arr = [5, 2, 8, 1, 9, 3, 7];
  console.log("数组:", arr);
  console.log("查找 8 ->", linearSearch(arr, 8));
  console.log("查找 10 ->", linearSearch(arr, 10));
  const arr2 = [1, 2, 3, 2, 4, 2];
  console.log("数组2:", arr2);
  console.log("查找所有 2 ->", linearSearchAll(arr2, 2));
}

module.exports = { linearSearch, linearSearchAll };

