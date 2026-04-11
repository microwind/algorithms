/*
*
 * SHA-256哈希算法 - 密码学哈希函数
 *
 * 问题：生成消息的固定长度哈希值
 *
 * 注意：此实现使用Node.js内置crypto模块
 * 实际应用应使用成熟的加密库
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
*/

// @ts-ignore - Node.js crypto module
const crypto = require('crypto');

/*
*
 * SHA-256哈希函数（使用Node.js内置crypto模块）
*/
function sha256Hash(message: string): string {
    // @ts-ignore
    return crypto.createHash('sha256').update(message).digest('hex');
}

/*
*
 * 主函数
*/
function main(): void {
    console.log("=== SHA-256哈希算法 ===");

    const message = "Hello, World!";
    console.log(`消息: ${message}`);

    const hash = sha256Hash(message);
    console.log(`SHA-256: ${hash}`);

    console.log("\n注意：此实现使用Node.js内置crypto模块，");
    console.log("实际应用应使用成熟的加密库。");
}

// 运行测试
main();
