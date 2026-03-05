/*
*
 * 二分查找 - 分治法的查询应用
 *
 * 前置条件：数组必须已排序
 *
 * 时间复杂度: O(log n)
 * 空间复杂度: O(1) 迭代版本，O(log n) 递归版本
*/

/*
*
 * 二分查找（迭代版本）
 * @param {number[]} arr - 已排序的数组
 * @param {number} target - 查找的目标值
 * @returns {number} 目标值的索引，如果不存在返回 -1
*/
function binarySearch(arr, target) {
    let left = 0, right = arr.length - 1;

    // 循环直到左右指针相遇, 找到目标值或确定不存在
    while (left <= right) {
        const mid = Math.floor(left + (right - left) / 2);
        // 检查中间元素是否是目标值
        if (arr[mid] === target) {
            return mid;
        // 如果中间元素小于目标值, 继续在右半部分搜索
        } else if (arr[mid] < target) {
            left = mid + 1;
        // 如果中间元素大于目标值, 继续在左半部分搜索
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

/*
*
 * 二分查找（递归版本）
*/
function binarySearchRecursive(arr, left, right, target) {
    if (left > right) {
        return -1;
    }

    const mid = Math.floor(left + (right - left) / 2);
    // 检查中间元素是否是目标值
    if (arr[mid] === target) {
        return mid;
    } else if (arr[mid] < target) {
        // 如果中间元素小于目标值, 继续在右半部分搜索
        return binarySearchRecursive(arr, mid + 1, right, target);
    } else {
        // 如果中间元素大于目标值, 继续在左半部分搜索
        return binarySearchRecursive(arr, left, mid - 1, target);
    }
}

/*
*
 * 查找第一个 >= target 的元素位置（左边界）
*/
function binarySearchLeft(arr, target) {
    let left = 0, right = arr.length - 1;
    let result = -1;

    while (left <= right) {
        const mid = Math.floor(left + (right - left) / 2);

        if (arr[mid] >= target) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

// 测试函数
console.log("=== 二分查找 ===\n");

const arr = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19];
console.log("数组:", arr);
console.log();

// 测试用例1：迭代版本
console.log("1. 迭代版本:");
console.log("  查找 7:", binarySearch(arr, 7));
console.log("  查找 20:", binarySearch(arr, 20));
console.log();

// 测试用例2：递归版本
console.log("2. 递归版本:");
console.log("  查找 9:", binarySearchRecursive(arr, 0, arr.length - 1, 9));
console.log("  查找 2:", binarySearchRecursive(arr, 0, arr.length - 1, 2));
console.log();

// 测试用例3：查找边界
const arrDup = [1, 2, 2, 2, 3, 4, 5, 5, 5, 6];
console.log("3. 查找边界 (数组:", arrDup, "):");
console.log("  左边界 2:", binarySearchLeft(arrDup, 2));
console.log("  左边界 5:", binarySearchLeft(arrDup, 5));
console.log();

// 测试用例4：查找不存在的元素
console.log("4. 查找不存在的元素:");
console.log("  查找 100:", binarySearch(arr, 100));
console.log("  查找 0:", binarySearch(arr, 0));
