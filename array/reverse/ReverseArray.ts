/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组反转算法 - TypeScript实现
 */

/**
 * 反转数组
 * 算法原理：使用双指针技术，头尾指针向中间移动并交换元素
 * 时间复杂度：O(n) - 只需遍历数组的一半
 * 空间复杂度：O(1) - 原地操作，不使用额外空间
 * @param arr - 待反转的数组
 * @returns 反转后的数组（原数组被修改）
 */
function reverseArray(arr: number[]): number[] {
    let left = 0;
    let right = arr.length - 1;

    // 左右指针向中间移动，交换元素
    while (left < right) {
        // 交换左右指针指向的元素
        [arr[left], arr[right]] = [arr[right], arr[left]];
        left++;
        right--;
    }

    return arr;
}

/**
 * 主函数 - 测试数组反转
 */
function main(): void {
    const arr: number[] = [1, 2, 3, 4, 5];
    console.log("原始数组:", arr);
    reverseArray(arr);
    console.log("反转后数组:", arr);
}

// 执行主函数
main();

/**
 * 输出结果：
 * 原始数组: [ 1, 2, 3, 4, 5 ]
 * 反转后数组: [ 5, 4, 3, 2, 1 ]
 */

export { reverseArray };
