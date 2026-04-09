/**
 * Copyright https://github.com/microwind
 * Fast Power (Binary Exponentiation)
 */

function fastPower(base: number, exponent: number, mod: number): number {
    let result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result;
}

function main(): void {
    console.log("2^10 = " + fastPower(2, 10, 1000000007));
    console.log("3^5 = " + fastPower(3, 5, 1000000007));
}

main();
export { fastPower };
