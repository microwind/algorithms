/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
/**
 * 归并排序 ，采用分而治之(divide - conquer)的步骤
 * 1. 分解（Divide），把待排序元素的序列分解为两个子序列，以中间2分, 每个子序列包括一半成员。
 * 2. 解决（Conquer），对每个子序列分别调用归并操作, 进行递归或非递归循环操作，完成内部排序。
 * 3. 合并（Combine），合并两个排好序的子序列，生成排序结果。 归并排序的最坏时间复杂度和平均时间复杂度均为O(nlogn)
 */
var MergeSort = /** @class */ (function () {
    function MergeSort() {
    }
    MergeSort.prototype.merge = function (arr, left, mid, right) {
        // 先建立一个长度等于原数组的临时数组
        var temp = [];
        // 左侧指针
        var i = left;
        // 右侧指针
        var j = mid + 1;
        // 临时数组指针
        var k = 0;
        // 当左指针小于中间，且右指针不大于最右侧时
        while (i <= mid && j <= right) {
            // 如果左侧小于右侧，将数移到临时数组中左侧
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
                // 否则移动到临时数组右侧
            }
            else {
                temp[k++] = arr[j++];
            }
        }
        // 如果左边数组还有数据，就把左侧剩余都放入到原数组后面
        while (i <= mid) {
            temp[k++] = arr[i++];
        }
        // 如果右侧数组还有数据，把剩下的数据放入到原数组后面
        while (j <= right) {
            temp[k++] = arr[j++];
        }
        // 将排序后的元素全部移动到原数组中
        var x = 0;
        while (left <= right) {
            arr[left++] = temp[x++];
        }
        console.log("arr:", arr);
    };
    MergeSort.prototype.mergeSort = function (arr, left, right) {
        // 得到中间值
        var mid = Math.floor((left + right) / 2);
        // 如果左侧小于右侧则执行合并排序
        if (left < right) {
            // 递归合并左侧
            this.mergeSort(arr, left, mid);
            // 递归合并右侧
            this.mergeSort(arr, mid + 1, right);
            // 合并排序
            this.merge(arr, left, mid, right);
        }
        return arr;
    };
    return MergeSort;
}());
(function () {
    var arr = [7, 11, 9, 10, 12, 13, 8, -2, 0, 8];
    console.time("sort");
    console.log("origin:", arr);
    var mergeSort = new MergeSort();
    console.log("\r\nsorted:", mergeSort.mergeSort(arr, 0, arr.length - 1));
    console.timeEnd("sort");
})();
/**
jarry@jarrys-mbp mergesort % tsc MergeSort.ts -m es2020
jarry@jarrys-mbp mergesort % node MergeSort.js
origin: [ 7, 11, 9, 10, 12, 13, 8, -2, 0, 8 ]
arr: [ 7, 11, 9, 10, 12, 13, 8, -2, 0, 8 ]
arr: [ 7, 9, 11, 10, 12, 13, 8, -2, 0, 8 ]
arr: [ 7, 9, 11, 10, 12, 13, 8, -2, 0, 8 ]
arr: [ 7, 9, 10, 11, 12, 13, 8, -2, 0, 8 ]
arr: [ 7, 9, 10, 11, 12, 8, 13, -2, 0, 8 ]
arr: [ 7, 9, 10, 11, 12, -2, 8, 13, 0, 8 ]
arr: [ 7, 9, 10, 11, 12, -2, 8, 13, 0, 8 ]
arr: [ 7, 9, 10, 11, 12, -2, 0, 8, 8, 13 ]
arr: [ -2, 0, 7, 8, 8, 9, 10, 11, 12, 13 ]

sorted: [ -2, 0, 7, 8, 8, 9, 10, 11, 12, 13 ]
sort: 4.897ms
 */ 
