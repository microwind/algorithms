/**
 * 动态规划记忆化搜索示例
 * 
 * 算法特点：
 * - 使用缓存避免重复计算
 * - 时间复杂度从 O(2^n) 优化到 O(n)
 * 
 * 学习重点：理解记忆化搜索的优化原理
 */

// 记忆化数组
const memo = new Array(100).fill(-1);

/**
 * 初始化记忆化数组
 */
function initMemo() {
    for (let i = 0; i < 100; i++) {
        memo[i] = -1;
    }
}

/**
 * 记忆化版本斐波那契
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param {number} n 要计算的斐波那契数列位置
 * @return {number} 第n个斐波那契数
 */
function fibonacciMemo(n) {
    // 基础情况
    if (n <= 1) return n;
    
    // 如果已计算过，直接返回缓存结果
    if (memo[n] !== -1) {
        return memo[n];
    }
    
    // 递归计算并缓存结果
    memo[n] = fibonacciMemo(n - 1) + fibonacciMemo(n - 2);
    return memo[n];
}

/**
 * 普通递归版本（用于对比）
 * 时间复杂度: O(2^n)，空间复杂度: O(n)
 * @param {number} n 要计算的斐波那契数列位置
 * @return {number} 第n个斐波那契数
 */
function fibonacciNaive(n) {
    if (n <= 1) return n;
    return fibonacciNaive(n - 1) + fibonacciNaive(n - 2);
}

/**
 * 主函数 - 测试记忆化搜索性能对比
 */
function main() {
    const n = 40;
    
    // 测试1：输出对比标题
    console.log(`斐波那契数列对比 (n=${n}):`);
    console.log();
    
    // 测试2：普通递归（很慢）
    console.log("普通递归: ");
    console.log(`F(${n}) = ${fibonacciNaive(n)}`);
    console.log("  （时间复杂度: O(2^n)，有大量重复计算）");
    console.log();
    
    // 测试3：记忆化版本（很快）
    initMemo();
    console.log("记忆化搜索: ");
    console.log(`F(${n}) = ${fibonacciMemo(n)}`);
    console.log("  （时间复杂度: O(n)，每个值只计算一次）");
    console.log();
    
    // 输出性能提升说明
    console.log("性能提升: 从指数级 O(2^n) 降到线性 O(n)");
    console.log("当 n=40 时，普通递归需要约 2^40 ≈ 1万亿次操作");
    console.log("记忆化版本只需要 40 次计算");
}

/*打印结果
jarry@Mac dp-memoization % node fibonacci_memo.js
斐波那契数列对比 (n=40):

普通递归: F(40) = 102334155
  （时间复杂度: O(2^n)，有大量重复计算）

记忆化搜索: F(40) = 102334155
  （时间复杂度: O(n)，每个值只计算一次）

性能提升: 从指数级 O(2^n) 降到线性 O(n)
当 n=40 时，普通递归需要约 2^40 ≈ 1万亿次操作
记忆化版本只需要 40 次计算
*/

// 运行主函数
main();
