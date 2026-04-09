/**
 * 数学基础 - 幂运算 (Power/Exponentiation)
 */

function power(base, exp) {
    if (exp < 0) return 1.0 / power(base, -exp);
    if (exp === 0) return 1;
    
    let result = 1;
    let current = base;
    let e = exp;
    
    while (e > 0) {
        if (e & 1) result *= current;
        current *= current;
        e >>= 1;
    }
    return result;
}

function powerBigInt(base, exp) {
    const b = BigInt(base);
    let result = 1n;
    let current = b;
    let e = BigInt(exp);
    
    while (e > 0n) {
        if (e & 1n) result *= current;
        current *= current;
        e >>= 1n;
    }
    return result;
}

function powerMod(base, exp, mod) {
    let result = 1 % mod;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

function testPower() {
    console.log("幂运算演示:");
    for (let i = 0; i <= 10; i++) {
        console.log(`2^${i} = ${power(2, i)}`);
    }
    
    console.log("\n大数幂运算:");
    console.log(`2^100 = ${powerBigInt(2, 100)}`);
    
    console.log("\n模幂运算:");
    console.log(`3^100 mod 1000 = ${powerMod(3, 100, 1000)}`);
}

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { power, powerBigInt, powerMod, testPower };
    if (require.main === module) testPower();
} else {
    window.powerModule = { power, powerBigInt, powerMod, testPower };
}
