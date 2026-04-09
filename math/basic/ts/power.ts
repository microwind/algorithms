function power(base: number, exp: number): number {
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

function powerBigInt(base: bigint, exp: number): bigint {
    let result = 1n;
    let current = base;
    let e = exp;
    
    while (e > 0) {
        if (e & 1) result *= current;
        current *= current;
        e >>= 1;
    }
    return result;
}

function powerMod(base: number, exp: number, mod: number): number {
    let result = 1 % mod;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

function testPower(): void {
    console.log("幂运算:");
    for (let i = 0; i <= 10; i++) {
        console.log(`2^${i} = ${power(2, i)}`);
    }
    console.log(`\n3^100 mod 1000 = ${powerMod(3, 100, 1000)}`);
}

testPower();
export { power, powerBigInt, powerMod, testPower };
