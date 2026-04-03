const crypto = require('crypto');

class AES {
    static encrypt(plainText, key) {
        // 创建密钥
        const keyBytes = Buffer.from(key, 'utf8');
        
        // 创建加密器
        const cipher = crypto.createCipher('aes-128-ecb', keyBytes);
        
        // 加密
        let encrypted = cipher.update(plainText, 'utf8', 'base64');
        encrypted += cipher.final('base64');
        
        return encrypted;
    }
    
    static decrypt(encryptedText, key) {
        // 创建密钥
        const keyBytes = Buffer.from(key, 'utf8');
        
        // 创建解密器
        const decipher = crypto.createDecipher('aes-128-ecb', keyBytes);
        
        // 解密
        let decrypted = decipher.update(encryptedText, 'base64', 'utf8');
        decrypted += decipher.final('utf8');
        
        return decrypted;
    }
    
    static main() {
        const plainText = "Hello, World!";
        const key = "1234567890123456"; // 16字节密钥
        
        console.log("原文:", plainText);
        
        const encrypted = AES.encrypt(plainText, key);
        console.log("加密后:", encrypted);
        
        const decrypted = AES.decrypt(encrypted, key);
        console.log("解密后:", decrypted);
        
        console.log("验证:", plainText === decrypted);
    }
}

// 示例使用
AES.main();
