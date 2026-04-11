/**
 * Copyright © https://github.com/microwind All rights reserved.
 *
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/*
*
 * RSA加密算法 - 非对称加密
 *
 * 问题：使用RSA进行非对称加密
 *
 * 核心思想：
 * - 生成两个大质数p和q
 * - 计算n = p * q
 * - 计算φ(n) = (p-1)*(q-1)
 * - 选择公钥指数e
 * - 计算私钥指数d
 * - 加密：c = m^e mod n
 * - 解密：m = c^d mod n
 *
 * 注意：此实现仅用于教学目的
 * 实际应用应使用成熟的加密库
 *
 * 时间复杂度: O(n^3) for key generation
 * 空间复杂度: O(n)
*/

class RSA {
    n: bigint;
    e: bigint;
    d: bigint;

    constructor(n: bigint, e: bigint, d: bigint) {
        this.n = n;
        this.e = e;
        this.d = d;
    }

    /*
    *
     * 检查是否为质数
    */
    static isPrime(num: bigint): boolean {
        if (num < 2n) return false;
        if (num === 2n) return true;
        if (num % 2n === 0n) return false;

        for (let i = 3n; i * i <= num; i += 2n) {
            if (num % i === 0n) return false;
        }
        return true;
    }

    /*
    *
     * 生成随机质数
    */
    static generatePrime(bits: number): bigint {
        while (true) {
            let num = BigInt(2) ** BigInt(bits - 1);
            num += BigInt(Math.floor(Math.random() * Number(BigInt(2) ** BigInt(bits - 1))));
            if (RSA.isPrime(num)) {
                return num;
            }
        }
    }

    /*
    *
     * 计算模逆元
    */
    static modInverse(a: bigint, m: bigint): bigint {
        let [m0, x, y] = [m, 1n, 0n];

        if (m === 1n) return 0n;

        while (a > 1n) {
            let q = a / m;
            let t = m;
            m = a % m;
            a = t;
            t = y;
            y = x - q * y;
            x = t;
        }

        if (x < 0n) x += m0;
        return x;
    }

    /*
    *
     * 模幂运算
    */
    static modPow(base: bigint, exponent: bigint, modulus: bigint): bigint {
        let result = 1n;
        base = base % modulus;

        while (exponent > 0n) {
            if (exponent % 2n === 1n) {
                result = (result * base) % modulus;
            }
            exponent = exponent >> 1n;
            base = (base * base) % modulus;
        }

        return result;
    }

    /*
    *
     * 创建新的RSA实例
    */
    static create(bitLength: number): RSA {
        console.log("生成RSA密钥对...");

        // 选择两个大质数
        const p = RSA.generatePrime(bitLength / 2);
        const q = RSA.generatePrime(bitLength / 2);
        console.log(`生成质数p: ${p}`);
        console.log(`生成质数q: ${q}`);

        // 计算n = p * q
        const n = p * q;
        console.log(`计算n = p * q: ${n}`);

        // 计算φ(n) = (p-1)*(q-1)
        const phi = (p - 1n) * (q - 1n);
        console.log(`计算φ(n): ${phi}`);

        // 选择公钥指数e
        const e = 65537n;
        console.log(`选择公钥指数e: ${e}`);

        // 计算私钥指数d
        const d = RSA.modInverse(e, phi);
        console.log(`计算私钥指数d: ${d}`);
        console.log("RSA密钥对生成完成");

        return new RSA(n, e, d);
    }

    /*
    *
     * RSA加密
    */
    encrypt(message: string): string {
        console.log("开始RSA加密...");
        console.log(`明文: ${message}`);

        const m = BigInt(message.split('').map(c => c.charCodeAt(0)).join(''));
        console.log(`转换为数字: ${m}`);

        const c = RSA.modPow(m, this.e, this.n);
        console.log(`加密计算 c = m^e mod n: ${c}`);

        const ciphertext = c.toString(16);
        console.log(`加密完成，密文长度: ${ciphertext.length}`);
        return ciphertext;
    }

    /*
    *
     * RSA解密
    */
    decrypt(ciphertext: string): string {
        console.log("开始RSA解密...");
        console.log(`密文: ${ciphertext}`);

        const c = BigInt('0x' + ciphertext);
        console.log(`转换为数字: ${c}`);

        const m = RSA.modPow(c, this.d, this.n);
        console.log(`解密计算 m = c^d mod n: ${m}`);

        const message = m.toString().split('').map(c => String.fromCharCode(parseInt(c, 10))).join('');
        console.log(`解密完成，明文长度: ${message.length}`);
        return message;
    }

    /*
    *
     * 获取公钥信息
    */
    getPublicKey(): string {
        return `公钥(n,e): (${this.n},${this.e})`;
    }

    /*
    *
     * 获取私钥信息
    */
    getPrivateKey(): string {
        return `私钥(n,d): (${this.n},${this.d})`;
    }
}

/*
*
 * 主函数
*/
function main(): void {
    console.log("=== RSA算法演示 ===");

    const rsa = RSA.create(64); // 64位密钥（教学用，实际应使用更大密钥）
    console.log(rsa.getPublicKey());
    console.log(rsa.getPrivateKey());

    const message = "Hi";
    console.log(`\n原始消息: ${message}`);
    console.log(`消息长度: ${message.length}`);

    // 加密
    const encrypted = rsa.encrypt(message);
    console.log(`加密结果: ${encrypted}`);

    // 解密
    const decrypted = rsa.decrypt(encrypted);
    console.log(`解密结果: ${decrypted}`);

    // 验证
    const isValid = message === decrypted;
    if (isValid) {
        console.log("验证结果: ✓ 成功");
    } else {
        console.log("验证结果: ✗ 失败");
    }
    console.log("=== 演示结束 ===");

    console.log("\n注意：此实现仅用于教学目的，");
    console.log("实际应用应使用成熟的加密库如crypto或node-forge。");
}

// 运行测试
main();
