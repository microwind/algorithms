/**
 * 数学基础 - 阶乘计算 (Factorial)
 * 计算非负整数的阶乘 n!
 * 支持递归、迭代和大数计算
 * 时间复杂度: O(n)
 */

/**
 * 迭代计算阶乘
 * 
 * 算法原理：
 * - n! = 1 × 2 × 3 × ... × n
 * - 0! = 1（空积的定义）
 * 
 * 参数:
 *     n: 非负整数（n ≤ 170，避免Infinity）
 * 返回:
 *     n! 的结果
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
function factorialIterative(n) {
    if (n < 0) throw new Error("n必须非负");
    if (n > 170) throw new Error("n太大，会导致Infinity");
    
    let result = 1;
    for (let i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

/**
 * 递归计算阶乘
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(n) - 递归栈
 */
function factorialRecursive(n) {
    if (n < 0) throw new Error("n必须非负");
    if (n <= 1) return 1;
    return n * factorialRecursive(n - 1);
}

/**
 * 尾递归优化版本
 */
function factorialTailRecursive(n, accumulator = 1) {
    if (n <= 1) return accumulator;
    return factorialTailRecursive(n - 1, n * accumulator);
}

/**
 * BigInt阶乘计算（ES2020+）
 * 
 * 可以计算任意大的阶乘
 */
function factorialBigInt(n) {
    if (n < 0) throw new Error("n必须非负");
    
    let result = 1n;
    for (let i = 2n; i <= BigInt(n); i++) {
        result *= i;
    }
    return result;
}

/**
 * 使用reduce计算阶乘（函数式风格）
 */
function factorialReduce(n) {
    if (n < 0) throw new Error("n必须非负");
    if (n <= 1) return 1;
    
    return Array.from({length: n}, (_, i) => i + 1)
        .reduce((acc, val) => acc * val, 1);
}

/**
 * Gamma函数近似（计算非整数"阶乘"）
 * n! = Γ(n+1)
 * 使用Lanczos近似
 */
function gammaLanczos(z) {
    // Lanczos近似系数
    const p = [
        676.5203681218851,
        -1259.1392167224028,
        771.32342877765313,
        -176.61502916214059,
        12.507343278686905,
        -0.13857109526572012,
        9.9843695780195716e-6,
        1.5056327351493116e-7
    ];
    
    if (z < 0.5) {
        // 反射公式
        return Math.PI / (Math.sin(Math.PI * z) * gammaLanczos(1 - z));
    }
    
    z -= 1;
    let x = 0.99999999999980993;
    for (let i = 0; i < p.length; i++) {
        x += p[i] / (z + i + 1);
    }
    
    const t = z + p.length - 0.5;
    return Math.sqrt(2 * Math.PI) * Math.pow(t, z + 0.5) * Math.exp(-t) * x;
}

/**
 * 排列数 P(n, k) = n! / (n-k)!
 */
function permutation(n, k) {
    if (k > n || k < 0) throw new Error("k必须在0到n之间");
    if (n > 170) throw new Error("n太大");
    
    let result = 1;
    for (let i = n; i > n - k; i--) {
        result *= i;
    }
    return result;
}

/**
 * 组合数 C(n, k) = n! / (k! × (n-k)!)
 */
function combination(n, k) {
    if (k > n || k < 0) throw new Error("k必须在0到n之间");
    if (k > n / 2) k = n - k;  // 利用对称性
    if (n > 170) throw new Error("n太大");
    
    let result = 1;
    for (let i = 1; i <= k; i++) {
        result = result * (n - k + i) / i;
    }
    return Math.round(result);
}

/**
 * 测试函数
 */
function testFactorial() {
    console.log("==================================================");
    console.log("    阶乘计算演示 (Factorial n!)");
    console.log("==================================================\n");
    
    // 阶乘表
    console.log("阶乘表 (0! 到 20!):");
    console.log("--------------------------------------------------");
    for (let i = 0; i <= 20; i++) {
        const result = factorialIterative(i);
        console.log(`${i.toString().padStart(2)}! = ${result.toString().padStart(20)}`);
    }
    
    // BigInt阶乘
    console.log("\n==================================================");
    console.log("BigInt阶乘 (ES2020+):");
    console.log("==================================================");
    for (let n of [50, 100, 200]) {
        const factN = factorialBigInt(n);
        const digits = factN.toString().length;
        console.log(`${n}! 的位数: ${digits}`);
    }
    
    // 显示100!的前50位和后20位
    const fact100 = factorialBigInt(100);
    const fact100Str = fact100.toString();
    console.log(`\n100! = ${fact100Str.substring(0, 50)}...${fact100Str.substring(fact100Str.length - 20)}`);
    
    // Gamma函数（非整数阶乘）
    console.log("\n==================================================");
    console.log("Gamma函数（非整数阶乘）:");
    console.log("==================================================");
    for (let x of [0.5, 1, 2, 3, 4, 5, 10]) {
        const gamma = gammaLanczos(x);
        console.log(`Γ(${x}) = ${gamma.toFixed(6)} (即 ${x-1}!)`);
    }
    
    // 排列组合
    console.log("\n==================================================");
    console.log("排列组合计算:");
    console.log("==================================================");
    console.log(`P(10, 3) = ${permutation(10, 3)} (从10个中取3个排列)`);
    console.log(`C(10, 3) = ${combination(10, 3)} (从10个中取3个组合)`);
    console.log(`C(52, 5) = ${combination(52, 5)} (扑克牌5张组合数)`);
    
    // 杨辉三角
    console.log("\n==================================================");
    console.log("杨辉三角（前8行）:");
    console.log("==================================================");
    for (let n = 0; n < 8; n++) {
        let row = ' '.repeat((8 - n) * 2);
        for (let k = 0; k <= n; k++) {
            row += combination(n, k).toString().padStart(4) + ' ';
        }
        console.log(row);
    }
    
    // 数学性质
    console.log("\n==================================================");
    console.log("阶乘的数学性质:");
    console.log("==================================================");
    console.log("• 定义: n! = n × (n-1) × ... × 2 × 1");
    console.log("• 递推: n! = n × (n-1)!");
    console.log("• 0! = 1（空积的定义）");
    console.log("• 增长: 阶乘比指数增长更快");
    console.log("• Gamma函数: Γ(n+1) = n!（扩展到实数）");
    
    // 应用场景
    console.log("\n==================================================");
    console.log("应用场景:");
    console.log("==================================================");
    console.log("• 排列组合: 计算可能性的总数");
    console.log("• 概率论: 生日问题、洗牌算法");
    console.log("• 泰勒级数: e^x = Σ x^n/n!");
    console.log("• 图论: 计算不同图的数量");
    console.log("• 密码学: 密钥空间计算");
    
    // JavaScript特性
    console.log("\n==================================================");
    console.log("JavaScript特性:");
    console.log("==================================================");
    console.log("• BigInt支持: ES2020+可计算任意大阶乘");
    console.log("• Number.MAX_SAFE_INTEGER: 9007199254740991");
    console.log("• 170! ≈ 7.26 × 10^306（接近Number.MAX_VALUE）");
    console.log("• Gamma函数: 可计算非整数的阶乘");
}

// 导出模块
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        factorialIterative,
        factorialRecursive,
        factorialTailRecursive,
        factorialBigInt,
        factorialReduce,
        gammaLanczos,
        permutation,
        combination,
        testFactorial
    };
    
    if (require.main === module) {
        testFactorial();
    }
} else {
    // 浏览器环境
    window.factorialModule = {
        factorialIterative,
        factorialRecursive,
        factorialTailRecursive,
        factorialBigInt,
        factorialReduce,
        gammaLanczos,
        permutation,
        combination,
        testFactorial
    };
}
