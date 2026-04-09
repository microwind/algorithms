/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 阶乘计算 (Factorial)
 * 计算非负整数的阶乘 n!
 * 支持递归、迭代和TypeScript类型安全
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
function factorialIterative(n: number): number {
    if (n < 0) throw new Error("n必须非负");
    if (n > 170) throw new Error("n太大，会导致Infinity");
    
    let result: number = 1;
    for (let i: number = 2; i <= n; i++) {
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
function factorialRecursive(n: number): number {
    if (n < 0) throw new Error("n必须非负");
    if (n <= 1) return 1;
    return n * factorialRecursive(n - 1);
}

/**
 * BigInt阶乘计算（ES2020+）
 * 
 * 可以计算任意大的阶乘
 */
function factorialBigInt(n: number | bigint): bigint {
    const bigN: bigint = typeof n === 'bigint' ? n : BigInt(n);
    
    if (bigN < 0) throw new Error("n必须非负");
    
    let result: bigint = 1n;
    for (let i: bigint = 2n; i <= bigN; i++) {
        result *= i;
    }
    return result;
}

/**
 * 泛型阶乘函数（演示TypeScript泛型）
 */
function factorialGeneric<T extends number>(n: T): number {
    return factorialIterative(n);
}

/**
 * 排列数 P(n, k) = n! / (n-k)!
 */
function permutation(n: number, k: number): number {
    if (k > n || k < 0) throw new Error("k必须在0到n之间");
    if (n > 170) throw new Error("n太大");
    
    let result: number = 1;
    for (let i: number = n; i > n - k; i--) {
        result *= i;
    }
    return result;
}

/**
 * 组合数 C(n, k) = n! / (k! × (n-k)!)
 */
function combination(n: number, k: number): number {
    if (k > n || k < 0) throw new Error("k必须在0到n之间");
    if (k > n / 2) k = n - k;  // 利用对称性
    if (n > 170) throw new Error("n太大");
    
    let result: number = 1;
    for (let i: number = 1; i <= k; i++) {
        result = result * (n - k + i) / i;
    }
    return Math.round(result);
}

/**
 * 接口定义：阶乘结果
 */
interface FactorialResult {
    n: number;
    factorial: number;
    method: string;
    timestamp: Date;
}

/**
 * 创建阶乘结果对象
 */
function createFactorialResult(n: number, method: string = "iterative"): FactorialResult {
    return {
        n,
        factorial: factorialIterative(n),
        method,
        timestamp: new Date()
    };
}

/**
 * 阶乘类（面向对象风格）
 */
class FactorialCalculator {
    private cache: Map<number, number> = new Map();
    
    /**
     * 计算阶乘（带缓存）
     */
    calculate(n: number): number {
        // 检查缓存
        if (this.cache.has(n)) {
            return this.cache.get(n)!;
        }
        
        const result = factorialIterative(n);
        this.cache.set(n, result);
        return result;
    }
    
    /**
     * 计算排列数
     */
    permutation(n: number, k: number): number {
        return permutation(n, k);
    }
    
    /**
     * 计算组合数
     */
    combination(n: number, k: number): number {
        return combination(n, k);
    }
    
    /**
     * 清空缓存
     */
    clearCache(): void {
        this.cache.clear();
    }
    
    /**
     * 获取缓存大小
     */
    getCacheSize(): number {
        return this.cache.size;
    }
}

/**
 * 测试函数
 */
function testFactorial(): void {
    console.log("==================================================");
    console.log("    阶乘计算演示 (Factorial n!) - TypeScript");
    console.log("==================================================\n");
    
    // 阶乘表
    console.log("阶乘表 (0! 到 20!):");
    console.log("--------------------------------------------------");
    for (let i: number = 0; i <= 20; i++) {
        const result: number = factorialIterative(i);
        console.log(`${i.toString().padStart(2)}! = ${result.toString().padStart(20)}`);
    }
    
    // BigInt阶乘
    console.log("\n==================================================");
    console.log("BigInt阶乘 (ES2020+):");
    console.log("==================================================");
    for (const n of [50, 100, 200]) {
        const factN: bigint = factorialBigInt(n);
        const digits: number = factN.toString().length;
        console.log(`${n}! 的位数: ${digits}`);
    }
    
    // 显示100!的前50位和后20位
    const fact100: bigint = factorialBigInt(100);
    const fact100Str: string = fact100.toString();
    console.log(`\n100! = ${fact100Str.substring(0, 50)}...${fact100Str.substring(fact100Str.length - 20)}`);
    
    // 排列组合
    console.log("\n==================================================");
    console.log("排列组合计算:");
    console.log("==================================================");
    console.log(`P(10, 3) = ${permutation(10, 3)} (从10个中取3个排列)`);
    console.log(`C(10, 3) = ${combination(10, 3)} (从10个中取3个组合)`);
    console.log(`C(52, 5) = ${combination(52, 5)} (扑克牌5张组合数)`);
    
    // 使用类计算
    console.log("\n==================================================");
    console.log("使用FactorialCalculator类:");
    console.log("==================================================");
    const calculator: FactorialCalculator = new FactorialCalculator();
    for (let i: number = 5; i <= 15; i++) {
        const result: number = calculator.calculate(i);
        console.log(`${i}! = ${result} (从缓存获取: ${calculator.getCacheSize()})`);
    }
    
    // 杨辉三角
    console.log("\n==================================================");
    console.log("杨辉三角（前8行）:");
    console.log("==================================================");
    for (let n: number = 0; n < 8; n++) {
        let row: string = ' '.repeat((8 - n) * 2);
        for (let k: number = 0; k <= n; k++) {
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
    console.log("• 斯特林近似: n! ≈ √(2πn) × (n/e)^n");
    
    // TypeScript特性
    console.log("\n==================================================");
    console.log("TypeScript特性:");
    console.log("==================================================");
    console.log("• 类型安全: 编译时类型检查");
    console.log("• 接口定义: 结构化类型系统");
    console.log("• 泛型支持: 类型参数化");
    console.log("• 类与面向对象: 支持封装、继承、多态");
    console.log("• BigInt支持: ES2020+任意精度整数");
    console.log("• 类型推断: 自动推断变量类型");
    
    // 代码示例
    console.log("\n==================================================");
    console.log("TypeScript代码示例:");
    console.log("==================================================");
    console.log(`
// 类型安全的阶乘函数
function factorial(n: number): number {
    if (n < 0) throw new Error("n必须非负");
    let result: number = 1;
    for (let i: number = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// 使用接口定义结果结构
interface CombinationResult {
    n: number;
    k: number;
    result: number;
}

// 泛型函数
function memoize<T extends (...args: any[]) => any>(fn: T): T {
    const cache = new Map();
    return ((...args: any[]) => {
        const key = JSON.stringify(args);
        if (cache.has(key)) return cache.get(key);
        const result = fn(...args);
        cache.set(key, result);
        return result;
    }) as T;
}
`);
}

// 运行测试
testFactorial();

export {
    factorialIterative,
    factorialRecursive,
    factorialBigInt,
    factorialGeneric,
    permutation,
    combination,
    createFactorialResult,
    FactorialCalculator
};

export type { FactorialResult };
