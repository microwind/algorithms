function isPrime(n: number): boolean {
    if (n < 2) return false;
    if (n === 2) return true;
    if (n % 2 === 0) return false;
    for (let i = 3; i * i <= n; i += 2) {
        if (n % i === 0) return false;
    }
    return true;
}

function sieveOfEratosthenes(limit: number): boolean[] {
    const isPrime = new Array(limit + 1).fill(true);
    isPrime[0] = isPrime[1] = false;
    for (let p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {
            for (let multiple = p * p; multiple <= limit; multiple += p) {
                isPrime[multiple] = false;
            }
        }
    }
    return isPrime;
}

function testPrime(): void {
    console.log("100以内的素数:");
    const primes: number[] = [];
    for (let i = 2; i <= 100; i++) {
        if (isPrime(i)) primes.push(i);
    }
    console.log(primes.join(", "));
}

testPrime();
export { isPrime, sieveOfEratosthenes, testPrime };
