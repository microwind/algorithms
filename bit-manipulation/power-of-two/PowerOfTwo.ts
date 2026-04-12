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
 * @param n 待检查的数
 * @return true 如果是2的幂，否则 false
*/
function isPowerOfTwo(n: number): boolean {
    return n > 0 && (n & (n - 1)) === 0;
}

/*
*
 * 使用位计数判断（备选方案）
 *
 * 统计二进制表示中1的个数，如果只有一个1则是2的幂
 *
 * @param n 待检查的数
 * @return true 如果是2的幂，否则 false
*/
function isPowerOfTwoBuiltin(n: number): boolean {
    if (n <= 0) return false;

    let count = 0;
    let temp = n;
    while (temp > 0) {
        count += temp & 1;
        temp >>>= 1;
    }
    return count === 1;
}

/*
*
 * 计算2的幂中的位置（幂的指数）
 *
 * 例如：
 * - 8 (1000) 的位置是 3 (2^3 = 8)
 * - 16 (10000) 的位置是 4 (2^4 = 16)
 *
 * @param n 2的幂
 * @return 指数，如果不是2的幂返回 -1
*/
function powerOfTwoExponent(n: number): number {
    if (!isPowerOfTwo(n)) {
        return -1;
    }

    let exp = 0;
    let temp = n;
    while ((temp & 1) === 0) {
        temp >>>= 1;
        exp++;
    }
    return exp;
}

/*
*
 * 找到大于等于n的最小2的幂
 *
 * 例如：
 * - n=5 -> 8 (2^3)
 * - n=8 -> 8 (2^3)
 * - n=10 -> 16 (2^4)
 *
 * @param n 输入数
 * @return 大于等于n的最小2的幂
*/
function nextPowerOfTwo(n: number): number {
    if (n <= 1) return 1;

    // 如果已经是2的幂，直接返回
    if (isPowerOfTwo(n)) {
        return n;
    }

    // 找到下一个2的幂
    n--;
    n |= n >>> 1;
    n |= n >>> 2;
    n |= n >>> 4;
    n |= n >>> 8;
    n |= n >>> 16;
    return n + 1;
}

/*
*
 * 获取一个2的幂是2的几次方
 *
 * @param n 2的幂
 * @return 幂的指数
*/
function getExponent(n: number): number {
    if (!isPowerOfTwo(n)) return -1;

    let exp = 0;
    let temp = n;
    while ((temp & 1) === 0) {
        exp++;
        temp >>>= 1;
    }
    return exp;
}

/*
*
 * 打印二进制表示
*/
function printBinary(n: number): string {
    return '0b' + n.toString(2).padStart(16, '0');
}

/*
*
 * 测试函数
*/
function main(): void {
    console.log("=== 2的幂 ===\n");

    // 测试用例1：判断是否为2的幂
    console.log("1. 判断是否为2的幂:");
    const testNums = [1, 2, 3, 4, 5, 8, 16, 17, 32, 100];

    for (const num of testNums) {
        console.log(`  ${num.toString().padStart(3)}: ${isPowerOfTwo(num) ? '是2的幂' : '不是2的幂'}`);
    }
    console.log();

    // 测试用例2：获取幂的指数
    console.log("2. 获取2的幂中的指数:");
    const powerNums = [1, 2, 4, 8, 16, 32, 64, 128, 256];

    for (const num of powerNums) {
        const exp = getExponent(num);
        console.log(`  2^${exp} = ${num}`);
    }
    console.log();

    // 测试用例3：找下一个2的幂
    console.log("3. 找大于等于n的最小2的幂:");
    const testNums2 = [1, 3, 5, 7, 8, 9, 15, 16, 17, 100];

    for (const num of testNums2) {
        const next = nextPowerOfTwo(num);
        console.log(`  n=${num.toString().padStart(3)} -> ${next}`);
    }
    console.log();

    // 测试用例4：边界情况
    console.log("4. 边界情况:");
    console.log(`  0 是2的幂: ${isPowerOfTwo(0) ? '是' : '否'}`);
    console.log(`  1 是2的幂: ${isPowerOfTwo(1) ? '是' : '否'}`);
    console.log(`  -8 是2的幂: ${isPowerOfTwo(-8) ? '是' : '否'}`);
    console.log();

    // 测试用例5：二进制表示
    console.log("5. 2的幂的二进制表示:");
    for (let i = 0; i <= 4; i++) {
        const num = 1 << i;
        console.log(`  2^${i} = ${num.toString().padStart(2)} = ${printBinary(num)}`);
    }
}

// 运行测试
main();
