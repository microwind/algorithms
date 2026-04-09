/**
数学算法 - 素数筛 (Sieve of Eratosthenes)
高效找出一定范围内的所有素数
 */

function sieve(n) {
    const isPrime = new Array(n + 1).fill(true);
    isPrime[0] = isPrime[1] = false;
    
    for (let p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            for (let i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }
    
    const primes = [];
    for (let i = 2; i <= n; i++) {
        if (isPrime[i]) primes.push(i);
    }
    console.log("Primes up to " + n + ": " + primes.join(" "));
}

function main() {
    sieve(50);
}

main();
if (typeof module !== 'undefined') module.exports = { sieve };
