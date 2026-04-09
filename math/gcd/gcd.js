/**
 * Copyright https://github.com/microwind
 * GCD - Greatest Common Divisor
 */

function gcd(x, y) {
    while (y !== 0) {
        const temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

function main() {
    console.log("GCD(48, 18) = " + gcd(48, 18));
    console.log("GCD(56, 98) = " + gcd(56, 98));
}

main();
if (typeof module !== 'undefined') module.exports = { gcd };
