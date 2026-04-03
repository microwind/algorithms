/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use num_bigint::{BigUint, RandGen};
use num_traits::{Zero, One};
use rand::Rng;

struct RSA {
    n: BigUint,
    e: BigUint,
    d: BigUint,
}

impl RSA {
    /**
     * 创建新的RSA实例
     * @param bit_length 密钥位数
     */
    fn new(bit_length: usize) -> Self {
        let mut rsa = RSA {
            n: BigUint::zero(),
            e: BigUint::zero(),
            d: BigUint::zero(),
        };
        rsa.generate_keys(bit_length);
        rsa
    }
    
    /**
     * 生成RSA密钥对
     * @param bit_length 密钥位数
     */
    fn generate_keys(&mut self, bit_length: usize) {
        println!("生成RSA密钥对...");
        let mut rng = rand::thread_rng();
        
        // 选择两个大质数（简化版）
        let p = rng.gen_biguint(bit_length / 2);
        let q = rng.gen_biguint(bit_length / 2);
        println!("生成质数p: {}", p);
        println!("生成质数q: {}", q);
        
        // 计算n = p * q
        self.n = &p * &q;
        println!("计算n = p * q: {}", self.n);
        
        // 计算φ(n) = (p-1)*(q-1)
        let phi = (&p - BigUint::one()) * (&q - BigUint::one());
        println!("计算φ(n): {}", phi);
        
        // 选择公钥指数e
        self.e = BigUint::from(65537u32);
        println!("选择公钥指数e: {}", self.e);
        
        // 计算私钥指数d
        self.d = self.mod_inverse(&self.e, &phi).unwrap();
        println!("计算私钥指数d: {}", self.d);
        println!("RSA密钥对生成完成");
    }
    
    /**
     * 简化的模逆计算
     * @param a 数a
     * @param m 模数m
     * @return a模m的逆元
     */
    fn mod_inverse(&self, a: &BigUint, m: &BigUint) -> Option<BigUint> {
        // 简化的模逆计算（实际应用中需要更复杂的算法）
        // 这里仅作演示，实际RSA实现需要完善的数论函数
        Some(a.clone())
    }
    
    /**
     * RSA加密算法
     * @param message 明文消息
     * @return Base64编码的密文
     */
    fn encrypt(&self, message: &str) -> String {
        println!("开始RSA加密...");
        println!("明文: {}", message);
        
        let m = BigUint::from_bytes_be(message.as_bytes());
        println!("转换为数字: {}", m);
        
        let c = m.modpow(&self.e, &self.n);
        println!("加密计算 c = m^e mod n: {}", c);
        
        // 转换为base64
        use base64::{Engine as _, engine::general_purpose::STANDARD_NO_PAD};
        let result = STANDARD_NO_PAD.encode(c.to_bytes_be());
        println!("加密完成，密文长度: {}", result.len());
        result
    }
    
    /**
     * RSA解密算法
     * @param ciphertext Base64编码的密文
     * @return 解密后的明文
     */
    fn decrypt(&self, ciphertext: &str) -> Option<String> {
        println!("开始RSA解密...");
        println!("密文: {}", ciphertext);
        
        use base64::{Engine as _, engine::general_purpose::STANDARD_NO_PAD};
        
        let c_bytes = STANDARD_NO_PAD.decode(ciphertext).ok()?;
        let c = BigUint::from_bytes_be(&c_bytes);
        println!("转换为数字: {}", c);
        
        let m = c.modpow(&self.d, &self.n);
        println!("解密计算 m = c^d mod n: {}", m);
        
        String::from_utf8(m.to_bytes_be()).ok()
    }
    
    /**
     * 获取公钥信息
     * @return 公钥字符串
     */
    fn get_public_key(&self) -> String {
        format!("公钥(n,e): ({},{})", self.n, self.e)
    }
    
    /**
     * 获取私钥信息
     * @return 私钥字符串
     */
    fn get_private_key(&self) -> String {
        format!("私钥(n,d): ({},{})", self.n, self.d)
    }
}

/**
 * 主函数，演示RSA加密和解密
 */
fn main() {
    println!("=== RSA算法演示 ===");
    
    let rsa = RSA::new(512); // 512位密钥
    println!("{}", rsa.get_public_key());
    println!("{}", rsa.get_private_key());
    
    let message = "Hello, RSA!";
    println!("\n原始消息: {}", message);
    println!("消息长度: {}", message.len());
    
    // 加密
    let encrypted = rsa.encrypt(message);
    println!("加密结果: {}", encrypted);
    
    // 解密
    if let Some(decrypted) = rsa.decrypt(&encrypted) {
        println!("解密结果: {}", decrypted);
        println!("解密长度: {}", decrypted.len());
        
        // 验证
        let is_valid = message == decrypted;
        println!("验证结果: {}", if is_valid { "✓ 成功" } else { "✗ 失败" });
    } else {
        println!("解密失败");
    }
    println!("=== 演示结束 ===");
}
