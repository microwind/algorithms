/**
 * Copyright https://github.com/microwind
 * Prime Number Check
 */

function isPrime(n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 === 0 || n % 3 === 0) return false;
    for (let i = 5; i * i <= n; i += 6) {
        if (n % i === 0 || n % (i + 2) === 0) return false;
    }
    return true;
}

function main() {
    const primes = [];
    for (let i = 1; i <= 50; i++) {
        if (isPrime(i)) primes.push(i);
    }
    console.log("Primes up to 50:", primes.join(" "));
}

main();
if (typeof module !== 'undefined') module.exports = { isPrime };
