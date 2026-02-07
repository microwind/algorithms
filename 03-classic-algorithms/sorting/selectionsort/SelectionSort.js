/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
var SelectionSort = /** @class */ (function () {
    function SelectionSort() {
    }
    // 标准版
    SelectionSort.prototype.selectionSort1 = function (arr) {
        var min, minIdx, tmp;
        var l = arr.length;
        for (var i = 0; i < l - 1; i++) {
            min = arr[i];
            minIdx = i;
            var j = i + 1;
            for (; j < l; j++) {
                // 从待排序列表找到最小值和位置
                if (arr[j] < min) {
                    min = arr[j];
                    minIdx = j;
                }
            }
            console.log('i=' + i, ' j=' + j, 'min=' + min, 'minIdx=' + minIdx, 'arr[]=', arr);
            // 将待排序里最小值交换到已排序最后面
            if (minIdx !== i) {
                tmp = arr[i];
                arr[i] = min;
                arr[minIdx] = tmp;
            }
        }
        return arr;
    };
    // 新建数组版，无需交换
    SelectionSort.prototype.selectionSort2 = function (arr) {
        var min, minIdx, newArr = [];
        var l = arr.length;
        for (var i = 0; i < l; i++) {
            min = arr[i];
            minIdx = i;
            var j = i + 1;
            for (; j < l; j++) {
                // 找到并记录下最小值和位置
                if (arr[j] < min) {
                    min = arr[j];
                    minIdx = j;
                }
            }
            console.log('i=' + i, ' j=' + j, 'min=' + min, 'minIdx=' + minIdx, 'arr[]=', arr);
            // 将待排序里最小值添加到新数组中去
            newArr.push(min);
            // 原数组中删除对应的项
            arr.splice(minIdx, 1);
            l--;
            i--;
        }
        return newArr;
    };
    return SelectionSort;
}());
;
(function () {
    var selectionSort = new SelectionSort();
    var arr1 = [7, 11, -9, 10, -12, 13, 8];
    console.time('sort1');
    console.log('origin arr1:', arr1);
    console.log('\r\narr1 sorted:', selectionSort.selectionSort1(arr1));
    console.timeEnd('sort1');
    var arr2 = [7, 11, -9, 10, -12, 13, 8];
    console.time('sort2');
    console.log('origin arr2:', arr2);
    console.log('\r\narr2 sorted:', selectionSort.selectionSort1(arr2));
    console.timeEnd('sort2');
})();
/**
jarrys-MacBook-Pro:selectionsort jarry$ tsc SelectionSort.ts -m es6
jarrys-MacBook-Pro:selectionsort jarry$ node SelectionSort.js
origin: [ 7, 11, 9, 10, 12, 13, 8 ]
i=0  j=7 min=7 minIdx=0 arr[]= [ 7, 11, 9, 10, 12, 13, 8 ]
i=1  j=7 min=8 minIdx=6 arr[]= [ 7, 11, 9, 10, 12, 13, 8 ]
i=2  j=7 min=9 minIdx=2 arr[]= [ 7, 8, 9, 10, 12, 13, 11 ]
i=3  j=7 min=10 minIdx=3 arr[]= [ 7, 8, 9, 10, 12, 13, 11 ]
i=4  j=7 min=11 minIdx=6 arr[]= [ 7, 8, 9, 10, 12, 13, 11 ]
i=5  j=7 min=12 minIdx=6 arr[]= [ 7, 8, 9, 10, 11, 13, 12 ]
time: 1.027ms

sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 5.681ms
 */
