/**
 * Copyright https://github.com/microwind
 * Approximate Equality Check
 */

function approxEqual(a, b, epsilon) {
    return Math.abs(a - b) < epsilon;
}

function main() {
    console.log("Approximate Equality Check:");
    console.log("0.1 + 0.2 ≈ 0.3:", approxEqual(0.1 + 0.2, 0.3, 1e-10));
}

main();
if (typeof module !== 'undefined') module.exports = { approxEqual };
