/**
 * Copyright https://github.com/microwind
 * Check if number is even/odd
 */

function isEven(n: number): boolean {
    return n % 2 === 0;
}

function main(): void {
    const testNumbers = [2, 3, 4, 5, 10, 15];
    for (const n of testNumbers) {
        console.log(`${n} is ${isEven(n) ? 'even' : 'odd'}`);
    }
}

main();
export { isEven };
