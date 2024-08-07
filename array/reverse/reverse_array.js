// 反转数组的函数
function reverseArray(arr) {
  let n = arr.length;
  // 交换数组的前后元素
  for (let i = 0; i < n / 2; i++) {
      [arr[i], arr[n - i - 1]] = [arr[n - i - 1], arr[i]];
  }
}

let arr = [1, 2, 3, 4, 5]; // 初始化数组
reverseArray(arr); // 调用反转函数
console.log(arr); // 输出反转后的数组