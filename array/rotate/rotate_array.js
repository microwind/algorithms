/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组旋转算法 - JavaScript实现
 * 
 * 算法原理：
 * - 将数组的前d个元素移动到数组末尾
 * - 剩余元素左移填充前面位置
 * - 使用临时数组存储前d个元素
 * 
 * 旋转类型：
 * - 左旋转：元素向左移动，前面的移到后面
 * - 右旋转：元素向右移动，后面的移到前面
 * 
 * 本实现为左旋转（将前d个元素移到末尾）
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(d) - 需要临时存储d个元素
 * 
 * 优化：使用三次反转法可将空间复杂度降至O(1)
 * 
 * 应用场景：
 * - 循环移位
 * - 数据重排
 * - 图像处理中的像素移动
 */

/**
 * 数组左旋转函数
 * 将数组前d个元素移到数组末尾
 * @param {number[]} arr - 待旋转的数组
 * @param {number} d - 旋转位置数（前d个元素移到末尾）
 * @returns {number[]} 旋转后的数组
 */
function rotateArray(arr, d) {
    let n = arr.length;
    // 步骤1：保存前d个元素到临时数组
    let temp = arr.slice(0, d);
    // 步骤2：将剩余元素移到前面，并拼接临时数组
    arr = arr.slice(d).concat(temp);
    return arr;
}

/**
 * 打印数组
 * @param {number[]} arr - 要打印的数组
 */
function printArray(arr) {
    process.stdout.write("[");
    for (let i = 0; i < arr.length; i++) {
        process.stdout.write(arr[i].toString());
        if (i < arr.length - 1) {
            process.stdout.write(", ");
        }
    }
    console.log("]");
}

// 测试代码
let arr = [1, 2, 3, 4, 5, 6, 7];
let d = 3;  // 旋转3位

console.log("Original array: ");
printArray(arr);

arr = rotateArray(arr, d);

console.log(`Rotated array (d=${d}): `);
printArray(arr);

/*
 * 输出结果：
 * Original array: [1, 2, 3, 4, 5, 6, 7]
 * Rotated array (d=3): [4, 5, 6, 7, 1, 2, 3]
 */