/**
 * 数学基础 - 斐波那契数列 (Fibonacci Sequence)
 */

function fibonacciIterative(n) {
    if (n < 0) throw new Error("n必须非负");
    if (n <= 1) return n;
    let a = 0n, b = 1n;
    for (let i = 2; i <= n; i++) {
        const temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

function fibonacciMatrix(n) {
    if (n < 0) throw new Error("n必须非负");
    if (n <= 1) return BigInt(n);
    
    function multiply(a, b) {
        return [
            [a[0][0]*b[0][0] + a[0][1]*b[1][0], a[0][0]*b[0][1] + a[0][1]*b[1][1]],
            [a[1][0]*b[0][0] + a[1][1]*b[1][0], a[1][0]*b[0][1] + a[1][1]*b[1][1]]
        ];
    }
    
    let result = [[1n, 0n], [0n, 1n]];
    let base = [[1n, 1n], [1n, 0n]];
    let power = n - 1;
    
    while (power > 0) {
        if (power & 1n) result = multiply(result, base);
        base = multiply(base, base);
        power >>= 1n;
    }
    return result[0][0];
}

function testFibonacci() {
    console.log("斐波那契数列前20项:");
    for (let i = 0; i < 20; i++) {
        process.stdout.write(`F(${i}) = ${fibonacciIterative(i).toString().padStart(5)}  `);
        if ((i + 1) % 4 === 0) console.log();
    }
    
    console.log("\n\n大数计算:");
    for (const n of [50n, 100n, 200n]) {
        const fib = fibonacciMatrix(n);
        console.log(`F(${n}) 的位数: ${fib.toString().length}`);
    }
}

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { fibonacciIterative, fibonacciMatrix, testFibonacci };
    if (require.main === module) testFibonacci();
} else {
    window.fibonacciModule = { fibonacciIterative, fibonacciMatrix, testFibonacci };
}
