/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
// 1. 希尔排序，基于插入排序进行了分组排序
var ShellSort = /** @class */ (function () {
    function ShellSort() {
    }
    ShellSort.prototype.shellSort1 = function (arr) {
        var len = arr.length;
        // 设置分组增量值（步长）为1/2的数组长度
        var gap = Math.floor(len / 2);
        // 根据步长得到子序列，如果间隔大于0，则表示还可以继续分组
        while (gap > 0) {
            for (var i = 0; i < len; i++) {
                var current = arr[i];
                var j = i;
                // 对子序列按照插入排序
                while (j >= gap && current < arr[j - gap]) {
                    console.log('gap=' + gap + ' i=' + i + ' j=' + j + ' (j - gap)=' + (j - gap), 'arr:', arr);
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                // 交换当前项
                arr[j] = current;
            }
            // 调整步长为1/2
            gap = Math.floor(gap / 2);
        }
        return arr;
    };
    /* 2. 希尔排序，基于插入排序进行分组排序，步长按3倍递减。 */
    ShellSort.prototype.shellSort2 = function (arr) {
        var len = arr.length;
        var gap = 1;
        // 初始步长按3倍递增，小于1/3数组长度
        while (gap < Math.floor(len / 3)) {
            gap = gap * 3 + 1;
        }
        // 根据步长得到子序列，如果间隔大于0，则表示还可以继续分组
        while (gap > 0) {
            for (var i = gap; i < len; i++) {
                var current = arr[i];
                var j = i - gap;
                // 对子序列按照插入排序
                for (; j >= 0 && arr[j] > current; j -= gap) {
                    console.log('gap=' + gap + ' i=' + i + ' j=' + j + ' (j + gap)=' + (j + gap), 'arr:', arr);
                    arr[j + gap] = arr[j];
                }
                arr[j + gap] = current;
            }
            // 步长按3倍缩减
            gap = Math.floor(gap / 3);
        }
        return arr;
    };
    return ShellSort;
}());
;
(function () {
    var shellSort = new ShellSort();
    var arr1 = [33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431];
    console.time('shellSort1');
    console.log('origin shellSort1:', arr1);
    console.log('shellSort1 sorted:', shellSort.shellSort1(arr1));
    console.timeEnd('shellSort1');
    var arr2 = [33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431];
    console.time('shellSort2');
    console.log('origin shellSort2:', arr2);
    console.log('shellSort2 sorted:', shellSort.shellSort2(arr2));
    console.timeEnd('shellSort2');
})();
/*
jarry@jarrys-MacBook-Pro shellsort % tsc ShellSort.ts -t es2020
jarry@jarrys-MacBook-Pro shellsort % node ShellSort.js
origin shellSort1: [
     33,      4,  15,
     43, 323454,  -7,
   10.5,   1235, 200,
  87431
]
gap=5 left=0 right=5 sub_arr= [ 33, 4, 15, 43, 323454 ]
gap=5 left=4 right=9 sub_arr= [ 323454, 33, 10.5, 1235, 200 ]
gap=2 left=3 right=5 sub_arr= [ 43, 87431 ]
gap=2 left=4 right=6 sub_arr= [ 87431, 43 ]
gap=2 left=2 right=4 sub_arr= [ 15, 33 ]
gap=2 left=6 right=8 sub_arr= [ 87431, 1235 ]
gap=1 left=3 right=4 sub_arr= [ 33 ]
shellSort1 sorted: [
      -7,    4,  10.5,
      15,   33,    43,
     200, 1235, 87431,
  323454
]
shellSort1: 9.868ms
origin shellSort2: [
     33,      4,  15,
     43, 323454,  -7,
   10.5,   1235, 200,
  87431
]
gap=4 left=1 right=5 sub_arr= [ 4, 15, 43, 323454 ]
gap=4 left=2 right=6 sub_arr= [ 15, 43, 323454, 4 ]
gap=4 left=4 right=8 sub_arr= [ 323454, 4, 15, 1235 ]
gap=1 left=0 right=1 sub_arr= [ 33 ]
gap=1 left=1 right=2 sub_arr= [ 33 ]
gap=1 left=4 right=5 sub_arr= [ 200 ]
gap=1 left=3 right=4 sub_arr= [ 43 ]
gap=1 left=2 right=3 sub_arr= [ 33 ]
gap=1 left=1 right=2 sub_arr= [ 10.5 ]
gap=1 left=5 right=6 sub_arr= [ 200 ]
gap=1 left=4 right=5 sub_arr= [ 43 ]
gap=1 left=3 right=4 sub_arr= [ 33 ]
gap=1 left=8 right=9 sub_arr= [ 323454 ]
shellSort2 sorted: [
      -7,    4,  10.5,
      15,   33,    43,
     200, 1235, 87431,
  323454
]
shellSort2: 1.761ms
*/
