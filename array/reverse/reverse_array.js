/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组反转算法 - JavaScript实现
 * 
 * 算法原理：
 * - 使用双指针技术，交换数组首尾元素
 * - 向中间移动指针，继续交换，直到相遇
 * - 只需遍历数组的一半，时间复杂度O(n/2) = O(n)
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(1) - 仅使用一个临时变量
 * 
 * 应用场景：
 * - 字符串反转
 * - 回文检查
 * - 数据预处理
 */

/**
 * 反转数组
 * 使用双指针法，从数组两端向中间交换元素
 * @param {number[]} arr - 待反转的数组
 * @returns {number[]} 反转后的数组
 */
function reverseArray(arr) {
    let n = arr.length;
    // 交换数组的前后元素，只需要遍历数组的前一半
    for (let i = 0; i < n / 2; i++) {
        // 使用解构赋值交换两个元素的值
        [arr[i], arr[n - i - 1]] = [arr[n - i - 1], arr[i]];
    }
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
let arr = [1, 2, 3, 4, 5];

console.log("反转前的数组: ");
printArray(arr);

reverseArray(arr);

console.log("反转后的数组: ");
printArray(arr);

/*
 * 输出结果：
 * 反转前的数组: [1, 2, 3, 4, 5]
 * 反转后的数组: [5, 4, 3, 2, 1]
 */