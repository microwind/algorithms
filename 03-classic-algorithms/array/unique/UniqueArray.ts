/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// the multi method for array unique
// JavaScript数组去重的N种方法
class UniqueArray {
  arr: Array<any>;
  constructor(arr: Array<any>) {
    this.arr = arr;
  }
  // 1. new array
  unique1() {
    console.time("time");
    var arr = this.arr.slice(0);
    var newArr = [];
    for (var i = 0, l = arr.length; i < l; i++) {
      for (var j = 0; j <= i; j++) {
        if (arr[i] === arr[j]) {
          if (i === j) {
            newArr.push(arr[i]);
          }
          break;
        }
      }
    }
    console.log("new array result:", newArr);
    console.timeEnd("time");
  }

  unique2() {
    // 2. new array + indexOf
    console.time("time");
    var arr = this.arr.slice(0);
    var newArr = [];
    for (var i = 0, l = arr.length; i < l; i++) {
      if (newArr.indexOf(arr[i]) < 0) {
        newArr.push(arr[i]);
      }
    }
    console.log("new array + indexOf:", newArr);
    console.timeEnd("time");
  }

  unique3() {
    // 3. new array + includes
    console.time("time");
    var arr = this.arr.slice(0);
    var newArr = [];
    for (var i = 0, l = arr.length; i < l; i++) {
      if (!newArr.includes(arr[i])) {
        newArr.push(arr[i]);
      }
    }
    console.log("new array + includes:", newArr);
    console.timeEnd("time");
  }

  unique4() {
    // 4. one array last -> first
    console.time("time");
    var arr = this.arr.slice(0);
    var l = arr.length;
    while (l-- > 0) {
      for (var i = 0; i < l; i++) {
        if (arr[l] === arr[i]) {
          arr.splice(l, 1);
          break;
        }
      }
    }
    console.log("one array last -> first result:", arr);
    console.timeEnd("time");
  }

  unique5() {
    // 5. one array last -> first from right
    console.time("time");
    var arr = this.arr.slice(0);
    var l = arr.length;
    var i = 0;
    while (l-- > 0) {
      i = l;
      while (i-- > 0) {
        if (arr[l] === arr[i]) {
          arr.splice(l, 1);
          break;
        }
      }
    }
    console.log("one array last -> first from right:", arr);
    console.timeEnd("time");
  }

  unique6() {
    // 6. one array first -> last
    console.time("time");
    var arr = this.arr.slice(0);
    var l = arr.length;
    for (var i = 0; i < l; i++) {
      for (var j = i + 1; j < l; j++) {
        if (arr[i] === arr[j]) {
          arr.splice(j, 1);
          l--;
          i--;
          break;
        }
      }
    }
    console.log("one array first -> last result:", arr);
    console.timeEnd("time");
  }

  unique7() {
    // 7. forEach + indexOf
    console.time("time");
    var arr = this.arr.slice(0);
    var newArr = [];
    for (var i = 0, l = arr.length; i < l; i++) {
      if (i === arr.indexOf(arr[i])) {
        newArr.push(arr[i]);
      } else if (arr.indexOf(arr[i]) >= 0) {
        // break same item
        continue;
      }
    }
    console.log("forEach + indexOf result:", newArr);
    console.timeEnd("time");
  }

  unique8() {
    // 8. filter + indexOf
    console.time("time");
    var arr = this.arr.slice(0);
    console.log(
      "filter + indexOf: ",
      arr.filter((item, i) => i === arr.indexOf(item))
    );
    console.timeEnd("time");
  }

  unique9() {
    // 9. Array.from object
    console.time("time");
    var arr = this.arr.slice(0);
    var obj = {};
    arr.forEach((item) => {
      obj[item] = item;
    });
    console.log("Array.from object:", Array.from(Object.values(obj)));
    console.timeEnd("time");
  }

  unique10() {
    // 10. Array.from Map
    console.time("time");
    var arr = this.arr.slice(0);
    var map = new Map();
    arr.forEach((item, i) => {
      map.set(item, item);
    });
    console.log("Array.from Map:", Array.from(map.values()));
    console.timeEnd("time");
  }

  unique11() {
    // 11. from Set
    console.time("time");
    var arr = this.arr.slice(0);
    var set = new Set(arr);
    console.log("from Set:", Array.from(set));
    console.timeEnd("time");
  }

  unique12() {
    // 12. sort+remove
    console.time("time");
    var arr = this.arr.slice(0);
    arr.sort();
    var l = arr.length;
    while (l-- > 1) {
      if (arr[l] === arr[l - 1]) {
        arr.splice(l, 1);
      }
    }
    console.log("sort+remove:", arr);
    console.timeEnd("time");
  }

  unique13() {
    // 13. sort+remove ASE
    console.time("time");
    var arr = this.arr.slice(0);
    arr.sort((a, b) => {
      return a.toString() > b.toString() ? 1 : -1;
    });
    var l = arr.length;
    for (var i = 0; i < l - 1; i++) {
      if (arr[i] === arr[i + 1]) {
        arr.splice(i, 1);
        l--;
        i--;
      }
    }
    console.log("sort+remove ASE:", arr);
    console.timeEnd("time");
  }

  unique14() {
    // 14. from reduce
    console.time("time");
    var arr = this.arr.slice(0);
    var newArr = arr.reduce((result, item) => {
      if (!Array.isArray(result)) {
        result = [result]
      }
      return result.includes(item) ? result : [...result].concat(item);
    });
    console.log("from reduce:", newArr);
    console.timeEnd("time");
  }

  unique15() {
    // 15. indexOf + new Array push
    console.time("time");
    var arr = this.arr.slice(0);
    var newArr = [];
    for (var i = 0, l = arr.length; i < l; i++) {
      var item = arr[i];
      if (newArr.indexOf(item) < 0) {
        newArr.push(item);
      }
    }
    console.log("new Array push:", newArr);
    console.timeEnd("time");
  }

  unique16() {
    // 16. filter+hasOwnProperty
    console.time("time");
    var arr = this.arr.slice(0);
    var obj = {};
    arr = arr.filter((item) => {
      return obj.hasOwnProperty(typeof item + item)
        ? false
        : (obj[typeof item + item] = true);
    });
    console.log("filter+hasOwnProperty:", arr);
    console.timeEnd("time");
  }

  recursionUnique(arr: Array<number>, len: number) {
    // 17. recursion
    console.time("time");
    if (len <= 1) {
      return arr;
    }
    var l = len;
    var last = l - 1;
    var isRepeat = false;
    while (l-- > 1) {
      if (arr[last] === arr[l - 1]) {
        isRepeat = true;
        break;
      }
    }
    if (isRepeat) {
      arr.splice(last, 1);
    }
    return this.recursionUnique(arr, len - 1);
  }

  recursionUniqueNew(arr: Array<number>, len: number) {
    // 18. recursionUniqueNew
    console.time("time");
    if (len <= 1) {
      return arr;
    }
    var l = len;
    var last = l - 1;
    var lastItem = arr[last];
    var isRepeat = false;
    var result = [];
    while (l-- > 1) {
      if (lastItem === arr[l - 1]) {
        isRepeat = true;
        break;
      }
    }
    arr.splice(last);
    if (!isRepeat) {
      result.push(lastItem);
    }
    return this.recursionUniqueNew(arr, len - 1).concat(result);
  }
}

(function () {
  var arr = [1, 1, 3, -1, 1, 2, 2, 4, 2, 2, -1];
  const unique = new UniqueArray(arr);
  console.log("begin to test:\n");
  for (var i = 1; i <= 16; i++) {
    unique["unique" + i]();
  }

  console.log("recursionUnique:", unique.recursionUnique(arr.slice(0), arr.length));
  console.timeEnd("time");

  console.log(
    "recursionUniqueNew:",
    unique.recursionUniqueNew(arr.slice(0), arr.length)
  );
  console.timeEnd("time");
})();

/**
jarrys-MacBook-Pro:unique jarry$ tsc UniqueArray.ts -t es2020
jarrys-MacBook-Pro:unique jarry$ node UniqueArray.js
begin to test:

new array result: [ 1, 3, -1, 2, 4 ]
time: 2.387ms
new array + indexOf: [ 1, 3, -1, 2, 4 ]
time: 0.197ms
new array + includes: [ 1, 3, -1, 2, 4 ]
time: 0.209ms
one array last -> first result: [ 1, 3, -1, 2, 4 ]
time: 0.064ms
one array last -> first from right: [ 1, 3, -1, 2, 4 ]
time: 0.054ms
one array first -> last result: [ 1, 3, -1, 2, 4 ]
time: 0.052ms
forEach + indexOf result: [ 1, 3, -1, 2, 4 ]
time: 0.059ms
filter + indexOf:  [ 1, 3, -1, 2, 4 ]
time: 0.076ms
Array.from object: [ 1, 2, 3, 4, -1 ]
time: 0.278ms
Array.from Map: [ 1, 3, -1, 2, 4 ]
time: 0.302ms
from Set: [ 1, 3, -1, 2, 4 ]
time: 0.274ms
sort+remove: [ -1, 1, 2, 3, 4 ]
time: 0.552ms
sort+remove ASE: [ -1, 1, 2, 3, 4 ]
time: 0.114ms
from reduce: [ 1, 3, -1, 2, 4 ]
time: 0.429ms
new Array push: [ 1, 3, -1, 2, 4 ]
time: 0.078ms
filter+hasOwnProperty: [ 1, 3, -1, 2, 4 ]
time: 0.282ms
recursionUnique: [ 1, 3, -1, 2, 4 ]
time: 0.049ms
recursionUniqueNew: [ 1, 3, -1, 2, 4 ]
time: 0.051ms
*/
