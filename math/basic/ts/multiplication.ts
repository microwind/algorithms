function multiply(a: number, b: number): number {
    return a * b;
}

function safeMultiply(a: number, b: number): { result: number; overflow: boolean } {
    const result = a * b;
    const overflow = !Number.isSafeInteger(result);
    return { result, overflow };
}

function multiplyBigInt(a: bigint, b: bigint): bigint {
    return a * b;
}

function testMultiplication(): void {
    console.log("乘法运算:");
    console.log(`12 × 8 = ${multiply(12, 8)}`);
    console.log(`100 × 25 = ${multiply(100, 25)}`);
    console.log(`BigInt: 9007199254740992n × 2n = ${multiplyBigInt(9007199254740992n, 2n)}`);
}

testMultiplication();
export { multiply, safeMultiply, multiplyBigInt, testMultiplication };
