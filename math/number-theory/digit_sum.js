/**
 * Copyright https://github.com/microwind
 * Digit Sum
 */

function digitSum(n) {
    let sum = 0;
    while (n > 0) {
        sum += n % 10;
        n = Math.floor(n / 10);
    }
    return sum;
}

function main() {
    const n = 12345;
    console.log(`Digit sum of ${n} = ${digitSum(n)}`);
}

main();
if (typeof module !== 'undefined') module.exports = { digitSum };
