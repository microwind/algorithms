// 旋转数组
function rotateArray(arr, d) {
  let n = arr.length;
  let temp = arr.slice(0, d);
  arr = arr.slice(d).concat(temp);
  return arr;
}

let arr = [1, 2, 3, 4, 5, 6, 7];
let d = 2;
arr = rotateArray(arr, d);
console.log("Rotated array:", arr);

/**
jarry@jarrys-MacBook-Pro rotate % node rotate_array.js
Rotated array: [
  3, 4, 5, 6,
  7, 1, 2
]
 */