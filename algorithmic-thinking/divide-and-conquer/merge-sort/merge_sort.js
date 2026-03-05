/*
*
 * 归并排序 - 分治法的典型应用
 *
 * 分治法三个步骤：
 * 1. 分解：将数组分成两个子数组
 * 2. 求解：递归对子数组进行归并排序
 * 3. 合并：将两个已排序的子数组合并
 *
 * 时间复杂度: O(n log n)
 * 空间复杂度: O(n)
*/

/*
*
 * 合并两个已排序的数组
 * @param {number[]} arr - 原数组
 * @param {number} left - 左侧起始位置
 * @param {number} mid - 中间位置
 * @param {number} right - 右侧结束位置
*/
function merge(arr, left, mid, right) {
    // 创建临时数组
    const temp = new Array(right - left + 1);

    let i = left;
    let j = mid + 1;
    let k = 0;

    // 比较两个子数组的元素
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // 复制左侧剩余元素
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // 复制右侧剩余元素
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // 将临时数组复制回原数组
    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
}

/*
*
 * 递归进行归并排序
 * @param {number[]} arr - 待排序数组
 * @param {number} left - 起始位置
 * @param {number} right - 结束位置
*/
function mergeSortHelper(arr, left, right) {
    if (left < right) {
        const mid = Math.floor(left + (right - left) / 2);

        // 递归排序左半部分
        mergeSortHelper(arr, left, mid);

        // 递归排序右半部分
        mergeSortHelper(arr, mid + 1, right);

        // 合并两个已排序的部分
        merge(arr, left, mid, right);
    }
}

/*
*
 * 归并排序入口函数
 * @param {number[]} arr - 待排序数组
*/
function mergeSort(arr) {
    if (!arr || arr.length <= 1) {
        return arr;
    }
    mergeSortHelper(arr, 0, arr.length - 1);
    return arr;
}

// 测试函数
console.log("=== 归并排序 ===\n");

// 测试用例1：随机数组
let arr1 = [64, 34, 25, 12, 22, 11, 90];
console.log("原数组:", arr1);
mergeSort(arr1);
console.log("排序后:", arr1);
console.log();

// 测试用例2：已排序数组
let arr2 = [1, 2, 3, 4, 5];
console.log("已排序数组:", arr2);
mergeSort(arr2);
console.log("排序后:", arr2);
console.log();

// 测试用例3：反序数组
let arr3 = [5, 4, 3, 2, 1];
console.log("反序数组:", arr3);
mergeSort(arr3);
console.log("排序后:", arr3);
console.log();

// 测试用例4：包含重复元素
let arr4 = [3, 1, 4, 1, 5, 9, 2, 6];
console.log("包含重复:", arr4);
mergeSort(arr4);
console.log("排序后:", arr4);
