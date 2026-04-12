/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组数据结构 - TypeScript实现
 */

// 定义一个包含5个整数的数组
let arr: number[] = [1, 2, 3, 4, 5];

// 访问数组元素
console.log("Element at index 2:", arr[2]);

// 修改数组元素
arr[2] = 10;
console.log("Modified element at index 2:", arr[2]);

// 遍历数组
let output = "";
for (const value of arr) {
  output += value + " ";
}
console.log(output.trim());

/*
 * 输出结果：
 * Element at index 2: 3
 * Modified element at index 2: 10
 * 1 2 10 4 5
 */
