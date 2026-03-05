/*
*
 * 计数1位 - Hamming权重
 *
 * 问题：计算整数二进制表示中1的个数
 *
 * 核心思想：
 * - 逐位检查：与1进行AND操作
 * - Brian Kernighan算法：n & (n-1) 移除最右边的1
 * - 预计算查表法（对于频繁调用优化）
 *
 * 时间复杂度: O(log n) 或 O(1) 取决于实现方式
 * 空间复杂度: O(1)
*/

/*
*
 * 逐位检查：循环检查每一位
 *
 * @param {number} n 输入数
 * @returns {number} 1的个数
*/
function countOnesLoop(n) {
    let count = 0;
    while (n > 0) {
        count += n & 1;
        n >>>= 1;  // 无符号右移
    }
    return count;
}

/*
*
 * Brian Kernighan算法：移除最右边的1
 *
 * 原理：
 * - n & (n-1) 移除n的最右边的1
 * - 重复这个操作直到n为0
 * - 操作次数就是1的个数
 * - 只需O(k)的时间，k是1的个数
 *
 * @param {number} n 输入数
 * @returns {number} 1的个数
*/
function countOnesKernighan(n) {
    let count = 0;
    while (n > 0) {
        n &= n - 1;  // 移除最右边的1
        count++;
    }
    return count;
}

/*
*
 * 使用JavaScript内置方法
 *
 * @param {number} n 输入数
 * @returns {number} 1的个数
*/
function countOnesBuiltin(n) {
    return (n >>> 0).toString(2).split('0').join('').length;
}

/*
*
 * 使用查表法（用于频繁调用的优化）
 *
 * @param {number} n 输入数
 * @returns {number} 1的个数
*/
function countOnesTable(n) {
    const lookup = [];
    for (let i = 0; i < 256; i++) {
        lookup[i] = countOnesLoop(i);
    }

    let count = 0;
    while (n > 0) {
        count += lookup[n & 0xFF];
        n >>>= 8;
    }
    return count;
}

/*
*
 * 打印二进制表示
*/
function printBinary(n) {
    return '0b' + n.toString(2).padStart(8, '0');
}

// 测试函数
console.log("=== 计数1位 (Hamming权重) ===\n");

// 测试用例1：基本用例
console.log("1. 基本用例:");
const testNums = [0, 1, 3, 5, 7, 15, 31, 63, 127, 255];

for (let num of testNums) {
    const count = countOnesLoop(num);
    console.log(`  ${String(num).padStart(3, ' ')} ${printBinary(num)}: ${count}个1`);
}
console.log();

// 测试用例2：比较不同算法
console.log("2. 不同算法的结果比较:");
const testNums2 = [1, 7, 15, 127, 255, 1023];

for (let num of testNums2) {
    const loop = countOnesLoop(num);
    const kernighan = countOnesKernighan(num);
    const table = countOnesTable(num);
    const builtin = countOnesBuiltin(num);

    console.log(`  n=${String(num).padStart(4, ' ')}: loop=${loop}, kernighan=${kernighan}, table=${table}, builtin=${builtin}`);
}
console.log();

// 测试用例3：大数值
console.log("3. 大数值:");
const largeNums = [
    0xFFFF,      // 2^16 - 1
    0xFFFFF,     // 2^20 - 1
    0x3FFFFFFF   // 2^30 - 1
];

for (let num of largeNums) {
    const count = countOnesKernighan(num);
    console.log(`  0x${num.toString(16).toUpperCase().padStart(8, '0')}: ${count}个1`);
}
console.log();

// 测试用例4：稀疏1的情况（Kernighan优势明显）
console.log("4. 稀疏1的情况（Kernighan优势明显）:");
const sparseNums = [1, 2, 4, 8, 16, 32, 64, 128, 256];

for (let num of sparseNums) {
    const count = countOnesKernighan(num);
    console.log(`  ${String(num).padStart(3, ' ')} (2^?): ${count}个1`);
}
console.log();

// 测试用例5：特殊值
console.log("5. 特殊值:");
console.log(`  0x00000000: ${countOnesLoop(0x00000000)}个1`);
console.log(`  0xFFFFFFFF: ${countOnesLoop(0xFFFFFFFF >>> 0)}个1`);
console.log(`  0x80000000: ${countOnesLoop(0x80000000 >>> 0)}个1`);
console.log(`  0x00000001: ${countOnesLoop(0x00000001)}个1`);
