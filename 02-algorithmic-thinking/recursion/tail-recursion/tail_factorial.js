/**
 * 本模块展示普通递归与尾递归的区别
 * 1. 普通递归：递归调用后仍有计算操作，需要保留当前栈帧
 * 2. 尾递归：最后一步是递归调用，无后续操作
 */

/**
 * 普通递归计算阶乘
 * @param {number} n - 待计算阶乘的整数
 * @param {number} accumulator - 用于跟踪中间结果
 * @returns {number} 阶乘计算结果
 */
function factorial(n, accumulator) {
    console.log(`\ncurrent number: ${n}, accumulator: ${accumulator}`);
    
    // 递归终止条件
    if (n <= 1) {
        return 1;
    }
    
    // 递归调用后还有乘法操作，不是尾递归
    return n * factorial(n - 1, n * accumulator);
}

/**
 * 尾递归计算阶乘
 * @param {number} n - 待计算阶乘的整数
 * @param {number} accumulator - 累加器，用于存储中间计算结果
 * @returns {number} 阶乘计算结果
 */
function tailFactorial(n, accumulator) {
    console.log(`\ncurrent number: ${n}, accumulator: ${accumulator}`);
    
    // 递归终止条件
    if (n <= 1) {
        return accumulator;
    }
    
    // 最后一步是递归调用，无其他操作，符合尾递归特征
    return tailFactorial(n - 1, n * accumulator);
}

/**
 * 尾递归包装函数，提供更友好的接口
 * @param {number} n - 待计算阶乘的整数
 * @returns {number} 阶乘计算结果
 */
function factorialTail(n) {
    return tailFactorial(n, 1);
}

// 测试普通递归
const startTime = performance.now();
console.log(`\nfactorial(5) result: ${factorial(5, 1)}`);
const elapsedTime = performance.now() - startTime;
console.log(`time: ${elapsedTime.toFixed(6)} ms.`);

// 测试尾递归
const startTime2 = performance.now();
console.log("\n===============");
console.log(`\nfactorialTail(5) result: ${factorialTail(5)}`);
const elapsedTime2 = performance.now() - startTime2;
console.log(`time: ${elapsedTime2.toFixed(6)} ms.`);

/*
jarry@Mac tail-recursion % node tail_factorial.js 

current number: 5, accumulator: 1

current number: 4, accumulator: 5

current number: 3, accumulator: 20

current number: 2, accumulator: 60

current number: 1, accumulator: 120

factorial(5) result: 120
time: 4.365833 ms.

===============

current number: 5, accumulator: 1

current number: 4, accumulator: 5

current number: 3, accumulator: 20

current number: 2, accumulator: 60

current number: 1, accumulator: 120

factorialTail(5) result: 120
time: 0.709042 ms.
*/
