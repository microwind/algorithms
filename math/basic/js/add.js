/**
 * 数学基础 - 加法运算 (Addition)
 * 安全加法，溢出检测
 */

function add(a, b) {
    const result = a + b;
    if (!Number.isSafeInteger(result)) {
        throw new Error("加法溢出");
    }
    return result;
}

function safeAdd(a, b) {
    if (Number.MAX_SAFE_INTEGER - a < b) {
        throw new Error("加法溢出");
    }
    return a + b;
}

function bigAdd(a, b) {
    return BigInt(a) + BigInt(b);
}

function testAdd() {
    console.log("加法运算演示:");
    console.log(`5 + 3 = ${add(5, 3)}`);
    console.log(`100 + 200 = ${add(100, 200)}`);
    console.log(`BigInt: 9007199254740992n + 1n = ${bigAdd(9007199254740992, 1)}`);
}

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { add, safeAdd, bigAdd, testAdd };
    if (require.main === module) testAdd();
} else {
    window.addModule = { add, safeAdd, bigAdd, testAdd };
}
