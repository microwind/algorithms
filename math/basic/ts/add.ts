function add(a: number, b: number): number {
    const result = a + b;
    if (!Number.isSafeInteger(result)) {
        throw new Error("加法溢出");
    }
    return result;
}

function safeAdd(a: number, b: number): { result: number; overflow: boolean } {
    const result = a + b;
    const overflow = !Number.isSafeInteger(result);
    return { result, overflow };
}

function bigAdd(a: bigint, b: bigint): bigint {
    return a + b;
}

function testAdd(): void {
    console.log("加法运算:");
    console.log(`5 + 3 = ${add(5, 3)}`);
    console.log(`100 + 200 = ${add(100, 200)}`);
    console.log(`BigInt: 9007199254740992n + 1n = ${bigAdd(9007199254740992n, 1n)}`);
}

testAdd();
export { add, safeAdd, bigAdd, testAdd };
