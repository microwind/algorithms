// 递归分解数组，最小粒度为2个
let step = 0;

function divide(arr) {
  // 如果数组剩余1个或0个则无法继续分解
  console.log('start:', arr);
  const len = arr.length;
  if (len < 2) {
    return arr;
  }
  const mid = Math.round(len / 2);
  let left = arr.slice(0, mid);
  let right = arr.slice(mid);
  left = divide(left);  // 递归分解左半部分
  right = divide(right);  // 递归分解右半部分
  step += 1;
  console.log('after:', step + '->', arr, left, right);
  return left.concat(right);  // 合并左右部分
}

divide([3, 1, 2, 5, 6, 4]);

/*
           f([3, 1, 2, 5, 6, 4])
              /             \
          f([3, 1, 2])    f([5, 6, 4])
          /        \         /        \
      f([3, 1])   f([2])  f([5, 6]), f([4])
      /     \              /      \
  f([3])    f([1])      f([5]) f([6])
*/

/*
jarry@MacBook-Pro recursion % node divide.js
start: [ 3, 1, 2, 5, 6, 4 ]
start: [ 3, 1, 2 ]
start: [ 3, 1 ]
start: [ 3 ]
start: [ 1 ]
after: 1-> [ 3, 1 ] [ 3 ] [ 1 ]
start: [ 2 ]
after: 2-> [ 3, 1, 2 ] [ 3, 1 ] [ 2 ]
start: [ 5, 6, 4 ]
start: [ 5, 6 ]
start: [ 5 ]
start: [ 6 ]
after: 3-> [ 5, 6 ] [ 5 ] [ 6 ]
start: [ 4 ]
after: 4-> [ 5, 6, 4 ] [ 5, 6 ] [ 4 ]
after: 5-> [ 3, 1, 2, 5, 6, 4 ] [ 3, 1, 2 ] [ 5, 6, 4 ]
*/