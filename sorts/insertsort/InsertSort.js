/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
var InsertSort = /** @class */ (function () {
    function InsertSort(arr) {
        this.insertSort1(arr.slice(0));
        this.insertSort2(arr.slice(0));
        this.insertSort3(arr.slice(0));
        this.insertSort4(arr.slice(0));
        this.insertSort5(arr.slice(0));
        this.arr = this.insertSort6(arr);
    }
    /**
     * 插入排序标准版
     */
    InsertSort.prototype.insertSort1 = function (arr) {
        console.time('time');
        var j, current, l = arr.length;
        // 外循环用于遍历待排序区间，内循环用来遍历已排序区间
        for (var i = 0; i < l; i++) {
            j = i;
            current = arr[i];
            // 将该项自右往左与已排序项逐个对比，当遇到比自己大的项(表示升序)时，将该位置右移
            // 直到遇到小于等于自己的项则停止移动，表示插入成功
            // console.log(
            //   'i=' + i,
            //   ' j=' + j,
            //   'current=' + current,
            //   'arr[i]=' + arr[i],
            //   'arr[j]=' + arr[j],
            //   'arr[]=',
            //   arr
            // )
            while (j-- > 0 && current < arr[j]) {
                // 逐个位移
                arr[j + 1] = arr[j];
            }
            // 交换为当前项
            arr[j + 1] = current;
        }
        console.log('sort1:', arr);
        console.timeEnd('time');
        return arr;
    };
    /**
     * 插入排序标准版2，j递减时机不同
     */
    InsertSort.prototype.insertSort2 = function (arr) {
        console.time('time');
        var j, current, l = arr.length;
        for (var i = 0; i < l; i++) {
            j = i - 1;
            current = arr[i];
            // console.log(
            //   'i=' + i,
            //   ' j=' + j,
            //   'current=' + current,
            //   'arr[i]=' + arr[i],
            //   'arr[j+1]=' + arr[j + 1],
            //   'arr[]=',
            //   arr
            // )
            while (j >= 0 && current < arr[j]) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = current;
        }
        console.log('sort2:', arr);
        console.timeEnd('time');
        return arr;
    };
    /**
     * 插入排序splice版本
     */
    InsertSort.prototype.insertSort3 = function (arr) {
        console.time('time');
        var j, current, l = arr.length, isMin;
        for (var i = 1; i < l; i++) {
            j = i - 1;
            current = arr.splice(i, 1)[0];
            isMin = true;
            while (j >= 0) {
                if (current > arr[j]) {
                    // console.log(
                    //   'i=' + i,
                    //   ' j=' + j,
                    //   'current=' + current,
                    //   'arr[i]=' + arr[i],
                    //   'arr[j]=' + arr[j],
                    //   'arr[]=',
                    //   arr
                    // )
                    // 利用splice插入
                    arr.splice(j + 1, 0, current);
                    isMin = false;
                    break;
                }
                j--;
            }
            if (isMin) {
                arr.splice(0, 0, current);
            }
        }
        console.log('sort3:', arr);
        console.timeEnd('time');
        return arr;
    };
    /**
     * 插入排序新建数组+splice版
     */
    InsertSort.prototype.insertSort4 = function (arr) {
        console.time('time');
        var j, len, l = arr.length, isMax;
        var newArr = arr.slice(0, 1);
        for (var i = 1; i < l; i++) {
            isMax = true;
            for (var j_1 = 0, len_1 = newArr.length; j_1 < len_1; j_1++) {
                // console.log(
                //   'i=' + i,
                //   ' j=' + j,
                //   'arr[i]=' + arr[i],
                //   'newArr[j]=' + newArr[j],
                //   'arr[]=',
                //   arr
                // )
                if (arr[i] < newArr[j_1]) {
                    // 新建数组来插入到某个位置中
                    newArr.splice(j_1, 0, arr[i]);
                    isMax = false;
                    break;
                }
            }
            if (isMax) {
                newArr.push(arr[i]);
            }
        }
        console.warn('sort4 newArr:', newArr);
        console.timeEnd('time');
        return newArr;
    };
    /**
     * 插入排序新建数组版倒序遍历
     */
    InsertSort.prototype.insertSort5 = function (arr) {
        console.time('time');
        var l = arr.length, len, isMin;
        var newArr = arr.slice(0, 1);
        for (var i = 1; i < l; i++) {
            isMin = true;
            len = newArr.length;
            while (len--) {
                // console.log(
                //   'i=' + i,
                //   ' len=' + len,
                //   'arr[i]=' + arr[i],
                //   'newArr[len]=' + newArr[len],
                //   'arr[]=',
                //   arr
                // )
                if (arr[i] > newArr[len]) {
                    newArr.splice(len + 1, 0, arr[i]);
                    isMin = false;
                    break;
                }
            }
            if (isMin) {
                newArr.unshift(arr[i]);
            }
        }
        console.warn('sort5 newArr:', newArr);
        console.timeEnd('time');
        return newArr;
    };
    /**
     * 插入排序新建数组版挪动插入版
     */
    InsertSort.prototype.insertSort6 = function (arr) {
        console.time('time');
        var len = arr.length;
        var newArr = [arr[0]];
        for (var i = 1; i < len; i++) {
            var l = newArr.length;
            while (l--) {
                if (arr[i] < newArr[l]) {
                    newArr[l + 1] = newArr[l];
                    if (l === 0) {
                        newArr[0] = arr[i];
                    }
                }
                else {
                    newArr[l + 1] = arr[i];
                    break;
                }
            }
        }
        console.log('sort6:', arr);
        console.timeEnd('time');
        return newArr;
    };
    return InsertSort;
}());
;
(function () {
    var arr = [7, 11, 9, 10, 12, 13, 8];
    console.time('sort-all');
    console.log('origin:', arr);
    console.log('\r\nsorted:', new InsertSort(arr).arr);
    console.timeEnd('sort-all');
})();
/**
jarrys-mbp:insertsort jarry$ tsc InsertSort.ts -t es6
jarrys-mbp:insertsort jarry$ node InsertSort.js
origin: [
   7, 11, 9, 10,
  12, 13, 8
]
sort1: [
   7,  8,  9, 10,
  11, 12, 13
]
time: 0.274ms
sort2: [
   7,  8,  9, 10,
  11, 12, 13
]
time: 0.264ms
sort3: [
   7,  8,  9, 10,
  11, 12, 13
]
time: 0.163ms
sort4 newArr: [
   7,  8,  9, 10,
  11, 12, 13
]
time: 3.699ms
sort5 newArr: [
   7,  8,  9, 10,
  11, 12, 13
]
time: 0.121ms
sort6: [
   7, 11, 9, 10,
  12, 13, 8
]
time: 0.128ms

sorted: [
   7,  8,  9, 10,
  11, 12, 13
]
sort-all: 13.866ms
*/
