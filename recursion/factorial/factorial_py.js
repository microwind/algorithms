/**
 * 阶乘递归示例
 * n! = n × (n-1) × (n-2) × ... × 1
 */

// 方法1: 递归版本
function factorialRecursive(n) {
    /* 递归计算阶乘，O(n) 时间复杂度，O(n) 空间复杂度 */
    if (n <= 1) {
        return 1;
    }
    return n * factorialRecursive(n - 1);
}

// 方法2: 迭代版本
function factorialIterative(n) {
    /* 迭代计算阶乘，O(n) 时间复杂度，O(1) 空间复杂度 */
    let result = 1;
    for (let i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// 方法3: 尾递归
function factorialTail(n, acc = 1) {
    /* 尾递归版本 */
    if (n <= 1) {
        return acc;
    }
    return factorialTail(n - 1, n * acc);
}

// 主程序
function main() {
    console.log("=== 阶乘计算 ===\n");
    
    const testValues = [5, 10, 20];
    
    for (const n of testValues) {
        console.log(`${n}! = ${factorialRecursive(n)}`);
        console.log(`迭代版本: ${n}! = ${factorialIterative(n)}`);
        console.log(`尾递归版本: ${n}! = ${factorialTail(n)}`);
        console.log();
    }
}

main();
