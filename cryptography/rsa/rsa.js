/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class RSA {
    /**
     * RSA构造函数
     * @param {number} bitLength 密钥位数
     */
    constructor(bitLength = 512) {
        this.bitLength = bitLength;
        this.generateKeys();
    }
    
    /**
     * 生成RSA密钥对
     */
    generateKeys() {
        console.log("生成RSA密钥对...");
        
        // 简化的质数生成（实际应用中需要更复杂的算法）
        this.p = this.generatePrime(this.bitLength / 2);
        this.q = this.generatePrime(this.bitLength / 2);
        console.log(`生成质数p: ${this.p}`);
        console.log(`生成质数q: ${this.q}`);
        
        // 计算n = p * q
        this.n = this.p * this.q;
        console.log(`计算n = p * q: ${this.n}`);
        
        // 计算φ(n) = (p-1)*(q-1)
        this.phi = (this.p - 1) * (this.q - 1);
        console.log(`计算φ(n): ${this.phi}`);
        
        // 选择公钥指数e
        this.e = 65537;
        console.log(`选择公钥指数e: ${this.e}`);
        
        // 计算私钥指数d
        this.d = this.modInverse(this.e, this.phi);
        console.log(`计算私钥指数d: ${this.d}`);
        console.log("RSA密钥对生成完成");
    }
    
    /**
     * 简化的素数测试
     * @param {number} n 待测试的数
     * @return 是否为质数
     */
    isPrime(n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 === 0) return false;
        
        for (let i = 3; i * i <= n; i += 2) {
            if (n % i === 0) return false;
        }
        return true;
    }
    
    /**
     * 生成指定位数的大质数
     * @param {number} bits 位数
     * @return 大质数
     */
    generatePrime(bits) {
        while (true) {
            let num = Math.floor(Math.random() * (1 << bits)) | (1 << (bits - 1)) | 1;
            if (this.isPrime(num)) {
                return num;
            }
        }
    }
    
    /**
     * 扩展欧几里得算法
     * @param {number} a 第一个数
     * @param {number} b 第二个数
     * @return [g, x, y] 其中g是最大公约数，ax + by = g
     */
    extendedGcd(a, b) {
        if (a === 0) return [b, 0, 1];
        let [g, y, x] = this.extendedGcd(b % a, a);
        return [g, x - Math.floor(b / a) * y, y];
    }
    
    /**
     * 计算模逆
     * @param {number} a 数a
     * @param {number} m 模数m
     * @return a模m的逆元
     */
    modInverse(a, m) {
        const [g, x] = this.extendedGcd(a, m);
        if (g !== 1) return null;
        return ((x % m) + m) % m;
    }
    
    /**
     * RSA加密算法
     * @param {string} message 明文消息
     * @return Base64编码的密文
     */
    encrypt(message) {
        console.log("开始RSA加密...");
        console.log(`明文: ${message}`);
        
        const m = BigInt('0x' + Buffer.from(message).toString('hex'));
        console.log(`转换为数字: ${m}`);
        
        const c = m ** BigInt(this.e) % BigInt(this.n);
        console.log(`加密计算 c = m^e mod n: ${c}`);
        
        // 转换为base64
        const hex = c.toString(16).padStart(Math.ceil(c.toString(16).length / 2) * 2, '0');
        const bytes = Buffer.from(hex, 'hex');
        const result = bytes.toString('base64');
        console.log(`加密完成，密文长度: ${result.length}`);
        return result;
    }
    
    /**
     * RSA解密算法
     * @param {string} ciphertext Base64编码的密文
     * @return 解密后的明文
     */
    decrypt(ciphertext) {
        console.log("开始RSA解密...");
        console.log(`密文: ${ciphertext}`);
        
        const bytes = Buffer.from(ciphertext, 'base64');
        const hex = bytes.toString('hex');
        const c = BigInt('0x' + hex);
        console.log(`转换为数字: ${c}`);
        
        const m = c ** BigInt(this.d) % BigInt(this.n);
        console.log(`解密计算 m = c^d mod n: ${m}`);
        
        // 转换回字符串
        const decryptedHex = m.toString(16).padStart(Math.ceil(m.toString(16).length / 2) * 2, '0');
        const decryptedBytes = Buffer.from(decryptedHex, 'hex');
        const result = decryptedBytes.toString();
        console.log(`解密完成，明文长度: ${result.length}`);
        return result;
    }
    
    /**
     * 获取公钥信息
     * @return 公钥字符串
     */
    getPublicKey() {
        return `公钥(n,e): (${this.n},${this.e})`;
    }
    
    /**
     * 获取私钥信息
     * @return 私钥字符串
     */
    getPrivateKey() {
        return `私钥(n,d): (${this.n},${this.d})`;
    }
}

/**
 * 主函数，演示RSA加密和解密
 */
function main() {
    console.log("=== RSA算法演示 ===");
    
    const rsa = new RSA(512); // 512位密钥
    console.log(rsa.getPublicKey());
    console.log(rsa.getPrivateKey());
    
    const message = "Hello, RSA!";
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
    console.log(`验证结果: ${isValid ? '✓ 成功' : '✗ 失败'}`);
    console.log("=== 演示结束 ===");
}

// 执行主函数
main();
