/**
 * Copyright https://github.com/microwind
 * Approximate Equality Check
 */

function approxEqual(a: number, b: number, epsilon: number): boolean {
    return Math.abs(a - b) < epsilon;
}

function main(): void {
    console.log("Approximate Equality Check:");
    console.log("0.1 + 0.2 ≈ 0.3:", approxEqual(0.1 + 0.2, 0.3, 1e-10));
}

main();
export { approxEqual };
