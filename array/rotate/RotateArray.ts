/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组旋转算法 - TypeScript实现
 */

/**
 * 翻转数组的指定区间
 * @param arr - 待翻转的数组
 * @param start - 起始索引
 * @param end - 结束索引
 */
function reverse(arr: number[], start: number, end: number): void {
    while (start < end) {
        [arr[start], arr[end]] = [arr[end], arr[start]];
        start++;
        end--;
    }
}

/**
 * 向右旋转数组k个位置
 * 算法原理：三次翻转法
 *   1. 翻转整个数组
 *   2. 翻转前k个元素
 *   3. 翻转后n-k个元素
 * 时间复杂度：O(n) - 三次线性遍历
 * 空间复杂度：O(1) - 原地操作
 * @param arr - 待旋转的数组
 * @param k - 旋转位数
 * @returns 旋转后的数组
 */
function rotateArray(arr: number[], k: number): number[] {
    const n = arr.length;
    if (n === 0) return arr;

    // 处理k大于数组长度的情况
    k = k % n;
    if (k === 0) return arr;

    // 三次翻转法
    reverse(arr, 0, n - 1);     // 翻转整个数组
    reverse(arr, 0, k - 1);     // 翻转前k个
    reverse(arr, k, n - 1);     // 翻转后n-k个

    return arr;
}

/**
 * 向左旋转数组k个位置
 * @param arr - 待旋转的数组
 * @param k - 旋转位数
 * @returns 旋转后的数组
 */
function rotateArrayLeft(arr: number[], k: number): number[] {
    const n = arr.length;
    if (n === 0) return arr;

    k = k % n;
    if (k === 0) return arr;

    // 向左旋转k位等价于向右旋转n-k位
    return rotateArray(arr, n - k);
}

/**
 * 主函数 - 测试数组旋转
 */
function main(): void {
    let arr1: number[] = [1, 2, 3, 4, 5, 6, 7];
    console.log("原始数组:", [...arr1]);
    rotateArray(arr1, 3);
    console.log("向右旋转3位:", arr1);

    let arr2: number[] = [1, 2, 3, 4, 5, 6, 7];
    rotateArrayLeft(arr2, 3);
    console.log("向左旋转3位:", arr2);
}

// 执行主函数
main();

/**
 * 输出结果：
 * 原始数组: [ 1, 2, 3, 4, 5, 6, 7 ]
 * 向右旋转3位: [ 5, 6, 7, 1, 2, 3, 4 ]
 * 向左旋转3位: [ 4, 5, 6, 7, 1, 2, 3 ]
 */

export { rotateArray, rotateArrayLeft };
