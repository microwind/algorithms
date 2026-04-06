/**
 * 递归算法示例集合（基于JavaScript版本）
 * 包含阶乘、递归计算等示例
 */

/**
 * 阶乘递归计算（版本1）
 * @param x 输入数字
 * @returns 阶乘结果
 */
function factorial(x: number): number {
    console.log('x=', x);
    if (x < 1) return 0;
    if (x === 1) return 1;
    // 递归调用：x * (x-1) * (x-2) * ... * 1
    return x * factorial(x - 1);
}

/**
 * 阶乘递归计算（版本2）
 * @param x 输入数字
 * @returns 阶乘结果
 */
function factorial2(x: number): number {
    console.log('x=', x);
    if (x <= 1) return x;
    // 递归调用：x * (x-1) * (x-2) * ... * 1
    return x * factorial2(x - 1);
}

/**
 * 递归计算示例
 * @param n 输入数字
 * @returns 计算结果
 */
function recursion(n: number): number {
    console.log('begin: n=', n);
    if (n >= 15) return n;
    n *= 3;
    // 递归调用：recursion(n + 1) + recursion(n * 2)
    return recursion(n + 1) + recursion(n * 2);
}

/**
 * 递归计算示例2
 * @param n 输入数字
 * @returns 计算结果
 */
function recursion2(n: number): number {
    console.log('begin: n=', n);
    if (n >= 15) return n;
    n *= 3;
    return recursion2(n + 1) - recursion2(n * 2);
}

// 主程序
console.log('factorial(5)', factorial(5));
console.log('recursion(1)=', recursion(1));
console.log('recursion2(1)=', recursion2(1));
