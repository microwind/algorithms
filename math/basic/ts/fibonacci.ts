function fibonacciIterative(n: number): bigint {
    if (n < 0) throw new Error("n必须非负");
    if (n <= 1) return BigInt(n);
    let a = 0n, b = 1n;
    for (let i = 2; i <= n; i++) {
        const temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

function fibonacciMatrix(n: number): bigint {
    if (n < 0) throw new Error("n必须非负");
    if (n <= 1) return BigInt(n);
    
    function multiply(a: bigint[][], b: bigint[][]): bigint[][] {
        return [
            [a[0][0]*b[0][0] + a[0][1]*b[1][0], a[0][0]*b[0][1] + a[0][1]*b[1][1]],
            [a[1][0]*b[0][0] + a[1][1]*b[1][0], a[1][0]*b[0][1] + a[1][1]*b[1][1]]
        ];
    }
    
    let result: bigint[][] = [[1n, 0n], [0n, 1n]];
    let base: bigint[][] = [[1n, 1n], [1n, 0n]];
    let power = n - 1;
    
    while (power > 0) {
        if (power & 1) result = multiply(result, base);
        base = multiply(base, base);
        power >>= 1;
    }
    return result[0][0];
}

function testFibonacci(): void {
    console.log("斐波那契数列前20项:");
    for (let i = 0; i < 20; i++) {
        process.stdout.write(`F(${i}) = ${fibonacciIterative(i).toString()}  `);
        if ((i + 1) % 3 === 0) console.log();
    }
}

testFibonacci();
export { fibonacciIterative, fibonacciMatrix, testFibonacci };
