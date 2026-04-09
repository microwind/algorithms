/**
 * 数学基础 - 最大公约数与最小公倍数 (GCD and LCM)
 * 使用欧几里得算法计算两个整数的最大公约数
 * 时间复杂度: O(log min(a,b))
 */

/**
 * 欧几里得算法 - 迭代版
 * 
 * 算法原理：gcd(a, b) = gcd(b, a mod b)
 */
function gcd(a, b) {
    a = Math.abs(a);
    b = Math.abs(b);
    
    while (b !== 0) {
        const temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * 欧几里得算法 - 递归版
 */
function gcdRecursive(a, b) {
    a = Math.abs(a);
    b = Math.abs(b);
    
    if (b === 0) return a;
    return gcdRecursive(b, a % b);
}

/**
 * 二进制GCD算法（Stein算法）
 */
function gcdBinary(a, b) {
    if (a === 0) return b;
    if (b === 0) return a;
    
    a = Math.abs(a);
    b = Math.abs(b);
    
    // 找出公因数2的幂次
    let shift = 0;
    while (((a | b) & 1) === 0) {
        a >>= 1;
        b >>= 1;
        shift++;
    }
    
    // 去除a的所有因数2
    while ((a & 1) === 0) {
        a >>= 1;
    }
    
    // 主循环
    while (b !== 0) {
        while ((b & 1) === 0) {
            b >>= 1;
        }
        
        if (a > b) {
            [a, b] = [b, a];
        }
        
        b = b - a;
    }
    
    return a << shift;
}

/**
 * 最小公倍数 (LCM)
 * 
 * 公式: lcm(a, b) = |a × b| / gcd(a, b)
 */
function lcm(a, b) {
    if (a === 0 || b === 0) return 0;
    return Math.abs(a / gcd(a, b) * b);
}

/**
 * 扩展欧几里得算法
 * 
 * 返回 [gcd, x, y] 使得 ax + by = gcd(a, b)
 */
function gcdExtended(a, b) {
    if (b === 0) {
        return [a, 1, 0];
    }
    
    const [gcd, x1, y1] = gcdExtended(b, a % b);
    const x = y1;
    const y = x1 - Math.floor(a / b) * y1;
    
    return [gcd, x, y];
}

/**
 * 多个数的GCD
 */
function gcdMultiple(...numbers) {
    if (numbers.length === 0) return 0;
    
    return numbers.reduce((acc, num) => gcd(acc, num));
}

/**
 * 多个数的LCM
 */
function lcmMultiple(...numbers) {
    if (numbers.length === 0) return 0;
    
    return numbers.reduce((acc, num) => lcm(acc, num));
}

/**
 * 判断两个数是否互质
 */
function areCoprime(a, b) {
    return gcd(a, b) === 1;
}

/**
 * 欧拉函数 φ(n)
 */
function eulerTotient(n) {
    if (n <= 0) return 0;
    
    let result = n;
    let temp = n;
    
    for (let p = 2; p * p <= temp; p++) {
        if (temp % p === 0) {
            while (temp % p === 0) {
                temp = Math.floor(temp / p);
            }
            result -= Math.floor(result / p);
        }
    }
    
    if (temp > 1) {
        result -= Math.floor(result / temp);
    }
    
    return result;
}

/**
 * 测试函数
 */
function testGCD() {
    console.log("==================================================");
    console.log("  最大公约数计算 (GCD) - 欧几里得算法");
    console.log("==================================================\n");
    
    // GCD测试
    const testCases = [[48, 18], [56, 98], [100, 35], [101, 103]];
    console.log("GCD测试:");
    console.log("--------------------------------------------------");
    testCases.forEach(([a, b]) => {
        const gcdVal = gcd(a, b);
        const lcmVal = lcm(a, b);
        console.log(`gcd(${a}, ${b}) = ${gcdVal}, lcm(${a}, ${b}) = ${lcmVal}`);
    });
    
    // 扩展欧几里得
    console.log("\n==================================================");
    console.log("扩展欧几里得算法:");
    console.log("==================================================");
    const a = 240, b = 46;
    const [g, x, y] = gcdExtended(a, b);
    console.log(`${a} × ${x} + ${b} × ${y} = ${g}`);
    console.log(`验证: ${a * x} + ${b * y} = ${a * x + b * y}`);
    
    // 多个数的GCD
    console.log("\n==================================================");
    console.log("多个数的GCD和LCM:");
    console.log("==================================================");
    const numbers = [12, 18, 24, 36];
    console.log(`数字: ${numbers.join(", ")}`);
    console.log(`gcd = ${gcdMultiple(...numbers)}`);
    console.log(`lcm = ${lcmMultiple(...numbers)}`);
    
    // 欧拉函数
    console.log("\n==================================================");
    console.log("欧拉函数 φ(n):");
    console.log("==================================================");
    for (let i = 1; i <= 20; i++) {
        process.stdout.write(`φ(${i.toString().padStart(2)}) = ${eulerTotient(i).toString().padStart(2)}  `);
        if (i % 5 === 0) console.log();
    }
    
    // 数学性质
    console.log("\n==================================================");
    console.log("数学性质:");
    console.log("==================================================");
    console.log("• gcd(a, b) = gcd(b, a mod b)");
    console.log("• gcd(a, b) × lcm(a, b) = |a × b|");
    console.log("• 贝祖定理: 存在x,y使得 ax + by = gcd(a,b)");
    
    // JavaScript特性
    console.log("\n==================================================");
    console.log("JavaScript特性:");
    console.log("==================================================");
    console.log("• 展开运算符: ...numbers处理多个参数");
    console.log("• 解构赋值: [a, b] = [b, a]");
    console.log("• BigInt支持: ES2020+可处理大数");
    console.log("• 函数式编程: reduce, map, filter");
}

// 导出模块
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        gcd, gcdRecursive, gcdBinary,
        lcm, gcdExtended,
        gcdMultiple, lcmMultiple,
        areCoprime, eulerTotient,
        testGCD
    };
    
    if (require.main === module) {
        testGCD();
    }
} else {
    window.gcdModule = {
        gcd, gcdRecursive, gcdBinary,
        lcm, gcdExtended,
        gcdMultiple, lcmMultiple,
        areCoprime, eulerTotient,
        testGCD
    };
}
