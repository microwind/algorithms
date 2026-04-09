/**
 * 数学基础 - 平方根计算 (Square Root)
 */

function sqrtNewton(n, epsilon = 1e-10) {
    if (n < 0) throw new Error("不能计算负数的平方根");
    if (n === 0) return 0;
    
    let x = n;
    while (Math.abs(x * x - n) > epsilon) {
        x = (x + n / x) / 2.0;
    }
    return x;
}

function sqrtInteger(n) {
    if (n < 0) throw new Error("不能计算负数的平方根");
    if (n < 2) return n;
    
    let left = 1, right = n >> 1;
    while (left <= right) {
        const mid = (left + right) >> 1;
        const square = mid * mid;
        if (square === n) return mid;
        if (square < n) left = mid + 1;
        else right = mid - 1;
    }
    return right;
}

function testSqrt() {
    console.log("牛顿迭代法求平方根:");
    const testValues = [1, 2, 4, 9, 16, 25, 100, 10000];
    testValues.forEach(n => {
        const result = sqrtNewton(n);
        console.log(`sqrt(${n}) = ${result.toFixed(10)} (Math.sqrt: ${Math.sqrt(n)})`);
    });
    
    console.log("\n整数平方根:");
    [1, 2, 4, 8, 9, 15, 16, 25].forEach(n => {
        console.log(`isqrt(${n}) = ${sqrtInteger(n)}`);
    });
}

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { sqrtNewton, sqrtInteger, testSqrt };
    if (require.main === module) testSqrt();
} else {
    window.sqrtModule = { sqrtNewton, sqrtInteger, testSqrt };
}
