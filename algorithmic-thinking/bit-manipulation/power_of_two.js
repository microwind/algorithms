/*
*
 * 2的幂 - 位运算和数字性质
 *
 * 问题：
 * 1. 检查一个数是否是2的幂
 * 2. 计算2的幂相关的位操作
 *
 * 核心思想：
 * - 2的幂在二进制表示中只有一个1（1, 2, 4, 8, 16, ...）
 * - n & (n-1) == 0 可以判断是否为2的幂
 * - 利用位运算的性质进行快速计算
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
*/

/*
*
 * 判断一个数是否是2的幂
 *
 * 原理：
 * - 2的幂的二进制表示只有一个1，其余为0
 * - 例如：8 = 1000 (二进制)
 * - n-1 = 0111 (二进制)
 * - n & (n-1) = 0
 *
 * @param {number} n 待检查的数
 * @returns {boolean} true 如果是2的幂，否则 false
*/
function isPowerOfTwo(n) {
    return n > 0 && (n & (n - 1)) === 0;
}

/*
*
 * 使用位计数判断（备选方案）
 *
 * @param {number} n 待检查的数
 * @returns {boolean} true 如果是2的幂，否则 false
*/
function isPowerOfTwoBuiltin(n) {
    if (n <= 0) return false;
    return (n.toString(2).match(/1/g) || []).length === 1;
}

/*
*
 * 计算2的幂中的位置（幂的指数）
 *
 * @param {number} n 2的幂
 * @returns {number} 指数，如果不是2的幂返回 -1
*/
function powerOfTwoExponent(n) {
    if (!isPowerOfTwo(n)) {
        return -1;
    }

    let exp = 0;
    while ((n & 1) === 0) {
        n >>= 1;
        exp++;
    }
    return exp;
}

/*
*
 * 找到大于等于n的最小2的幂
 *
 * @param {number} n 输入数
 * @returns {number} 大于等于n的最小2的幂
*/
function nextPowerOfTwo(n) {
    if (n <= 1) return 1;

    // 如果已经是2的幂，直接返回
    if (isPowerOfTwo(n)) {
        return n;
    }

    // 找到下一个2的幂
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

/*
*
 * 获取一个2的幂是2的几次方
 *
 * @param {number} n 2的幂
 * @returns {number} 幂的指数
*/
function getExponent(n) {
    if (!isPowerOfTwo(n)) return -1;

    let exp = 0;
    while ((n & 1) === 0) {
        exp++;
        n >>= 1;
    }
    return exp;
}

/*
*
 * 打印二进制表示
*/
function printBinary(n) {
    return '0b' + n.toString(2).padStart(16, '0');
}

// 测试函数
console.log("=== 2的幂 ===\n");

// 测试用例1：判断是否为2的幂
console.log("1. 判断是否为2的幂:");
const testNums = [1, 2, 3, 4, 5, 8, 16, 17, 32, 100];

for (let num of testNums) {
    console.log(`  ${String(num).padStart(3, ' ')}: ${isPowerOfTwo(num) ? "是2的幂" : "不是2的幂"}`);
}
console.log();

// 测试用例2：获取幂的指数
console.log("2. 获取2的幂中的指数:");
const powerNums = [1, 2, 4, 8, 16, 32, 64, 128, 256];

for (let num of powerNums) {
    const exp = getExponent(num);
    console.log(`  2^${exp} = ${num}`);
}
console.log();

// 测试用例3：找下一个2的幂
console.log("3. 找大于等于n的最小2的幂:");
const testNums2 = [1, 3, 5, 7, 8, 9, 15, 16, 17, 100];

for (let num of testNums2) {
    const next = nextPowerOfTwo(num);
    console.log(`  n=${String(num).padStart(3, ' ')} -> ${next}`);
}
console.log();

// 测试用例4：边界情况
console.log("4. 边界情况:");
console.log(`  0 是2的幂: ${isPowerOfTwo(0) ? "是" : "否"}`);
console.log(`  1 是2的幂: ${isPowerOfTwo(1) ? "是" : "否"}`);
console.log(`  -8 是2的幂: ${isPowerOfTwo(-8) ? "是" : "否"}`);
console.log();

// 测试用例5：二进制表示
console.log("5. 2的幂的二进制表示:");
for (let i = 0; i <= 4; i++) {
    const num = 1 << i;
    console.log(`  2^${i} = ${String(num).padStart(2, ' ')} = ${printBinary(num)}`);
}
