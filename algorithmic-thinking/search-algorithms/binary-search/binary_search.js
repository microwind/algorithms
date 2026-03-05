/*
 * 二分搜索（Binary Search）- JavaScript 版本
 *
 * 前置条件：数组必须按升序排序。
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1) 迭代版
 */

// 迭代版二分搜索：返回任意一个等于 target 的下标，未找到返回 -1
function binarySearchIterative(arr, target) {
  let left = 0;
  let right = arr.length - 1;

  while (left <= right) {
    const mid = Math.floor((left + right) / 2);
    if (arr[mid] === target) {
      return mid;
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}

// 递归版二分搜索
function binarySearchRecursive(arr, target, left = 0, right = arr.length - 1) {
  if (left > right) return -1;
  const mid = Math.floor((left + right) / 2);
  if (arr[mid] === target) return mid;
  if (arr[mid] < target) return binarySearchRecursive(arr, target, mid + 1, right);
  return binarySearchRecursive(arr, target, left, mid - 1);
}

// 查找第一个等于 target 的位置（左边界）
function findFirstOccurrence(arr, target) {
  let left = 0;
  let right = arr.length - 1;
  let result = -1;
  while (left <= right) {
    const mid = Math.floor((left + right) / 2);
    if (arr[mid] === target) {
      result = mid;
      right = mid - 1; // 继续向左收缩
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return result;
}

// 查找最后一个等于 target 的位置（右边界）
function findLastOccurrence(arr, target) {
  let left = 0;
  let right = arr.length - 1;
  let result = -1;
  while (left <= right) {
    const mid = Math.floor((left + right) / 2);
    if (arr[mid] === target) {
      result = mid;
      left = mid + 1; // 继续向右收缩
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return result;
}

// 查找插入位置（lower bound）
function findInsertPosition(arr, target) {
  let left = 0;
  let right = arr.length;
  while (left < right) {
    const mid = Math.floor((left + right) / 2);
    if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left;
}

// 简单演示
if (require.main === module) {
  console.log("========== Binary Search (JavaScript) ==========");
  const arr = [1, 3, 5, 7, 9, 11, 13];
  console.log("数组:", arr);
  console.log("查找 7 ->", binarySearchIterative(arr, 7));
  console.log("递归查找 7 ->", binarySearchRecursive(arr, 7));

  const arr2 = [1, 3, 5, 5, 5, 7, 9];
  console.log("\n数组2:", arr2);
  console.log("第一个 5 的位置 ->", findFirstOccurrence(arr2, 5));
  console.log("最后一个 5 的位置 ->", findLastOccurrence(arr2, 5));
  console.log("插入 6 的位置 ->", findInsertPosition(arr2, 6));
}

module.exports = {
  binarySearchIterative,
  binarySearchRecursive,
  findFirstOccurrence,
  findLastOccurrence,
  findInsertPosition,
};

