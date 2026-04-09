function sqrtNewton(n: number, epsilon: number = 1e-10): number {
    if (n < 0) throw new Error("不能计算负数的平方根");
    if (n === 0) return 0;
    
    let x = n;
    while (Math.abs(x * x - n) > epsilon) {
        x = (x + n / x) / 2.0;
    }
    return x;
}

function sqrtInteger(n: number): number {
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

function testSqrt(): void {
    console.log("平方根计算:");
    const testValues = [1, 2, 4, 9, 16, 25, 100];
    testValues.forEach(n => {
        const result = sqrtNewton(n);
        console.log(`sqrt(${n}) = ${result.toFixed(10)}`);
    });
}

testSqrt();
export { sqrtNewton, sqrtInteger, testSqrt };
