/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.Base64;

public class RSA {
    
    private BigInteger n, e, d;
    
    /**
     * RSA构造函数
     * @param bitLength 密钥位数
     */
    public RSA(int bitLength) {
        generateKeys(bitLength);
    }
    
    /**
     * 生成RSA密钥对
     * @param bitLength 密钥位数
     */
    private void generateKeys(int bitLength) {
        System.out.println("生成RSA密钥对...");
        SecureRandom random = new SecureRandom();
        
        // 选择两个大质数
        BigInteger p = BigInteger.probablePrime(bitLength / 2, random);
        BigInteger q = BigInteger.probablePrime(bitLength / 2, random);
        System.out.println("生成质数p: " + p);
        System.out.println("生成质数q: " + q);
        
        // 计算n = p * q
        n = p.multiply(q);
        System.out.println("计算n = p * q: " + n);
        
        // 计算φ(n) = (p-1)*(q-1)
        BigInteger phi = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));
        System.out.println("计算φ(n): " + phi);
        
        // 选择公钥指数e
        e = BigInteger.valueOf(65537);
        System.out.println("选择公钥指数e: " + e);
        
        // 计算私钥指数d
        d = e.modInverse(phi);
        System.out.println("计算私钥指数d: " + d);
        System.out.println("RSA密钥对生成完成");
    }
    
    /**
     * RSA加密算法
     * @param message 明文消息
     * @return Base64编码的密文
     */
    public String encrypt(String message) {
        System.out.println("开始RSA加密...");
        System.out.println("明文: " + message);
        
        BigInteger m = new BigInteger(message.getBytes());
        System.out.println("转换为数字: " + m);
        
        BigInteger c = m.modPow(e, n);
        System.out.println("加密计算 c = m^e mod n: " + c);
        
        String result = Base64.getEncoder().encodeToString(c.toByteArray());
        System.out.println("加密完成，密文长度: " + result.length());
        return result;
    }
    
    /**
     * RSA解密算法
     * @param ciphertext Base64编码的密文
     * @return 解密后的明文
     */
    public String decrypt(String ciphertext) {
        System.out.println("开始RSA解密...");
        System.out.println("密文: " + ciphertext);
        
        BigInteger c = new BigInteger(Base64.getDecoder().decode(ciphertext));
        System.out.println("转换为数字: " + c);
        
        BigInteger m = c.modPow(d, n);
        System.out.println("解密计算 m = c^d mod n: " + m);
        
        String result = new String(m.toByteArray());
        System.out.println("解密完成，明文长度: " + result.length());
        return result;
    }
    
    /**
     * 获取公钥信息
     * @return 公钥字符串
     */
    public String getPublicKey() {
        return String.format("公钥(n,e): (%s,%s)", n, e);
    }
    
    /**
     * 获取私钥信息
     * @return 私钥字符串
     */
    public String getPrivateKey() {
        return String.format("私钥(n,d): (%s,%s)", n, d);
    }
    
    /**
     * 主函数，演示RSA加密和解密
     */
    public static void main(String[] args) {
        System.out.println("=== RSA算法演示 ===");
        
        RSA rsa = new RSA(512); // 512位密钥
        System.out.println(rsa.getPublicKey());
        System.out.println(rsa.getPrivateKey());
        
        String message = "Hello, RSA!";
        System.out.println("\n原始消息: " + message);
        System.out.println("消息长度: " + message.length());
        
        // 加密
        String encrypted = rsa.encrypt(message);
        System.out.println("加密结果: " + encrypted);
        
        // 解密
        String decrypted = rsa.decrypt(encrypted);
        System.out.println("解密结果: " + decrypted);
        
        // 验证
        boolean isValid = message.equals(decrypted);
        System.out.println("验证结果: " + (isValid ? "✓ 成功" : "✗ 失败"));
        System.out.println("=== 演示结束 ===");
    }
}
