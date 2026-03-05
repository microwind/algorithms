/*
*
 * 快速排序 - 分治法的高效应用
 *
 * 分治法三个步骤：
 * 1. 分解：选择一个基准元素，将数组分为三部分
 * 2. 求解：递归对左右两部分进行快速排序
 * 3. 合并：基准元素已经在最终位置，无需额外合并
 *
 * 时间复杂度: O(n log n) 平均，O(n²) 最坏
 * 空间复杂度: O(log n)
*/

/*
*
 * 分割函数：使用 Hoare 分割方案
 * @param {number[]} arr - 数组
 * @param {number} low - 起始位置
 * @param {number} high - 结束位置
 * @returns {number} 分割点位置
*/
function partition(arr, low, high) {
    const pivot = arr[high];
    let i = low - 1;

    // 遍历数组，将小于基准的元素放到左边, 大于基准的元素放到右边
    for (let j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            // 交换 arr[i] 和 arr[j]
            [arr[i], arr[j]] = [arr[j], arr[i]];
        }
    }

    // 交换 arr[i+1] 和 arr[high]
    [arr[i + 1], arr[high]] = [arr[high], arr[i + 1]];

    return i + 1;
}

/*
*
 * 递归进行快速排序
 * @param {number[]} arr - 数组
 * @param {number} low - 起始位置
 * @param {number} high - 结束位置
*/
function quickSortHelper(arr, low, high) {
    if (low < high) {
        // 分割
        const pi = partition(arr, low, high);

        // 递归排序左右两部分
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

/*
*
 * 快速排序入口函数
 * @param {number[]} arr - 待排序数组
 * @returns {number[]} 排序后的数组
*/
function quickSort(arr) {
    if (!arr || arr.length <= 1) {
        return arr;
    }
    quickSortHelper(arr, 0, arr.length - 1);
    return arr;
}

// 测试函数
console.log("=== 快速排序 ===\n");

// 测试用例1：随机数组
let arr1 = [64, 34, 25, 12, 22, 11, 90];
console.log("原数组:", arr1);
quickSort(arr1);
console.log("排序后:", arr1);
console.log();

// 测试用例2：已排序数组
let arr2 = [1, 2, 3, 4, 5];
console.log("已排序数组:", arr2);
quickSort(arr2);
console.log("排序后:", arr2);
console.log();

// 测试用例3：反序数组
let arr3 = [5, 4, 3, 2, 1];
console.log("反序数组:", arr3);
quickSort(arr3);
console.log("排序后:", arr3);
console.log();

// 测试用例4：包含重复元素
let arr4 = [3, 1, 4, 1, 5, 9, 2, 6];
console.log("包含重复:", arr4);
quickSort(arr4);
console.log("排序后:", arr4);
