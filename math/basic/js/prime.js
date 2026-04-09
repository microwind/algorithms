/**
 * 数学基础 - 素数判定与生成 (Prime Numbers)
 * 判断素数并生成素数表
 * 时间复杂度: O(√n) - 试除法, O(n log log n) - 筛法
 */

/**
 * 试除法判断素数
 * 
 * 时间复杂度: O(√n)
 */
function isPrime(n) {
    if (n < 2) return false;
    if (n === 2) return true;
    if (n % 2 === 0) return false;
    
    for (let i = 3; i * i <= n; i += 2) {
        if (n % i === 0) return false;
    }
    return true;
}

/**
 * 优化的素数判断（6k±1形式）
 */
function isPrimeOptimized(n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 === 0 || n % 3 === 0) return false;
    
    for (let i = 5; i * i <= n; i += 6) {
        if (n % i === 0 || n % (i + 2) === 0) return false;
    }
    return true;
}

/**
 * 埃拉托斯特尼筛法
 * 
 * 时间复杂度: O(n log log n)
 */
function sieveOfEratosthenes(limit) {
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

/**
 * 获取素数列表
 */
function getPrimes(limit) {
    const sieve = sieveOfEratosthenes(limit);
    const primes = [];
    for (let i = 2; i <= limit; i++) {
        if (sieve[i]) primes.push(i);
    }
    return primes;
}

/**
 * 素因数分解
 */
function primeFactorization(n) {
    const factors = [];
    let d = 2;
    while (d * d <= n) {
        while (n % d === 0) {
            factors.push(d);
            n /= d;
        }
        d++;
    }
    if (n > 1) factors.push(n);
    return factors;
}

/**
 * Miller-Rabin素性测试（概率算法）
 */
function isProbablePrime(n, k = 5) {
    if (n < 2) return false;
    if (n === 2 || n === 3) return true;
    if (n % 2 === 0) return false;
    
    // 写成 n-1 = d * 2^r
    let d = n - 1;
    let r = 0;
    while (d % 2 === 0) {
        d /= 2;
        r++;
    }
    
    // 测试轮数
    for (let i = 0; i < k; i++) {
        const a = Math.floor(Math.random() * (n - 3)) + 2;
        let x = modPow(a, d, n);
        
        if (x === 1 || x === n - 1) continue;
        
        let continueOuter = false;
        for (let j = 0; j < r - 1; j++) {
            x = modPow(x, 2, n);
            if (x === n - 1) {
                continueOuter = true;
                break;
            }
        }
        
        if (continueOuter) continue;
        return false;
    }
    
    return true;
}

/**
 * 模幂运算
 */
function modPow(base, exp, mod) {
    let result = 1 % mod;
    base = base % mod;
    while (exp > 0) {
        if ((exp & 1) === 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

/**
 * 素数计数 π(n)
 */
function countPrimes(n) {
    if (n < 2) return 0;
    const sieve = sieveOfEratosthenes(n);
    return sieve.filter(Boolean).length - 2; // 减去索引0和1
}

/**
 * 第n个素数（估算）
 */
function nthPrime(n) {
    // 使用素数定理估算上界
    let limit = n < 6 ? 15 : Math.floor(n * (Math.log(n) + Math.log(Math.log(n)))) + 10;
    const primes = getPrimes(limit);
    return primes[n - 1];
}

/**
 * 测试函数
 */
function testPrime() {
    console.log("==================================================");
    console.log("    素数判定与生成 (Prime Numbers)");
    console.log("==================================================\n");
    
    // 100以内的素数
    console.log("100以内的素数:");
    console.log("--------------------------------------------------");
    const primes100 = getPrimes(100);
    for (let i = 0; i < primes100.length; i++) {
        process.stdout.write(`${primes100[i].toString().padStart(3)} `);
        if ((i + 1) % 10 === 0) console.log();
    }
    console.log(`\n共 ${primes100.length} 个素数\n`);
    
    // 素数判定
    console.log("素数判定测试:");
    console.log("--------------------------------------------------");
    const testNumbers = [1, 2, 3, 4, 17, 18, 97, 541, 1009];
    testNumbers.forEach(n => {
        const result = isPrimeOptimized(n) ? "是素数" : "不是素数";
        console.log(`${n.toString().padStart(6)} ${result}`);
    });
    
    // 素因数分解
    console.log("\n==================================================");
    console.log("素因数分解:");
    console.log("==================================================");
    const numbersToFactor = [12, 100, 360, 1001, 2024];
    numbersToFactor.forEach(n => {
        const factors = primeFactorization(n);
        const factorStr = factors.join(" × ");
        console.log(`${n.toString().padStart(6)} = ${factorStr}`);
    });
    
    // 素数计数
    console.log("\n==================================================");
    console.log("素数计数 π(n):");
    console.log("==================================================");
    [10, 100, 1000, 10000].forEach(n => {
        const count = countPrimes(n);
        const approx = n / Math.log(n);
        console.log(`π(${n.toString().padStart(6)}) = ${count.toString().padStart(6)} (近似: ${approx.toFixed(1)})`);
    });
    
    // 数学性质
    console.log("\n==================================================");
    console.log("数学性质:");
    console.log("==================================================");
    console.log("• 素数定理: π(n) ~ n/ln(n)");
    console.log("• 欧几里得定理: 素数有无穷多个");
    console.log("• 唯一分解定理: 每个整数可唯一表示为素数乘积");
}

// 导出模块
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        isPrime, isPrimeOptimized,
        sieveOfEratosthenes, getPrimes,
        primeFactorization,
        isProbablePrime,
        countPrimes, nthPrime,
        testPrime
    };
    
    if (require.main === module) {
        testPrime();
    }
} else {
    window.primeModule = {
        isPrime, isPrimeOptimized,
        sieveOfEratosthenes, getPrimes,
        primeFactorization,
        isProbablePrime,
        countPrimes, nthPrime,
        testPrime
    };
}
