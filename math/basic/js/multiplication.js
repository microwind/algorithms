/**
 * 数学基础 - 乘法运算 (Multiplication)
 */

function multiply(a, b) {
    return a * b;
}

function safeMultiply(a, b) {
    const result = a * b;
    if (!Number.isSafeInteger(result)) {
        throw new Error("乘法溢出");
    }
    return result;
}

function multiplyBigInt(a, b) {
    return BigInt(a) * BigInt(b);
}

function powerOfTwoMultiply(a, power) {
    return a << power;
}

function testMultiplication() {
    console.log("乘法运算演示:");
    console.log(`12 × 8 = ${multiply(12, 8)}`);
    console.log(`100 × 25 = ${multiply(100, 25)}`);
    console.log(`7 << 3 (7 × 8) = ${powerOfTwoMultiply(7, 3)}`);
    console.log(`BigInt: 9007199254740992n × 2n = ${multiplyBigInt(9007199254740992, 2)}`);
}

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { multiply, safeMultiply, multiplyBigInt, powerOfTwoMultiply, testMultiplication };
    if (require.main === module) testMultiplication();
} else {
    window.multiplicationModule = { multiply, safeMultiply, multiplyBigInt, powerOfTwoMultiply, testMultiplication };
}
