/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
var BubbleSort = /** @class */ (function () {
    function BubbleSort(arr) {
        this.bubbleSort1(arr.slice(0));
        this.bubbleSort2(arr.slice(0));
        this.bubbleSort3(arr.slice(0));
    }
    /**
     * 冒泡排序升序，将最大的冒泡到最后
     */
    BubbleSort.prototype.bubbleSort1 = function (arr) {
        var _a;
        console.log('bubbleSort1 from left to right:');
        var len = arr.length;
        for (var i = 0; i < len; i++) {
            for (var j = 0; j < len - i - 1; j++) {
                // 自左往右每两个进行比较，把大的交换到右侧
                // 逐轮冒出最大数，已经排好序的不要再比较
                if (arr[j] > arr[j + 1]) {
                    _a = [arr[j + 1], arr[j]], arr[j] = _a[0], arr[j + 1] = _a[1];
                }
                // console.log('i=' + i, 'j=' + j, arr)
            }
        }
        console.log(arr);
    };
    /**
     * 冒泡排序降序，将最小的冒泡到最后
     */
    BubbleSort.prototype.bubbleSort2 = function (arr) {
        var _a;
        console.log('bubbleSort2 from right to left:');
        var len = arr.length;
        for (var i = 0; i < len; i++) {
            for (var j = len - 1; j > i; j--) {
                // 自右往左每两个进行比较，把小的交换到右侧
                // 逐轮冒出最小数，已经排好序的不要再比较
                if (arr[j - 1] < arr[j]) {
                    _a = [arr[j], arr[j - 1]], arr[j - 1] = _a[0], arr[j] = _a[1];
                }
                // console.log('i=' + i, 'j=' + j, arr)
            }
        }
        console.log(arr);
    };
    /**
     * 冒泡排序升序，增加交换标志，针对有序情况优化
     */
    BubbleSort.prototype.bubbleSort3 = function (arr) {
        var _a;
        console.log('bubbleSort3 add flag:');
        // 增加一个标志，如果某一轮没有进行过任何的交换
        // 则说明当前数组已排好序，则不必继续后面的遍历，
        var len = arr.length;
        var flag = true;
        for (var i = 0; i < len && flag === true; i++) {
            flag = false;
            // console.warn('no. ' + i)
            for (var j = 0; j < len - i - 1; j++) {
                // 自左往右每两个进行比较，把大的交换到右侧
                // 逐轮冒出最大数，已经排好序的不要再比较
                if (arr[j] > arr[j + 1]) {
                    flag = true;
                    _a = [arr[j + 1], arr[j]], arr[j] = _a[0], arr[j + 1] = _a[1];
                }
                // console.log('i=' + i, 'j=' + j, arr)
            }
        }
        console.log(arr);
    };
    return BubbleSort;
}());
;
(function () {
    // test
    var arr = [7, 11, 9, 10, 12, 13, 8];
    console.time('bubbleSort');
    new BubbleSort(arr);
    console.timeEnd('bubbleSort');
})();
/*
jarrys-MacBook-Pro:bubblesort jarry$ tsc BubbleSort.ts -t es2020
jarrys-MacBook-Pro:bubblesort jarry$ node BubbleSort.js
bubbleSort1 from left to right:
[
   7,  8,  9, 10,
  11, 12, 13
]
bubbleSort2 from right to left:
[
  13, 12, 11, 10,
   9,  8,  7
]
bubbleSort3 add flag:
[
   7,  8,  9, 10,
  11, 12, 13
]
bubbleSort: 8.312ms
*/ 
