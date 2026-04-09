/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 分治算法示例 - 数组求和
 * 
 * 算法特点：
 * - 分治法将问题分解为子问题
 * - 递归解决子问题后合并结果
 * - 时间复杂度: O(n)，空间复杂度: O(log n)
 * 
 * 学习重点：理解分治算法的递归实现
 */

/**
 * 递归计算数组元素和
 * 时间复杂度: O(n)，空间复杂度: O(log n)
 * @param arr 数组
 * @param left 左边界
 * @param right 右边界
 * @return 数组和
 */
function divideSum(arr: number[], left: number, right: number): number {
    // 基本情况：单个元素
    if (left == right) {
        return arr[left];
    }
    
    // 分治：将数组分成两半
    const mid = Math.floor((left + right) / 2);
    const leftSum = divideSum(arr, left, mid);
    const rightSum = divideSum(arr, mid + 1, right);
    
    // 合并：返回两半的和
    return leftSum + rightSum;
}

/**
 * 主函数 - 测试分治算法
 */
function main(): void {
    // 测试1：数组求和
    const testArray = [1, 2, 3, 4, 5, 6, 7, 8];
    console.log("1. 分治算法 - 数组求和:");
    console.log(`   数组: [${testArray.join(', ')}]`);
    console.log(`   求和结果: ${divideSum(testArray, 0, testArray.length - 1)}`);
    console.log("===");
    
    // 测试2：空数组
    const emptyArray: number[] = [];
    console.log("2. 边界测试 - 空数组:");
    console.log(`   数组: [${emptyArray.join(', ')}]`);
    console.log(`   求和结果: ${emptyArray.length > 0 ? divideSum(emptyArray, 0, emptyArray.length - 1) : 0}`);
    console.log("===");
    
    // 测试3：单个元素
    const singleArray = [42];
    console.log("3. 边界测试 - 单个元素:");
    console.log(`   数组: [${singleArray.join(', ')}]`);
    console.log(`   求和结果: ${divideSum(singleArray, 0, singleArray.length - 1)}`);
    console.log("===");
}

/*打印结果
jarry@Mac divide-conquer % npx ts-node divide.ts
1. 分治算法 - 数组求和:
   数组: [1, 2, 3, 4, 5, 6, 7, 8]
   求和结果: 36
===
2. 边界测试 - 空数组:
   数组: []
   求和结果: 0
===
3. 边界测试 - 单个元素:
   数组: [42]
   求和结果: 42
===
*/

// 运行主函数
main();
