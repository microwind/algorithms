/**
 * Copyright https://github.com/microwind
 * Fibonacci Sequence
 */

function fibonacci(n: number): number {
    if (n <= 1) return n;
    let first = 0, second = 1, result = 0;
    for (let i = 1; i < n; i++) {
        result = first + second;
        first = second;
        second = result;
    }
    return result;
}

function main(): void {
    console.log("Fibonacci Sequence:");
    for (let i = 0; i <= 10; i++) {
        console.log(`F(${i}) = ${fibonacci(i)}`);
    }
}

main();
export { fibonacci };
