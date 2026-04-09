/**
 * Copyright https://github.com/microwind
 * Digit Sum
 */

function digitSum(n: number): number {
    let sum = 0;
    while (n > 0) {
        sum += n % 10;
        n = Math.floor(n / 10);
    }
    return sum;
}

function main(): void {
    const n = 12345;
    console.log(`Digit sum of ${n} = ${digitSum(n)}`);
}

main();
export { digitSum };
