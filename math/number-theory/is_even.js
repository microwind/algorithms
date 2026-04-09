/**
 * Copyright https://github.com/microwind
 * Check if number is even/odd
 */

function isEven(n) {
    return n % 2 === 0;
}

function main() {
    const testNumbers = [2, 3, 4, 5, 10, 15];
    for (const n of testNumbers) {
        console.log(`${n} is ${isEven(n) ? 'even' : 'odd'}`);
    }
}

main();
if (typeof module !== 'undefined') module.exports = { isEven };
