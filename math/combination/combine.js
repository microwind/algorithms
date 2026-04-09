/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 组合计算 (Combination)
 * 计算从n个元素中选取k个元素的组合数
 */

function factorial(n) {
    let product = 1;
    for (let i = 1; i <= n; i++) {
        product *= i;
    }
    return product;
}

function combine(n, k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

function main() {
    const n = 5;
    console.log("组合计算 C(n,k)");
    console.log("===============");
    
    for (let k = 1; k <= n; k++) {
        const result = combine(n, k);
        console.log(`C(${n},${k}) = ${result}`);
    }
}

main();

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { factorial, combine };
}
