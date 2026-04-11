/*
*
 * 凯撒密码 - 简单的替换加密
 *
 * 问题：将字母表中的每个字母移动固定位数
 *
 * 核心思想：
 * - 字母替换
 * - 循环移位
 * - 保持大小写
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
*/

/*
*
 * 凯撒加密
*/
function caesarEncrypt(text: string, shift: number): string {
    let result = "";

    for (let i = 0; i < text.length; i++) {
        const c = text[i];

        if (c >= 'A' && c <= 'Z') {
            result += String.fromCharCode((c.charCodeAt(0) - 65 + shift) % 26 + 65);
        } else if (c >= 'a' && c <= 'z') {
            result += String.fromCharCode((c.charCodeAt(0) - 97 + shift) % 26 + 97);
        } else {
            result += c;
        }
    }

    return result;
}

/*
*
 * 凯撒解密
*/
function caesarDecrypt(text: string, shift: number): string {
    return caesarEncrypt(text, 26 - (shift % 26));
}

/*
*
 * 主函数
*/
function main(): void {
    console.log("=== 凯撒密码 ===");

    const text = "Hello, World!";
    const shift = 3;

    console.log(`明文: ${text}`);
    console.log(`移位数: ${shift}`);

    // 加密
    const encrypted = caesarEncrypt(text, shift);
    console.log(`加密后: ${encrypted}`);

    // 解密
    const decrypted = caesarDecrypt(encrypted, shift);
    console.log(`解密后: ${decrypted}`);

    console.log(`验证: ${text === decrypted}`);
}

// 运行测试
main();
