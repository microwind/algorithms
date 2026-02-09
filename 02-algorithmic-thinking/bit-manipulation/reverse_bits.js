/**
 * 反转二进制位
 *
 * 问题：反转一个32位整数的二进制表示
 *
 * 核心思想：
 * - 逐位提取和重建
 * - 位操作实现高效反转
 *
 * 时间复杂度: O(32)
 * 空间复杂度: O(1)
 */

/**
 * 逐位反转：从右到左提取，从左到右重建
 *
 * @param {number} n 输入的32位整数
 * @returns {number} 反转后的32位整数
 */
function reverseBitsIterative(n) {
    let result = 0;
    for (let i = 0; i < 32; i++) {
        // 提取n的最右边一位
        const bit = n & 1;
        // 右移n，处理下一位
        n >>>= 1;
        // result左移，为新位腾出空间
        result = (result << 1) | bit;
    }
    return result >>> 0;  // 转换为32位无符号整数
}

/**
 * 手动位操作：逐位反转
 *
 * @param {number} n 输入的32位整数
 * @returns {number} 反转后的32位整数
 */
function reverseBitsManual(n) {
    let result = 0;
    // 处理32位
    for (let i = 0; i < 32; i++) {
        // 从n中提取第i位
        if (((n >>> i) & 1) === 1) {
            // 在result中设置第(31-i)位
            result |= (1 << (31 - i));
        }
    }
    return result >>> 0;  // 转换为32位无符号整数
}

/**
 * 按字节反转（4个字节的整数）
 *
 * @param {number} n 输入的32位整数
 * @returns {number} 反转后的32位整数
 */
function reverseBitsByteByByte(n) {
    let result = 0;

    // 处理4个字节
    for (let i = 0; i < 4; i++) {
        // 提取第i个字节
        const byteVal = (n >>> (i * 8)) & 0xFF;

        // 反转字节内的位
        let reversedByte = 0;
        for (let j = 0; j < 8; j++) {
            if (((byteVal >>> j) & 1) === 1) {
                reversedByte |= (1 << (7 - j));
            }
        }

        // 将反转后的字节放在结果的正确位置
        result |= (reversedByte << ((3 - i) * 8));
    }

    return result >>> 0;  // 转换为32位无符号整数
}

/**
 * 使用查表法反转（针对频繁调用优化）
 *
 * @param {number} n 输入的32位整数
 * @returns {number} 反转后的32位整数
 */
function reverseBitsLookup(n) {
    const lookup = [];

    // 预计算0-255的位反转
    for (let i = 0; i < 256; i++) {
        let byteVal = i;
        let reversed = 0;
        for (let j = 0; j < 8; j++) {
            if (((byteVal >>> j) & 1) === 1) {
                reversed |= (1 << (7 - j));
            }
        }
        lookup[i] = reversed;
    }

    let result = 0;
    for (let i = 0; i < 4; i++) {
        const byteVal = (n >>> (i * 8)) & 0xFF;
        const reversedByte = lookup[byteVal];
        result |= (reversedByte << ((3 - i) * 8));
    }

    return result >>> 0;  // 转换为32位无符号整数
}

/**
 * 打印32位二进制表示
 */
function printBinary32(n) {
    return '0b' + (n >>> 0).toString(2).padStart(32, '0');
}

// 测试函数
console.log("=== 反转二进制位 ===\n");

// 测试用例1：基本用例
console.log("1. 基本用例:");
const testCases = [
    1,           // 最右位为1
    2,           // 倒数第二位为1
    3,           // 最右两位为1
    43261596,    // 复杂用例
];

for (let num of testCases) {
    const result = reverseBitsIterative(num);

    console.log(`  输入:   ${printBinary32(num)} (${num})`);
    console.log(`  输出:   ${printBinary32(result)} (${result})\n`);
}

// 测试用例2：比较不同算法
console.log("2. 不同算法的结果比较:");
const testNums = [0, 1, 2, 7, 15, 255, 43261596, 2147483647];

for (let num of testNums) {
    const iter = reverseBitsIterative(num);
    const manual = reverseBitsManual(num);
    const byteByByte = reverseBitsByteByByte(num);
    const lookup = reverseBitsLookup(num);

    const allMatch = (iter === manual) && (manual === byteByByte) && (byteByByte === lookup);
    console.log(`  n=${num}: 所有算法一致 = ${allMatch ? "是" : "否"}`);
}
console.log();

// 测试用例3：特殊值
console.log("3. 特殊值:");
const special = [
    {value: 0x00000000, desc: "全0"},
    {value: 0xFFFFFFFF, desc: "全1"},
    {value: 0x80000000, desc: "仅最左位为1"},
    {value: 0x00000001, desc: "仅最右位为1"},
    {value: 0x12345678, desc: "任意值"},
];

for (let s of special) {
    const num = s.value >>> 0;
    const result = reverseBitsIterative(num);
    console.log(`  ${s.desc.padEnd(15, ' ')}: 0x${num.toString(16).toUpperCase().padStart(8, '0')} -> 0x${result.toString(16).toUpperCase().padStart(8, '0')}`);
}
console.log();

// 测试用例4：验证对称性（反转两次应该恢复）
console.log("4. 验证反转的对称性（反转两次应该恢复）:");
const symmetryNums = [1, 7, 255, 43261596];

for (let num of symmetryNums) {
    const once = reverseBitsIterative(num);
    const twice = reverseBitsIterative(once);
    console.log(`  ${num}: 反转两次后恢复 = ${num === twice ? "是" : "否"}`);
}
