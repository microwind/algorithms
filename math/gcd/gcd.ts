/**
 * Copyright https://github.com/microwind
 * GCD - Greatest Common Divisor
 */

function gcd(x: number, y: number): number {
    while (y !== 0) {
        const temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

function main(): void {
    console.log("GCD(48, 18) = " + gcd(48, 18));
    console.log("GCD(56, 98) = " + gcd(56, 98));
}

main();
export { gcd };
