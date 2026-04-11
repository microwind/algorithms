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
 * 原理：
 * - 将n与1进行AND操作，检查最右边的位
 * - 右移n，继续检查下一位
 * - 重复直到n为0
 *
 * @param n 输入数
 * @return 1的个数
*/
function countOnesLoop(n: number): number {
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
 * @param n 输入数
 * @return 1的个数
*/
function countOnesKernighan(n: number): number {
    let count = 0;
    while (n > 0) {
        n &= n - 1;  // 移除最右边的1
        count++;
    }
    return count;
}

/*
*
 * 使用查表法（用于频繁调用的优化）
 *
 * @param n 输入数
 * @return 1的个数
*/
function countOnesTable(n: number): number {
    // 预计算0-255中1的个数
    const lookup: number[] = [];
    for (let i = 0; i < 256; i++) {
        lookup.push(countOnesLoop(i));
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
 * 并行计数法（位操作优化）
 *
 * @param n 输入数
 * @return 1的个数
*/
function countOnesParallel(n: number): number {
    n = ((n & 0xaaaaaaaa) >>> 1) + (n & 0x55555555);
    n = ((n & 0xcccccccc) >>> 2) + (n & 0x33333333);
    n = ((n & 0xf0f0f0f0) >>> 4) + (n & 0x0f0f0f0f);
    n = ((n & 0xff00ff00) >>> 8) + (n & 0x00ff00ff);
    n = ((n & 0xffff0000) >>> 16) + (n & 0x0000ffff);
    return n;
}

/*
*
 * 打印二进制表示
*/
function printBinary(n: number): string {
    return '0b' + n.toString(2).padStart(8, '0');
}

/*
*
 * 测试函数
*/
function main(): void {
    console.log("=== 计数1位 (Hamming权重) ===\n");

    // 测试用例1：基本用例
    console.log("1. 基本用例:");
    const testNums = [0, 1, 3, 5, 7, 15, 31, 63, 127, 255];

    for (const num of testNums) {
        const count = countOnesLoop(num);
        console.log(`  ${num.toString().padStart(3)} ${printBinary(num)}: ${count}个1`);
    }
    console.log();

    // 测试用例2：比较不同算法
    console.log("2. 不同算法的结果比较:");
    const testNums2 = [1, 7, 15, 127, 255, 1023];

    for (const num of testNums2) {
        const loop = countOnesLoop(num);
        const kern = countOnesKernighan(num);
        const table = countOnesTable(num);
        const parallel = countOnesParallel(num);

        console.log(`  n=${num.toString().padStart(4)}: loop=${loop}, kernighan=${kern}, table=${table}, parallel=${parallel}`);
    }
    console.log();

    // 测试用例3：大数值
    console.log("3. 大数值:");
    const largeNums = [
        0xFFFF,      // 2^16 - 1
        0xFFFFF,     // 2^20 - 1
        0x3FFFFFFF   // 2^30 - 1
    ];

    for (const num of largeNums) {
        const count = countOnesKernighan(num);
        console.log(`  0x${num.toString(16).toUpperCase().padStart(8, '0')}: ${count}个1`);
    }
    console.log();

    // 测试用例4：稀疏1的情况（Kernighan优势明显）
    console.log("4. 稀疏1的情况（Kernighan优势明显）:");
    const sparseNums = [1, 2, 4, 8, 16, 32, 64, 128, 256];

    for (const num of sparseNums) {
        const count = countOnesKernighan(num);
        console.log(`  ${num.toString().padStart(3)} (2^?): ${count}个1`);
    }
    console.log();

    // 测试用例5：特殊值
    console.log("5. 特殊值:");
    console.log(`  0x00000000: ${countOnesLoop(0x00000000)}个1`);
    console.log(`  0xFFFFFFFF: ${countOnesLoop(0xFFFFFFFF)}个1`);
    console.log(`  0x80000000: ${countOnesLoop(0x80000000)}个1`);
    console.log(`  0x00000001: ${countOnesLoop(0x00000001)}个1`);
}

// 运行测试
main();
